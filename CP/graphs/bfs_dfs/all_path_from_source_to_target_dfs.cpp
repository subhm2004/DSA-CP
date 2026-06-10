// ════════════════════════════════════════════════════════════════════════════
// ALL PATHS SOURCE → TARGET (DFS + Backtracking)
// ────────────────────────────────────────────────────────────────────────────
// DFS se har possible path explore karo. Target pe pahunch ke path save karo,
// phir backtrack (path.pop_back) taaki doosri branches try ho saken.
// LC 797 - All Paths From Source to Target
// ════════════════════════════════════════════════════════════════════════════

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    unordered_map<int, list<pair<int, int>>> adjList;

    // ── dfs: current node se target tak saari paths recursively dhundho ─────
    // Step 1: Current node ko path vector mein push_back karo (ab tak ka route extend).
    // Step 2: Agar node == target hai to poora path result mein save karo — ek valid path mil gaya.
    // Step 3: Warna har neighbor ke liye recursively dfs(neighbor) call karo — saari branches explore.
    // Step 4: Recursion wapas aane par path.pop_back() — backtrack taaki doosri sibling branches try ho saken.
    // Step 5: Path by reference pass hota hai taaki har branch apna copy banaye bina share kare.
    void dfs(int node, vector<int> &path, vector<vector<int>> &result, int target)
    {
        path.push_back(node);
        if (node == target)
        {
            result.push_back(path); // poora path mil gaya — save karo
        }
        else
        {
            for (auto &[neighbor, _] : adjList[node])
            {
                dfs(neighbor, path, result, target); // aage badho
            }
        }
        path.pop_back(); // backtrack — is node ko path se hatao, sibling try karo
    }

    // ── allPathsSourceTarget: graph ko adjList mein convert karke DFS chalao ──
    // Step 1: Adjacency list (graph[u]) ko unordered_map + list format mein convert karo.
    // Step 2: Empty path vector aur empty result vector banao.
    // Step 3: Node 0 se DFS start karo — source hamesha 0, target hamesha n-1 (DAG assumption).
    // Step 4: DFS saari 0 → (n-1) paths result mein bharega.
    // Step 5: Final result return karo — har entry ek complete valid path hai.
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>> &graph)
    {
        int n = graph.size();
        for (int u = 0; u < n; ++u)
        {
            for (int v : graph[u])
            {
                adjList[u].emplace_back(v, 0); // dummy weight
            }
        }

        vector<vector<int>> result;
        vector<int> path;
        dfs(0, path, result, n - 1);
        return result;
    }
};

// Example usage
int main()
{
    Solution sol;
    vector<vector<int>> graph = {{1, 2}, {3}, {3}, {}};
    vector<vector<int>> paths = sol.allPathsSourceTarget(graph);

    for (auto &path : paths)
    {
        for (int node : path)
            cout << node << " ";
        cout << endl;
    }

    return 0;
}
