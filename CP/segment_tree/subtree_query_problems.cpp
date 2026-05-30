#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// ============================================================
// BIT (Fenwick Tree)
// ============================================================
class BIT
{
public:
    int n;
    vector<ll> bit;

    BIT(int n)
    {
        this->n = n;
        bit.assign(n + 1, 0);
    }

    void update(int i, ll x)
    {
        for (; i <= n; i += (i & -i))
            bit[i] += x;
    }

    ll sum(int i)
    {
        ll total = 0;
        for (; i > 0; i -= (i & -i))
            total += bit[i];
        return total;
    }

    // Range sum [l, r] (1-indexed)
    ll query(int l, int r) { return sum(r) - sum(l - 1); }
};

// ============================================================
// SEGMENT TREE — Max, Min, XOR (teen alag merge operations)
// ============================================================
class SegmentTree
{
    vector<int> mx, mn, xorTree;
    int n;

    void build(vector<int> &arr, int idx, int l, int r)
    {
        if (l == r)
        {
            mx[idx] = mn[idx] = xorTree[idx] = arr[l];
            return;
        }
        int m = (l + r) / 2;
        build(arr, 2 * idx + 1, l, m);
        build(arr, 2 * idx + 2, m + 1, r);
        mx[idx] = max(mx[2 * idx + 1], mx[2 * idx + 2]);
        mn[idx] = min(mn[2 * idx + 1], mn[2 * idx + 2]);
        xorTree[idx] = xorTree[2 * idx + 1] ^ xorTree[2 * idx + 2];
    }

    void update(int idx, int l, int r, int pos, int val)
    {
        if (l == r)
        {
            mx[idx] = mn[idx] = xorTree[idx] = val;
            return;
        }
        int m = (l + r) / 2;
        if (pos <= m)
            update(2 * idx + 1, l, m, pos, val);
        else
            update(2 * idx + 2, m + 1, r, pos, val);
        mx[idx] = max(mx[2 * idx + 1], mx[2 * idx + 2]);
        mn[idx] = min(mn[2 * idx + 1], mn[2 * idx + 2]);
        xorTree[idx] = xorTree[2 * idx + 1] ^ xorTree[2 * idx + 2];
    }

    int queryMax(int idx, int l, int r, int ql, int qr)
    {
        if (qr < l || r < ql)
            return INT_MIN;
        if (ql <= l && r <= qr)
            return mx[idx];
        int m = (l + r) / 2;
        return max(queryMax(2 * idx + 1, l, m, ql, qr),
                   queryMax(2 * idx + 2, m + 1, r, ql, qr));
    }

    int queryMin(int idx, int l, int r, int ql, int qr)
    {
        if (qr < l || r < ql)
            return INT_MAX;
        if (ql <= l && r <= qr)
            return mn[idx];
        int m = (l + r) / 2;
        return min(queryMin(2 * idx + 1, l, m, ql, qr),
                   queryMin(2 * idx + 2, m + 1, r, ql, qr));
    }

    int queryXor(int idx, int l, int r, int ql, int qr)
    {
        if (qr < l || r < ql)
            return 0;
        if (ql <= l && r <= qr)
            return xorTree[idx];
        int m = (l + r) / 2;
        return queryXor(2 * idx + 1, l, m, ql, qr) ^
               queryXor(2 * idx + 2, m + 1, r, ql, qr);
    }

public:
    SegmentTree(vector<int> &arr)
    {
        n = arr.size();
        mx.resize(4 * n);
        mn.resize(4 * n);
        xorTree.resize(4 * n);
        build(arr, 0, 0, n - 1);
    }

    void update(int pos, int val) { update(0, 0, n - 1, pos, val); }
    int queryMax(int l, int r) { return queryMax(0, 0, n - 1, l, r); }
    int queryMin(int l, int r) { return queryMin(0, 0, n - 1, l, r); }
    int queryXor(int l, int r) { return queryXor(0, 0, n - 1, l, r); }
};

// ============================================================
// LAZY SEGMENT TREE — Subtree Range Update (+X to range)
// ============================================================
class LazySegTree
{
    vector<ll> tree, lazy;
    int n;

    void build(vector<int> &arr, int idx, int l, int r)
    {
        lazy[idx] = 0;
        if (l == r)
        {
            tree[idx] = arr[l];
            return;
        }
        int m = (l + r) / 2;
        build(arr, 2 * idx + 1, l, m);
        build(arr, 2 * idx + 2, m + 1, r);
        tree[idx] = tree[2 * idx + 1] + tree[2 * idx + 2];
    }

    void pushDown(int idx, int l, int r)
    {
        if (lazy[idx] != 0)
        {
            int m = (l + r) / 2;
            // left child update
            tree[2 * idx + 1] += lazy[idx] * (m - l + 1);
            lazy[2 * idx + 1] += lazy[idx];
            // right child update
            tree[2 * idx + 2] += lazy[idx] * (r - m);
            lazy[2 * idx + 2] += lazy[idx];
            // clear parent lazy
            lazy[idx] = 0;
        }
    }

    void update(int idx, int l, int r, int ql, int qr, ll val)
    {
        if (qr < l || r < ql)
            return;
        if (ql <= l && r <= qr)
        {
            tree[idx] += val * (r - l + 1);
            lazy[idx] += val;
            return;
        }
        pushDown(idx, l, r);
        int m = (l + r) / 2;
        update(2 * idx + 1, l, m, ql, qr, val);
        update(2 * idx + 2, m + 1, r, ql, qr, val);
        tree[idx] = tree[2 * idx + 1] + tree[2 * idx + 2];
    }

    ll query(int idx, int l, int r, int ql, int qr)
    {
        if (qr < l || r < ql)
            return 0;
        if (ql <= l && r <= qr)
            return tree[idx];
        pushDown(idx, l, r);
        int m = (l + r) / 2;
        return query(2 * idx + 1, l, m, ql, qr) +
               query(2 * idx + 2, m + 1, r, ql, qr);
    }

public:
    LazySegTree(vector<int> &arr)
    {
        n = arr.size();
        tree.resize(4 * n);
        lazy.resize(4 * n);
        build(arr, 0, 0, n - 1);
    }

    // Range mein saare nodes ko +val karo
    void update(int l, int r, ll val) { update(0, 0, n - 1, l, r, val); }
    ll query(int l, int r) { return query(0, 0, n - 1, l, r); }
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

    void dfs(int u, int par)
    {
        in_time[u] = timer++;
        for (int v : adj[u])
            if (v != par)
                dfs(v, u);
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

    /*
           0 (val=3)
          / \
         1   2  (val=1, val=4)
        / \   \
       3   4   5  (val=2, val=7, val=5)
    */
    int n = 6;
    vector<int> vals = {3, 1, 4, 2, 7, 5};

    EulerTour et(n);
    et.addEdge(0, 1);
    et.addEdge(0, 2);
    et.addEdge(1, 3);
    et.addEdge(1, 4);
    et.addEdge(2, 5);
    et.build(0);

    // Flat array banao euler tour order se
    vector<int> flat(n);
    for (int node = 0; node < n; node++)
        flat[et.in_time[node]] = vals[node];

    // -------------------------------------------------------
    // CODE 1: Max, Min, XOR queries on subtree
    // -------------------------------------------------------
    cout << "======= MAX / MIN / XOR =======\n";
    SegmentTree seg(flat);

    // Max/Min/Xor queries
    vector<vector<int>> Query_operations = {{0}, {1}, {2}};

    for (auto &q : Query_operations)
    {
        int node = q[0];
        int l = et.in_time[node], r = et.out_time[node];
        cout << "Subtree of node " << node << ":\n";
        cout << "  Max = " << seg.queryMax(l, r) << "\n";
        cout << "  Min = " << seg.queryMin(l, r) << "\n";
        cout << "  Xor = " << seg.queryXor(l, r) << "\n";
    }

    // Update node 3 ki value 2 -> 9
    vector<vector<int>> updates = {{3, 9}};
    for (auto &u : updates)
        seg.update(et.in_time[u[0]], u[1]);

    cout << "\nNode 3 update (2->9) ke baad:\n";
    cout << "  Subtree Max of node 1 = " << seg.queryMax(et.in_time[1], et.out_time[1]) << "\n";
    cout << "  Subtree Min of node 1 = " << seg.queryMin(et.in_time[1], et.out_time[1]) << "\n";
    cout << "  Subtree Xor of node 1 = " << seg.queryXor(et.in_time[1], et.out_time[1]) << "\n";

    // -------------------------------------------------------
    // CODE 2: Subtree Range Update (Lazy Seg Tree)
    // -------------------------------------------------------
    cout << "\n======= SUBTREE RANGE UPDATE (LAZY) =======\n";
    LazySegTree lazySeg(flat);

    cout << "Before update:\n";
    cout << "  Subtree sum of node 0 = " << lazySeg.query(et.in_time[0], et.out_time[0]) << "\n"; // 3+1+4+2+7+5 = 22
    cout << "  Subtree sum of node 1 = " << lazySeg.query(et.in_time[1], et.out_time[1]) << "\n"; // 1+2+7 = 10

    // Subtree of node 1 ke saare nodes ko +10 karo
    vector<vector<int>> rangeUpdates = {{1, 10}}; // {node, addVal}
    for (auto &u : rangeUpdates)
    {
        int node = u[0], addVal = u[1];
        lazySeg.update(et.in_time[node], et.out_time[node], addVal);
        cout << "\nSubtree of node " << node << " mein +=" << addVal << " kiya\n";
    }

    cout << "\nAfter update:\n";
    cout << "  Subtree sum of node 0 = " << lazySeg.query(et.in_time[0], et.out_time[0]) << "\n"; // 22 + 3*10 = 52
    cout << "  Subtree sum of node 1 = " << lazySeg.query(et.in_time[1], et.out_time[1]) << "\n"; // 10 + 3*10 = 40
    cout << "  Subtree sum of node 2 = " << lazySeg.query(et.in_time[2], et.out_time[2]) << "\n"; // 4+5 = 9 (unchanged)

    // -------------------------------------------------------
    // CODE 3: Count nodes in subtree with value X (BIT use)
    // -------------------------------------------------------
    cout << "\n======= COUNT IN SUBTREE (BIT) =======\n";

    // BIT 1-indexed hai, euler tour 0-indexed → +1 karo
    // flat array mein value X hai wahan 1 rakho, baaki 0

    int targetVal = 2; // kitne nodes ki value == 2 hai subtree mein
    BIT bit(n);

    // BIT mein sirf wahi positions mark karo jahan value == targetVal
    for (int node = 0; node < n; node++)
        if (vals[node] == targetVal)
            bit.update(et.in_time[node] + 1, 1); // +1 for 1-indexing

    // Count queries
    vector<int> countQueries = {0, 1, 2}; // in nodes ke subtree mein count chahiye
    for (int node : countQueries)
    {
        int l = et.in_time[node] + 1; // 1-indexed
        int r = et.out_time[node] + 1;
        cout << "Count of value " << targetVal
             << " in subtree of node " << node
             << " = " << bit.query(l, r) << "\n";
    }

    // BIT update: node 5 ki value change 5->2 (naya targetVal node)
    cout << "\nNode 5 ki value 5->2 karte hain\n";
    bit.update(et.in_time[5] + 1, 1); // node 5 ab targetVal hai

    cout << "Count of value " << targetVal
         << " in subtree of node 0 = "
         << bit.query(et.in_time[0] + 1, et.out_time[0] + 1) << "\n";
    cout << "Count of value " << targetVal
         << " in subtree of node 2 = "
         << bit.query(et.in_time[2] + 1, et.out_time[2] + 1) << "\n";

    return 0;
}