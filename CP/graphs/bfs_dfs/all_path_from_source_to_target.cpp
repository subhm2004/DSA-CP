#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
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
                    q.push(newPath);
                }
            }
        }
    }

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
