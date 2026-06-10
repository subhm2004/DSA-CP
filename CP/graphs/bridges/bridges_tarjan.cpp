// ════════════════════════════════════════════════════════════════════════════
// BRIDGES — Tarjan's Algorithm (DFS)
// ────────────────────────────────────────────────────────────────────────────
// Bridge = aisi edge jiska hataana graph ko disconnect kar de.
// disc[u] = DFS discovery time | low[u] = subtree se sabse chhota reachable time
// Bridge condition: low[v] > disc[u] (v ka subtree u ke bina upar nahi ja sakta)
// Time: O(V + E) | Space: O(V + E)
// ════════════════════════════════════════════════════════════════════════════

#include <bits/stdc++.h>
using namespace std;

class BridgeFinder {
    vector<vector<int>> adj;
    vector<int> disc, low;              // discovery time aur low-link values
    vector<pair<int, int>> bridges;
    int timer = 0;

    // ── dfs: Tarjan DFS — har edge par low[] update karo ────────────────────
    // u      -> current node
    // parent -> jis node se aaye (parent edge skip karo undirected mein)
    void dfs(int u, int parent) {
        // Step 1: node visit — disc[u] aur low[u] dono = ++timer
        disc[u] = low[u] = ++timer;

        for (int v : adj[u]) {
            if (v == parent)
                continue;

            if (disc[v] == 0) {
                // Step 2: tree edge — child DFS, phir low[u] = min(low[u], low[v])
                dfs(v, u);
                low[u] = min(low[u], low[v]);

                // Step 3: bridge condition — low[v] > disc[u] matlab v alag component
                if (low[v] > disc[u])
                    bridges.push_back({min(u, v), max(u, v)});
            } else {
                // Step 4: back edge — ancestor ka disc time se low update
                low[u] = min(low[u], disc[v]);
            }
        }
    }

public:
    BridgeFinder(int n) : adj(n), disc(n, 0), low(n, 0) {}

    // ── addEdge: undirected edge — dono taraf adjacency me add ──────────────
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // ── findBridges: har disconnected component se DFS chalao ───────────────
    vector<pair<int, int>> findBridges() {
        for (int i = 0; i < (int)adj.size(); i++)
            if (disc[i] == 0)
                dfs(i, -1);
        return bridges;
    }
};

int main() {
    int n = 5;
    BridgeFinder g(n);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0); // triangle — ye edges bridge nahi
    g.addEdge(1, 3);
    g.addEdge(3, 4); // 1-3 aur 3-4 bridges hain

    auto bridges = g.findBridges();
    cout << "Bridges:\n";
    for (auto [u, v] : bridges)
        cout << u << " -- " << v << endl;
    return 0;
}
