#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// DIJKSTRA WITH PATH RECONSTRUCTION — Shortest Path + Actual Route
// ────────────────────────────────────────────────────────────────────────────
// Normal Dijkstra jaisa, par parent[] array se actual path bhi print karta hai.
//
// parent[node] = jis node se shortest path me aaye (source ke liye -1)
// Path reconstruct: destination se parent follow karo source tak, reverse print
//
// Dijkstra_algo.cpp se farq: yahan sirf distance nahi, poora route bhi dikhta hai.
// Time: O((V+E) log V)  |  Space: O(V)
// ════════════════════════════════════════════════════════════════════════════

// ── addEdge: graph me weighted edge add karo ───────────────────────────────
void addEdge(unordered_map<int, list<pair<int, int>>> &adjList, int u, int v, int wt, bool direction)
{
    adjList[u].push_back({v, wt});
    if (direction == 1)
        adjList[v].push_back({u, wt});
}

// ── printadj: adjacency list print karo ────────────────────────────────────
void printadj(const unordered_map<int, list<pair<int, int>>> &adjList)
{
    cout << "Adjacency List:\n";
    for (const auto &entry : adjList)
    {
        int node = entry.first;
        cout << "Node " << node << ":";
        for (const auto &nbr : entry.second)
        {
            cout << "[" << nbr.first << ", " << nbr.second << "] ";
        }
        cout << endl;
    }
}

// ── printPath: parent array se source -> node ka path recursively print ────
// Pehle current node print, phir parent pe recurse — source se dest order me aata hai
void printPath(int node, const unordered_map<int, int> &parent)
{
    // Base case: source (-1) pe pahunch gaye — ruk jao
    if (node == -1)
        return;
    // Step 1: pehle current node print karo (source se dest order banega)
    cout << node << " ";
    // Step 2: parent[node] pe recurse — source tak backtrack karte jao
    printPath(parent.at(node), parent);
}

// ── shortestDistDijkstra: Dijkstra + har node ka shortest path print ───────
// dist + parent dono maintain karo. Relaxation pe parent[neighbor] = node set karo.
// Ant me har node ke liye distance aur poora path dikhao.
void shortestDistDijkstra(const unordered_map<int, list<pair<int, int>>> &adjList, int src)
{
    unordered_map<int, int> dist;
    unordered_map<int, int> parent;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Step 1: har node ko INF dist aur parent=-1 se initialize karo
    for (const auto &entry : adjList)
    {
        dist[entry.first] = INT_MAX;
        parent[entry.first] = -1;
    }

    // Step 2: source dist=0, PQ me daalo
    dist[src] = 0;
    pq.push({0, src});

    // Step 3: standard Dijkstra loop — min dist node pop, neighbors relax
    while (!pq.empty())
    {
        auto [currDist, node] = pq.top();
        pq.pop();

        for (const auto &nbr : adjList.find(node)->second)
        {
            int neighbor = nbr.first;
            int weight = nbr.second;

            // Step 4: better path mila? dist + parent update, PQ me push
            if (currDist + weight < dist[neighbor])
            {
                dist[neighbor] = currDist + weight;
                pq.push({dist[neighbor], neighbor});
                parent[neighbor] = node;  // path reconstruct ke liye — neighbor 'node' se aaya
            }
        }
    }

    cout << "\nShortest distances and paths from source " << src << ":\n";
    for (const auto &entry : adjList)
    {
        int node = entry.first;
        cout << "Node " << node << " -> ";
        if (dist[node] == INT_MAX)
        {
            cout << "INF (No path)\n";
        }
        else
        {
            cout << dist[node] << " (Path: ";
            printPath(node, parent);
            cout << ")\n";
        }
    }
}

int main()
{
    unordered_map<int, list<pair<int, int>>> adjList;

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
    shortestDistDijkstra(adjList, 6);

    return 0;
}
