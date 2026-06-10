/*
 * ============================================================================
 * TOPIC    : Two Pointers
 * FILE     : two_sum_sorted.cpp
 * PROBLEM  : Two sum in sorted array — find pair with target
 * APPROACH : l=0, r=n-1, move based on sum vs target
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * LEETCODE : 167 — Two Sum II (Input Array Is Sorted)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// TWO SUM — SORTED ARRAY (Two Pointers)
// ────────────────────────────────────────────────────────────────────────────
// Array sorted hai → agar sum chhota hai to left++ (bada element chahiye)
//                    agar sum bada hai to right-- (chhota element chahiye)
// Unsorted array pe hash map O(n) use karo — yahan sort + two pointer O(n log n)
// COMPLEX: O(n) two pointer  |  O(n log n) agar sort include karo
// ════════════════════════════════════════════════════════════════════════════

// ── twoSumSorted: target sum wala pair dhundho ──
//   1) array sort karo (already sorted ho to skip bhi kar sakte ho)
//   2) l = 0 (sabse chhota), r = n-1 (sabse bada)
//   3) sum == target → pair mil gaya, return
//   4) sum < target → l++ (chhota side badhao, sum badhega)
//   5) sum > target → r-- (bada side ghatao, sum ghatega)
//   6) l >= r → koi pair nahi, {-1,-1}
pair<int, int> twoSumSorted(vector<int> a, int target)
{
    sort(a.begin(), a.end());
    int l = 0, r = (int)a.size() - 1;

    while (l < r)
    {
        long long sum = (long long)a[l] + a[r]; // overflow se bachne ke liye long long
        if (sum == target)
            return {a[l], a[r]};
        if (sum < target)
            l++; // sum badhana hai → chhota element hatao, bada lao
        else
            r--; // sum ghataana hai → bada element hatao
    }
    return {-1, -1};
}

int main()
{
    vector<int> a = {2, 7, 11, 15};
    int target = 9;
    auto [x, y] = twoSumSorted(a, target);
    cout << "Pair with sum " << target << ": " << x << ", " << y << endl;
    return 0;
}
