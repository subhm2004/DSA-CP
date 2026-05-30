#include <bits/stdc++.h> // single parse dfs
using namespace std;

class Solution
{
public:
    unordered_map<int, list<pair<int, int>>> adjList;

    // Function to add an edge to the adjacency list
    void addEdge(int u, int v, bool direction)
    {
        // direction = 0 -> undirected graph
        // direction = 1 -> directed graph
        adjList[u].push_back({v, 1});
        if (direction == 0)
        {
            adjList[v].push_back({u, 1});
        }
    }

    // Function to print the adjacency list
    void printAdjacencyList()
    {
        for (auto node : adjList)
        {
            cout << node.first << " -> ";
            for (auto neighbour : node.second)
            {
                cout << "(" << neighbour.first << ", " << neighbour.second << "), ";
            }
            cout << endl;
        }
    }

    // DFS to calculate maximum depth
    int maxDepth(int node, int parent, int &maxDiameter)
    {
        int maxSubDepth1 = 0, maxSubDepth2 = 0;

        for (auto [neighbor, weight] : adjList[node])
        {
            if (neighbor == parent)
                continue;

            int subDepth = maxDepth(neighbor, node, maxDiameter) + weight;

            // Update the two largest depths
            if (subDepth > maxSubDepth1)
            {
                maxSubDepth2 = maxSubDepth1;
                maxSubDepth1 = subDepth;
            }
            else if (subDepth > maxSubDepth2)
            {
                maxSubDepth2 = subDepth;
            }
        }

        // Update the diameter using the two largest depths
        maxDiameter = max(maxDiameter, maxSubDepth1 + maxSubDepth2);

        return maxSubDepth1;
    }

    // Function to get the diameter of the tree
    int getDiameter(vector<vector<int>> &edges)
    {
        adjList.clear(); // Clear previous data

        // Build the graph using the addEdge function
        for (const auto &edge : edges)
        {
            int u = edge[0], v = edge[1];
            addEdge(u, v, 0); // Undirected graph
        }

        int maxDiameter = 0;
        maxDepth(edges[0][0], -1, maxDiameter); // Start DFS from any node
        return maxDiameter;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {4, 5}};

    cout << "Adjacency List Representation:\n";
    sol.getDiameter(edges); // Build the graph
    sol.printAdjacencyList();

    cout << "\nDiameter of the tree: " << sol.getDiameter(edges) << endl;
    return 0;
}
