#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <limits.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// FLOYD-WARSHALL ALGORITHM — All-Pairs Shortest Path
// ────────────────────────────────────────────────────────────────────────────
// Har pair (i, j) ke liye shortest distance nikalta hai — single source nahi.
// Idea: intermediate node k ko try karo — kya i -> k -> j path chhota hai?
//
// dist[i][j] = i se j tak shortest distance
//   - shuru me direct edge weight (ya INF agar edge nahi)
//   - diagonal dist[i][i] = 0 (khud se khud = 0)
//
// 3 nested loops: har intermediate k, har start i, har end j
//   dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
//
// Negative cycle detect: agar kisi i pe dist[i][i] < 0 -> cycle hai
// Time: O(V³)  |  Space: O(V²)
// ════════════════════════════════════════════════════════════════════════════

class Graph
{
public:
    unordered_map<int, list<pair<int, int>>> adjList;  // node -> (neighbor, weight)

    // ── addEdge: graph me edge add karo ─────────────────────────────────────
    // u se v tak weight 'wt' wali edge daalo.
    // direction = 1 -> undirected (dono taraf edge), 0 -> directed (sirf u->v).
    void addEdge(int u, int v, int wt, bool direction)
    {
        adjList[u].push_back({v, wt});
        if (direction == 1)
        {
            adjList[v].push_back({u, wt});
        }
    }

    // ── printadj: adjacency list print karo (debugging ke liye) ─────────────
    void printadj() const
    {
        cout << "Adjacency List:" << endl;
        for (const auto &entry : adjList)
        {
            int node = entry.first;
            cout << "Node " << node << ":";
            for (const auto &nbr : entry.second)
            {
                cout << " -> (" << nbr.first << ", " << nbr.second << ")";
            }
            cout << endl;
        }
    }

    // ── floydWarshall: sabhi node pairs ke shortest distance nikalo ────────
    // Step 1: dist matrix banao, diagonal 0, direct edges se initialize.
    // Step 2: har intermediate node k ke through relax karo (3 loops).
    // Step 3: negative cycle check — dist[i][i] < 0 matlab cycle.
    // Step 4: final distance matrix print karo.
    void floydWarshall(int n)
    {
        // Step 1: dist matrix banao — sab INF, diagonal (i,i) = 0
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
        for (int i = 0; i < n; i++)
        {
            dist[i][i] = 0;
        }

        // Step 2: direct edges se dist[u][v] initialize karo
        for (auto node : adjList)
        {
            for (auto nbr : node.second)
            {
                int u = node.first;
                int v = nbr.first;
                int wt = nbr.second;
                dist[u][v] = wt;
            }
        }

        // Step 3: 3 nested loops — har intermediate node k se path try karo
        // dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
        for (int intermediate = 0; intermediate < n; intermediate++)
        {
            for (int start = 0; start < n; start++)
            {
                for (int end = 0; end < n; end++)
                {
                    if (dist[start][intermediate] != INT_MAX && dist[intermediate][end] != INT_MAX)
                    {
                        dist[start][end] = min(dist[start][end], dist[start][intermediate] + dist[intermediate][end]);
                    }
                }
            }
        }

        // Step 4: negative cycle check — dist[i][i] < 0 matlab infinite negative loop
        for (int i = 0; i < n; i++)
        {
            if (dist[i][i] < 0)
            {
                cout << "Negative weight cycle detected!" << endl;
                return;
            }
        }

        // Final distance matrix print karo
        cout << "Printing distance matrix: " << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][j] == INT_MAX)
                    cout << "INF, ";
                else
                    cout << dist[i][j] << ", ";
            }
            cout << endl;
        }
    }
};

int main()
{
    Graph g;

    // Directed graph example — edges add karo
    g.addEdge(0, 1, 4, 0);
    g.addEdge(0, 2, 1, 0);
    g.addEdge(2, 1, 2, 0);
    g.addEdge(1, 3, 1, 0);
    g.addEdge(2, 3, 5, 0);

    int n = 4;

    g.printadj();

    cout << "\nRunning Floyd-Warshall Algorithm..." << endl;
    g.floydWarshall(n);

    return 0;
}
