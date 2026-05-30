/*
 * ============================================================================
 * TOPIC    : Virtual Tree (Auxiliary Tree)
 * FILE     : virtual_tree.cpp
 * PROBLEM  : Build tree containing only key nodes + LCAs (for k queries on tree)
 * APPROACH : Sort nodes by Euler tour order, stack + LCA to add edges
 * COMPLEX  : O(k log k) per build  |  Space: O(k)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct VirtualTree {
    int n, timer = 0;
    vector<vector<int>> adj;
    vector<int> depth, parent, tin, tout;

    VirtualTree(int n) : n(n), adj(n), depth(n), parent(n, -1), tin(n), tout(n) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

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

    bool isAncestor(int u, int v) {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }

    int lca(int a, int b) {
        if (isAncestor(a, b))
            return a;
        if (isAncestor(b, a))
            return b;
        while (!isAncestor(parent[a], b))
            a = parent[a];
        return parent[a];
    }

    // Build virtual tree adjacency for key nodes (must include root 0)
    vector<vector<int>> build(vector<int> nodes) {
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
