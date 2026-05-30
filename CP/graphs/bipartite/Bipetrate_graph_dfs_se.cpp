#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
using namespace std;

class Graph
{
    int V;                                 // Number of vertices
    unordered_map<int, list<int>> adjList; // Adjacency List

public:
    Graph(int V)
    {
        this->V = V;
    }

    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Undirected graph
    }

    bool isBipartiteDFS(int node, vector<int> &color, int currentColor)
    {
        color[node] = currentColor; // Color current node

        for (int nbr : adjList[node])
        {
            if (color[nbr] == -1)
            { // If not colored
                if (!isBipartiteDFS(nbr, color, 1 - currentColor))
                    return false; // If conflict found, return false
            }
            else if (color[nbr] == currentColor)
            {
                return false; // Same color detected, not bipartite
            }
        }
        return true; // Successfully colored
    }

    bool isBipartite()
    {
        vector<int> color(V, -1); // -1 means uncolored

        for (int i = 0; i < V; i++)
        {
            if (color[i] == -1)
            { // Check all components
                if (!isBipartiteDFS(i, color, 0))
                    return false;
            }
        }
        return true;
    }
};

int main()
{
    int V = 4; // Number of vertices
    Graph g(V);

    // Edge list
    vector<pair<int, int>> edges = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0} // Bipartite graph example
    };

    // Adding edges
    // for (auto edge : edges)
    // {
    //     g.addEdge(edge.first, edge.second);
    // }
    for (auto [u, v] : edges)
    {
        g.addEdge(u, v);
    }

    if (g.isBipartite())
    {
        cout << "The graph is Bipartite.\n";
    }
    else
    {
        cout << "The graph is NOT Bipartite.\n";
    }

    return 0;
}
