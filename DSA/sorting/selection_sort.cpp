/*
 * ============================================================================
 * TOPIC    : Sorting
 * FILE     : selection_sort.cpp
 * PROBLEM  : Selection Sort
 * APPROACH : Select minimum from unsorted suffix each pass
 * COMPLEX  : Time: O(n²)  |  Space: O(1)  |  Stable: No
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// SELECTION SORT — Har pass me minimum select karo
// ────────────────────────────────────────────────────────────────────────────
// Unsorted part se min dhundho, current position pe swap
// Exactly n-1 passes — har pass ek element final position pe
// Unstable — equal elements ka order change ho sakta hai
// ════════════════════════════════════════════════════════════════════════════

// ── selectionSort: min select karke sort ────────────────────────────────────
//   1) i se minIdx dhundho unsorted suffix me
//   2) minIdx != i -> swap
//   3) i++ — agla position fix
void selectionSort(vector<int> &a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[minIdx])
                minIdx = j;  // chhota element track
        }
        if (minIdx != i)
            swap(a[i], a[minIdx]);  // min ko i pe lao
    }
}

// ── main: selection sort demo ───────────────────────────────────────────────
int main() {
    vector<int> a = {12, 4, 7, 11, 56, 34, 2};
    selectionSort(a);
    for (int x : a)
        cout << x << " ";
    cout << endl;
    return 0;
}
