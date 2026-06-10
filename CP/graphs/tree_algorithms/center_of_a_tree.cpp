#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// CENTER OF A TREE — Onion Peeling Technique
// ────────────────────────────────────────────────────────────────────────────
// Tree ka center = wo node(s) jinka sabse zyada distance (eccentricity) minimum ho.
// Ek tree me 1 ya 2 centers hote hain.
//
// Onion Peeling: baar-baar leaf nodes (degree=1) hatao jab tak 1-2 nodes bache.
//   Round 1: sab leaves remove -> unke neighbors ki degree kam
//   Round 2: naye leaves remove -> repeat
//   Jab 1-2 nodes bache -> wahi center(s) hain!
//
// Topological sort on tree jaisa feel — andar ki taraf peel karte jao.
// Time: O(V)  |  Space: O(V)
// ════════════════════════════════════════════════════════════════════════════

class TreeCenter
{
private:
    int n;
    unordered_map<int, list<int>> adjList; // har node ki neighbor list
    unordered_map<int, int> degree;        // har node ki degree (kitne neighbors hain)

    // ── buildGraph: edge list se adjacency list aur degree array banao ─────
    void buildGraph(vector<vector<int>> &edges)
    {
        // Step 1: har node ke liye empty adjacency list aur degree=0
        for (int i = 0; i < n; i++)
        {
            adjList[i];
            degree[i] = 0;
        }

        // Step 2: har undirected edge dono taraf add, degree count badhao
        for (auto &e : edges)
        {
            adjList[e[0]].push_back(e[1]);
            adjList[e[1]].push_back(e[0]);
            degree[e[0]]++;
            degree[e[1]]++;
        }
    }

    // ── printTree: adjacency list debug print ───────────────────────────────
    void printTree()
    {
        cout << "\n--- Adjacency List ---\n";
        for (auto &[node, neighbors] : adjList)
        {
            cout << "  Node " << node << " -> ";
            for (int neighbor : neighbors)
                cout << neighbor << " ";
            cout << "\n";
        }
    }

public:
    // Constructor: n nodes aur edges se graph build karo
    TreeCenter(int n, vector<vector<int>> &edges) : n(n)
    {
        buildGraph(edges);
    }

    // ── findCenter: onion peeling se tree ka center dhundo ─────────────────
    // Base cases: n=1 -> {0}, n=2 -> {0,1}.
    // Degree=1 wale sab leaves queue me daalo.
    // Har round me saari current leaves hatao, neighbors ki degree-- karo.
    // Jab 2 se kam nodes bache -> queue me jo bache wahi center(s).
    vector<int> findCenter()
    {
        if (n == 1)
            return {0};
        if (n == 2)
            return {0, 1};

        printTree();

        // Shuru me sab leaf nodes (degree = 1) queue me daalo
        queue<int> q;
        for (auto &[node, deg] : degree)
            if (deg == 1)
                q.push(node);

        int remainingNodes = n;
        int round = 1;

        cout << "\n--- Onion Peeling Rounds ---\n";

        // Jab tak 2 se zyada nodes bache, har round me leaves peel karo
        while (remainingNodes > 2)
        {
            int sz = q.size();
            remainingNodes -= sz;

            cout << "  Round " << round++ << " | Removing leaves: ";

            while (sz--)
            {
                int leaf = q.front();
                q.pop();
                cout << leaf << " ";

                // Leaf ke har neighbor ki degree kam karo
                for (int nei : adjList[leaf])
                {
                    degree[nei]--;
                    if (degree[nei] == 1)  // Naya leaf ban gaya -> queue me daalo
                        q.push(nei);
                }
            }

            cout << "| Remaining: " << remainingNodes << "\n";
        }

        // Queue me jo 1-2 nodes bache -> center(s)
        vector<int> centers;
        while (!q.empty())
        {
            centers.push_back(q.front());
            q.pop();
        }
        return centers;
    }

    // ── printResult: center node(s) ka result dikhao ───────────────────────
    void printResult(vector<int> &centers)
    {
        cout << "\n--- Result ---\n";
        if (centers.size() == 1)
            cout << "  Single Center : Node " << centers[0] << "\n";
        else
            cout << "  Two Centers   : Node " << centers[0] << " and Node " << centers[1] << "\n";
        cout << "  (Ye node(s) sabse kam maximum distance rakhte hain baaki nodes se)\n";
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    /*
     *  Hardcoded Example Tree:
     *
     *      1
     *      |
     *      0
     *     / \
     *    2   3
     *        |
     *        4
     *        |
     *        5
     *
     *  Nodes: 0,1,2,3,4,5
     *  Edges: 0-1, 0-2, 0-3, 3-4, 4-5
     *  Expected Center: Node 3
     */

    int n = 6;

    vector<vector<int>> edges = {
        {0, 1}, // 0 aur 1 connected hain
        {0, 2}, // 0 aur 2 connected hain
        {0, 3}, // 0 aur 3 connected hain
        {3, 4}, // 3 aur 4 connected hain
        {4, 5}  // 4 aur 5 connected hain
    };

    TreeCenter tc(n, edges);
    vector<int> centers = tc.findCenter();
    tc.printResult(centers);

    return 0;
}
