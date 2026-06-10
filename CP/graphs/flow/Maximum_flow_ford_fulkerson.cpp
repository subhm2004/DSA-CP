// ════════════════════════════════════════════════════════════════════════════
// EDMONDS-KARP ALGORITHM — Maximum Flow (BFS-based Ford-Fulkerson)
// ────────────────────────────────────────────────────────────────────────────
// Ford-Fulkerson ka BFS version: har baar shortest augmenting path (edge count)
// dhund kar uspe flow push karo.
//
// Residual graph:
//   - capacity[u][v] = kitna aur flow bhej sakte ho u -> v
//   - Reverse edge capacity badhao jab forward pe flow bhejo (cancel karne ke liye)
//
// Jab tak BFS se s se t tak path milti hai, flow badhate raho.
// Complexity: O(V * E^2)
// ════════════════════════════════════════════════════════════════════════════

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

class FlowNetwork
{
public:
    int n;
    unordered_map<int, unordered_map<int, int>> capacity;
    unordered_map<int, list<int>> adjList;

    FlowNetwork(int nodes) : n(nodes) {}

    // ── addEdge: u -> v capacity; reverse edge bhi adj list me (residual) ──
    void addEdge(int u, int v, int cap)
    {
        capacity[u][v] += cap;  // parallel edges ho to capacity sum karo
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    // ── bfs: s se t tak augmenting path dhundo, parent array me store karo ───
    // Returns bottleneck flow; 0 agar koi path nahi
    int bfs(int s, int t, unordered_map<int, int> &parent)
    {
        // Step 1: BFS queue me source daalo, parent[s]=-2 mark
        unordered_map<int, bool> visited;
        queue<pair<int, int>> q;
        q.push({s, INF});
        parent[s] = -2;

        // Step 2: level-order BFS — sirf residual capacity > 0 wali edges
        while (!q.empty())
        {
            int cur = q.front().first;
            int flow = q.front().second;
            q.pop();

            for (int next : adjList[cur])
            {
                if (!visited[next] && capacity[cur][next] > 0)
                {
                    parent[next] = cur;
                    visited[next] = true;
                    // Step 3: path ka bottleneck = min of edge capacities so far
                    int new_flow = min(flow, capacity[cur][next]);
                    if (next == t)
                        return new_flow;
                    q.push({next, new_flow});
                }
            }
        }

        return 0; // koi augmenting path nahi
    }

    // ── maxflow: BFS loop — har path pe flow push, residual update ───────────
    int maxflow(int s, int t)
    {
        int flow = 0;
        unordered_map<int, int> parent;
        int new_flow;

        // Step 1: jab tak BFS se augmenting path milti hai, repeat karo
        while ((new_flow = bfs(s, t, parent)))
        {
            flow += new_flow;
            // Step 2: sink se source tak parent follow karke residual update
            int cur = t;
            while (cur != s)
            {
                int prev = parent[cur];
                capacity[prev][cur] -= new_flow;  // forward capacity kam
                capacity[cur][prev] += new_flow;  // reverse me flow store (cancel ke liye)
                cur = prev;
            }
        }

        return flow;
    }
};
int main()
{
    int nodes = 8;
    FlowNetwork fn(nodes);

    vector<tuple<int, int, int>> edges = {
        {0, 1, 10}, {0, 2, 15}, {1, 3, 10}, {1, 4, 20}, {2, 5, 25}, {2, 6, 30}, {5, 7, 10}};

    for (auto [u, v, cap] : edges)
    {
        fn.addEdge(u, v, cap);
    }

    int s = 0, t = 7;
    cout << "Maximum Flow: " << fn.maxflow(s, t) << endl;

    return 0;
}

// Main function
// int main() {
//     int nodes, edges;
//     cout << "Enter number of nodes and edges: ";
//     cin >> nodes >> edges;

//     FlowNetwork fn(nodes);

//     cout << "Enter edges (u v capacity):\n";
//     for (int i = 0; i < edges; i++) {
//         int u, v, cap;
//         cin >> u >> v >> cap;
//         fn.addEdge(u, v, cap);
//     }

//     int s, t;
//     cout << "Enter source and sink: ";
//     cin >> s >> t;

//     cout << "Maximum Flow: " << fn.maxflow(s, t) << endl;
//     return 0;
// }
