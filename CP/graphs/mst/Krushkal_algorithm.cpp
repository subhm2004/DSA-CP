#include <iostream>  // For input/output operations (cout, cin)
#include <vector>    // For dynamic arrays
#include <tuple>     // For tuple data structure to store edge information
#include <algorithm> // For sort function

using namespace std;

// Type alias for better readability
// cell represents an edge: (source_vertex, destination_vertex, weight)
using cell = tuple<int, int, int>;

/**
 * Union-Find (Disjoint Set Union) Data Structure
 * Used to efficiently detect cycles in Kruskal's algorithm
 *
 * Key Operations:
 * - find(): Find the root/representative of a set
 * - union(): Merge two sets together
 *
 * Optimizations:
 * - Path Compression: Makes find() nearly O(1)
 * - Union by Rank: Keeps trees balanced
 */
class UnionFind
{
public:
    vector<int> parent; // parent[i] stores the parent of node i
    vector<int> rank;   // rank[i] stores the rank (approximate height) of tree rooted at i

    /**
     * Constructor: Initialize Union-Find structure
     * @param n: number of elements (vertices in graph)
     *
     * Initially:
     * - Each element is its own parent (separate sets)
     * - All ranks are 0 (single node trees)
     */
    UnionFind(int n) : parent(n), rank(n, 0)
    {
        // Initialize each node as its own parent (self-loop)
        for (int i = 0; i < n; i++)
        {
            parent[i] = i; // Node i is the parent of itself
        }
    }

    /**
     * Find operation with Path Compression optimization
     * Finds the root (representative) of the set containing element i
     *
     * Path Compression: During traversal, make every node point directly to root
     * This flattens the tree structure for future operations
     *
     * @param i: element whose root we want to find
     * @return: root of the set containing element i
     *
     * Time Complexity: Nearly O(1) amortized due to path compression
     */
    int find(int i)
    {
        // Base case: if i is its own parent, then i is the root
        if (parent[i] == i)
            return i;

        // Path Compression: Make parent[i] point directly to root
        // This recursively finds root and updates parent[i] on the way back
        return parent[i] = find(parent[i]);
    }

    /**
     * Union operation with Union by Rank optimization
     * Merges the sets containing elements x and y
     *
     * Union by Rank: Always attach smaller tree under root of larger tree
     * This keeps the tree height balanced and operations efficient
     *
     * @param x: first element
     * @param y: second element
     *
     * Time Complexity: Nearly O(1) amortized
     */
    void unionByRank(int x, int y)
    {
        // Find roots of both elements
        int x_parent = find(x);
        int y_parent = find(y);

        // If both elements are already in the same set, do nothing
        if (x_parent == y_parent)
            return;

        // Union by Rank: Attach tree with smaller rank under tree with larger rank
        if (rank[x_parent] < rank[y_parent])
        {
            // Tree rooted at y_parent is taller, so make it the new root
            parent[x_parent] = y_parent;
        }
        else if (rank[x_parent] > rank[y_parent])
        {
            // Tree rooted at x_parent is taller, so make it the new root
            parent[y_parent] = x_parent;
        }
        else
        {
            // Both trees have same rank, arbitrarily choose y_parent as root
            parent[x_parent] = y_parent;
            rank[y_parent]++; // Increase rank since tree height increased by 1
        }
    }
};

/**
 * Graph class for Kruskal's Algorithm implementation
 * Stores edges and implements MST finding algorithm
 */
class Graph
{
public:
    // Vector to store all edges in the graph
    // Each edge is stored as tuple<source, destination, weight>
    vector<cell> edges;

    /**
     * Add a weighted edge to the graph
     * Since we're finding MST, we treat the graph as undirected
     * But we only store each edge once (not both u->v and v->u)
     *
     * @param u: source vertex
     * @param v: destination vertex
     * @param weight: weight of the edge between u and v
     */
    void addEdge(int u, int v, int weight)
    {
        // Store edge as tuple (u, v, weight)
        edges.push_back({u, v, weight});
    }

    /**
     * Kruskal's Algorithm for finding Minimum Spanning Tree
     *
     * Algorithm Steps:
     * 1. Sort all edges by weight in ascending order
     * 2. Initialize Union-Find structure
     * 3. For each edge (in sorted order):
     *    - If edge connects two different components (no cycle)
     *    - Add edge to MST and union the components
     * 4. Continue until we have V-1 edges in MST
     *
     * @param n: number of vertices in the graph
     * @return: total weight of the Minimum Spanning Tree
     *
     * Time Complexity: O(E log E) due to sorting
     * Space Complexity: O(V) for Union-Find structure
     */
    int kruskalMST(int n)
    {
        // STEP 1: Sort all edges by weight in ascending order
        // Lambda function for custom comparison
        sort(edges.begin(), edges.end(), [](const cell &a, const cell &b)
             {
                 // Compare edges by their weights (third element of tuple)
                 // get<2>() extracts the weight from tuple
                 return get<2>(a) < get<2>(b); // Sort in ascending order
             });

        // STEP 2: Initialize Union-Find data structure
        UnionFind uf(n);

        // Variable to store total weight of MST
        int mst_Weight = 0;

        // Counter for number of edges added to MST (for debugging)
        int edges_added = 0;

        // STEP 3: Process each edge in sorted order
        for (auto &edge : edges)
        {
            // Extract edge information from tuple
            int u = get<0>(edge);      // Source vertex
            int v = get<1>(edge);      // Destination vertex
            int weight = get<2>(edge); // Edge weight

            // STEP 4: Check if adding this edge creates a cycle
            // If u and v are in different components, adding edge won't create cycle
            if (uf.find(u) != uf.find(v))
            {
                // No cycle detected, safe to add this edge to MST
                uf.unionByRank(u, v); // Union the two components
                mst_Weight += weight; // Add edge weight to total MST weight
                edges_added++;        // Increment edge counter

                // Optional: Early termination when we have V-1 edges
                // (Complete MST for V vertices has exactly V-1 edges)
                if (edges_added == n - 1)
                    break;
            }
            // If uf.find(u) == uf.find(v), then u and v are in same component
            // Adding this edge would create a cycle, so we skip it
        }

        return mst_Weight; // Return total weight of MST
    }
};

int main()
{
    // Create a graph object
    Graph g;

    // Number of vertices in the graph (0, 1, 2, 3, 4, 5)
    int n = 6;

    // Create a weighted undirected graph
    // Graph structure visualization:
    //     0
    //   / | \
    // (10) (6) (5)
    //  /   |   \
    // 1    2----3
    //  \   |   /
    //  (15) (4)
    //    \ | /
    //     \|/
    //
    // Note: The graph is not fully connected as described by edges below

    // Add weighted edges to the graph
    g.addEdge(0, 1, 10); // Edge between vertex 0 and 1 with weight 10
    g.addEdge(0, 2, 6);  // Edge between vertex 0 and 2 with weight 6
    g.addEdge(0, 3, 5);  // Edge between vertex 0 and 3 with weight 5
    g.addEdge(1, 3, 15); // Edge between vertex 1 and 3 with weight 15
    g.addEdge(2, 3, 4);  // Edge between vertex 2 and 3 with weight 4

    // Execute Kruskal's algorithm and display the result
    cout << "Minimum Spanning Tree Weight: " << g.kruskalMST(n) << endl;

    return 0;
}

/*
DETAILED ALGORITHM EXECUTION TRACE:
===================================

Initial Graph Edges:
- 0-1: weight 10
- 0-2: weight 6
- 0-3: weight 5
- 1-3: weight 15
- 2-3: weight 4

Step 1: Sort edges by weight
Sorted order: (2,3,4), (0,3,5), (0,2,6), (0,1,10), (1,3,15)

Step 2: Initialize Union-Find
parent = [0, 1, 2, 3, 4, 5]  // Each node is its own parent
rank = [0, 0, 0, 0, 0, 0]    // All ranks are 0

Step 3: Process edges in sorted order

Edge (2,3,4):
- find(2) = 2, find(3) = 3
- 2 ≠ 3, so no cycle
- Union(2,3), MST weight = 4
- parent = [0, 1, 3, 3, 4, 5], Components: {0}, {1}, {2,3}, {4}, {5}

Edge (0,3,5):
- find(0) = 0, find(3) = 3
- 0 ≠ 3, so no cycle
- Union(0,3), MST weight = 4 + 5 = 9
- Components: {0,2,3}, {1}, {4}, {5}

Edge (0,2,6):
- find(0) = 3, find(2) = 3 (due to path compression)
- 3 = 3, so adding this edge would create cycle
- Skip this edge

Edge (0,1,10):
- find(0) = 3, find(1) = 1
- 3 ≠ 1, so no cycle
- Union(0,1), MST weight = 9 + 10 = 19
- Components: {0,1,2,3}, {4}, {5}

Edge (1,3,15):
- find(1) = 3, find(3) = 3
- 3 = 3, so adding this edge would create cycle
- Skip this edge

Final MST:
- Edges: (2,3), (0,3), (0,1)
- Total weight: 4 + 5 + 10 = 19
- Note: Vertices 4 and 5 are isolated (not connected to main component)

IMPORTANT NOTE:
==============
The given graph is NOT connected! Vertices 4 and 5 are isolated.
For a proper MST, all vertices should be connected.
The algorithm returns weight 19 for the MST of the connected component {0,1,2,3}.

KEY CONCEPTS:
============
1. Greedy Choice: Always pick the minimum weight edge that doesn't create cycle
2. Cycle Detection: Union-Find efficiently detects cycles in nearly O(1) time
3. Optimal Substructure: MST property ensures global optimum
4. Cut Property: Any minimum weight edge crossing a cut is in some MST

Time Complexity: O(E log E) - dominated by sorting
Space Complexity: O(V) - for Union-Find structure

Applications:
- Network design (minimum cost connectivity)
- Circuit design (minimum wire length)
- Clustering algorithms
- Approximation algorithms for TSP
*/