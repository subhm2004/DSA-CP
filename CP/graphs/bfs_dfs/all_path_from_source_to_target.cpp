// ════════════════════════════════════════════════════════════════════════════
// ALL PATHS SOURCE → TARGET (BFS approach)
// ────────────────────────────────────────────────────────────────────────────
// Directed acyclic graph mein node 0 se node n-1 tak saari possible paths
// nikaalne ka BFS template. Har queue entry ek partial path hai.
// LC 797 - All Paths From Source to Target
// ════════════════════════════════════════════════════════════════════════════

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // ── bfs: adjacency list se saari paths BFS se collect karo ───────────────
    // Step 1: Queue mein seedha {0} push karo — BFS partial paths se start hoti hai.
    // Step 2: Front se path nikalo; last node agar n-1 hai to result mein save karo.
    // Step 3: Warna har neighbor ke liye path ka copy banao, neighbor append karo, queue mein daalo.
    // Step 4: Har queue entry ek alag partial path hai — BFS level-wise saari routes expand karti hai.
    // Step 5: Jab queue khali ho jaye tab saari source-to-target paths result mein collect ho chuki hoti hain.
    void bfs(vector<vector<int>> &graph, vector<vector<int>> &result)
    {
        int n = graph.size();
        queue<vector<int>> q;
        q.push({0}); // Start BFS with the initial path {0}

        while (!q.empty())
        {
            vector<int> path = q.front();
            q.pop();
            int lastNode = path.back();

            if (lastNode == n - 1)
            {
                result.push_back(path); // If last node is the target, store the path
            }
            else
            {
                for (int neighbor : graph[lastNode])
                {
                    vector<int> newPath = path;
                    newPath.push_back(neighbor);
                    q.push(newPath); // naya path queue mein — BFS level-wise expand
                }
            }
        }
    }

    // ── allPathsSourceTarget: wrapper jo result return karta hai ─────────────
    // Step 1: Empty result vector banao.
    // Step 2: Internal bfs() ko graph aur result pass karo — paths fill ho jayengi.
    // Step 3: BFS complete hone ke baad result directly return karo.
    // Step 4: Ye wrapper LeetCode-style API deta hai — caller ko BFS details jaanne ki zaroorat nahi.
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>> &graph)
    {
        vector<vector<int>> result;
        bfs(graph, result);
        return result;
    }
};

// Example Usage
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

/*
 * NOTE: Neeche DFS version bhi hai reference ke liye — compile avoid karne ke liye
 * block comment mein rakha hai. Same file mein do Solution classes compile nahi hongi.
 *
 * ── DFS approach (backtracking) ──
 * DFS se har path explore karo, target pe pahunch ke save karo, phir backtrack.
 */

#if 0
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    void dfs(vector<vector<int>> &graph, int node, vector<int> &path, vector<vector<int>> &result)
    {
        path.push_back(node); // Add current node to path

        if (node == graph.size() - 1)
        {
            result.push_back(path); // If target node is reached, store path
        }
        else
        {
            for (int neighbor : graph[node])
            {
                dfs(graph, neighbor, path, result);
            }
        }

        path.pop_back(); // Backtrack
    }

    vector<vector<int>> allPathsSourceTarget(vector<vector<int>> &graph)
    {
        vector<vector<int>> result;
        vector<int> path;
        dfs(graph, 0, path, result);
        return result;
    }
};

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
#endif
