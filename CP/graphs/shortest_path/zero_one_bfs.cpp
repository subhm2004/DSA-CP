/*
 * ============================================================================
 * TOPIC    : Shortest Path — 0-1 BFS
 * FILE     : zero_one_bfs.cpp
 * PROBLEM  : Shortest path when edge weights are 0 or 1
 * APPROACH : Deque — push front for weight 0, back for weight 1
 * COMPLEX  : Time: O(V + E)  |  Space: O(V + E)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

vector<int> zeroOneBFS(int n, const vector<vector<pair<int, int>>> &adj, int src) {
    const int INF = 1e9;
    vector<int> dist(n, INF);
    deque<int> dq;
    dist[src] = 0;
    dq.push_back(src);

    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
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
