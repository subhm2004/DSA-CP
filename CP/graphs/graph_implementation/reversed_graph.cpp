#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <tuple>

using namespace std;

class Graph
{
public:
    unordered_map<int, list<int>> adjList; // Adjacency list
    vector<tuple<int, int, int>> edges;    // Store edges as tuples (u, v, weight)

    // Add edge to the graph
    void addEdge(int u, int v, int weight, bool direction)
    {
        adjList[u].push_back(v);         // Add directed edge from u to v
        edges.push_back({u, v, weight}); // Add edge to the list

        // If it's an undirected graph (direction == 0), add reverse edge as well
        if (direction == 0)
        {
            adjList[v].push_back(u);         // Add directed edge from v to u
            edges.push_back({v, u, weight}); // Add reverse edge to the list
        }
    }

    // Function to reverse the graph
    void reverseGraph()
    {
        unordered_map<int, list<int>> reversedAdjList;

        // Traverse through the adjacency list and reverse the edges
        for (auto &pair : adjList)
        {
            int u = pair.first;
            for (int v : pair.second)
            {
                reversedAdjList[v].push_back(u); // Reverse edge u -> v to v -> u
            }
        }

        // Now, the reversed adjacency list is stored in reversedAdjList
        adjList = reversedAdjList;
    }

    // Function to print the graph's adjacency list
    void printGraph()
    {
        for (auto &pair : adjList)
        {
            cout << pair.first << " -> ";
            for (int v : pair.second)
            {
                cout << v << " ";
            }
            cout << endl;
        }
    }

    // Function to print edges (for reference)
    void printEdges()
    {
        for (auto &edge : edges)
        {
            int u = get<0>(edge); // Manually extract values from the tuple
            int v = get<1>(edge);
            int w = get<2>(edge);
            cout << "(" << u << ", " << v << ", " << w << ")" << endl;
        }
    }
};

int main()
{
    Graph g;

    // Add directed edges
    g.addEdge(0, 1, 10, 1); // Directed edge from 0 to 1 with weight 10
    g.addEdge(1, 2, 20, 1); // Directed edge from 1 to 2 with weight 20
    g.addEdge(2, 3, 30, 1); // Directed edge from 2 to 3 with weight 30

    // Add undirected edges
    g.addEdge(3, 4, 40, 0); // Undirected edge between 3 and 4 with weight 40

    cout << "Original Graph:" << endl;
    g.printGraph(); // Print the original graph

    // Reverse the graph
    g.reverseGraph();

    cout << "\nReversed Graph:" << endl;
    g.printGraph(); // Print the reversed graph

    return 0;
}
