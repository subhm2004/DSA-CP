// ════════════════════════════════════════════════════════════════════════════
// SECOND BEST MINIMUM SPANNING TREE
// ────────────────────────────────────────────────────────────────────────────
// MST ke alawa sabse chhoti total weight wala spanning tree.
//
// Key observation: second-best MST, MST se exactly EK edge swap se banta hai:
//   MST se ek edge hatao (e_old), ek non-MST edge add karo (e_new)
//   delta = w(e_new) - w(e_old) minimum positive hona chahiye
//
// Steps:
//   1) Kruskal → MST weight + tree adjacency + inMst mark
//   2) Root pe binary lifting — har jump pe path ki top-2 max edge weights
//   3) Har non-MST edge (u,v,w): tree path u…v pe sabse bhari edge dhundho
//   4) candidate = MST_weight + w - k; answer = min candidate
//
// Time: O(E log V)  |  Space: O(V log V)
// Ref: https://cp-algorithms.com/graph/second_best_mst.html
// ════════════════════════════════════════════════════════════════════════════

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w, id;
    bool operator<(const Edge &o) const { return w < o.w; }
};

struct DSU {
    vector<int> p, r;
    explicit DSU(int n) : p(n), r(n, 0) { iota(p.begin(), p.end(), 0); }
    // ── find: path compression ke saath root dhundho ────────────────────────
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    // ── unite: do sets merge — false return matlab already connected ───────
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
};

// Do (max1, max2) pairs merge karo → combined path ki top-2 distinct weights
pair<int, int> combine(pair<int, int> a, pair<int, int> b) {
    int best = -2, second = -3;
    for (int x : {a.first, a.second, b.first, b.second}) {
        if (x > best) {
            second = best;
            best = x;
        } else if (x > second && x < best) {
            second = x;
        }
    }
    return {best, second};
}

struct SecondBestMST {
    int n, LOG;
    long long mstWeight = 0;
    vector<vector<pair<int, int>>> adj; // MST tree: (neighbor, edge weight)
    vector<int> depth;
    vector<vector<int>> up;             // binary lifting parent
    vector<vector<pair<int, int>>> mx; // mx[v][j] = 2^j jump pe top-2 max edges
    vector<char> inMst;

    explicit SecondBestMST(int n_) : n(n_) {
        LOG = 1;
        while ((1 << LOG) <= n) LOG++;
        adj.assign(n, {});
        depth.assign(n, 0);
        up.assign(n, vector<int>(LOG, -1));
        mx.assign(n, vector<pair<int, int>>(LOG, {-1, -2}));
    }

    // DFS se depth + direct parent edge weight set karo
    void dfs(int u, int par, int d) {
        depth[u] = depth[par] + 1;
        up[u][0] = par;
        mx[u][0] = {d, -2}; // d = edge (u,par) ka weight; root pe 0 sentinel
        for (auto [v, w] : adj[u]) {
            if (v == par) continue;
            dfs(v, u, w);
        }
    }

    // Binary lifting table banao — har 2^j jump pe max edges merge
    void buildLifting() {
        dfs(0, 0, 0);
        for (int j = 1; j < LOG; j++) {
            for (int v = 0; v < n; v++) {
                int mid = up[v][j - 1];
                if (mid == -1) continue;
                up[v][j] = up[mid][j - 1];
                mx[v][j] = combine(mx[v][j - 1], mx[mid][j - 1]);
            }
        }
    }

    // ── MST path u-v pe do sabse bhari edge weights ───────────────────────
    pair<int, int> pathMaxEdges(int u, int v) {
        pair<int, int> ans = {-2, -3};
        if (depth[u] < depth[v]) swap(u, v);

        // Step 1: u ko v ke depth tak uthao — har jump pe top-2 max edges collect
        int diff = depth[u] - depth[v];
        for (int j = LOG - 1; j >= 0; j--) {
            if (diff >> j & 1) {
                ans = combine(ans, mx[u][j]);
                u = up[u][j];
            }
        }
        if (u == v) return ans;

        // Step 2: same depth pe LCA tak dono ko saath uthao
        for (int j = LOG - 1; j >= 0; j--) {
            if (up[u][j] != -1 && up[u][j] != up[v][j]) {
                ans = combine(ans, combine(mx[u][j], mx[v][j]));
                u = up[u][j];
                v = up[v][j];
            }
        }
        // Step 3: LCA ke neeche wale direct edges bhi merge karo
        ans = combine(ans, combine(mx[u][0], mx[v][0]));
        return ans;
    }

    // Returns {mstWeight, secondBestWeight}; second = LLONG_MAX agar impossible
    pair<long long, long long> solve(vector<Edge> edges) {
        sort(edges.begin(), edges.end());
        inMst.assign((int)edges.size(), 0);
        DSU dsu(n);

        // Step 1: Kruskal MST
        for (const Edge &e : edges) {
            if (dsu.unite(e.u, e.v)) {
                mstWeight += e.w;
                inMst[e.id] = 1;
                adj[e.u].push_back({e.v, e.w});
                adj[e.v].push_back({e.u, e.w});
            }
        }

        buildLifting();

        // Step 2: har non-MST edge se ek swap try karo
        long long secondBest = LLONG_MAX;
        for (const Edge &e : edges) {
            if (inMst[e.id]) continue;

            auto [best, second] = pathMaxEdges(e.u, e.v);
            long long cand = LLONG_MAX;

            // Agar path ki sabse bhari edge != e.w → usse hata ke e add karo
            if (best != e.w)
                cand = mstWeight + e.w - best;
            else if (second >= 0)
                cand = mstWeight + e.w - second; // tie case — second heaviest

            secondBest = min(secondBest, cand);
        }

        return {mstWeight, secondBest};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ---- Demo graph (0-indexed) ----
    //   0 --10-- 1
    //   | \      |
    //   6  5     15
    //   |   \    |
    //   2 ---4-- 3
    // MST: 2-3(4), 0-3(5), 0-1(10) = 19
    // Second best: (0,3,5) ki jagah (0,2,6) → 19 + 6 - 5 = 20

    int n = 4;
    vector<Edge> edges = {
        {0, 1, 10, 0},
        {0, 2, 6, 1},
        {0, 3, 5, 2},
        {1, 3, 15, 3},
        {2, 3, 4, 4},
    };

    SecondBestMST solver(n);
    auto [mst, second] = solver.solve(edges);

    cout << "=== Second Best MST (Kruskal + LCA) ===\n\n";
    cout << "MST weight          : " << mst << "\n";
    cout << "Second best MST     : " << second << "\n";

    return 0;
}
