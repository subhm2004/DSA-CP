#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <algorithm>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// TARJAN'S ALGORITHM — Bridges (Cut Edges) dhundhna
// ────────────────────────────────────────────────────────────────────────────
// Bridge = aisi edge jiski hataane se graph ke components badh jaate hain.
//
// DFS me do arrays:
//   disc[u] = discovery time (pehli baar kab visit hua)
//   low[u]  = u ke subtree se reachable sabse chhota disc time
//
// Edge (u, v) bridge hai agar: low[v] > disc[u]
//   matlab v ka subtree u ya uske ancestors tak kisi aur raaste se nahi ja sakta
//
// Time: O(V + E)  |  Space: O(V)
// ════════════════════════════════════════════════════════════════════════════

class Graph
{
public:
    unordered_map<int, list<int>> adjList;

    // direction = 1 undirected (dono taraf edge), 0 directed
    // ── addEdge: edge add karo — direction=1 undirected, 0 directed ──────────
    void addEdge(int u, int v, bool direction)
    {
        adjList[u].push_back(v);
        if (direction == 1)
        {
            adjList[v].push_back(u);
        }
    }

    // ── DFS helper: bridges collect karo ───────────────────────────────────
    void find_Bridges_DFS(
        int currentNode,
        int parentNode,
        int &timer,
        vector<int> &discoveryTime,
        vector<int> &lowestTime,
        unordered_map<int, bool> &visited,
        vector<pair<int, int>> &ans)
    {
        // Step 1: node visit karo, disc[] aur low[] = current timer set karo
        visited[currentNode] = true;
        discoveryTime[currentNode] = timer;
        lowestTime[currentNode] = timer;
        timer++;

        for (auto neighbor : adjList[currentNode])
        {
            if (neighbor == parentNode)
                continue;

            if (!visited[neighbor])
            {
                // Step 2: tree edge — pehle child DFS, phir low[] propagate
                find_Bridges_DFS(neighbor, currentNode, timer, discoveryTime, lowestTime, visited, ans);
                lowestTime[currentNode] = min(lowestTime[currentNode], lowestTime[neighbor]);

                // Step 3: bridge check — low[child] > disc[u] matlab child alag component
                if (lowestTime[neighbor] > discoveryTime[currentNode])
                {
                    ans.push_back({currentNode, neighbor});
                }
            }
            else
            {
                // Step 4: back edge — visited ancestor se low[] update
                lowestTime[currentNode] = min(lowestTime[currentNode], discoveryTime[neighbor]);
            }
        }
    }

    // Saare bridges print karo — disconnected components handle
    void find_Bridges(int n)
    {
        vector<int> discoveryTime(n, -1);
        vector<int> lowestTime(n, -1);
        unordered_map<int, bool> visited;
        int timer = 0;
        vector<pair<int, int>> ans;

        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                find_Bridges_DFS(i, -1, timer, discoveryTime, lowestTime, visited, ans);
            }
        }

        cout << "Bridges in the graph are:" << endl;
        if (ans.empty())
        {
            cout << "No bridges found in the graph." << endl;
        }
        else
        {
            for (auto bridge : ans)
            {
                cout << bridge.first << " -- " << bridge.second << endl;
            }
        }
    }
};

int main()
{
    Graph g;

    int n, m;
    cout << "Enter the number of nodes and edges: ";
    cin >> n >> m;

    if (n <= 0 || m < 0)
    {
        cout << "Invalid input! Number of nodes should be positive, edges non-negative." << endl;
        return 1;
    }

    cout << "Enter the edges (u v): " << endl;
    cout << "Note: Vertices should be numbered from 0 to " << (n - 1) << endl;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        if (u < 0 || u >= n || v < 0 || v >= n)
        {
            cout << "Warning: Edge (" << u << ", " << v << ") contains invalid vertex numbers!" << endl;
            cout << "Valid range: 0 to " << (n - 1) << endl;
        }

        g.addEdge(u, v, 1); // undirected
    }

    cout << "\n=== BRIDGE FINDING ALGORITHM EXECUTION ===" << endl;
    g.find_Bridges(n);

    return 0;
}
