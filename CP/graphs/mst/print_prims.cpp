#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// PRIM'S MST — edges + total weight print karna
// ────────────────────────────────────────────────────────────────────────────
// Greedy: ek vertex se shuru (key[0]=0), har step pe sabse chhoti "key"
//         wala node jo abhi MST me nahi hai usko add karo, neighbors ki key update.
// key[v] = MST se v tak minimum edge weight
// parent[v] = MST me v ka parent (edge reconstruct karne ke liye)
// Time: O(V²) is implementation me (linear min search)  |  Space: O(V+E)
// ════════════════════════════════════════════════════════════════════════════

class Solution
{
public:
    unordered_map<int, list<pair<int, int>>> adjList; // u -> [(v, weight), ...]

    // Edge add: direction=0 undirected, 1 directed
    void addEdge(int u, int v, int w, bool direction)
    {
        adjList[u].push_back({v, w});
        if (!direction)
        {
            adjList[v].push_back({u, w}); // undirected -> reverse bhi
        }
    }

    // ── MST me abhi nahi aaya, sabse chhoti key wala node ──────────────────
    int get_min_value_node(unordered_map<int, int> &key, unordered_map<int, bool> &mst)
    {
        int temp = INT_MAX, index = -1;
        for (auto &[node, weight] : key)
        {
            if (!mst[node] && weight < temp)
            {
                temp = weight;
                index = node;
            }
        }
        return index; // -1 matlab koi node nahi mila (disconnected)
    }

    // ── Prim's: MST weight + edge list return ────────────────────────────────
    tuple<int, vector<tuple<int, int, int>>> Prims_Algo(int V)
    {
        unordered_map<int, int> key;    // min edge weight to reach each vertex from MST
        unordered_map<int, bool> mst;   // kya vertex MST me hai?
        unordered_map<int, int> parent; // MST tree me parent

        for (int i = 0; i < V; i++)
        {
            key[i] = INT_MAX;
            mst[i] = false;
            parent[i] = -1;
        }

        key[0] = 0; // node 0 se start — pehla pick hoga

        // V baar loop — har baar ek naya vertex MST me
        for (int i = 0; i < V; i++)
        {
            int u = get_min_value_node(key, mst);
            if (u == -1)
                break; // disconnected graph

            mst[u] = true;

            // u ke saare neighbors ki key relax karo
            for (auto &edge : adjList[u])
            {
                int v = edge.first, w = edge.second;
                if (!mst[v] && w < key[v])
                {
                    key[v] = w;
                    parent[v] = u;
                }
            }
        }

        // MST edges collect karke total weight nikalo
        int sum = 0;
        vector<tuple<int, int, int>> mstEdges;
        for (int u = 0; u < V; ++u)
        {
            if (parent[u] == -1)
                continue; // root (0) ka parent nahi

            for (auto &edge : adjList[u])
            {
                int v = edge.first, w = edge.second;
                if (v == parent[u])
                {
                    sum += w;
                    mstEdges.emplace_back(parent[u], u, w);
                    break;
                }
            }
        }
        return make_tuple(sum, mstEdges);
    }

    // ── printMST: Prim's chalao aur edges + total weight print karo ────────
    // Step 1: Prims_Algo se {weight, edge list} tuple lo.
    // Step 2: har MST edge parent-child format me print karo.
    // Step 3: ant me total MST weight dikhao.
    void printMST(int V)
    {
        auto [mstWeight, mstEdges] = Prims_Algo(V);

        cout << "Minimum Spanning Tree Edges:\n";
        for (auto &[p, u, w] : mstEdges)
        {
            cout << p << " - " << u << " (Weight: " << w << ")\n";
        }
        cout << "Total MST Weight: " << mstWeight << endl;
    }
};

int main()
{
    Solution sol;

    // ---- 5 vertex undirected demo graph ----
    sol.addEdge(0, 1, 2, 0);
    sol.addEdge(1, 2, 3, 0);
    sol.addEdge(0, 3, 6, 0);
    sol.addEdge(1, 3, 8, 0);
    sol.addEdge(1, 4, 5, 0);
    sol.addEdge(2, 4, 7, 0);

    int V = 5;
    sol.printMST(V);

    return 0;
}
