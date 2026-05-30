#include <bits/stdc++.h> // onion peeling technique se tree ka center nikalne ke liye
// basically ye topological sort on tree hai, jisme hum repeatedly leaf nodes ko remove karte hain jab tak 1 ya 2 nodes bache na ho
using namespace std;

class TreeCenter
{
private:
    int n;
    unordered_map<int, list<int>> adjList; // har node ki neighbor list
    unordered_map<int, int> degree;        // har node ki degree (kitne neighbors hain)

    void buildGraph(vector<vector<int>> &edges)
    {
        for (int i = 0; i < n; i++)
        {
            adjList[i];
            degree[i] = 0;
        }

        for (auto &e : edges)
        {
            adjList[e[0]].push_back(e[1]);
            adjList[e[1]].push_back(e[0]);
            degree[e[0]]++;
            degree[e[1]]++;
        }
    }

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
    TreeCenter(int n, vector<vector<int>> &edges) : n(n)
    {
        buildGraph(edges);
    }

    vector<int> findCenter()
    {
        if (n == 1)
            return {0};
        if (n == 2)
            return {0, 1};

        printTree();

        queue<int> q;
        for (auto &[node, deg] : degree)
            if (deg == 1)
                q.push(node);

        int remainingNodes = n;
        int round = 1;

        cout << "\n--- Onion Peeling Rounds ---\n";

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

                for (int nei : adjList[leaf])
                {
                    degree[nei]--;
                    if (degree[nei] == 1)
                        q.push(nei);
                }
            }

            cout << "| Remaining: " << remainingNodes << "\n";
        }

        vector<int> centers;
        while (!q.empty())
        {
            centers.push_back(q.front());
            q.pop();
        }
        return centers;
    }

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

/*
 * Expected Output:
 *
 * --- Adjacency List ---
 *   Node 0 -> 1 2 3
 *   Node 1 -> 0
 *   Node 2 -> 0
 *   Node 3 -> 0 4
 *   Node 4 -> 3 5
 *   Node 5 -> 4
 *
 * --- Onion Peeling Rounds ---
 *   Round 1 | Removing leaves: 1 2 5 | Remaining: 3
 *   Round 2 | Removing leaves: 0 4   | Remaining: 1
 *
 * --- Result ---
 *   Single Center : Node 3
 */