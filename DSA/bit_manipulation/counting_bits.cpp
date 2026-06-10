/*
 * ============================================================================
 * TOPIC    : Bit Manipulation — Counting Bits
 * FILE     : counting_bits.cpp
 * PROBLEM  : Number of 1's for every i in [0, n]
 * LEETCODE : 338 — Counting Bits
 * APPROACH : dp[i] = dp[i >> 1] + (i & 1)
 * COMPLEX  : Time: O(n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// COUNTING BITS — har number 0..n mein kitne set bits?
// ────────────────────────────────────────────────────────────────────────────
// DP trick: i >> 1 = i ko right shift (last bit hatao)
// dp[i] = dp[i/2] + (i ka last bit 1 hai ya 0)
// i & 1 -> last bit; i >> 1 -> pehle wale bits ka count already dp mein
// O(n) mein sab answers — brute force O(n log n) se better
// ════════════════════════════════════════════════════════════════════════════

// ── countBits: 0 se n tak har i ke set-bit count ──────────────────────────
//   1) dp[0..n] array, dp[0]=0
//   2) i=1 se n tak loop
//   3) dp[i] = dp[i >> 1] + (i & 1) — half ka count + last bit
//   4) dp return — vector of counts
vector<int> countBits(int n) {
    vector<int> dp(n + 1, 0);
    for (int i = 1; i <= n; i++)
        dp[i] = dp[i >> 1] + (i & 1);
    return dp;
}

int main() {
    for (int x : countBits(5)) cout << x << " ";
    cout << endl; // 0 1 1 2 1 2
    return 0;
}
