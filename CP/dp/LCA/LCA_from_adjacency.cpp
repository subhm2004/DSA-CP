#include <bits/stdc++.h>
using namespace std;

/*
 * CP mein tree aksar edges ki form mein aata hai:
 *   vector<vector<int>> edges = {{1,2}, {1,3}, {2,4}, ...};
 *
 * Yahan directly edges se adjacency list banao, DFS se up[][] table bharo,
 * phir LCA + Kth Ancestor query karo.
 *
 * Note: 1-indexed nodes (root = 1), root ka parent = -1 (koi parent nahi).
 */

class BinaryLifting {
private:
    int n, LOG;
    vector<vector<int>> up;
    vector<int> depth;
    unordered_map<int, list<int>> adjList;

    /*
     * dfs(node, parent, d)
     * Har node par depth set karo, up[node][0] = parent,
     * aur DFS ke dauran hi poora up table bhar do.
     */
    void dfs(int node, int parent, int d) {
        depth[node] = d;
        up[node][0] = parent;

        for (int j = 1; j < LOG; ++j) {
            if (up[node][j - 1] != -1) {
                up[node][j] = up[up[node][j - 1]][j - 1];
            } else {
                up[node][j] = -1;
            }
        }

        for (int child : adjList[node]) {
            if (child != parent) {
                dfs(child, node, d + 1);
            }
        }
    }

public:
    /*
     * Constructor: n nodes, edges se tree build karo
     * root = 1, up[1][0] = -1 (root ka koi parent nahi)
     */
    BinaryLifting(int n, vector<vector<int>>& edges) {
        this->n = n;
        LOG = ceil(log2(n + 1)) + 1;
        up.assign(n + 1, vector<int>(LOG, -1));
        depth.assign(n + 1, 0);

        for (auto& e : edges) {
            adjList[e[0]].push_back(e[1]);
            adjList[e[1]].push_back(e[0]);
        }

        dfs(1, -1, 0);
    }

    /*
     * get_Kth_Ancestor(node, k)
     * -------------------------
     * "node" se exactly k edges UPAR wala ancestor return karta hai.
     * Agar k zyada ho (root se bahar jaana pade) to -1 return.
     *
     * Pehle se table bana hai:
     *   up[node][0] = direct parent (1 step)
     *   up[node][1] = 2 steps upar wala ancestor  (2^1 = 2)
     *   up[node][2] = 4 steps upar wala ancestor  (2^2 = 4)
     *   up[node][i] = 2^i steps upar wala ancestor
     *
     * Trick — k ko binary mein todo:
     *   k = 13  ->  binary 1101  ->  8 + 4 + 0 + 1
     *   Matlab: 8 step jump + 4 step jump + 1 step jump
     *
     *   i=0: k & 1   -> 1 step   -> up[node][0]
     *   i=1: k & 2   -> 2 steps  -> up[node][1]
     *   i=2: k & 4   -> 4 steps  -> up[node][2]
     *   i=3: k & 8   -> 8 steps  -> up[node][3]
     *
     * Example (Tree 1):
     *         1          depth: 1->0, 2->1, 3->1, 4->2, 5->2
     *        / \
     *       2   3
     *      / \
     *     4   5
     *
     *   get_Kth_Ancestor(4, 1):
     *     k=1, bit 0 set -> node = up[4][0] = 2  (parent of 4)
     *
     *   get_Kth_Ancestor(4, 2):
     *     k=2, bit 1 set -> node = up[4][1] = up[up[4][0]][0] = up[2][0] = 1
     *
     *   get_Kth_Ancestor(4, 3):
     *     k=3 = 11 binary -> 1 step + 2 steps -> root ke upar -1 -> return -1
     *
     * Time: O(LOG) = O(log n)
     */
    int get_Kth_Ancestor(int node, int k) {
        for (int i = 0; i < LOG; ++i) {
            if (k & (1 << i)) {              // k ka i-th bit check — 2^i jump chahiye?
                node = up[node][i];          // 2^i steps ek saath upar jump
                if (node == -1) {            // root(1) ka parent -1 hai, aage nahi
                    return -1;
                }
            }
        }
        return node;
    }

    /*
     * get_LCA(u, v)
     * -------------
     * LCA = Lowest Common Ancestor
     * Dono nodes u aur v ka sabse NEECHE wala common ancestor.
     * (sabse deep node jo dono ka ancestor ho)
     *
     * ── STEP 1: Depth equalize karo ──
     *   Jo node zyada neeche hai (zyada depth), use upar uthao.
     *   swap se u hamesha neeche wala ya equal depth wala rehta hai.
     *
     *   Example: LCA(4, 3) in Tree 1
     *     depth[4]=2, depth[3]=1  ->  swap nahi, u=4
     *     u = get_Kth_Ancestor(4, 2-1) = get_Kth_Ancestor(4, 1) = 2
     *     ab u=2, v=3 dono depth=1 par
     *
     * ── STEP 2: Kya dono same node hain? ──
     *   Agar haan, matlab ek dusre ka ancestor tha — wahi LCA hai.
     *
     *   Example: LCA(4, 2) — 4 ko 1 step upar lao -> u=2, v=2 -> return 2
     *
     * ── STEP 3: Binary lifting se saath-saath upar chalo ──
     *   Sabse BADA jump (2^(LOG-1)) se shuru, chhote tak aao.
     *   Sirf tab jump karo jab up[u][i] != up[v][i]
     *   (matlab abhi LCA cross nahi hua — dono alag subtrees mein hain)
     *
     *   Loop ke baad u aur v, LCA ke TURANT neeche wale children honge
     *   (siblings jaisa — same parent, alag node).
     *
     *   Example: LCA(4, 3) after step 1: u=2, v=3
     *     up[2][1] vs up[3][1] — alag hain, jump karo
     *     up[2][0] vs up[3][0] — dono = 1, jump MAT karo (LCA cross ho jayega)
     *     loop khatam -> u=2, v=3
     *
     * ── STEP 4: LCA = dono ka direct parent ──
     *   return up[u][0]  ->  up[2][0] = 1
     *
     *   LCA(4, 3) = 1  ✓
     *
     * Visual (Tree 1):
     *         1       LCA(4,3)=1,  LCA(2,3)=1
     *        / \
     *       2   3     LCA(4,5)=2
     *      / \
     *     4   5
     *
     * Time: O(LOG) = O(log n)
     */
    int get_LCA(int u, int v) {
        // Step 1: u ko neeche wale node par lao (zyada depth wala)
        if (depth[u] < depth[v]) {
            swap(u, v);
        }

        // u ko utna upar uthao jitna v neeche hai — ab same level
        u = get_Kth_Ancestor(u, depth[u] - depth[v]);

        // Step 2: ek dusre ka ancestor hai to wahi LCA
        if (u == v) {
            return u;
        }

        // Step 3: bade jump se chhote tak — LCA ke just neeche ruk jao
        for (int i = LOG - 1; i >= 0; --i) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }

        // Step 4: ab u aur v ke parent = LCA
        return up[u][0];
    }

    int get_Depth(int node) {
        return depth[node];
    }
};

void solveTree(int treeNum, int n, vector<vector<int>>& edges,
               vector<pair<int, int>>& lcaQ, vector<pair<int, int>>& kthQ) {
    cout << "\n===== Tree " << treeNum << " (Edges se build) =====\n";

    BinaryLifting bl(n, edges);

    cout << "Edges: ";
    for (auto& e : edges) {
        cout << "(" << e[0] << "," << e[1] << ") ";
    }
    cout << "\n";

    cout << "\n-- LCA Queries --\n";
    for (auto& [u, v] : lcaQ) {
        cout << "LCA(" << u << ", " << v << ") = " << bl.get_LCA(u, v) << "\n";
    }

    cout << "\n-- Kth Ancestor Queries --\n";
    for (auto& [node, k] : kthQ) {
        cout << "get_Kth_Ancestor(" << node << ", " << k << ") = "
             << bl.get_Kth_Ancestor(node, k) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // -------------------------------------------------------
    // Tree 1: Simple binary tree (1-indexed)
    //         1
    //        / \
    //       2   3
    //      / \
    //     4   5
    // -------------------------------------------------------
    {
        int n = 5;
        vector<vector<int>> edges = {{1, 2}, {1, 3}, {2, 4}, {2, 5}};
        vector<pair<int, int>> lcaQ = {{4, 5}, {4, 3}, {2, 3}};
        vector<pair<int, int>> kthQ = {{4, 1}, {4, 2}, {5, 1}};
        solveTree(1, n, edges, lcaQ, kthQ);
    }

    // -------------------------------------------------------
    // Tree 2: Linear chain
    //    1 - 2 - 3 - 4 - 5 - 6
    // -------------------------------------------------------
    {
        int n = 6;
        vector<vector<int>> edges = {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}};
        vector<pair<int, int>> lcaQ = {{6, 4}, {5, 3}, {6, 2}};
        vector<pair<int, int>> kthQ = {{6, 2}, {6, 5}, {4, 1}};
        solveTree(2, n, edges, lcaQ, kthQ);
    }

    // -------------------------------------------------------
    // Tree 3: Wide tree
    //            1
    //          / | \ \
    //         2  3  4  5
    //        /\     \
    //       6  7     8
    //      /
    //     9
    // -------------------------------------------------------
    {
        int n = 9;
        vector<vector<int>> edges = {
            {1, 2}, {1, 3}, {1, 4}, {1, 5},
            {2, 6}, {2, 7}, {4, 8}, {6, 9}
        };
        vector<pair<int, int>> lcaQ = {{9, 8}, {7, 8}, {9, 3}, {6, 5}};
        vector<pair<int, int>> kthQ = {{9, 1}, {9, 3}, {8, 2}};
        solveTree(3, n, edges, lcaQ, kthQ);
    }

    return 0;
}
