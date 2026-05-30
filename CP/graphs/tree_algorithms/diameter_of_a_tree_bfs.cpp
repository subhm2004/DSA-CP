#include <bits/stdc++.h>
/*
TREE DIAMETER USING BFS - VERY IMPORTANT ALGORITHM!
Ye algorithm tree ki diameter efficiently nikalta hai using TWO BFS calls

DIAMETER = Tree mein sabse lamba path (distance between two farthest nodes)

KEY INSIGHT:
- Tree mein kisi bhi node se sabse door wala node, diameter ka ek end point hota hai
- Phir us end point se sabse door wala node, diameter ka dusra end point hota hai
*/
using namespace std;

class Solution
{
public:
    // BFS helper function jo kisi node se sabse door ka node aur uska distance return karta hai
    // adj: adjacency list, start: starting node
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

    // Main function jo tree ka diameter calculate karta hai using TWO BFS approach
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

    // Edge list se adjacency list banane ka function
    unordered_map<int, list<int>> buildAdj(const vector<vector<int>> &edges)
    {
        unordered_map<int, list<int>> adj; // Adjacency list

        // Har edge ko process karo
        for (const auto &edge : edges)
        {
            // Undirected graph hai, so dono taraf se edge add karo
            adj[edge[0]].push_back(edge[1]); // edge[0] -> edge[1]
            adj[edge[1]].push_back(edge[0]); // edge[1] -> edge[0]
        }

        return adj; // Completed adjacency list return karo
    }

    // Main public function jo diameter calculate karta hai
    int treeDiameter(vector<vector<int>> &edges)
    {
        // Step-1: Edge list se adjacency list banao
        unordered_map<int, list<int>> adj = buildAdj(edges);

        // Step-2: Diameter calculate karo using two BFS approach
        return find_diameter(adj);
    }
};

// Example aur testing
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

/*
DETAILED ALGORITHM EXPLANATION:

1. WHY TWO BFS APPROACH WORKS FOR TREES:
   - Mathematical property: Tree mein kisi bhi node se sabse door ka node,
     diameter ka ek endpoint hota hai
   - Phir us endpoint se sabse door ka node, diameter ka dusra endpoint hota hai

2. STEP-BY-STEP TRACE (for given example):

   First BFS from node 0:
   - Level 0: [0]
   - Level 1: [1]
   - Level 2: [2, 4]
   - Level 3: [3, 5]
   - Farthest nodes: 3 and 5 (both at distance 3)
   - Let's say we get node 3

   Second BFS from node 3:
   - Level 0: [3]
   - Level 1: [2]
   - Level 2: [1]
   - Level 3: [0, 4]
   - Level 4: [5]
   - Farthest node: 5 at distance 4
   - Diameter = 4

3. TIME COMPLEXITY: O(V + E)
   - Two BFS traversals: 2 * O(V + E)
   - Building adjacency list: O(E)
   - Total: O(V + E)

4. SPACE COMPLEXITY: O(V + E)
   - Adjacency list: O(V + E)
   - BFS queue and visited: O(V)

5. WHY THIS IS BETTER THAN OTHER APPROACHES:
   - DFS approach: O(V²) in worst case (need to run DFS from every node)
   - This approach: O(V + E) - much more efficient!

6. IMPORTANT POINTS TO REMEMBER:
   - Works only for TREES (connected acyclic graphs)
   - For general graphs, this approach won't work
   - Very useful in competitive programming
   - Must remember this two-BFS technique!

APPLICATIONS:
- Finding diameter of trees
- Finding the longest path in trees
- Center of tree problems
- Tree rerooting problems
*/