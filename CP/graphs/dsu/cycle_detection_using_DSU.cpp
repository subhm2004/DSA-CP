#include <iostream>
#include <unordered_map>
#include <list>
#include <tuple>

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

    // Check if the graph contains a cycle
    bool hasCycle()
    {
        UnionFind uf(adjList.size());
        for (auto &edge : edges)
        {
            int u = get<0>(edge);
            int v = get<1>(edge);
            if (uf.find(u) == uf.find(v))
            {
                return true; // Cycle detected
            }
            uf.unionByRank(u, v);
        }
        return false; // No cycle
    }
};

int main()
{
    Graph g;

    // Adding edges to the graph
    g.addEdge(0, 1, 10, 0);
    g.addEdge(0, 2, 6, 0);
    g.addEdge(0, 3, 5, 0);
    g.addEdge(1, 3, 15, 0);
    g.addEdge(2, 3, 4, 0);

    // Cycle Detection
    if (g.hasCycle())
    {
        cout << "Graph contains a cycle" << endl;
    }
    else
    {
        cout << "Graph does not contain a cycle" << endl;
    }

    return 0;
}
