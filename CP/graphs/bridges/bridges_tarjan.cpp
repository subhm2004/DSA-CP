/*
 * ============================================================================
 * TOPIC    : Bridges — Tarjan's Algorithm
 * FILE     : bridges_tarjan.cpp
 * PROBLEM  : Find all bridge edges in undirected graph
 * APPROACH : DFS with disc[] and low[] — bridge if low[v] > disc[u]
 * COMPLEX  : Time: O(V + E)  |  Space: O(V + E)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

class BridgeFinder {
    vector<vector<int>> adj;
    vector<int> disc, low;
    vector<pair<int, int>> bridges;
    int timer = 0;

    void dfs(int u, int parent) {
        disc[u] = low[u] = ++timer;
        for (int v : adj[u]) {
            if (v == parent)
                continue;
            if (disc[v] == 0) {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] > disc[u])
                    bridges.push_back({min(u, v), max(u, v)});
            } else {
                low[u] = min(low[u], disc[v]);
            }
        }
    }

public:
    BridgeFinder(int n) : adj(n), disc(n, 0), low(n, 0) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<pair<int, int>> findBridges() {
        for (int i = 0; i < (int)adj.size(); i++)
            if (disc[i] == 0)
                dfs(i, -1);
        return bridges;
    }
};

int main() {
    int n = 5;
    BridgeFinder g(n);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(1, 3);
    g.addEdge(3, 4);

    auto bridges = g.findBridges();
    cout << "Bridges:\n";
    for (auto [u, v] : bridges)
        cout << u << " -- " << v << endl;
    return 0;
}
