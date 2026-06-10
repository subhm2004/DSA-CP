#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// TREE DIAMETER — Two-Pass DFS Approach
// ────────────────────────────────────────────────────────────────────────────
// BFS wale two-pass approach ka DFS version:
//
//   DFS-1: kisi node se sabse door node dhundo (farthestNode)
//   DFS-2: farthestNode se sabse door node dhundo -> distance = DIAMETER
//
// DFS me depth track karte hain — har step pe depth + weight.
// Tree property: farthest-from-farthest = diameter length.
// Time: O(V)  |  Space: O(V)
// ════════════════════════════════════════════════════════════════════════════

class Solution
{
public:
    unordered_map<int, list<pair<int, int>>> adjList;

    // ── addEdge: adjacency list me edge add karo ─────────────────────────────
    // direction = 0 -> undirected, 1 -> directed
    void addEdge(int u, int v, bool direction)
    {
        adjList[u].push_back({v, 1});
        if (direction == 0)
        {
            adjList[v].push_back({u, 1});
        }
    }

    // ── printAdjacencyList: graph structure print karo ─────────────────────
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

    // ── dfs: start se sabse door node aur max depth dhundo ──────────────────
    // Har node pe depth update karo — agar current depth > maxDepth to
    // farthestNode = current node. Parent skip (tree traversal).
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

    // ── getDiameter: do DFS passes se tree diameter return karo ──────────────
    // Pass 1: random node se farthest node dhundo.
    // Pass 2: farthest node se dobara DFS — maxDepth = diameter.
    int getDiameter()
    {
        if (adjList.empty())
            return 0;

        // Step 1: kisi node se DFS — sabse door node = diameter ka ek endpoint
        int farthestNode = -1, maxDepth = -1;
        dfs(adjList.begin()->first, -1, 0, maxDepth, farthestNode);

        // Step 2: us endpoint se dobara DFS — maxDepth = diameter length
        maxDepth = -1;
        dfs(farthestNode, -1, 0, maxDepth, farthestNode);

        return maxDepth;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {4, 5}};

    // Edge list se graph build karo
    for (const auto &edge : edges)
    {
        sol.addEdge(edge[0], edge[1], 0);
    }

    cout << "Adjacency List Representation:\n";
    sol.printAdjacencyList();

    cout << "\nDiameter of the tree: " << sol.getDiameter() << endl;
    return 0;
}
