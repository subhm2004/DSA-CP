#include <iostream>      // For input/output operations (cout, cin)
#include <vector>        // For dynamic arrays
#include <unordered_map> // For hash map data structure (efficient key-value storage)
#include <list>          // For linked list to store adjacency lists
#include <algorithm>     // For min function
using namespace std;

/**
 * Graph class for finding Bridges using Tarjan's Bridge-Finding Algorithm
 *
 * BRIDGE DEFINITION:
 * A bridge (or cut edge) is an edge in a connected graph whose removal
 * increases the number of connected components. In other words, removing
 * a bridge disconnects the graph.
 *
 * ALGORITHM OVERVIEW:
 * Tarjan's algorithm uses DFS (Depth-First Search) with two key concepts:
 * 1. Discovery Time: When a vertex is first visited during DFS
 * 2. Low Time: Lowest discovery time reachable from the vertex's subtree
 *
 * BRIDGE CONDITION:
 * An edge (u,v) is a bridge if: low[v] > disc[u]
 * This means vertex v cannot reach vertex u or any ancestor of u
 * through any path other than the direct edge (u,v)
 *
 * TIME COMPLEXITY: O(V + E) where V = vertices, E = edges
 * SPACE COMPLEXITY: O(V) for arrays and recursion stack
 *
 * REAL-WORLD APPLICATIONS:
 * - Network reliability analysis (critical network links)
 * - Transportation systems (critical roads/bridges)
 * - Social network analysis (critical relationships)
 * - Circuit design (critical connections)
 * - Internet infrastructure (critical backbone connections)
 */
class Graph
{
public:
    // Adjacency list representation using hash map
    // Key: vertex number, Value: list of adjacent vertices
    // This allows efficient storage for sparse graphs and handles non-sequential vertex numbering
    unordered_map<int, list<int>> adjList;

    /**
     * Add an edge to the graph
     *
     * @param u: source vertex
     * @param v: destination vertex
     * @param direction: 0 for directed graph, 1 for undirected graph
     *
     * For bridge finding, we typically work with undirected graphs
     * since bridges are more meaningful in undirected contexts
     */
    void addEdge(int u, int v, bool direction)
    {
        // Always add edge from u to v
        adjList[u].push_back(v);

        if (direction == 1)
        {
            // For undirected graph, also add edge from v to u
            // This creates bidirectional connectivity
            adjList[v].push_back(u);
        }
    }

    /**
     * DFS utility function to find bridges using Tarjan's Algorithm
     *
     * CORE ALGORITHM LOGIC:
     * 1. Assign discovery time and low time to current vertex
     * 2. Explore all unvisited neighbors recursively
     * 3. Update low time based on what's reachable from subtree
     * 4. Check bridge condition: if low[neighbor] > disc[current], edge is bridge
     * 5. Handle back edges by updating low time with discovery time
     *
     * BRIDGE DETECTION PRINCIPLE:
     * If removing edge (current, neighbor) would disconnect neighbor's subtree
     * from current vertex and its ancestors, then it's a bridge.
     *
     * @param currentNode: vertex currently being processed in DFS
     * @param parentNode: parent of currentNode in DFS tree (-1 for root)
     * @param timer: global counter for assigning discovery times (passed by reference)
     * @param discoveryTime: array storing when each vertex was first discovered
     * @param lowestTime: array storing lowest discovery time reachable from each vertex
     * @param visited: hash map tracking which vertices have been visited
     * @param ans: vector storing all discovered bridges as vertex pairs
     */
    void find_Bridges_DFS(
        int currentNode,
        int parentNode,
        int &timer,
        vector<int> &discoveryTime,
        vector<int> &lowestTime,
        unordered_map<int, bool> &visited,
        vector<pair<int, int>> &ans)
    {
        // STEP 1: Mark current vertex as visited
        visited[currentNode] = true;

        // STEP 2: Initialize discovery and low times
        // Discovery time = when vertex is first encountered
        // Low time = lowest discovery time reachable from this vertex's subtree
        discoveryTime[currentNode] = timer;
        lowestTime[currentNode] = timer;
        timer++; // Increment global timer for next vertex

        // STEP 3: Explore all adjacent vertices (neighbors)
        for (auto neighbor : adjList[currentNode])
        {
            // STEP 3a: Skip parent to avoid false back edge detection
            // In undirected graphs, parent is always adjacent, but it's not a meaningful back edge
            if (neighbor == parentNode)
            {
                continue; // Skip the parent node
            }

            if (!visited[neighbor])
            {
                // STEP 3b: Tree edge - neighbor is unvisited
                // This creates a tree edge in the DFS spanning tree

                // Recursively explore the unvisited neighbor
                find_Bridges_DFS(neighbor, currentNode, timer, discoveryTime, lowestTime, visited, ans);

                // STEP 3c: Update low time after returning from recursion
                // Low time represents the earliest discovered vertex reachable
                // from the subtree rooted at currentNode
                lowestTime[currentNode] = min(lowestTime[currentNode], lowestTime[neighbor]);

                // STEP 3d: BRIDGE DETECTION - Check the bridge condition
                // If low[neighbor] > disc[currentNode], then edge (currentNode, neighbor) is a bridge
                //
                // EXPLANATION:
                // - If neighbor's subtree can reach currentNode or its ancestors,
                //   then low[neighbor] <= disc[currentNode]
                // - If low[neighbor] > disc[currentNode], it means neighbor's subtree
                //   cannot reach currentNode through any other path
                // - Therefore, removing edge (currentNode, neighbor) would disconnect
                //   neighbor's subtree from the rest of the graph
                if (lowestTime[neighbor] > discoveryTime[currentNode])
                {
                    // Edge (currentNode, neighbor) is a bridge!
                    // Add it to the answer list
                    ans.push_back({currentNode, neighbor});
                }
            }
            else
            {
                // STEP 3e: Back edge - neighbor is already visited
                // This creates a back edge that can help reach ancestors

                // Update low time with discovery time of the visited neighbor
                // This represents an alternative path back to an ancestor
                // Note: We use discoveryTime[neighbor], not lowestTime[neighbor]
                // because we want the actual time when neighbor was discovered
                lowestTime[currentNode] = min(lowestTime[currentNode], discoveryTime[neighbor]);
            }
        }

        // STEP 4: After processing all neighbors, currentNode's low time is finalized
        // It now represents the lowest discovery time reachable from currentNode's subtree
    }

    /**
     * Main function to find all bridges in the graph
     * Handles disconnected graphs by starting DFS from each unvisited vertex
     *
     * @param n: total number of vertices in the graph (0 to n-1)
     *
     * ALGORITHM STEPS:
     * 1. Initialize data structures for tracking discovery times, low times, and visited status
     * 2. Handle disconnected components by iterating through all vertices
     * 3. Start DFS from each unvisited vertex (handles forest of DFS trees)
     * 4. Output all discovered bridges
     *
     * HANDLING DISCONNECTED GRAPHS:
     * The graph might have multiple connected components, so we need to
     * start DFS from each unvisited vertex to ensure complete coverage
     */
    void find_Bridges(int n)
    {
        // STEP 1: Initialize data structures

        // Discovery time array: stores when each vertex was first visited
        // -1 indicates unvisited vertex
        vector<int> discoveryTime(n, -1);

        // Low time array: stores lowest discovery time reachable from each vertex
        // -1 indicates unprocessed vertex
        vector<int> lowestTime(n, -1);

        // Visited hash map: tracks which vertices have been explored
        // Using unordered_map for O(1) average lookup time
        unordered_map<int, bool> visited;

        // Global timer: assigns unique discovery times to vertices
        // Incremented each time a new vertex is discovered
        int timer = 0;

        // Answer vector: stores all discovered bridges as pairs of vertices
        vector<pair<int, int>> ans;

        // STEP 2: Handle disconnected graph components
        // Iterate through all possible vertex numbers (0 to n-1)
        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                // Start DFS from unvisited vertex i
                // Parent is -1 (indicating root of DFS tree)
                // This ensures we explore each connected component
                find_Bridges_DFS(i, -1, timer, discoveryTime, lowestTime, visited, ans);
            }
        }

        // STEP 3: Output all discovered bridges
        cout << "Bridges in the graph are:" << endl;
        if (ans.empty())
        {
            cout << "No bridges found in the graph." << endl;
        }
        else
        {
            for (auto bridge : ans)
            {
                cout << bridge.first << " -- " << bridge.second << endl;
            }
        }
    }
};

/**
 * Main function - Entry point of the program
 * Handles user input and demonstrates bridge finding algorithm
 */
int main()
{
    // Create a graph object
    Graph g;

    int n, m; // n = number of vertices, m = number of edges

    // Get graph size from user
    cout << "Enter the number of nodes and edges: ";
    cin >> n >> m;

    // Input validation
    if (n <= 0 || m < 0)
    {
        cout << "Invalid input! Number of nodes should be positive, edges non-negative." << endl;
        return 1;
    }

    // Get edges from user
    cout << "Enter the edges (u v): " << endl;
    cout << "Note: Vertices should be numbered from 0 to " << (n - 1) << endl;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        // Input validation for vertex numbers
        if (u < 0 || u >= n || v < 0 || v >= n)
        {
            cout << "Warning: Edge (" << u << ", " << v << ") contains invalid vertex numbers!" << endl;
            cout << "Valid range: 0 to " << (n - 1) << endl;
        }

        // Add edge to graph as undirected (direction = 1)
        g.addEdge(u, v, 1);
    }

    cout << "\n=== BRIDGE FINDING ALGORITHM EXECUTION ===" << endl;

    // Execute bridge finding algorithm and display results
    g.find_Bridges(n);

    return 0;
}

/*
DETAILED EXAMPLE EXECUTION:
==========================

Example Input:
Nodes: 5, Edges: 5
Edges: (0,1), (0,2), (1,2), (1,3), (3,4)

Graph Visualization:
    0
   / \
  1---2
  |
  3---4

Adjacency List:
0: [1, 2]
1: [0, 2, 3]
2: [0, 1]
3: [1, 4]
4: [3]

DFS EXECUTION TRACE:
===================

Starting DFS from vertex 0 (timer = 0):

Visit 0: disc[0] = 0, low[0] = 0, timer = 1
├─ Explore neighbor 1:
   Visit 1: disc[1] = 1, low[1] = 1, timer = 2
   ├─ Skip neighbor 0 (parent)
   ├─ Explore neighbor 2:
      Visit 2: disc[2] = 2, low[2] = 2, timer = 3
      ├─ Neighbor 0 already visited (back edge)
      ├─ low[2] = min(2, disc[0]) = min(2, 0) = 0
      └─ Skip neighbor 1 (parent)
      Return to 1: low[1] = min(1, low[2]) = min(1, 0) = 0
      Check bridge: low[2] > disc[1]? → 0 > 1? NO
   └─ Explore neighbor 3:
      Visit 3: disc[3] = 3, low[3] = 3, timer = 4
      ├─ Skip neighbor 1 (parent)
      └─ Explore neighbor 4:
         Visit 4: disc[4] = 4, low[4] = 4, timer = 5
         └─ Skip neighbor 3 (parent)
         Return to 3: low[3] = min(3, low[4]) = min(3, 4) = 3
         Check bridge: low[4] > disc[3]? → 4 > 3? YES → BRIDGE (3,4)
      Return to 1: low[1] = min(0, low[3]) = min(0, 3) = 0
      Check bridge: low[3] > disc[1]? → 3 > 1? YES → BRIDGE (1,3)
└─ Return to 0: low[0] = min(0, low[1]) = min(0, 0) = 0
   Check bridge: low[1] > disc[0]? → 0 > 0? NO

FINAL RESULTS:
=============
Bridges found: (3,4), (1,3)

EXPLANATION:
- Bridge (3,4): Removing this edge isolates vertex 4
- Bridge (1,3): Removing this edge separates {0,1,2} from {3,4}
- Edge (0,1): Not a bridge because of alternative path 0→2→1
- Edge (0,2): Not a bridge because of alternative path 0→1→2
- Edge (1,2): Not a bridge because of alternative paths through 0

COMPLEXITY ANALYSIS:
===================
Time Complexity: O(V + E)
- Each vertex is visited exactly once: O(V)
- Each edge is examined exactly twice (once from each endpoint): O(E)
- Overall: O(V + E)

Space Complexity: O(V)
- Discovery time array: O(V)
- Low time array: O(V)
- Visited hash map: O(V)
- Recursion stack depth: O(V) in worst case
- Overall: O(V)

PRACTICAL APPLICATIONS:
======================
1. Network Infrastructure: Identify critical network links whose failure would partition the network
2. Transportation: Find critical roads/bridges whose closure would disconnect regions
3. Social Networks: Identify relationships critical for information flow
4. Distributed Systems: Find critical connections for system reliability
5. Circuit Design: Identify critical wires whose removal breaks functionality
*/