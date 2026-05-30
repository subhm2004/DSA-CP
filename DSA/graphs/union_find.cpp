/*
 * ============================================================================
 * TOPIC    : Graphs — Union Find (DSU)
 * FILE     : union_find.cpp
 * PROBLEM  : Disjoint set union with path compression + rank
 * LEETCODE : 684 — Redundant Connection (pattern)
 * APPROACH : find with path compression; union by rank
 * COMPLEX  : Time: O(α(n)) amortized  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct UnionFind {
    vector<int> parent, rank_;

    UnionFind(int n) : parent(n), rank_(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (rank_[a] < rank_[b]) swap(a, b);
        parent[b] = a;
        if (rank_[a] == rank_[b]) rank_[a]++;
        return true;
    }

    bool connected(int a, int b) { return find(a) == find(b); }
};

int main() {
    UnionFind dsu(5);
    dsu.unite(0, 1);
    dsu.unite(1, 2);
    cout << (dsu.connected(0, 2) ? "YES" : "NO") << endl;
    return 0;
}
