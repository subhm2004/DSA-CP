#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// ════════════════════════════════════════════════════════════════════════════
// SUBTREE QUERY PROBLEMS  (Euler Tour + Segment Tree / BIT ka combo)
// ────────────────────────────────────────────────────────────────────────────
// Idea: tree (graph) ke har node ka SUBTREE ek array me CONTIGUOUS range ban jaata
// hai agar hum Euler Tour (DFS in/out time) use karein. Phir subtree pe koi bhi
// query bas ek RANGE query ban jaati hai segment tree / BIT pe:
//
//   node u ka subtree  ==  flat array me range [in_time[u], out_time[u]]
//
// Recursive seg tree functions me common params (ek baar samajh le):
//   idx -> tree array me current node ka index (root = 0)
//          left child = 2*idx + 1, right child = 2*idx + 2
//   l,r -> current node jis segment ka maalik hai uske left/right ends (arr index)
//   ql,qr -> query/update ki gayi range ke left/right ends
//   m   -> (l + r) / 2, segment ko do halves me todne ka point
//
// 3 overlap case: 1) NO overlap (qr<l || r<ql)  2) FULL overlap (ql<=l && r<=qr)
//                 3) PARTIAL -> dono bachho me recurse
// ════════════════════════════════════════════════════════════════════════════

// ════════════════════════════════════════════════════════════════════════════
// BIT (Fenwick Tree) — prefix sum / point update ke liye fast structure
// ────────────────────────────────────────────────────────────────────────────
// 1-indexed hota hai. (i & -i) lowest set bit deta hai jisse ye agle/pichle
// responsible node tak jump karta hai. Yaha "kitne nodes ki value == X hai
// subtree me" count karne ke liye use ho raha hai.
// ════════════════════════════════════════════════════════════════════════════
class BIT
{
public:
    int n;
    vector<ll> bit;  // 1-indexed fenwick array

    // ── BIT: constructor — n size ka fenwick array banao ──
    //   1) n store karo taaki loop ki upper bound pata rahe
    //   2) bit vector ko n+1 size do (index 0 dummy hai, real indices 1..n)
    //   3) Sab entries 0 se init karo — abhi koi prefix sum nahi hai
    BIT(int n)
    {
        this->n = n;
        bit.assign(n + 1, 0);
    }

    // ── update: index i pe x add karo (point update) ──
    //   1) i se shuru karke har responsible node tak jao jahan i ka asar padta hai
    //   2) Har node pe x add karo (bit[i] += x)
    //   3) i += (i & -i) → lowest set bit se agla parent node jise ye index cover karta hai
    //   4) Jab tak i <= n hai tab tak loop chalao — O(log n) nodes update hote hain
    void update(int i, ll x)
    {
        for (; i <= n; i += (i & -i))  // i & -i = lowest set bit → agla responsible node
            bit[i] += x;
    }

    // ── sum: prefix sum [1, i] nikalo ──
    //   1) total = 0 se shuru karo
    //   2) i se niche jao: har step pe bit[i] ko total me jodo
    //   3) i -= (i & -i) → pichla block jiska sum abhi tak nahi liya
    //   4) i > 0 tak chalao, phir total return karo
    ll sum(int i)
    {
        ll total = 0;
        for (; i > 0; i -= (i & -i))  // pichla responsible block ki taraf jump
            total += bit[i];
        return total;
    }

    // ── query: range sum [l, r] (1-indexed) ──
    //   1) prefix(r) se [1..r] ka total lo
    //   2) prefix(l-1) subtract karo taaki [1..l-1] hata jaaye
    //   3) Bacha hua = exactly [l, r] ka sum
    ll query(int l, int r) { return sum(r) - sum(l - 1); }
};

// ============================================================
// SEGMENT TREE — Max, Min, XOR (teen alag merge operations)
// ============================================================
class SegmentTree
{
    vector<int> mx, mn, xorTree;  // teen alag trees: max, min, xor
    int n;

    // ── build: array se teeno trees (max/min/xor) ek saath banao ──
    //   1) Base case l==r → leaf hai, teeno arrays me arr[l] daal do
    //   2) mid = (l+r)/2 se segment ko left [l,m] aur right [m+1,r] me todo
    //   3) Dono bachho ko recursively build karo
    //   4) Wapsi pe parent me max = max(left,right), min = min(...), xor = xor(...)
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

    // ── update: position pos ki value val se replace karo ──
    //   1) pos jis half me hai (left ya right) usi child me recurse karo
    //   2) Leaf (l==r) pe pahunch ke teeno arrays me val set karo
    //   3) Wapsi aate waqt har ancestor pe max/min/xor dobara merge karo
    //   4) Sirf root se pos tak ka path change hota hai — O(log n)
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

    // ── queryMax: range [ql,qr] me maximum element ──
    //   1) Case 1 NO overlap (qr<l || r<ql) → INT_MIN (max ka identity)
    //   2) Case 2 FULL overlap (ql<=l && r<=qr) → seedha mx[idx] return
    //   3) Case 3 PARTIAL → mid se todo, dono bachho ka max lo aur unka max return
    int queryMax(int idx, int l, int r, int ql, int qr)
    {
        if (qr < l || r < ql)  // Case 1: no overlap
            return INT_MIN;
        if (ql <= l && r <= qr)  // Case 2: full overlap
            return mx[idx];
        int m = (l + r) / 2;  // Case 3: partial
        return max(queryMax(2 * idx + 1, l, m, ql, qr),
                   queryMax(2 * idx + 2, m + 1, r, ql, qr));
    }

    // ── queryMin: range [ql,qr] me minimum element ──
    //   1) Case 1 NO overlap → INT_MAX return (min ka identity)
    //   2) Case 2 FULL overlap → seedha mn[idx] return
    //   3) Case 3 PARTIAL → dono bachho se min maang ke unka min return
    int queryMin(int idx, int l, int r, int ql, int qr)
    {
        if (qr < l || r < ql)  // Case 1
            return INT_MAX;
        if (ql <= l && r <= qr)  // Case 2
            return mn[idx];
        int m = (l + r) / 2;  // Case 3
        return min(queryMin(2 * idx + 1, l, m, ql, qr),
                   queryMin(2 * idx + 2, m + 1, r, ql, qr));
    }

    // ── queryXor: range [ql,qr] ka XOR ──
    //   1) Case 1 NO overlap → 0 return (XOR identity: x^0 = x)
    //   2) Case 2 FULL overlap → seedha xorTree[idx] return
    //   3) Case 3 PARTIAL → left XOR ^ right XOR combine karo
    int queryXor(int idx, int l, int r, int ql, int qr)
    {
        if (qr < l || r < ql)  // Case 1
            return 0;
        if (ql <= l && r <= qr)  // Case 2
            return xorTree[idx];
        int m = (l + r) / 2;  // Case 3
        return queryXor(2 * idx + 1, l, m, ql, qr) ^
               queryXor(2 * idx + 2, m + 1, r, ql, qr);
    }

public:
    // ── SegmentTree: constructor — teen parallel trees allocate + build ──
    //   1) n = arr.size(), har tree ke liye 4*n size safe allocate karo
    //   2) mx, mn, xorTree teeno vectors resize karo
    //   3) Root (idx=0) se poori array [0, n-1] par build() call karo
    SegmentTree(vector<int> &arr)
    {
        n = arr.size();
        mx.resize(4 * n);
        mn.resize(4 * n);
        xorTree.resize(4 * n);
        build(arr, 0, 0, n - 1);
    }

    // Public wrappers: root idx=0, segment [0, n-1] khud set ho jaata hai
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
    vector<ll> tree, lazy;  // sum tree + pending lazy add
    int n;

    // ── build: array se sum-based lazy segment tree banao ──
    //   1) Har node pe lazy[idx]=0 set karo (abhi koi pending add nahi)
    //   2) Leaf pe tree[idx] = arr[l], internal pe dono bachho ka sum
    //   3) Recursively left [l,m] aur right [m+1,r] build karo
    //   4) Parent ka sum = left child sum + right child sum
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

    // ── pushDown: parent ka pending lazy bachho tak bhejo ──
    //   1) Agar lazy[idx]==0 hai to kuch nahi karna — return implicitly
    //   2) Left child: tree me lazy*leftSize add, lazy child me += lazy[idx]
    //   3) Right child: tree me lazy*rightSize add, lazy child me += lazy[idx]
    //   4) Parent lazy clear karo — ab ye pending apply ho chuka hai
    void pushDown(int idx, int l, int r)
    {
        if (lazy[idx] != 0)
        {
            int m = (l + r) / 2;
            tree[2 * idx + 1] += lazy[idx] * (m - l + 1);  // left segment size se multiply
            lazy[2 * idx + 1] += lazy[idx];                 // bacche ko pending pass
            tree[2 * idx + 2] += lazy[idx] * (r - m);       // right segment size
            lazy[2 * idx + 2] += lazy[idx];
            lazy[idx] = 0;  // parent ka pending clear
        }
    }

    // ── update: range [ql,qr] ke har element me val add karo ──
    //   1) Case 1 NO overlap → seedha return, kuch mat karo
    //   2) Case 2 FULL overlap → tree[idx] += val*size, lazy[idx] += val
    //   3) Case 3 PARTIAL → pehle pushDown (pending clear), phir dono bachho me recurse
    //   4) Wapsi pe tree[idx] = left sum + right sum refresh karo
    void update(int idx, int l, int r, int ql, int qr, ll val)
    {
        if (qr < l || r < ql)  // Case 1
            return;
        if (ql <= l && r <= qr)  // Case 2: full overlap — lazy lagao
        {
            tree[idx] += val * (r - l + 1);
            lazy[idx] += val;
            return;
        }
        pushDown(idx, l, r);  // Case 3: pehle pending apply karo
        int m = (l + r) / 2;
        update(2 * idx + 1, l, m, ql, qr, val);
        update(2 * idx + 2, m + 1, r, ql, qr, val);
        tree[idx] = tree[2 * idx + 1] + tree[2 * idx + 2];
    }

    // ── query: range [ql,qr] ka sum nikalo ──
    //   1) Case 1 NO overlap → 0 return (sum identity)
    //   2) Case 2 FULL overlap → seedha tree[idx] return (sara segment andar hai)
    //   3) Case 3 PARTIAL → pushDown karke dono bachho ka sum jodo
    ll query(int idx, int l, int r, int ql, int qr)
    {
        if (qr < l || r < ql)  // Case 1
            return 0;
        if (ql <= l && r <= qr)  // Case 2
            return tree[idx];
        pushDown(idx, l, r);  // Case 3: query se pehle pending apply
        int m = (l + r) / 2;
        return query(2 * idx + 1, l, m, ql, qr) +
               query(2 * idx + 2, m + 1, r, ql, qr);
    }

public:
    // ── LazySegTree: constructor — sum tree + lazy array banao ──
    //   1) n = arr.size(), tree aur lazy dono 4*n size allocate
    //   2) Root se build() call — initial array values tree me daal do
    LazySegTree(vector<int> &arr)
    {
        n = arr.size();
        tree.resize(4 * n);
        lazy.resize(4 * n);
        build(arr, 0, 0, n - 1);
    }

    // Public wrappers: bahar se [l,r] range update/query, root khud set
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
    vector<vector<int>> adj;          // undirected tree
    vector<int> in_time, out_time;    // har node ka entry/exit timestamp
    int timer = 0;                    // global counter

    // ── EulerTour: constructor — n nodes ka tree structure init ──
    //   1) n store karo, adj list n size ki banao
    //   2) in_time, out_time vectors n size ke allocate karo
    //   3) timer = 0 (global counter, har visit pe badhega)
    EulerTour(int n) : n(n), adj(n), in_time(n), out_time(n) {}

    // ── addEdge: undirected edge u-v add karo ──
    //   1) adj[u] me v push karo (u se v ja sakte hain)
    //   2) adj[v] me u push karo (undirected hai — dono taraf)
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // ── dfs: Euler timestamps bharto — subtree ko flat range banao ──
    //   1) in_time[u] = timer++ → u enter hua, entry timestamp assign
    //   2) Har child v (parent ko chhod ke) me recursively dfs karo
    //   3) Sab children ke baad out_time[u] = timer-1 → subtree ka last index
    //   4) Result: u ka poora subtree flat array me [in_time[u], out_time[u]] hai
    void dfs(int u, int par)
    {
        in_time[u] = timer++;
        for (int v : adj[u])
            if (v != par)  // parent pe wapas mat jao (cycle avoid)
                dfs(v, u);
        out_time[u] = timer - 1;
    }

    // ── build: root se Euler tour shuru karo ──
    //   1) timer reset implicitly 0 se (pehli build ke liye)
    //   2) dfs(root, -1) call — parent=-1 kyunki root ka koi parent nahi
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