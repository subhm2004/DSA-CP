/*
 * ============================================================================
 * TOPIC    : Sorting
 * FILE     : heap_sort.cpp
 * PROBLEM  : Heap Sort
 * LEETCODE : 912 — Sort an Array (heap sort approach)
 * APPROACH : Build max heap; swap root with last, heapify down
 * COMPLEX  : Time: O(n log n)  |  Space: O(1)  |  Stable: No
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// HEAP SORT — Max heap se in-place sort
// ────────────────────────────────────────────────────────────────────────────
// Pehle max heap banao — phir root (max) ko end pe swap
// Heap size kam karo, root pe heapify — sorted array ban jata hai
// O(n log n) guaranteed, in-place — extra space nahi
// ════════════════════════════════════════════════════════════════════════════

// ── heapify: subtree ko max-heap property maintain ──────────────────────────
//   1) largest among i, left, right child
//   2) largest != i -> swap, recurse down
void heapify(vector<int> &a, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] > a[largest])
        largest = left;
    if (right < n && a[right] > a[largest])
        largest = right;

    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest);  // neeche heapify
    }
}

// ── heapSort: build heap, extract max repeatedly ────────────────────────────
//   1) n/2-1 se 0 tak heapify — heap build
//   2) root swap with last, heap size--, heapify root
void heapSort(vector<int> &a) {
    int n = a.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);  // max heap build

    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);      // max ko end pe
        heapify(a, i, 0);      // root heapify
    }
}

// ── main: heap sort demo ────────────────────────────────────────────────────
int main() {
    vector<int> a = {12, 11, 13, 5, 6, 7};
    heapSort(a);
    for (int x : a)
        cout << x << " ";
    cout << endl;
    return 0;
}
