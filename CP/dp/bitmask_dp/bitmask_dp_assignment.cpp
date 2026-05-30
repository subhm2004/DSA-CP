/*
 * ============================================================================
 * TOPIC    : Bitmask DP
 * FILE     : bitmask_dp_assignment.cpp
 * PROBLEM  : Assign n jobs to n workers — min total cost
 * APPROACH : dp[mask] = min cost when `mask` jobs are assigned
 * COMPLEX  : Time: O(n^2 * 2^n)  |  Space: O(2^n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int minAssignment(const vector<vector<int>> &cost) {
    int n = cost.size();
    const int INF = 1e9;
    vector<int> dp(1 << n, INF);
    dp[0] = 0;

    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp[mask] == INF)
            continue;
        int worker = __builtin_popcount(mask);
        for (int job = 0; job < n; job++) {
            if (mask & (1 << job))
                continue;
            int next = mask | (1 << job);
            dp[next] = min(dp[next], dp[mask] + cost[worker][job]);
        }
    }

    return dp[(1 << n) - 1];
}

int main() {
    vector<vector<int>> cost = {
        {9, 2, 7, 8},
        {6, 4, 3, 7},
        {5, 8, 1, 8},
        {7, 6, 9, 4}
    };

    cout << "Minimum assignment cost = " << minAssignment(cost) << endl;
    return 0;
}
