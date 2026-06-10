/*
 * ============================================================================
 * TOPIC    : Dynamic Programming — Unbounded Knapsack
 * FILE     : unbounded_knapsack.cpp
 * PROBLEM  : Max value — unlimited copies of each item
 * LEETCODE : 279 — Perfect Squares
 * APPROACH : dp[w] = max over items of dp[w-wt[i]] + val[i], forward loop
 * COMPLEX  : Time: O(n*W)  |  Space: O(W)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// UNBOUNDED KNAPSACK — har item unlimited copies, weight W me max value
// ────────────────────────────────────────────────────────────────────────────
// 0/1 se farq: same item baar-baar le sakte ho.
// Weight FORWARD loop (1 se W) — dp[w-wt] pehle hi compute ho chuka, reuse allowed.
// Har weight w pe sab items try karo: dp[w] = max(dp[w], dp[w-wt]+val).
// COMPLEX: Time O(n*W)  |  Space O(W)
// ════════════════════════════════════════════════════════════════════════════

// ── unboundedKnapsack: unlimited items se max value ────────────────────────
//   1) dp[w] = capacity w me max value, initially 0
//   2) Weight 1 se W tak forward iterate — same item repeat allowed
//   3) Har weight pe har item try karo (agar wt[i] <= w)
//   4) dp[w] = max(dp[w], dp[w-wt[i]] + val[i]) — ek aur copy lo
//   5) dp[W] = final max value
int unboundedKnapsack(const vector<int> &wt, const vector<int> &val, int W) {
    vector<int> dp(W + 1, 0);
    for (int w = 1; w <= W; w++)
        for (int i = 0; i < (int)wt.size(); i++)
            if (wt[i] <= w)
                dp[w] = max(dp[w], dp[w - wt[i]] + val[i]); // item i ki ek copy add karo
    return dp[W];
}

// ── main: wt {1,3,4} val {10,40,50} capacity 8 test ───────────────────────
//   1) Best: do 4-weight items -> 50+50 = 80
//   2) Max value print karo
int main() {
    vector<int> wt = {1, 3, 4}, val = {10, 40, 50};
    cout << unboundedKnapsack(wt, val, 8) << endl; // 80 (two 4s)
    return 0;
}
