/*
 * ============================================================================
 * TOPIC    : DAG DP
 * FILE     : longest_path_dag.cpp
 * PROBLEM  : Longest path in a Directed Acyclic Graph
 * APPROACH : Topological sort + relax edges in topo order
 * COMPLEX  : Time: O(V + E)  |  Space: O(V + E)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int longestPathDAG(int n, vector<vector<int>> &adj, int src) {
    vector<int> indeg(n, 0);
    for (int u = 0; u < n; u++)
        for (int v : adj[u])
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
        for (int v : adj[u])
            if (--indeg[v] == 0)
                q.push(v);
    }

    vector<int> dist(n, INT_MIN);
    dist[src] = 0;

    for (int u : topo) {
        if (dist[u] == INT_MIN)
            continue;
        for (int v : adj[u])
            dist[v] = max(dist[v], dist[u] + 1);
    }

    return *max_element(dist.begin(), dist.end());
}

int main() {
    int n = 6;
    vector<vector<int>> adj(n);
    adj[0] = {1, 2};
    adj[1] = {3};
    adj[2] = {3, 4};
    adj[3] = {5};
    adj[4] = {5};

    cout << "Longest path length from 0 = " << longestPathDAG(n, adj, 0) << endl;
    return 0;
}
