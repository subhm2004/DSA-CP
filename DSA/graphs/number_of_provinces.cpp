/*
 * ============================================================================
 * TOPIC    : Graphs — Number of Provinces (Union Find)
 * FILE     : number_of_provinces.cpp
 * PROBLEM  : Connected components in adjacency matrix
 * LEETCODE : 547 — Number of Provinces
 * APPROACH : DSU — union friends in each row
 * COMPLEX  : Time: O(n^2 α(n))  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct UnionFind {
    vector<int> parent;
    UnionFind(int n) : parent(n) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) parent[b] = a;
    }
};

int findCircleNum(vector<vector<int>> &isConnected) {
    int n = isConnected.size();
    UnionFind dsu(n);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (isConnected[i][j]) dsu.unite(i, j);

    unordered_set<int> roots;
    for (int i = 0; i < n; i++) roots.insert(dsu.find(i));
    return roots.size();
}

int main() {
    vector<vector<int>> g = {{1,1,0},{1,1,0},{0,0,1}};
    cout << findCircleNum(g) << endl; // 2
    return 0;
}
