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

int coinChangeMin(const vector<int> &coins, int amount) {
    const int INF = 1e9;
    vector<int> dp(amount + 1, INF);
    dp[0] = 0;
    for (int a = 1; a <= amount; a++)
        for (int c : coins)
            if (c <= a)
                dp[a] = min(dp[a], dp[a - c] + 1);
    return dp[amount] == INF ? -1 : dp[amount];
}

int main() {
    vector<int> coins = {1, 2, 5};
    cout << coinChangeMin(coins, 11) << endl; // 3
    return 0;
}
