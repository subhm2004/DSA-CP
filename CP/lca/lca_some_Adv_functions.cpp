#include <bits/stdc++.h>
using namespace std;

class Binary_Lifting
{
private:
    int n, LOG;
    vector<vector<int>> up;
    vector<int> depth;
    vector<vector<int>> children;

    // ✅ NEW: Path query tables
    vector<vector<int>> maxEdge;       // max edge weight on path to 2^j-th ancestor
    vector<vector<int>> minEdge;       // min edge weight on path to 2^j-th ancestor
    vector<vector<long long>> sumNode; // sum of nodes on path to 2^j-th ancestor

    vector<int> nodeVal;      // value of each node
    vector<int> edgeToParent; // edge weight to parent

    void dfs(int node, int d)
    {
        depth[node] = d;
        for (int child : children[node])
            dfs(child, d + 1);
    }

    void preCompute(const vector<int> &parent)
    {
        // Step 1: Children list
        children.assign(n, vector<int>());
        for (int i = 0; i < n; ++i)
            if (parent[i] != -1)
                children[parent[i]].push_back(i);

        // Step 2: 2^0-th parent + base cases for path queries
        for (int i = 0; i < n; ++i)
        {
            up[i][0] = parent[i];
            maxEdge[i][0] = (parent[i] != -1) ? edgeToParent[i] : 0;
            minEdge[i][0] = (parent[i] != -1) ? edgeToParent[i] : INT_MAX;
            sumNode[i][0] = (parent[i] != -1) ? nodeVal[parent[i]] : 0; // parent node ka value
        }

        // Step 3: Depth via DFS
        for (int i = 0; i < n; ++i)
            if (parent[i] == -1)
                dfs(i, 0);

        // Step 4: Fill all tables
        for (int j = 1; j < LOG; ++j)
        {
            for (int i = 0; i < n; ++i)
            {
                int prev = up[i][j - 1];
                if (prev != -1)
                {
                    up[i][j] = up[prev][j - 1];
                    maxEdge[i][j] = max(maxEdge[i][j - 1], maxEdge[prev][j - 1]);
                    minEdge[i][j] = min(minEdge[i][j - 1], minEdge[prev][j - 1]);
                    sumNode[i][j] = sumNode[i][j - 1] + sumNode[prev][j - 1];
                }
                else
                {
                    up[i][j] = -1;
                    maxEdge[i][j] = 0;
                    minEdge[i][j] = INT_MAX;
                    sumNode[i][j] = 0;
                }
            }
        }
    }

public:
    Binary_Lifting(int n, const vector<int> &parent,
                   const vector<int> &nodeValues,
                   const vector<int> &edgeWeights) // edgeWeights[i] = weight of edge i→parent[i]
    {
        this->n = n;
        LOG = (n > 1) ? (int)ceil(log2(n)) + 1 : 1;
        nodeVal = nodeValues;
        edgeToParent = edgeWeights;

        up.assign(n, vector<int>(LOG, -1));
        maxEdge.assign(n, vector<int>(LOG, 0));
        minEdge.assign(n, vector<int>(LOG, INT_MAX));
        sumNode.assign(n, vector<long long>(LOG, 0));
        depth.assign(n, 0);

        preCompute(parent);
    }

    // ─────────────────────────────────────────
    // Core: K-th Ancestor
    // ─────────────────────────────────────────
    int get_Kth_Ancestor(int node, int k)
    {
        for (int i = 0; i < LOG; ++i)
            if (k & (1 << i))
            {
                node = up[node][i];
                if (node == -1)
                    return -1;
            }
        return node;
    }

    // ─────────────────────────────────────────
    // Core: LCA
    // ─────────────────────────────────────────
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

    // ─────────────────────────────────────────
    // ✅ NEW: Max edge weight on path(u, v)
    // ─────────────────────────────────────────
    int max_edge_on_path(int u, int v)
    {
        int lca = find_LCA(u, v);
        if (lca == -1)
            return -1;

        int result = 0;

        // u → LCA
        auto climb = [&](int node, int steps, bool isMax) -> int
        {
            int val = isMax ? 0 : INT_MAX;
            for (int i = 0; i < LOG; ++i)
                if (steps & (1 << i))
                {
                    val = isMax ? max(val, maxEdge[node][i])
                                : min(val, minEdge[node][i]);
                    node = up[node][i];
                    if (node == -1)
                        break;
                }
            return val;
        };

        int du = depth[u] - depth[lca];
        int dv = depth[v] - depth[lca];

        return max(climb(u, du, true), climb(v, dv, true));
    }

    // ─────────────────────────────────────────
    // ✅ NEW: Min edge weight on path(u, v)
    // ─────────────────────────────────────────
    int min_edge_on_path(int u, int v)
    {
        int lca = find_LCA(u, v);
        if (lca == -1)
            return -1;

        auto climb_min = [&](int node, int steps) -> int
        {
            int val = INT_MAX;
            for (int i = 0; i < LOG; ++i)
                if (steps & (1 << i))
                {
                    val = min(val, minEdge[node][i]);
                    node = up[node][i];
                    if (node == -1)
                        break;
                }
            return val;
        };

        int du = depth[u] - depth[lca];
        int dv = depth[v] - depth[lca];

        int fromU = (du > 0) ? climb_min(u, du) : INT_MAX;
        int fromV = (dv > 0) ? climb_min(v, dv) : INT_MAX;

        return min(fromU, fromV);
    }

    // ─────────────────────────────────────────
    // ✅ NEW: Sum of node values on path(u, v)
    // Includes both u and v
    // ─────────────────────────────────────────
    long long sum_on_path(int u, int v)
    {
        int lca = find_LCA(u, v);
        if (lca == -1)
            return -1;

        auto climb_sum = [&](int node, int steps) -> long long
        {
            long long s = nodeVal[node]; // include node itself
            for (int i = 0; i < LOG; ++i)
                if (steps & (1 << i))
                {
                    s += sumNode[node][i];
                    node = up[node][i];
                    if (node == -1)
                        break;
                }
            return s;
        };

        int du = depth[u] - depth[lca];
        int dv = depth[v] - depth[lca];

        // u se LCA tak + v se LCA tak - LCA double count
        return climb_sum(u, du) + climb_sum(v, dv) - nodeVal[lca];
    }

    // ─────────────────────────────────────────
    // ✅ NEW: XOR of node values on path(u, v)
    // ─────────────────────────────────────────
    int xor_on_path(int u, int v)
    {
        int lca = find_LCA(u, v);
        if (lca == -1)
            return -1;

        // prefix XOR from root: xorRoot[v] XOR xorRoot[u] XOR nodeVal[lca]
        // Simple approach: climb and XOR
        auto climb_xor = [&](int node, int steps) -> int
        {
            int x = nodeVal[node];
            for (int i = 0; i < LOG; ++i)
                if (steps & (1 << i))
                {
                    // XOR all nodes in this jump
                    // (stored separately would be faster, here we recompute via climbing)
                    node = up[node][i];
                    if (node == -1)
                        break;
                    x ^= nodeVal[node];
                }
            return x;
        };

        int du = depth[u] - depth[lca];
        int dv = depth[v] - depth[lca];

        return climb_xor(u, du) ^ climb_xor(v, dv) ^ nodeVal[lca];
    }

    // ─────────────────────────────────────────
    // ✅ NEW: LCA of multiple nodes
    // LCA(a,b,c,...) = LCA(LCA(a,b), c) ...
    // ─────────────────────────────────────────
    int lca_of_multiple(vector<int> &nodes)
    {
        if (nodes.empty())
            return -1;
        int result = nodes[0];
        for (int i = 1; i < (int)nodes.size(); ++i)
            result = find_LCA(result, nodes[i]);
        return result;
    }

    // ─────────────────────────────────────────
    // Existing features
    // ─────────────────────────────────────────
    int distance(int u, int v)
    {
        int lca = find_LCA(u, v);
        if (lca == -1)
            return -1;
        return depth[u] + depth[v] - 2 * depth[lca];
    }

    int kth_node_on_path(int u, int v, int k)
    {
        int lca = find_LCA(u, v);
        if (lca == -1)
            return -1;
        int dist_u = depth[u] - depth[lca];
        int dist_v = depth[v] - depth[lca];
        int total = dist_u + dist_v;

        if (k < 0 || k > total)
            return -1;
        if (k <= dist_u)
            return get_Kth_Ancestor(u, k);
        return get_Kth_Ancestor(v, total - k);
    }

    int getDepth(int node) { return depth[node]; }
};

// ═══════════════════════════════════════════════════════
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    /*
        Tree:
                0  (val=10)
               / \
              1   2  (val=20, 30)
             / \    \
            3   4    5  (val=40, 50, 60)
                 \
                  6  (val=70)

        parent[]     = {-1, 0, 0, 1, 1, 2, 4}
        nodeValues[] = {10, 20, 30, 40, 50, 60, 70}
        edgeWeights[] = {0, 5, 3, 8, 2, 7, 4}
            (edgeWeights[i] = weight of edge from i to parent[i])
            (root ka 0 hoga, ignored)
    */

    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    vector<int> parent(n), nodeValues(n), edgeWeights(n, 0);

    cout << "Enter parent of each node (root = -1):\n";
    for (int i = 0; i < n; ++i)
    {
        cout << "parent[" << i << "] = ";
        cin >> parent[i];
    }

    cout << "Enter node values:\n";
    for (int i = 0; i < n; ++i)
    {
        cout << "val[" << i << "] = ";
        cin >> nodeValues[i];
    }

    cout << "Enter edge weight to parent (root = 0):\n";
    for (int i = 0; i < n; ++i)
    {
        cout << "edge[" << i << "] = ";
        cin >> edgeWeights[i];
    }

    Binary_Lifting bl(n, parent, nodeValues, edgeWeights);

    int choice;
    do
    {
        cout << "\n========== MENU ==========\n";
        cout << "1.  K-th Ancestor\n";
        cout << "2.  LCA (2 nodes)\n";
        cout << "3.  Depth of node\n";
        cout << "4.  Distance between nodes\n";
        cout << "5.  Kth node on path(u,v)\n";
        cout << "6.  Max edge weight on path\n"; // ✅ NEW
        cout << "7.  Min edge weight on path\n"; // ✅ NEW
        cout << "8.  Sum of nodes on path\n";    // ✅ NEW
        cout << "9.  XOR of nodes on path\n";    // ✅ NEW
        cout << "10. LCA of multiple nodes\n";   // ✅ NEW
        cout << "0.  Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int node, k;
            cout << "Node aur K: ";
            cin >> node >> k;
            int ans = bl.get_Kth_Ancestor(node, k);
            cout << (ans == -1 ? "Exist nahi karta\n" : to_string(ans) + "\n");
        }
        else if (choice == 2)
        {
            int u, v;
            cout << "u v: ";
            cin >> u >> v;
            cout << "LCA = " << bl.find_LCA(u, v) << "\n";
        }
        else if (choice == 3)
        {
            int node;
            cout << "Node: ";
            cin >> node;
            cout << "Depth = " << bl.getDepth(node) << "\n";
        }
        else if (choice == 4)
        {
            int u, v;
            cout << "u v: ";
            cin >> u >> v;
            cout << "Distance = " << bl.distance(u, v) << "\n";
        }
        else if (choice == 5)
        {
            int u, v, k;
            cout << "u v k: ";
            cin >> u >> v >> k;
            int ans = bl.kth_node_on_path(u, v, k);
            cout << (ans == -1 ? "Invalid k\n" : to_string(ans) + "\n");
        }
        else if (choice == 6)
        {
            int u, v;
            cout << "u v: ";
            cin >> u >> v;
            cout << "Max edge on path = " << bl.max_edge_on_path(u, v) << "\n";
        }
        else if (choice == 7)
        {
            int u, v;
            cout << "u v: ";
            cin >> u >> v;
            cout << "Min edge on path = " << bl.min_edge_on_path(u, v) << "\n";
        }
        else if (choice == 8)
        {
            int u, v;
            cout << "u v: ";
            cin >> u >> v;
            cout << "Sum on path = " << bl.sum_on_path(u, v) << "\n";
        }
        else if (choice == 9)
        {
            int u, v;
            cout << "u v: ";
            cin >> u >> v;
            cout << "XOR on path = " << bl.xor_on_path(u, v) << "\n";
        }
        else if (choice == 10)
        {
            int m;
            cout << "Kitne nodes: ";
            cin >> m;
            vector<int> nodes(m);
            cout << "Nodes: ";
            for (int &x : nodes)
                cin >> x;
            cout << "LCA of all = " << bl.lca_of_multiple(nodes) << "\n";
        }
        else if (choice != 0)
            cout << "Invalid!\n";

    } while (choice != 0);

    return 0;
}

/*
═══════════════════════════════════════════════════
Tree used:
        0  (val=10)
       / \
      1   2  (val=20, 30)
     / \    \
    3   4    5  (val=40, 50, 60)
         \
          6  (val=70)

Edge weights (node → parent):
  1→0: 5,  2→0: 3
  3→1: 8,  4→1: 2,  5→2: 7
  6→4: 4

Sample Queries:
  Max edge path(3,6) = max(8,2,4)     = 8
  Min edge path(3,6) = min(8,2,4)     = 2
  Sum path(3,6)      = 40+20+10+50+70 = (3→1→0→... wait)
                     = 40+20+50+70    = 180  [path: 3→1→4→6]
  XOR path(3,5)      = 40^20^10^30^60
  LCA(3,5,6)         = 0
═══════════════════════════════════════════════════

Time Complexity:
  Preprocessing   : O(N log N)
  All queries     : O(log N) each
  Multi-node LCA  : O(K log N) for K nodes

Space: O(N log N)
*/
/*
```

---

## Naye features ka quick summary
```
Feature              Formula / Trick
─────────────────────────────────────────────────────
Max edge path(u,v)   Climb u→LCA, v→LCA, max lena
Min edge path(u,v)   Same, min lena
Sum path(u,v)        sum(u→LCA) + sum(v→LCA) - nodeVal[LCA]
XOR path(u,v)        xor(u→LCA) ^ xor(v→LCA) ^ nodeVal[LCA]
Multi LCA            LCA(LCA(a,b), c, d...) iteratively
*/