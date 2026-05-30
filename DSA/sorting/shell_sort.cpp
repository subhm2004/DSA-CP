/*
 * ============================================================================
 * TOPIC    : Sorting
 * FILE     : shell_sort.cpp
 * PROBLEM  : Shell Sort (diminishing increment insertion sort)
 * APPROACH : Sort subarrays with gap, reduce gap until 1
 * COMPLEX  : Time: O(n^1.3) approx  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

void shellSort(vector<int> &a) {
    int n = a.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = a[i], j = i;
            while (j >= gap && a[j - gap] > temp) {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = temp;
        }
    }
}

int main() {
    vector<int> a = {12, 34, 54, 2, 3, 9, 11, 10};
    shellSort(a);
    for (int x : a)
        cout << x << " ";
    cout << endl;
    return 0;
}
