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

void selectionSort(vector<int> &a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[minIdx])
                minIdx = j;
        }
        if (minIdx != i)
            swap(a[i], a[minIdx]);
    }
}

int main() {
    vector<int> a = {12, 4, 7, 11, 56, 34, 2};
    selectionSort(a);
    for (int x : a)
        cout << x << " ";
    cout << endl;
    return 0;
}
