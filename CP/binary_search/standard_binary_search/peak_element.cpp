/*
 * ============================================================================
 * TOPIC    : Standard Binary Search
 * FILE     : peak_element.cpp
 * PROBLEM  : Find a peak element (nums[i] > neighbors)
 * APPROACH : Binary search — move toward larger neighbor
 * COMPLEX  : Time: O(log n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int findPeak(const vector<int> &a) {
    int lo = 0, hi = (int)a.size() - 1;

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] < a[mid + 1])
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo;
}

int main() {
    vector<int> a = {5, 10, 15, 11, 9, 8, 7, 6, 5};
    int idx = findPeak(a);
    cout << "Peak index = " << idx << ", value = " << a[idx] << endl;
    return 0;
}
