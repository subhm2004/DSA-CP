#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <algorithm>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// TARJAN'S ALGORITHM — Articulation Points + Bridges
// ────────────────────────────────────────────────────────────────────────────
// Articulation Point (cut vertex): node jiski hataane se components badh jaate
// Bridge (cut edge): edge jiski hataane se graph tut jaata hai
//
// Dono ke liye DFS + disc[] + low[] same tarah se:
//   Bridge (u,v):     low[v] > disc[u]
//   Articulation u:
//     - root hai aur DFS tree me >1 bacche
//     - non-root aur kisi bacche ka low >= disc[u] (bacha ancestors tak nahi)
//
// Time: O(V + E)  |  Space: O(V)
// ════════════════════════════════════════════════════════════════════════════

class Graph
{
public:
    unordered_map<int, list<int>> adjList;

    // ── addEdge: edge add — direction=1 undirected, 0 directed ─────────────
    void addEdge(int u, int v, bool direction)
    {
        adjList[u].push_back(v);
        if (direction == 1)
        {
            adjList[v].push_back(u);
        }
    }

    // ── Articulation points DFS ────────────────────────────────────────────
    void find_Articulation_Points_DFS(
        int currentNode,
        int parentNode,
        int &timer,
        vector<int> &discoveryTime,
        vector<int> &lowestTime,
        unordered_map<int, bool> &visited,
        unordered_map<int, bool> &articulation_Points,
        int &childCount)
    {
        // Step 1: node visit, disc[] aur low[] assign karo
        visited[currentNode] = true;
        discoveryTime[currentNode] = timer;
        lowestTime[currentNode] = timer;
        timer++;
        childCount = 0;

        for (auto neighbor : adjList[currentNode])
        {
            if (neighbor == parentNode)
                continue;

            if (!visited[neighbor])
            {
                childCount++;
                find_Articulation_Points_DFS(neighbor, currentNode, timer,
                                             discoveryTime, lowestTime, visited,
                                             articulation_Points, childCount);
                lowestTime[currentNode] = min(lowestTime[currentNode], lowestTime[neighbor]);

                // Step 2: root node aur 2+ DFS children → articulation point
                if (parentNode == -1 && childCount > 1)
                {
                    articulation_Points[currentNode] = true;
                }

                // Step 3: non-root aur low[child] >= disc[u] → u articulation
                if (parentNode != -1 && lowestTime[neighbor] >= discoveryTime[currentNode])
                {
                    articulation_Points[currentNode] = true;
                }
            }
            else
            {
                lowestTime[currentNode] = min(lowestTime[currentNode], discoveryTime[neighbor]);
            }
        }
    }

    void findArticulation_Points(int n, vector<int> &articulation_PointsVector)
    {
        vector<int> discoveryTime(n, -1);
        vector<int> lowestTime(n, -1);
        unordered_map<int, bool> visited;
        unordered_map<int, bool> articulation_PointsMap;
        int timer = 0;

        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                int childCount = 0;
                find_Articulation_Points_DFS(i, -1, timer, discoveryTime, lowestTime,
                                             visited, articulation_PointsMap, childCount);
            }
        }

        for (auto point : articulation_PointsMap)
        {
            if (point.second)
            {
                articulation_PointsVector.push_back(point.first);
            }
        }
    }

    // ── Bridges DFS ─────────────────────────────────────────────────────────
    void findBridgesDFS(
        int currentNode,
        int parentNode,
        int &timer,
        vector<int> &discoveryTime,
        vector<int> &lowestTime,
        unordered_map<int, bool> &visited,
        vector<pair<int, int>> &ans)
    {
        visited[currentNode] = true;
        discoveryTime[currentNode] = timer;
        lowestTime[currentNode] = timer;
        timer++;

        for (auto neighbor : adjList[currentNode])
        {
            if (neighbor == parentNode)
                continue;

            if (!visited[neighbor])
            {
                findBridgesDFS(neighbor, currentNode, timer, discoveryTime,
                               lowestTime, visited, ans);

                lowestTime[currentNode] = min(lowestTime[currentNode], lowestTime[neighbor]);

                if (lowestTime[neighbor] > discoveryTime[currentNode])
                {
                    ans.push_back({currentNode, neighbor});
                }
            }
            else
            {
                lowestTime[currentNode] = min(lowestTime[currentNode], discoveryTime[neighbor]);
            }
        }
    }

    void findBridges(int n)
    {
        vector<int> discoveryTime(n, -1);
        vector<int> lowestTime(n, -1);
        unordered_map<int, bool> visited;
        int timer = 0;
        vector<pair<int, int>> ans;

        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                findBridgesDFS(i, -1, timer, discoveryTime, lowestTime, visited, ans);
            }
        }

        cout << "Bridges in the graph are:" << endl;
        for (auto bridge : ans)
        {
            cout << bridge.first << " -- " << bridge.second << endl;
        }
    }
};

int main()
{
    Graph g;

    // ---- Fixed demo: expected bridges (1,3), (3,4); articulation 1, 3 ----
    //     0
    //    / \
    //   1---2
    //   |
    //   3---4
    int n = 5, m = 5;
    cout << "Enter the number of nodes and edges: " << endl;
    cout << "Number of nodes: " << n << ", Number of edges: " << m << endl;

    vector<pair<int, int>> edges = {
        {0, 1},
        {0, 2},
        {1, 2},
        {1, 3},
        {3, 4}
    };

    cout << "Enter the edges (u v): " << endl;
    for (auto edge : edges)
    {
        int u = edge.first;
        int v = edge.second;
        cout << u << " " << v << endl;
        g.addEdge(u, v, 1);
    }

    vector<int> articulation_PointsVector;

    cout << "\n=== ALGORITHM EXECUTION ===" << endl;
    g.findBridges(n);
    g.findArticulation_Points(n, articulation_PointsVector);

    cout << "\nArticulation points in the graph are:" << endl;
    for (int point : articulation_PointsVector)
    {
        cout << point << endl;
    }

    return 0;
}
