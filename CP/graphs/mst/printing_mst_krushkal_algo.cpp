#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

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
    vector<tuple<int, int, int>> edges; // Store edges as tuples (u, v, weight)

    // Add edge to the graph
    void addEdge(int u, int v, int weight)
    {
        edges.push_back({u, v, weight});
    }

    // Kruskal's Algorithm to find Minimum Spanning Tree (MST)
    int kruskalMST(int n)
    {
        // Sort edges by weight using lambda function
        sort(edges.begin(), edges.end(), [](const tuple<int, int, int> &a, const tuple<int, int, int> &b)
             {
                 return get<2>(a) < get<2>(b); // Compare by weight (get<2>)
             });

        UnionFind uf(n);
        int mstWeight = 0;

        cout << "Edges in the Minimum Spanning Tree:" << endl;

        for (auto &edge : edges)
        {
            int u = get<0>(edge);
            int v = get<1>(edge);
            int weight = get<2>(edge);

            if (uf.find(u) != uf.find(v))
            {
                uf.unionByRank(u, v);                                             // If no cycle, unite the sets
                mstWeight += weight;                                              // Add edge to MST
                cout << u << " - " << v << " (Weight: " << weight << ")" << endl; // Print the edge
            }
        }

        return mstWeight;
    }
};

int main()
{
    Graph g;
    int n = 6; // Number of nodes

    // Adding weighted edges for MST
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);

    // Kruskal's Algorithm
    int mstWeight = g.kruskalMST(n);
    cout << "Total weight of the Minimum Spanning Tree: " << mstWeight << endl;

    return 0;
}
