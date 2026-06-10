/*
 * ============================================================================
 * TOPIC    : Dynamic Programming — Coin Change (minimum coins)
 * FILE     : coin_change_min_coins.cpp
 * PROBLEM  : Fewest coins to make amount
 * LEETCODE : 322 — Coin Change
 * APPROACH : Unbounded knapsack style — dp[a] = min coins for amount a
 * COMPLEX  : Time: O(n*amount)  |  Space: O(amount)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// COIN CHANGE MIN — amount banane ke liye minimum kitne coins chahiye
// ────────────────────────────────────────────────────────────────────────────
// Unbounded knapsack style — har coin unlimited baar use kar sakte ho.
// dp[a] = amount a banane ke min coins. dp[0]=0, baaki INF se start.
// Har amount a: har coin c try karo -> dp[a] = min(dp[a], dp[a-c]+1).
// dp[amount] still INF ho to impossible — return -1.
// COMPLEX: Time O(n*amount)  |  Space O(amount)
// ════════════════════════════════════════════════════════════════════════════

// ── coinChangeMin: minimum coins to make amount ────────────────────────────
//   1) dp[a] = min coins for amount a, dp[0]=0, baaki INF
//   2) Amount 1 se amount tak forward iterate
//   3) Har coin c (c<=a): ek coin use karo, baaki a-c ke min + 1
//   4) dp[a] = min across all coins
//   5) INF ho to -1 (impossible), warna dp[amount]
int coinChangeMin(const vector<int> &coins, int amount) {
    const int INF = 1e9;
    vector<int> dp(amount + 1, INF);
    dp[0] = 0;                                             // amount 0 — zero coins
    for (int a = 1; a <= amount; a++)
        for (int c : coins)
            if (c <= a)
                dp[a] = min(dp[a], dp[a - c] + 1);         // coin c lo, count +1
    return dp[amount] == INF ? -1 : dp[amount];            // impossible check
}

// ── main: coins {1,2,5} se amount 11 min coins test ────────────────────────
//   1) Optimal: 5+5+1 = 3 coins
//   2) Min coins print karo
int main() {
    vector<int> coins = {1, 2, 5};
    cout << coinChangeMin(coins, 11) << endl; // 3
    return 0;
}
