#include <iostream>
#include <unordered_map>
#include <list>
#include <stack>
using namespace std;

class Kosa_Raju_Algorithm
{
public:
    unordered_map<int, list<int>> adjList;

    void addEdge(int u, int v, bool direction)
    {
        // direction = 1 -> undirected Kosa_Raju_Algorithm
        // direction = 0 -> directed Kosa_Raju_Algorithm
        adjList[u].push_back(v);
        if (direction == 1)
        {
            adjList[v].push_back(u);
        }
    }

    void topo_sort_DFS(int src, stack<int> &s, unordered_map<int, bool> &visited)
    {
        visited[src] = true;
        for (auto nbr : adjList[src])
        {
            if (!visited[nbr])
            {
                topo_sort_DFS(nbr, s, visited);
            }
        }
        s.push(src);
    }

    void DFS(int src, unordered_map<int, bool> &visited, unordered_map<int, list<int>> &adjNew)
    {
        visited[src] = true;
        cout << src << " ";
        for (auto nbr : adjNew[src])
        {
            if (!visited[nbr])
            {
                DFS(nbr, visited, adjNew);
            }
        }
    }

    int countSCC(int n)
    {
        stack<int> s;
        unordered_map<int, bool> visited;

        // Step 1: Find the topological ordering
        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                topo_sort_DFS(i, s, visited);
            }
        }

        // Step 2: Reverse all edges
        unordered_map<int, list<int>> adjNew;
        for (auto t : adjList)
        {
            for (auto nbr : t.second)
            {
                adjNew[nbr].push_back(t.first);
            }
        }

        // Step 3: Perform DFS based on the topological order
        int count = 0;
        unordered_map<int, bool> visited2;

        while (!s.empty())
        {
            int node = s.top();
            s.pop();
            if (!visited2[node])
            {
                cout << "SCC " << count + 1 << ": ";
                DFS(node, visited2, adjNew);
                cout << endl;
                count++;
            }
        }
        return count;
    }
};

int main()
{
    Kosa_Raju_Algorithm g;
    int n, m;
    cout << "Enter the number of nodes and edges: ";
    cin >> n >> m;

    cout << "Enter the edges (u -> v):" << endl;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v, 0); // Directed Kosa_Raju_Algorithm
    }

    cout << "Total strongly connected components (SCC): " << g.countSCC(n) << endl;

    return 0;
}
