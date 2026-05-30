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
