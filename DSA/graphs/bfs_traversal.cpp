/*
 * ============================================================================
 * TOPIC    : Graphs — BFS Traversal
 * FILE     : bfs_traversal.cpp
 * PROBLEM  : Level-order BFS from source on adjacency list
 * LEETCODE : 102 — Binary Tree Level Order Traversal (BFS pattern)
 * APPROACH : Queue + visited array
 * COMPLEX  : Time: O(V+E)  |  Space: O(V)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

vector<int> bfs(int n, const vector<vector<int>> &adj, int src) {
    vector<int> order, dist(n, -1);
    queue<int> q;
    dist[src] = 0;
    q.push(src);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (int v : adj[u])
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
    }
    return order;
}

int main() {
    int n = 5;
    vector<vector<int>> adj(n);
    auto add = [&](int u, int v) { adj[u].push_back(v); adj[v].push_back(u); };
    add(0, 1); add(0, 2); add(1, 3); add(2, 4);
    for (int x : bfs(n, adj, 0)) cout << x << " ";
    cout << endl; // 0 1 2 3 4
    return 0;
}
