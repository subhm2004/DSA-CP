/*
 * ============================================================================
 * TOPIC    : Dynamic Programming — 0/1 Knapsack
 * FILE     : knapsack_0_1.cpp
 * PROBLEM  : Max value with weight limit W (each item once)
 * LEETCODE : 474 — Ones and Zeroes
 * APPROACH : dp[i][w] = max(take item i, skip item i)
 * COMPLEX  : Time: O(n*W)  |  Space: O(n*W) or O(W) optimized
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// 0/1 KNAPSACK — har item ek hi baar, weight W me max value
// ────────────────────────────────────────────────────────────────────────────
// dp[w] = capacity w me achievable max value.
// Har item: lo (dp[w-wt]+val) ya chhodo (dp[w]) — better choose karo.
// Weight reverse loop (W se wt[i] tak) — same item do baar na use ho.
// 1D array se space O(W) — 2D ki jagah optimized version.
// COMPLEX: Time O(n*W)  |  Space O(W)
// ════════════════════════════════════════════════════════════════════════════

// ── knapsack01: 0/1 knapsack max value return karo ────────────────────────
//   1) dp[w] = capacity w me max value, initially sab 0
//   2) Har item i ke liye weight w reverse me iterate karo
//   3) w >= wt[i] ho to item le sakte ho: dp[w-wt]+val
//   4) dp[w] = max(skip=dp[w], take=dp[w-wt]+val)
//   5) dp[W] = final answer
int knapsack01(const vector<int> &wt, const vector<int> &val, int W) {
    int n = wt.size();
    vector<int> dp(W + 1, 0);
    for (int i = 0; i < n; i++)
        for (int w = W; w >= wt[i]; w--)                   // reverse — 0/1 guarantee
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);    // item lo ya mat lo
    return dp[W];
}

// ── main: sample items pe knapsack test ────────────────────────────────────
//   1) wt/val arrays aur capacity W=7 define karo
//   2) Max value print — expected 9 (items 3+4 ya 1+3+5)
int main() {
    vector<int> wt = {1, 3, 4, 5}, val = {1, 4, 5, 7};
    int W = 7;
    cout << "Max value: " << knapsack01(wt, val, W) << endl; // 9
    return 0;
}
