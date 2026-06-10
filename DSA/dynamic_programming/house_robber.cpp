/*
 * ============================================================================
 * TOPIC    : Dynamic Programming — House Robber
 * FILE     : house_robber.cpp
 * PROBLEM  : Max money robbing non-adjacent houses
 * LEETCODE : 198 — House Robber
 * APPROACH : dp[i] = max(rob i + dp[i-2], dp[i-1])
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// HOUSE ROBBER — adjacent houses rob nahi kar sakte, max money kamao
// ────────────────────────────────────────────────────────────────────────────
// Har house pe choice: rob karo (to prev-2 ka best + current) ya skip karo.
// take = i tak rob karke max money, skip = i-1 tak max (i skip).
// Do variables se O(1) space — purana dp[i-2] aur dp[i-1] track karo.
// COMPLEX: Time O(n)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── rob: non-adjacent houses se max loot return karo ───────────────────────
//   1) take = max money jab last robbed house included ho
//   2) skip = max money jab last house skip ho
//   3) Har house x: next = max(skip+x, take) — rob ya skip decide
//   4) skip = purana take, take = next — window aage badhao
//   5) End me take = overall best answer
int rob(const vector<int> &nums) {
    int take = 0, skip = 0;
    for (int x : nums) {
        int next = max(skip + x, take);                  // x rob karo (skip+x) ya skip (take)
        skip = take;                                       // ab take becomes prev skip state
        take = next;                                       // update best with current decision
    }
    return take;
}

// ── main: sample houses pe max robbery test ────────────────────────────────
//   1) nums = {2,7,9,3,1} — optimal: 2+9+1 = 12
//   2) Answer print karo
int main() {
    vector<int> nums = {2, 7, 9, 3, 1};
    cout << rob(nums) << endl; // 12
    return 0;
}
