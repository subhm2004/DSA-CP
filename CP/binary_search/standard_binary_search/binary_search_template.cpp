/*
 * ============================================================================
 * TOPIC    : Standard Binary Search
 * FILE     : binary_search_template.cpp
 * PROBLEM  : Classic BS — find first/last occurrence, lower/upper bound
 * APPROACH : lower_bound / upper_bound style binary search
 * COMPLEX  : Time: O(log n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int lowerBoundIdx(const vector<int> &a, int target) {
    int lo = 0, hi = (int)a.size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] < target)
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo;
}

int upperBoundIdx(const vector<int> &a, int target) {
    int lo = 0, hi = (int)a.size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] <= target)
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo;
}

int main() {
    vector<int> a = {1, 2, 2, 2, 3, 4, 5};
    int target = 2;

    int lb = lowerBoundIdx(a, target);
    int ub = upperBoundIdx(a, target);

    cout << "lower_bound(2) index = " << lb << endl;
    cout << "upper_bound(2) index = " << ub << endl;
    cout << "count of 2 = " << (ub - lb) << endl;
    return 0;
}
