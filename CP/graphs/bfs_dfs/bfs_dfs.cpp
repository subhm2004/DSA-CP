// ════════════════════════════════════════════════════════════════════════════
// BFS + DFS — Generic Graph Traversal (Adjacency List)
// ────────────────────────────────────────────────────────────────────────────
// Template Graph class jo BFS aur DFS dono support karta hai.
// BFS = queue se level-by-level explore  |  DFS = recursion se depth-first
// Disconnected graph ke liye har unvisited node se alag se start karo.
// Time: O(V + E) per traversal  |  Space: O(V)
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
    unordered_map<T, list<T>> adjList; // node -> neighbors ki list

    // direction = 0 → undirected (dono taraf edge)
    // direction = 1 → directed (sirf u → v)
    // Step 1: u ki adjacency list mein v ko neighbor ke roop mein add karo.
    // Step 2: Agar graph undirected hai (direction == 0) to v se u ki taraf bhi edge daalo.
    // Step 3: Directed graph mein sirf u -> v store hota hai — reverse edge nahi banega.
    // Step 4: Har addEdge call se adjList grow hoti hai — node pehle se map mein na ho to auto-create.
    void addEdge(T u, T v, bool direction)
    {
        adjList[u].push_back(v);
        if (direction == 0)
        {
            adjList[v].push_back(u);
        }
    }

    // Step 1: adjList ki har entry (node -> neighbors) ko iterate karo.
    // Step 2: Pehle source node print karo, phir "->" arrow lagao.
    // Step 3: Us node ke saare neighbors comma-separated print karo.
    // Step 4: Har node ke baad newline — debugging ke liye graph structure clearly dikhe.
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

    // ── BFS: queue se source se level-by-level explore karo ─────────────────
    // Step 1: Source ko queue mein push karo aur visited[src] = true mark karo.
    // Step 2: Jab tak queue empty na ho — front node nikalo aur print karo.
    // Step 3: Us node ke har unvisited neighbor ko queue mein daalo aur visited mark karo.
    // Step 4: FIFO queue ki wajah se pehle paas wale nodes pehle process hote hain (level order).
    // Step 5: Disconnected graph mein main loop har unvisited node se ye function alag se call karta hai.
    void bfs(int src, unordered_map<int, bool> &visited)
    {
        queue<int> q;
        q.push(src);
        visited[src] = true;

        while (!q.empty())
        {
            int frontNode = q.front();
            q.pop();
            cout << frontNode << ", ";

            // Saare unvisited neighbors ko queue me daalo
            for (auto neighbour : adjList[frontNode])
            {
                if (!visited[neighbour])
                {
                    q.push(neighbour);
                    visited[neighbour] = true;
                }
            }
        }
    }

    // ── DFS: recursion se jitna deep ja sakte ho jao, phir backtrack ────────
    // Step 1: Current node ko print karo aur visited[src] = true set karo.
    // Step 2: Har unvisited neighbor ke liye recursively dfs(neighbour) call karo.
    // Step 3: Ek branch poori depth tak explore hone ke baad hi next sibling try hota hai.
    // Step 4: Recursion stack implicitly backtrack karta hai — extra pop_back ki zaroorat nahi.
    // Step 5: Disconnected components ke liye main loop har unvisited node se DFS start karta hai.
    void dfs(int src, unordered_map<int, bool> &visited)
    {
        cout << src << ", ";
        visited[src] = true;

        for (auto neighbour : adjList[src])
        {
            if (!visited[neighbour])
            {
                dfs(neighbour, visited);
            }
        }
    }
};

int main()
{
    Graph<int> g;
    int n, e;

    cout << "Enter the number of nodes: ";
    cin >> n;

    cout << "Enter the number of edges: ";
    cin >> e;

    cout << "Enter edges (u v) with space (0-indexed):" << endl;
    for (int i = 0; i < e; i++)
    {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v, 0); // undirected graph assume kiya
    }

    // Adjacency list print karo
    cout << "\nAdjacency List:" << endl;
    g.printAdjacencyList();

    // BFS — har disconnected component ke liye alag se start
    unordered_map<int, bool> visited;
    cout << "\nPrinting BFS Traversal: " << endl;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            g.bfs(i, visited);
        }
    }
    cout << endl;

    // DFS — same logic, har unvisited node se DFS chalao
    unordered_map<int, bool> visited2;
    cout << "\nPrinting DFS Traversal: " << endl;
    for (int i = 0; i < n; i++)
    {
        if (!visited2[i])
        {
            g.dfs(i, visited2);
        }
    }

    return 0;
}
