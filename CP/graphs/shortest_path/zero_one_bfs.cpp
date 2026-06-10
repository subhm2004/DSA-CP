#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// 0-1 BFS — Shortest Path jab edge weights sirf 0 ya 1 hon
// ────────────────────────────────────────────────────────────────────────────
// Normal BFS O(V+E) hai par unweighted graphs ke liye.
// Jab weights 0/1 hon, deque use karo — Dijkstra jaisa par O(V+E)!
//
// Weight 0 edge -> neighbor ko deque ke FRONT me daalo (turant process hoga)
// Weight 1 edge -> neighbor ko deque ke BACK me daalo (thoda baad process)
//
// Kyunki sirf 0/1 weights hain, deque se hamesha minimum distance wala
// node pehle process hota hai — priority queue ki zaroorat nahi.
// Time: O(V + E)  |  Space: O(V + E)
// ════════════════════════════════════════════════════════════════════════════

// ── zeroOneBFS: src se sab nodes ka shortest distance return karo ──────────
// dist[src] = 0, deque me src daalo.
// Har node pop karke neighbors relax — weight 0 -> push_front, weight 1 -> push_back.
// Final dist array return (unreachable = INF).
vector<int> zeroOneBFS(int n, const vector<vector<pair<int, int>>> &adj, int src) {
    const int INF = 1e9;
    // Step 1: dist[] sab INF, source = 0, deque me src daalo
    vector<int> dist(n, INF);
    deque<int> dq;
    dist[src] = 0;
    dq.push_back(src);

    // Step 2: deque se node nikalo — 0-weight edges wale nodes pehle process honge
    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        // Step 3: har neighbor relax karo
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                // Step 4: weight 0 -> front (turant process), weight 1 -> back (thoda baad)
                if (w == 0)
                    dq.push_front(v);
                else
                    dq.push_back(v);
            }
        }
    }
    return dist;
}

int main() {
    int n = 5;
    vector<vector<pair<int, int>>> adj(n);
    adj[0].push_back({1, 0});
    adj[0].push_back({2, 1});
    adj[1].push_back({2, 0});
    adj[2].push_back({3, 1});
    adj[3].push_back({4, 0});

    auto dist = zeroOneBFS(n, adj, 0);
    cout << "Distances from 0:\n";
    for (int i = 0; i < n; i++)
        cout << i << " -> " << dist[i] << endl;
    return 0;
}
