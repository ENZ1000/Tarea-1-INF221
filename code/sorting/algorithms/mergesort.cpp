/**
 Autor: Enzo Marambio Vasquez
 Rol USM: 202473576-4
 Asignatura: INF-221 Algoritmos y Complejidad
 Tarea 1 - 2026-2
 
 Implementación optimizada de Merge Sort.
 
 Referencia:
 GeeksforGeeks: Merge Sort Algorithm (https://www.geeksforgeeks.org/merge-sort/)
 */
#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int>& arr, vector<int>& temp, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (int p = left; p <= right; p++) {
        arr[p] = temp[p];
    }
}

void mergeSortRecursive(vector<int>& arr, vector<int>& temp, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSortRecursive(arr, temp, left, mid);
    mergeSortRecursive(arr, temp, mid + 1, right);
    merge(arr, temp, left, mid, right);
}

vector<int> mergeSort(vector<int>& arr) {
    if (arr.size() <= 1) return arr;
    vector<int> temp(arr.size());
    mergeSortRecursive(arr, temp, 0, arr.size() - 1);
    return arr;
}