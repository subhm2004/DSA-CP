// ════════════════════════════════════════════════════════════════════════════
// MIN COST MAX FLOW — Successive Shortest Path (SPFA)
// ────────────────────────────────────────────────────────────────────────────
// Problem: source se sink tak MAXIMUM flow bhejo, total COST minimum ho.
//
// Approach:
//   1) Residual graph me SPFA se shortest path (cost ke hisaab se) dhundo
//   2) Path pe jitna flow bhej sakte ho (bottleneck) bhejo
//   3) Forward edge ki capacity kam karo, reverse edge ki badhao
//   4) Jab tak augmenting path milti rahe, repeat karo
//
// Reverse edge cost = -forward cost (flow cancel karne ke liye)
// Complexity: O(flow * E log V) typical with SPFA
// ════════════════════════════════════════════════════════════════════════════

#include <bits/stdc++.h>
using namespace std;

struct MinCostMaxFlow {
    struct Edge {
        int to, rev;           // rev = reverse edge ka index us node ki adj list me
        long long cap, cost;   // cap = remaining capacity, cost = per unit cost
    };

    int n, s, t;
    vector<vector<Edge>> g;
    vector<long long> dist;
    vector<int> parent, parentEdge;

    // ── Constructor: n nodes, source s, sink t ─────────────────────────────
    MinCostMaxFlow(int n, int s, int t) : n(n), s(s), t(t), g(n), dist(n), parent(n), parentEdge(n) {}

    // ── addEdge: u -> v with capacity aur cost; reverse edge cap=0, cost=-cost ─
    void addEdge(int u, int v, long long cap, long long cost) {
        g[u].push_back({v, (int)g[v].size(), cap, cost});
        g[v].push_back({u, (int)g[u].size(), 0, -cost});
    }

    // ── spfa: source se sink tak shortest path (cost) dhundo ───────────────
    // Returns false agar koi augmenting path nahi mili (dist[t] == INF)
    bool spfa() {
        const long long INF = 1e18;
        // Step 1: dist[] sab INF, source=0, SPFA queue me daalo
        fill(dist.begin(), dist.end(), INF);
        vector<bool> inq(n, false);
        queue<int> q;
        dist[s] = 0;
        q.push(s);
        inq[s] = true;

        // Step 2: residual graph pe shortest path (cost ke hisaab se) dhundo
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u] = false;
            for (int i = 0; i < (int)g[u].size(); i++) {
                Edge &e = g[u][i];
                // Step 3: cap>0 edges relax — parent track for path reconstruction
                if (e.cap > 0 && dist[u] + e.cost < dist[e.to]) {
                    dist[e.to] = dist[u] + e.cost;
                    parent[e.to] = u;
                    parentEdge[e.to] = i;
                    if (!inq[e.to]) {
                        inq[e.to] = true;
                        q.push(e.to);
                    }
                }
            }
        }
        return dist[t] != 1e18; // augmenting path mili ya nahi
    }

    // ── minCostMaxFlow: loop me SPFA + augment until no path ────────────────
    pair<long long, long long> minCostMaxFlow() {
        long long flow = 0, cost = 0;
        // Step 1: jab tak cheapest augmenting path milti hai, repeat
        while (spfa()) {
            // Step 2: path ka bottleneck = min remaining capacity on path
            long long add = LLONG_MAX;
            for (int v = t; v != s; v = parent[v]) {
                Edge &e = g[parent[v]][parentEdge[v]];
                add = min(add, e.cap);
            }
            // Step 3: flow push — forward cap kam, reverse cap badhao
            for (int v = t; v != s; v = parent[v]) {
                Edge &e = g[parent[v]][parentEdge[v]];
                e.cap -= add;
                g[v][e.rev].cap += add;
            }
            flow += add;
            cost += add * dist[t];
        }
        return {flow, cost};
    }
};

int main() {
    int n = 4, s = 0, t = 3;
    MinCostMaxFlow mcmf(n, s, t);
    mcmf.addEdge(0, 1, 2, 1);
    mcmf.addEdge(0, 2, 1, 3);
    mcmf.addEdge(1, 2, 1, 1);
    mcmf.addEdge(1, 3, 1, 2);
    mcmf.addEdge(2, 3, 2, 1);

    auto [flow, cost] = mcmf.minCostMaxFlow();
    cout << "Flow = " << flow << ", Min cost = " << cost << endl;
    return 0;
}
