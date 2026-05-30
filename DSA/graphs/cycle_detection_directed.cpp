/*
 * ============================================================================
 * TOPIC    : Graphs — Cycle Detection (Directed)
 * FILE     : cycle_detection_directed.cpp
 * PROBLEM  : Detect cycle in directed graph
 * LEETCODE : 207 — Course Schedule
 * APPROACH : DFS three-color (0=unvisited, 1=stack, 2=done)
 * COMPLEX  : Time: O(V+E)  |  Space: O(V)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

bool dfsDir(int u, const vector<vector<int>> &adj, vector<int> &color) {
    color[u] = 1;
    for (int v : adj[u]) {
        if (color[v] == 1) return true;
        if (color[v] == 0 && dfsDir(v, adj, color)) return true;
    }
    color[u] = 2;
    return false;
}

bool hasCycleDirected(int n, const vector<vector<int>> &adj) {
    vector<int> color(n, 0);
    for (int i = 0; i < n; i++)
        if (color[i] == 0 && dfsDir(i, adj, color))
            return true;
    return false;
}

int main() {
    vector<vector<int>> adj(4);
    adj[0] = {1}; adj[1] = {2}; adj[2] = {3}; adj[3] = {1};
    cout << (hasCycleDirected(4, adj) ? "Cycle" : "No cycle") << endl;
    return 0;
}
