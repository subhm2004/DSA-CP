/*
 * ============================================================================
 * TOPIC    : Network Flow — Dinic's Algorithm
 * FILE     : dinic_max_flow.cpp
 * PROBLEM  : Maximum flow faster than Edmonds-Karp
 * APPROACH : Level graph (BFS) + blocking flow (DFS)
 * COMPLEX  : Time: O(V^2 E) typical  |  Space: O(V + E)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct Dinic {
    struct Edge {
        int to, rev;
        long long cap;
    };

    int n, s, t;
    vector<vector<Edge>> g;
    vector<int> level, ptr;

    Dinic(int n, int s, int t) : n(n), s(s), t(t), g(n), level(n), ptr(n) {}

    void addEdge(int u, int v, long long cap) {
        Edge a{v, (int)g[v].size(), cap};
        Edge b{u, (int)g[u].size(), 0};
        g[u].push_back(a);
        g[v].push_back(b);
    }

    bool bfs() {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto &e : g[u]) {
                if (e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }

    long long dfs(int u, long long pushed) {
        if (pushed == 0 || u == t)
            return pushed;
        for (int &cid = ptr[u]; cid < (int)g[u].size(); cid++) {
            Edge &e = g[u][cid];
            if (level[e.to] != level[u] + 1 || e.cap == 0)
                continue;
            long long tr = dfs(e.to, min(pushed, e.cap));
            if (tr == 0)
                continue;
            e.cap -= tr;
            g[e.to][e.rev].cap += tr;
            return tr;
        }
        return 0;
    }

    long long maxFlow() {
        long long flow = 0;
        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, LLONG_MAX))
                flow += pushed;
        }
        return flow;
    }
};

int main() {
    // Example: 0->1 (10), 0->2 (15), 1->3 (10), 2->3 (25), 3->4 (30)
    int n = 5, s = 0, t = 4;
    Dinic dinic(n, s, t);
    dinic.addEdge(0, 1, 10);
    dinic.addEdge(0, 2, 15);
    dinic.addEdge(1, 3, 10);
    dinic.addEdge(2, 3, 25);
    dinic.addEdge(3, 4, 30);

    cout << "Max flow (Dinic) = " << dinic.maxFlow() << endl;
    return 0;
}
