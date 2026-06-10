// ════════════════════════════════════════════════════════════════════════════
// CONNECTED COMPONENTS — Union Find (DSU)
// ────────────────────────────────────────────────────────────────────────────
// Har edge par union karo — end mein kitne alag roots hain = kitne components.
// find() with path compression + unionByRank se almost O(1) per operation.
// ════════════════════════════════════════════════════════════════════════════

#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <tuple>
#include <algorithm> // for max

using namespace std;

class UnionFind
{
public:
    vector<int> parent;
    vector<int> rank;

    // Step 1: parent array size n banao — har index ek node represent karta hai.
    // Step 2: rank array ko 0 se initialize karo — shuru mein har tree ki height 0.
    // Step 3: Har node i ka parent[i] = i set karo — initially har node alag component hai.
    // Step 4: Total n disjoint sets ban gaye — ab edges se merge karenge.
    UnionFind(int n) : parent(n), rank(n, 0)
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = i; // Initially, each node is its own parent
        }
    }

    // Step 1: Agar parent[i] == i hai to i khud root hai — seedha return karo.
    // Step 2: Warna recursively find(parent[i]) call karo — tree ke upar jao.
    // Step 3: Path compression: parent[i] = find(parent[i]) — saare nodes direct root point karenge.
    // Step 4: Compressed root return karo — future find() calls almost O(1) ho jayenge.
    int find(int i)
    {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]); // Path compression
    }

    // Step 1: x aur y ke respective roots dhundho — find(x) aur find(y).
    // Step 2: Agar dono same root hain to already same set mein hain — return.
    // Step 3: Chhoti rank wale root ko badi rank wale ke parent banao.
    // Step 4: Rank equal ho to koi ek root banao aur uski rank++ karo (height badhi).
    // Step 5: Union by rank se tree flat rehti hai — find() fast rehta hai.
    void unionByRank(int x, int y)
    {
        int x_parent = find(x);
        int y_parent = find(y);

        if (x_parent == y_parent)
            return; // They are already in the same set

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
            rank[y_parent]++; // Increase rank of the new root
        }
    }

    // Step 1: components counter = 0 se shuru karo.
    // Step 2: Har index i par check karo — parent[i] == i matlab i ek root/representative hai.
    // Step 3: Har root ek alag connected component represent karta hai — components++.
    // Step 4: Saare nodes scan karne ke baad total components return karo.
    int countComponents()
    {
        int components = 0;
        for (int i = 0; i < parent.size(); ++i)
        {
            if (parent[i] == i) // A root node
                components++;
        }
        return components;
    }
};

class Graph
{
public:
    unordered_map<int, list<int>> adjList;
    vector<tuple<int, int, int>> edges; // Store edges as tuples (u, v, weight)

    // Step 1: u ki adjacency list mein v add karo aur edges vector mein (u,v,weight) store karo.
    // Step 2: Undirected graph (direction==0) mein reverse edge v->u bhi add karo.
    // Step 3: DSU sirf edges vector use karega — adjList optional display ke liye hai.
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

    // Step 1: adjList ki har entry iterate karo — node aur uske neighbors.
    // Step 2: Node print karo, arrow lagao, phir saare neighbors space-separated.
    // Step 3: Har node ke baad newline — graph structure clearly dikhe.
    void printGraph()
    {
        for (auto &entry : adjList)
        {
            cout << entry.first << " -> ";
            for (auto &neighbor : entry.second)
            {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // Step 1: Graph se maximum node index nikalo — DSU size = maxNode + 1.
    // Step 2: Fresh UnionFind object banao us size ke saath.
    // Step 3: Har edge (u,v) par unionByRank(u,v) call karo — connected nodes ek set mein merge.
    // Step 4: Saari edges process hone ke baad countComponents() call karo.
    // Step 5: Kitne roots bache = kitne alag connected components hain graph mein.
    int findConnectedComponents()
    {
        int maxNode = 0;
        for (auto &entry : adjList)
        {
            maxNode = max(maxNode, entry.first);
            for (auto &neighbor : entry.second)
            {
                maxNode = max(maxNode, neighbor);
            }
        }

        UnionFind uf(maxNode + 1);

        for (auto &edge : edges)
        {
            int u = get<0>(edge);
            int v = get<1>(edge);
            uf.unionByRank(u, v); // connected nodes ko ek set mein merge
        }

        return uf.countComponents();
    }
};

int main()
{
    Graph g;

    // Component 1: 0 <-> 1 <-> 2
    g.addEdge(0, 1, 1, 0);
    g.addEdge(1, 2, 1, 0);

    // Component 2: 3 <-> 4
    g.addEdge(3, 4, 1, 0);

    // Component 3: 5 <-> 6
    g.addEdge(5, 6, 1, 0);

    // Component 4: 7 (isolated node)

    // Component 5: 8 <-> 9 <-> 10
    g.addEdge(8, 9, 1, 0);
    g.addEdge(9, 10, 1, 0);

    // Component 6: 11 <-> 12
    g.addEdge(11, 12, 1, 0);

    // Component 7: 13 (isolated node)

    // Component 8: 14 <-> 15 <-> 16
    g.addEdge(14, 15, 1, 0);
    g.addEdge(15, 16, 1, 0);

    cout << "Graph's Adjacency List:" << endl;
    g.printGraph();

    int components = g.findConnectedComponents();
    cout << "Number of connected components: " << components << endl;

    return 0;
}
