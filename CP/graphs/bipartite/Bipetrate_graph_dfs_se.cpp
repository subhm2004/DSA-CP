// ════════════════════════════════════════════════════════════════════════════
// BIPARTITE CHECK — DFS (2-Coloring)
// ────────────────────────────────────────────────────────────────────────────
// BFS wali same idea, bas queue ki jagah recursion
// Har node ko 0 ya 1 color do — neighbor ko hamesha opposite
// Same color neighbor mile → odd cycle → not bipartite
// Time: O(V + E)  |  Space: O(V)
// ════════════════════════════════════════════════════════════════════════════

#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
using namespace std;

class Graph
{
    int V;
    unordered_map<int, list<int>> adjList;

public:
    // Step 1: V vertices store karo, empty adjacency list ready.
    // Step 2: addEdge se undirected graph build hoga — DFS 2-coloring ke liye.
    Graph(int V)
    {
        this->V = V;
    }

    // Step 1: u-v undirected edge — dono taraf adjacency list mein add karo.
    // Step 2: DFS traversal mein har neighbor check hoga coloring ke liye.
    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    // Step 1: color[node] = currentColor assign karo — current node ko ye color mila.
    // Step 2: Har neighbor check karo — unvisited (-1) ho to recurse with 1-currentColor.
    // Step 3: Recursive call false de to propagate — subtree mein conflict mila.
    // Step 4: Visited neighbor same currentColor ho → adjacent same color → NOT bipartite.
    // Step 5: Saare neighbors OK → true — is subtree mein valid 2-coloring hai.
    bool isBipartiteDFS(int node, vector<int> &color, int currentColor)
    {
        color[node] = currentColor;

        for (int nbr : adjList[node])
        {
            if (color[nbr] == -1)
            {
                // unvisited neighbor ko opposite color ke saath recurse
                if (!isBipartiteDFS(nbr, color, 1 - currentColor))
                    return false;
            }
            else if (color[nbr] == currentColor)
            {
                return false; // conflict — same color adjacent nodes
            }
        }
        return true;
    }

    // Step 1: color array size V, sab -1 initialize karo.
    // Step 2: Har unvisited node i se isBipartiteDFS(i, color, 0) start karo.
    // Step 3: Disconnected components alag se handle — har component ko color 0 se shuru.
    // Step 4: Koi component fail ho to false return.
    // Step 5: Saare components pass → true — graph bipartite hai.
    bool isBipartite()
    {
        vector<int> color(V, -1);

        for (int i = 0; i < V; i++)
        {
            if (color[i] == -1)
            {
                if (!isBipartiteDFS(i, color, 0))
                    return false;
            }
        }
        return true;
    }
};

int main()
{
    int V = 4;
    Graph g(V);

    vector<pair<int, int>> edges = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}};

    for (auto [u, v] : edges)
    {
        g.addEdge(u, v);
    }

    if (g.isBipartite())
    {
        cout << "The graph is Bipartite.\n";
    }
    else
    {
        cout << "The graph is NOT Bipartite.\n";
    }

    return 0;
}
