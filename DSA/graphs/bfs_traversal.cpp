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

// ════════════════════════════════════════════════════════════════════════════
// GRAPHS — BFS Traversal (Level-Order)
// ────────────────────────────────────────────────────────────────────────────
// Problem: Undirected/directed graph me source se BFS traversal order aur
//          shortest distance (unweighted) nikalo.
//
// Approach: Queue + dist array as visited
//   - dist[src] = 0, src queue me push
//   - Queue se node uthao, neighbors check — unvisited ho to dist set + push
//   - dist[v] == -1 means unvisited — visited + distance dono track
//
// Complexity: Time O(V+E)  |  Space O(V) for queue + dist array
// ════════════════════════════════════════════════════════════════════════════

// ── bfs: source se level-order traversal order return ──
//   1) dist array -1 se init — -1 = unvisited
//   2) src ko dist=0 set karke queue me daalo
//   3) Queue empty tak: front pop, order me push, neighbors explore
//   4) Neighbor unvisited ho to dist[v] = dist[u]+1, queue me push
//   5) BFS order vector return — level-by-level discovery
vector<int> bfs(int n, const vector<vector<int>> &adj, int src) {
    vector<int> order, dist(n, -1);
    queue<int> q;
    dist[src] = 0;  // source visited + distance 0
    q.push(src);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);  // dequeue order = BFS traversal order
        for (int v : adj[u])
            if (dist[v] == -1) {  // pehli baar mila — unvisited neighbor
                dist[v] = dist[u] + 1;  // shortest path in unweighted graph
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
