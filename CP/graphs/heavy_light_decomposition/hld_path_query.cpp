/*
 * ============================================================================
 * TOPIC    : Heavy-Light Decomposition (HLD)
 * FILE     : hld_path_query.cpp
 * PROBLEM  : Path sum query / update on tree in O(log^2 n)
 * APPROACH : Decompose into heavy chains, segment tree on linearized array
 * COMPLEX  : Query/Update O(log^2 n)  |  Build O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n;
    vector<long long> t;
    SegTree(int n) : n(n), t(4 * n, 0) {}

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

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int dfs(int v, int p) {
        parent[v] = p;
        depth[v] = (p == -1 ? 0 : depth[p] + 1);
        int maxSub = 0;
        for (int u : adj[v]) {
            if (u == p)
                continue;
            int sub = dfs(u, v);
            sz[v] += sz[u];
            if (sub > maxSub) {
                maxSub = sub;
                heavy[v] = u;
            }
        }
        return sz[v];
    }

    void decompose(int v, int h) {
        head[v] = h;
        pos[v] = timer++;
        st.update(1, 0, n - 1, pos[v], base[v]);
        if (heavy[v] != -1)
            decompose(heavy[v], h);
        for (int u : adj[v]) {
            if (u == parent[v] || u == heavy[v])
                continue;
            decompose(u, u);
        }
    }

    long long queryPath(int a, int b) {
        long long res = 0;
        for (; head[a] != head[b]; b = parent[head[b]]) {
            if (depth[head[a]] < depth[head[b]])
                swap(a, b);
            res += st.query(1, 0, n - 1, pos[head[a]], pos[a]);
            a = parent[head[a]];
        }
        if (depth[a] > depth[b])
            swap(a, b);
        res += st.query(1, 0, n - 1, pos[a], pos[b]);
        return res;
    }

    void build(int root = 0) {
        dfs(root, -1);
        decompose(root, root);
    }
};

int main() {
  // Tree: 0-1-3, 1-2, 1-4
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
