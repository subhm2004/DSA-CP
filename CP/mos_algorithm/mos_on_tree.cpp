/*
 * ============================================================================
 * TOPIC    : Mo's Algorithm on Tree
 * FILE     : mos_on_tree.cpp
 * PROBLEM  : Offline subtree/path frequency queries on tree
 * APPROACH : Euler tour flatten + Mo's with block sorting
 * COMPLEX  : O((n + q) * sqrt(n))
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// MO'S ALGORITHM ON TREE — Subtree Distinct Count
// ────────────────────────────────────────────────────────────────────────────
// Idea:
//   1) Tree ko Euler tour se flat array me badal do.
//      Node u ka poora subtree = euler array me range [first[u], last[u]]
//   2) Ab har subtree query ek normal range query ban gayi -> Mo's algorithm lagao.
//
// Mo's ke core pointers:
//   curL, curR -> abhi current range [curL, curR] euler array me cover ho rahi hai
//   blockSize  -> sqrt(n) blocks, queries ko is order me sort karte hain taaki
//                 pointers zyada idhar-udhar na jayein (amortized fast)
// ════════════════════════════════════════════════════════════════════════════

struct MoOnTree {
    int n, timer = 0, blockSize;
    vector<vector<int>> adj;
    vector<int> euler;              // DFS order me nodes ki list
    vector<int> first, last;        // node u ka subtree range [first[u], last[u]]
    vector<int> depth, parent, value;
    vector<int> freq;               // current range me har value ki kitni baar aayi
    long long curAns = 0;           // current range me kitne DISTINCT values hain

    // ── MoOnTree: n nodes ka empty tree graph initialize karo ──
    //   1) n nodes ke liye adjacency list, first/last, depth, parent, value vectors banao
    //   2) parent sab -1 se init — root ka koi parent nahi
    //   3) timer=0, curAns=0 — euler tour aur Mo window abhi shuru nahi hui
    //   4) edges aur values baad me addEdge() / direct assignment se set honge
    MoOnTree(int n) : n(n), adj(n), first(n), last(n), depth(n), parent(n, -1), value(n) {}

    // ── addEdge: undirected edge u-v tree me add karo ──
    //   1) adj[u] me v push karo aur adj[v] me u push karo
    //   2) undirected edge hai — dono taraf neighbor list update
    //   3) tree hai to edges n-1 hongi; DFS is adj list se traverse karega
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // ── dfs: Euler tour timestamps bharto — subtree ko flat range banao ──
    //   1) node u visit hote hi first[u] = timer set karo aur euler[timer] = u push karo
    //   2) timer++ — har visit ek euler array index occupy karta hai
    //   3) har child v (parent p ko skip) ke liye depth/parent set karke recurse karo
    //   4) saare children ke baad last[u] = timer-1 — u ka subtree euler me [first[u], last[u]] hai
    void dfs(int u, int p) {
        first[u] = timer;
        euler.push_back(u);
        timer++;
        for (int v : adj[u]) {
            if (v == p) continue;  // parent edge skip — tree me cycle nahi
            depth[v] = depth[u] + 1;
            parent[v] = u;
            dfs(v, u);
        }
        last[u] = timer - 1;  // subtree ka last euler index — continuous range ban gaya
    }

    struct Query {
        int l, r, idx;  // euler range [l,r] + original query index
    };

    // ── addRemove: Mo window me ek euler position add/remove karo ──
    //   1) euler[pos] se actual tree node nikalo (parameter 'node' yahan node id hai)
    //   2) us node ki value = value[node] lo aur freq array update karo
    //   3) add=true: freq badhao; agar 0->1 gayi to curAns++ (naya distinct value)
    //   4) add=false: freq ghatao; agar 1->0 gayi to curAns-- (value range se gayi)
    void addRemove(int node, vector<long long> &answers, const vector<Query> &queries, int qidx, bool add) {
        int v = value[node];
        if (add) {
            if (freq[v] == 0) curAns++;  // pehli baar is value ki freq — distinct count badha
            freq[v]++;
        } else {
            freq[v]--;
            if (freq[v] == 0) curAns--;  // value poori tarah range se chali gayi
        }
    }

    // ── subtreeQueries: saari subtree queries offline Mo's se answer karo ──
    //   1) blockSize = sqrt(n) set karo aur root se DFS karke euler tour banao
    //   2) har subtree query (node u) ko euler range [first[u], last[u]] me convert karo
    //   3) queries ko Mo's block order me sort karo (block on l, odd-even r trick)
    //   4) curL/curR pointers se range expand/shrink karo — har step pe addRemove call
    //   5) range match hone par ans[q.idx] = curAns store karo
    vector<long long> subtreeQueries(const vector<pair<int, int>> &queriesIn) {
        blockSize = max(1, (int)sqrt(n));
        dfs(0, -1);  // node 0 root maan ke euler tour start

        int maxVal = *max_element(value.begin(), value.end());
        freq.assign(maxVal + 1, 0);

        vector<Query> qs;
        for (int i = 0; i < (int)queriesIn.size(); i++) {
            int u = queriesIn[i].first;
            // subtree of u = euler array me continuous range [first[u], last[u]]
            qs.push_back({first[u], last[u], i});
        }

        // Mo's sorting: pehle block (l/blockSize), phir odd-even r optimization
        sort(qs.begin(), qs.end(), [&](const Query &a, const Query &b) {
            int ba = a.l / blockSize, bb = b.l / blockSize;
            if (ba != bb) return ba < bb;
            // odd block -> r descending, even block -> r ascending (zig-zag)
            return (ba & 1) ? a.r > b.r : a.r < b.r;
        });

        vector<long long> ans(queriesIn.size());
        int curL = 0, curR = -1;  // shuru me empty Mo window
        curAns = 0;

        // lambdas: euler[pos] node ko Mo window me add/remove karte hain
        auto expand = [&](int pos) { addRemove(euler[pos], ans, qs, 0, true); };
        auto shrink = [&](int pos) { addRemove(euler[pos], ans, qs, 0, false); };

        for (auto &q : qs) {
            // Mo's pointer movement: pehle expand (add), phir shrink (remove)
            while (curL > q.l) expand(--curL);   // left expand — euler index kam
            while (curR < q.r) expand(++curR);   // right expand — euler index badhao
            while (curL < q.l) shrink(curL++);   // left shrink — extra left nodes hatao
            while (curR > q.r) shrink(curR--);   // right shrink — extra right nodes hatao
            ans[q.idx] = curAns;
        }
        return ans;
    }
};

// ── main: sample tree pe teen subtree distinct-count queries chalao ──
//   1) 5-node tree banao, values assign karo, edges add karo
//   2) subtree queries for nodes 0, 1, 2 run karo
//   3) har subtree ka distinct value count print karo
int main() {
    // Tree: 0-1-3, 0-2-4
    MoOnTree mo(5);
    mo.value = {1, 2, 2, 3, 3};
    mo.addEdge(0, 1);
    mo.addEdge(0, 2);
    mo.addEdge(1, 3);
    mo.addEdge(2, 4);

    auto ans = mo.subtreeQueries({{0, 0}, {1, 0}, {2, 0}});
    cout << "Distinct in subtree(0) = " << ans[0] << endl;
    cout << "Distinct in subtree(1) = " << ans[1] << endl;
    cout << "Distinct in subtree(2) = " << ans[2] << endl;
    return 0;
}
