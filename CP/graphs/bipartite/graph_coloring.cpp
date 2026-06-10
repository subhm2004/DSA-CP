// ════════════════════════════════════════════════════════════════════════════
// GRAPH COLORING — Backtracking (Adjacency List Version)
// ────────────────────────────────────────────────────────────────────────────
// Har vertex ko 1..m me se koi color do
// Adjacent vertices same color nahi ho sakte
// Backtrack jab koi valid color na mile
// Time: O(m^V)  |  Space: O(V + E)
// ════════════════════════════════════════════════════════════════════════════

#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
using namespace std;

class GraphColoring
{
    int V;                                 // total vertices
    unordered_map<int, list<int>> adjList; // adjacency list
    vector<int> color;                     // color[i] = vertex i ka assigned color

public:
    // Step 1: Total vertices V store karo.
    // Step 2: color array size V, sab 0 — 0 matlab abhi koi color assign nahi hua.
    // Step 3: Empty adjacency list ready — addEdge se graph build hoga.
    GraphColoring(int V)
    {
        this->V = V;
        color.resize(V, 0);
    }

    // Step 1: adjList[u] mein v push karo.
    // Step 2: adjList[v] mein u push karo — undirected graph assumption.
    // Step 3: Dono nodes ke neighbors list update — coloring mein dono check honge.
    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // undirected
    }

    // Step 1: v ke saare neighbors iterate karo.
    // Step 2: Agar koi neighbor pehle se color c pe hai → conflict → false return.
    // Step 3: Saare neighbors alag color pe hain → safe hai → true return.
    // Step 4: Backtracking mein har color try karne se pehle ye check hota hai.
    bool isSafe(int v, int c)
    {
        for (int neighbor : adjList[v])
        {
            if (color[neighbor] == c)
                return false; // neighbor pehle se same color pe hai
        }
        return true;
    }

    // Step 1: Agar v == V ho to saare vertices color ho gaye — true return (solution mil gaya).
    // Step 2: Colors 1 se m tak try karo — har color c ke liye isSafe(v,c) check karo.
    // Step 3: Safe ho to color[v] = c assign karo aur solve(v+1, m) recursively call karo.
    // Step 4: Recursive call true de to propagate; warna color[v] = 0 backtrack karo.
    // Step 5: Koi color kaam na kare to false — is vertex pe koi valid coloring nahi.
    bool solve(int v, int m)
    {
        if (v == V) // sab vertices color ho gaye
            return true;

        for (int c = 1; c <= m; c++)
        {
            if (isSafe(v, c))
            {
                color[v] = c;
                if (solve(v + 1, m))
                    return true;
                color[v] = 0; // backtrack
            }
        }
        return false;
    }

    // Step 1: solve(0, m) se vertex 0 se backtracking shuru karo.
    // Step 2: Solution mila to har vertex ka assigned color print karo.
    // Step 3: Solution nahi mila to "No solution" message — m colors kaafi nahi hain.
    // Step 4: m badha kar minimum colors dhundh sakte ho (chromatic number ke liye).
    void graphColoring(int m)
    {
        if (solve(0, m))
        {
            cout << "Solution exists! Colors assigned to vertices:\n";
            for (int i = 0; i < V; i++)
                cout << "Vertex " << i << " -> Color " << color[i] << endl;
        }
        else
        {
            cout << "No solution exists with " << m << " colors.\n";
        }
    }
};

int main()
{
    int V = 4;
    GraphColoring g(V);

    vector<pair<int, int>> edges = {
        {0, 1}, {0, 2}, {1, 2}, {1, 3}};

    for (auto edge : edges)
    {
        g.addEdge(edge.first, edge.second);
    }

    int m = 3; // maximum kitne colors try karne hain
    g.graphColoring(m);

    return 0;
}
