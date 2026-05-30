/*
 * ============================================================================
 * TOPIC    : DAG DP
 * FILE     : dag_dp_topological_order.cpp
 * PROBLEM  : Max profit path in DAG with weighted edges (job scheduling style)
 * APPROACH : DP in topological order — dp[v] = max(dp[u] + weight)
 * COMPLEX  : Time: O(V + E)  |  Space: O(V + E)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

long long maxProfitPath(int n, vector<vector<pair<int, int>>> &adj) {
    vector<int> indeg(n, 0);
    for (int u = 0; u < n; u++)
        for (auto [v, w] : adj[u])
            indeg[v]++;

    queue<int> q;
    for (int i = 0; i < n; i++)
        if (indeg[i] == 0)
            q.push(i);

    vector<int> topo;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo.push_back(u);
        for (auto [v, w] : adj[u])
            if (--indeg[v] == 0)
                q.push(v);
    }

    vector<long long> dp(n, 0);
    for (int u : topo)
        for (auto [v, w] : adj[u])
            dp[v] = max(dp[v], dp[u] + w);

    return *max_element(dp.begin(), dp.end());
}

int main() {
    int n = 5;
    vector<vector<pair<int, int>>> adj(n);
    adj[0] = {{1, 3}, {2, 2}};
    adj[1] = {{3, 4}};
    adj[2] = {{3, 5}, {4, 1}};
    adj[3] = {{4, 2}};

    cout << "Max weighted path profit = " << maxProfitPath(n, adj) << endl;
    return 0;
}
