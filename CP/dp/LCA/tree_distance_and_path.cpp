#include <bits/stdc++.h>
using namespace std;

/*
 * Binary Lifting ke upar common tree queries:
 *   1. distance(u, v)     — u se v tak kitne edges
 *   2. kthOnPath(u, v, k) — u->v path par k-th node (0-indexed, u = k=0)
 *
 * distance = depth[u] + depth[v] - 2 * depth[lca(u,v)]
 */

class TreeLCA {
private:
    int n, LOG;
    vector<vector<int>> up;
    vector<int> depth;

    void computeDepth(const vector<int>& parent) {
        depth[0] = 0;
        for (int i = 1; i < n; ++i)
            depth[i] = depth[parent[i]] + 1;
    }

public:
    TreeLCA(int n, const vector<int>& parent) : n(n) {
        LOG = ceil(log2(n + 1)) + 1;
        up.assign(n, vector<int>(LOG, -1));
        depth.assign(n, 0);

        for (int i = 0; i < n; ++i)
            up[i][0] = parent[i];

        computeDepth(parent);

        for (int j = 1; j < LOG; ++j)
            for (int i = 0; i < n; ++i)
                if (up[i][j - 1] != -1)
                    up[i][j] = up[up[i][j - 1]][j - 1];
    }

    int getKthAncestor(int node, int k) {
        for (int i = 0; i < LOG; ++i) {
            if (k & (1 << i)) {
                node = up[node][i];
                if (node == -1) return -1;
            }
        }
        return node;
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        u = getKthAncestor(u, depth[u] - depth[v]);
        if (u == v) return u;

        for (int j = LOG - 1; j >= 0; --j)
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        return up[u][0];
    }

    int getDepth(int u) const { return depth[u]; }

    /*
     * distance(u, v) — simple path par edges ki ginti
     */
    int distance(int u, int v) {
        int anc = lca(u, v);
        return depth[u] + depth[v] - 2 * depth[anc];
    }

    /*
     * kthOnPath(u, v, k) — u se v jaate hue k-th node
     *   k = 0 -> u,  k = distance(u,v) -> v
     *   Path: u -> ... -> lca -> ... -> v
     *
     *   distToLca = depth[u] - depth[lca]
     *   agar k <= distToLca: u se k steps upar nahi, neeche side se upar
     *     = getKthAncestor(u, k)  ... wait
     *
     *   From u toward lca: we go UP. k steps from u toward lca = ancestor at k up.
     *   If k <= distToLca: return getKthAncestor(u, k)
     *   Else: from v side, remaining steps from v going up:
     *     rem = distance(u,v) - k
     *     return getKthAncestor(v, rem)
     */
    int kthOnPath(int u, int v, int k) {
        int anc = lca(u, v);
        int distToLca = depth[u] - depth[anc];
        int total = distance(u, v);

        if (k < 0 || k > total) return -1;
        if (k <= distToLca) return getKthAncestor(u, k);
        return getKthAncestor(v, total - k);
    }
};

void solveTree(int treeNum, vector<int>& parent,
               vector<pair<int,int>>& distQ,
               vector<tuple<int,int,int>>& pathQ) {
    cout << "\n===== Tree " << treeNum << " (Distance & Path) =====\n";

    TreeLCA tree(parent.size(), parent);

    cout << "\n-- Distance Queries --\n";
    for (auto& [u, v] : distQ)
        cout << "dist(" << u << ", " << v << ") = " << tree.distance(u, v) << "\n";

    cout << "\n-- Kth Node on Path Queries --\n";
    for (auto& [u, v, k] : pathQ)
        cout << "kthOnPath(" << u << ", " << v << ", " << k << ") = "
             << tree.kthOnPath(u, v, k) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Tree 1:
    //         0
    //        / \
    //       1   2
    //      / \
    //     3   4
    {
        vector<int> parent = {-1, 0, 0, 1, 1};
        vector<pair<int,int>> distQ = {{3, 4}, {3, 2}, {1, 2}};
        vector<tuple<int,int,int>> pathQ = {
            {3, 4, 0}, {3, 4, 1}, {3, 4, 2},
            {3, 2, 0}, {3, 2, 1}, {3, 2, 2}
        };
        solveTree(1, parent, distQ, pathQ);
    }

    // Tree 2: chain 0-1-2-3-4-5
    {
        vector<int> parent = {-1, 0, 1, 2, 3, 4};
        vector<pair<int,int>> distQ = {{5, 0}, {5, 3}, {2, 4}};
        vector<tuple<int,int,int>> pathQ = {
            {5, 0, 0}, {5, 0, 3}, {5, 0, 5},
            {5, 3, 0}, {5, 3, 2}
        };
        solveTree(2, parent, distQ, pathQ);
    }

    // Tree 3: wide tree
    {
        vector<int> parent = {-1, 0, 0, 0, 0, 1, 1, 3, 5};
        vector<pair<int,int>> distQ = {{8, 7}, {8, 2}, {5, 4}};
        vector<tuple<int,int,int>> pathQ = {
            {8, 7, 0}, {8, 7, 2}, {8, 7, 4},
            {8, 2, 0}, {8, 2, 3}
        };
        solveTree(3, parent, distQ, pathQ);
    }

    return 0;
}
