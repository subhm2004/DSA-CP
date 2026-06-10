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

// ════════════════════════════════════════════════════════════════════════════
// COIN CHANGE WAYS — amount banane ke kitne combinations (order matter nahi)
// ────────────────────────────────────────────────────────────────────────────
// Combination count hai, permutation nahi — isliye outer loop coins, inner amount.
// dp[a] = amount a banane ke total ways.
// Har coin c: dp[a] += dp[a-c] — coin c use karke bache hue amount ke ways.
// dp[0]=1 — zero amount ek hi tareeke se (koi coin nahi lo).
// COMPLEX: Time O(n*amount)  |  Space O(amount)
// ════════════════════════════════════════════════════════════════════════════

// ── coinChangeWays: amount banane ke total combinations ────────────────────
//   1) dp[0]=1 base — empty selection se amount 0
//   2) Har coin c ke liye amount c se amount tak forward loop
//   3) dp[a] += dp[a-c] — coin c lo, baaki a-c ke ways add
//   4) Coin outer loop — same coin order fix, combinations count
//   5) dp[amount] = final answer
int coinChangeWays(const vector<int> &coins, int amount) {
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;                                             // amount 0 — ek way (no coin)
    for (int c : coins)
        for (int a = c; a <= amount; a++)
            dp[a] += dp[a - c];                            // coin c include karke ways add
    return dp[amount];
}

// ── main: coins {1,2,5} se amount 5 ke ways test ───────────────────────────
//   1) 5 banane ke 4 combinations: 5, 2+2+1, 2+1+1+1, 1*5
//   2) Ways count print karo
int main() {
    vector<int> coins = {1, 2, 5};
    cout << coinChangeWays(coins, 5) << endl; // 4
    return 0;
}
