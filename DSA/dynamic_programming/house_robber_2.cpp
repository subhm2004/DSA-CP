/*
 * ============================================================================
 * TOPIC    : Dynamic Programming — House Robber II (circular)
 * FILE     : house_robber_2.cpp
 * PROBLEM  : Houses in circle — first and last adjacent
 * LEETCODE : 213 — House Robber II
 * APPROACH : max(rob range [0..n-2], rob range [1..n-1])
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// HOUSE ROBBER II — circular street, first aur last house adjacent
// ────────────────────────────────────────────────────────────────────────────
// Circle me first+last dono rob nahi kar sakte — ek break karna padega.
// Do cases: (1) first house rob, last skip -> range [0..n-2]
//           (2) first skip, last rob possible -> range [1..n-1]
// Dono me se max = answer. Core logic same House Robber I (linear).
// COMPLEX: Time O(n)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── robLinear: lo..hi range me non-adjacent max loot ───────────────────────
//   1) take/skip variables — House Robber I ka same O(1) DP
//   2) Sirf lo se hi tak iterate — circular constraint break ho chuka
//   3) Har house: next = max(skip+nums[i], take)
//   4) skip/take slide karo
//   5) take = range ka best answer
int robLinear(const vector<int> &nums, int lo, int hi) {
    int take = 0, skip = 0;
    for (int i = lo; i <= hi; i++) {
        int next = max(skip + nums[i], take);             // rob ya skip current house
        skip = take;
        take = next;
    }
    return take;
}

// ── robCircular: circular houses me max robbery ────────────────────────────
//   1) n==1 to seedha nums[0] — koi adjacency issue nahi
//   2) Case A: rob [0..n-2] — last house skip (first rob allowed)
//   3) Case B: rob [1..n-1] — first house skip (last rob allowed)
//   4) Dono cases ka max return — circle constraint satisfied
//   5) Kabhi first+last dono rob nahi honge
int robCircular(const vector<int> &nums) {
    int n = nums.size();
    if (n == 1) return nums[0];                            // single house — no circle issue
    return max(robLinear(nums, 0, n - 2),                  // first rob, last skip
               robLinear(nums, 1, n - 1));                  // first skip, last rob
}

// ── main: circular houses {2,3,2} pe test ──────────────────────────────────
//   1) First+last adjacent — max = 3 (sirf middle house)
//   2) Answer print karo
int main() {
    vector<int> nums = {2, 3, 2};
    cout << robCircular(nums) << endl; // 3
    return 0;
}
