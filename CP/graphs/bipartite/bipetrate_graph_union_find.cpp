#include <iostream>
#include <vector>

using namespace std;

class UnionFind
{
public:
    vector<int> parent;
    vector<int> rank;
    vector<int> color; // 0 ya 1 bipartiteness check ke liye

    UnionFind(int n) : parent(n), rank(n, 0), color(n, -1) // Color ko -1 (unvisited) initialize kar rahe hain
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = i; // Har node initially apna khud ka parent hoti hai
        }
    }

    int find(int i)
    {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]); // Path compression se optimization hoti hai
    }

    bool unionByRank(int x, int y)
    {
        int x_parent = find(x);
        int y_parent = find(y);

        if (x_parent == y_parent)
            return false; // Agar pehle se connected hai, toh main function mein bipartiteness check karenge

        // Union by rank: chhoti tree ko badi tree ke niche attach karna
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

    // Graph bipartite hai ya nahi check karne ka function
    bool isBipartite(int n, vector<vector<int>> &edges)
    {
        for (int i = 0; i < n; i++)
        {
            color[i] = -1; // Har node ka color reset kar rahe hain
        }

        for (auto &edge : edges)
        {
            int u = edge[0], v = edge[1];

            if (color[u] == -1)
                color[u] = 0; // Pehli node ko color assign kar rahe hain

            if (color[v] == -1)
                color[v] = 1 - color[u]; // Adjacent node ko opposite color dena

            else if (color[u] == color[v])
                return false; // Agar dono ka color same hai, toh graph bipartite nahi hai

            unionByRank(u, v);
        }

        return true;
    }
};

// Driver Code
int main()
{
    int n = 4;                                                    // Number of nodes
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 3}, {3, 0}}; // Example edges

    UnionFind uf(n);
    if (uf.isBipartite(n, edges))
        cout << "Graph Bipartite hai" << endl;
    else
        cout << "Graph Bipartite nahi hai" << endl;

    return 0;
}
