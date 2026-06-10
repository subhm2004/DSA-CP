// ════════════════════════════════════════════════════════════════════════════
// BIPARTITE CHECK — BFS (2-Coloring)
// ────────────────────────────────────────────────────────────────────────────
// Bipartite = graph ko 2 groups me baat sakte ho jahan har edge groups ke beech ho
// BFS se alternate color (0/1) assign karo
// Agar koi neighbor parent jaisa color hai → NOT bipartite
// Disconnected graph ke liye har component alag se check karo
// Time: O(V + E)  |  Space: O(V)
// ════════════════════════════════════════════════════════════════════════════

#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <queue>
using namespace std;

class Graph
{
    int V;
    unordered_map<int, list<int>> adjList;

public:
    // Step 1: Total vertices V store karo.
    // Step 2: Empty adjacency list ready — addEdge se undirected graph build hoga.
    Graph(int V)
    {
        this->V = V;
    }

    // Step 1: adjList[u] mein v aur adjList[v] mein u push — undirected edge.
    // Step 2: Bipartite check mein har edge dono taraf traverse hogi.
    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    // Step 1: src ko queue mein push karo, color[src] = 0 assign karo.
    // Step 2: Front node pop karo, har neighbor check karo.
    // Step 3: Neighbor uncolored (-1) ho to opposite color do: 1 - color[node], queue mein push.
    // Step 4: Neighbor colored aur same color as parent → odd cycle → false return.
    // Step 5: Queue khatam ho jaye to component bipartite hai — true return.
    bool isBipartiteBFS(int src, vector<int> &color)
    {
        queue<int> q;
        q.push(src);
        color[src] = 0; // source ko color 0 do

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            for (int nbr : adjList[node])
            {
                if (color[nbr] == -1)
                {
                    // uncolored neighbor ko opposite color do
                    color[nbr] = 1 - color[node];
                    q.push(nbr);
                }
                else if (color[nbr] == color[node])
                {
                    // same color as parent = odd cycle = not bipartite
                    return false;
                }
            }
        }
        return true;
    }

    // Step 1: color array size V, sab -1 (uncolored) initialize karo.
    // Step 2: Har node i = 0..V-1 check karo — disconnected components handle karne ke liye.
    // Step 3: Agar color[i] == -1 ho to isBipartiteBFS(i, color) se naya component start karo.
    // Step 4: Koi bhi component fail ho to turant false — poora graph bipartite nahi.
    // Step 5: Saare components pass → true — 2-coloring possible hai poori graph pe.
    bool isBipartite()
    {
        vector<int> color(V, -1); // -1 = abhi color nahi mila

        for (int i = 0; i < V; i++)
        {
            if (color[i] == -1)
            {
                if (!isBipartiteBFS(i, color))
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

    // Square cycle 0-1-2-3-0 — bipartite hai (even cycle)
    vector<pair<int, int>> edges = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}};

    for (auto edge : edges)
    {
        g.addEdge(edge.first, edge.second);
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
