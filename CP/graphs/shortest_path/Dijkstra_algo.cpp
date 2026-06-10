#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// DIJKSTRA'S ALGORITHM — Single Source Shortest Path (Non-Negative Weights)
// ────────────────────────────────────────────────────────────────────────────
// Ek source se sabhi nodes tak minimum distance nikalta hai.
// Greedy + Priority Queue: hamesha sabse chhota dist wala node pehle process karo.
//
// dist[node] = source se node tak shortest distance (shuru me INF, src = 0)
// PQ me {distance, node} — min-heap se sabse kareeb node nikalo
//
// Jab node pop ho, uske neighbors relax karo:
//   agar dist[node] + edgeWeight < dist[neighbor] -> update + PQ me daalo
//
// NOTE: Negative edge weights pe kaam NAHI karega — Bellman-Ford use karo.
// Time: O((V+E) log V)  |  Space: O(V)
// ════════════════════════════════════════════════════════════════════════════

// ── addEdge: adjacency list me edge add karo ───────────────────────────────
// direction = 1 -> undirected (dono taraf), 0 -> directed (sirf u->v)
void addEdge(unordered_map<int, list<pair<int, int>>> &adjList, int u, int v, int wt, bool direction)
{
    // Step 1: u ki adjacency list me (neighbor v, weight wt) daalo
    adjList[u].push_back({v, wt});
    // Step 2: agar undirected hai (direction=1) to reverse edge bhi add karo
    if (direction == 1)
    {
        adjList[v].push_back({u, wt});
    }
}

// ── printadj: adjacency list console pe dikhao ─────────────────────────────
void printadj(const unordered_map<int, list<pair<int, int>>> &adjList)
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

// ── shortestDistDijkstra: source se sab nodes ka shortest distance ─────────
// dist initialize karo (INF), src = 0. PQ me {0, src} daalo.
// Har pop pe neighbors relax — better path mila to dist update + PQ push.
// Ant me har node ka shortest distance print karo.
void shortestDistDijkstra(const unordered_map<int, list<pair<int, int>>> &adjList, int n, int src)
{
    // Step 1: dist[] initialize — sab INF, source = 0
    unordered_map<int, int> dist;
    for (int i = 1; i < n; ++i)
    {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    // Step 2: min-heap me {distance, node} daalo — greedy pick hamesha sabse chhota dist
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src}); // {distance, node}

    // Step 3: jab tak PQ khali nahi, sabse kareeb node pop karke neighbors relax karo
    while (!pq.empty())
    {
        auto [nodeDistance, node] = pq.top();
        pq.pop();

        // Step 4: current node ke saare neighbors check karo
        for (const auto &nbr : adjList.find(node)->second)
        {
            int neighbor = nbr.first;
            int edgeWeight = nbr.second;

            // Step 5: relaxation — agar naya path chhota hai to dist update + PQ me daalo
            if (nodeDistance + edgeWeight < dist[neighbor])
            {
                dist[neighbor] = nodeDistance + edgeWeight;
                pq.push({dist[neighbor], neighbor});
            }
        }
    }

    // Sabhi nodes ka shortest distance print karo
    cout << "Shortest distances from source " << src << ":\n";
    for (int i = 1; i < n; ++i)
    {
        if (dist[i] == INT_MAX)
        {
            cout << "Node " << i << " -> INF" << endl;
        }
        else
        {
            cout << "Node " << i << " -> " << dist[i] << endl;
        }
    }
}

int main()
{
    int n = 7; // Number of nodes
    unordered_map<int, list<pair<int, int>>> adjList;

    // Undirected weighted graph build karo
    addEdge(adjList, 6, 3, 2, 1);
    addEdge(adjList, 6, 1, 14, 1);
    addEdge(adjList, 3, 1, 9, 1);
    addEdge(adjList, 3, 2, 10, 1);
    addEdge(adjList, 1, 2, 7, 1);
    addEdge(adjList, 2, 4, 15, 1);
    addEdge(adjList, 4, 3, 11, 1);
    addEdge(adjList, 6, 5, 9, 1);
    addEdge(adjList, 4, 5, 6, 1);

    printadj(adjList);
    shortestDistDijkstra(adjList, n, 6);

    return 0;
}
