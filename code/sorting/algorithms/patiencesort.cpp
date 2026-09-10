/**
 Autor: Enzo Marambio Vasquez
 Rol USM: 202473576-4
 Asignatura: INF-221 Algoritmos y Complejidad
 Tarea 1 - 2026-2
 
 Implementación optimizada de Patience Sort con búsqueda binaria y Min-Heap.
 
 Referencia:
 GeeksforGeeks: Patience Sorting (https://www.geeksforgeeks.org/patience-sorting/)
 */

 #include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct HeapNode {
    int value;
    int pileIndex;

    bool operator>(const HeapNode& other) const {
        return value > other.value;
    }
};

vector<int> patienceSort(vector<int>& arr) {
    if (arr.size() <= 1) return arr;

    vector<vector<int>> piles;
    vector<int> pileTops;

    for (int x : arr) {
        auto it = lower_bound(pileTops.begin(), pileTops.end(), x);

        if (it == pileTops.end()) {
            piles.push_back({x});
            pileTops.push_back(x);
        } else {
            int index = distance(pileTops.begin(), it);
            piles[index].push_back(x);
            pileTops[index] = x;
        }
    }

    priority_queue<HeapNode, vector<HeapNode>, greater<HeapNode>> minHeap;

    for (size_t i = 0; i < piles.size(); i++) {
        minHeap.push({piles[i].back(), static_cast<int>(i)});
        piles[i].pop_back();
    }

    int outIdx = 0;
    while (!minHeap.empty()) {
        HeapNode current = minHeap.top();
        minHeap.pop();

        arr[outIdx++] = current.value;

        if (!piles[current.pileIndex].empty()) {
            minHeap.push({piles[current.pileIndex].back(), current.pileIndex});
            piles[current.pileIndex].pop_back();
        }
    }

    return arr;
}