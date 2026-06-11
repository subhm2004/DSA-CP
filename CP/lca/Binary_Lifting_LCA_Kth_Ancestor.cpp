#include <bits/stdc++.h>
using namespace std;

class BinaryLifting {
private:
    int n;
    int LOG;
    vector<vector<int>> up;  // up[node][j] = 2^j-th ancestor of node
    vector<int> depth;       // depth[node] = tree mein depth (root = 0)

    /*
     * DFS se depth array fill karte hain.
     * parent[root] = -1 hona chahiye.
     */
    void computeDepths(int node, int par, const vector<vector<int>>& adj) {
        for (int child : adj[node]) {
            if (child == par) continue;
            depth[child] = depth[node] + 1;
            computeDepths(child, node, adj);
        }
    }

public:
    /*
     * Constructor — do cheezein accept karta hai:
     *   1. parent[] array: parent[i] = i ka direct parent (-1 for root)
     *   2. root: tree ka root node
     *
     * Andar kya hota hai:
     *   - up[i][0] = parent[i]  (2^0 = 1 step upar)
     *   - up[i][j] = up[ up[i][j-1] ][j-1]
     *     Matlab: 2^j steps = pehle 2^(j-1) steps, phir aur 2^(j-1) steps
     */
    BinaryLifting(int n, const vector<int>& parent, int root = 0) {
        this->n = n;
        LOG = 1;
        while ((1 << LOG) <= n) LOG++;  // LOG = ceil(log2(n)) + 1

        up.assign(n, vector<int>(LOG, -1));
        depth.assign(n, 0);

        // Adjacency list banao parent[] se
        vector<vector<int>> adj(n);
        for (int i = 0; i < n; i++) {
            if (parent[i] != -1) {
                adj[i].push_back(parent[i]);
                adj[parent[i]].push_back(i);
            }
        }

        // Depth compute karo DFS se
        computeDepths(root, -1, adj);

        // 2^0-th ancestor = direct parent
        for (int i = 0; i < n; i++) {
            up[i][0] = parent[i];  // -1 if root
        }

        // 2^j-th ancestor fill karo (DP over ancestors)
        // up[i][j] = up[ up[i][j-1] ][j-1]
        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i < n; i++) {
                int mid = up[i][j - 1];  // 2^(j-1) steps upar
                if (mid != -1)
                    up[i][j] = up[mid][j - 1];  // aur 2^(j-1) steps upar
                // agar mid = -1, toh up[i][j] = -1 (root ke upar kuch nahi)
            }
        }
    }

    /*
     * getKthAncestor(node, k):
     *   k ko binary mein decompose karo.
     *   Jis bit j set hai, wahan 2^j steps jump karo.
     *   Example: k=5 = 101 binary → jump 4 steps, phir 1 step
     */
    int getKthAncestor(int node, int k) {
        for (int j = 0; j < LOG; j++) {
            if (k & (1 << j)) {          // j-th bit set hai k mein?
                node = up[node][j];      // 2^j steps jump karo
                if (node == -1) return -1; // root se bahar gaye
            }
        }
        return node;
    }

    /*
     * LCA(u, v) — Lowest Common Ancestor
     *
     * Algorithm 3 steps mein:
     *
     * Step 1: Ensure u deeper hai (swap if needed)
     *
     * Step 2: u ko v ke saath same depth pe lao
     *   diff = depth[u] - depth[v]
     *   u = getKthAncestor(u, diff)
     *
     * Step 3: Dono ko saath upar uthao jab tak same node na ho
     *   Sabse bade j se shuru karo (greedy — zyada steps pehle)
     *   Jab up[u][j] != up[v][j] → dono jump karo
     *   End mein up[u][0] = LCA
     */
    int lca(int u, int v) {
        // Step 1: u ko deeper banana (agar u shallower hai toh swap)
        if (depth[u] < depth[v]) swap(u, v);

        // Step 2: u ko v ki depth pe lao
        int diff = depth[u] - depth[v];
        u = getKthAncestor(u, diff);

        // Edge case: agar same node aa gaye toh yahi LCA hai
        if (u == v) return u;

        // Step 3: Dono ko saath upar uthao
        // Sabse bade j se shuru karo (LOG-1 se 0 tak)
        for (int j = LOG - 1; j >= 0; j--) {
            // Agar 2^j steps upar alag ancestor hai, toh jump karo
            // Agar same ancestor hai, mat karo (ho sakta hai LCA hi ho)
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }

        // Ab u aur v ke direct parents = LCA
        return up[u][0];
    }

    // Helper: depth return karo kisi node ki
    int getDepth(int node) {
        return depth[node];
    }
};

// ==================== Main ====================

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    /*
     * Example tree:
     *         1
     *       /   \
     *      2     3
     *     / \   / \
     *    4   5 6   7
     *   / \
     *  8   9
     *
     * 0-indexed: node 0 = root
     * parent[] = {-1, 0, 0, 1, 1, 2, 2, 3, 3}
     *             0   1  2  3  4  5  6  7  8
     */
    int n = 9;
    vector<int> parent = {-1, 0, 0, 1, 1, 2, 2, 3, 3};

    BinaryLifting bl(n, parent, 0);

    // LCA queries
    cout << "LCA(4, 5) = " << bl.lca(4, 5) << "\n";  // Expected: 1
    cout << "LCA(5, 6) = " << bl.lca(5, 6) << "\n";  // Expected: 0
    cout << "LCA(7, 8) = " << bl.lca(7, 8) << "\n";  // Expected: 3
    cout << "LCA(4, 2) = " << bl.lca(4, 2) << "\n";  // Expected: 1

    // kth Ancestor
    cout << "3rd ancestor of node 8 = " << bl.getKthAncestor(8, 3) << "\n"; // Expected: 0

    return 0;
}
