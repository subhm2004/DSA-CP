#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <queue>
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

    bool isBipartiteBFS(int src, vector<int> &color)
    {
        queue<int> q;
        q.push(src);
        color[src] = 0; // Color the starting node with 0

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            for (int nbr : adjList[node])
            {
                if (color[nbr] == -1)
                { // If uncolored, assign opposite color
                    color[nbr] = 1 - color[node];
                    q.push(nbr);
                }
                else if (color[nbr] == color[node])
                { // If same color as parent, not bipartite
                    return false;
                }
            }
        }
        return true;
    }

    bool isBipartite()
    {
        vector<int> color(V, -1); // -1 means uncolored

        for (int i = 0; i < V; i++)
        {
            if (color[i] == -1)
            { // Check all components (important for disconnected graphs)
                if (!isBipartiteBFS(i, color))
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
    for (auto edge : edges)
    {
        g.addEdge(edge.first, edge.second);
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
