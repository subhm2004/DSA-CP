#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
using namespace std;

class GraphColoring
{
    int V;                                 // Number of vertices
    unordered_map<int, list<int>> adjList; // Adjacency list
    vector<int> color;                     // Stores assigned colors

public:
    GraphColoring(int V)
    {
        this->V = V;
        color.resize(V, 0);
    }

    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Undirected graph
    }

    bool isSafe(int v, int c)
    {
        for (int neighbor : adjList[v])
        {
            if (color[neighbor] == c) // If adjacent vertex has same color
                return false;
        }
        return true;
    }

    bool solve(int v, int m)
    {
        if (v == V) // All vertices are colored
            return true;

        for (int c = 1; c <= m; c++)
        {
            if (isSafe(v, c))
            {
                color[v] = c;
                if (solve(v + 1, m)) // Recur for next vertex
                    return true;
                color[v] = 0; // Backtrack
            }
        }
        return false;
    }

    void graphColoring(int m)
    {
        if (solve(0, m))
        {
            cout << "Solution exists! Colors assigned to vertices:\n";
            for (int i = 0; i < V; i++)
                cout << "Vertex " << i << " -> Color " << color[i] << endl;
        }
        else
        {
            cout << "No solution exists with " << m << " colors.\n";
        }
    }
};

int main()
{
    int V = 4; // Number of vertices
    GraphColoring g(V);

    // Edge list as vector of pairs
    vector<pair<int, int>> edges = {
        {0, 1}, {0, 2}, {1, 2}, {1, 3}};

    // Adding edges using loop
    for (auto edge : edges)
    {
        g.addEdge(edge.first, edge.second);
    }

    int m = 3; // Number of colors
    g.graphColoring(m);

    return 0;
}
