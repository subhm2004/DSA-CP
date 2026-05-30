#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Graph
{
public:
    unordered_map<T, list<T>> adjList;

    void addEdge(T u, T v, bool direction)
    {
        // direction = 0 -> undirected graph
        // direction = 1 -> directed graph
        adjList[u].push_back(v);
        if (direction == 0)
        {
            adjList[v].push_back(u);
        }
    }

    void printAdjacencyList()
    {
        for (auto node : adjList)
        {
            cout << node.first << " -> ";
            for (auto neighbor : node.second)
            {
                cout << neighbor << ", ";
            }
            cout << endl;
        }
    }

    void topoSortBfs(int n, vector<int> &ans)
    {
        queue<int> q;
        unordered_map<int, int> indegree;

        // Calculate indegree for each node
        for (auto i : adjList)
        {
            int src = i.first;
            for (auto nbr : i.second)
            {
                indegree[nbr]++;
            }
        }

        // Push nodes with indegree = 0 into the queue
        for (int i = 0; i < n; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }

        // BFS logic for Topological Sort
        while (!q.empty())
        {
            int fNode = q.front();
            q.pop();
            ans.push_back(fNode);

            for (auto nbr : adjList[fNode])
            {
                indegree[nbr]--;
                if (indegree[nbr] == 0)
                {
                    q.push(nbr);
                }
            }
        }
    }
};

int main()
{
    Graph<int> g;
    int n = 8; // Number of nodes in the graph

    // Adding edges to form a DAG
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(1, 4, 1);
    g.addEdge(2, 5, 1);
    g.addEdge(3, 6, 1);
    g.addEdge(4, 6, 1);
    g.addEdge(5, 7, 1);
    g.addEdge(6, 7, 1);

    g.printAdjacencyList();
    cout << endl;

    vector<int> ans;
    g.topoSortBfs(n, ans);

    if (ans.size() == n)
    {
        cout << "It is a valid topological sort." << endl;
    }
    else
    {
        cout << "Cycle present or invalid topological sort." << endl;
    }

    cout << "Topological Sort using BFS: ";
    for (auto i : ans)
    {
        cout << i << ", ";
    }
    cout << endl;

    return 0;
}
