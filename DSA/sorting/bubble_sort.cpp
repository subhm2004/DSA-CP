/*
 * ============================================================================
 * TOPIC    : Sorting
 * FILE     : bubble_sort.cpp
 * PROBLEM  : Bubble Sort
 * APPROACH : Compare adjacent pairs; swap if out of order
 * COMPLEX  : Time: O(n²)  |  Space: O(1)  |  Stable: Yes
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// BUBBLE SORT — Adjacent swap se sort
// ────────────────────────────────────────────────────────────────────────────
// Har pass me largest element end ki taraf "bubble" hota hai
// swapped flag — agar koi swap nahi -> already sorted, early exit
// Stable sort — equal elements ka order preserve
// ════════════════════════════════════════════════════════════════════════════

// ── bubbleSort: adjacent compare karke sort ─────────────────────────────────
//   1) n-1 passes — har pass ek element sahi jagah
//   2) arr[j]>arr[j+1] -> swap
//   3) swapped false -> break (optimized)
void bubbleSort(vector<int> &a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;  // koi swap nahi — sorted hai
    }
}

// ── main: bubble sort demo ───────────────────────────────────────────────────
int main() {
    vector<int> a = {64, 34, 25, 12, 22, 11, 90};
    bubbleSort(a);
    for (int x : a)
        cout << x << " ";
    cout << endl;
    return 0;
}
