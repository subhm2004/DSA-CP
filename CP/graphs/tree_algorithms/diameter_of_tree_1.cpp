#include <iostream> // 2 parse dfs hai ye
#include <vector>
#include <unordered_map>
#include <list>
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

    // DFS to find the farthest node and depth
    void dfs(int node, int parent, int depth, int &maxDepth, int &farthestNode)
    {
        if (depth > maxDepth)
        {
            maxDepth = depth;
            farthestNode = node;
        }

        for (auto [neighbor, weight] : adjList[node])
        {
            if (neighbor != parent)
            {
                dfs(neighbor, node, depth + weight, maxDepth, farthestNode);
            }
        }
    }

    // Function to get the diameter of the tree
    int getDiameter()
    {
        if (adjList.empty())
            return 0;

        int farthestNode = -1, maxDepth = -1;
        dfs(adjList.begin()->first, -1, 0, maxDepth, farthestNode);

        maxDepth = -1;
        dfs(farthestNode, -1, 0, maxDepth, farthestNode);

        return maxDepth;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {4, 5}};

    // Build the graph
    for (const auto &edge : edges)
    {
        sol.addEdge(edge[0], edge[1], 0);
    }

    cout << "Adjacency List Representation:\n";
    sol.printAdjacencyList();

    cout << "\nDiameter of the tree: " << sol.getDiameter() << endl;
    return 0;
}
