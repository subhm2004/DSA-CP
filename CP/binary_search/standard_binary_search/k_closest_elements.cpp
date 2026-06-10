/*
 * ============================================================================
 * TOPIC    : Standard Binary Search
 * FILE     : k_closest_elements.cpp
 * PROBLEM  : K closest elements to target in sorted array
 * APPROACH : Two pointers shrink window of size k
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// K CLOSEST ELEMENTS — Sorted array me target ke paas ke k elements
// ────────────────────────────────────────────────────────────────────────────
// Window [lo..hi] size >= k rakho, jab tak size > k:
//   left ya right se aage wala hatao jo target se zyada door ho
// Ant me [lo..lo+k-1] = answer (sorted order me)
// ════════════════════════════════════════════════════════════════════════════

// ── kClosest: target ke sabse kareeb k elements ─────────────────────────────
//   1) lo=0, hi=n-1 — poori array window
//   2) jab hi-lo+1 > k: door wala pointer hatao
//   3) |a[lo]-target| > |a[hi]-target| -> lo++, warna hi--
//   4) [lo..lo+k) subarray return
vector<int> kClosest(const vector<int> &a, int k, int target) {
    int lo = 0, hi = (int)a.size() - 1;

    while (hi - lo >= k) {
        if (abs(a[lo] - target) > abs(a[hi] - target))
            lo++; // left zyada door hai
        else
            hi--; // right zyada door hai
    }

    return vector<int>(a.begin() + lo, a.begin() + lo + k);
}

int main() {
    vector<int> a = {12, 16, 22, 30, 35, 39, 42, 45, 48, 50};
    int k = 4, target = 35;

    for (int x : kClosest(a, k, target))
        cout << x << " ";
    cout << endl;
    return 0;
}
