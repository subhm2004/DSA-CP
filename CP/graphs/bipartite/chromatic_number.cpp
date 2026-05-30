#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>

using namespace std;

class Graph
{
public:
    unordered_map<int, list<int>> adjList;
    unordered_map<int, int> degree;
    int vertices;

    Graph(int v)
    {
        vertices = v;
    }

    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Since the graph is undirected
        degree[u]++;
        degree[v]++;
    }

    void printGraph()
    {
        cout << "\nAdjacency List:\n";
        for (auto &node : adjList)
        {
            cout << node.first << " -> ";
            for (int neighbor : node.second)
            {
                cout << neighbor << " ";
            }
            cout << endl;
        }

        cout << "\nDegree of nodes:\n";
        for (auto &node : adjList)
        {
            int v = node.first;
            cout << "Node " << v << ": Degree = " << degree[v] << endl;
        }
    }

    vector<vector<int>> getAdjMatrix()
    {
        vector<vector<int>> graph(vertices, vector<int>(vertices, 0));
        for (auto &node : adjList)
        {
            int u = node.first;
            for (int v : node.second)
            {
                graph[u][v] = 1;
            }
        }
        return graph;
    }
};

bool isSafe(int node, vector<vector<int>> &graph, vector<int> &color, int c)
{
    for (int neighbor = 0; neighbor < graph.size(); neighbor++)
    {
        if (graph[node][neighbor] && color[neighbor] == c) // Adjacent node has the same color
            return false;
    }
    return true;
}

bool graph_Coloring_Util(vector<vector<int>> &graph, int m, vector<int> &color, int node)
{
    if (node == graph.size()) // All nodes colored
        return true;

    for (int c = 1; c <= m; c++)
    {
        if (isSafe(node, graph, color, c))
        {
            color[node] = c;
            if (graph_Coloring_Util(graph, m, color, node + 1))
                return true;
            color[node] = 0; // Backtrack
        }
    }
    return false;
}

void graph_Coloring(Graph &g, int m)
{
    vector<vector<int>> graph = g.getAdjMatrix();
    int n = graph.size();
    vector<int> color(n, 0);

    if (graph_Coloring_Util(graph, m, color, 0))
    {
        cout << "\nGraph can be colored with " << m << " colors:\n";
        for (int i = 0; i < n; i++)
            cout << "Vertex " << i << " -> Color " << color[i] << endl;
    }
    else
    {
        cout << "\nGraph cannot be colored with " << m << " colors.\n";
    }
}

int main()
{
    int n = 6; // Number of vertices (0 to 5)
    int m = 3; // Number of colors

    vector<pair<int, int>> edges = {{0, 1}, {1, 2}, {2, 0}, {1, 3}, {3, 4}, {4, 1}};

    Graph g(n);
    for (auto edge : edges)
    {
        g.addEdge(edge.first, edge.second);
    }

    g.printGraph();
    graph_Coloring(g, m);

    return 0;
}
