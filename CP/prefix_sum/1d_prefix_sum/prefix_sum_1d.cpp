/*
 * ============================================================================
 * TOPIC    : Prefix Sum — 1D
 * FILE     : prefix_sum_1d.cpp
 * PROBLEM  : Range sum queries on static array
 * APPROACH : prefix[i] = sum of arr[0..i-1]
 * COMPLEX  : Build O(n), Query O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// 1D PREFIX SUM — static array pe O(1) range sum
// ────────────────────────────────────────────────────────────────────────────
// pref[i] = arr[0] + arr[1] + ... + arr[i-1]   (pref[0] = 0)
// sum(l, r) = pref[r+1] - pref[l]
//
// Kab use: static array, bahut saari range sum queries
// Mat use: point updates zyada → Fenwick / seg tree
// COMPLEX: build O(n)  |  query O(1)
// ════════════════════════════════════════════════════════════════════════════

struct PrefixSum1D
{
    vector<long long> pref;

    // ── PrefixSum1D: constructor me prefix array build ──
    //   pref size = n+1, pref[0]=0
    //   pref[i+1] = pref[i] + a[i]
    PrefixSum1D(const vector<int> &a)
    {
        pref.assign(a.size() + 1, 0);
        for (int i = 0; i < (int)a.size(); i++)
            pref[i + 1] = pref[i] + a[i];
    }

    // ── rangeSum: [l, r] inclusive sum — 0-indexed ──
    //   = pref[r+1] - pref[l]
    long long rangeSum(int l, int r) const
    {
        return pref[r + 1] - pref[l];
    }
};

int main()
{
    vector<int> a = {1, 2, 3, 4, 5};
    PrefixSum1D ps(a);
    cout << "Sum [1,3] = " << ps.rangeSum(1, 3) << endl; // 2+3+4 = 9
    cout << "Sum [0,4] = " << ps.rangeSum(0, 4) << endl; // 1+2+3+4+5 = 15
    return 0;
}
