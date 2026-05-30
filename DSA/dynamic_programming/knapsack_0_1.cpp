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

int knapsack01(const vector<int> &wt, const vector<int> &val, int W) {
    int n = wt.size();
    vector<int> dp(W + 1, 0);
    for (int i = 0; i < n; i++)
        for (int w = W; w >= wt[i]; w--)
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
    return dp[W];
}

int main() {
    vector<int> wt = {1, 3, 4, 5}, val = {1, 4, 5, 7};
    int W = 7;
    cout << "Max value: " << knapsack01(wt, val, W) << endl; // 9
    return 0;
}
