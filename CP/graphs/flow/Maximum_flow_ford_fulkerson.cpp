// Edmonds-Karp Algorithm (BFS-based Ford-Fulkerson)

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9; // Infinity value for max flow

class FlowNetwork
{
public:
    int n;
    unordered_map<int, unordered_map<int, int>> capacity;
    unordered_map<int, list<int>> adjList;

    FlowNetwork(int nodes) : n(nodes) {}

    void addEdge(int u, int v, int cap)
    {
        capacity[u][v] += cap; // If multiple edges exist, sum them
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Residual graph (reverse edge)
    }

    int bfs(int s, int t, unordered_map<int, int> &parent)
    {
        unordered_map<int, bool> visited;
        queue<pair<int, int>> q;
        q.push({s, INF});
        parent[s] = -2;

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
                    int new_flow = min(flow, capacity[cur][next]);
                    if (next == t)
                        return new_flow;
                    q.push({next, new_flow});
                }
            }
        }

        return 0;
    }

    int maxflow(int s, int t)
    {
        int flow = 0;
        unordered_map<int, int> parent;
        int new_flow;

        while ((new_flow = bfs(s, t, parent)))
        {
            flow += new_flow;
            int cur = t;
            while (cur != s)
            {
                int prev = parent[cur];
                capacity[prev][cur] -= new_flow;
                capacity[cur][prev] += new_flow;
                cur = prev;
            }
        }

        return flow;
    }
};
int main()
{
    int nodes = 8; // Number of nodes
    FlowNetwork fn(nodes);

    vector<tuple<int, int, int>> edges = {
        {0, 1, 10}, {0, 2, 15}, {1, 3, 10}, {1, 4, 20}, {2, 5, 25}, {2, 6, 30}, {5, 7, 10}};

    for (auto [u, v, cap] : edges)
    {
        fn.addEdge(u, v, cap);
    }

    int s = 0, t = 7; // Source & Sink
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
