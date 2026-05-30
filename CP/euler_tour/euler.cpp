/*
What is Hierholzer's Algorithm?
Hierholzer’s algorithm is used to find an Eulerian Path (a trail visiting every edge exactly once) or an Eulerian Circuit (a closed trail visiting every edge exactly once) in a graph.

Conditions:
An Eulerian Circuit exists if all vertices have even degree.
An Eulerian Path exists if exactly two vertices have odd degree.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <stack>
using namespace std;

class Graph
{
    int V;
    unordered_map<int, list<int>> adjList; // Adjacency list

public:
    Graph(int V)
    {
        this->V = V;
    }

    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
    }

    void findEulerianPathOrCircuit()
    {
        unordered_map<int, list<int>> tempAdj = adjList; // Copy adjacency list

        stack<int> stk;
        vector<int> path;
        int startNode = 0;

        // Finding a start node (any node with an edge)
        unordered_map<int, list<int>>::iterator it;
        for (it = adjList.begin(); it != adjList.end(); ++it)
        {
            if (!it->second.empty())
            {
                startNode = it->first;
                break;
            }
        }

        stk.push(startNode);

        while (!stk.empty())
        {
            int node = stk.top();

            if (!tempAdj[node].empty())
            {
                int next = tempAdj[node].front();
                tempAdj[node].pop_front();
                stk.push(next);
            }
            else
            {
                path.push_back(node);
                stk.pop();
            }
        }

        // Output the Eulerian Path or Circuit
        cout << "Eulerian Path/Circuit: ";
        for (int i = path.size() - 1; i >= 0; i--)
            cout << path[i] << " ";
        cout << endl;
    }
};

int main()
{
    int V = 6;
    Graph g(V);

    vector<pair<int, int>> edges = {
        {0, 1}, {1, 2}, {2, 0}, {1, 3}, {3, 4}, {4, 1}};

    for (size_t i = 0; i < edges.size(); i++)
    {
        g.addEdge(edges[i].first, edges[i].second);
    }

    g.findEulerianPathOrCircuit();

    return 0;
}

