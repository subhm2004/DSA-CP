#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <map>
using namespace std;

class Solution
{
public:
    unordered_map<int, list<pair<int, int>>> adjList; // Weighted adjacency list (for directed/undirected graph)
    map<int, vector<int>> adjMap;                     // Unweighted adjacency list (for DFS path checking)
    vector<int> inTime, outTime;
    vector<bool> visited;
    int timer = 0;

    // Method to add an edge to the graph (directed or undirected)
    void addEdge(int u, int v, int w, bool direction)
    {
        adjList[u].push_back({v, w}); // Add weighted edge to adjList
        if (!direction)
        {
            adjList[v].push_back({u, w}); // Add reverse edge if undirected
        }

        adjMap[u].push_back(v); // Add unweighted edge to adjMap
        if (!direction)
        {
            adjMap[v].push_back(u); // Add reverse edge for undirected graph
        }
    }

    // Method to perform DFS and fill inTime and outTime
    void dfs(int start)
    {
        visited[start] = true;
        inTime[start] = ++timer;

        for (auto x : adjMap[start])
        {
            if (!visited[x])
                dfs(x);
        }

        outTime[start] = ++timer;
    }

    // Method to check if two nodes are on the same path in DFS traversal
    bool onSamePath(int u, int v)
    {
        return ((inTime[u] < inTime[v] && outTime[u] > outTime[v]) ||
                (inTime[v] < inTime[u] && outTime[v] > outTime[u]));
    }

    // Method to print the weighted adjacency list (adjList)
    void printGraph()
    {
        for (auto &pair : adjList)
        {
            cout << pair.first << " -> ";
            for (auto &neighbor : pair.second)
            {
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }

    // Method to print the unweighted adjacency list (adjMap)
    void printAdjMap()
    {
        for (auto &pair : adjMap)
        {
            cout << pair.first << " -> ";
            for (auto &neighbor : pair.second)
            {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    Solution graph;

    // Adding edges to the graph
    graph.addEdge(1, 2, 4, false); // Undirected edge with weight 4 between 1 and 2
    graph.addEdge(1, 3, 5, true);  // Directed edge with weight 5 from 1 to 3
    graph.addEdge(2, 3, 6, false); // Undirected edge with weight 6 between 2 and 3

    // Printing the graph with weighted edges
    cout << "Adjacency List with Weights:\n";
    graph.printGraph();

    // Printing the graph with unweighted edges for DFS traversal
    cout << "\nAdjacency List for DFS Traversal:\n";
    graph.printAdjMap();

    // Initialize DFS-related structures for path checking
    int V = 9;
    graph.inTime.resize(V + 1, 0); // V+1 for 1-based indexing
    graph.outTime.resize(V + 1, 0);
    graph.visited.resize(V + 1, false);

    // Perform DFS starting from node 1
    graph.dfs(1);

    // Queries to check if following pairs are on the same path
    cout << "\nPath Check Queries:\n";
    cout << (graph.onSamePath(1, 5) ? "Yes\n" : "No\n");
    cout << (graph.onSamePath(2, 9) ? "Yes\n" : "No\n");
    cout << (graph.onSamePath(2, 6) ? "Yes\n" : "No\n");

    return 0;
}
