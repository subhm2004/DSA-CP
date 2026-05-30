#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
    unordered_map<int, list<int>> adjList;
    unordered_map<int, int> inDegree, outDegree;

    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
        outDegree[u]++;
        inDegree[v]++;
    }

    void calculateDegrees()
    {
        inDegree.clear();
        outDegree.clear();

        for (auto i : adjList)
        {
            int src = i.first;
            for (int nbr : i.second)
            {
                outDegree[src]++;
                inDegree[nbr]++;
            }
        }
    }

    void printAdjList()
    {
        for (auto i : adjList)
        {
            cout << i.first << " -> ";
            for (int j : i.second)
            {
                cout << j << ", ";
            }
            cout << endl;
        }
    }

    // 🔹 DFS for checking connectivity
    void DFS(int node, unordered_map<int, bool> &visited)
    {
        visited[node] = true;
        for (int nbr : adjList[node])
        {
            if (!visited[nbr])
                DFS(nbr, visited);
        }
    }

    // 🔹 Check if Graph is Connected (Ignoring 0 in-degree nodes)
    bool isConnected()
    {
        unordered_map<int, bool> visited;
        int startNode = -1;

        for (auto &node : adjList)
        {
            if (!node.second.empty())
            {
                startNode = node.first;
                break;
            }
        }

        if (startNode == -1)
            return true;

        DFS(startNode, visited);

        for (auto &node : adjList)
        {
            if (!visited[node.first] && (!node.second.empty() || inDegree[node.first] > 0))
                return false;
        }

        return true;
    }

    // 🔹 Check Eulerian Path for Directed Graph
    bool hasEulerianPath()
    {
        if (!isConnected())
            return false;

        int startNodes = 0, endNodes = 0;

        for (auto &node : adjList)
        {
            int u = node.first;
            if (outDegree[u] - inDegree[u] == 1)
                startNodes++;
            else if (inDegree[u] - outDegree[u] == 1)
                endNodes++;
            else if (inDegree[u] != outDegree[u])
                return false;
        }

        return (startNodes == 0 && endNodes == 0) || (startNodes == 1 && endNodes == 1);
    }

    // 🔹 Check Eulerian Circuit for Directed Graph
    bool hasEulerianCircuit()
    {
        if (!isConnected())
            return false;

        for (auto &node : adjList)
        {
            if (inDegree[node.first] != outDegree[node.first])
                return false;
        }

        return true;
    }
};

int main()
{
    Graph g;

    // Example Graph
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 0);
    g.addEdge(1, 3);

    g.calculateDegrees(); // Compute in-degree & out-degree

    cout << "Graph Adjacency List:\n";
    g.printAdjList();

    cout << "\nEulerian Path: " << (g.hasEulerianPath() ? "Yes" : "No") << endl;
    cout << "Eulerian Circuit: " << (g.hasEulerianCircuit() ? "Yes" : "No") << endl;

    return 0;
}
