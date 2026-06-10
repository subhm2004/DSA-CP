#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

using cell = tuple<int, int, int>; // edge = (u, v, weight)

// ════════════════════════════════════════════════════════════════════════════
// KRUSKAL'S ALGORITHM — Minimum Spanning Tree (weight only)
// ────────────────────────────────────────────────────────────────────────────
// Greedy + Union-Find:
//   1) Saari edges weight se sort
//   2) Chhoti se badi edge lo — agar alag components connect kare (no cycle) MST me daalo
//   3) V-1 edges mil jayein to MST complete (connected graph me)
//
// Cycle check: find(u) != find(v) matlab alag sets — safe to unite
// Time: O(E log E)  |  Space: O(V)
// ════════════════════════════════════════════════════════════════════════════

class UnionFind
{
public:
    vector<int> parent;
    vector<int> rank;

    // ── Constructor: har node apna alag set — parent[i]=i, rank sab 0 ───────
    UnionFind(int n) : parent(n), rank(n, 0)
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    // ── find: node i ka root dhundho (path compression ke saath) ───────────
    // Agar parent[i]==i to i khud root hai.
    // Warna recursively root dhundho aur beech ke nodes ko seedha root se jod do.
    int find(int i)
    {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    // ── unionByRank: do sets merge karo — same root ho to cycle, skip ──────
    // Chhoti rank wale tree ko badi rank wale ke neeche chipkao.
    // Same rank merge pe nayi root ki rank badhao.
    void unionByRank(int x, int y)
    {
        int x_parent = find(x);
        int y_parent = find(y);

        if (x_parent == y_parent)
            return;

        if (rank[x_parent] < rank[y_parent])
        {
            parent[x_parent] = y_parent;
        }
        else if (rank[x_parent] > rank[y_parent])
        {
            parent[y_parent] = x_parent;
        }
        else
        {
            parent[x_parent] = y_parent;
            rank[y_parent]++;
        }
    }
};

class Graph
{
public:
    vector<cell> edges;

    // ── addEdge: edge list me (u, v, weight) store karo ────────────────────
    void addEdge(int u, int v, int weight)
    {
        edges.push_back({u, v, weight});
    }

    // ── kruskalMST: greedy + DSU se minimum spanning tree weight nikalo ───
    // Step 1: saari edges weight se sort karo (chhoti pehle).
    // Step 2: har edge try karo — alag components connect kare to MST me lo.
    // Step 3: n-1 edges mil jayein to MST complete, total weight return karo.
    int kruskalMST(int n)
    {
        sort(edges.begin(), edges.end(), [](const cell &a, const cell &b)
             {
                 return get<2>(a) < get<2>(b);
             });

        UnionFind uf(n);
        int mst_Weight = 0;
        int edges_added = 0;

        for (auto &edge : edges)
        {
            int u = get<0>(edge);
            int v = get<1>(edge);
            int weight = get<2>(edge);

            // find(u) != find(v) matlab alag sets — cycle nahi banegi
            if (uf.find(u) != uf.find(v))
            {
                uf.unionByRank(u, v);
                mst_Weight += weight;
                edges_added++;

                if (edges_added == n - 1)
                    break;
            }
        }

        return mst_Weight;
    }
};

int main()
{
    Graph g;
    int n = 6;

    // ---- Demo graph: nodes 0-3 connected, 4-5 isolated ----
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);

    // Expected MST edges: (2,3,4), (0,3,5), (0,1,10) → total 19
    cout << "Minimum Spanning Tree Weight: " << g.kruskalMST(n) << endl;

    return 0;
}
