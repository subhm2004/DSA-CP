#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <map>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// CHECK IF TWO NODES ON SAME DFS PATH — Euler Tour / In-Out Time Technique
// ────────────────────────────────────────────────────────────────────────────
// DFS traversal me har node ko do timestamps milti hain:
//   inTime[u]  = jab node u pe enter kiye
//   outTime[u] = jab node u se completely wapas aaye (subtree khatam)
//
// Node v, node u ke subtree me hai IFF:
//   inTime[u] < inTime[v]  AND  outTime[u] > outTime[v]
//
// Agar ye condition kisi direction me true hai -> dono nodes same root-to-leaf
// path pe hain (ek dusre ka ancestor-descendant relationship).
// Time: O(V + E) preprocessing  |  Query: O(1)
// ════════════════════════════════════════════════════════════════════════════

class Solution
{
public:
    unordered_map<int, list<pair<int, int>>> adjList; // Weighted adjacency list (for directed/undirected graph)
    map<int, vector<int>> adjMap;                     // Unweighted adjacency list (for DFS path checking)
    vector<int> inTime, outTime;
    vector<bool> visited;
    int timer = 0;

    // ── addEdge: directed/undirected edge dono lists me add karo ────────────
    // adjList = weighted edges, adjMap = unweighted (DFS in-out time ke liye)
    void addEdge(int u, int v, int w, bool direction)
    {
        adjList[u].push_back({v, w}); // Add weighted edge to adjList
        if (!direction)
        {
            adjList[v].push_back({u, w}); // Add reverse edge if undirected
        }

        adjMap[u].push_back(v); // Add unweighted edge to adjMap
        if (!direction)
        {
            adjMap[v].push_back(u); // Add reverse edge for undirected graph
        }
    }

    // ── dfs: DFS traversal karke inTime aur outTime fill karo ─────────────
    // Enter pe inTime[node] = ++timer, sab children visit karo, exit pe outTime[node] = ++timer.
    void dfs(int start)
    {
        // Step 1: node enter — visited=true, inTime assign
        visited[start] = true;
        inTime[start] = ++timer;

        // Step 2: saare unvisited children pe recurse
        for (auto x : adjMap[start])
        {
            if (!visited[x])
                dfs(x);
        }

        // Step 3: subtree khatam — outTime assign (Euler tour interval)
        outTime[start] = ++timer;
    }

    // ── onSamePath: kya u aur v same DFS path pe hain? ─────────────────────
    // Check karo: kya ek node dusre ke subtree me hai (in-out time se).
    // Dono directions check — u ancestor of v YA v ancestor of u.
    bool onSamePath(int u, int v)
    {
        // Step 1: check karo kya u, v ka ancestor hai (in-out interval nesting)
        // Step 2: ya v, u ka ancestor hai — dono me se koi bhi true ho to same path
        return ((inTime[u] < inTime[v] && outTime[u] > outTime[v]) ||
                (inTime[v] < inTime[u] && outTime[v] > outTime[u]));
    }

    // ── printGraph: weighted adjacency list print karo ─────────────────────
    void printGraph()
    {
        for (auto &pair : adjList)
        {
            cout << pair.first << " -> ";
            for (auto &neighbor : pair.second)
            {
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }

    // ── printAdjMap: unweighted adjacency list print karo ────────────────────
    void printAdjMap()
    {
        for (auto &pair : adjMap)
        {
            cout << pair.first << " -> ";
            for (auto &neighbor : pair.second)
            {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    Solution graph;

    // Graph me edges add karo
    graph.addEdge(1, 2, 4, false); // Undirected edge with weight 4 between 1 and 2
    graph.addEdge(1, 3, 5, true);  // Directed edge with weight 5 from 1 to 3
    graph.addEdge(2, 3, 6, false); // Undirected edge with weight 6 between 2 and 3

    // Weighted graph print karo
    cout << "Adjacency List with Weights:\n";
    graph.printGraph();

    // Unweighted graph print karo (DFS ke liye)
    cout << "\nAdjacency List for DFS Traversal:\n";
    graph.printAdjMap();

    // DFS ke liye inTime/outTime arrays initialize karo
    int V = 9;
    graph.inTime.resize(V + 1, 0); // V+1 for 1-based indexing
    graph.outTime.resize(V + 1, 0);
    graph.visited.resize(V + 1, false);

    // Node 1 se DFS start karo — inTime/outTime fill honge
    graph.dfs(1);

    // Queries: kya ye node pairs same path pe hain?
    cout << "\nPath Check Queries:\n";
    cout << (graph.onSamePath(1, 5) ? "Yes\n" : "No\n");
    cout << (graph.onSamePath(2, 9) ? "Yes\n" : "No\n");
    cout << (graph.onSamePath(2, 6) ? "Yes\n" : "No\n");

    return 0;
}
