#include <bits/stdc++.h>
using namespace std;

/*
 * Binary Lifting se tree par do cheezein fast milti hain:
 *   1. Kth ancestor  -> O(log n)
 *   2. LCA (Lowest Common Ancestor) -> O(log n)
 *
 * Idea: Har node ke liye precompute karo ki "2^j steps upar jaoge to kaunsa node milega"
 * Example: up[5][2] = node 5 se 2^2 = 4 level upar wala ancestor
 */

class BinaryLifting {
private:
    int n;                      // tree mein total kitne nodes hain
    int LOG;                    // kitne binary powers store karni hain (ceil(log2(n)) + 1)
    vector<vector<int>> up;     // up[node][j] = node se 2^j steps upar wala ancestor
    vector<int> depth;          // depth[i] = root (node 0) se node i tak kitne edges hain

    /*
     * computeDepth(parent)
     * --------------------
     * Har node ki depth (root se distance) nikalta hai.
     *
     * parent[i] = node i ka direct parent
     * depth[0] = 0  (root ki depth 0 hoti hai)
     * depth[i] = depth[parent[i]] + 1
     *
     * Note: Ye loop tabhi sahi kaam karta hai jab parent array
     *       topological order mein ho — matlab har child ka index
     *       apne parent se bada ho (jaise BFS/DFS se banaya ho).
     *
     * Time: O(n)
     */
    void computeDepth(const vector<int>& parent) {
        depth[0] = 0;
        for (int i = 1; i < n; ++i) {
            depth[i] = depth[parent[i]] + 1;
        }
    }

public:
    /*
     * BinaryLifting(n, parent) — Constructor / Preprocessing
     * ------------------------------------------------------
     * Poora binary lifting table build karta hai.
     *
     * Step 1: LOG set karo
     *   LOG = ceil(log2(n+1)) + 1
     *   Kyunki maximum 2^(LOG-1) steps cover karne padenge
     *
     * Step 2: up table initialize
     *   up[i][0] = parent[i]   (1 step = direct parent)
     *   Root ka parent -1 hota hai (koi ancestor nahi)
     *
     * Step 3: Depth compute karo (LCA ke liye zaroori)
     *
     * Step 4: DP se poora table bharo
     *   up[i][j] = up[ up[i][j-1] ][j-1]
     *
     *   Matlab: 2^j steps upar jaane ke liye pehle 2^(j-1) upar jao,
     *   phir wahan se aur 2^(j-1) upar jao.
     *
     *   Example: up[7][2] (4 steps upar)
     *     = up[ up[7][1] ][1]     // pehle 2 upar, phir wahan se 2 aur upar
     *
     * Time:  O(n * LOG)  ≈ O(n log n)
     * Space: O(n * LOG)
     */
    BinaryLifting(int n, const vector<int>& parent) {
        this->n = n;
        LOG = ceil(log2(n + 1)) + 1;
        up.assign(n, vector<int>(LOG, -1));
        depth.assign(n, 0);

        // Step 2: Base case — 2^0 = 1 step = direct parent
        for (int i = 0; i < n; ++i) {
            up[i][0] = parent[i];
        }

        // Step 3: Depth compute
        computeDepth(parent);

        // Step 4: DP — 2^j ancestor = 2^(j-1) ancestor ka 2^(j-1) ancestor
        for (int j = 1; j < LOG; ++j) {
            for (int i = 0; i < n; ++i) {
                if (up[i][j - 1] != -1) {
                    up[i][j] = up[up[i][j - 1]][j - 1];
                }
            }
        }
    }

    /*
     * getKthAncestor(node, k)
     * -----------------------
     * node se exactly k steps UPAR wala ancestor return karta hai.
     * Agar k steps upar koi node nahi (root se bahar), to -1 return.
     *
     * Trick: k ko binary representation mein tod do.
     *   k = 13 = 1101 (binary) = 8 + 4 + 1
     *   Matlab: 8 steps upar + 4 steps upar + 1 step upar
     *
     *   i=0: k & 1  -> 1 step  upar  -> up[node][0]
     *   i=1: k & 2  -> 2 steps upar  -> up[node][1]
     *   i=2: k & 4  -> 4 steps upar  -> up[node][2]
     *   i=3: k & 8  -> 8 steps upar  -> up[node][3]
     *
     * Example: node=7, k=5 (binary 101)
     *   i=0: 5&1=1 -> up[7][0] = parent of 7
     *   i=2: 5&4=4 -> up[...][2] = 4 steps upar
     *
     * Time: O(LOG) = O(log n)
     */
    int getKthAncestor(int node, int k) {
        for (int i = 0; i < LOG; ++i) {
            if (k & (1 << i)) {              // agar k ka i-th bit set hai
                node = up[node][i];          // 2^i steps upar jump karo
                if (node == -1) {            // root se upar nahi ja sakte
                    return -1;
                }
            }
        }
        return node;
    }

    /*
     * lca(u, v)
     * ---------
     * Lowest Common Ancestor — dono nodes ka sabse neeche wala common ancestor.
     *
     * Step 1: Depth equalize karo
     *   Jo node zyada neeche hai (zyada depth), use upar uthao
     *   taaki dono same level par aa jayein.
     *   u = getKthAncestor(u, depth[u] - depth[v])
     *
     * Step 2: Agar ab dono same node hain, wahi LCA hai
     *   (matlab ek node dusre ka ancestor tha)
     *
     * Step 3: Binary lifting se saath-saath upar chalo
     *   Sabse bade jump (2^(LOG-1)) se shuru karo, chhote tak aao.
     *   Sirf tab jump karo jab up[u][j] != up[v][j]
     *   (matlab abhi LCA cross nahi hua)
     *
     *   Loop ke baad u aur v LCA ke turant neeche wale children honge.
     *
     * Step 4: LCA = up[u][0] = dono ka direct parent
     *
     * Example: Tree mein LCA(3, 4) jahan 3 aur 4 siblings hain
     *   Dono same depth par lao -> phir jump karo -> LCA = unka parent
     *
     * Time: O(LOG) = O(log n)
     */
    int lca(int u, int v) {
        // Step 1: u ko hamesha neeche wale node par rakho (zyada depth wala)
        if (depth[u] < depth[v]) {
            swap(u, v);
        }

        // u ko utna upar lao jitna v neeche hai — ab dono same level par
        u = getKthAncestor(u, depth[u] - depth[v]);

        // Step 2: agar same node ho gaye, wahi LCA hai
        if (u == v) {
            return u;
        }

        // Step 3: bade jump se chhote tak — LCA ke just neeche ruk jao
        for (int j = LOG - 1; j >= 0; --j) {
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }

        // Step 4: ab u aur v siblings hain (same parent) — wahi LCA
        return up[u][0];
    }
};


/*
 * solveTree(treeNum, parent, lcaQueries, kthQueries)
 * --------------------------------------------------
 * Ek sample tree par BinaryLifting test karta hai.
 * Parent array se tree build karta hai, phir saari queries run karke
 * output print karta hai — debugging / learning ke liye helpful.
 *
 * Parameters:
 *   treeNum     — konsa test tree hai (sirf print ke liye)
 *   parent      — parent[i] = node i ka parent (-1 for root)
 *   lcaQueries  — (u, v) pairs jinke LCA nikalne hain
 *   kthQueries  — (node, k) pairs jinke k-th ancestor nikalne hain
 */
void solveTree(int treeNum, vector<int>& parent,
               vector<pair<int, int>>& lcaQueries,
               vector<pair<int, int>>& kthQueries) {
    cout << "\n===== Tree " << treeNum << " =====\n";

    int n = parent.size();
    BinaryLifting bl(n, parent);

    cout << "Parent Array: ";
    for (int i = 0; i < n; ++i) {
        cout << parent[i] << " ";
    }
    cout << "\n";

    cout << "\n-- LCA Queries --\n";
    for (auto& [u, v] : lcaQueries) {
        cout << "LCA(" << u << ", " << v << ") = " << bl.lca(u, v) << "\n";
    }

    cout << "\n-- Kth Ancestor Queries --\n";
    for (auto& [node, k] : kthQueries) {
        cout << "getKthAncestor(" << node << ", " << k << ") = "
             << bl.getKthAncestor(node, k) << "\n";
    }
}

/*
 * main()
 * ------
 * Teen alag-alag trees par Binary Lifting demo karta hai:
 *
 * Tree 1: Simple binary tree  — basic LCA + ancestor test
 * Tree 2: Linear chain        — worst case depth (sabse lamba path)
 * Tree 3: Wide tree           — zyada children, alag branches
 *
 * Har tree ke liye solveTree() call hota hai jo queries run karke output deta hai.
 */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // -------------------------------------------------------
    // Tree 1: Simple binary tree
    //         0
    //        / \
    //       1   2
    //      / \
    //     3   4
    // parent = [-1, 0, 0, 1, 1]
    // -------------------------------------------------------
    {
        vector<int> parent = {-1, 0, 0, 1, 1};
        vector<pair<int, int>> lcaQ = {{3, 4}, {3, 2}, {1, 2}};
        vector<pair<int, int>> kthQ = {{3, 1}, {3, 2}, {4, 1}};
        solveTree(1, parent, lcaQ, kthQ);
    }

    // -------------------------------------------------------
    // Tree 2: Linear chain (worst case for depth)
    //    0 - 1 - 2 - 3 - 4 - 5
    // parent = [-1, 0, 1, 2, 3, 4]
    // -------------------------------------------------------
    {
        vector<int> parent = {-1, 0, 1, 2, 3, 4};
        vector<pair<int, int>> lcaQ = {{5, 3}, {4, 2}, {5, 1}};
        vector<pair<int, int>> kthQ = {{5, 2}, {5, 5}, {3, 1}};
        solveTree(2, parent, lcaQ, kthQ);
    }

    // -------------------------------------------------------
    // Tree 3: Wide tree
    //            0
    //          / | \ \
    //         1  2  3  4
    //        /\     \
    //       5  6     7
    //      /
    //     8
    // parent = [-1, 0, 0, 0, 0, 1, 1, 3, 5]
    // -------------------------------------------------------
    {
        vector<int> parent = {-1, 0, 0, 0, 0, 1, 1, 3, 5};
        vector<pair<int, int>> lcaQ = {{8, 7}, {6, 7}, {8, 2}, {5, 4}};
        vector<pair<int, int>> kthQ = {{8, 1}, {8, 3}, {7, 2}};
        solveTree(3, parent, lcaQ, kthQ);
    }

    return 0;
}
