#include <iostream>      // For input/output operations (cout, cin)
#include <vector>        // For dynamic arrays
#include <unordered_map> // For hash map data structure
#include <list>          // For linked list to store adjacency lists
#include <algorithm>     // For min function
using namespace std;

/**
 * Graph class for finding Bridges and Articulation Points
 * Using Tarjan's Algorithm based on DFS
 *
 * Key Concepts:
 * - Bridge: An edge whose removal increases the number of connected components
 * - Articulation Point (Cut Vertex): A vertex whose removal increases connected components
 * - Discovery Time: When a vertex is first visited during DFS
 * - Low Time: Lowest discovery time reachable from the subtree rooted at this vertex
 *
 * Applications:
 * - Network reliability analysis
 * - Finding critical connections in infrastructure
 * - Social network analysis
 * - Circuit design and fault tolerance
 */
class Graph
{
public:
    // Adjacency list representation using hash map
    // Key: vertex, Value: list of adjacent vertices
    unordered_map<int, list<int>> adjList;

    /**
     * Add an edge to the graph
     * @param u: source vertex
     * @param v: destination vertex
     * @param direction: 0 for directed, 1 for undirected graph
     *
     * For undirected graphs, we add both u->v and v->u edges
     */
    void addEdge(int u, int v, bool direction)
    {
        // Add edge from u to v
        adjList[u].push_back(v);

        if (direction == 1)
        {
            // Undirected graph: also add edge from v to u
            adjList[v].push_back(u);
        }
    }

    /**
     * DFS utility function to find Articulation Points using Tarjan's Algorithm
     *
     * Core Logic:
     * 1. For root node: articulation point if it has > 1 children in DFS tree
     * 2. For non-root node: articulation point if removal disconnects some part
     *
     * Articulation Point Conditions:
     * - Root with multiple children in DFS tree
     * - Non-root where low[child] >= disc[current] (child can't reach ancestors)
     *
     * @param currentNode: current vertex being processed
     * @param parentNode: parent of current vertex in DFS tree (-1 for root)
     * @param timer: global timer for discovery times (passed by reference)
     * @param discoveryTime: array storing discovery time of each vertex
     * @param lowestTime: array storing lowest reachable discovery time
     * @param visited: tracks which vertices have been visited
     * @param articulation_Points: stores which vertices are articulation points
     * @param childCount: number of children of current node in DFS tree
     */
    void find_Articulation_Points_DFS(
        int currentNode,
        int parentNode,
        int &timer,
        vector<int> &discoveryTime,
        vector<int> &lowestTime,
        unordered_map<int, bool> &visited,
        unordered_map<int, bool> &articulation_Points,
        int &childCount)
    {
        // Mark current node as visited
        visited[currentNode] = true;

        // Set discovery and low time for current node
        discoveryTime[currentNode] = timer;
        lowestTime[currentNode] = timer;
        timer++; // Increment global timer

        // Initialize child count for current node
        childCount = 0;

        // Traverse all adjacent vertices (neighbors)
        for (auto neighbor : adjList[currentNode])
        {
            // Skip the parent to avoid going back in undirected graph
            if (neighbor == parentNode)
            {
                continue; // Skip the parent node
            }

            if (!visited[neighbor])
            {
                // This neighbor is a child in DFS tree
                childCount++;

                // Recursive DFS call for unvisited neighbor
                find_Articulation_Points_DFS(neighbor, currentNode, timer,
                                             discoveryTime, lowestTime, visited,
                                             articulation_Points, childCount);

                // Update low time of current node
                // Low time is minimum of current low time and child's low time
                lowestTime[currentNode] = min(lowestTime[currentNode], lowestTime[neighbor]);

                // ARTICULATION POINT CONDITION 1: Root node with multiple children
                // If current node is root (parent == -1) and has > 1 children
                // Then removing root will disconnect the children
                if (parentNode == -1 && childCount > 1)
                {
                    articulation_Points[currentNode] = true;
                }

                // ARTICULATION POINT CONDITION 2: Non-root node
                // If low time of child >= discovery time of current node
                // This means child cannot reach any ancestor of current node
                // So removing current node will disconnect child from ancestors
                if (parentNode != -1 && lowestTime[neighbor] >= discoveryTime[currentNode])
                {
                    articulation_Points[currentNode] = true;
                }
            }
            else
            {
                // Neighbor is already visited (back edge or cross edge)
                // Update low time with discovery time of visited neighbor
                // This represents a back edge that can reach an ancestor
                lowestTime[currentNode] = min(lowestTime[currentNode], discoveryTime[neighbor]);
            }
        }
    }

    /**
     * Main function to find all articulation points in the graph
     * Handles disconnected components by running DFS from each unvisited vertex
     *
     * @param n: total number of vertices in the graph
     * @param articulation_PointsVector: vector to store found articulation points
     *
     * Time Complexity: O(V + E) where V = vertices, E = edges
     * Space Complexity: O(V) for storing arrays and hash maps
     */
    void findArticulation_Points(int n, vector<int> &articulation_PointsVector)
    {
        // Initialize arrays for discovery and low times
        vector<int> discoveryTime(n, -1); // -1 indicates unvisited
        vector<int> lowestTime(n, -1);    // -1 indicates unprocessed

        // Hash maps for tracking visited status and articulation points
        unordered_map<int, bool> visited;
        unordered_map<int, bool> articulation_PointsMap;

        int timer = 0; // Global timer for assigning discovery times

        // Handle disconnected components
        // Run DFS from each unvisited vertex
        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                int childCount = 0;
                // Start DFS from vertex i with no parent (-1)
                find_Articulation_Points_DFS(i, -1, timer, discoveryTime, lowestTime,
                                             visited, articulation_PointsMap, childCount);
            }
        }

        // Convert hash map results to vector format
        // Extract all vertices marked as articulation points
        for (auto point : articulation_PointsMap)
        {
            if (point.second) // If vertex is marked as articulation point
            {
                articulation_PointsVector.push_back(point.first);
            }
        }
    }

    /**
     * DFS utility function to find Bridges using Tarjan's Algorithm
     *
     * Bridge Condition:
     * An edge (u,v) is a bridge if low[v] > disc[u]
     * This means there's no back edge from v's subtree to u or u's ancestors
     *
     * Core Logic:
     * - If removing edge (u,v) disconnects the graph, it's a bridge
     * - This happens when v cannot reach u's ancestors through any other path
     *
     * @param currentNode: current vertex being processed
     * @param parentNode: parent of current vertex in DFS tree
     * @param timer: global timer for discovery times
     * @param discoveryTime: array storing discovery time of each vertex
     * @param lowestTime: array storing lowest reachable discovery time
     * @param visited: tracks visited vertices
     * @param ans: vector to store found bridges as pairs of vertices
     */
    void findBridgesDFS(
        int currentNode,
        int parentNode,
        int &timer,
        vector<int> &discoveryTime,
        vector<int> &lowestTime,
        unordered_map<int, bool> &visited,
        vector<pair<int, int>> &ans)
    {
        // Mark current node as visited and set times
        visited[currentNode] = true;
        discoveryTime[currentNode] = timer;
        lowestTime[currentNode] = timer;
        timer++; // Increment global timer

        // Explore all adjacent vertices
        for (auto neighbor : adjList[currentNode])
        {
            // Skip parent to avoid false back edge in undirected graph
            if (neighbor == parentNode)
            {
                continue; // Skip the parent node
            }

            if (!visited[neighbor])
            {
                // Tree edge: recursively explore unvisited neighbor
                findBridgesDFS(neighbor, currentNode, timer, discoveryTime,
                               lowestTime, visited, ans);

                // Update low time after exploring child
                // Low time represents earliest visited vertex reachable from subtree
                lowestTime[currentNode] = min(lowestTime[currentNode], lowestTime[neighbor]);

                // BRIDGE CONDITION: Check if edge (currentNode, neighbor) is a bridge
                // If low[neighbor] > disc[currentNode], then edge is a bridge
                // This means neighbor's subtree cannot reach currentNode's ancestors
                if (lowestTime[neighbor] > discoveryTime[currentNode])
                {
                    // Edge (currentNode, neighbor) is a bridge
                    ans.push_back({currentNode, neighbor});
                }
            }
            else
            {
                // Back edge: neighbor is already visited
                // Update low time with discovery time of visited neighbor
                // This creates a path back to an ancestor
                lowestTime[currentNode] = min(lowestTime[currentNode], discoveryTime[neighbor]);
            }
        }
    }

    /**
     * Main function to find all bridges in the graph
     * Handles disconnected components and outputs results
     *
     * @param n: total number of vertices in the graph
     *
     * A bridge is a critical edge whose removal increases connected components
     * Time Complexity: O(V + E)
     * Space Complexity: O(V)
     */
    void findBridges(int n)
    {
        // Initialize data structures
        vector<int> discoveryTime(n, -1); // Discovery times for all vertices
        vector<int> lowestTime(n, -1);    // Lowest reachable times
        unordered_map<int, bool> visited; // Visited status tracker
        int timer = 0;                    // Global timer
        vector<pair<int, int>> ans;       // Store bridge edges

        // Handle disconnected graph components
        // Start DFS from each unvisited vertex
        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                // Start DFS from vertex i (root has no parent: -1)
                findBridgesDFS(i, -1, timer, discoveryTime, lowestTime, visited, ans);
            }
        }

        // Output all discovered bridges
        cout << "Bridges in the graph are:" << endl;
        for (auto bridge : ans)
        {
            cout << bridge.first << " -- " << bridge.second << endl;
        }
    }
};

int main()
{
    Graph g;

    // Predefined test case for demonstration
    int n = 5, m = 5; // Number of vertices and edges
    cout << "Enter the number of nodes and edges: " << endl;
    cout << "Number of nodes: " << n << ", Number of edges: " << m << endl;

    // Test graph structure:
    //     0
    //    / \
    //   1---2
    //   |
    //   3---4
    //
    // Expected bridges: (1,3), (3,4)
    // Expected articulation points: 1, 3

    // Predefined edges for testing
    vector<pair<int, int>> edges = {
        {0, 1}, // Edge 0-1
        {0, 2}, // Edge 0-2
        {1, 2}, // Edge 1-2 (creates triangle with 0-1, 0-2)
        {1, 3}, // Edge 1-3 (bridge: critical connection)
        {3, 4}  // Edge 3-4 (bridge: critical connection)
    };

    cout << "Enter the edges (u v): " << endl;
    for (auto edge : edges)
    {
        int u = edge.first;
        int v = edge.second;
        cout << u << " " << v << endl;
        g.addEdge(u, v, 1); // 1 indicates undirected graph
    }

    // Vector to store discovered articulation points
    vector<int> articulation_PointsVector;

    // Execute algorithms and display results
    cout << "\n=== ALGORITHM EXECUTION ===" << endl;

    // Find and display bridges
    g.findBridges(n);

    // Find articulation points
    g.findArticulation_Points(n, articulation_PointsVector);

    // Display articulation points
    cout << "\nArticulation points in the graph are:" << endl;
    for (int point : articulation_PointsVector)
    {
        cout << point << endl;
    }

    return 0;
}

/*
DETAILED ALGORITHM EXECUTION TRACE:
===================================

Input Graph:
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

DFS EXECUTION FOR BRIDGES:
=========================

Starting DFS from vertex 0:
timer = 0

Visit 0: disc[0] = 0, low[0] = 0, timer = 1
  Visit 1: disc[1] = 1, low[1] = 1, timer = 2
    Visit 2: disc[2] = 2, low[2] = 2, timer = 3
      Back to 0: low[2] = min(2, 0) = 0
    Back to 1: low[1] = min(1, 0) = 0
    Visit 3: disc[3] = 3, low[3] = 3, timer = 4
      Visit 4: disc[4] = 4, low[4] = 4, timer = 5
      Back to 3: low[3] = min(3, 4) = 3
      Check: low[4] > disc[3] → 4 > 3 ✓ → Bridge (3,4)
    Back to 1: low[1] = min(0, 3) = 0
    Check: low[3] > disc[1] → 3 > 1 ✓ → Bridge (1,3)
  Back to 0: low[0] = min(0, 0) = 0

BRIDGES FOUND: (1,3), (3,4)

DFS EXECUTION FOR ARTICULATION POINTS:
=====================================

Starting DFS from vertex 0:
timer = 0, childCount = 0

Visit 0 (root): disc[0] = 0, low[0] = 0, timer = 1
  childCount = 1
  Visit 1: disc[1] = 1, low[1] = 1, timer = 2
    Visit 2: disc[2] = 2, low[2] = 2, timer = 3
      Back to 0: low[2] = min(2, 0) = 0
    Back to 1: low[1] = min(1, 0) = 0
    Check: low[2] >= disc[1] → 0 >= 1 ✗ (not articulation point)

    Visit 3: disc[3] = 3, low[3] = 3, timer = 4
      Visit 4: disc[4] = 4, low[4] = 4, timer = 5
      Back to 3: low[3] = min(3, 4) = 3
      Check: low[4] >= disc[3] → 4 >= 3 ✓ → 3 is articulation point
    Back to 1: low[1] = min(0, 3) = 0
    Check: low[3] >= disc[1] → 3 >= 1 ✓ → 1 is articulation point
  Back to 0: low[0] = min(0, 0) = 0

Root check: childCount = 1 ≤ 1 → 0 is not articulation point

ARTICULATION POINTS FOUND: 1, 3

EXPLANATION:
===========
- Bridge (1,3): Removing this edge disconnects {0,1,2} from {3,4}
- Bridge (3,4): Removing this edge isolates vertex 4
- Articulation Point 1: Removing vertex 1 disconnects 0,2 from 3,4
- Articulation Point 3: Removing vertex 3 isolates vertex 4

TIME & SPACE COMPLEXITY:
=======================
- Time Complexity: O(V + E) - single DFS traversal
- Space Complexity: O(V) - for arrays and recursion stack

APPLICATIONS:
============
1. Network Reliability: Identify critical network connections
2. Social Networks: Find influential people whose removal fragments network
3. Transportation: Identify critical routes/stations
4. Circuit Design: Find critical components for fault tolerance
5. Distributed Systems: Identify critical nodes for system stability
*/