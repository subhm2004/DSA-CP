#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <list>
#include <tuple>

using namespace std;

/*
KRUSKAL'S MINIMUM SPANNING TREE ALGORITHM
- Greedy algorithm hai jo minimum weight ka spanning tree banata hai
- Union-Find data structure use karta hai cycle detection ke liye
- Steps: 1) Sort edges by weight 2) Pick smallest edge 3) Check cycle 4) Add if no cycle
*/

// UnionFind class - disjoint sets handle karta hai aur cycle detection mein help karta hai
class UnionFind
{
public:
    vector<int> parent; // Har element ka parent/representative store karta hai
    vector<int> rank;   // Tree ki height/rank track karta hai optimization ke liye

    // Constructor - initial setup karta hai
    UnionFind(int n) : parent(n), rank(n, 0)
    {
        // Initially har element apna khud ka parent hai (separate sets)
        for (int i = 0; i < n; i++)
        {
            parent[i] = i; // Self-parent initially
        }
    }

    // Find function with path compression - element ka ultimate parent return karta hai
    int find(int i)
    {
        // Base case: agar element apna khud ka parent hai
        if (parent[i] == i)
            return i;

        // PATH COMPRESSION: Recursively find karte time direct root ko point kara do
        // Ye future operations ko fast bana deta hai
        return parent[i] = find(parent[i]);
    }

    // Union by rank - do sets ko merge karta hai rank ke basis par
    void unionByRank(int x, int y)
    {
        int x_parent = find(x); // x ka ultimate parent
        int y_parent = find(y); // y ka ultimate parent

        // Agar dono already same set mein hain, nothing to do
        if (x_parent == y_parent)
            return;

        // UNION BY RANK: Chhoti rank wale tree ko badi rank wale mein attach karo
        // Ye overall tree height minimize karta hai
        if (rank[x_parent] < rank[y_parent])
        {
            parent[x_parent] = y_parent; // x_parent ko y_parent ke neeche attach karo
        }
        else if (rank[x_parent] > rank[y_parent])
        {
            parent[y_parent] = x_parent; // y_parent ko x_parent ke neeche attach karo
        }
        else
        {
            // Agar rank same hai, koi bhi ko root banao aur rank increase karo
            parent[y_parent] = x_parent;
            rank[x_parent]++; // Root ka rank badh gaya
        }
    }

    // Connected components count karta hai
    int countComponents()
    {
        int components = 0;
        for (int i = 0; i < parent.size(); ++i)
        {
            if (parent[i] == i) // Root/representative node hai
                components++;
        }
        return components;
    }
};

// Graph class - weighted graph operations handle karta hai
class Graph
{
public:
    // Adjacency list representation: node -> [(neighbor, weight)]
    unordered_map<int, list<pair<int, int>>> adjList;

    // Edge list for Kruskal's algorithm: (u, v, weight)
    vector<tuple<int, int, int>> edges;

    // Graph mein edge add karne ka function
    void addEdge(int u, int v, int weight, bool directed)
    {
        // Adjacency list mein add karo
        adjList[u].push_back({v, weight});

        // Edge list mein add karo (Kruskal ke liye zaroori hai)
        edges.push_back({u, v, weight});

        // Agar undirected graph hai to reverse edge bhi add karo
        if (!directed)
        {
            adjList[v].push_back({u, weight}); // Reverse adjacency
            edges.push_back({v, u, weight});   // Reverse edge (but we'll handle duplicates in MST)
        }
    }

    // Adjacency list ko weights ke saath print karta hai
    void printAdjacencyListWithWeights()
    {
        cout << "Adjacency List with Weights:" << endl;
        for (const auto &node : adjList)
        {
            cout << "Node " << node.first << ":";
            // Har node ke neighbors aur unke weights print karo
            for (const auto &nbr : node.second)
            {
                cout << " -> (" << nbr.first << ", " << nbr.second << ")";
            }
            cout << endl;
        }
    }

    // KRUSKAL'S MST ALGORITHM - Main algorithm!
    int kruskalMST(int n)
    {
        // STEP 1: Saare edges ko weight ke hisaab se sort karo (ascending order)
        // Lambda function use kiya hai sorting ke liye
        sort(edges.begin(), edges.end(), [](const tuple<int, int, int> &a, const tuple<int, int, int> &b)
             {
                 return get<2>(a) < get<2>(b); // Compare weights (3rd element of tuple)
             });

        UnionFind uf(n);   // Union-Find object create karo
        int mstWeight = 0; // MST ka total weight track karta hai

        cout << "\nKruskal's MST Algorithm Steps:" << endl;

        // STEP 2: Har edge ko process karo (smallest weight se start karo)
        for (auto &edge : edges)
        {
            int u = get<0>(edge);      // Source node
            int v = get<1>(edge);      // Destination node
            int weight = get<2>(edge); // Edge weight

            // STEP 3: Check karo ki ye edge cycle banata hai ya nahi
            // Agar u aur v already connected hain, matlab cycle banega
            if (uf.find(u) != uf.find(v))
            {
                // No cycle! Ye edge MST mein include kar sakte hain
                uf.unionByRank(u, v); // Union karo (connect karo)
                mstWeight += weight;  // Total weight mein add karo

                cout << "Edge (" << u << "-" << v << ") with weight " << weight << " added to MST" << endl;
            }
            else
            {
                cout << "Edge (" << u << "-" << v << ") with weight " << weight << " creates cycle, REJECTED" << endl;
            }
        }

        return mstWeight; // Total MST weight return karo
    }

    // Cycle detection function - graph mein cycle hai ya nahi check karta hai
    bool hasCycle()
    {
        UnionFind uf(adjList.size()); // Fresh Union-Find object

        cout << "\nCycle Detection Steps:" << endl;

        // Har edge check karo
        for (auto &edge : edges)
        {
            int u = get<0>(edge);
            int v = get<1>(edge);

            // Agar u aur v already same component mein hain, matlab cycle hai
            if (uf.find(u) == uf.find(v))
            {
                cout << "Cycle found with edge (" << u << "-" << v << ")" << endl;
                return true; // Cycle detected!
            }

            // Union karo for next iteration
            uf.unionByRank(u, v);
        }

        cout << "No cycle found in the graph" << endl;
        return false; // No cycle
    }

    // Connected components count karta hai
    int findConnectedComponents()
    {
        UnionFind uf(adjList.size()); // Fresh Union-Find object

        // Saare edges process karo to connect components
        for (auto &edge : edges)
        {
            int u = get<0>(edge);
            int v = get<1>(edge);
            uf.unionByRank(u, v); // Connect u and v
        }

        // Final component count return karo
        return uf.countComponents();
    }
};

int main()
{
    Graph g;
    int n = 6; // Total number of nodes (0 to 5)

    /*
    SAMPLE GRAPH:
    Nodes: 0, 1, 2, 3, 4, 5
    Edges with weights:
    0-1: 10
    0-2: 6
    0-3: 5
    1-3: 15
    2-3: 4

    Expected MST: Should pick edges with weights 4, 5, 6, 10 (total = 25)
    */

    // Graph mein weighted edges add karo
    cout << "Adding edges to the graph..." << endl;
    g.addEdge(0, 1, 10, false); // Edge 0-1 with weight 10 (undirected)
    g.addEdge(0, 2, 6, false);  // Edge 0-2 with weight 6 (undirected)
    g.addEdge(0, 3, 5, false);  // Edge 0-3 with weight 5 (undirected)
    g.addEdge(1, 3, 15, false); // Edge 1-3 with weight 15 (undirected)
    g.addEdge(2, 3, 4, false);  // Edge 2-3 with weight 4 (undirected)

    // Adjacency list print karo
    g.printAdjacencyListWithWeights();

    // KRUSKAL'S MST ALGORITHM run karo
    cout << "\n"
         << string(50, '=') << endl;
    cout << "RUNNING KRUSKAL'S MST ALGORITHM" << endl;
    cout << string(50, '=') << endl;

    int mstWeight = g.kruskalMST(n);
    cout << "\nFinal Minimum Spanning Tree Weight: " << mstWeight << endl;

    // Connected components count karo
    cout << "\nNumber of Connected Components: " << g.findConnectedComponents() << endl;

    // Cycle detection karo
    cout << "\n"
         << string(50, '=') << endl;
    cout << "CYCLE DETECTION" << endl;
    cout << string(50, '=') << endl;

    if (g.hasCycle())
    {
        cout << "\nResult: Graph contains a cycle" << endl;
    }
    else
    {
        cout << "\nResult: Graph does not contain a cycle" << endl;
    }

    return 0;
}

/*
DETAILED ALGORITHM EXPLANATION:

1. KRUSKAL'S MST ALGORITHM STEPS:
   a) Sort all edges by weight (ascending order)
   b) Initialize Union-Find structure
   c) For each edge (u,v):
      - If u and v are in different components → Add edge to MST
      - If u and v are in same component → Skip (would create cycle)
   d) Continue until MST has (V-1) edges

2. WHY KRUSKAL'S WORKS (Greedy Choice):
   - Always pick the minimum weight edge that doesn't create cycle
   - This greedy choice is always optimal for MST
   - Union-Find efficiently detects cycles

3. TIME COMPLEXITY:
   - Sorting edges: O(E log E)
   - Union-Find operations: O(E × α(V)) ≈ O(E)
   - Overall: O(E log E) where E = edges, V = vertices

4. SPACE COMPLEXITY: O(V + E)
   - Union-Find: O(V)
   - Edge storage: O(E)

5. EXAMPLE TRACE:
   Edges sorted: (2,3,4), (0,3,5), (0,2,6), (0,1,10), (1,3,15)

   Step 1: Add (2,3,4) → MST weight = 4
   Step 2: Add (0,3,5) → MST weight = 9
   Step 3: Add (0,2,6) → MST weight = 15
   Step 4: Add (0,1,10) → MST weight = 25
   Step 5: Skip (1,3,15) → Creates cycle

   Final MST weight: 25

6. APPLICATIONS:
   - Network design (minimum cost to connect all nodes)
   - Clustering algorithms
   - Approximate solutions for TSP
   - Image segmentation

7. KRUSKAL vs PRIM:
   - Kruskal: Edge-based, good for sparse graphs
   - Prim: Vertex-based, good for dense graphs
   - Both have same time complexity with proper implementation

IMPORTANT: Kruskal's algorithm is fundamental in graph theory aur competitive programming mein bahut important hai!
*/