#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>

// Inclusión directa de los algoritmos
#include "algorithms/naive.cpp"
#include "algorithms/strassen.cpp"

using namespace std;

// Carga una matriz cuadrada de n x n desde un archivo de texto
vector<vector<int>> leerMatriz(const string& ruta, int n) {
    vector<vector<int>> matriz(n, vector<int>(n, 0));
    ifstream file(ruta);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir " << ruta << endl;
        return {};
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!(file >> matriz[i][j])) {
                cerr << "Error al leer datos en " << ruta << endl;
                file.close();
                return {};
            }
        }
    }
    file.close();
    return matriz;
}

// Guarda la matriz resultante en el archivo de salida
void guardarMatriz(const string& ruta, const vector<vector<int>>& matriz) {
    ofstream file(ruta);
    if (!file.is_open()) {
        cerr << "Error al guardar resultado en " << ruta << endl;
        return;
    }
    int n = matriz.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file << matriz[i][j] << (j + 1 < n ? " " : "");
        }
        file << "\n";
    }
    file.close();
}

int main() {
    // Parámetros definidos por matrix_generator.py
    vector<int> Ns = {16, 64, 256, 1024};
    vector<string> Ts = {"dispersa", "diagonal", "densa"};
    vector<string> Ds = {"D0", "D10"};
    vector<string> Ms = {"a", "b", "c"};
    vector<string> Algoritmos = {"naive", "strassen"};

    // Archivo CSV para registrar mediciones
    ofstream csv("data/measurements/matrix_measurements.csv");
    if (!csv.is_open()) {
        cerr << "Error al crear data/measurements/matrix_measurements.csv" << endl;
        return 1;
    }
    csv << "n,tipo,dominio,muestra,algoritmo,tiempo_ms\n";

    for (int n : Ns) {
        for (const string& t : Ts) {
            for (const string& d : Ds) {
                for (const string& m : Ms) {
                    string baseName = to_string(n) + "_" + t + "_" + d + "_" + m;
                    string file1 = "data/matrix_input/" + baseName + "_1.txt";
                    string file2 = "data/matrix_input/" + baseName + "_2.txt";

                    cout << "\n------------------------------------------" << endl;
                    cout << "Procesando par: " << baseName << endl;

                    vector<vector<int>> A = leerMatriz(file1, n);
                    vector<vector<int>> B = leerMatriz(file2, n);

                    if (A.empty() || B.empty()) {
                        cout << "Archivos de entrada no encontrados o dañados. Omitiendo..." << endl;
                        continue;
                    }

                    for (const string& alg : Algoritmos) {
                        cout << "  [" << alg << "] Multiplicando... " << flush;

                        vector<vector<int>> C;
                        auto start = chrono::high_resolution_clock::now();

                        if (alg == "naive") {
                            C = multiplyNaive(A, B);
                        } else if (alg == "strassen") {
                            C = multiplyStrassen(A, B);
                        }

                        auto end = chrono::high_resolution_clock::now();
                        double duracionMs = chrono::duration<double, milli>(end - start).count();

                        // Guardar métrica en CSV
                        csv << n << "," << t << "," << d << "," << m << ","
                            << alg << "," << duracionMs << "\n";
                        csv.flush();

                        // Guardar archivo de salida independiente
                        string outputFile = "data/matrix_output/" + baseName + "_" + alg + "_out.txt";
                        guardarMatriz(outputFile, C);

                        cout << "OK (" << duracionMs << " ms)" << endl;
                    }
                }
            }
        }
    }

    csv.close();
    cout << "\nMediciones completadas. Archivo generado en data/measurements/matrix_measurements.csv" << endl;
    return 0;
}