#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <climits> // For INT_MAX
#include <stack>   // For reconstructing the path
using namespace std;

class Graph
{
public:
    // Adjacency list representation: node -> list of (nbr, weight)
    unordered_map<int, list<pair<int, int>>> adjList;

    void addEdge(int u, int v, int wt, bool direction)
    {
        // direction = 1 -> undirected graph
        // direction => 0 -> directed graph;
        adjList[u].push_back({v, wt});
        if (direction == 1)
        {
            adjList[v].push_back({u, wt});
        }
    }

    void printAdjList()
    {
        for (auto i : adjList)
        {
            cout << i.first << "-> ";
            for (auto j : i.second)
            {
                cout << "(" << j.first << ", " << j.second << "), ";
            }
            cout << endl;
        }
    }

    // Bellman-Ford Algorithm to find shortest paths from a source
    void bellmanFordAlgorithm(int n, int source)
    {
        // Distance vector initialized with maximum possible value (infinity)
        vector<int> distance(n, INT_MAX);
        distance[source] = 0;

        // Parent array to reconstruct paths
        vector<int> parent(n, INT_MIN);

        // Relax edges (n - 1) times
        for (int i = 0; i < n - 1; i++)
        {
            for (const auto &node : adjList)
            {
                int currentNode = node.first;
                for (const auto &nbr : node.second)
                {
                    int adjacentNode = nbr.first;
                    int edgeWeight = nbr.second;

                    // Relax the edge
                    if (distance[currentNode] != INT_MAX && distance[currentNode] + edgeWeight < distance[adjacentNode])
                    {
                        distance[adjacentNode] = distance[currentNode] + edgeWeight;
                        parent[adjacentNode] = currentNode; // Update parent for path reconstruction
                    }
                }
            }
        }

        // Check for negative weight cycles
        bool hasNegativeCycle = false;
        for (const auto &node : adjList)
        {
            int currentNode = node.first;
            for (const auto &nbr : node.second)
            {
                int adjacentNode = nbr.first;
                int edgeWeight = nbr.second;

                if (distance[currentNode] != INT_MAX && distance[currentNode] + edgeWeight < distance[adjacentNode])
                {
                    hasNegativeCycle = true;
                    break;
                }
            }
        }

        // Output results
        if (hasNegativeCycle)
        {
            cout << "Negative weight cycle detected." << endl;
        }
        else
        {
            cout << "No negative weight cycle." << endl;
            cout << "Shortest distances and paths from source " << source << ":" << endl;

            for (int i = 0; i < n; i++)
            {
                cout << "Node " << i << ": ";
                if (distance[i] == INT_MAX)
                {
                    cout << "Infinity (No path)" << endl;
                }
                else
                {
                    cout << "Distance = " << distance[i] << ", Path = ";
                    printPath(parent, i);
                    cout << endl;
                }
            }
        }
    }

    // Helper function to reconstruct and print the path from source to a given node
    void printPath(const vector<int> &parent, int node)
    {
        stack<int> st;
        int currentNode = node;

        while (currentNode != INT_MIN)
        {
            st.push(currentNode);
            currentNode = parent[currentNode];
        }

        // Print the path from source to the node
        while (!st.empty())
        {
            cout << st.top();
            st.pop();
            if (!st.empty())
            {
                cout << " -> ";
            }
        }
    }
};

int main()
{
    Graph g;

    // Adding edges to the graph
    g.addEdge(0, 1, -1, 0);
    g.addEdge(1, 4, 2, 0);
    g.addEdge(1, 2, 3, 0);
    g.addEdge(1, 3, 2, 0);
    g.addEdge(0, 2, 4, 0);
    g.addEdge(3, 1, 1, 0);
    g.addEdge(4, 3, -3, 0);
    g.addEdge(3, 2, 5, 0);

    cout << "Adjacency List:" << endl;
    g.printAdjList();

    cout << "\nRunning Bellman-Ford Algorithm:" << endl;
    g.bellmanFordAlgorithm(5, 0); // Assuming 5 nodes (0 to 4) and source node as 0

    return 0;
}
