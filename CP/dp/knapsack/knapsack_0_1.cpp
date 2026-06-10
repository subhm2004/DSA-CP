/*
 * ============================================================================
 * TOPIC    : Knapsack — 0/1 Knapsack
 * FILE     : knapsack_0_1.cpp
 * PROBLEM  : Max value with weight limit W (each item once)
 * APPROACH : 2D DP or 1D space-optimized
 * COMPLEX  : Time: O(n * W)  |  Space: O(W)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// 0/1 KNAPSACK — 1D Space-Optimized DP
// ────────────────────────────────────────────────────────────────────────────
// State: dp[w] = max value achievable with capacity exactly w (pehle i items se).
// Transition: item i lo -> dp[w] = max(skip, take) = max(dp[w], dp[w-wt[i]] + val[i]).
// Reverse loop (w = W se wt[i] tak) zaroori hai — warna same item do baar use ho jayega.
// Complexity: O(n * W) time, O(W) space.
// ════════════════════════════════════════════════════════════════════════════

// ── knapsack01: max value with weight limit W ───────────────────────────────
//   1) dp[0..W] = 0 — koi item nahi liya to value 0
//   2) har item i ke liye capacity w ko W se reverse me update karo
//   3) item lo -> dp[w-wt[i]] + val[i]; skip -> dp[w] as-is; max le lo
//   4) dp[W] return — poori capacity use karke max value
int knapsack01(const vector<int> &wt, const vector<int> &val, int W) {
    int n = wt.size();
    vector<int> dp(W + 1, 0);

    for (int i = 0; i < n; i++) {
        // reverse loop: 0/1 constraint — ek item sirf ek baar count ho
        for (int w = W; w >= wt[i]; w--)
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
    }

    return dp[W];
}

// ── main: sample 0/1 knapsack run ───────────────────────────────────────────
//   1) weights aur values ka chhota test case
//   2) knapsack01 call karke max value print karo
int main() {
    vector<int> wt = {1, 3, 4, 5}, val = {1, 4, 5, 7};
    int W = 7;
    cout << "0/1 Knapsack max value (W=" << W << "): " << knapsack01(wt, val, W) << endl;
    return 0;
}
