#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <tuple>

using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// GRAPH REVERSAL — Directed Graph ki saari edges ulta kar do
// ────────────────────────────────────────────────────────────────────────────
// Original: u -> v  becomes  Reversed: v -> u
// Undirected edges add karte waqt dono direction store hoti hain, reverse
// karne pe effectively swap ho jati hain.
// ════════════════════════════════════════════════════════════════════════════

class Graph
{
public:
    unordered_map<int, list<int>> adjList;
    vector<tuple<int, int, int>> edges;

    // Step 1: adjList[u] mein v push karo aur edges vector mein (u,v,weight) tuple store karo.
    // Step 2: direction == 0 (undirected) ho to v->u reverse edge bhi add karo.
    // Step 3: direction != 0 matlab directed u->v — sirf ek direction store hogi.
    // Step 4: reverseGraph() baad mein har u->v ko v->u mein badlega.
    void addEdge(int u, int v, int weight, bool direction)
    {
        adjList[u].push_back(v);
        edges.push_back({u, v, weight});

        if (direction == 0)
        {
            adjList[v].push_back(u);
            edges.push_back({v, u, weight});
        }
    }

    // Step 1: Naya empty reversedAdjList map banao.
    // Step 2: Original adjList ki har entry (u -> neighbors) iterate karo.
    // Step 3: Har edge u->v ke liye reversedAdjList[v].push_back(u) karo — direction ulta.
    // Step 4: Poora reversed map banne ke baad adjList = reversedAdjList assign karo.
    // Step 5: Ab graph ulta hai — topological sort / Kosaraju mein useful hota hai.
    void reverseGraph()
    {
        unordered_map<int, list<int>> reversedAdjList;

        for (auto &pair : adjList)
        {
            int u = pair.first;
            for (int v : pair.second)
            {
                reversedAdjList[v].push_back(u);
            }
        }

        adjList = reversedAdjList;
    }

    // Step 1: adjList ki har node-neighbor pair iterate karo.
    // Step 2: Node print karo, arrow, phir saare neighbors space-separated.
    // Step 3: Har node ke baad newline — original vs reversed compare karne ke liye.
    void printGraph()
    {
        for (auto &pair : adjList)
        {
            cout << pair.first << " -> ";
            for (int v : pair.second)
            {
                cout << v << " ";
            }
            cout << endl;
        }
    }

    // Step 1: edges vector ki har tuple (u, v, w) iterate karo.
    // Step 2: get<0>, get<1>, get<2> se u, v, weight nikalo.
    // Step 3: "(u, v, w)" format mein print karo — original edge list dikhao.
    // Step 4: Note: reverseGraph() sirf adjList badalta hai, edges vector original rehta hai.
    void printEdges()
    {
        for (auto &edge : edges)
        {
            int u = get<0>(edge);
            int v = get<1>(edge);
            int w = get<2>(edge);
            cout << "(" << u << ", " << v << ", " << w << ")" << endl;
        }
    }
};

int main()
{
    Graph g;

    g.addEdge(0, 1, 10, 1);
    g.addEdge(1, 2, 20, 1);
    g.addEdge(2, 3, 30, 1);
    g.addEdge(3, 4, 40, 0);

    cout << "Original Graph:" << endl;
    g.printGraph();

    g.reverseGraph();

    cout << "\nReversed Graph:" << endl;
    g.printGraph();

    return 0;
}
