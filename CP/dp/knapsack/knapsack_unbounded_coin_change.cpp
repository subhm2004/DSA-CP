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

int minCoins(const vector<int> &coins, int target) {
    const int INF = 1e9;
    vector<int> dp(target + 1, INF);
    dp[0] = 0;

    for (int t = 1; t <= target; t++) {
        for (int c : coins) {
            if (c <= t && dp[t - c] != INF)
                dp[t] = min(dp[t], dp[t - c] + 1);
        }
    }

    return dp[target] == INF ? -1 : dp[target];
}

int main() {
    vector<int> coins = {1, 2, 5};
    int target = 11;
    cout << "Min coins for " << target << " = " << minCoins(coins, target) << endl;
    return 0;
}
