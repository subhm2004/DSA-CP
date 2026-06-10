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

// ════════════════════════════════════════════════════════════════════════════
// LEETCODE 547 — Number of Provinces
// ────────────────────────────────────────────────────────────────────────────
// Problem: n cities hain, isConnected[i][j]=1 matlab directly connected.
//          Transitively connected cities ek province — total provinces count karo.
//
// Approach: Union-Find (DSU) with path compression
//   - Matrix scan karo — isConnected[i][j]==1 pe i aur j ko unite karo
//   - Har city ka root find karo, unique roots = number of provinces
//   - Province = connected component in undirected graph
//
// Complexity: Time O(n² α(n))  |  Space O(n) for parent array
// ════════════════════════════════════════════════════════════════════════════

struct UnionFind {
    vector<int> parent;

    // ── UnionFind: n elements, har ek apna parent ──
    //   1) parent vector size n allocate karo
    //   2) iota se parent[i] = i initialize — sab alag sets
    UnionFind(int n) : parent(n) { iota(parent.begin(), parent.end(), 0); }

    // ── find: element ka representative root dhundho ──
    //   1) Agar parent[x] == x to x hi root hai
    //   2) Warna recursively parent[x] = find(parent[x]) — path compression
    //   3) Compressed root return karo — future finds fast
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }

    // ── unite: do sets ko merge karo ──
    //   1) Dono elements ke actual roots find karo
    //   2) Alag roots hain to ek ka parent doosre root banao
    //   3) Same root pe kuch nahi — already connected
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) parent[b] = a;  // b ke set ko a ke under merge
    }
};

// ── findCircleNum: provinces (connected components) count karo ──
//   1) n cities, DSU(n) banao
//   2) Upper triangle scan — isConnected[i][j]==1 pe unite(i,j)
//   3) Har city i ka root find karke set me daalo
//   4) Unique roots ki count = number of provinces
int findCircleNum(vector<vector<int>> &isConnected) {
    int n = isConnected.size();
    UnionFind dsu(n);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (isConnected[i][j]) dsu.unite(i, j);  // direct edge — same province

    unordered_set<int> roots;
    for (int i = 0; i < n; i++) roots.insert(dsu.find(i));  // har component ka ek root
    return roots.size();
}

int main() {
    vector<vector<int>> g = {{1,1,0},{1,1,0},{0,0,1}};
    cout << findCircleNum(g) << endl; // 2
    return 0;
}
