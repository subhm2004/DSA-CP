#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <tuple>
#include <algorithm> // for max

using namespace std;

class UnionFind
{
public:
    vector<int> parent;
    vector<int> rank;

    // Constructor to initialize parent and rank vectors
    UnionFind(int n) : parent(n), rank(n, 0)
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = i; // Initially, each node is its own parent
        }
    }

    // Find function with path compression
    int find(int i)
    {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]); // Path compression
    }

    // Union function by rank
    void unionByRank(int x, int y)
    {
        int x_parent = find(x);
        int y_parent = find(y);

        if (x_parent == y_parent)
            return; // They are already in the same set

        // Union by rank: attach the smaller tree under the larger one
        if (rank[x_parent] < rank[y_parent])
        {
            parent[x_parent] = y_parent;
        }
        else if (rank[x_parent] > rank[y_parent])
        {
            parent[y_parent] = x_parent;
        }
        else
        {
            parent[x_parent] = y_parent;
            rank[y_parent]++; // Increase rank of the new root
        }
    }

    // Count the number of connected components
    int countComponents()
    {
        int components = 0;
        for (int i = 0; i < parent.size(); ++i)
        {
            if (parent[i] == i) // A root node
                components++;
        }
        return components;
    }
};

class Graph
{
public:
    unordered_map<int, list<int>> adjList;
    vector<tuple<int, int, int>> edges; // Store edges as tuples (u, v, weight)

    // Add edge to the graph
    void addEdge(int u, int v, int weight, bool direction)
    {
        adjList[u].push_back(v);
        edges.push_back({u, v, weight}); // Add edge to the list
        if (direction == 0)
        {
            adjList[v].push_back(u);
            edges.push_back({v, u, weight}); // Add reverse edge for undirected graph
        }
    }

    // Print the graph's adjacency list
    void printGraph()
    {
        for (auto &entry : adjList)
        {
            cout << entry.first << " -> ";
            for (auto &neighbor : entry.second)
            {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // Find the number of connected components
    int findConnectedComponents()
    {
        // Find the highest node value
        int maxNode = 0;
        for (auto &entry : adjList)
        {
            maxNode = max(maxNode, entry.first);
            for (auto &neighbor : entry.second)
            {
                maxNode = max(maxNode, neighbor);
            }
        }

        // Create UnionFind with size equal to the highest node index + 1
        UnionFind uf(maxNode + 1);

        // Traverse all edges and perform union on connected nodes
        for (auto &edge : edges)
        {
            int u = get<0>(edge);
            int v = get<1>(edge);
            uf.unionByRank(u, v);
        }

        // Return the number of connected components
        return uf.countComponents();
    }
};

int main()
{
    Graph g;

    // Adding edges for connected components check

    // Component 1: 0 <-> 1 <-> 2
    g.addEdge(0, 1, 1, 0);
    g.addEdge(1, 2, 1, 0);

    // Component 2: 3 <-> 4
    g.addEdge(3, 4, 1, 0);

    // Component 3: 5 <-> 6
    g.addEdge(5, 6, 1, 0);

    // Component 4: 7 (isolated node)

    // Component 5: 8 <-> 9 <-> 10
    g.addEdge(8, 9, 1, 0);
    g.addEdge(9, 10, 1, 0);

    // Component 6: 11 <-> 12
    g.addEdge(11, 12, 1, 0);

    // Component 7: 13 (isolated node)

    // Component 8: 14 <-> 15 <-> 16
    g.addEdge(14, 15, 1, 0);
    g.addEdge(15, 16, 1, 0);

    // Printing the graph's adjacency list
    cout << "Graph's Adjacency List:" << endl;
    g.printGraph();

    // Finding and printing the number of connected components
    int components = g.findConnectedComponents();
    cout << "Number of connected components: " << components << endl;

    return 0;
}
