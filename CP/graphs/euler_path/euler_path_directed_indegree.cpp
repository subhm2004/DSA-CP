#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// DIRECTED GRAPH — EULERIAN PATH / CIRCUIT CHECK (In-Degree / Out-Degree)
// ────────────────────────────────────────────────────────────────────────────
// Eulerian Path  : har edge exactly ek baar traverse ho (start != end allowed)
// Eulerian Circuit: path jisme start = end bhi ho sakta hai
//
// Directed graph ke liye conditions:
//   1) Underlying graph connected hona chahiye (edges wale nodes)
//   2) Path  ke liye: sab nodes me inDeg == outDeg, EXCEPT
//      exactly 1 node jahan outDeg = inDeg + 1 (START)
//      exactly 1 node jahan inDeg  = outDeg + 1 (END)
//      ya phir sab equal hon (circuit case)
//   3) Circuit ke liye: har node pe inDeg == outDeg
// ════════════════════════════════════════════════════════════════════════════

class Graph
{
public:
    unordered_map<int, list<int>> adjList;
    unordered_map<int, int> inDegree, outDegree;

    // ── addEdge: directed edge u -> v daalo, degrees update karo ───────────
    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
        outDegree[u]++;
        inDegree[v]++;
    }

    // ── calculateDegrees: adjList se in/out degree dobara compute karo ─────
    // addEdge pe already update ho chuka hota hai; ye function recompute ke liye
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

    // ── printAdjList: debugging ke liye adjacency list print ─────────────────
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

    // ── DFS: connectivity check — saare reachable nodes visit karo ───────────
    void DFS(int node, unordered_map<int, bool> &visited)
    {
        visited[node] = true;
        for (int nbr : adjList[node])
        {
            if (!visited[nbr])
                DFS(nbr, visited);
        }
    }

    // ── isConnected: kya saare "active" nodes ek component me hain? ─────────
    // Sirf un nodes ko consider karo jinke paas outgoing edge hai ya inDeg > 0
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
            return true;  // koi edge hi nahi — trivially connected

        DFS(startNode, visited);

        for (auto &node : adjList)
        {
            if (!visited[node.first] && (!node.second.empty() || inDegree[node.first] > 0))
                return false;
        }

        return true;
    }

    // ── hasEulerianPath: degree conditions + connectivity check ─────────────
    bool hasEulerianPath()
    {
        // Step 1: pehle connectivity check — sab edge-wale nodes ek component me?
        if (!isConnected())
            return false;

        // Step 2: har node ka in/out degree imbalance count karo
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

        // Step 3: circuit (0,0) ya path (1,1) imbalance allowed
        return (startNodes == 0 && endNodes == 0) || (startNodes == 1 && endNodes == 1);
    }

    // ── hasEulerianCircuit: sab nodes pe inDeg == outDeg hona chahiye ───────
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

    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 0);
    g.addEdge(1, 3);

    g.calculateDegrees();

    cout << "Graph Adjacency List:\n";
    g.printAdjList();

    cout << "\nEulerian Path: " << (g.hasEulerianPath() ? "Yes" : "No") << endl;
    cout << "Eulerian Circuit: " << (g.hasEulerianCircuit() ? "Yes" : "No") << endl;

    return 0;
}
