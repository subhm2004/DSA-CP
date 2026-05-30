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

struct BIT {
    int n;
    vector<long long> bit;
    BIT(int n) : n(n), bit(n + 1, 0) {}

    void add(int i, long long v) {
        for (; i <= n; i += i & -i)
            bit[i] += v;
    }

    long long sum(int i) const {
        long long s = 0;
        for (; i > 0; i -= i & -i)
            s += bit[i];
        return s;
    }

    long long rangeSum(int l, int r) const {
        return sum(r) - sum(l - 1);
    }
};

class TreeEulerTour {
    vector<vector<int>> adj;
    vector<int> tin, tout;
    vector<long long> val;
    int timer = 0;

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
    TreeEulerTour(int n) : adj(n), tin(n), tout(n), val(n) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void setValue(int u, long long x) { val[u] = x; }

    void build(int root = 0) {
        timer = 0;
        dfs(root, -1);
    }

    int subtreeL(int u) const { return tin[u]; }
    int subtreeR(int u) const { return tout[u]; }
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

    bit.add(tree.subtreeL(3), 5); // add 5 to node 3
    cout << "After +5 at node 3, subtree sum at 1 = "
         << bit.rangeSum(tree.subtreeL(1), tree.subtreeR(1)) << endl;
    return 0;
}
