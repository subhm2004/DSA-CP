#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * TREE REROOTING DP — Master Template (2-Pass)
 * ════════════════════════════════════════════════════════════════════════════
 *
 * PROBLEM TYPE:
 *   Tree diya hai. Har node ko ROOT maan kar kuch answer chahiye.
 *   Example: har node se baaki sab nodes ki total distance?
 *
 * NAIVE: har node se DFS → O(n²) — n nodes × O(n) each
 * REROOTING: 2 pass DFS → O(n) total
 *
 * ────────────────────────────────────────────────────────────────────────────
 * CORE IDEA (2 passes)
 * ────────────────────────────────────────────────────────────────────────────
 *
 * PASS 1 — dfsDown (root = 0 fixed):
 *   down[u] = answer jab sirf u ke SUBTREE ko dekho (parent ignore)
 *   sz[u]   = subtree size
 *
 *   Merge rule problem pe depend karta hai.
 *   Sum of distances example:
 *     down[u] += down[v] + sz[v]   (child v ke sab nodes ek edge door)
 *
 * PASS 2 — dfsReroot (parent se child ko root shift):
 *   ans[root] = down[root]  (poora tree = root ka subtree)
 *   jab u → child v pe root shift:
 *     ans[v] = ans[u] - sz[v] + (n - sz[v])
 *
 *   Intuition:
 *     v ke subtree wale nodes pehle 1 step CLOSE the (u root se)
 *     baaki (n - sz[v]) nodes 1 step FAR ho gaye
 *
 * ────────────────────────────────────────────────────────────────────────────
 * Kab use karo:
 *   "Har node as root" / "reroot" / "sum of distances from each node"
 *   "Answer for every rooting" tree DP problems
 *
 * Time: O(n)  |  Space: O(n)
 * ════════════════════════════════════════════════════════════════════════════
 */

class TreeRerooting {
private:
    int n;
    vector<vector<int>> adj;
    vector<int> sz;          // subtree size
    vector<long long> down;  // pass 1: subtree contribution
    vector<long long> ans;   // final answer for each node as root

    /*
     * dfsDown(u, parent)
     * -----------------
     * Post-order: pehle children, phir u combine.
     * down[u] = u se apne subtree ke har node tak distance ka sum.
     */
    void dfsDown(int u, int parent) {
        sz[u] = 1;
        down[u] = 0;

        for (int v : adj[u]) {
            if (v == parent) continue;
            dfsDown(v, u);
            sz[u] += sz[v];
            down[u] += down[v] + sz[v];  // child subtree nodes ek edge door
        }
    }

    /*
     * dfsReroot(u, parent)
     * --------------------
     * Pre-order: parent ka answer se children ka answer derive.
     *
     * u se v pe root shift:
     *   ans[v] = ans[u] - sz[v] + (n - sz[v])
     *            ↑ lose    ↑ gain
     *   (v subtree wale close, baaki far)
     */
    void dfsReroot(int u, int parent) {
        for (int v : adj[u]) {
            if (v == parent) continue;
            ans[v] = ans[u] - sz[v] + (n - sz[v]);
            dfsReroot(v, u);
        }
    }

public:
    TreeRerooting(int n_, const vector<vector<int>>& edges) : n(n_) {
        adj.assign(n, {});
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        sz.assign(n, 0);
        down.assign(n, 0);
        ans.assign(n, 0);
    }

    /*
     * sumOfDistancesFromAllNodes()
     * ----------------------------
     * Return vector ans where ans[i] = sum of distances from node i
     * to every other node in tree.
     */
    vector<long long> sumOfDistancesFromAllNodes(int root = 0) {
        dfsDown(root, -1);
        ans[root] = down[root];
        dfsReroot(root, -1);
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Tree: 0-1-2-3 chain + 1-4 branch
    //       0
    //       |
    //       1
    //      / \
    //     2   4
    //     |
    //     3
    int n = 5;
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 3}, {1, 4}};

    TreeRerooting tr(n, edges);
    vector<long long> dist = tr.sumOfDistancesFromAllNodes(0);

    cout << "Sum of distances from each node (rerooting O(n)):\n";
    for (int i = 0; i < n; ++i)
        cout << "  node " << i << " -> " << dist[i] << "\n";

    return 0;
}
