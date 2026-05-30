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
            break;
    }
}

int main() {
    vector<int> a = {64, 34, 25, 12, 22, 11, 90};
    bubbleSort(a);
    for (int x : a)
        cout << x << " ";
    cout << endl;
    return 0;
}
