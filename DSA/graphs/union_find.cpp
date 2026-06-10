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

// ════════════════════════════════════════════════════════════════════════════
// GRAPHS — Union Find (Disjoint Set Union)
// ────────────────────────────────────────────────────────────────────────────
// Problem: Dynamic connectivity — elements ko groups me merge karo aur
//          query karo ki do elements same group me hain ya nahi.
//
// Approach: DSU with Path Compression + Union by Rank
//   - parent[i] = representative of i's set
//   - find: root dhundho, path pe sabko root se attach (compression)
//   - unite: smaller rank tree ko badi rank ke neeche merge
//   - connected: find(a) == find(b) check
//
// Complexity: Time O(α(n)) amortized per op  |  Space O(n)
// ════════════════════════════════════════════════════════════════════════════

struct UnionFind {
    vector<int> parent, rank_;

    // ── UnionFind: n disjoint sets initialize ──
    //   1) parent aur rank_ dono size n
    //   2) iota se parent[i]=i — har element apna set
    //   3) rank_ sab 0 — initially sab trees height 0
    UnionFind(int n) : parent(n), rank_(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    // ── find: element x ka set representative ──
    //   1) parent[x]==x → x root hai
    //   2) Warna parent[x] = find(parent[x]) — path compression
    //   3) Amortized nearly O(1) with compression + rank
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }

    // ── unite: sets of a and b merge karo ──
    //   1) Dono ke roots find karo
    //   2) Same root → already connected, false return
    //   3) Union by rank: chhoti rank wali tree badi ke neeche
    //   4) Equal rank pe merge ke baad rank[a]++ — tree height badh sakti hai
    //   5) Successful merge → true return
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;  // already same component
        if (rank_[a] < rank_[b]) swap(a, b);  // a = taller/equal rank tree
        parent[b] = a;  // b's tree hangs under a
        if (rank_[a] == rank_[b]) rank_[a]++;  // same height merge → height +1
        return true;
    }

    // ── connected: a aur b same set me hain? ──
    //   1) find(a) aur find(b) compare karo
    //   2) Equal roots → connected, warna nahi
    bool connected(int a, int b) { return find(a) == find(b); }
};

int main() {
    UnionFind dsu(5);
    dsu.unite(0, 1);
    dsu.unite(1, 2);
    cout << (dsu.connected(0, 2) ? "YES" : "NO") << endl;
    return 0;
}
