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

// ════════════════════════════════════════════════════════════════════════════
// LEETCODE 210 — Course Schedule II (Kahn's Topological Sort)
// ────────────────────────────────────────────────────────────────────────────
// Problem: DAG ka topological order nikalo — har edge u→v me u, v se pehle aaye.
//          Cycle ho to empty return (courses complete nahi ho sakte).
//
// Approach: Kahn's Algorithm (BFS on indegree 0 nodes)
//   - Sab nodes ka indegree count karo
//   - indegree 0 wale queue me daalo
//   - Node process karo → neighbors ka indegree-- → 0 ho to queue me
//   - order.size()==n → valid topo sort, warna cycle
//
// Complexity: Time O(V+E)  |  Space O(V) for indegree + queue
// ════════════════════════════════════════════════════════════════════════════

// ── topoSort: DAG ka topological ordering return ──
//   1) Har edge u→v ke liye indeg[v]++ — incoming edges count
//   2) indeg[i]==0 wale sab queue me push — koi prerequisite nahi
//   3) BFS: node pop → order me add → neighbors indeg-- → 0 ho to push
//   4) order.size()==n → valid order return
//   5) Kam nodes process hue → cycle hai → empty vector return
vector<int> topoSort(int n, const vector<vector<int>> &adj) {
    vector<int> indeg(n, 0);
    for (int u = 0; u < n; u++)
        for (int v : adj[u]) indeg[v]++;  // har edge se v ka indegree badhao

    queue<int> q;
    for (int i = 0; i < n; i++)
        if (indeg[i] == 0) q.push(i);  // no prerequisites — pehle le sakte ho

    vector<int> order;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);  // u ab safe hai — saare prerequisites done
        for (int v : adj[u])
            if (--indeg[v] == 0) q.push(v);  // v ka last prerequisite complete
    }
    return order.size() == n ? order : vector<int>{};  // nahi to cycle
}

int main() {
    int n = 4;
    vector<vector<int>> adj(n);
    adj[0] = {1}; adj[1] = {2}; adj[0].push_back(2); adj[2] = {3};
    for (int x : topoSort(n, adj)) cout << x << " ";
    cout << endl;
    return 0;
}
