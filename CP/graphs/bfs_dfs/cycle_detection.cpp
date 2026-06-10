// ════════════════════════════════════════════════════════════════════════════
// CYCLE DETECTION — BFS, DFS (Undirected) & DFS (Directed)
// ────────────────────────────────────────────────────────────────────────────
// Undirected: parent track karo — agar visited neighbor parent nahi hai → cycle
// Directed:   dfsVisited (recursion stack) — back edge = cycle
// Time: O(V + E)  |  Space: O(V)
// ════════════════════════════════════════════════════════════════════════════

#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <queue>
using namespace std;

template <typename T>
class Graph
{
public:
    unordered_map<T, list<T>> adjList;

    // Step 1: u ki adjacency list mein v add karo.
    // Step 2: Undirected graph (direction==0) mein v se u ki reverse edge bhi daalo.
    // Step 3: Directed graph mein sirf u -> v store hota hai.
    void addEdge(T u, T v, bool direction)
    {
        adjList[u].push_back(v);
        if (direction == 0)
        {
            adjList[v].push_back(u);
        }
    }

    // Step 1: Har node ki adjacency list iterate karo.
    // Step 2: Node print karo, phir uske saare neighbors comma-separated.
    // Step 3: Debugging ke liye poora graph structure console pe dikhao.
    void printAdjacencyList()
    {
        for (auto node : adjList)
        {
            cout << node.first << "-> ";
            for (auto neighbour : node.second)
            {
                cout << neighbour << ", ";
            }
            cout << endl;
        }
    }

    // ── Undirected cycle via BFS: parent se aaye hue edge ko ignore karo ────
    // Step 1: Source ko queue mein daalo, visited mark karo, parent[src] = -1 set karo.
    // Step 2: Front node nikalo, uske har neighbor ko check karo.
    // Step 3: Agar neighbor unvisited hai to queue mein push karo aur parent[neighbor] = frontNode.
    // Step 4: Agar neighbor visited hai AUR parent[frontNode] nahi hai → cross/back edge → CYCLE!
    // Step 5: Parent tracking se woh edge ignore hoti hai jisse hum aaye the (undirected mein normal edge).
    bool check_Cyclic_Using_Bfs(int src, unordered_map<int, bool> &visited)
    {
        queue<int> q;
        unordered_map<int, int> parent;

        q.push(src);
        visited[src] = true;
        parent[src] = -1;

        while (!q.empty())
        {
            int frontNode = q.front();
            q.pop();

            for (auto nbr : adjList[frontNode])
            {
                if (!visited[nbr])
                {
                    q.push(nbr);
                    visited[nbr] = true;
                    parent[nbr] = frontNode;
                }
                else if (nbr != parent[frontNode])
                {
                    // visited neighbor jo parent nahi hai = cross/back edge = cycle
                    return true;
                }
            }
        }
        return false;
    }

    // ── Undirected cycle via DFS: same parent logic ───────────────────────────
    // Step 1: Current node ko visited mark karo.
    // Step 2: Har neighbor ke liye — agar unvisited hai to dfs(neighbor, src) recursively call karo.
    // Step 3: Recursive call true return kare to turant true propagate karo (cycle mil gaya).
    // Step 4: Agar neighbor visited hai AUR neighbor != parent → back edge → cycle detected!
    // Step 5: Parent parameter batata hai hum kis node se aaye — us edge ko ignore karte hain.
    bool check_Cyclic_Using_Dfs(int src, unordered_map<int, bool> &visited, int parent)
    {
        visited[src] = true;

        for (auto nbr : adjList[src])
        {
            if (!visited[nbr])
            {
                if (check_Cyclic_Using_Dfs(nbr, visited, src))
                    return true;
            }
            else if (nbr != parent)
            {
                return true; // back edge mil gaya
            }
        }
        return false;
    }

    // ── Directed cycle via DFS: dfsVisited = current recursion path (stack) ───
    // Step 1: visited[src] = true (kabhi visit hua) aur dfsVisited[src] = true (abhi stack mein hai).
    // Step 2: Har neighbor ke liye — unvisited ho to recursively dfs call karo.
    // Step 3: Agar neighbor visited hai AUR dfsVisited[neighbor] == true → back edge → CYCLE!
    // Step 4: dfsVisited[src] = false karo jab wapas aao — node recursion stack se nikal gaya.
    // Step 5: visited alag rakhta hai permanently visited; dfsVisited sirf current DFS path track karta hai.
    bool check_Cyclic_Directed_Graph_Using_Dfs(int src, unordered_map<int, bool> &visited, unordered_map<int, bool> &dfsVisited)
    {
        visited[src] = true;
        dfsVisited[src] = true; // abhi recursion stack me hai

        for (auto nbr : adjList[src])
        {
            if (!visited[nbr])
            {
                if (check_Cyclic_Directed_Graph_Using_Dfs(nbr, visited, dfsVisited))
                    return true;
            }
            else if (dfsVisited[nbr])
            {
                // neighbor abhi bhi stack me = back edge = cycle
                return true;
            }
        }
        dfsVisited[src] = false; // backtrack — stack se nikal gaya
        return false;
    }
};

int main()
{
    Graph<int> g;
    int n = 5;

    // Directed cycle: 0→1→2→3→4→0
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 1);
    g.addEdge(4, 0, 1);

    g.printAdjacencyList();
    cout << endl;

    // Har disconnected component ke liye directed cycle check
    bool ans = false;
    unordered_map<int, bool> visited;
    unordered_map<int, bool> dfsVisited;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            ans = g.check_Cyclic_Directed_Graph_Using_Dfs(i, visited, dfsVisited);
            if (ans)
                break;
        }
    }

    cout << (ans ? "Cycle is Present" : "Cycle Absent") << endl;

    return 0;
}
