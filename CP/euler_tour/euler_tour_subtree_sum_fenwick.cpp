/*
 * ============================================================================
 * TOPIC    : Euler Tour + Fenwick Tree
 * FILE     : euler_tour_subtree_sum_fenwick.cpp
 * PROBLEM  : Subtree sum query and point update on tree
 * APPROACH : Euler tour flattens subtree to contiguous range in BIT
 * COMPLEX  : Query/Update O(log n)  |  DFS O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// EULER TOUR + BIT — Subtree Sum (1-indexed tin/tout)
// ────────────────────────────────────────────────────────────────────────────
// tin[u]  = DFS entry time (subtree range start)
// tout[u] = DFS exit time (subtree range end)
// Subtree of u = BIT range [tin[u], tout[u]]
// ════════════════════════════════════════════════════════════════════════════

struct BIT {
    int n;
    vector<long long> bit;
    // ── BIT: n-size ka fenwick tree initialize karo ─────────────────────────
    //   1) n store karo, bit array size n+1 (1-indexed BIT)
    //   2) sab bit[i] = 0 — abhi koi value add nahi hui
    BIT(int n) : n(n), bit(n + 1, 0) {}

    // ── add: index 'i' pe 'v' add karo ──────────────────────────────────────
    //   1) i se start karo, bit[i] += v
    //   2) i += i & -i se next responsible index pe jump (Fenwick trick)
    //   3) jab tak i <= n, repeat — O(log n) me update ho jaata hai
    void add(int i, long long v) {
        for (; i <= n; i += i & -i)
            bit[i] += v;
    }

    // ── sum: [1, i] prefix sum nikalo ────────────────────────────────────────
    //   1) s = 0, i se shuru
    //   2) s += bit[i], phir i -= i & -i (parent index)
    //   3) i > 0 tak repeat — prefix sum mil gaya
    long long sum(int i) const {
        long long s = 0;
        for (; i > 0; i -= i & -i)
            s += bit[i];
        return s;
    }

    // ── rangeSum: [l, r] ka sum nikalo ──────────────────────────────────────
    //   1) sum(r) = [1,r] ka total
    //   2) sum(l-1) subtract karo — beech ka [l,r] bach gaya
    //   3) inclusion-exclusion se range query O(log n)
    long long rangeSum(int l, int r) const {
        return sum(r) - sum(l - 1);
    }
};

class TreeEulerTour {
    vector<vector<int>> adj;
    vector<int> tin, tout;   // subtree range boundaries
    vector<long long> val;
    int timer = 0;

    // ── dfs: entry pe tin set, exit pe tout set ───────────────────────────────
    //   1) node u enter hote hi tin[u] = ++timer (subtree range start)
    //   2) har child pe dfs (parent skip — cycle na bane)
    //   3) sab children ke baad tout[u] = timer (subtree range end)
    //   4) subtree of u = euler indices [tin[u], tout[u]] — continuous range!
    void dfs(int u, int p) {
        tin[u] = ++timer;
        for (int v : adj[u]) {
            if (v == p)
                continue;
            dfs(v, u);
        }
        tout[u] = timer;
    }

public:
    // ── TreeEulerTour: n nodes ke liye adjacency + tin/tout arrays banao ────
    //   1) adj, tin, tout, val sab size n ke
    //   2) timer = 0 — build() me dfs se badhega
    TreeEulerTour(int n) : adj(n), tin(n), tout(n), val(n) {}

    // ── addEdge: undirected edge u-v add karo ───────────────────────────────
    //   1) adj[u] me v, adj[v] me u — dono taraf edge
    //   2) tree hai to ek hi connected component banega
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // ── setValue: node u ki value store karo ────────────────────────────────
    //   1) val[u] = x — baad me BIT me initial add ke liye use hoga
    void setValue(int u, long long x) { val[u] = x; }

    // ── build: root se DFS karke tin/tout bharto ────────────────────────────
    //   1) timer reset karo 0
    //   2) root se dfs chalao (parent = -1)
    //   3) ab har node ka subtree [tin, tout] range ready hai BIT ke liye
    void build(int root = 0) {
        timer = 0;
        dfs(root, -1);
    }

    // ── subtreeL: node u ke subtree ka left boundary (tin) ──────────────────
    int subtreeL(int u) const { return tin[u]; }

    // ── subtreeR: node u ke subtree ka right boundary (tout) ────────────────
    int subtreeR(int u) const { return tout[u]; }

    // ── nodeVal: node u ki stored value return karo ───────────────────────────
    long long nodeVal(int u) const { return val[u]; }
};

int main() {
    int n = 5;
    TreeEulerTour tree(n);
    tree.setValue(0, 10);
    tree.setValue(1, 2);
    tree.setValue(2, 5);
    tree.setValue(3, 8);
    tree.setValue(4, 1);

    tree.addEdge(0, 1);
    tree.addEdge(0, 2);
    tree.addEdge(1, 3);
    tree.addEdge(1, 4);
    tree.build(0);

    BIT bit(n);
    for (int u = 0; u < n; u++)
        bit.add(tree.subtreeL(u), tree.nodeVal(u));

    cout << "Subtree sum at node 1 = "
         << bit.rangeSum(tree.subtreeL(1), tree.subtreeR(1)) << endl;

    bit.add(tree.subtreeL(3), 5);
    cout << "After +5 at node 3, subtree sum at 1 = "
         << bit.rangeSum(tree.subtreeL(1), tree.subtreeR(1)) << endl;
    return 0;
}
