// ════════════════════════════════════════════════════════════════════════════
// CYCLE DETECTION — 3-Color DFS (Directed Graph)
// ────────────────────────────────────────────────────────────────────────────
// WHITE = unvisited (abhi tak visit nahi kiya)
// GRAY  = currently being processed (recursion stack me hai)
// BLACK = completely processed (saare neighbors done)
//
// GRAY node dubara mile → BACK EDGE → cycle present
// Time: O(V + E)  |  Space: O(V)
// ════════════════════════════════════════════════════════════════════════════

#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
using namespace std;

// Color constants ko define karne ke liye struct use kiya
// Ye cleaner approach hai constants define karne ke liye
struct Color
{
    static const int WHITE = 0; // Unvisited node
    static const int GRAY = 1;  // Currently being processed
    static const int BLACK = 2; // Completely processed
};

class Solution
{
public:
    // Adjacency List representation of graph
    // Key: node number, Value: list of pairs (neighbor, weight)
    unordered_map<int, list<pair<int, int>>> adjList;

    // Step 1: u ki adjacency list mein {v, weight} pair push karo.
    // Step 2: Agar graph undirected hai (!direction) to v se u ki reverse edge bhi add karo.
    // Step 3: Directed graph mein sirf u -> v store hota hai — cycle detection directed ke liye hai.
    // Step 4: Weight yahan 0 hai kyunki cycle detection mein weight matter nahi karta.
    void addEdge(int u, int v, int w, bool direction)
    {
        // u se v ki taraf edge add karo
        adjList[u].push_back({v, w});

        // Agar undirected graph hai to reverse edge bhi add karo
        if (!direction)
        {
            adjList[v].push_back({u, w});
        }
    }

    // Step 1: Current node ko GRAY mark karo — matlab abhi DFS recursion stack mein process ho raha hai.
    // Step 2: Har neighbor ko check karo — agar GRAY hai to BACK EDGE mila → turant true return (CYCLE!).
    // Step 3: Agar neighbor WHITE (unvisited) hai to recursively isCycleUtil(neighbor) call karo.
    // Step 4: Recursive call se cycle mile to true propagate karo — aage check karne ki zaroorat nahi.
    // Step 5: Saare neighbors done hone par node ko BLACK karo — poori subtree process ho gayi, safe hai.
    bool isCycleUtil(int node, unordered_map<int, int> &nodeColor)
    {
        // Current node ko GRAY mark karo (processing start kar rahe hain)
        nodeColor[node] = Color::GRAY;

        // Current node ke saare neighbors ko check karo
        for (auto &neighbor : adjList[node])
        {
            int v = neighbor.first; // Neighbor node ka number

            // MAIN CYCLE DETECTION LOGIC:
            // Agar neighbor GRAY hai, matlab back edge mil gaya = CYCLE!
            if (nodeColor[v] == Color::GRAY)
                return true; // Back edge found - cycle detected!

            // Agar neighbor WHITE hai (unvisited), to usse recursively check karo
            // Agar recursive call mein cycle mil jaye to true return karo
            if (nodeColor[v] == Color::WHITE && isCycleUtil(v, nodeColor))
                return true;

            // Note: BLACK nodes ko ignore karte hain kyunki wo already processed hain
        }

        // Saare neighbors process ho gaye, ab current node ko BLACK mark karo
        nodeColor[node] = Color::BLACK;
        return false; // Is path mein koi cycle nahi mili
    }

    // Step 1: Saare V nodes ko initially WHITE (unvisited) mark karo nodeColor map mein.
    // Step 2: Har node i = 0 se V-1 tak check karo — disconnected components handle karne ke liye.
    // Step 3: Agar node abhi WHITE hai to isCycleUtil(i) se DFS start karo.
    // Step 4: Kisi bhi component mein cycle mile to turant true return karo.
    // Step 5: Saare components clean hain to false return — graph mein koi directed cycle nahi hai.
    bool isCycle(int V)
    {
        // Har node ka color track karne ke liye map
        unordered_map<int, int> nodeColor;

        // Initially saare nodes ko WHITE (unvisited) mark karo
        for (int i = 0; i < V; ++i)
            nodeColor[i] = Color::WHITE;

        // Har unvisited node se DFS start karo
        // Ye isliye zaroori hai kyunki graph disconnected ho sakta hai
        for (int i = 0; i < V; ++i)
        {
            // Agar node abhi bhi WHITE hai (unvisited)
            if (nodeColor[i] == Color::WHITE)
            {
                // Us node se DFS start karo
                if (isCycleUtil(i, nodeColor))
                    return true; // Cycle mil gaya!
            }
        }

        // Saare components check kar liye, koi cycle nahi mili
        return false;
    }
};

int main()
{
    Solution graph; // Graph object create karo

    int V = 4; // Total 4 vertices (0, 1, 2, 3)

    // Directed edges add karo
    // Format: addEdge(source, destination, weight, isDirected)
    graph.addEdge(0, 1, 0, true); // 0 -> 1
    graph.addEdge(0, 2, 0, true); // 0 -> 2
    graph.addEdge(1, 2, 0, true); // 1 -> 2
    graph.addEdge(2, 0, 0, true); // 2 -> 0 (ye cycle banata hai: 0->2->0)
    graph.addEdge(2, 3, 0, true); // 2 -> 3
    graph.addEdge(3, 3, 0, true); // 3 -> 3 (self-loop, ye bhi cycle hai)

    // Cycle detection function call karo
    if (graph.isCycle(V))
    {
        cout << "There is a cycle" << endl;
    }
    else
    {
        cout << "No cycle" << endl;
    }

    return 0;
}

/*
DETAILED ALGORITHM EXPLANATION:

1. THREE-COLOR METHOD:
   - WHITE: Node abhi visit nahi hui
   - GRAY: Node currently process ho rahi hai (DFS stack mein hai)
   - BLACK: Node completely process ho gayi

2. CYCLE DETECTION LOGIC:
   - Agar DFS ke dauraan koi GRAY node encounter karte hain
   - Matlab current path mein wapas aa gaye (BACK EDGE)
   - Back edge = Cycle present hai

3. WHY THIS METHOD WORKS:
   - GRAY nodes current DFS path represent karte hain
   - Agar GRAY node ko wapas milta hai = path mein loop hai
   - BLACK nodes safe hain kyunki wo already processed hain

4. EXAMPLE TRACE (for given graph):
   Start with node 0 (WHITE):
   - 0 becomes GRAY
   - Visit neighbor 1: 1 becomes GRAY
   - From 1, visit 2: 2 becomes GRAY
   - From 2, visit 0: 0 is already GRAY! → CYCLE DETECTED!

5. TIME COMPLEXITY: O(V + E)
   - V vertices ko visit karte hain
   - E edges ko process karte hain

6. SPACE COMPLEXITY: O(V)
   - Color map: O(V)
   - Recursion stack: O(V) in worst case

ADVANTAGES:
- Directed graphs mein efficiently cycle detect karta hai
- Three-color method clear aur intuitive hai
- Self-loops aur complex cycles dono handle karta hai
*/