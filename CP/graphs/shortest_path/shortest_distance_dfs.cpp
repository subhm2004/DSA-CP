#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>
#include <set>
#include <limits.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// SHORTEST PATH — Multiple Approaches (BFS, Topo Sort + DFS, Dijkstra with Set)
// ────────────────────────────────────────────────────────────────────────────
// Ek hi file me teen alag techniques:
//
//   1) shortestPathBfs     — Unweighted graph, BFS se path reconstruct
//   2) topoSortDfs + shortestpathDfs — DAG pe topological order se relax
//   3) shortestDistDijkstra — Dijkstra using SET instead of priority_queue
//
// Dijkstra with set: pair{dist, node} sorted rehta hai — purana entry erase
// karke naya insert karna padta hai jab distance improve ho.
// ════════════════════════════════════════════════════════════════════════════

class graph
{
public:
    unordered_map<int, list<pair<int, int>>> adjList;  // node -> (neighbor, weight)

    // ── addEdge: weighted edge add karo (directed/undirected) ─────────────
    // direction = 1 -> undirected, 0 -> directed
    void addEdge(int u, int v, int wt, bool direction)
    {
        adjList[u].push_back({v, wt});
        if (direction == 1)
        {
            adjList[v].push_back({u, wt});
        }
    }

    // ── printAdjList: adjacency list console pe print karo ──────────────────
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

    // ── shortestPathBfs: unweighted graph me src se dest ka path (BFS) ────
    // BFS se level-order traverse — pehli baar dest tak pahunchne ka path shortest.
    // parent[] se dest se src tak backtrack, reverse karke print.
    void shortestPathBfs(int src, int dest)
    {
        queue<int> q;
        unordered_map<int, bool> visited;
        unordered_map<int, int> parent;

        // Step 1: source ko queue me daalo, visited=true, parent=-1
        q.push(src);
        visited[src] = 1;
        parent[src] = -1;

        // Step 2: BFS — level order me sab nodes explore, parent track karo
        while (!q.empty())
        {
            int fNode = q.front();
            q.pop();

            for (auto nbr : adjList[fNode])
            {
                if (!visited[nbr.first])
                {
                    q.push(nbr.first);
                    visited[nbr.first] = 1;
                    parent[nbr.first] = fNode;
                }
            }
        }

        // Step 3: dest se src tak parent follow karke path banao
        vector<int> ans;
        int node = dest;
        while (node != -1)
        {
            ans.push_back(node);
            node = parent[node];
        }

        // Step 4: reverse karke source -> dest order me print karo
        reverse(ans.begin(), ans.end());

        cout << "printing ANs: " << endl;
        for (auto i : ans)
        {
            cout << i << ", ";
        }
        cout << endl;
    }

    // ── topoSortDfs: DFS se topological order nikalo (DAG ke liye) ──────────
    // Neighbors pehle visit karo, wapas aate waqt stack me push — reverse topo order.
    void topoSortDfs(int src, unordered_map<int, bool> &visited, stack<int> &ans)
    {
        // Step 1: current node visited mark karo
        visited[src] = true;

        // Step 2: pehle saare unvisited neighbors pe DFS recurse karo
        for (auto neighbour : adjList[src])
        {
            if (!visited[neighbour.first])
            {
                topoSortDfs(neighbour.first, visited, ans);
            }
        }

        // Step 3: post-order — sab descendants ke baad node stack me push
        ans.push(src);
    }

    // ── shortestpathDfs: topo order me nodes process karke shortest path ────
    // DAG assumption: topo order me aage wale nodes pehle process ho chuke honge.
    // Har node ke neighbors relax karo — dist[top] + weight < dist[nbr] ho to update.
    void shortestpathDfs(int dest, stack<int> topoOrder, int n)
    {
        vector<int> dist(n, INT_MAX);

        // Step 1: topo stack se source nikalo, dist[source] = 0
        int src = topoOrder.top();
        topoOrder.pop();
        dist[src] = 0;

        // Step 2: source ke direct neighbors ki distance set karo
        for (auto nbr : adjList[0])
        {
            if (dist[0] + nbr.second < dist[nbr.first])
            {
                dist[nbr.first] = dist[0] + nbr.second;
            }
        }

        // Step 3: baaki nodes topo order me process — DAG me aage wale pehle done
        while (!topoOrder.empty())
        {
            int topElement = topoOrder.top();
            topoOrder.pop();

            // Step 4: sirf reachable node ke neighbors relax karo
            if (dist[topElement] != INT_MAX)
            {
                for (auto nbr : adjList[topElement])
                {
                    if (dist[topElement] + nbr.second < dist[nbr.first])
                    {
                        dist[nbr.first] = dist[topElement] + nbr.second;
                    }
                }
            }
        }

        cout << "Printing Ans: " << endl;
        for (int i = 0; i < n; i++)
        {
            cout << i << "-> " << dist[i] << endl;
        }
    }

    // ── shortestDistDijkstra: Dijkstra using SET (priority_queue ki jagah) ──
    // set<pair<dist, node>> sorted rehta hai — begin() = minimum distance node.
    // Neighbor relax pe purani entry erase karo, nayi distance se insert karo.
    void shortestDistDijkstra(int src, int n)
    {
        vector<int> dist(n, INT_MAX);
        set<pair<int, int>> st;
        // Step 1: source dist=0, set me {0, src} insert — sorted order me min pehle
        dist[src] = 0;
        st.insert(make_pair(0, src));

        // Step 2: jab tak set khali nahi, sabse chhota dist wala node process karo
        while (!st.empty())
        {
            auto topElement = *(st.begin());
            int nodeDistance = topElement.first;
            int node = topElement.second;
            st.erase(st.begin());

            // Step 3: har neighbor relax karo
            for (auto nbr : adjList[node])
            {
                if (nodeDistance + nbr.second < dist[nbr.first])
                {
                    // Step 4: purani stale entry erase karo, nayi dist se insert
                    auto result = st.find(make_pair(dist[nbr.first], nbr.first));
                    if (result != st.end())
                    {
                        st.erase(result);
                    }
                    dist[nbr.first] = nodeDistance + nbr.second;
                    st.insert(make_pair(dist[nbr.first], nbr.first));
                }
            }
        }

        cout << "printing ans:" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << dist[i] << ", ";
        }
        cout << endl;
    }
};

int main()
{
    graph g;

    g.addEdge(6, 3, 2, 1);
    g.addEdge(6, 1, 14, 1);
    g.addEdge(3, 1, 9, 1);
    g.addEdge(3, 2, 10, 1);
    g.addEdge(1, 2, 7, 1);
    g.addEdge(2, 4, 15, 1);
    g.addEdge(4, 3, 11, 1);

    g.addEdge(6, 5, 9, 1);
    g.addEdge(4, 5, 6, 1);

    g.printAdjList();

    // g.shortestDistDijkstra(6, 7);

    stack<int> topoOrder;
    unordered_map<int, bool> visited;
    g.topoSortDfs(0, visited, topoOrder);

    g.shortestpathDfs(3, topoOrder, 5);

    // int src = 0;
    // // int dest = 4;

    // g.shortestPathBfs(src, dest);

    return 0;
}
