/*
 * ============================================================================
 * TOPIC    : Graphs — DFS Traversal
 * FILE     : dfs_traversal.cpp
 * PROBLEM  : Depth-first traversal from source
 * LEETCODE : 104 — Maximum Depth (DFS pattern)
 * APPROACH : Recursive / stack DFS with visited
 * COMPLEX  : Time: O(V+E)  |  Space: O(V)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

void dfs(int u, const vector<vector<int>> &adj, vector<bool> &vis, vector<int> &order) {
    vis[u] = true;
    order.push_back(u);
    for (int v : adj[u])
        if (!vis[v]) dfs(v, adj, vis, order);
}

vector<int> dfsOrder(int n, const vector<vector<int>> &adj, int src) {
    vector<bool> vis(n, false);
    vector<int> order;
    dfs(src, adj, vis, order);
    return order;
}

int main() {
    int n = 5;
    vector<vector<int>> adj(n);
    auto add = [&](int u, int v) { adj[u].push_back(v); adj[v].push_back(u); };
    add(0, 1); add(0, 2); add(1, 3); add(2, 4);
    for (int x : dfsOrder(n, adj, 0)) cout << x << " ";
    cout << endl;
    return 0;
}
