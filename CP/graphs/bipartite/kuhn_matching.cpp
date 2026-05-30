/*
 * ============================================================================
 * TOPIC    : Bipartite Matching — Kuhn's Algorithm
 * FILE     : kuhn_matching.cpp
 * PROBLEM  : Maximum matching in bipartite graph
 * APPROACH : DFS augmenting paths (Kuhn)
 * COMPLEX  : O(V * E)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct Kuhn {
    int nLeft, nRight;
    vector<vector<int>> adj;
    vector<int> matchR, vis;
    int timer = 0;

    Kuhn(int nL, int nR) : nLeft(nL), nRight(nR), adj(nL), matchR(nR, -1), vis(nR) {}

    void addEdge(int u, int v) { adj[u].push_back(v); }

    bool dfs(int u) {
        for (int v : adj[u]) {
            if (vis[v] == timer) continue;
            vis[v] = timer;
            if (matchR[v] == -1 || dfs(matchR[v])) {
                matchR[v] = u;
                return true;
            }
        }
        return false;
    }

    int maxMatching() {
        int matching = 0;
        for (int u = 0; u < nLeft; u++) {
            timer++;
            if (dfs(u)) matching++;
        }
        return matching;
    }

    vector<pair<int, int>> getPairs() {
        vector<pair<int, int>> pairs;
        for (int v = 0; v < nRight; v++)
            if (matchR[v] != -1)
                pairs.push_back({matchR[v], v});
        return pairs;
    }
};

int main() {
    // Jobs (0..2) -> Workers (0..3)
    Kuhn km(3, 4);
    km.addEdge(0, 0);
    km.addEdge(0, 1);
    km.addEdge(1, 1);
    km.addEdge(1, 2);
    km.addEdge(2, 2);
    km.addEdge(2, 3);

    cout << "Max matching = " << km.maxMatching() << endl;
    for (auto [u, v] : km.getPairs())
        cout << "Job " << u << " -> Worker " << v << endl;
    return 0;
}
