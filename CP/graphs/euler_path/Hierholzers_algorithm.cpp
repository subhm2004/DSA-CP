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

        // An Eulerian Path exists if:
        // 1. The graph has an Eulerian Circuit (every node has equal in-degree and out-degree).
        //    This happens when there are no special start or end nodes: (startNodes == 0 && endNodes == 0).
        // 2. The graph has a single valid Eulerian Path, which requires exactly one start node (out-degree = in-degree + 1)
        //    and exactly one end node (in-degree = out-degree + 1): (startNodes == 1 && endNodes == 1).
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
        if (hasEulerianCircuit())
        {
            cout << "Eulerian Circuit Exists." << endl;
        }
        else if (hasEulerianPath())
        {
            cout << "Eulerian Path Exists." << endl;
        }
        else if (hasEulerianPath() && hasEulerianCircuit())
        {
            cout << "Eulerian Path and circuit both Exists." << endl;
        }
        else
        {
            cout << "No Eulerian Path or Circuit exists." << endl;
            return;
        }

        unordered_map<int, list<int>> tempAdj = adjList;
        stack<int> st;
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
        {
            startNode = adjList.begin()->first;
        }

        st.push(startNode);

        while (!st.empty())
        {
            int node = st.top();

            if (!tempAdj[node].empty())
            {
                int next = tempAdj[node].front();
                tempAdj[node].pop_front();
                st.push(next);
            }
            else
            {
                path.push_back(node);
                st.pop();
            }
        }

        cout << "Eulerian Path/Circuit: ";
        for (int i = path.size() - 1; i >= 0; i--)
            cout << path[i] << " ";
        cout << endl;
    }
};

int main()
{
    Graph g;
    vector<pair<int, int>> edges = {{0, 1}, {1, 2}, {2, 0}, {1, 3}, {3, 4}, {4, 1}};

    for (auto edge : edges)
    {
        g.addEdge(edge.first, edge.second);
    }

    g.findEulerianPathOrCircuit();
    return 0;
}
