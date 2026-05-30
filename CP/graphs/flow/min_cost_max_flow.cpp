/*
 * ============================================================================
 * TOPIC    : Network Flow — Min Cost Max Flow
 * FILE     : min_cost_max_flow.cpp
 * PROBLEM  : Send max flow with minimum total cost
 * APPROACH : Successive shortest path (SPFA / Dijkstra on potentials)
 * COMPLEX  : Time: O(flow * E log V)  |  Space: O(V + E)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct MinCostMaxFlow {
    struct Edge {
        int to, rev;
        long long cap, cost;
    };

    int n, s, t;
    vector<vector<Edge>> g;
    vector<long long> dist;
    vector<int> parent, parentEdge;

    MinCostMaxFlow(int n, int s, int t) : n(n), s(s), t(t), g(n), dist(n), parent(n), parentEdge(n) {}

    void addEdge(int u, int v, long long cap, long long cost) {
        g[u].push_back({v, (int)g[v].size(), cap, cost});
        g[v].push_back({u, (int)g[u].size(), 0, -cost});
    }

    bool spfa() {
        const long long INF = 1e18;
        fill(dist.begin(), dist.end(), INF);
        vector<bool> inq(n, false);
        queue<int> q;
        dist[s] = 0;
        q.push(s);
        inq[s] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u] = false;
            for (int i = 0; i < (int)g[u].size(); i++) {
                Edge &e = g[u][i];
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
        return dist[t] != 1e18;
    }

    pair<long long, long long> minCostMaxFlow() {
        long long flow = 0, cost = 0;
        while (spfa()) {
            long long add = LLONG_MAX;
            for (int v = t; v != s; v = parent[v]) {
                Edge &e = g[parent[v]][parentEdge[v]];
                add = min(add, e.cap);
            }
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
