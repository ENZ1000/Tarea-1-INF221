/**
 Autor: Enzo Marambio Vasquez
 Rol USM: 202473576-4
 Asignatura: INF-221 Algoritmos y Complejidad
 Tarea 1 - 2026-2
 
 Referencias:
 Referencia de implementacion: https://www.geeksforgeeks.org/strassens-matrix-multiplication/
 */
#include <iostream>
#include <vector>

using namespace std;

// Funciones auxiliares para sumar y restar matrices cuadradas del mismo tamaño
vector<vector<int>> addMatrix(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

vector<vector<int>> subMatrix(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

// Algoritmo recursivo de Strassen
vector<vector<int>> multiplyStrassen(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();

    // Caso base: matriz de 1x1 (o umbral pequeño donde la multiplicación directa es más rápida)
    if (n <= 1) {
        vector<vector<int>> C(1, vector<int>(1));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int k = n / 2;

    // Submatrices de tamaño (n/2) x (n/2)
    vector<vector<int>> A11(k, vector<int>(k)), A12(k, vector<int>(k)),
                        A21(k, vector<int>(k)), A22(k, vector<int>(k)),
                        B11(k, vector<int>(k)), B12(k, vector<int>(k)),
                        B21(k, vector<int>(k)), B22(k, vector<int>(k));

    // Partición de matrices A y B en cuatro bloques cuadrantes
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // Fórmulas de las 7 multiplicaciones de Strassen (P1 a P7)
    // P1 = (A11 + A22) * (B11 + B22)
    vector<vector<int>> P1 = multiplyStrassen(addMatrix(A11, A22), addMatrix(B11, B22));
    // P2 = (A21 + A22) * B11
    vector<vector<int>> P2 = multiplyStrassen(addMatrix(A21, A22), B11);
    // P3 = A11 * (B12 - B22)
    vector<vector<int>> P3 = multiplyStrassen(A11, subMatrix(B12, B22));
    // P4 = A22 * (B21 - B11)
    vector<vector<int>> P4 = multiplyStrassen(A22, subMatrix(B21, B11));
    // P5 = (A11 + A12) * B22
    vector<vector<int>> P5 = multiplyStrassen(addMatrix(A11, A12), B22);
    // P6 = (A21 - A11) * (B11 + B12)
    vector<vector<int>> P6 = multiplyStrassen(subMatrix(A21, A11), addMatrix(B11, B12));
    // P7 = (A12 - A22) * (B21 + B22)
    vector<vector<int>> P7 = multiplyStrassen(subMatrix(A12, A22), addMatrix(B21, B22));

    // Reconstrucción de los cuatro cuadrantes de la matriz C
    // C11 = P1 + P4 - P5 + P7
    vector<vector<int>> C11 = addMatrix(subMatrix(addMatrix(P1, P4), P5), P7);
    // C12 = P3 + P5
    vector<vector<int>> C12 = addMatrix(P3, P5);
    // C21 = P2 + P4
    vector<vector<int>> C21 = addMatrix(P2, P4);
    // C22 = P1 - P2 + P3 + P6
    vector<vector<int>> C22 = addMatrix(subMatrix(addMatrix(P1, P3), P2), P6);

    // Unificación de los bloques en la matriz resultante C
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j]         = C11[i][j];
            C[i][j + k]     = C12[i][j];
            C[i + k][j]     = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    return C;
}