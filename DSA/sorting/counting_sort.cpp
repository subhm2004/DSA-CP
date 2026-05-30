/*
 * ============================================================================
 * TOPIC    : Sorting
 * FILE     : counting_sort.cpp
 * PROBLEM  : Counting Sort (non-negative integers in small range)
 * LEETCODE : 912 — Sort an Array (counting sort)
 * APPROACH : Count frequencies, prefix sum, place elements
 * COMPLEX  : Time: O(n + k)  |  Space: O(k)  |  Stable: Yes
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

void countingSort(vector<int> &a) {
    if (a.empty())
        return;

    int maxVal = *max_element(a.begin(), a.end());
    vector<int> count(maxVal + 1, 0);

    for (int x : a)
        count[x]++;

    for (int i = 1; i <= maxVal; i++)
        count[i] += count[i - 1];

    vector<int> output(a.size());
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        output[count[a[i]] - 1] = a[i];
        count[a[i]]--;
    }
    a = output;
}

int main() {
    vector<int> a = {4, 2, 2, 8, 3, 3, 1};
    countingSort(a);
    for (int x : a)
        cout << x << " ";
    cout << endl;
    return 0;
}
