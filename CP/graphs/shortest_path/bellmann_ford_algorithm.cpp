#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <climits> // For INT_MAX
#include <stack>   // For reconstructing the path
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// BELLMAN-FORD ALGORITHM — Single Source Shortest Path (Negative Weights OK)
// ────────────────────────────────────────────────────────────────────────────
// Dijkstra se better jab negative edge weights ho sakti hain.
// Idea: saari edges ko (V-1) baar "relax" karo — har baar distances improve ho sakti hain.
//
// Relax edge (u, v, w): agar dist[u] + w < dist[v] -> dist[v] update, parent[v] = u
// (V-1) rounds ke baad shortest paths mil jani chahiye (agar negative cycle nahi).
//
// Vth round: agar koi aur relax ho sake -> NEGATIVE WEIGHT CYCLE hai!
// Time: O(V * E)  |  Space: O(V)
// ════════════════════════════════════════════════════════════════════════════

class Graph
{
public:
    // Adjacency list representation: node -> list of (nbr, weight)
    unordered_map<int, list<pair<int, int>>> adjList;

    // ── addEdge: directed/undirected edge add karo ─────────────────────────
    // direction = 1 -> undirected, 0 -> directed
    void addEdge(int u, int v, int wt, bool direction)
    {
        adjList[u].push_back({v, wt});
        if (direction == 1)
        {
            adjList[v].push_back({u, wt});
        }
    }

    // ── printAdjList: graph ki adjacency list dikhao ───────────────────────
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

    // ── bellmanFordAlgorithm: source se shortest paths + negative cycle check ─
    // Step 1: distance[] = INF, source = 0.
    // Step 2: (V-1) baar saari edges relax karo.
    // Step 3: ek aur round — agar relax ho -> negative cycle.
    // Step 4: distances aur paths print karo (stack se path reconstruct).
    void bellmanFordAlgorithm(int n, int source)
    {
        // Step 1: distance[] sab INF, source = 0; parent[] path reconstruct ke liye
        vector<int> distance(n, INT_MAX);
        distance[source] = 0;
        vector<int> parent(n, INT_MIN);

        // Step 2: (n-1) rounds — har round me saari edges relax karo
        // Kyunki shortest path me max (n-1) edges hoti hain, itne rounds kaafi hain
        for (int i = 0; i < n - 1; i++)
        {
            for (const auto &node : adjList)
            {
                int currentNode = node.first;
                for (const auto &nbr : node.second)
                {
                    int adjacentNode = nbr.first;
                    int edgeWeight = nbr.second;

                    // Relax: currentNode reachable ho aur naya path chhota ho
                    if (distance[currentNode] != INT_MAX && distance[currentNode] + edgeWeight < distance[adjacentNode])
                    {
                        distance[adjacentNode] = distance[currentNode] + edgeWeight;
                        parent[adjacentNode] = currentNode;
                    }
                }
            }
        }

        // Step 3: nth round — agar ab bhi relax ho sake to negative cycle hai
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

        // Results print karo
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

    // ── printPath: parent array se source -> node ka path stack se print ───
    // Node se parent follow karo source tak, stack me daalo, phir pop karke print.
    void printPath(const vector<int> &parent, int node)
    {
        // Step 1: dest se source tak parent follow karke stack me nodes daalo
        stack<int> st;
        int currentNode = node;
        while (currentNode != INT_MIN)
        {
            st.push(currentNode);
            currentNode = parent[currentNode];
        }

        // Step 2: stack pop karke source -> dest order me print karo
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

    // Directed graph with negative edges — Bellman-Ford ka classic example
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
    g.bellmanFordAlgorithm(5, 0); // 5 nodes (0 to 4), source = 0

    return 0;
}
