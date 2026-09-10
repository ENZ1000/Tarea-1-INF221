/**
 Autor: Enzo Marambio Vasquez
 Rol USM: 202473576-4
 Asignatura: INF-221 Algoritmos y Complejidad
 Tarea 1 - 2026-2
 
 Referencias:
 Referencia de implementacion: https://www.geeksforgeeks.org/c-program-multiply-two-matrices/
 */
#include <iostream>
#include <vector>

using namespace std;

// Multiplicación tradicional cúbica O(N^3)
vector<vector<int>> multiplyNaive(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    // Bucle clásico de 3 índices: filas de A, columnas de B y suma de productos
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}