#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * PROBLEM: Sum of Distances in Tree  (LeetCode 834)
 * ════════════════════════════════════════════════════════════════════════════
 *
 * Diya hai: n nodes ka tree (0..n-1), edges list.
 * Poochna hai: ans[i] = node i se har dusre node tak distance ka SUM
 *
 * Example:
 *   n=6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
 *        0
 *       / \
 *      1   2
 *         /|\
 *        3 4 5
 *
 *   ans[0] = 8  (dist to 1,2,3,4,5 = 1+1+2+2+2)
 *   ans[1] = 9
 *   ans[2] = 6
 *   ...
 *
 * NAIVE: har node se BFS/DFS → O(n²)
 * REROOTING: 2 DFS → O(n)
 *
 * APPROACH:
 *   Pass 1: sz[u], down[u] — subtree size + distance sum in subtree
 *   Pass 2: ans[v] = ans[u] - sz[v] + (n - sz[v])
 *
 * Time: O(n)  |  Space: O(n)
 * ════════════════════════════════════════════════════════════════════════════
 */

class Solution {
private:
    int n;
    vector<vector<int>> adj;
    vector<int> sz;
    vector<long long> down, ans;

    void dfsDown(int u, int parent) {
        sz[u] = 1;
        down[u] = 0;
        for (int v : adj[u]) {
            if (v == parent) continue;
            dfsDown(v, u);
            sz[u] += sz[v];
            down[u] += down[v] + sz[v];
        }
    }

    void dfsReroot(int u, int parent) {
        for (int v : adj[u]) {
            if (v == parent) continue;
            ans[v] = ans[u] - sz[v] + (n - sz[v]);
            dfsReroot(v, u);
        }
    }

public:
    vector<int> sumOfDistancesInTree(int n_, vector<vector<int>>& edges) {
        n = n_;
        adj.assign(n, {});
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        sz.assign(n, 0);
        down.assign(n, 0);
        ans.assign(n, 0);

        dfsDown(0, -1);
        ans[0] = down[0];
        dfsReroot(0, -1);

        return vector<int>(ans.begin(), ans.end());
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 6;
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {2, 3}, {2, 4}, {2, 5}};

    Solution sol;
    vector<int> result = sol.sumOfDistancesInTree(n, edges);

    cout << "LC 834 — Sum of distances from each node:\n";
    for (int i = 0; i < n; ++i)
        cout << "  ans[" << i << "] = " << result[i] << "\n";

    // Second example: line 0-1-2-3
    n = 4;
    edges = {{0, 1}, {1, 2}, {2, 3}};
    result = sol.sumOfDistancesInTree(n, edges);
    cout << "\nLine tree 0-1-2-3:\n";
    for (int i = 0; i < n; ++i)
        cout << "  ans[" << i << "] = " << result[i] << "\n";

    return 0;
}
