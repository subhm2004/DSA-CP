#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <queue>
using namespace std;

template <typename T>
class Graph
{
public:
    unordered_map<T, list<T>> adjList;

    void addEdge(T u, T v, bool direction)
    {
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
            cout << node.first << "-> ";
            for (auto neighbour : node.second)
            {
                cout << neighbour << ", ";
            }
            cout << endl;
        }
    }

    bool check_Cyclic_Using_Bfs(int src, unordered_map<int, bool> &visited)
    {
        queue<int> q;
        unordered_map<int, int> parent;

        q.push(src);
        visited[src] = true;
        parent[src] = -1;

        while (!q.empty())
        {
            int frontNode = q.front();
            q.pop();

            for (auto nbr : adjList[frontNode])
            {
                if (!visited[nbr])
                {
                    q.push(nbr);
                    visited[nbr] = true;
                    parent[nbr] = frontNode;
                }
                else if (nbr != parent[frontNode])
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool check_Cyclic_Using_Dfs(int src, unordered_map<int, bool> &visited, int parent)
    {
        visited[src] = true;

        for (auto nbr : adjList[src])
        {
            if (!visited[nbr])
            {
                if (check_Cyclic_Using_Dfs(nbr, visited, src))
                    return true;
            }
            else if (nbr != parent)
            {
                return true;
            }
        }
        return false;
    }

    bool check_Cyclic_Directed_Graph_Using_Dfs(int src, unordered_map<int, bool> &visited, unordered_map<int, bool> &dfsVisited)
    {
        visited[src] = true;
        dfsVisited[src] = true;

        for (auto nbr : adjList[src])
        {
            if (!visited[nbr])
            {
                if (check_Cyclic_Directed_Graph_Using_Dfs(nbr, visited, dfsVisited))
                    return true;
            }
            else if (dfsVisited[nbr])
            {
                return true;
            }
        }
        dfsVisited[src] = false;
        return false;
    }
};

int main()
{
    Graph<int> g;
    int n = 5;
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 1);
    g.addEdge(4, 0, 1);

    g.printAdjacencyList();
    cout << endl;

    bool ans = false;
    unordered_map<int, bool> visited;
    unordered_map<int, bool> dfsVisited;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            ans = g.check_Cyclic_Directed_Graph_Using_Dfs(i, visited, dfsVisited);
            if (ans)
                break;
        }
    }

    cout << (ans ? "Cycle is Present" : "Cycle Absent") << endl;

    return 0;
}
