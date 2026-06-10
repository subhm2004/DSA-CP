#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// TREE DIAMETER — Two BFS Approach (VERY IMPORTANT!)
// ────────────────────────────────────────────────────────────────────────────
// Diameter = tree me sabse lamba path (do farthest nodes ke beech distance).
//
// KEY INSIGHT (tree ki mathematical property):
//   BFS-1: kisi bhi node se sabse door node = diameter ka ek ENDPOINT
//   BFS-2: us endpoint se sabse door node = dusra ENDPOINT, distance = DIAMETER
//
// DFS har node se chalane se O(V²) — ye approach sirf 2 BFS = O(V+E)!
// Sirf TREES pe kaam karta hai (connected, acyclic).
// Time: O(V + E)  |  Space: O(V + E)
// ════════════════════════════════════════════════════════════════════════════

class Solution
{
public:
    // ── BFS: start se sabse door node aur uski distance return karo ────────
    // Level-wise BFS: har level ke baad distance++. Last level ka last node
    // = sabse door wala node (farthest_Node).
    // Returns: {farthest_node, distance_to_farthest_node}
    pair<int, int> BFS(unordered_map<int, list<int>> &adj, int start)
    {
        queue<int> q;                     // BFS ke liye queue
        unordered_map<int, bool> visited; // Visited nodes track karne ke liye
        q.push(start);                    // Starting node ko queue mein daalo
        visited[start] = true;            // Starting node ko visited mark karo

        int farthest_Node = start; // Sabse door ka node (initially start node)
        int distance = 0;          // Distance counter

        // Standard BFS traversal with level-wise processing
        while (!q.empty())
        {
            int size = q.size(); // Current level mein kitne nodes hain

            // Current level ke saare nodes process karo
            while (size--)
            {
                int curr = q.front(); // Current node nikalo
                q.pop();

                farthest_Node = curr; // Ye node current level ki last node hai
                                      // Last level ka last node = sabse door ka node

                // Current node ke saare neighbors check karo
                for (int neighbor : adj[curr])
                {
                    if (!visited[neighbor]) // Agar neighbor unvisited hai
                    {
                        visited[neighbor] = true; // Use visited mark karo
                        q.push(neighbor);         // Queue mein add karo next level ke liye
                    }
                }
            }

            // Agar queue mein abhi bhi nodes hain, matlab next level hai
            // To distance increment karo
            if (!q.empty())
                distance++;
        }

        return {farthest_Node, distance}; // Sabse door ka node aur uska distance return karo
    }

    // ── find_diameter: do BFS se tree ka diameter nikalo ───────────────────
    // Step 1: random node (0) se sabse door node dhundo -> ek endpoint.
    // Step 2: us endpoint se sabse door node dhundo -> distance = diameter.
    int find_diameter(unordered_map<int, list<int>> &adj)
    {
        // STEP-1: Kisi bhi random node se sabse door ka node dhundo
        // Ye node diameter ka ek end point hoga (MATHEMATICAL PROPERTY of trees)
        auto [farthest_Node, _] = BFS(adj, 0); // Node 0 se start karo (koi bhi node le sakte hain)
                                               // '_' means we ignore the distance in step 1

        // STEP-2: Step-1 mein mile node se sabse door ka node dhundo
        // Ye distance hi diameter hoga!
        auto [otherEndNode, diameter] = BFS(adj, farthest_Node);

        return diameter; // Final diameter return karo
    }

    // ── buildAdj: edge list se undirected adjacency list banao ───────────────
    unordered_map<int, list<int>> buildAdj(const vector<vector<int>> &edges)
    {
        unordered_map<int, list<int>> adj; // Adjacency list

        // Har edge ko process karo — undirected graph, dono taraf edge add
        for (const auto &edge : edges)
        {
            adj[edge[0]].push_back(edge[1]); // edge[0] -> edge[1]
            adj[edge[1]].push_back(edge[0]); // edge[1] -> edge[0]
        }

        return adj; // Completed adjacency list return karo
    }

    // ── treeDiameter: public API — edges se diameter return karo ───────────
    int treeDiameter(vector<vector<int>> &edges)
    {
        // Step-1: Edge list se adjacency list banao
        unordered_map<int, list<int>> adj = buildAdj(edges);

        // Step-2: Diameter calculate karo using two BFS approach
        return find_diameter(adj);
    }
};

int main()
{
    Solution sol;

    /*
    Tree structure (example):
           0
           |
           1
          / \
         2   4
         |   |
         3   5

    Edges: {{0,1}, {1,2}, {2,3}, {1,4}, {4,5}}
    Diameter path: 3 -> 2 -> 1 -> 4 -> 5 (length = 4)
    */
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 3}, {1, 4}, {4, 5}};

    cout << "Tree Diameter: " << sol.treeDiameter(edges) << endl; // Output: 4
    return 0;
}
