// union by rank with path compression and parity check for bipartite graph
#include <bits/stdc++.h>
using namespace std;

// 🔥 DSU CLASS (Parity ke saath)
class DSU
{
public:
    vector<int> parent, rank, parity;

    DSU(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        parity.resize(n, 0);

        // parent = [0,1,2,...]
        // iota(parent.begin(), parent.end(), 0);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    // 🔍 FIND (path compression + parity)
    pair<int, int> find(int x)
    {

        // agar root hai
        if (parent[x] == x)
            return {x, 0};

        // recursion se root dhundo
        auto [root, p] = find(parent[x]);

        // path compression
        parent[x] = root;

        // parity update
        parity[x] ^= p;

        return {parent[x], parity[x]};
    }

    // 🔗 UNION BY RANK (bipartite check)
    bool unionByRank(int u, int v)
    {

        auto [pu, xu] = find(u);
        auto [pv, xv] = find(v);

        // 🧠 same component
        if (pu == pv)
        {
            // check: u aur v opposite hone chahiye
            return ((xu ^ xv) == 1);
        }

        // 🧠 different component → merge
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

// 🔥 SOLUTION CLASS
class Solution
{
public:
    bool isBipartite(int n, vector<vector<int>> &edges)
    {

        // 🔥 adjacency list using unordered_map
        unordered_map<int, list<int>> adjList;

        // graph build karo
        for (auto &e : edges)
        {
            int u = e[0], v = e[1];

            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }

        // DSU initialize
        DSU dsu(n);

        // 🔥 har edge check karo via adjList
        for (auto &it : adjList)
        {
            int u = it.first;

            for (int v : it.second)
            {

                // agar violation mila → bipartite nahi
                if (!dsu.unionByRank(u, v))
                {
                    return false;
                }
            }
        }

        return true;
    }
};

// 🔥 MAIN FUNCTION
int main()
{

    int n, m;
    cin >> n >> m;

    vector<vector<int>> edges;

    // input lo
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        edges.push_back({u, v});
    }

    Solution obj;

    if (obj.isBipartite(n, edges))
    {
        cout << "Graph is Bipartite\n";
    }
    else
    {
        cout << "Graph is NOT Bipartite\n";
    }

    return 0;
}