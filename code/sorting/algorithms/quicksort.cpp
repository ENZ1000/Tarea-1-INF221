/**
 Autor: Enzo Marambio Vasquez
 Rol USM: 202473576-4
 Asignatura: INF-221 Algoritmos y Complejidad
 Tarea 1 - 2026-2
 
 Implementación de Quick Sort con partición de Hoare y pivote central.
 
 Referencias:
 Hoare, C. A. R. (1962). Quicksort. The Computer Journal, 5(1), 10-16.
 GeeksforGeeks: QuickSort using Random or Middle Pivoting (https://www.geeksforgeeks.org/quick-sort/)
 */
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int partitionHoare(vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    int pivot = arr[mid];

    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j) {
            return j;
        }

        swap(arr[i], arr[j]);
    }
}

void quickSortRecursive(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionHoare(arr, low, high);
        quickSortRecursive(arr, low, pi);
        quickSortRecursive(arr, pi + 1, high);
    }
}

vector<int> quickSort(vector<int>& arr) {
    if (arr.size() <= 1) return arr;
    quickSortRecursive(arr, 0, arr.size() - 1);
    return arr;
}