#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Function to add an edge to the graph
void addEdge(unordered_map<int, list<pair<int, int>>> &adjList, int u, int v, int wt, bool direction)
{
    adjList[u].push_back({v, wt});
    if (direction == 1)
    {
        adjList[v].push_back({u, wt});
    }
}

// Function to print the adjacency list
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

// Dijkstra's algorithm using priority queue
void shortestDistDijkstra(const unordered_map<int, list<pair<int, int>>> &adjList, int n, int src)
{
    unordered_map<int, int> dist;
    for (int i = 1; i < n; ++i)
    {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src}); // {distance, node}

    while (!pq.empty())
    {
        auto [nodeDistance, node] = pq.top();
        pq.pop();

        for (const auto &nbr : adjList.find(node)->second)
        {
            int neighbor = nbr.first;
            int edgeWeight = nbr.second;

            if (nodeDistance + edgeWeight < dist[neighbor])
            {
                dist[neighbor] = nodeDistance + edgeWeight;
                pq.push({dist[neighbor], neighbor});
            }
        }
    }

    // Print distances
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
