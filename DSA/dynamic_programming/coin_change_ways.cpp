/*
 * ============================================================================
 * TOPIC    : Dynamic Programming — Coin Change (number of ways)
 * FILE     : coin_change_ways.cpp
 * PROBLEM  : Count combinations to make amount (order doesn't matter)
 * LEETCODE : 518 — Coin Change II
 * APPROACH : For each coin, dp[a] += dp[a-coin]
 * COMPLEX  : Time: O(n*amount)  |  Space: O(amount)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int coinChangeWays(const vector<int> &coins, int amount) {
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;
    for (int c : coins)
        for (int a = c; a <= amount; a++)
            dp[a] += dp[a - c];
    return dp[amount];
}

int main() {
    vector<int> coins = {1, 2, 5};
    cout << coinChangeWays(coins, 5) << endl; // 4
    return 0;
}
