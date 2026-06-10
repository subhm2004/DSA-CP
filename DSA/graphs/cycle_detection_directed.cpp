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

// ════════════════════════════════════════════════════════════════════════════
// LEETCODE 207 — Course Schedule (Cycle Detection)
// ────────────────────────────────────────────────────────────────────────────
// Problem: Directed graph me cycle hai ya nahi? Cycle = courses complete
//          nahi kar sakte (prerequisite loop).
//
// Approach: DFS Three-Color Marking
//   - 0 = unvisited (white), 1 = currently in recursion stack (gray)
//   - 2 = fully processed (black)
//   - Gray neighbor mila = back-edge = cycle
//   - Har unvisited node se DFS start karo
//
// Complexity: Time O(V+E)  |  Space O(V) for color array + stack
// ════════════════════════════════════════════════════════════════════════════

// ── dfsDir: node u se DFS — cycle detect karo ──
//   1) color[u] = 1 — ab recursion stack me hai (gray)
//   2) Har neighbor v: agar gray (1) hai to cycle mil gaya
//   3) Agar white (0) hai to recursively dfsDir call
//   4) Sab neighbors done → color[u] = 2 (black) — safe node
//   5) Koi cycle nahi to false return
bool dfsDir(int u, const vector<vector<int>> &adj, vector<int> &color) {
    color[u] = 1;  // entering recursion stack
    for (int v : adj[u]) {
        if (color[v] == 1) return true;  // back-edge — v abhi stack me hai
        if (color[v] == 0 && dfsDir(v, adj, color)) return true;  // subtree me cycle
    }
    color[u] = 2;  // poora subtree process ho gaya — no cycle from u
    return false;
}

// ── hasCycleDirected: poora graph scan — kahi cycle hai? ──
//   1) color array size n, sab 0 (unvisited)
//   2) Har node i jo unvisited ho usse dfsDir start karo
//   3) Kisi bhi DFS se true aaya to seedha true return
//   4) Sab components clean → false (DAG hai)
bool hasCycleDirected(int n, const vector<vector<int>> &adj) {
    vector<int> color(n, 0);
    for (int i = 0; i < n; i++)
        if (color[i] == 0 && dfsDir(i, adj, color))
            return true;  // disconnected component me bhi cycle ho sakta hai
    return false;
}

int main() {
    vector<vector<int>> adj(4);
    adj[0] = {1}; adj[1] = {2}; adj[2] = {3}; adj[3] = {1};
    cout << (hasCycleDirected(4, adj) ? "Cycle" : "No cycle") << endl;
    return 0;
}
