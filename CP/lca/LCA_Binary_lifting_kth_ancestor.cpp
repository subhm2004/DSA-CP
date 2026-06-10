#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// BINARY LIFTING — LCA + K-th Ancestor + Distance + Kth Node on Path
// ────────────────────────────────────────────────────────────────────────────
// up[i][j] = 2^j-th ancestor. Extra helpers:
//   distance(u,v) = depth[u]+depth[v]-2*depth[LCA]
//   kth_node_on_path = u se LCA tak ya LCA se v tak ancestor jump
// Complexity: preprocess O(n log n), har query O(log n)
// ════════════════════════════════════════════════════════════════════════════

class Binary_Lifting
{
private:
    int n, LOG;
    vector<vector<int>> up;
    vector<int> depth;
    vector<vector<int>> children;

    // ── dfs: depth[] bharno ───────────────────────────────────────────────────
    //   1) depth[node] = d set karo
    //   2) har child pe dfs(child, d+1) — children list se traverse
    //   3) root se poori tree ki depth ready ho jaati hai
    void dfs(int node, int d)
    {
        depth[node] = d;
        for (int child : children[node])
            dfs(child, d + 1);
    }

    // ── preCompute: children list, up[][] table, depth build ─────────────────
    //   1) parent array se children adjacency list banao
    //   2) up[i][0] = parent[i] — direct parent store
    //   3) root (parent=-1) se dfs — depth[] fill
    //   4) j=1..LOG-1: up[i][j] = up[up[i][j-1]][j-1] — binary lifting DP
    void preCompute(const vector<int> &parent)
    {
        children.assign(n, vector<int>());
        for (int i = 0; i < n; ++i)
            if (parent[i] != -1)
                children[parent[i]].push_back(i);

        for (int i = 0; i < n; ++i)
            up[i][0] = parent[i];

        for (int i = 0; i < n; ++i)
            if (parent[i] == -1)
                dfs(i, 0);

        for (int j = 1; j < LOG; ++j)
            for (int i = 0; i < n; ++i)
                if (up[i][j - 1] != -1)
                    up[i][j] = up[up[i][j - 1]][j - 1];
    }

public:
    // ── Binary_Lifting: constructor — tables allocate + preCompute chalao ───
    //   1) n, LOG set karo, up aur depth arrays allocate
    //   2) preCompute(parent) se saari preprocessing ek jagah
    Binary_Lifting(int n, const vector<int> &parent)
    {
        this->n = n;
        LOG = (n > 1) ? (int)ceil(log2(n)) + 1 : 1;
        up.assign(n, vector<int>(LOG, -1));
        depth.assign(n, 0);

        preCompute(parent);
    }

    // ── get_Kth_Ancestor: K-th ancestor (binary bits se jump) ───────────────
    //   1) K ke i-th bit set hai to node = up[node][i] (2^i jump)
    //   2) node -1 ho gaya to ancestor nahi hai
    //   3) saare set bits process -> exactly K steps upar
    int get_Kth_Ancestor(int node, int k)
    {
        for (int i = 0; i < LOG; ++i)
        {
            if (k & (1 << i))
            {
                node = up[node][i];
                if (node == -1)
                    return -1;
            }
        }
        return node;
    }

    // ── find_LCA: same depth lao, phir saath-saath upar chadho ────────────────
    //   1) deeper node u ko depth[v] tak upar lao
    //   2) u==v ho gaya to wahi LCA
    //   3) bade se chhote jump se dono ko upar le jao jab tak same ancestor na ho
    //   4) up[u][0] = direct parent = LCA
    int find_LCA(int u, int v)
    {
        if (depth[u] < depth[v])
            swap(u, v);

        u = get_Kth_Ancestor(u, depth[u] - depth[v]);

        if (u == -1)
            return -1;
        if (u == v)
            return u;

        for (int i = LOG - 1; i >= 0; --i)
            if (up[u][i] != -1 && up[u][i] != up[v][i])  // abhi LCA ke neeche
            {
                u = up[u][i];
                v = up[v][i];
            }

        return up[u][0];
    }

    // ── distance: depth[u] + depth[v] - 2*depth[LCA] ───────────────────────
    //   1) pehle LCA nikalo
    //   2) formula: u se LCA + v se LCA = total path length (edges)
    //   3) LCA nahi mila to -1 return
    int distance(int u, int v)
    {
        int lca = find_LCA(u, v);
        if (lca == -1)
            return -1;
        return depth[u] + depth[v] - 2 * depth[lca];
    }

    // ── kth_node_on_path: path u→v pe k-th node (0-indexed from u) ────────
    //   1) LCA nikalo, dist_u = u se LCA tak, dist_v = v se LCA tak
    //   2) total = dist_u + dist_v — path ki length
    //   3) k invalid ho to -1
    //   4) k <= dist_u -> u se k steps upar; warna v se (total-k) steps upar
    int kth_node_on_path(int u, int v, int k)
    {
        int lca = find_LCA(u, v);
        if (lca == -1)
            return -1;

        int dist_u = depth[u] - depth[lca]; // u se LCA tak steps
        int dist_v = depth[v] - depth[lca]; // v se LCA tak steps
        int total = dist_u + dist_v;

        if (k < 0 || k > total)
            return -1; // invalid k

        if (k <= dist_u)
        {
            // u se LCA ki taraf k steps
            return get_Kth_Ancestor(u, k);
        }
        else
        {
            // LCA se v ki taraf — v se (total-k) steps upar
            int steps_from_v = total - k;
            return get_Kth_Ancestor(v, steps_from_v);
        }
    }

    // ── getDepth: node ki root se depth return karo ───────────────────────────
    int getDepth(int node) { return depth[node]; }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    /*
        Example Tree:
                0
               / \
              1   2
             / \    \
            3   4    5
                 \
                  6

        parent[] = {-1, 0, 0, 1, 1, 2, 4}
        Node 0 → root (parent = -1)
    */

    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    vector<int> parent(n);
    cout << "Enter parent of each node (root ka parent = -1):\n";
    for (int i = 0; i < n; ++i)
    {
        cout << "parent[" << i << "] = ";
        cin >> parent[i];
    }

    Binary_Lifting bl(n, parent);

    int choice;
    do
    {
        cout << "\n===== MENU =====\n";
        cout << "1. K-th Ancestor dhundo\n";
        cout << "2. LCA dhundo\n";
        cout << "3. Node ki Depth dekho\n";
        cout << "4. Distance between two nodes\n"; // ✅ NEW
        cout << "5. Kth node on path(u, v)\n";     // ✅ NEW
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int node, k;
            cout << "Node aur K enter karo: ";
            cin >> node >> k;

            if (node < 0 || node >= n)
            {
                cout << "Invalid node!\n";
                continue;
            }

            int ans = bl.get_Kth_Ancestor(node, k);
            if (ans == -1)
                cout << "Node " << node << " ka " << k << "-th ancestor exist nahi karta.\n";
            else
                cout << node << " ka " << k << "-th ancestor = " << ans << "\n";
        }
        else if (choice == 2)
        {
            int u, v;
            cout << "Do nodes enter karo (u v): ";
            cin >> u >> v;

            if (u < 0 || u >= n || v < 0 || v >= n)
            {
                cout << "Invalid nodes!\n";
                continue;
            }

            int lca = bl.find_LCA(u, v);
            if (lca == -1)
                cout << "LCA exist nahi karta.\n";
            else
                cout << "LCA(" << u << ", " << v << ") = " << lca << "\n";
        }
        else if (choice == 3)
        {
            int node;
            cout << "Node enter karo: ";
            cin >> node;

            if (node < 0 || node >= n)
            {
                cout << "Invalid node!\n";
                continue;
            }

            cout << "Depth of node " << node << " = " << bl.getDepth(node) << "\n";
        }
        else if (choice == 4) // ✅ NEW: Distance
        {
            int u, v;
            cout << "Do nodes enter karo (u v): ";
            cin >> u >> v;

            if (u < 0 || u >= n || v < 0 || v >= n)
            {
                cout << "Invalid nodes!\n";
                continue;
            }

            int dist = bl.distance(u, v);
            if (dist == -1)
                cout << "Distance calculate nahi ho sakta.\n";
            else
                cout << "Distance(" << u << ", " << v << ") = " << dist << "\n";
        }
        else if (choice == 5) // ✅ NEW: Kth node on path
        {
            int u, v, k;
            cout << "u, v aur k enter karo (0-indexed from u): ";
            cin >> u >> v >> k;

            if (u < 0 || u >= n || v < 0 || v >= n)
            {
                cout << "Invalid nodes!\n";
                continue;
            }

            int node = bl.kth_node_on_path(u, v, k);
            if (node == -1)
                cout << "Kth node exist nahi karta (k out of range).\n";
            else
                cout << k << "-th node on path(" << u << " → " << v << ") = " << node << "\n";
        }
        else if (choice != 0)
        {
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    cout << "Program exit ho gaya.\n";
    return 0;
}

/*
    Time Complexity:
    - Preprocessing      : O(n log n)
    - K-th Ancestor      : O(log n)
    - LCA                : O(log n)
    - Distance           : O(log n)  → sirf ek LCA call
    - Kth Node on Path   : O(log n)  → ek LCA + ek ancestor call
    - Depth Query        : O(1)

    Space Complexity:
    - O(n log n) for 'up' table
    - O(n) for depth[]

    Tree used in example:
            0          ← depth 0
           / \
          1   2        ← depth 1
         / \    \
        3   4    5     ← depth 2
             \
              6        ← depth 3

    Sample:
    Distance(3, 6) = 3   [3→1→4→6]
    3rd node on path(3,6) = 6  [k=0→3, k=1→1, k=2→4, k=3→6]
*/