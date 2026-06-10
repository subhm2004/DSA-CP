// ════════════════════════════════════════════════════════════════════════════
// BIPARTITE CHECK — Union-Find + 2-Coloring on Edges
// ────────────────────────────────────────────────────────────────────────────
// Har edge pe adjacent nodes ko opposite color do (0/1)
// Agar dono nodes ka color pehle se same hai → NOT bipartite
// DSU se components merge karte jao (optional connectivity track)
// Time: O(E × α(V))  |  Space: O(V)
// ════════════════════════════════════════════════════════════════════════════

#include <iostream>
#include <vector>

using namespace std;

class UnionFind
{
public:
    vector<int> parent;
    vector<int> rank;
    vector<int> color; // 0 ya 1 — bipartite 2-coloring ke liye

    // Step 1: parent aur rank arrays size n — standard DSU setup.
    // Step 2: color array -1 se initialize — -1 matlab abhi color assign nahi hua.
    // Step 3: parent[i] = i — har node alag set; color edges process karte waqt assign hoga.
    UnionFind(int n) : parent(n), rank(n, 0), color(n, -1) // -1 = abhi color assign nahi hua
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    // Step 1: parent[i] == i ho to i root hai — return i.
    // Step 2: Warna recursively parent chain follow karo.
    // Step 3: Path compression: parent[i] = find(parent[i]) — direct root link banao.
    // Step 4: Root return — connectivity check ke liye use hota hai.
    int find(int i)
    {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]); // path compression
    }

    // Step 1: find(x) aur find(y) se roots nikalo.
    // Step 2: Same root ho to already connected — false return (color check alag se hota hai).
    // Step 3: Chhoti rank wale ko badi rank ke neeche attach karo.
    // Step 4: Equal rank ho to ek root banao, rank++ — components merge ho gaye.
    bool unionByRank(int x, int y)
    {
        int x_parent = find(x);
        int y_parent = find(y);

        if (x_parent == y_parent)
            return false; // same component — color conflict check alag se hota hai

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
        return true;
    }

    // Step 1: Saare nodes ka color -1 reset karo.
    // Step 2: Har edge (u,v) par: u uncolored ho to color[u]=0 assign karo.
    // Step 3: v uncolored ho to color[v] = 1 - color[u] — neighbor ko opposite color do.
    // Step 4: Dono colored aur same color ho → odd cycle → NOT bipartite, false return.
    // Step 5: unionByRank(u,v) se components merge; saari edges OK → true return.
    bool isBipartite(int n, vector<vector<int>> &edges)
    {
        for (int i = 0; i < n; i++)
        {
            color[i] = -1;
        }

        for (auto &edge : edges)
        {
            int u = edge[0], v = edge[1];

            if (color[u] == -1)
                color[u] = 0;

            if (color[v] == -1)
                color[v] = 1 - color[u]; // neighbor ko opposite color
            else if (color[u] == color[v])
                return false; // dono same color = odd cycle

            unionByRank(u, v);
        }

        return true;
    }
};

int main()
{
    int n = 4;
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 3}, {3, 0}}; // square = bipartite

    UnionFind uf(n);
    if (uf.isBipartite(n, edges))
        cout << "Graph Bipartite hai" << endl;
    else
        cout << "Graph Bipartite nahi hai" << endl;

    return 0;
}
