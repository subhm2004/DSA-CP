#include <bits/stdc++.h>
using namespace std;

// ============================================================
// SEGMENT TREE
// ============================================================
class SegmentTree
{
    vector<int> tree;
    int n;

    void build(vector<int> &arr, int idx, int l, int r)
    {
        if (l == r) { tree[idx] = arr[l]; return; }
        int m = (l + r) / 2;
        build(arr, 2*idx+1, l, m);
        build(arr, 2*idx+2, m+1, r);
        tree[idx] = tree[2*idx+1] + tree[2*idx+2];
    }

    void update(int idx, int l, int r, int pos, int val)
    {
        if (l == r) { tree[idx] = val; return; }
        int m = (l + r) / 2;
        if (pos <= m) update(2*idx+1, l, m, pos, val);
        else          update(2*idx+2, m+1, r, pos, val);
        tree[idx] = tree[2*idx+1] + tree[2*idx+2];
    }

    int query(int idx, int l, int r, int ql, int qr)
    {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return tree[idx];
        int m = (l + r) / 2;
        return query(2*idx+1, l, m, ql, qr) + query(2*idx+2, m+1, r, ql, qr);
    }

public:
    SegmentTree(vector<int> &arr)
    {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 0, 0, n-1);
    }

    void update(int pos, int val) { update(0, 0, n-1, pos, val); }
    int  query(int l, int r)      { return query(0, 0, n-1, l, r); }
};

// ============================================================
// EULER TOUR
// ============================================================
class EulerTour
{
public:
    int n;
    vector<vector<int>> adj;
    vector<int> in_time, out_time;
    int timer = 0;

    EulerTour(int n) : n(n), adj(n), in_time(n), out_time(n) {}

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int parent)
    {
        in_time[u] = timer++;
        for (int v : adj[u])
            if (v != parent) dfs(v, u);
        out_time[u] = timer - 1;
    }

    void build(int root = 0) { dfs(root, -1); }
};

// ============================================================
// MAIN
// ============================================================
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 5;
    vector<int> vals = {1, 2, 3, 4, 5};  // node 0..4 ki values

    /*
           0 (val=1)
          / \
         1   2  (val=2, val=3)
        / \
       3   4  (val=4, val=5)
    */

    // Query_operations[i] = {node}        → subtree sum of node
    // updates[i]          = {node, newVal} → node ki value update karo
    vector<vector<int>> Query_operations = {
        {0},   // subtree sum of node 0
        {1},   // subtree sum of node 1
        {2},   // subtree sum of node 2
        {3},   // subtree sum of node 3
    };

    vector<vector<int>> updates = {
        {3, 10},  // node 3 ki value → 10
        {0, 5},   // node 0 ki value → 5
    };

    // -------------------------------------------------------
    // Step 1: Euler Tour
    // -------------------------------------------------------
    EulerTour et(n);
    et.addEdge(0, 1);
    et.addEdge(0, 2);
    et.addEdge(1, 3);
    et.addEdge(1, 4);
    et.build(0);

    // -------------------------------------------------------
    // Step 2: Flat array banao
    // -------------------------------------------------------
    vector<int> flat(n);
    for (int node = 0; node < n; node++)
        flat[et.in_time[node]] = vals[node];

    // -------------------------------------------------------
    // Step 3: Segment Tree banao
    // -------------------------------------------------------
    SegmentTree seg(flat);

    // -------------------------------------------------------
    // Pehle saari queries chalao (updates se pehle)
    // -------------------------------------------------------
    cout << "=== Queries (before updates) ===\n";
    for (auto &q : Query_operations)
    {
        int node = q[0];
        int ans  = seg.query(et.in_time[node], et.out_time[node]);
        cout << "Subtree sum of node " << node << " = " << ans << "\n";
    }

    // -------------------------------------------------------
    // Ab updates apply karo
    // -------------------------------------------------------
    cout << "\n=== Updates ===\n";
    for (auto &u : updates)
    {
        int node   = u[0];
        int newVal = u[1];
        seg.update(et.in_time[node], newVal);
        vals[node] = newVal;  // vals bhi sync rakho
        cout << "Node " << node << " updated to " << newVal << "\n";
    }

    // -------------------------------------------------------
    // Updates ke baad phir se queries
    // -------------------------------------------------------
    cout << "\n=== Queries (after updates) ===\n";
    for (auto &q : Query_operations)
    {
        int node = q[0];
        int ans  = seg.query(et.in_time[node], et.out_time[node]);
        cout << "Subtree sum of node " << node << " = " << ans << "\n";
    }

    return 0;
}
