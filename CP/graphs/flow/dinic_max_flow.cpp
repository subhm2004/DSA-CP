// ════════════════════════════════════════════════════════════════════════════
// DINIC'S ALGORITHM — Maximum Flow (Level Graph + Blocking Flow)
// ────────────────────────────────────────────────────────────────────────────
// Ford-Fulkerson se tez: har iteration me level graph (BFS) banao, phir
// blocking flow (DFS with ptr optimization) nikal kar flow badhao.
//
// Key ideas:
//   - BFS: sirf un edges se level assign karo jahan cap > 0 aur level[u]+1 == level[v]
//   - DFS: level graph pe blocking flow — jahan tak push ho sake
//   - ptr[u]: har node ke liye last tried edge index (repeated DFS fast)
//
// Complexity: O(V^2 * E) worst case, practice me bahut fast
// ════════════════════════════════════════════════════════════════════════════

#include <bits/stdc++.h>
using namespace std;

struct Dinic {
    struct Edge {
        int to, rev;
        long long cap;
    };

    int n, s, t;
    vector<vector<Edge>> g;
    vector<int> level, ptr;  // level = BFS depth, ptr = DFS optimization

    Dinic(int n, int s, int t) : n(n), s(s), t(t), g(n), level(n), ptr(n) {}

    // ── addEdge: forward edge cap ke saath, reverse edge cap=0 ───────────────
    void addEdge(int u, int v, long long cap) {
        Edge a{v, (int)g[v].size(), cap};
        Edge b{u, (int)g[u].size(), 0};
        g[u].push_back(a);
        g[v].push_back(b);
    }

    // ── bfs: level graph banao — sink reachable hai ya nahi ────────────────
    bool bfs() {
        // Step 1: level[] reset, source level=0, BFS queue me daalo
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        // Step 2: sirf cap>0 edges se level assign — level graph banta hai
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
        return level[t] != -1; // sink reachable hai ya nahi
    }

    // ── dfs: level graph pe blocking flow push karo ────────────────────────
    long long dfs(int u, long long pushed) {
        // Base: koi flow nahi bacha ya sink pahunch gaye
        if (pushed == 0 || u == t)
            return pushed;
        // Step 1: ptr[u] se current edge index — repeated DFS fast hota hai
        for (int &cid = ptr[u]; cid < (int)g[u].size(); cid++) {
            Edge &e = g[u][cid];
            // Step 2: sirf level graph edges (level[to] = level[u]+1) use karo
            if (level[e.to] != level[u] + 1 || e.cap == 0)
                continue;
            long long tr = dfs(e.to, min(pushed, e.cap));
            if (tr == 0)
                continue;
            // Step 3: flow push — forward cap kam, reverse cap badhao
            e.cap -= tr;
            g[e.to][e.rev].cap += tr;
            return tr;
        }
        return 0;
    }

    // ── maxFlow: BFS + blocking DFS loop ───────────────────────────────────
    long long maxFlow() {
        long long flow = 0;
        // Step 1: jab tak level graph me sink reachable hai, repeat
        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            // Step 2: blocking flow nikalo — jitna push ho sake DFS se
            while (long long pushed = dfs(s, LLONG_MAX))
                flow += pushed;
        }
        return flow;
    }
};

int main() {
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
