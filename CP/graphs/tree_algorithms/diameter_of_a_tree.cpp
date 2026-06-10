#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// TREE DIAMETER — Single-Pass DFS Approach
// ────────────────────────────────────────────────────────────────────────────
// Ek hi DFS traversal me diameter nikalte hain — har node pe do sabse lambi
// branches (subtree depths) track karte hain.
//
// maxDepth(node): node ke subtree ki maximum depth return karta hai.
//   Har child se depth aati hai — top 2 depths ko combine karke diameter update.
//   maxDiameter = max(maxDiameter, maxSubDepth1 + maxSubDepth2)
//
// Parent skip karo DFS me (cycle avoid) — tree hai to parent wapas nahi jayega.
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

    // ── maxDepth: DFS se subtree ki max depth + diameter update ─────────────
    // Har child se subDepth = maxDepth(child) + weight aati hai.
    // Top 2 subDepths rakho — inka sum current best diameter candidate hai.
    // Return: is node se niche ki sabse lambi branch ki depth (maxSubDepth1).
    int maxDepth(int node, int parent, int &maxDiameter)
    {
        int maxSubDepth1 = 0, maxSubDepth2 = 0;

        // Step 1: har child se subtree depth recursively lo (parent skip)
        for (auto [neighbor, weight] : adjList[node])
        {
            if (neighbor == parent)
                continue;

            int subDepth = maxDepth(neighbor, node, maxDiameter) + weight;

            // Step 2: top 2 sabse lambi branches track karo
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

        // Step 3: do branches ka sum = is node se guzarne wala longest path
        maxDiameter = max(maxDiameter, maxSubDepth1 + maxSubDepth2);

        return maxSubDepth1;
    }

    // ── getDiameter: edges se graph banao aur single DFS se diameter nikalo ─
    int getDiameter(vector<vector<int>> &edges)
    {
        adjList.clear(); // Clear previous data

        // Edge list se undirected graph build karo
        for (const auto &edge : edges)
        {
            int u = edge[0], v = edge[1];
            addEdge(u, v, 0); // Undirected graph
        }

        int maxDiameter = 0;
        maxDepth(edges[0][0], -1, maxDiameter); // Kisi bhi node se DFS start
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
