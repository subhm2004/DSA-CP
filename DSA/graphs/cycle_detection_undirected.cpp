/*
 * ============================================================================
 * TOPIC    : Graphs — Cycle Detection (Undirected)
 * FILE     : cycle_detection_undirected.cpp
 * PROBLEM  : Detect cycle in undirected graph
 * LEETCODE : 261 — Graph Valid Tree
 * APPROACH : DFS — if visited neighbor is not parent, cycle exists
 * COMPLEX  : Time: O(V+E)  |  Space: O(V)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

bool dfsCycle(int u, int p, const vector<vector<int>> &adj, vector<bool> &vis) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) {
            if (dfsCycle(v, u, adj, vis)) return true;
        } else if (v != p)
            return true;
    }
    return false;
}

bool hasCycleUndirected(int n, const vector<vector<int>> &adj) {
    vector<bool> vis(n, false);
    for (int i = 0; i < n; i++)
        if (!vis[i] && dfsCycle(i, -1, adj, vis))
            return true;
    return false;
}

int main() {
    vector<vector<int>> adj(3);
    adj[0] = {1}; adj[1] = {0, 2}; adj[2] = {1};
    cout << (hasCycleUndirected(3, adj) ? "Cycle" : "No cycle") << endl;
    return 0;
}
