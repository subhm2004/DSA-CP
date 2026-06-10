#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// UNDIRECTED GRAPH — EULERIAN PATH PRINT (Hierholzer's Algorithm)
// ────────────────────────────────────────────────────────────────────────────
// Undirected me edge remove karte waqt DONO taraf se hatao (u->v aur v->u).
// Start node = odd degree wala (path case), warna koi bhi node (circuit).
//
// Hierholzer steps:
//   1) Stack pe start push
//   2) Jab edges bachi hain → next neighbor pe jao, dono lists se edge hatao
//   3) Jab koi edge nahi → node ko path me daalo, stack se pop
//   4) Path reverse karke return karo
// ════════════════════════════════════════════════════════════════════════════

class Graph
{
public:
    unordered_map<int, list<int>> adjList;
    unordered_map<int, int> inDegree;

    // ── addEdge: undirected edge — dono nodes ka degree badhao ─────────────
    void addEdge(int u, int v, bool direction)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u);

        inDegree[u]++;
        inDegree[v]++;
    }

    // ── calculateInDegree: adjList se degree recompute ─────────────────────
    void calculateInDegree()
    {
        inDegree.clear();

        for (auto &i : adjList)
        {
            for (auto &nbr : i.second)
            {
                inDegree[nbr]++;
            }
        }
    }

    // ── isConnected: graph connected hai ya nahi ───────────────────────────
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

    // ── DFS: reachability ke liye ──────────────────────────────────────────
    void DFS(int node, unordered_map<int, bool> &visited)
    {
        visited[node] = true;
        for (auto &neighbor : adjList[node])
        {
            if (!visited[neighbor])
                DFS(neighbor, visited);
        }
    }

    // ── hasEulerianPath: 0 ya 2 odd-degree nodes ───────────────────────────
    bool hasEulerianPath()
    {
        if (!isConnected())
            return false;

        int oddDegreeCount = 0;
        for (auto &node : inDegree)
        {
            if (node.second % 2 != 0)
                oddDegreeCount++;
        }

        return (oddDegreeCount == 0 || oddDegreeCount == 2);
    }

    // ── findEulerianPath: Hierholzer se actual path construct karo ─────────
    vector<int> findEulerianPath()
    {
        // Step 1: odd-degree condition fail ho to path impossible
        if (!hasEulerianPath())
        {
            cout << "Eulerian Path does not exist." << endl;
            return {};
        }

        unordered_map<int, list<int>> tempGraph = adjList;
        stack<int> st;
        vector<int> path;
        int startNode = -1;

        // Step 2: odd degree wala node = path start; circuit me koi bhi node
        for (auto &node : inDegree)
        {
            if (node.second % 2 != 0)
            {
                startNode = node.first;
                break;
            }
        }

        if (startNode == -1)
            startNode = adjList.begin()->first;

        st.push(startNode);

        // Step 3: Hierholzer — undirected me edge dono taraf se remove karo
        while (!st.empty())
        {
            int v = st.top();

            if (!tempGraph[v].empty())
            {
                int next = tempGraph[v].front();
                tempGraph[v].pop_front();
                tempGraph[next].remove(v);
                st.push(next);
            }
            else
            {
                path.push_back(v);
                st.pop();
            }
        }

        // Step 4: stack se ulta aaya tha — reverse karke sahi order
        reverse(path.begin(), path.end());
        return path;
    }
};

int main()
{
    Graph g;

    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 0, 1);
    g.addEdge(1, 3, 1);

    g.calculateInDegree();

    cout << "Graph Adjacency List:\n";
    for (auto &node : g.adjList)
    {
        cout << node.first << " -> ";
        for (auto &nbr : node.second)
        {
            cout << nbr << ", ";
        }
        cout << endl;
    }

    vector<int> eulerPath = g.findEulerianPath();
    if (!eulerPath.empty())
    {
        cout << "Eulerian Path: ";
        for (int node : eulerPath)
        {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}
