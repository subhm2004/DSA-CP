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

// ════════════════════════════════════════════════════════════════════════════
// GRAPHS — DFS Traversal (Depth-First)
// ────────────────────────────────────────────────────────────────────────────
// Problem: Adjacency list graph me source se DFS traversal order nikalo —
//          pehle ek branch poori depth tak, phir backtrack.
//
// Approach: Recursive DFS + visited array
//   - vis[u] = true mark karo, order me push
//   - Har unvisited neighbor pe recursively dfs call
//   - Pre-order style: node pe aate hi order me add
//
// Complexity: Time O(V+E)  |  Space O(V) for vis + recursion stack
// ════════════════════════════════════════════════════════════════════════════

// ── dfs: node u se recursive depth-first explore ──
//   1) vis[u] = true — visited mark
//   2) u ko order me push — pre-order traversal
//   3) Har neighbor v: agar unvisited ho to dfs(v) call
//   4) Ek branch poori explore hone ke baad backtrack hota hai
void dfs(int u, const vector<vector<int>> &adj, vector<bool> &vis, vector<int> &order) {
    vis[u] = true;
    order.push_back(u);  // node enter karte hi record — DFS order
    for (int v : adj[u])
        if (!vis[v]) dfs(v, adj, vis, order);  // unvisited neighbor — depth me jao
}

// ── dfsOrder: source se DFS traversal order return ──
//   1) vis array false se init, order empty
//   2) src se dfs start karo
//   3) Connected component ka DFS order return
//   4) (Disconnected graph me har component ke liye alag call chahiye)
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
