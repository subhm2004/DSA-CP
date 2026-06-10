#include <iostream>
#include <unordered_map>
#include <list>
#include <stack>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// KOSARAJU'S ALGORITHM — Strongly Connected Components (SCC) count + print
// ────────────────────────────────────────────────────────────────────────────
// Directed graph me SCC = aisa subset jahan har node har doosre tak reachable.
//
// 3 steps:
//   1) Pehli DFS: finish time order stack me (larger finish time = pehle pop)
//   2) Saari edges reverse karke naya graph banao
//   3) Stack order me DFS — har nayi DFS ek alag SCC hai
//
// Time: O(V + E)  |  Space: O(V + E)
// ════════════════════════════════════════════════════════════════════════════

class Kosa_Raju_Algorithm
{
public:
    unordered_map<int, list<int>> adjList;

    // ── addEdge: directed edge u->v add karo (SCC ke liye direction=0) ────
    void addEdge(int u, int v, bool direction)
    {
        adjList[u].push_back(v);
        if (direction == 1)
        {
            adjList[v].push_back(u);
        }
    }

    // ── Step 1 helper: DFS karke stack me push (finish time order) ─────────
    // Jab saare neighbors process ho jayein tab hi node stack me daalo —
    // isse "sabse last finish" wala node stack ke top pe aata hai.
    void topo_sort_DFS(int src, stack<int> &s, unordered_map<int, bool> &visited)
    {
        // Step 1: current node visited mark karo
        visited[src] = true;
        // Step 2: pehle saare unvisited neighbors pe recurse karo
        for (auto nbr : adjList[src])
        {
            if (!visited[nbr])
            {
                topo_sort_DFS(nbr, s, visited);
            }
        }
        // Step 3: post-order push — finish time zyada wala baad me pop hoga
        s.push(src);
    }

    // ── Step 3 helper: reversed graph pe DFS — ek SCC ke saare nodes print ─
    void DFS(int src, unordered_map<int, bool> &visited, unordered_map<int, list<int>> &adjNew)
    {
        visited[src] = true;
        cout << src << " ";
        for (auto nbr : adjNew[src])
        {
            if (!visited[nbr])
            {
                DFS(nbr, visited, adjNew);
            }
        }
    }

    // ── Poori Kosaraju pipeline ─────────────────────────────────────────────
    int countSCC(int n)
    {
        stack<int> s;
        unordered_map<int, bool> visited;

        // Step 1: original graph pe DFS — finish order stack me store
        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                topo_sort_DFS(i, s, visited);
            }
        }

        // Step 2: graph transpose karo — har directed edge u->v ko v->u banao
        unordered_map<int, list<int>> adjNew;
        for (auto t : adjList)
        {
            for (auto nbr : t.second)
            {
                adjNew[nbr].push_back(t.first);
            }
        }

        // Step 3: stack order me reversed graph pe DFS — har nayi DFS = ek SCC
        int count = 0;
        unordered_map<int, bool> visited2;

        while (!s.empty())
        {
            int node = s.top();
            s.pop();
            if (!visited2[node])
            {
                cout << "SCC " << count + 1 << ": ";
                DFS(node, visited2, adjNew);
                cout << endl;
                count++;
            }
        }
        return count;
    }
};

int main()
{
    Kosa_Raju_Algorithm g;
    int n, m;
    cout << "Enter the number of nodes and edges: ";
    cin >> n >> m;

    cout << "Enter the edges (u -> v):" << endl;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v, 0); // directed edge
    }

    cout << "Total strongly connected components (SCC): " << g.countSCC(n) << endl;

    return 0;
}
