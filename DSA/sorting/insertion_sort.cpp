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

void insertionSort(vector<int> &a) {
    int n = a.size();
    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

int main() {
    vector<int> a = {10, 7, 1, 6, 14, 9};
    insertionSort(a);
    for (int x : a)
        cout << x << " ";
    cout << endl;
    return 0;
}
