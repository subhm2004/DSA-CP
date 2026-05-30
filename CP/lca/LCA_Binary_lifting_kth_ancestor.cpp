#include <bits/stdc++.h>
using namespace std;

class Binary_Lifting
{
private:
    int n, LOG;
    vector<vector<int>> up;
    vector<int> depth;
    vector<vector<int>> children;

    void dfs(int node, int d)
    {
        depth[node] = d;
        for (int child : children[node])
            dfs(child, d + 1);
    }

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
    Binary_Lifting(int n, const vector<int> &parent)
    {
        this->n = n;
        LOG = (n > 1) ? (int)ceil(log2(n)) + 1 : 1;
        up.assign(n, vector<int>(LOG, -1));
        depth.assign(n, 0);

        preCompute(parent);
    }

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
            if (up[u][i] != -1 && up[u][i] != up[v][i])
            {
                u = up[u][i];
                v = up[v][i];
            }

        return up[u][0];
    }

    // ✅ NEW: Distance between two nodes
    // Formula: depth[u] + depth[v] - 2 * depth[LCA(u,v)]
    int distance(int u, int v)
    {
        int lca = find_LCA(u, v);
        if (lca == -1)
            return -1;
        return depth[u] + depth[v] - 2 * depth[lca];
    }

    // ✅ NEW: Kth node on path from u to v (0-indexed from u)
    // Path: u → LCA → v
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

/*
```

---

## Dono Functions ka Logic

### Distance — 1 line formula
```
depth[u] + depth[v] - 2 * depth[LCA]

3 se 6 tak:
depth[3]=2, depth[6]=3, LCA=1, depth[1]=1
= 2 + 3 - 2*1 = 3 ✅
```

### Kth Node on Path
```
Path(3, 6): 3 → 1 → 4 → 6
             ↑LCA

dist_u = depth[3] - depth[1] = 1   (3→1)
dist_v = depth[6] - depth[1] = 2   (6→1)
total  = 3

k=0 → get_Kth_Ancestor(3, 0) = 3
k=1 → get_Kth_Ancestor(3, 1) = 1  (LCA)
k=2 → get_Kth_Ancestor(6, 1) = 4
k=3 → get_Kth_Ancestor(6, 0) = 6

*/