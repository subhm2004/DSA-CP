// ════════════════════════════════════════════════════════════════════════════
// CENTROID DECOMPOSITION — Tree ko centroid layers me tod do
// ────────────────────────────────────────────────────────────────────────────
// Centroid = aisa node jiska koi bhi subtree size <= n/2 ho.
// Idea: centroid "hata do" (dead mark), har bache hue component me recurse.
//
// Use cases: tree pe distance queries, path counting, "colors on tree" etc.
// Build time: O(n log n) — har level pe at most n/2 size ka component
//
// cdTree = optional centroid tree (parent centroid se connect)
// ════════════════════════════════════════════════════════════════════════════

#include <bits/stdc++.h>
using namespace std;

struct CentroidDecomposition {
    int n;
    vector<vector<int>> adj;
    vector<int> sz, dead;
    vector<vector<int>> cdTree;
    vector<int> parentCentroid;

    CentroidDecomposition(int n) : n(n), adj(n), sz(n), dead(n), cdTree(n), parentCentroid(n, -1) {}

    // ── addEdge: undirected tree edge ──────────────────────────────────────
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // ── getSize: subtree size compute (dead nodes skip) ────────────────────
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

    // ── getCentroid: tree ka centroid dhundo (heavy child avoid karke) ─────
    // Agar kisi child ka sz > treeSize/2, wahan recurse karo
    int getCentroid(int v, int p, int treeSize) {
        // Step 1: agar koi child ka subtree > treeSize/2, wahan recurse karo
        // Centroid wahi node hai jiska koi bhi child subtree half se chhota ho
        for (int u : adj[v]) {
            if (u == p || dead[u])
                continue;
            if (sz[u] > treeSize / 2)
                return getCentroid(u, v, treeSize);
        }
        return v;
    }

    // ── decompose: centroid mark dead, subtrees pe recurse ────────────────
    void decompose(int entry, int pCentroid = -1) {
        // Step 1: current component ka size aur centroid nikalo
        int treeSize = getSize(entry, -1);
        int c = getCentroid(entry, -1, treeSize);
        // Step 2: centroid ko dead mark karo, parent centroid tree me jod do
        dead[c] = 1;
        parentCentroid[c] = pCentroid;

        if (pCentroid != -1) {
            cdTree[pCentroid].push_back(c);
            cdTree[c].push_back(pCentroid);
        }

        // Step 3: har alive subtree me alag se recurse karo
        for (int u : adj[c]) {
            if (!dead[u])
                decompose(u, c);
        }
    }

    // ── countWithinK: example stub — distance K ke andar nodes count ───────
    // Full solution me har centroid se distances precompute karte hain
    int countWithinK(int start, int k, int c, int distFromCentroid) {
        if (distFromCentroid > k)
            return 0;
        int res = 1;
        for (int childCentroid : cdTree[c]) {
            if (childCentroid == parentCentroid[c])
                continue;
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
