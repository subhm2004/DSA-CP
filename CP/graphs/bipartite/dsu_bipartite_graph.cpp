// ════════════════════════════════════════════════════════════════════════════
// BIPARTITE CHECK — DSU with Parity (XOR Trick)
// ────────────────────────────────────────────────────────────────────────────
// parity[x] = node x aur uske root ke beech kitne edges (mod 2)
// Bipartite me adjacent nodes ka parity opposite hona chahiye (XOR = 1)
// Same component me merge karte waqt parity maintain karo
// Agar same root pe (xu XOR xv) != 1 → NOT bipartite
// Time: O(E × α(V))  |  Space: O(V)
// ════════════════════════════════════════════════════════════════════════════

#include <bits/stdc++.h>
using namespace std;

class DSU
{
public:
    vector<int> parent, rank, parity; // parity = root se relative color (0/1)

    // Step 1: parent, rank, parity arrays size n resize karo.
    // Step 2: parity[i] = 0 initially — node apne root se same "color" (relative).
    // Step 3: parent[i] = i — har node alag component; bipartite check edges se hoga.
    DSU(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        parity.resize(n, 0);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    // Step 1: parent[x] == x ho to root mil gaya — return {x, 0}.
    // Step 2: Warna recursively find(parent[x]) se {root, p} nikalo.
    // Step 3: Path compression: parent[x] = root; parity[x] ^= p — root tak ka XOR accumulate.
    // Step 4: Return {root, parity[x]} — x ka root aur root se relative color (0/1).
    // Step 5: Parity batata hai node root se even/odd edges door hai — bipartite constraint ke liye.
    pair<int, int> find(int x)
    {
        if (parent[x] == x)
            return {x, 0}; // root — parity 0

        auto [root, p] = find(parent[x]);

        parent[x] = root;   // path compression
        parity[x] ^= p;     // accumulated parity root tak

        return {parent[x], parity[x]};
    }

    // Step 1: find(u) aur find(v) se roots aur parities nikalo — (pu,xu), (pv,xv).
    // Step 2: Same root ho to check (xu XOR xv) == 1 — adjacent nodes opposite color hone chahiye.
    // Step 3: XOR != 1 matlab same color constraint violate → NOT bipartite, false return.
    // Step 4: Alag roots ho to merge karo — parity set karo taaki u,v opposite rahein (XOR trick).
    // Step 5: Union by rank se chhoti tree badi ke neeche attach — true return (constraint OK).
    bool unionByRank(int u, int v)
    {
        auto [pu, xu] = find(u);
        auto [pv, xv] = find(v);

        if (pu == pv)
        {
            // same component — u aur v opposite hone chahiye (XOR = 1)
            return ((xu ^ xv) == 1);
        }

        // alag components — merge karo, parity set karo taaki u,v opposite rahein
        if (rank[pu] < rank[pv])
        {
            parent[pu] = pv;
            parity[pu] = xu ^ xv ^ 1;
        }
        else if (rank[pu] > rank[pv])
        {
            parent[pv] = pu;
            parity[pv] = xu ^ xv ^ 1;
        }
        else
        {
            parent[pv] = pu;
            parity[pv] = xu ^ xv ^ 1;
            rank[pu]++;
        }

        return true;
    }
};

class Solution
{
public:
    // Step 1: Edges se undirected adjacency list banao — har edge dono taraf add.
    // Step 2: DSU(n) object banao parity tracking ke saath.
    // Step 3: Har edge (u,v) par unionByRank(u,v) call karo — parity constraint check.
    // Step 4: Koi bhi union false return kare → graph bipartite NAHI hai.
    // Step 5: Saari edges pass ho jayein → true — 2-coloring possible hai.
    bool isBipartite(int n, vector<vector<int>> &edges)
    {
        unordered_map<int, list<int>> adjList;

        for (auto &e : edges)
        {
            int u = e[0], v = e[1];
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }

        DSU dsu(n);

        // Har edge pe parity constraint check karo
        for (auto &it : adjList)
        {
            int u = it.first;

            for (int v : it.second)
            {
                if (!dsu.unionByRank(u, v))
                    return false;
            }
        }

        return true;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> edges;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
    }

    Solution obj;

    if (obj.isBipartite(n, edges))
        cout << "Graph is Bipartite\n";
    else
        cout << "Graph is NOT Bipartite\n";

    return 0;
}
