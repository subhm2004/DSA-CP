// ════════════════════════════════════════════════════════════════════════════
// VIRTUAL TREE (Auxiliary Tree) — Key nodes + unke LCAs ka minimal tree
// ────────────────────────────────────────────────────────────────────────────
// Problem: tree pe k special nodes ke saath kaam karna (queries, DP, etc.)
// Virtual tree sirf key nodes + unke LCAs contain karta hai — size O(k).
//
// Steps:
//   1) Euler tour (tin/tout) se ancestor check
//   2) Key nodes ko tin order me sort karo
//   3) Stack se LCAs ke saath edges add karo
//
// Complexity: O(k log k) per build
// ════════════════════════════════════════════════════════════════════════════

#include <bits/stdc++.h>
using namespace std;

struct VirtualTree {
    int n, timer = 0;
    vector<vector<int>> adj;
    vector<int> depth, parent, tin, tout;

    VirtualTree(int n) : n(n), adj(n), depth(n), parent(n, -1), tin(n), tout(n) {}

    // ── addEdge: undirected tree edge ──────────────────────────────────────
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // ── dfs: parent, depth, Euler tin/tout set karo ────────────────────────
    void dfs(int v, int p) {
        parent[v] = p;
        depth[v] = (p == -1 ? 0 : depth[p] + 1);
        tin[v] = timer++;
        for (int u : adj[v]) {
            if (u == p)
                continue;
            dfs(u, v);
        }
        tout[v] = timer++;
    }

    // ── isAncestor: u, v ka ancestor hai? (tin/tout interval check) ────────
    bool isAncestor(int u, int v) {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }

    // ── lca: Lowest Common Ancestor of a and b ─────────────────────────────
    int lca(int a, int b) {
        // Step 1: agar a, b ka ancestor hai to a hi LCA
        if (isAncestor(a, b))
            return a;
        if (isAncestor(b, a))
            return b;
        // Step 2: a ko upar uthao jab tak parent[a], b ka ancestor na ho
        while (!isAncestor(parent[a], b))
            a = parent[a];
        return parent[a];
    }

    // ── build: key nodes se virtual tree adjacency banao ───────────────────
    vector<vector<int>> build(vector<int> nodes) {
        // Step 1: key nodes ko Euler tin order me sort karo
        auto cmp = [&](int a, int b) { return tin[a] < tin[b]; };
        sort(nodes.begin(), nodes.end(), cmp);

        vector<int> st;
        vector<vector<int>> vtree;
        auto addNode = [&](int x) {
            if ((int)vtree.size() <= x)
                vtree.resize(x + 1);
        };

        st.push_back(nodes[0]);
        addNode(nodes[0]);

        // Step 2: har key node ke liye LCA stack se edges add karo
        for (int i = 1; i < (int)nodes.size(); i++) {
            int w = lca(st.back(), nodes[i]);
            addNode(w);
            addNode(nodes[i]);

            while (st.size() > 1 && depth[st.back()] >= depth[w]) {
                int u = st.back();
                st.pop_back();
                int v = st.back();
                if (v != w) {
                    vtree[w].push_back(u);
                    vtree[u].push_back(w);
                } else {
                    vtree[v].push_back(u);
                    vtree[u].push_back(v);
                }
            }
            if (st.back() != w)
                st.push_back(w);
            st.push_back(nodes[i]);
        }

        // Step 3: stack me bache nodes ko bhi connect karke virtual tree return
        while (st.size() > 1) {
            int u = st.back();
            st.pop_back();
            int v = st.back();
            vtree[v].push_back(u);
            vtree[u].push_back(v);
        }
        return vtree;
    }
};

int main() {
    int n = 7;
    VirtualTree vt(n);
    vector<pair<int, int>> edges = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}};
    for (auto [u, v] : edges)
        vt.addEdge(u, v);
    vt.dfs(0, -1);

    vector<int> keyNodes = {3, 4, 6};
    auto vtree = vt.build(keyNodes);

    cout << "Virtual tree built for key nodes {3,4,6}\n";
    cout << "LCA(3,6) = " << vt.lca(3, 6) << endl;
    return 0;
}
