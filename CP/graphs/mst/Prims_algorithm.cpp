#include <bits/stdc++.h> // Include all standard C++ libraries
using namespace std;

class Solution
{
public:
    // Adjacency list to represent the weighted graph
    // Key: vertex number, Value: list of pairs (neighbor, weight)
    unordered_map<int, list<pair<int, int>>> adjList;

    /**
     * Function to add an edge to the graph
     * @param u: source vertex
     * @param v: destination vertex
     * @param w: weight of the edge between u and v
     * @param direction: true for directed edge, false for undirected edge
     */
    void addEdge(int u, int v, int w, bool direction)
    {
        // Add edge from u to v with weight w
        adjList[u].push_back({v, w});

        // If it's an undirected graph, add the reverse edge as well
        if (!direction)
        {
            // Add edge from v to u with same weight w
            adjList[v].push_back({u, w});
        }
    }

    /**
     * Function to find the vertex with minimum key value that is not yet included in MST
     * This is the core selection step of Prim's algorithm
     * @param key: map containing minimum edge weights to reach each vertex
     * @param mst: map tracking which vertices are already included in MST
     * @return: vertex number with minimum key value, or -1 if no vertex found
     */
    int get_min_value_node(unordered_map<int, int> &key, unordered_map<int, bool> &mst)
    {
        int temp = INT_MAX; // Initialize with maximum possible value
        int index = -1;     // Initialize index as -1 (not found)

        // Iterate through all vertices and their key values
        for (auto &[node, weight] : key) // Structured binding (C++17 feature)
        {
            // Check if vertex is not in MST and has smaller key value
            if (!mst[node] && weight < temp)
            {
                temp = weight; // Update minimum weight
                index = node;  // Update vertex with minimum weight
            }
        }
        return index; // Return vertex with minimum key value
    }

    /**
     * Prim's Algorithm implementation to find Minimum Spanning Tree
     * Algorithm Steps:
     * 1. Initialize all vertices with infinite key values
     * 2. Start with vertex 0 (key = 0)
     * 3. Repeatedly pick minimum key vertex not in MST
     * 4. Add it to MST and update keys of adjacent vertices
     * 5. Continue until all vertices are included
     *
     * @param V: total number of vertices in the graph
     * @return: total weight of the Minimum Spanning Tree
     */
    int Prims_Algo(int V)
    {
        // Data structures for Prim's algorithm
        unordered_map<int, int> key;    // Minimum edge weight to connect each vertex to MST
        unordered_map<int, bool> mst;   // Track which vertices are included in MST
        unordered_map<int, int> parent; // Store parent of each vertex in MST (for reconstruction)

        // STEP 1: Initialize all data structures
        for (int i = 0; i < V; i++)
        {
            key[i] = INT_MAX; // Initially, all vertices have infinite distance
            mst[i] = false;   // No vertex is included in MST initially
            parent[i] = -1;   // No parent assigned initially
        }

        // STEP 2: Start with vertex 0 as the root of MST
        key[0] = 0; // Make key 0 so that vertex 0 is picked first

        // STEP 3: Build MST by including V vertices one by one
        for (int i = 0; i < V; i++)
        {
            // Pick the vertex with minimum key value from vertices not yet in MST
            int u = get_min_value_node(key, mst);

            // If no vertex found, break (disconnected graph case)
            if (u == -1)
                break;

            // Include the picked vertex in MST
            mst[u] = true;

            // STEP 4: Update key values of adjacent vertices of the picked vertex
            // Only consider vertices that are not yet included in MST
            for (auto &edge : adjList[u]) // Iterate through all neighbors of u
            {
                int v = edge.first;  // Neighbor vertex
                int w = edge.second; // Weight of edge u-v

                // Update key[v] if:
                // 1. v is not in MST yet (!mst[v])
                // 2. Weight of edge u-v is smaller than current key[v] (w < key[v])
                if (!mst[v] && w < key[v])
                {
                    key[v] = w;    // Update key value
                    parent[v] = u; // Set u as parent of v in MST
                }
            }
        }

        // STEP 5: Calculate total weight of MST
        int sum = 0;

        // Iterate through all vertices to find MST edges
        for (int u = 0; u < V; ++u)
        {
            // Skip root vertex (vertex 0) as it has no parent
            if (parent[u] == -1)
                continue;

            // Find the edge weight between vertex u and its parent
            for (auto &edge : adjList[u])
            {
                int v = edge.first;  // Neighbor vertex
                int w = edge.second; // Edge weight

                // If this neighbor is the parent of current vertex
                if (v == parent[u])
                {
                    sum += w; // Add edge weight to total MST weight
                    break;    // Found the parent connection, no need to check further
                }
            }
        }

        return sum; // Return total weight of MST
    }
};

int main()
{
    // Create an instance of Solution class
    Solution sol;

    // Create a weighted undirected graph with 5 vertices (0, 1, 2, 3, 4)
    // Graph visualization:
    //       (2)
    //   0 -------- 1
    //   |     (8) /|\ (3)
    //   |       /  |  \
    // (6)|     /   |   2
    //   |   /    (5)|   |\
    //   | /        |   | \(7)
    //   3          4 ---+
    //
    // Adding edges to the graph (last parameter 0 means undirected)
    sol.addEdge(0, 1, 2, 0); // Edge between vertices 0 and 1 with weight 2
    sol.addEdge(1, 2, 3, 0); // Edge between vertices 1 and 2 with weight 3
    sol.addEdge(0, 3, 6, 0); // Edge between vertices 0 and 3 with weight 6
    sol.addEdge(1, 3, 8, 0); // Edge between vertices 1 and 3 with weight 8
    sol.addEdge(1, 4, 5, 0); // Edge between vertices 1 and 4 with weight 5
    sol.addEdge(2, 4, 7, 0); // Edge between vertices 2 and 4 with weight 7

    int V = 5; // Total number of vertices in the graph

    // Execute Prim's algorithm and display the result
    cout << "Minimum Spanning Tree Weight: " << sol.Prims_Algo(V) << endl;

    return 0;
}

/*
ALGORITHM EXPLANATION:
=====================

What is Minimum Spanning Tree (MST)?
- A subgraph that connects all vertices with minimum total edge weight
- Has exactly V-1 edges for V vertices
- No cycles (it's a tree)
- Multiple MSTs possible, but all have same total weight

Prim's Algorithm:
- Greedy algorithm that builds MST by adding one vertex at a time
- Always adds the minimum weight edge that connects MST to a non-MST vertex
- Guarantees optimal solution due to cut property

Time Complexity: O(V²) - due to finding minimum key vertex V times
Space Complexity: O(V + E) - for adjacency list and auxiliary data structures

Expected Output for given graph:
MST edges: 0-1(2), 1-2(3), 1-4(5), 0-3(6)
Total weight: 2 + 3 + 5 + 6 = 16

STEP-BY-STEP EXECUTION:
======================
Initial: key[0]=0, key[1,2,3,4]=∞, mst[all]=false

Step 1: Pick vertex 0 (min key=0)
        - mst[0] = true
        - Update: key[1]=2, key[3]=6

Step 2: Pick vertex 1 (min key=2)
        - mst[1] = true
        - Update: key[2]=3, key[4]=5, key[3] remains 6 (8>6)

Step 3: Pick vertex 2 (min key=3)
        - mst[2] = true
        - Update: key[4] remains 5 (7>5)

Step 4: Pick vertex 4 (min key=5)
        - mst[4] = true
        - No updates needed

Step 5: Pick vertex 3 (min key=6)
        - mst[3] = true
        - Algorithm complete

Final MST: 0-1-2, 1-4, 0-3 with total weight 16
*/