#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// UNDIRECTED GRAPH — EULERIAN PATH / CIRCUIT CHECK (Degree Condition)
// ────────────────────────────────────────────────────────────────────────────
// Undirected graph me har edge dono taraf count hoti hai adjList me.
//
// Eulerian Path  : connected + exactly 0 ya 2 nodes ka ODD degree
// Eulerian Circuit: connected + saare nodes ka EVEN degree
//
// Odd degree wale 2 nodes = path ka start aur end (circuit me 0 odd)
// ════════════════════════════════════════════════════════════════════════════

class Graph
{
public:
    unordered_map<int, list<pair<int, int>>> adjList;
    unordered_map<int, int> inDegree;  // yahan effectively degree store ho raha hai

    // ── addEdge: undirected edge u — v (dono direction me add) ─────────────
    void addEdge(int u, int v, int wt, bool direction)
    {
        adjList[u].push_back({v, wt});
        adjList[v].push_back({u, wt});
    }

    // ── calculateInDegree: har node ka total degree count karo ─────────────
    void calculateInDegree()
    {
        inDegree.clear();

        for (auto &i : adjList)
        {
            for (auto &nbr : i.second)
            {
                inDegree[nbr.first]++;
            }
        }
    }

    // ── printInDegree: har node ka degree print ────────────────────────────
    void printInDegree()
    {
        cout << "\nIn-Degree of Nodes:\n";
        for (auto &node : inDegree)
        {
            cout << "Node " << node.first << " -> " << node.second << endl;
        }
    }

    // ── printAdjList: weighted adjacency list print ────────────────────────
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

    // ── DFS: connectivity check ────────────────────────────────────────────
    void DFS(int node, unordered_map<int, bool> &visited)
    {
        visited[node] = true;
        for (auto &neighbor : adjList[node])
        {
            if (!visited[neighbor.first])
                DFS(neighbor.first, visited);
        }
    }

    // ── isConnected: saare nodes with edges ek component me? ─────────────
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

    // ── hasEulerianPath: 0 ya 2 odd-degree nodes hon ───────────────────────
    bool hasEulerianPath()
    {
        // Step 1: graph connected hona chahiye
        if (!isConnected())
            return false;

        // Step 2: odd degree wale nodes count karo
        int oddDegreeCount = 0;
        for (auto &node : adjList)
        {
            if (node.second.size() % 2 != 0)
                oddDegreeCount++;
        }

        // Step 3: 0 odd = circuit, 2 odd = path; aur kuch invalid
        return (oddDegreeCount == 0 || oddDegreeCount == 2);
    }

    // ── hasEulerianCircuit: saare degrees even hon ─────────────────────────
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

    g.calculateInDegree();

    cout << "Graph Adjacency List:\n";
    g.printAdjList();

    g.printInDegree();

    cout << "\nEulerian Path: " << (g.hasEulerianPath() ? "Yes" : "No") << endl;
    cout << "Eulerian Circuit: " << (g.hasEulerianCircuit() ? "Yes" : "No") << endl;

    return 0;
}
