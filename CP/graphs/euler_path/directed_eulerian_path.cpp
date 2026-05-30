#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
    unordered_map<int, list<int>> adjList;
    unordered_map<int, int> inDegree, outDegree;

    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
        outDegree[u]++;
        inDegree[v]++;
    }

    void calculateDegrees()
    {
        inDegree.clear();
        outDegree.clear();

        for (auto &i : adjList)
        {
            int src = i.first;
            for (int nbr : i.second)
            {
                outDegree[src]++;
                inDegree[nbr]++;
            }
        }
    }

    void DFS(int node, unordered_map<int, bool> &visited)
    {
        visited[node] = true;
        for (int nbr : adjList[node])
        {
            if (!visited[nbr])
                DFS(nbr, visited);
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
            return true;

        DFS(startNode, visited);

        for (auto &node : adjList)
        {
            if (!visited[node.first] && (!node.second.empty() || inDegree[node.first] > 0))
                return false;
        }

        return true;
    }

    bool hasEulerianPath()
    {
        if (!isConnected())
            return false;

        int startNodes = 0, endNodes = 0;

        for (auto &node : adjList)
        {
            int u = node.first;
            if (outDegree[u] - inDegree[u] == 1)
                startNodes++;
            else if (inDegree[u] - outDegree[u] == 1)
                endNodes++;
            else if (inDegree[u] != outDegree[u])
                return false;
        }

        return (startNodes == 0 && endNodes == 0) || (startNodes == 1 && endNodes == 1);
    }

    bool hasEulerianCircuit()
    {
        if (!isConnected())
            return false;

        for (auto &node : adjList)
        {
            if (inDegree[node.first] != outDegree[node.first])
                return false;
        }

        return true;
    }

    void findEulerianPathOrCircuit()
    {
        calculateDegrees();

        if (hasEulerianCircuit())
        {
            cout << "Eulerian Circuit Exists." << endl;
        }
        else if (hasEulerianPath())
        {
            cout << "Eulerian Path Exists." << endl;
        }
        else
        {
            cout << "No Eulerian Path or Circuit exists." << endl;
            return;
        }

        unordered_map<int, list<int>> tempAdj = adjList;
        stack<int> stk;
        vector<int> path;
        int startNode = -1;

        for (auto &node : adjList)
        {
            if (outDegree[node.first] - inDegree[node.first] == 1)
            {
                startNode = node.first;
                break;
            }
        }

        if (startNode == -1)
            startNode = adjList.begin()->first;

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

        reverse(path.begin(), path.end()); // Using reverse instead of manual iteration

        cout << "Eulerian Path/Circuit: ";
        for (int node : path)
            cout << node << " ";
        cout << endl;
    }
};

int main()
{
    Graph g;

    vector<pair<int, int>> edges = {
        {0, 1}, {1, 2}, {2, 0}, {1, 3}, {3, 4}, {4, 1}};

    for (auto edge : edges)
    {
        g.addEdge(edge.first, edge.second);
    }

    g.findEulerianPathOrCircuit();

    return 0;
}
