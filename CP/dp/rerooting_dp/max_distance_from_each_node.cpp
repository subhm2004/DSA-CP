#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * PROBLEM: Maximum Distance From Each Node (Rerooting variant)
 * ════════════════════════════════════════════════════════════════════════════
 *
 * Tree diya hai. Har node i ke liye:
 *   ans[i] = i se sabse door node tak ki distance (tree height from i)
 *
 * Example: chain 0-1-2-3
 *   ans[0]=3, ans[1]=2, ans[2]=2, ans[3]=3  (symmetric chain)
 *
 * APPROACH (rerooting with 2 values per node):
 *   down[u] = max distance from u going DOWN into subtree
 *   up[u]   = max distance from u going UP / outside subtree
 *   ans[u]  = max(down[u], up[u])
 *
 * Pass 1 — dfsDown:
 *   down[u] = max over children of (1 + down[v])
 *
 * Pass 2 — dfsReroot:
 *   child v ke liye up[v] = max(
 *       1 + up[u],                    // parent side se seedha up
 *       2 + down[sibling]             // sibling ke through (best non-v child)
 *   )
 *   sibling best = top two down values se nikalte hain
 *
 * Time: O(n)  |  Space: O(n)
 * ════════════════════════════════════════════════════════════════════════════
 */

class MaxDistanceReroot {
private:
    int n;
    vector<vector<int>> adj;
    vector<int> down, up, ans;

    void dfsDown(int u, int parent) {
        down[u] = 0;
        for (int v : adj[u]) {
            if (v == parent) continue;
            dfsDown(v, u);
            down[u] = max(down[u], 1 + down[v]);
        }
    }

    void dfsReroot(int u, int parent) {
        // children ka best down (sibling branch ke liye)
        int best1 = -1, best2 = -1, bestChild = -1;
        int childCnt = 0;
        for (int v : adj[u]) {
            if (v == parent) continue;
            ++childCnt;
            int cand = down[v];
            if (cand >= best1) {
                best2 = best1;
                best1 = cand;
                bestChild = v;
            } else if (cand >= best2) {
                best2 = cand;
            }
        }

        for (int v : adj[u]) {
            if (v == parent) continue;

            // u ke through parent side: up[u] + 1 edge
            int viaParent = up[u] + 1;
            // u ke through kisi AUR child ki branch: 1 (v→u) + 1 (u→sibling) + down[sibling]
            int siblingBest = (v == bestChild) ? best2 : best1;
            int viaSibling = (childCnt >= 2) ? (siblingBest + 2) : 0;

            up[v] = max(viaParent, viaSibling);
            dfsReroot(v, u);
        }
    }

public:
    MaxDistanceReroot(int n_, const vector<vector<int>>& edges) : n(n_) {
        adj.assign(n, {});
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        down.assign(n, 0);
        up.assign(n, 0);
        ans.assign(n, 0);
    }

    vector<int> maxDistanceFromEachNode(int root = 0) {
        dfsDown(root, -1);
        up[root] = 0;  // root ke upar koi node nahi
        dfsReroot(root, -1);

        for (int i = 0; i < n; ++i)
            ans[i] = max(down[i], up[i]);

        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Chain 0-1-2-3
    int n = 4;
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 3}};
    MaxDistanceReroot mr(n, edges);
    vector<int> res = mr.maxDistanceFromEachNode(0);

    cout << "Max distance from each node (chain 0-1-2-3):\n";
    for (int i = 0; i < n; ++i)
        cout << "  node " << i << " -> " << res[i] << "\n";

    // Star: 0 connected to 1,2,3,4
    n = 5;
    edges = {{0, 1}, {0, 2}, {0, 3}, {0, 4}};
    MaxDistanceReroot mr2(n, edges);
    res = mr2.maxDistanceFromEachNode(0);
    cout << "\nStar centered at 0:\n";
    for (int i = 0; i < n; ++i)
        cout << "  node " << i << " -> " << res[i] << "\n";

    return 0;
}
