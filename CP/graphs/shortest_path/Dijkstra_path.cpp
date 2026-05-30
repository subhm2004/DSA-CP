#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Add edge to the graph
void addEdge(unordered_map<int, list<pair<int, int>>> &adjList, int u, int v, int wt, bool direction)
{
    adjList[u].push_back({v, wt});
    if (direction == 1)
        adjList[v].push_back({u, wt});
}

// Print adjacency list
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

// Print path recursively
void printPath(int node, const unordered_map<int, int> &parent)
{
    if (node == -1)
        return;
    cout << node << " ";                // Print node before recursion (source to destination)
    printPath(parent.at(node), parent); // Recurse afterwards
}

// Dijkstra's algorithm
void shortestDistDijkstra(const unordered_map<int, list<pair<int, int>>> &adjList, int src)
{
    unordered_map<int, int> dist;
    unordered_map<int, int> parent;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    for (const auto &entry : adjList)
    {
        dist[entry.first] = INT_MAX;
        parent[entry.first] = -1;
    }

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty())
    {
        auto [currDist, node] = pq.top();
        pq.pop();

        for (const auto &nbr : adjList.find(node)->second)
        {
            int neighbor = nbr.first;
            int weight = nbr.second;

            if (currDist + weight < dist[neighbor])
            {
                dist[neighbor] = currDist + weight;
                pq.push({dist[neighbor], neighbor});
                parent[neighbor] = node;
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
