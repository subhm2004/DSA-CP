#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// PRIM'S ALGORITHM — Minimum Spanning Tree (total weight)
// ────────────────────────────────────────────────────────────────────────────
// Greedy tree grow karo:
//   key[v]  = MST se v tak minimum edge weight (abhi tak)
//   mst[v]  = kya v already MST me hai?
//   parent[v] = MST me v ka parent
//
// Har iteration: sabse chhoti key wala non-MST node pick → neighbors relax
// Time: O(V²) is impl me (linear min search)  |  Space: O(V+E)
// ════════════════════════════════════════════════════════════════════════════

class Solution
{
public:
    unordered_map<int, list<pair<int, int>>> adjList;

    // ── addEdge: weighted edge add — direction=0 undirected, 1 directed ──────
    void addEdge(int u, int v, int w, bool direction)
    {
        adjList[u].push_back({v, w});
        if (!direction)
        {
            adjList[v].push_back({u, w});
        }
    }

    // ── get_min_value_node: MST me nahi aaya sabse chhoti key wala node ────
    // Sab non-MST nodes scan karo — minimum key wala index return karo.
    // -1 return matlab koi node nahi mila (disconnected graph).
    int get_min_value_node(unordered_map<int, int> &key, unordered_map<int, bool> &mst)
    {
        int temp = INT_MAX;
        int index = -1;

        for (auto &[node, weight] : key)
        {
            if (!mst[node] && weight < temp)
            {
                temp = weight;
                index = node;
            }
        }
        return index;
    }

    // ── Prims_Algo: greedy se MST ka total weight return karo ───────────────
    // Step 1: key[]=INF, mst[]=false, parent[]=-1 initialize; key[0]=0.
    // Step 2: V baar loop — min key wala non-MST node pick, MST me daalo.
    // Step 3: picked node ke neighbors ki key relax karo (chhoti edge weight).
    // Step 4: parent array se MST edges ka sum nikalo aur return karo.
    int Prims_Algo(int V)
    {
        unordered_map<int, int> key;
        unordered_map<int, bool> mst;
        unordered_map<int, int> parent;

        for (int i = 0; i < V; i++)
        {
            key[i] = INT_MAX;
            mst[i] = false;
            parent[i] = -1;
        }

        key[0] = 0;

        for (int i = 0; i < V; i++)
        {
            int u = get_min_value_node(key, mst);
            if (u == -1)
                break;

            mst[u] = true;

            for (auto &edge : adjList[u])
            {
                int v = edge.first;
                int w = edge.second;

                if (!mst[v] && w < key[v])
                {
                    key[v] = w;
                    parent[v] = u;
                }
            }
        }

        int sum = 0;
        for (int u = 0; u < V; ++u)
        {
            if (parent[u] == -1)
                continue;

            for (auto &edge : adjList[u])
            {
                int v = edge.first;
                int w = edge.second;

                if (v == parent[u])
                {
                    sum += w;
                    break;
                }
            }
        }

        return sum;
    }
};

int main()
{
    Solution sol;

    // ---- 5 vertex demo (undirected) ----
    // MST expected: 0-1(2), 1-2(3), 1-4(5), 0-3(6) → total 16
    sol.addEdge(0, 1, 2, 0);
    sol.addEdge(1, 2, 3, 0);
    sol.addEdge(0, 3, 6, 0);
    sol.addEdge(1, 3, 8, 0);
    sol.addEdge(1, 4, 5, 0);
    sol.addEdge(2, 4, 7, 0);

    int V = 5;
    cout << "Minimum Spanning Tree Weight: " << sol.Prims_Algo(V) << endl;

    return 0;
}
