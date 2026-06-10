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

// ════════════════════════════════════════════════════════════════════════════
// GRAPHS — Cycle Detection (Undirected)
// ────────────────────────────────────────────────────────────────────────────
// Problem: Undirected graph me cycle hai ya nahi detect karo.
//          Tree me exactly V-1 edges hote hain — extra edge = cycle.
//
// Approach: DFS with Parent Tracking
//   - vis[u] = true mark karo
//   - Neighbor v: unvisited ho to dfs(v, u) — u parent hai
//   - Visited neighbor jo parent NAHI hai → cycle (back-edge)
//   - Disconnected components ke liye har unvisited se DFS
//
// Complexity: Time O(V+E)  |  Space O(V) for vis + stack
// ════════════════════════════════════════════════════════════════════════════

// ── dfsCycle: u se DFS — parent p ko ignore karke cycle dhundho ──
//   1) vis[u] = true mark karo
//   2) Har neighbor v: unvisited ho to dfsCycle(v, u) recursively
//   3) Visited v jo parent p nahi hai → cycle mil gaya (non-tree edge)
//   4) Sab clean → false return
bool dfsCycle(int u, int p, const vector<vector<int>> &adj, vector<bool> &vis) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) {
            if (dfsCycle(v, u, adj, vis)) return true;  // subtree me cycle
        } else if (v != p)
            return true;  // visited + not parent = back-edge = cycle
    }
    return false;
}

// ── hasCycleUndirected: poora undirected graph me cycle check ──
//   1) vis array false se init
//   2) Har unvisited node i se dfsCycle(i, -1) start
//   3) Kisi component me cycle mila → true
//   4) Sab components clean → false (forest/tree)
bool hasCycleUndirected(int n, const vector<vector<int>> &adj) {
    vector<bool> vis(n, false);
    for (int i = 0; i < n; i++)
        if (!vis[i] && dfsCycle(i, -1, adj, vis))
            return true;  // disconnected graph — har component check
    return false;
}

int main() {
    vector<vector<int>> adj(3);
    adj[0] = {1}; adj[1] = {0, 2}; adj[2] = {1};
    cout << (hasCycleUndirected(3, adj) ? "Cycle" : "No cycle") << endl;
    return 0;
}
