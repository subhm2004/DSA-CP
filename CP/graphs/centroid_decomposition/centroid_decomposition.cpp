/*
 * ============================================================================
 * TOPIC    : Centroid Decomposition
 * FILE     : centroid_decomposition.cpp
 * PROBLEM  : Decompose tree for distance queries / counting paths
 * APPROACH : Repeatedly remove centroid, process subtrees, recurse
 * COMPLEX  : Build O(n log n)  |  Space: O(n log n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct CentroidDecomposition {
    int n;
    vector<vector<int>> adj;
    vector<int> sz, dead;
    vector<vector<int>> cdTree; // optional: tree of centroids
    vector<int> parentCentroid;

    CentroidDecomposition(int n) : n(n), adj(n), sz(n), dead(n), cdTree(n), parentCentroid(n, -1) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int getSize(int v, int p) {
        sz[v] = 1;
        for (int u : adj[v]) {
            if (u == p || dead[u])
                continue;
            getSize(u, v);
            sz[v] += sz[u];
        }
        return sz[v];
    }

    int getCentroid(int v, int p, int treeSize) {
        for (int u : adj[v]) {
            if (u == p || dead[u])
                continue;
            if (sz[u] > treeSize / 2)
                return getCentroid(u, v, treeSize);
        }
        return v;
    }

    void decompose(int entry, int pCentroid = -1) {
        int treeSize = getSize(entry, -1);
        int c = getCentroid(entry, -1, treeSize);
        dead[c] = 1;
        parentCentroid[c] = pCentroid;

        if (pCentroid != -1) {
            cdTree[pCentroid].push_back(c);
            cdTree[c].push_back(pCentroid);
        }

        for (int u : adj[c]) {
            if (!dead[u])
                decompose(u, c);
        }
    }

    // Example: count nodes within distance K from start (naive on centroid tree)
    int countWithinK(int start, int k, int c, int distFromCentroid) {
        if (distFromCentroid > k)
            return 0;
        int res = 1;
        for (int childCentroid : cdTree[c]) {
            if (childCentroid == parentCentroid[c])
                continue;
            // In full solution: precompute distances from each centroid
        }
        return res;
    }
};

int main() {
    int n = 7;
    CentroidDecomposition cd(n);
    vector<pair<int, int>> edges = {{0, 1}, {1, 2}, {1, 3}, {3, 4}, {3, 5}, {5, 6}};
    for (auto [u, v] : edges)
        cd.addEdge(u, v);

    cd.decompose(0);

    cout << "Centroid decomposition complete.\n";
    cout << "Centroid parent of node 2: " << cd.parentCentroid[2] << endl;
    return 0;
}
