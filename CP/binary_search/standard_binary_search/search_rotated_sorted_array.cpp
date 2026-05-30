/*
 * ============================================================================
 * TOPIC    : Standard Binary Search
 * FILE     : search_rotated_sorted_array.cpp
 * PROBLEM  : Search target in rotated sorted array
 * APPROACH : Find pivot + BS on correct half
 * COMPLEX  : Time: O(log n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int findPivot(const vector<int> &a) {
    int lo = 0, hi = (int)a.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] > a[hi])
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo;
}

int binarySearch(const vector<int> &a, int lo, int hi, int target) {
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == target)
            return mid;
        if (a[mid] < target)
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return -1;
}

int searchRotated(const vector<int> &a, int target) {
    int n = a.size();
    if (n == 0)
        return -1;
    int pivot = findPivot(a);

    if (target >= a[pivot] && target <= a[n - 1])
        return binarySearch(a, pivot, n - 1, target);
    return binarySearch(a, 0, pivot - 1, target);
}

int main() {
    vector<int> a = {12, 14, 16, 2, 4, 6, 8, 10};
    cout << "Index of 14 = " << searchRotated(a, 14) << endl;
    cout << "Index of 6 = " << searchRotated(a, 6) << endl;
    return 0;
}
