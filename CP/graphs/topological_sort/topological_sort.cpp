#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <stack>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// TOPOLOGICAL SORT — DFS based (post-order stack)
// ────────────────────────────────────────────────────────────────────────────
// DAG me linear ordering: har edge u->v ke liye u, v se pehle aaye.
//
// DFS approach:
//   1) Har unvisited node se DFS
//   2) Pehle saare neighbors visit karo
//   3) Wapas aate waqt node stack me push — reverse finish order = topo sort
//
// Sirf DAG pe valid — cycle ho to valid ordering nahi.
// Time: O(V + E)  |  Space: O(V)
// ════════════════════════════════════════════════════════════════════════════

template <typename T>
class Graph
{
public:
    unordered_map<T, list<T>> adjList;

    // Step 1: adjList[u] mein v push — directed edge u -> v.
    // Step 2: direction == 0 ho to undirected — v se u bhi add karo.
    // Step 3: Topological sort sirf directed acyclic graphs (DAG) pe valid hai.
    void addEdge(T u, T v, bool direction)
    {
        adjList[u].push_back(v);
        if (direction == 0)
        {
            adjList[v].push_back(u);
        }
    }

    // Step 1: Har node ki adjacency list print karo — node -> neighbors format.
    // Step 2: Debugging ke liye graph structure console pe dikhao.
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

    // Step 1: visited[src] = true — current node processing shuru.
    // Step 2: Har unvisited neighbor par recursively topoSortDfs call karo.
    // Step 3: Pehle poori depth explore karo — post-order DFS (children pehle, parent baad).
    // Step 4: Wapas aate waqt src ko stack mein push — finish time order store hota hai.
    // Step 5: Stack pop se topological order milta hai — har edge u->v mein u, v se pehle.
    void topoSortDfs(int src, unordered_map<int, bool> &visited, stack<int> &ans)
    {
        visited[src] = true;

        for (auto neighbour : adjList[src])
        {
            if (!visited[neighbour])
            {
                topoSortDfs(neighbour, visited, ans);
            }
        }

        ans.push(src); // post-order push — stack top = sabse last finish
    }
};

int main()
{
    Graph<int> g;
    int n = 4;

    // ---- Demo DAG edges (note: kuch edges 4,5 ko point karte hain) ----
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 5, 1);
    g.addEdge(3, 4, 1);

    unordered_map<int, bool> visited;
    stack<int> ans;

    // Disconnected components handle — har unvisited se DFS
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            g.topoSortDfs(i, visited, ans);
        }
    }

    cout << "Topological Sort using DFS: ";
    while (!ans.empty())
    {
        cout << ans.top() << " ";
        ans.pop();
    }
    cout << endl;

    return 0;
}
