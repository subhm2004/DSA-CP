#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// DIRECTED EULERIAN PATH / CIRCUIT — CHECK + PRINT (Hierholzer's Algorithm)
// ────────────────────────────────────────────────────────────────────────────
// Pehle existence check (in/out degree rules), phir Hierholzer se actual path
// construct karo using stack + edge removal from temp adjacency list.
//
// Hierholzer idea (directed):
//   - Start node = jahan outDeg - inDeg == 1 (path case), warna koi bhi node
//   - Stack pe push karo, jab tak outgoing edges hain next pe jao
//   - Jab koi edge nahi bachi, node ko path me daalo (backtrack)
//   - Path reverse karke sahi order me print karo
// ════════════════════════════════════════════════════════════════════════════

class Graph
{
public:
    unordered_map<int, list<int>> adjList;
    unordered_map<int, int> inDegree, outDegree;

    // ── addEdge: directed edge u -> v ──────────────────────────────────────
    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
        outDegree[u]++;
        inDegree[v]++;
    }

    // ── calculateDegrees: adjList traverse karke degrees recompute ───────────
    void calculateDegrees()
    {
        // Step 1: purane degree maps clear karo
        inDegree.clear();
        outDegree.clear();

        // Step 2: adjList traverse karke har edge ke liye in/out count badhao
        for (auto &i : adjList)
        {
            int src = i.first;
            for (int nbr : i.second)
            {
                outDegree[src]++;
                inDegree[nbr]++;
            }
        }
    }

    // ── DFS: connectivity ke liye ──────────────────────────────────────────
    void DFS(int node, unordered_map<int, bool> &visited)
    {
        visited[node] = true;
        for (int nbr : adjList[node])
        {
            if (!visited[nbr])
                DFS(nbr, visited);
        }
    }

    // ── isConnected: saare edge-wale nodes ek component me? ────────────────
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

    // ── hasEulerianPath: in/out degree imbalance check ───────────────────────
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

    // ── hasEulerianCircuit: har node pe inDeg == outDeg ──────────────────────
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

    // ── findEulerianPathOrCircuit: check + Hierholzer se path print ────────
    void findEulerianPathOrCircuit()
    {
        calculateDegrees();

        if (hasEulerianCircuit())
        {
            cout << "Eulerian Circuit Exists." << endl;
        }
        else if (hasEulerianPath())
        {
            cout << "Eulerian Path Exists." << endl;
        }
        else
        {
            cout << "No Eulerian Path or Circuit exists." << endl;
            return;
        }

        unordered_map<int, list<int>> tempAdj = adjList;
        stack<int> stk;
        vector<int> path;
        int startNode = -1;

        // Path case: jahan outDeg ek zyada hai wahan se shuru karo
        for (auto &node : adjList)
        {
            if (outDegree[node.first] - inDegree[node.first] == 1)
            {
                startNode = node.first;
                break;
            }
        }

        if (startNode == -1)
            startNode = adjList.begin()->first;  // circuit case — koi bhi node

        stk.push(startNode);

        while (!stk.empty())
        {
            int node = stk.top();

            if (!tempAdj[node].empty())
            {
                int next = tempAdj[node].front();
                tempAdj[node].pop_front();  // edge use kar li — hata do
                stk.push(next);
            }
            else
            {
                path.push_back(node);  // dead end — path me add karo
                stk.pop();
            }
        }

        reverse(path.begin(), path.end());  // stack se ulta aaya tha

        cout << "Eulerian Path/Circuit: ";
        for (int node : path)
            cout << node << " ";
        cout << endl;
    }
};

int main()
{
    Graph g;

    vector<pair<int, int>> edges = {
        {0, 1}, {1, 2}, {2, 0}, {1, 3}, {3, 4}, {4, 1}};

    for (auto edge : edges)
    {
        g.addEdge(edge.first, edge.second);
    }

    g.findEulerianPathOrCircuit();

    return 0;
}
