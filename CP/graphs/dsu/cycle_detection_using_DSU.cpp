// ════════════════════════════════════════════════════════════════════════════
// CYCLE DETECTION — Union Find (DSU)
// ────────────────────────────────────────────────────────────────────────────
// Undirected graph mein: edge add karte waqt agar u aur v pehle se
// same component mein hain → ye edge cycle banayegi → cycle detected!
// Kruskal's MST mein bhi yahi trick use hoti hai.
// ════════════════════════════════════════════════════════════════════════════

#include <iostream>
#include <unordered_map>
#include <list>
#include <tuple>

using namespace std;

class UnionFind
{
public:
    vector<int> parent;
    vector<int> rank;

    // Step 1: parent array size n — har node apna khud ka set.
    // Step 2: rank array 0 se initialize — shuru mein sab single-node trees.
    // Step 3: parent[i] = i for all i — n disjoint sets ready.
    UnionFind(int n) : parent(n), rank(n, 0)
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    // Step 1: parent[i] == i ho to i root hai — return i.
    // Step 2: Warna recursively parent chain follow karo.
    // Step 3: Path compression: parent[i] = find(parent[i]) — direct root link banao.
    // Step 4: Root return — cycle check mein find(u) == find(v) fast compare hoga.
    int find(int i)
    {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    // Step 1: x aur y ke roots nikalo — find(x), find(y).
    // Step 2: Same root ho to already connected — return (cycle check pehle ho chuka).
    // Step 3: Chhoti rank wale ko badi rank ke neeche attach karo.
    // Step 4: Equal rank ho to ek root choose karo aur rank++ karo.
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
    unordered_map<int, list<int>> adjList;
    vector<tuple<int, int, int>> edges;

    // Step 1: adjList mein edge store karo aur edges vector mein tuple push karo.
    // Step 2: Undirected ho to reverse edge bhi add karo (direction == 0).
    // Step 3: hasCycle() edges vector iterate karke DSU par check karega.
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

    // Step 1: Fresh UnionFind banao graph ke node count ke saath.
    // Step 2: Har edge (u,v) ke liye pehle find(u) aur find(v) compare karo.
    // Step 3: Agar find(u) == find(v) → u aur v pehle se connected → ye edge cycle banayegi → true!
    // Step 4: Warna unionByRank(u,v) karo — components merge karo aage ki edges ke liye.
    // Step 5: Saari edges safe process ho jayein to false — graph acyclic hai.
    bool hasCycle()
    {
        UnionFind uf(adjList.size());
        for (auto &edge : edges)
        {
            int u = get<0>(edge);
            int v = get<1>(edge);
            if (uf.find(u) == uf.find(v))
            {
                return true; // u aur v pehle se connected — nayi edge cycle banayegi
            }
            uf.unionByRank(u, v);
        }
        return false;
    }
};

int main()
{
    Graph g;

    g.addEdge(0, 1, 10, 0);
    g.addEdge(0, 2, 6, 0);
    g.addEdge(0, 3, 5, 0);
    g.addEdge(1, 3, 15, 0);
    g.addEdge(2, 3, 4, 0); // ye graph mein cycle hai (triangle 0-2-3-0 type)

    if (g.hasCycle())
    {
        cout << "Graph contains a cycle" << endl;
    }
    else
    {
        cout << "Graph does not contain a cycle" << endl;
    }

    return 0;
}
