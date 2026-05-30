#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
    unordered_map<int, list<int>> adjList;
    unordered_map<int, int> inDegree; // Store in-degree

    void addEdge(int u, int v, bool direction)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Undirected graph

        // Correct In-Degree Calculation
        inDegree[u]++;
        inDegree[v]++;
    }

    void calculateInDegree()
    {
        inDegree.clear(); // Reset previous data

        for (auto &i : adjList)
        {
            for (auto &nbr : i.second)
            {
                inDegree[nbr]++; // Har connected node ka degree badhao
            }
        }
    }

    bool isConnected()
    {
        unordered_map<int, bool> visited;
        int startNode = -1;

        for (auto &node : adjList)
        {
            if (!node.second.empty())
            {
                startNode = node.first;
                break;
            }
        }

        if (startNode == -1)
            return true; // Empty graph is connected

        DFS(startNode, visited);

        for (auto &node : adjList)
        {
            if (!visited[node.first] && !node.second.empty())
                return false;
        }

        return true;
    }

    void DFS(int node, unordered_map<int, bool> &visited)
    {
        visited[node] = true;
        for (auto &neighbor : adjList[node])
        {
            if (!visited[neighbor])
                DFS(neighbor, visited);
        }
    }

    bool hasEulerianPath()
    {
        if (!isConnected())
            return false;

        int oddDegreeCount = 0;
        for (auto &node : inDegree)
        {
            if (node.second % 2 != 0)
                oddDegreeCount++;
        }

        return (oddDegreeCount == 0 || oddDegreeCount == 2);
    }

    vector<int> findEulerianPath()
    {
        if (!hasEulerianPath())
        {
            cout << "Eulerian Path does not exist." << endl;
            return {};
        }

        unordered_map<int, list<int>> tempGraph = adjList;
        stack<int> st;
        vector<int> path;
        int startNode = -1;

        for (auto &node : inDegree)
        {
            if (node.second % 2 != 0)
            {
                startNode = node.first;
                break;
            }
        }

        if (startNode == -1)
            startNode = adjList.begin()->first;

        st.push(startNode);

        while (!st.empty())
        {
            int v = st.top();

            if (!tempGraph[v].empty())
            {
                int next = tempGraph[v].front();
                tempGraph[v].pop_front();
                tempGraph[next].remove(v);
                st.push(next);
            }
            else
            {
                path.push_back(v);
                st.pop();
            }
        }

        reverse(path.begin(), path.end());
        return path;
    }
};

int main()
{
    Graph g;

    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 0, 1);
    g.addEdge(1, 3, 1);

    g.calculateInDegree(); // Compute in-degree after edges are added

    cout << "Graph Adjacency List:\n";
    for (auto &node : g.adjList)
    {
        cout << node.first << " -> ";
        for (auto &nbr : node.second)
        {
            cout << nbr << ", ";
        }
        cout << endl;
    }

    vector<int> eulerPath = g.findEulerianPath();
    if (!eulerPath.empty())
    {
        cout << "Eulerian Path: ";
        for (int node : eulerPath)
        {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}
