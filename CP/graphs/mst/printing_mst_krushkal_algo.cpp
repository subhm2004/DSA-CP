#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// KRUSKAL'S MST — edges print karke (Union-Find / DSU)
// ────────────────────────────────────────────────────────────────────────────
// Idea: saari edges ko weight ke hisaab se sort karo, phir chhoti se badi edge
//       uthao — agar cycle nahi banegi (DSU se check) to MST me daal do.
// MST me exactly (n-1) edges hoti hain jab graph connected ho.
// Time: O(E log E) sorting ki wajah se  |  Space: O(V)
// ════════════════════════════════════════════════════════════════════════════

class UnionFind
{
public:
    vector<int> parent;  // parent[i] = i ka set representative (root)
    vector<int> rank;    // rank[i] = tree ki approximate height (union by rank ke liye)

    // Constructor: har node apna alag set (parent[i]=i), rank sab 0
    UnionFind(int n) : parent(n), rank(n, 0)
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = i; // shuru me har node khud ka parent hai
        }
    }

    // ── find: node i ka root dhundho (path compression ke saath) ───────────
    // Path compression: return karte waqt saare beech ke nodes ko seedha root se jod do
    // taaki agli baar find() fast ho.
    int find(int i)
    {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]); // recursive find + path compression
    }

    // ── unionByRank: do sets ko merge karo ───────────────────────────────────
    // Agar x aur y pehle se same set me hain -> kuch mat karo (cycle ban jayegi).
    // Warna chhoti rank wale tree ko badi rank wale ke neeche chipka do.
    void unionByRank(int x, int y)
    {
        int x_parent = find(x);
        int y_parent = find(y);

        if (x_parent == y_parent)
            return; // dono same component me — edge add karne se cycle

        if (rank[x_parent] < rank[y_parent])
        {
            parent[x_parent] = y_parent; // chhota tree bade ke under
        }
        else if (rank[x_parent] > rank[y_parent])
        {
            parent[y_parent] = x_parent;
        }
        else
        {
            parent[x_parent] = y_parent;
            rank[y_parent]++; // same rank merge -> nayi root ki rank badhao
        }
    }
};

class Graph
{
public:
    vector<tuple<int, int, int>> edges; // har edge = (u, v, weight)

    // Graph me weighted edge add karo (undirected assume — ek baar store)
    // ── addEdge: edge list me (u, v, weight) tuple store karo ──────────────
    void addEdge(int u, int v, int weight)
    {
        edges.push_back({u, v, weight});
    }

    // ── Kruskal MST: total weight return + chosen edges print ────────────────
    int kruskalMST(int n)
    {
        // Step 1: edges ko weight se ascending sort
        sort(edges.begin(), edges.end(), [](const tuple<int, int, int> &a, const tuple<int, int, int> &b)
             {
                 return get<2>(a) < get<2>(b); // get<2> = weight compare
             });

        UnionFind uf(n);
        int mstWeight = 0;

        cout << "Edges in the Minimum Spanning Tree:" << endl;

        // Step 2: sorted order me har edge try karo
        for (auto &edge : edges)
        {
            int u = get<0>(edge);
            int v = get<1>(edge);
            int weight = get<2>(edge);

            // Agar u aur v alag components me hain -> safe, MST me lo
            if (uf.find(u) != uf.find(v))
            {
                uf.unionByRank(u, v);
                mstWeight += weight;
                cout << u << " - " << v << " (Weight: " << weight << ")" << endl;
            }
            // warna skip — cycle ban jati
        }

        return mstWeight;
    }
};

int main()
{
    Graph g;
    int n = 6; // nodes 0..5 (note: demo graph fully connected nahi ho sakta)

    // ---- Demo weighted edges ----
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);

    int mstWeight = g.kruskalMST(n);
    cout << "Total weight of the Minimum Spanning Tree: " << mstWeight << endl;

    return 0;
}
