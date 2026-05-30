/*
 * ============================================================================
 * TOPIC    : Tree DP
 * FILE     : tree_dp_max_independent_set.cpp
 * PROBLEM  : Maximum weight independent set on a tree
 * APPROACH : Tree DP — take node vs skip node
 * COMPLEX  : Time: O(n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> weight;
vector<vector<long long>> dp;

void dfs(int u, int parent) {
    dp[u][0] = 0;              // skip u
    dp[u][1] = weight[u];      // take u

    for (int v : adj[u]) {
        if (v == parent)
            continue;
        dfs(v, u);
        dp[u][0] += max(dp[v][0], dp[v][1]);
        dp[u][1] += dp[v][0];
    }
}

long long maxIndependentSet(int n) {
    dp.assign(n, vector<long long>(2, 0));
    dfs(0, -1);
    return max(dp[0][0], dp[0][1]);
}

int main() {
    // Tree: 0-1, 0-2, 1-3, 1-4
    int n = 5;
    adj.assign(n, {});
    weight = {5, 1, 2, 8, 9};

    adj[0] = {1, 2};
    adj[1] = {0, 3, 4};
    adj[2] = {0};
    adj[3] = {1};
    adj[4] = {1};

    cout << "Max independent set weight = " << maxIndependentSet(n) << endl;
    return 0;
}
