/*
 * ============================================================================
 * TOPIC    : Dynamic Programming — LIS
 * FILE     : longest_increasing_subsequence.cpp
 * PROBLEM  : Length of longest strictly increasing subsequence
 * LEETCODE : 300 — Longest Increasing Subsequence
 * APPROACH : O(n log n) — patience sorting with lower_bound
 * COMPLEX  : Time: O(n log n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LIS — longest strictly increasing subsequence ki length nikalo
// ────────────────────────────────────────────────────────────────────────────
// tail[len] = kisi LIS ki smallest ending value jiski length = len+1.
// Naya element x: lower_bound se dekho kahan fit hota hai.
//   x sabse bada -> nayi length (push_back).
//   warna existing tail replace — better ending = zyada future extend chance.
// tail.size() = LIS length. Actual subsequence nahi milti, sirf length.
// COMPLEX: Time O(n log n)  |  Space O(n)
// ════════════════════════════════════════════════════════════════════════════

// ── lisLength: LIS ki length return karo (O(n log n)) ──────────────────────
//   1) tail = patience sorting piles — har pile ka top smallest ending
//   2) Har x pe lower_bound se first >= x dhundho
//   3) x > sab tails -> push_back (LIS length badhi)
//   4) warna *it = x replace (same length, better/smaller ending)
//   5) tail.size() = final LIS length
int lisLength(const vector<int> &nums) {
    vector<int> tail;
    for (int x : nums) {
        auto it = lower_bound(tail.begin(), tail.end(), x); // x kis pile me fit hoga
        if (it == tail.end())
            tail.push_back(x);                               // nayi pile — LIS extend hui
        else
            *it = x;                                         // existing pile ka top chhota karo
    }
    return tail.size();
}

// ── main: sample array pe LIS length test ──────────────────────────────────
//   1) nums = {10,9,2,5,3,7,101,18} — LIS e.g. {2,3,7,18} length 4
//   2) Answer print karo
int main() {
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << lisLength(nums) << endl; // 4
    return 0;
}
