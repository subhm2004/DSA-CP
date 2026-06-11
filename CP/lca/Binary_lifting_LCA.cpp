#include <bits/stdc++.h>
using namespace std;

class BinaryLifting {
private:
    int n, LOG;
    vector<vector<int>> up;
    vector<int> depth;
    vector<vector<int>> adj; //  adjacency list — O(n) DFS ke liye

    // ── DFS: O(n) — adjacency list se children dhundo ──────────────────────
    //   1) depth[node] = d
    //   2) up[node][0] = direct parent
    //   3) lifting table fill karo: up[node][j] = up[up[node][j-1]][j-1]
    //   4) recursively saare children pe jao
    void dfs(int node, int parent, int d) {
        depth[node] = d;
        up[node][0] = (parent == -1) ? node : parent; // root ka parent = khud

        //  lifting table yahi fill karo DFS mein
        for (int j = 1; j < LOG; j++)
            up[node][j] = up[up[node][j-1]][j-1];

        for (int child : adj[node])
            if (child != parent)
                dfs(child, node, d + 1);
    }

public:
    // ── Constructor: adjacency list banao, DFS chalao ───────────────────────
    //   parent[] array ki jagah edges[][] lo — O(n) construction
    BinaryLifting(int n, vector<vector<int>>& edges) {
        this->n = n;
        LOG = ceil(log2(n + 1)) + 1;

        up.assign(n + 1, vector<int>(LOG, 0));
        depth.assign(n + 1, 0);
        adj.assign(n + 1, {});

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        dfs(1, -1, 0); // root = 1
    }

    // ── getKthAncestor: binary lifting se K-th ancestor ─────────────────────
    //   K ke set bits ke hisaab se jump karo
    int getKthAncestor(int node, int k) {
        for (int i = 0; i < LOG; i++) {
            if (k & (1 << i)) {
                node = up[node][i];
            }
        }
        return node;
    }

    // ── getLCA: u aur v ka lowest common ancestor ────────────────────────────
    //   1) u ko v ke level pe lao
    //   2) same ho gaye? return u
    //   3) bade jumps se dono ko saath upar jab tak parent alag ho
    //   4) up[u][0] = LCA
    int getLCA(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);

        u = getKthAncestor(u, depth[u] - depth[v]);

        if (u == v) return u;

        for (int i = LOG - 1; i >= 0; i--)
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }

        return up[u][0];
    }

    int getDepth(int node) { return depth[node]; }
};

int main() {
    // edges mein convert karo (0-indexed → 1-indexed)
    //
    //         0(1)
    //       / | \
    //      1  2  3        nodes: 0..10 → labels: 1..11
    //     /|  |\
    //    4 5  6 7
    //    |   / \
    //    8  9  10

    int n = 11;
    vector<vector<int>> edges = {
        {1,2},{1,3},{1,4},   // 0 ke children: 1,2,3
        {2,5},{2,6},          // 1 ke children: 4,5
        {3,7},{3,8},          // 2 ke children: 6,7
        {5,9},                // 4 ka child: 8
        {7,10},{7,11}         // 6 ke children: 9,10
    };

    BinaryLifting bl(n, edges);

    // 1-indexed mein convert karke test karo
    cout << "2nd ancestor of 9: "  << bl.getKthAncestor(9, 2)  << endl; // exp: 2
    cout << "3rd ancestor of 10: " << bl.getKthAncestor(10, 3) << endl; // exp: 1
    cout << "1st ancestor of 11: " << bl.getKthAncestor(11, 1) << endl; // exp: 7

    cout << "LCA of 6 and 9: "  << bl.getLCA(6, 9)  << endl; // exp: 2
    cout << "LCA of 9 and 11: " << bl.getLCA(9, 11) << endl; // exp: 7
    cout << "LCA of 10 and 11: "<< bl.getLCA(10,11) << endl; // exp: 7
    cout << "LCA of 8 and 11: " << bl.getLCA(8, 11) << endl; // exp: 3
    cout << "LCA of 4 and 11: " << bl.getLCA(4, 11) << endl; // exp: 1

    return 0;
}
