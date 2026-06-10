#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// EULER TOUR + SEGMENT TREE
// ────────────────────────────────────────────────────────────────────────────
// Idea: ek TREE (graph) pe subtree queries karni hain (jaise "node X ke poore
// subtree ki value ka sum"). Direct tree pe ye mushkil hai, isliye:
//   1) Euler Tour karke har node ko ek flat array me ek RANGE [in_time, out_time]
//      assign kar dete hain. Kisi node ka poora subtree us range me aa jaata hai.
//   2) Phir us flat array pe normal Segment Tree laga dete hain.
//      Ab "subtree sum" = "flat array ke [in_time, out_time] ka range sum".
//
// Segment tree ke recursive params (sabhi functions me common):
//   idx -> tree array me current node ka index (root = 0,
//          left child = 2*idx+1, right child = 2*idx+2)
//   l,r -> current node jis segment ka maalik hai uska [l, r] (actual array index)
//   ql,qr / pos -> query/update ki range ya position
// ════════════════════════════════════════════════════════════════════════════

// ============================================================
// SEGMENT TREE  (simple range-SUM tree, point update)
// ============================================================
class SegmentTree
{
    vector<int> tree;  // har node pe uske segment ka SUM
    int n;

    // ── build: arr se sum segment tree bottom-up banao ──
    //   1) Base case l==r → leaf hai, tree[idx] = arr[l] set karo
    //   2) mid = (l+r)/2 se segment ko left [l,m] aur right [m+1,r] me todo
    //   3) Dono bachho ko recursively build karo
    //   4) Parent ka sum = left child sum + right child sum
    void build(vector<int> &arr, int idx, int l, int r)
    {
        if (l == r) { tree[idx] = arr[l]; return; }  // leaf node
        int m = (l + r) / 2;
        build(arr, 2*idx+1, l, m);      // left half [l, m]
        build(arr, 2*idx+2, m+1, r);    // right half [m+1, r]
        tree[idx] = tree[2*idx+1] + tree[2*idx+2];  // sum upar le aao
    }

    // ── update: position pos ki value val se replace karo ──
    //   1) pos <= mid hai to left child me jao, warna right me
    //   2) Leaf (l==r) pe pahunch ke tree[idx] = val set karo
    //   3) Wapsi aate waqt parent ka sum = left + right refresh karo
    //   4) Sirf root se pos tak ka path change hota hai — O(log n)
    void update(int idx, int l, int r, int pos, int val)
    {
        if (l == r) { tree[idx] = val; return; }  // leaf mil gaya
        int m = (l + r) / 2;
        if (pos <= m) update(2*idx+1, l, m, pos, val);    // pos left me hai
        else          update(2*idx+2, m+1, r, pos, val);  // pos right me hai
        tree[idx] = tree[2*idx+1] + tree[2*idx+2];  // parent ka sum refresh
    }

    // ── query: range [ql,qr] ka sum nikalo ──
    //   1) Case 1 NO overlap (qr<l || r<ql) → 0 return (sum identity)
    //   2) Case 2 FULL overlap (ql<=l && r<=qr) → seedha tree[idx] return
    //   3) Case 3 PARTIAL → mid se todo, dono bachho ka sum jod ke return
    int query(int idx, int l, int r, int ql, int qr)
    {
        if (qr < l || r < ql) return 0;             // Case 1: no overlap
        if (ql <= l && r <= qr) return tree[idx];   // Case 2: full overlap
        int m = (l + r) / 2;                        // Case 3: partial
        return query(2*idx+1, l, m, ql, qr) + query(2*idx+2, m+1, r, ql, qr);
    }

public:
    // ── SegmentTree: constructor — 4*n size tree allocate + build ──
    //   1) n = arr.size(), tree vector 4*n size resize (safe upper bound)
    //   2) Root idx=0 se poori array [0, n-1] par build() call karo
    SegmentTree(vector<int> &arr)
    {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 0, 0, n-1);
    }

    // Public wrappers: bahar se call karo, idx/l/r khud root se set ho jaata hai
    void update(int pos, int val) { update(0, 0, n-1, pos, val); }  // pos pe val set
    int  query(int l, int r)      { return query(0, 0, n-1, l, r); } // [l,r] ka sum
};

// ============================================================
// EULER TOUR
// ────────────────────────────────────────────────────────────
// Tree ko ek flat array me badalne ka tarika. DFS ke time pe har
// node ko do timestamp dete hain:
//   in_time[u]  -> jab DFS me node u pehli baar visit hua
//   out_time[u] -> u ke subtree ka last node kab visit hua
// Khaas baat: u ka POORA subtree flat array me ek continuous range
// [in_time[u], out_time[u]] ban jaata hai. Isi liye subtree query ko
// hum range query me convert kar paate hain.
// ============================================================
class EulerTour
{
public:
    int n;
    vector<vector<int>> adj;          // adjacency list (undirected tree)
    vector<int> in_time, out_time;    // har node ka entry/exit timestamp
    int timer = 0;                    // global counter, har visit pe badhta hai

    // ── EulerTour: constructor — n nodes ka tree init ──
    //   1) n store, adj list n size ki banao
    //   2) in_time, out_time vectors allocate karo
    //   3) timer = 0 (global counter, har DFS visit pe badhega)
    EulerTour(int n) : n(n), adj(n), in_time(n), out_time(n) {}

    // ── addEdge: undirected edge u-v add karo ──
    //   1) adj[u] me v push karo
    //   2) adj[v] me u push karo (tree undirected hai)
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // ── dfs: timestamps bharto — subtree ko continuous range banao ──
    //   1) in_time[u] = timer++ → u enter hua, entry timestamp assign
    //   2) Har child v (parent ko chhod ke) me recursively dfs karo
    //   3) Sab children ke baad out_time[u] = timer-1 → subtree ka last index
    //   4) Result: u ka poora subtree flat array me [in_time[u], out_time[u]] hai
    void dfs(int u, int parent)
    {
        in_time[u] = timer++;                   // u ka entry time, phir counter++
        for (int v : adj[u])
            if (v != parent) dfs(v, u);         // har child me jao (parent chhodo)
        out_time[u] = timer - 1;                // subtree khatam -> last seen time
    }

    // ── build: root se Euler tour shuru karo ──
    //   1) dfs(root, -1) call karo — parent=-1 kyunki root ka koi parent nahi
    //   2) Poori tree ke in_time/out_time timestamps set ho jaate hain
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
    // Har node ki value ko uske in_time wale position pe rakho.
    // Yani flat[in_time[node]] = node ki value. Ab tree ka data
    // ek 1D array ban gaya jispe segment tree laga sakte hain.
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
        // node ka subtree = flat array ka [in_time, out_time] range -> range sum
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
        // node ki value flat array me in_time wale position pe hai -> point update
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
