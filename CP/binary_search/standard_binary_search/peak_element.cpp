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

// ════════════════════════════════════════════════════════════════════════════
// PEAK ELEMENT — nums[i] > nums[i-1] aur nums[i] > nums[i+1]
// ────────────────────────────────────────────────────────────────────────────
// a[mid] < a[mid+1] -> peak right side me -> lo = mid+1
// warna peak left ya mid pe -> hi = mid
// lo == hi pe koi bhi valid peak mil jata hai
// ════════════════════════════════════════════════════════════════════════════

// ── findPeak: koi bhi peak element ka index ─────────────────────────────────
//   1) mid aur mid+1 compare karo
//   2) ascending slope -> peak right me, lo = mid+1
//   3) descending ya flat -> peak left/mid pe, hi = mid
//   4) lo return — guaranteed peak index
int findPeak(const vector<int> &a) {
    int lo = 0, hi = (int)a.size() - 1;

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] < a[mid + 1])
            lo = mid + 1; // chadhai right me hai
        else
            hi = mid; // peak yahan ya left me
    }
    return lo;
}

int main() {
    vector<int> a = {5, 10, 15, 11, 9, 8, 7, 6, 5};
    int idx = findPeak(a);
    cout << "Peak index = " << idx << ", value = " << a[idx] << endl;
    return 0;
}
