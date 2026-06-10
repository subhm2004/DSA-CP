/*
 * ============================================================================
 * TOPIC    : LIS — Longest Increasing Subsequence
 * FILE     : lis_binary_search_o_nlogn.cpp
 * PROBLEM  : LIS length in O(n log n)
 * APPROACH : Patience sorting — tails[] + lower_bound
 * COMPLEX  : Time: O(n log n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LIS — O(n log n) Patience Sorting / Binary Search
// ────────────────────────────────────────────────────────────────────────────
// tails[len] = smallest ending element of any LIS of length (len+1).
// Naya element x: lower_bound se dekho kahan fit hota hai.
//   x > sabse bada -> nayi length (push_back).
//   warna kisi existing tail ko replace karo (better ending = zyada future extend).
// tails.size() = LIS length. Actual sequence nahi milti, sirf length.
// Complexity: O(n log n) time, O(n) space.
// ════════════════════════════════════════════════════════════════════════════

// ── lisLength: LIS ki length O(n log n) me ──────────────────────────────────
//   1) tails empty — abhi koi LIS nahi
//   2) har x ke liye lower_bound se sabse chhota tail >= x dhoondo
//   3) end me hai -> nayi LIS length; beech me hai -> tail replace (optimize)
//   4) tails.size() = final LIS length
int lisLength(const vector<int> &nums) {
    vector<int> tails;

    for (int x : nums) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end())
            tails.push_back(x); // x sabse bada — LIS ek aur lamba ho sakta hai
        else
            *it = x; // chhota ending element rakho — future elements ke liye better
    }

    return (int)tails.size();
}

// ── main: O(n log n) LIS length demo ──────────────────────────────────────────
//   1) sample array set karo, sirf length print karo
int main() {
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "LIS length (O(n log n)): " << lisLength(nums) << endl;
    return 0;
}
