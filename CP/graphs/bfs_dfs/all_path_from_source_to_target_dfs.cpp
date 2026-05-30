#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    unordered_map<int, list<pair<int, int>>> adjList;

    void dfs(int node, vector<int> &path, vector<vector<int>> &result, int target)
    {
        path.push_back(node);
        if (node == target)
        {
            result.push_back(path);
        }
        else
        {
            for (auto &[neighbor, _] : adjList[node])
            {
                dfs(neighbor, path, result, target);
            }
        }
        path.pop_back(); // backtrack
    }

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
