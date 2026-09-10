#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <future>
#include <algorithm>

// Inclusión de las implementaciones
#include "algorithms/sort.cpp"
#include "algorithms/mergesort.cpp"
#include "algorithms/quicksort.cpp"
#include "algorithms/patiencesort.cpp"

using namespace std;

// Función para leer el arreglo desde data/array_input/
vector<int> leerArreglo(const string& ruta) {
    vector<int> arr;
    ifstream file(ruta);
    if (!file.is_open()) {
        cerr << "Error al abrir: " << ruta << endl;
        return arr;
    }
    int val;
    while (file >> val) {
        arr.push_back(val);
    }
    file.close();
    return arr;
}

// Función para guardar el arreglo ordenado en data/array_output/
void guardarArreglo(const string& ruta, const vector<int>& arr) {
    ofstream file(ruta);
    if (!file.is_open()) {
        cerr << "Error al escribir en: " << ruta << endl;
        return;
    }
    for (size_t i = 0; i < arr.size(); i++) {
        file << arr[i] << (i + 1 < arr.size() ? " " : "");
    }
    file << "\n";
    file.close();
}

// Wrapper para ejecutar el algoritmo correspondiente
vector<int> ejecutarAlgoritmo(const string& alg, vector<int> arr) {
    if (alg == "sort")         return sortArray(arr);
    if (alg == "mergesort")    return mergeSort(arr);
    if (alg == "quicksort")    return quickSort(arr);
    if (alg == "patiencesort") return patienceSort(arr);
    return arr;
}

int main() {
    // Parámetros descritos en el enunciado de la tarea
    vector<int> Ns = {10, 1000, 100000, 10000000};
    vector<string> Ts = {"ascendente", "descendente", "aleatorio"};
    vector<string> Ds = {"D1", "D7"};
    vector<string> Ms = {"a", "b", "c"};
    vector<string> Algoritmos = {"sort", "mergesort", "quicksort", "patiencesort"};

    // Límite de tiempo máximo permitido (15 minutos = 900 segundos)
    const chrono::seconds TIMEOUT_LIMIT(900);

    // Archivo CSV para guardar las mediciones que leerá plot_generator.py
    ofstream csv("data/measurements/sorting_measurements.csv");
    if (!csv.is_open()) {
        cerr << "Error al crear data/measurements/sorting_measurements.csv" << endl;
        return 1;
    }
    csv << "n,tipo,dominio,muestra,algoritmo,tiempo_ms\n";

    for (int n : Ns) {
        for (const string& t : Ts) {
            for (const string& d : Ds) {
                for (const string& m : Ms) {
                    string baseName = to_string(n) + "_" + t + "_" + d + "_" + m;
                    string inputFile = "data/array_input/" + baseName + ".txt";

                    cout << "\n------------------------------------------" << endl;
                    cout << "Procesando: " << inputFile << endl;

                    vector<int> original = leerArreglo(inputFile);
                    if (original.empty()) {
                        cout << "Archivo no encontrado o vacío. Omitiendo..." << endl;
                        continue;
                    }

                    for (const string& alg : Algoritmos) {
                        cout << "  [" << alg << "] Ejecutando... " << flush;

                        auto start = chrono::high_resolution_clock::now();

                        // Lanzamiento asíncrono para vigilar el límite de tiempo
                        auto task = async(launch::async, [alg, &original]() {
                            return ejecutarAlgoritmo(alg, original);
                        });

                        if (task.wait_for(TIMEOUT_LIMIT) == future_status::timeout) {
                            cout << "TIMEOUT (> 15 min)." << endl;
                            // Registro de -1 para indicar que no finalizó a tiempo
                            csv << n << "," << t << "," << d << "," << m << ","
                                << alg << ",-1\n";
                            csv.flush();
                        } else {
                            vector<int> res = task.get();
                            auto end = chrono::high_resolution_clock::now();
                            double duracionMs = chrono::duration<double, milli>(end - start).count();

                            // Registro del tiempo en milisegundos
                            csv << n << "," << t << "," << d << "," << m << ","
                                << alg << "," << duracionMs << "\n";
                            csv.flush();

                            // Guardar el archivo ordenado correspondiente
                            string outputFile = "data/array_output/" + baseName + "_" + alg + "_out.txt";
                            guardarArreglo(outputFile, res);

                            cout << "OK (" << duracionMs << " ms)" << endl;
                        }
                    }
                }
            }
        }
    }

    csv.close();
    cout << "\nMediciones finalizadas. Datos guardados en data/measurements/sorting_measurements.csv" << endl;
    return 0;
}