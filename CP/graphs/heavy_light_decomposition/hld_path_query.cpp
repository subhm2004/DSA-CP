// ════════════════════════════════════════════════════════════════════════════
// HEAVY-LIGHT DECOMPOSITION (HLD) — Tree Path Queries in O(log^2 n)
// ────────────────────────────────────────────────────────────────────────────
// Tree ko "heavy chains" me todo:
//   - Heavy child = sabse bada subtree wala bacha
//   - Har chain ko linear array me flatten karo (pos array)
//   - Path query = kuch chains ke segments ka sum (segment tree se)
//
// queryPath(a,b): jab tak same chain head na ho, neeche wale head ka segment query
// Complexity: build O(n), query O(log^2 n)
// ════════════════════════════════════════════════════════════════════════════

#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n;
    vector<long long> t;

    SegTree(int n) : n(n), t(4 * n, 0) {}

    // ── update: pos pe value set karo ──────────────────────────────────────
    void update(int v, int tl, int tr, int pos, long long val) {
        if (tl == tr) {
            t[v] = val;
            return;
        }
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(2 * v, tl, tm, pos, val);
        else
            update(2 * v + 1, tm + 1, tr, pos, val);
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    // ── query: [l, r] range sum ────────────────────────────────────────────
    long long query(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 0;
        if (l == tl && r == tr)
            return t[v];
        int tm = (tl + tr) / 2;
        return query(2 * v, tl, tm, l, min(r, tm)) + query(2 * v + 1, tm + 1, tr, max(l, tm + 1), r);
    }
};

struct HLD {
    int n, timer = 0;
    vector<vector<int>> adj;
    vector<int> parent, depth, heavy, head, pos, sz;
    vector<long long> base;
    SegTree st;

    HLD(int n) : n(n), adj(n), parent(n), depth(n), heavy(n, -1), head(n), pos(n), sz(n, 1), base(n), st(n) {}

    // ── addEdge: undirected tree edge ──────────────────────────────────────
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // ── dfs: subtree sizes, heavy child, parent, depth set karo ─────────────
    int dfs(int v, int p) {
        // Step 1: parent aur depth set karo
        parent[v] = p;
        depth[v] = (p == -1 ? 0 : depth[p] + 1);
        int maxSub = 0;
        // Step 2: har child ka subtree size compute karo
        for (int u : adj[v]) {
            if (u == p)
                continue;
            int sub = dfs(u, v);
            sz[v] += sz[u];
            // Step 3: sabse bada subtree wala child = heavy child
            if (sub > maxSub) {
                maxSub = sub;
                heavy[v] = u;
            }
        }
        return sz[v];
    }

    // ── decompose: chains banao, pos assign karo, seg tree me values daalo ─
    void decompose(int v, int h) {
        head[v] = h;                    // is chain ka head
        pos[v] = timer++;               // linear array index
        st.update(1, 0, n - 1, pos[v], base[v]);
        if (heavy[v] != -1)
            decompose(heavy[v], h);     // heavy child same chain me
        for (int u : adj[v]) {
            if (u == parent[v] || u == heavy[v])
                continue;
            decompose(u, u);          // light child = nayi chain ka head
        }
    }

    // ── queryPath: a se b tak path ka sum ──────────────────────────────────
    long long queryPath(int a, int b) {
        long long res = 0;
        // Step 1: jab tak alag chains me ho, neeche wale chain ka segment query
        for (; head[a] != head[b]; b = parent[head[b]]) {
            if (depth[head[a]] < depth[head[b]])
                swap(a, b);
            res += st.query(1, 0, n - 1, pos[head[a]], pos[a]);
            a = parent[head[a]];
        }
        // Step 2: same chain me bacha hua segment query karo
        if (depth[a] > depth[b])
            swap(a, b);
        res += st.query(1, 0, n - 1, pos[a], pos[b]);
        return res;
    }

    // ── build: dfs + decompose se poora HLD ready karo ─────────────────────
    void build(int root = 0) {
        dfs(root, -1);
        decompose(root, root);
    }
};

int main() {
    int n = 5;
    HLD hld(n);
    hld.base = {10, 2, 5, 8, 1};
    hld.addEdge(0, 1);
    hld.addEdge(1, 2);
    hld.addEdge(1, 3);
    hld.addEdge(1, 4);
    hld.build(0);

    cout << "Path sum 2 -> 4 = " << hld.queryPath(2, 4) << endl;
    cout << "Path sum 0 -> 3 = " << hld.queryPath(0, 3) << endl;
    return 0;
}
