/*
 * ============================================================================
 * TOPIC    : Sorting
 * FILE     : insertion_sort.cpp
 * PROBLEM  : Insertion Sort
 * APPROACH : Insert each element into sorted prefix
 * COMPLEX  : Time: O(n²)  |  Space: O(1)  |  Stable: Yes
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// INSERTION SORT — Card sorting jaisa approach
// ────────────────────────────────────────────────────────────────────────────
// Sorted prefix me naya element sahi jagah insert karo
// Key leke left shift — jab tak bade elements hain
// Best case O(n) — nearly sorted array ke liye fast
// ════════════════════════════════════════════════════════════════════════════

// ── insertionSort: sorted prefix me insert karo ─────────────────────────────
//   1) key = a[i] — current element
//   2) j se left shift jab tak a[j]>key
//   3) a[j+1] = key — sahi position pe rakho
void insertionSort(vector<int> &a) {
    int n = a.size();
    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];  // right shift
            j--;
        }
        a[j + 1] = key;  // key insert
    }
}

// ── main: insertion sort demo ────────────────────────────────────────────────
int main() {
    vector<int> a = {10, 7, 1, 6, 14, 9};
    insertionSort(a);
    for (int x : a)
        cout << x << " ";
    cout << endl;
    return 0;
}
