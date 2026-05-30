/*
 * ============================================================================
 * TOPIC    : Dynamic Programming — Unbounded Knapsack
 * FILE     : unbounded_knapsack.cpp
 * PROBLEM  : Max value — unlimited copies of each item
 * LEETCODE : 279 — Perfect Squares
 * APPROACH : dp[w] = max over items of dp[w-wt[i]] + val[i], forward loop
 * COMPLEX  : Time: O(n*W)  |  Space: O(W)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int unboundedKnapsack(const vector<int> &wt, const vector<int> &val, int W) {
    vector<int> dp(W + 1, 0);
    for (int w = 1; w <= W; w++)
        for (int i = 0; i < (int)wt.size(); i++)
            if (wt[i] <= w)
                dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
    return dp[W];
}

int main() {
    vector<int> wt = {1, 3, 4}, val = {10, 40, 50};
    cout << unboundedKnapsack(wt, val, 8) << endl; // 80 (two 4s)
    return 0;
}
