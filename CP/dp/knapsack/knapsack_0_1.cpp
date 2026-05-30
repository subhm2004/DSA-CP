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

int knapsack01(const vector<int> &wt, const vector<int> &val, int W) {
    int n = wt.size();
    vector<int> dp(W + 1, 0);

    for (int i = 0; i < n; i++) {
        for (int w = W; w >= wt[i]; w--)
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
    }

    return dp[W];
}

int main() {
    vector<int> wt = {1, 3, 4, 5}, val = {1, 4, 5, 7};
    int W = 7;
    cout << "0/1 Knapsack max value (W=" << W << "): " << knapsack01(wt, val, W) << endl;
    return 0;
}
