/*
 * ============================================================================
 * TOPIC    : Graphs — Topological Sort (Kahn's BFS)
 * FILE     : topological_sort_kahn.cpp
 * PROBLEM  : Linear ordering of DAG (course schedule)
 * LEETCODE : 210 — Course Schedule II
 * APPROACH : BFS on nodes with indegree 0
 * COMPLEX  : Time: O(V+E)  |  Space: O(V)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

vector<int> topoSort(int n, const vector<vector<int>> &adj) {
    vector<int> indeg(n, 0);
    for (int u = 0; u < n; u++)
        for (int v : adj[u]) indeg[v]++;

    queue<int> q;
    for (int i = 0; i < n; i++)
        if (indeg[i] == 0) q.push(i);

    vector<int> order;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : adj[u])
            if (--indeg[v] == 0) q.push(v);
    }
    return order.size() == n ? order : vector<int>{};
}

int main() {
    int n = 4;
    vector<vector<int>> adj(n);
    adj[0] = {1}; adj[1] = {2}; adj[0].push_back(2); adj[2] = {3};
    for (int x : topoSort(n, adj)) cout << x << " ";
    cout << endl;
    return 0;
}
