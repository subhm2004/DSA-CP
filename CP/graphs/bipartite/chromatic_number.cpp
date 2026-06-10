// ════════════════════════════════════════════════════════════════════════════
// GRAPH COLORING — Minimum Colors (Chromatic Number via Backtracking)
// ────────────────────────────────────────────────────────────────────────────
// Har vertex ko color do taaki adjacent vertices ka color alag ho
// Backtracking se m colors try karo — sabse chhota m jahan solution mile
// Ye file fixed m=3 ke saath demo karti hai (minimum chromatic number dhundhne ke liye m badhao)
// Time: O(m^V) worst case  |  Space: O(V²) adjacency matrix
// ════════════════════════════════════════════════════════════════════════════

#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>

using namespace std;

class Graph
{
public:
    unordered_map<int, list<int>> adjList;
    unordered_map<int, int> degree;
    int vertices;

    // Step 1: vertices count store karo.
    // Step 2: Empty adjList aur degree map ready — addEdge se graph build hoga.
    Graph(int v)
    {
        vertices = v;
    }

    // Step 1: u-v undirected edge — dono taraf adjList mein add karo.
    // Step 2: degree[u]++ aur degree[v]++ — har node ka connection count track karo.
    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // undirected graph
        degree[u]++;
        degree[v]++;
    }

    // Step 1: Adjacency list print karo — har node aur uske neighbors.
    // Step 2: Degree map print karo — har node kitne edges se connected hai.
    // Step 3: Debugging aur graph analysis ke liye useful output.
    void printGraph()
    {
        cout << "\nAdjacency List:\n";
        for (auto &node : adjList)
        {
            cout << node.first << " -> ";
            for (int neighbor : node.second)
            {
                cout << neighbor << " ";
            }
            cout << endl;
        }

        cout << "\nDegree of nodes:\n";
        for (auto &node : adjList)
        {
            int v = node.first;
            cout << "Node " << v << ": Degree = " << degree[v] << endl;
        }
    }

    // Step 1: vertices × vertices zero matrix banao.
    // Step 2: adjList se har edge u->v ke liye graph[u][v] = 1 set karo.
    // Step 3: Matrix se O(1) neighbor check — isSafe() fast chalega backtracking mein.
    // Step 4: Converted matrix return karo.
    vector<vector<int>> getAdjMatrix()
    {
        vector<vector<int>> graph(vertices, vector<int>(vertices, 0));
        for (auto &node : adjList)
        {
            int u = node.first;
            for (int v : node.second)
            {
                graph[u][v] = 1;
            }
        }
        return graph;
    }
};

// Step 1: Har potential neighbor 0..n-1 check karo — graph[node][neighbor] == 1 matlab edge hai.
// Step 2: Agar neighbor connected hai AUR color[neighbor] == c → conflict → false.
// Step 3: Saare adjacent neighbors alag color pe → safe → true return.
// Step 4: Backtracking mein har color try karne se pehle ye validation hoti hai.
bool isSafe(int node, vector<vector<int>> &graph, vector<int> &color, int c)
{
    for (int neighbor = 0; neighbor < graph.size(); neighbor++)
    {
        if (graph[node][neighbor] && color[neighbor] == c)
            return false;
    }
    return true;
}

// Step 1: node == graph.size() ho to saare nodes colored — true (solution found).
// Step 2: Colors 1 se m tak try karo — isSafe(node, c) pass ho to color[node] = c.
// Step 3: Recursively graph_Coloring_Util(graph, m, color, node+1) call karo.
// Step 4: Success ho to true propagate; warna color[node] = 0 backtrack.
// Step 5: Koi color fit na ho to false — m colors se coloring impossible.
bool graph_Coloring_Util(vector<vector<int>> &graph, int m, vector<int> &color, int node)
{
    if (node == graph.size()) // sab nodes color ho gaye
        return true;

    for (int c = 1; c <= m; c++)
    {
        if (isSafe(node, graph, color, c))
        {
            color[node] = c;
            if (graph_Coloring_Util(graph, m, color, node + 1))
                return true;
            color[node] = 0; // backtrack — ye color kaam nahi kiya
        }
    }
    return false;
}

// Step 1: Graph se adjacency matrix nikalo getAdjMatrix() se.
// Step 2: color array size n, sab 0 initialize karo.
// Step 3: graph_Coloring_Util se node 0 se backtracking shuru — m colors try karo.
// Step 4: Solution mile to har vertex ka color print karo.
// Step 5: Fail ho to "cannot be colored" message — m colors kaafi nahi (chromatic number > m).
void graph_Coloring(Graph &g, int m)
{
    vector<vector<int>> graph = g.getAdjMatrix();
    int n = graph.size();
    vector<int> color(n, 0);

    if (graph_Coloring_Util(graph, m, color, 0))
    {
        cout << "\nGraph can be colored with " << m << " colors:\n";
        for (int i = 0; i < n; i++)
            cout << "Vertex " << i << " -> Color " << color[i] << endl;
    }
    else
    {
        cout << "\nGraph cannot be colored with " << m << " colors.\n";
    }
}

int main()
{
    int n = 6; // vertices 0..5
    int m = 3; // kitne colors try karne hain

    vector<pair<int, int>> edges = {{0, 1}, {1, 2}, {2, 0}, {1, 3}, {3, 4}, {4, 1}};

    Graph g(n);
    for (auto edge : edges)
    {
        g.addEdge(edge.first, edge.second);
    }

    g.printGraph();
    graph_Coloring(g, m);

    return 0;
}
