/*
 * ============================================================================
 * TOPIC    : Knapsack — Unbounded / Coin Change
 * FILE     : knapsack_unbounded_coin_change.cpp
 * PROBLEM  : Minimum coins to make target (infinite supply)
 * APPROACH : Unbounded knapsack — iterate weight forward
 * COMPLEX  : Time: O(n * target)  |  Space: O(target)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// UNBOUNDED KNAPSACK / MIN COIN CHANGE — Forward DP
// ────────────────────────────────────────────────────────────────────────────
// State: dp[t] = minimum coins needed to make sum t (coins unlimited supply).
// Transition: har coin c ke liye dp[t] = min(dp[t], dp[t-c] + 1) jab t >= c.
// Forward loop (t = 1..target) — same coin ek hi iteration me dobara use ho sakta hai.
// Complexity: O(n * target) time, O(target) space.
// ════════════════════════════════════════════════════════════════════════════

// ── minCoins: minimum coins to reach target ─────────────────────────────────
//   1) dp[0] = 0, baaki INF — abhi tak impossible sums
//   2) har amount t = 1 se target tak, har coin try karo
//   3) agar t-c reachable hai -> dp[t] ko dp[t-c]+1 se improve karo
//   4) dp[target] INF ho to -1, warna min coins return
int minCoins(const vector<int> &coins, int target) {
    const int INF = 1e9;
    vector<int> dp(target + 1, INF);
    dp[0] = 0;

    for (int t = 1; t <= target; t++) {
        for (int c : coins) {
            // forward DP: coin c ko isi t banane me dubara use kar sakte hain
            if (c <= t && dp[t - c] != INF)
                dp[t] = min(dp[t], dp[t - c] + 1);
        }
    }

    return dp[target] == INF ? -1 : dp[target];
}

// ── main: sample min coin change run ────────────────────────────────────────
//   1) coins {1,2,5} aur target 11 set karo
//   2) minCoins call karke answer print karo
int main() {
    vector<int> coins = {1, 2, 5};
    int target = 11;
    cout << "Min coins for " << target << " = " << minCoins(coins, target) << endl;
    return 0;
}
