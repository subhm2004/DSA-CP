#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
    unordered_map<int, list<pair<int, int>>> adjList;
    unordered_map<int, int> inDegree; // Store in-degree

    void addEdge(int u, int v, int wt, bool direction)
    {
        adjList[u].push_back({v, wt});
        adjList[v].push_back({u, wt}); // Undirected graph ke liye
    }

    void calculateInDegree()
    {
        inDegree.clear(); // Reset previous data

        for (auto &i : adjList)
        {
            for (auto &nbr : i.second)
            {
                inDegree[nbr.first]++; // Har connected node ka degree badhao
            }
        }
    }

    void printInDegree()
    {
        cout << "\nIn-Degree of Nodes:\n";
        for (auto &node : inDegree)
        {
            cout << "Node " << node.first << " -> " << node.second << endl;
        }
    }

    void printAdjList()
    {
        for (auto &i : adjList)
        {
            cout << i.first << " -> ";
            for (auto &j : i.second)
            {
                cout << "(" << j.first << ", " << j.second << "), ";
            }
            cout << endl;
        }
    }

    void DFS(int node, unordered_map<int, bool> &visited)
    {
        visited[node] = true;
        for (auto &neighbor : adjList[node])
        {
            if (!visited[neighbor.first])
                DFS(neighbor.first, visited);
        }
    }

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
            if (!visited[node.first] && !node.second.empty())
                return false;
        }

        return true;
    }

    bool hasEulerianPath()
    {
        if (!isConnected())
            return false;

        int oddDegreeCount = 0;

        for (auto &node : adjList)
        {
            if (node.second.size() % 2 != 0)
                oddDegreeCount++;
        }

        return (oddDegreeCount == 0 || oddDegreeCount == 2);
    }

    bool hasEulerianCircuit()
    {
        if (!isConnected())
            return false;

        for (auto &node : adjList)
        {
            if (node.second.size() % 2 != 0)
                return false;
        }

        return true;
    }
};

int main()
{
    Graph g;

    g.addEdge(0, 1, 1, 1);
    g.addEdge(1, 2, 1, 1);
    g.addEdge(2, 3, 1, 1);
    g.addEdge(3, 0, 1, 1);
    g.addEdge(1, 3, 1, 1);

    g.calculateInDegree(); // Compute in-degree after edges are added

    cout << "Graph Adjacency List:\n";
    g.printAdjList();

    g.printInDegree(); // Print in-degree

    cout << "\nEulerian Path: " << (g.hasEulerianPath() ? "Yes" : "No") << endl;
    cout << "Eulerian Circuit: " << (g.hasEulerianCircuit() ? "Yes" : "No") << endl;

    return 0;
}
