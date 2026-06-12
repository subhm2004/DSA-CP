#include <bits/stdc++.h>
using namespace std;

/*
 * Euler Tour + RMQ (Sparse Table) se LCA
 * --------------------------------------
 * DFS karte waqt har node ko euler[] mein daalo (entry + backtrack par dubara).
 * tin[u] = node u ka pehla index euler tour mein.
 *
 * LCA(u, v) = euler[ RMQ( depth, tin[u] .. tin[v] ) ]
 *   Range mein sabse kam depth wala node hi LCA hota hai.
 *
 * Preprocess: O(n log n)   |   Query: O(1)
 */

class EulerTourLCA {
private:
    int n, LOG;
    vector<vector<int>> adj;
    vector<int> depth, tin, euler, log2;
    vector<vector<int>> st;   // st[j][i] = [i, i+2^j) range mein min depth wale ka euler index

    void dfs(int u, int p) {
        tin[u] = euler.size();   // pehli baar euler[] mein aane ka index
        euler.push_back(u);

        for (int v : adj[u]) {
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            dfs(v, u);
            euler.push_back(u);   // backtrack — is edge se wapas aaye
        }
    }

    void buildSparseTable() {
        int m = euler.size();
        log2.assign(m + 1, 0);
        for (int i = 2; i <= m; ++i)
            log2[i] = log2[i / 2] + 1;

        LOG = log2[m] + 1;
        st.assign(LOG, vector<int>(m));

        for (int i = 0; i < m; ++i)
            st[0][i] = i;

        for (int j = 1; j < LOG; ++j)
            for (int i = 0; i + (1 << j) <= m; ++i) {
                int left = st[j - 1][i];
                int right = st[j - 1][i + (1 << (j - 1))];
                st[j][i] = (depth[euler[left]] <= depth[euler[right]]) ? left : right;
            }
    }

    int rmq(int l, int r) const {
        int j = log2[r - l + 1];
        int left = st[j][l];
        int right = st[j][r - (1 << j) + 1];
        return (depth[euler[left]] <= depth[euler[right]]) ? left : right;
    }

public:
    EulerTourLCA(int n, const vector<int>& parent) : n(n) {
        adj.assign(n, {});
        depth.assign(n, 0);
        tin.assign(n, 0);

        for (int i = 1; i < n; ++i)
            if (parent[i] != -1) {
                adj[parent[i]].push_back(i);
                adj[i].push_back(parent[i]);
            }

        dfs(0, -1);
        buildSparseTable();
    }

    EulerTourLCA(int n, const vector<vector<int>>& adjList, int root = 0)
        : n(n), adj(adjList) {
        depth.assign(n, 0);
        tin.assign(n, 0);
        dfs(root, -1);
        buildSparseTable();
    }

    int getDepth(int u) const { return depth[u]; }

    /*
     * lca(u, v) — O(1) query
     * tin[u] aur tin[v] ke beech euler tour par min depth wala node = LCA
     */
    int lca(int u, int v) const {
        int l = min(tin[u], tin[v]);
        int r = max(tin[u], tin[v]);
        return euler[rmq(l, r)];
    }
};

void solveTree(int treeNum, vector<int>& parent, vector<pair<int,int>>& queries) {
    cout << "\n===== Tree " << treeNum << " (Euler Tour + RMQ) =====\n";

    int n = parent.size();
    EulerTourLCA et(n, parent);

    cout << "Parent Array: ";
    for (int i = 0; i < n; ++i) cout << parent[i] << " ";
    cout << "\n\n-- LCA Queries (O(1) each) --\n";

    for (auto& [u, v] : queries)
        cout << "LCA(" << u << ", " << v << ") = " << et.lca(u, v) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    {
        vector<int> parent = {-1, 0, 0, 1, 1};
        vector<pair<int,int>> lcaQ = {{3, 4}, {3, 2}, {1, 2}};
        solveTree(1, parent, lcaQ);
    }

    {
        vector<int> parent = {-1, 0, 1, 2, 3, 4};
        vector<pair<int,int>> lcaQ = {{5, 3}, {4, 2}, {5, 1}};
        solveTree(2, parent, lcaQ);
    }

    {
        vector<int> parent = {-1, 0, 0, 0, 0, 1, 1, 3, 5};
        vector<pair<int,int>> lcaQ = {{8, 7}, {6, 7}, {8, 2}, {5, 4}};
        solveTree(3, parent, lcaQ);
    }

    return 0;
}
