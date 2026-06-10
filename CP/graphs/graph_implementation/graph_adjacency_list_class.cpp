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
// GRAPH ADJACENCY LIST CLASS — Shortest Path Algorithms Collection
// ────────────────────────────────────────────────────────────────────────────
// Weighted graph (directed/undirected) ke liye common algorithms:
//   - BFS shortest path (unweighted)
//   - DFS topological sort + shortest path on DAG
//   - Floyd-Warshall (all pairs)
//   - Bellman-Ford (negative weights + cycle detect)
//   - Dijkstra (non-negative weights)
//
// direction = 0 → directed, direction = 1 → undirected (code me aise hai)
// ════════════════════════════════════════════════════════════════════════════

class graph
{
public:
    unordered_map<int, list<pair<int, int>>> adjList;

    // Step 1: adjList[u] mein {v, wt} pair push karo — directed edge u->v.
    // Step 2: direction == 1 (undirected) ho to adjList[v] mein {u, wt} bhi push karo.
    // Step 3: direction == 0 matlab directed — sirf ek taraf edge store hogi.
    // Step 4: Weighted adjacency list ready — shortest path algorithms isi par chalenge.
    void addEdge(int u, int v, int wt, bool direction)
    {
        // direction = 1 -> undirected graph
        // direction => 0 -> directed graph;
        adjList[u].push_back({v, wt});
        if (direction == 1)
        {
            adjList[v].push_back({u, wt});
        }
    }

    // Step 1: adjList ki har node entry iterate karo.
    // Step 2: Node -> neighbors print karo, har neighbor (node, weight) format mein.
    // Step 3: Debugging ke liye poora weighted graph structure console pe dikhao.
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

    // Step 1: src ko queue mein push karo, visited[src]=true, parent[src]=-1.
    // Step 2: BFS chalao — har unvisited neighbor ko queue mein daalo, parent track karo.
    // Step 3: BFS poora graph cover karega — parent array se dest tak backtrack karo.
    // Step 4: dest se parent chain follow karke ans vector mein nodes collect karo.
    // Step 5: ans ko reverse karke print — src se dest ka shortest path (unweighted).
    void shortestPathBfs(int src, int dest)
    {
        queue<int> q;
        unordered_map<int, bool> visited;
        unordered_map<int, int> parent;

        // inital steps for src
        q.push(src);
        visited[src] = 1;
        parent[src] = -1;

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

        // store path in ans, after traversing in the parent array
        vector<int> ans;
        int node = dest;
        while (node != -1)
        {
            ans.push_back(node);
            node = parent[node];
        }

        reverse(ans.begin(), ans.end());

        cout << "printing ANs: " << endl;
        for (auto i : ans)
        {
            cout << i << ", ";
        }
        cout << endl;
    }

    // Step 1: visited[src] = true mark karo — current node processing shuru.
    // Step 2: Har unvisited neighbor ke liye recursively topoSortDfs call karo.
    // Step 3: Pehle saare descendants completely visit hone do (post-order DFS).
    // Step 4: Wapas aate waqt src ko stack mein push karo — finish order store hota hai.
    // Step 5: Stack pop karne se valid topological order milta hai (DAG pe).
    void topoSortDfs(int src, unordered_map<int, bool> &visited, stack<int> &ans)
    {

        visited[src] = true;

        for (auto neighbour : adjList[src])
        {
            if (!visited[neighbour.first])
            {
                topoSortDfs(neighbour.first, visited, ans);
            }
        }

        // while returning, store the node in stack
        cout << "Pushing " << src << endl;
        ans.push(src);
    }

    // Step 1: dist array INT_MAX se initialize; topo stack se source nikalo, dist[src]=0.
    // Step 2: Source ke direct neighbors relax karo — dist[nbr] = dist[src] + weight.
    // Step 3: Topo order mein baaki nodes process karo — pehle prerequisites, phir current.
    // Step 4: Agar dist[node] valid hai to uske neighbors relax karo (DAG shortest path).
    // Step 5: Final dist array print — har node tak minimum distance from source.
    void shortestpathDfs(int dest, stack<int> topoOrder, int n)
    {
        vector<int> dist(n, INT_MAX);

        int src = topoOrder.top();
        topoOrder.pop();
        dist[src] = 0;

        for (auto nbr : adjList[0])
        {
            if (dist[0] + nbr.second < dist[nbr.first])
            {
                dist[nbr.first] = dist[0] + nbr.second;
            }
        }

        while (!topoOrder.empty())
        {

            int topElement = topoOrder.top();
            topoOrder.pop();

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

    // Step 1: n×n dist matrix banao — diagonal 0, direct edges adjList se fill, baaki INF.
    // Step 2: Har helper node k = 0..n-1 ke liye saare pairs (src, dest) relax karo.
    // Step 3: dist[src][dest] = min(dist[src][dest], dist[src][k] + dist[k][dest]).
    // Step 4: Helper k allow karke indirect paths try karte hain — all-pairs shortest path.
    // Step 5: Final dist matrix print — har node pair ka minimum distance.
    void floydWarshal(int n)
    {
        vector<vector<int>> dist(n, vector<int>(n, 1e9));
        // diagnol pr zero mark krdo
        for (int i = 0; i < n; i++)
        {
            dist[i][i] = 0;
        }
        // graph k according dist insert krdia h
        for (auto t : adjList)
        {
            for (auto nbr : t.second)
            {
                int u = t.first;
                int v = nbr.first;
                int wt = nbr.second;
                dist[u][v] = wt;
            }
        }

        for (int helper = 0; helper < n; helper++)
        {
            for (int src = 0; src < n; src++)
            {
                for (int dest = 0; dest < n; dest++)
                {
                    dist[src][dest] = min(dist[src][dest], dist[src][helper] + dist[helper][dest]);
                }
            }
        }

        cout << "Printing distance array: " << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << dist[i][j] << ", ";
            }
            cout << endl;
        }
    }

    // Step 1: dist[src] = 0, baaki INT_MAX — single source shortest path setup.
    // Step 2: n-1 rounds mein har edge (u,v,wt) relax karo: dist[v] = min(dist[v], dist[u]+wt).
    // Step 3: n-1 rounds guarantee shortest path (no negative cycle case).
    // Step 4: Ek extra round — agar koi dist improve ho to negative cycle present hai!
    // Step 5: Cycle status aur final dist array print karo.
    void bellmanFordAlgo(int n, int src)
    {
        // assuming directed weightted graph
        vector<int> dist(n, INT_MAX);
        dist[src] = 0;
        // n-1 relaxation step
        for (int i = 0; i < n - 1; i++)
        {
            // for all edges
            for (auto t : adjList)
            {
                for (auto nbr : t.second)
                {
                    int u = t.first;
                    int v = nbr.first;
                    int wt = nbr.second;
                    if (dist[u] != INT_MAX && dist[u] + wt < dist[v])
                    {
                        dist[v] = dist[u] + wt;
                    }
                }
            }
        }

        // to check for -ve cycle
        bool negativeCycle = false;
        for (auto t : adjList)
        {
            for (auto nbr : t.second)
            {
                int u = t.first;
                int v = nbr.first;
                int wt = nbr.second;
                if (dist[u] != INT_MAX && dist[u] + wt < dist[v])
                {
                    negativeCycle = true;
                    break;
                }
            }
        }

        if (negativeCycle == true)
            cout << "-ve cycle present" << endl;
        else
            cout << "-ve cycle absent" << endl;

        cout << "printing dist array: ";
        for (auto i : dist)
            cout << i << " ";
        cout << endl;
    }

    // Step 1: dist[src]=0, set mein {0, src} insert — priority by distance (set sorted).
    // Step 2: Set se smallest distance wala node nikalo — greedy choice.
    // Step 3: Har neighbor relax karo — better dist mile to set se purana entry hatao, naya insert.
    // Step 4: Jab tak set empty na ho — har node ka shortest distance finalize hota hai.
    // Step 5: Final dist array print — non-negative weighted graph ka shortest path.
    void shortestDistDijkstra(int src, int n)
    {
        vector<int> dist(n, INT_MAX);
        set<pair<int, int>> st;
        // intiial steps
        dist[src] = 0;
        st.insert(make_pair(0, src));

        while (!st.empty())
        {
            // fetch the smallest or first eklement from set
            auto topElement = *(st.begin());
            int nodeDistance = topElement.first;
            int node = topElement.second;

            // pop from set
            st.erase(st.begin());

            // neighbour traverse

            for (auto nbr : adjList[node])
            {
                if (nodeDistance + nbr.second < dist[nbr.first])
                {
                    // mujhe distance update krna h
                    // finding entry in set
                    auto result = st.find(make_pair(dist[nbr.first], nbr.first));
                    // if found, then remove
                    if (result != st.end())
                    {
                        st.erase(result);
                    }
                    // updation in dist array and set
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

    g.addEdge(0, 1, -1, 0);
    g.addEdge(1, 4, 2, 0);
    g.addEdge(1, 2, 3, 0);

    g.addEdge(1, 3, 2, 0);
    g.addEdge(0, 2, 4, 0);
    g.addEdge(3, 1, 1, 0);

    g.addEdge(4, 3, -3, 0);
    g.addEdge(3, 2, 5, 0);
    // g.addEdge(3,1,1,0);
    // g.addEdge(6,3,2,1);
    // g.addEdge(6,1,14,1);
    // g.addEdge(3,1,9,1);
    // g.addEdge(3,2,10,1);
    // g.addEdge(1,2,7,1);
    // g.addEdge(2,4,15,1);
    // g.addEdge(4,3,11,1);

    // g.addEdge(6,5,9,1);
    // g.addEdge(4,5,6,1);

    g.printAdjList();
    // g.floydWarshal(4);
    g.bellmanFordAlgo(5, 0);
    // g.shortestDistDijkstra(0,3);

    // stack<int> topoOrder;
    // unordered_map<int, bool> visited;
    // g.topoSortDfs(0, visited, topoOrder);

    // g.shortestpathDfs(3, topoOrder,5);

    // int src = 0;
    // // int dest = 4;

    // g.shortestPathBfs(src, dest);

    return 0;
}
