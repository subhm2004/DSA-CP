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

// ════════════════════════════════════════════════════════════════════════════
// DAG DP — Max Profit Path (Topological Order)
// ────────────────────────────────────────────────────────────────────────────
// DAG me cycle nahi — topological sort se nodes linear order me process karo.
// Pehle Kahn's algo se topo order nikalo (indegree 0 wale nodes queue se).
// dp[v] = node v tak pohonchne ka maximum weighted path profit.
// Har edge (u→v,w): dp[v] = max(dp[v], dp[u] + w) — topo order me relax karo.
// Answer = sab nodes ka max dp — kisi bhi start se best profit path.
// ════════════════════════════════════════════════════════════════════════════

// ── maxProfitPath: DAG me maximum weighted path profit ────────────────────
//   1) indegree count karo; indegree 0 nodes queue me daalo (sources)
//   2) Kahn's BFS se topo[] order banao — har node ek baar process
//   3) dp[u] = 0 se shuru — har node tak best profit track karo
//   4) topo order me har edge relax: dp[v] = max(dp[v], dp[u] + weight)
//   5) max_element(dp) return — graph me kahin se bhi best profit path
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

// ── main: 5-node weighted DAG par max profit print ────────────────────────
//   Sample adjacency list build karke maxProfitPath call — result stdout par
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
