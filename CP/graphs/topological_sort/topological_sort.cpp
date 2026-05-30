#include <iostream>      // For input/output operations (cout, cin)
#include <vector>        // For dynamic arrays (not used in this code)
#include <unordered_map> // For hash map data structure
#include <list>          // For linked list to store adjacency list
#include <stack>         // For stack data structure used in topological sort
using namespace std;

// Template class for Graph - can work with any data type T (int, char, string, etc.)
template <typename T>
class Graph
{
public:
    // Adjacency list representation of graph
    // Key: vertex, Value: list of adjacent vertices
    unordered_map<T, list<T>> adjList;

    // Function to add an edge between two vertices
    // Parameters:
    // u: source vertex
    // v: destination vertex
    // direction: 0 for undirected edge, 1 for directed edge
    void addEdge(T u, T v, bool direction)
    {
        // Add edge from u to v
        adjList[u].push_back(v);

        // If undirected graph (direction = 0), add edge from v to u as well
        if (direction == 0)
        {
            adjList[v].push_back(u);
        }
    }

    // Function to print the adjacency list representation of the graph
    void printAdjacencyList()
    {
        // Iterate through each vertex in the adjacency list
        for (auto node : adjList)
        {
            cout << node.first << "-> "; // Print vertex

            // Print all neighbors of current vertex
            for (auto neighbour : node.second)
            {
                cout << neighbour << ", ";
            }
            cout << endl;
        }
    }

    // DFS-based topological sort function
    // Parameters:
    // src: current vertex being processed
    // visited: map to track visited vertices
    // ans: stack to store topologically sorted vertices
    void topoSortDfs(int src, unordered_map<int, bool> &visited, stack<int> &ans)
    {
        // Mark current vertex as visited
        visited[src] = true;

        // Recursively visit all unvisited neighbors
        for (auto neighbour : adjList[src])
        {
            if (!visited[neighbour])
            {
                // Recursive call for unvisited neighbor
                topoSortDfs(neighbour, visited, ans);
            }
        }

        // After visiting all neighbors, push current vertex to stack
        // This ensures vertices are stored in reverse topological order
        ans.push(src);
    }
};

int main()
{
    // Create a graph object for integer vertices
    Graph<int> g;

    // Number of vertices in the graph
    int n = 4;

    // Add directed edges to create a Directed Acyclic Graph (DAG)
    g.addEdge(0, 1, 1); // Edge from 0 to 1
    g.addEdge(1, 2, 1); // Edge from 1 to 2
    g.addEdge(2, 5, 1); // Edge from 2 to 5 (Note: vertex 5 is not in range 0-3)
    g.addEdge(3, 4, 1); // Edge from 3 to 4 (Note: vertex 4 is not in range 0-3)

    // Initialize data structures for topological sort
    unordered_map<int, bool> visited; // To track visited vertices
    stack<int> ans;                   // To store result in reverse topological order

    // Perform DFS from each unvisited vertex
    // This handles disconnected components in the graph
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            // Call DFS-based topological sort for unvisited vertex
            g.topoSortDfs(i, visited, ans);
        }
    }

    // Print the topological sort result
    cout << "Topological Sort using DFS: ";
    while (!ans.empty())
    {
        cout << ans.top() << " "; // Print top element
        ans.pop();                // Remove top element
    }
    cout << endl;

    return 0;
}

/*
ALGORITHM EXPLANATION:
===================

Topological Sorting:
- Linear ordering of vertices in a Directed Acyclic Graph (DAG)
- For every directed edge (u,v), vertex u comes before v in the ordering
- Only possible for DAGs (graphs with no cycles)

DFS-based Approach:
1. Start DFS from any unvisited vertex
2. Recursively visit all neighbors
3. After visiting all neighbors, add current vertex to stack
4. The stack will contain vertices in reverse topological order

Time Complexity: O(V + E) where V = vertices, E = edges
Space Complexity: O(V) for visited map and recursion stack

POTENTIAL ISSUES IN THIS CODE:
============================
1. Variable 'n' is set to 4, but edges include vertices 4 and 5
2. This may cause issues as loop only iterates from 0 to 3
3. Consider setting n = 6 or adjusting the edges accordingly

SAMPLE OUTPUT (with current edges):
==================================
Topological Sort using DFS: 3 0 1 2

Note: Vertices 4 and 5 won't be included in the sort due to the loop limitation
*/