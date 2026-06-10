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

// ════════════════════════════════════════════════════════════════════════════
// LOWER / UPPER BOUND — Sorted array me target ki position
// ────────────────────────────────────────────────────────────────────────────
// lo=0, hi=n (half-open [0,n)) — STL style
// lower_bound: pehla index jahan a[i] >= target
// upper_bound: pehla index jahan a[i] > target
// count = upper - lower
// ════════════════════════════════════════════════════════════════════════════

// ── lowerBoundIdx: pehla index jahan a[i] >= target ───────────────────────
//   1) mid nikalo, a[mid] < target -> answer right me -> lo = mid+1
//   2) warna answer left ya mid pe -> hi = mid (mid ko discard mat karo)
//   3) lo == hi pe converge -> first >= target index
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

// ── upperBoundIdx: pehla index jahan a[i] > target ────────────────────────
//   1) a[mid] <= target -> answer right me -> lo = mid+1
//   2) warna hi = mid
//   3) return lo = first > target index
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
