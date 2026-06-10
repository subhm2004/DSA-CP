// All Segment Tree Variations
#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// COMMON PARAMS (saari recursive functions me ye baar baar aate hain) — ek baar samajh le:
//
//   idx -> tree array me current node ka index (root = 0)
//          left child  = 2*idx + 1
//          right child = 2*idx + 2
//   l   -> current node jis segment ka maalik hai uska LEFT  end (actual array index)
//   r   -> current node jis segment ka maalik hai uska RIGHT end (actual array index)
//          matlab ye node array ke [l, r] hisse ko represent karta hai
//   ql  -> QUERY/UPDATE ka left end  (user ne jo range maangi uska start)
//   qr  -> QUERY/UPDATE ka right end (user ne jo range maangi uska end)
//   pos -> point update/query me jis single index pe kaam karna hai wo
//   m   -> mid = (l + r) / 2  -> [l, r] ko do halves me todne wala point
//
// Har recursion me node [l, r] vs query [ql, qr] ke 3 case hote hain:
//   1) NO overlap   -> node poori tarah query ke bahar (qr < l || r < ql) -> identity return
//   2) FULL overlap -> node poori tarah query ke andar (ql <= l && r <= qr) -> seedha node ki value
//   3) PARTIAL      -> thoda andar thoda bahar -> dono bachho me recurse karke combine karo
// ════════════════════════════════════════════════════════════════════════════

// ========================== Variation 1 ===========================
/*
    SegmentTree1:
    Purpose: Point Update & Range Query (Sum)
    Kab use kare: Jab aapko array ke kisi ek index par value update karni ho aur kisi bhi range ka sum nikalna ho.
    Example: Array me kisi ek element ko change karna aur fir kisi bhi subarray ka sum puchhna.
    Complexity: Build O(n), Update O(log n), Query O(log n)
    Note: Ye basic segment tree hai, bina lazy propagation ke.
*/
class SegmentTree1
{
    vector<int> tree; // segment tree ka array
    int n;            // original array ka size

    // ── build: array se sum segment tree bottom-up banao ──
    //   1) Base case l==r → leaf hai, tree[idx] = arr[l] set karo
    //   2) mid se segment ko left [l,m] aur right [m+1,r] me todo
    //   3) Dono bachho ko recursively build karo
    //   4) Parent ka sum = left child sum + right child sum
    void build(vector<int> &arr, int idx, int l, int r)
    {
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

    // ── update: position pos ki value val se replace karo ──
    //   1) pos <= mid hai to left child me jao, warna right me
    //   2) Leaf (l==r) pe pahunch ke tree[idx] = val set karo
    //   3) Wapsi pe har ancestor ka sum = left + right refresh karo
    void update(int idx, int l, int r, int pos, int val)
    {
        if (l == r)
        {
            tree[idx] = val;
            return;
        }
        int m = (l + r) / 2;
        if (pos <= m)
            update(2 * idx + 1, l, m, pos, val);
        else
            update(2 * idx + 2, m + 1, r, pos, val);
        tree[idx] = tree[2 * idx + 1] + tree[2 * idx + 2];
    }

    // ── query: range [ql,qr] ka sum nikalo ──
    //   1) Case 1 NO overlap (qr<l || r<ql) → 0 return (sum identity)
    //   2) Case 2 FULL overlap (ql<=l && r<=qr) → seedha tree[idx] return
    //   3) Case 3 PARTIAL → dono bachho ka sum jod ke return
    int query(int idx, int l, int r, int ql, int qr)
    {
        if (qr < l || r < ql)  // Case 1
            return 0;
        if (ql <= l && r <= qr)  // Case 2
            return tree[idx];
        int m = (l + r) / 2;  // Case 3
        return query(2 * idx + 1, l, m, ql, qr) + query(2 * idx + 2, m + 1, r, ql, qr);
    }

public:
    // ── SegmentTree1: constructor — point update + range sum tree ──
    //   1) n = arr.size(), tree vector 4*n size allocate
    //   2) Root idx=0 se poori array [0, n-1] par build() call karo
    SegmentTree1(vector<int> &arr)
    {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 0, 0, n - 1);
    }
    void update(int pos, int val) { update(0, 0, n - 1, pos, val); }
    int query(int l, int r) { return query(0, 0, n - 1, l, r); }
};

// ========================== Variation 2 ===========================
/*
    SegmentTree2:
    Purpose: Range Update & Point Query (Lazy Propagation)
    Kab use kare: Jab aapko kisi range me ek value add karni ho (ya increment karna ho) aur kisi ek index ka value puchhna ho.
    Example: Range [l, r] me sabhi elements ko +5 kar do, fir index i ka value kya hai?
    Complexity: Update O(log n), Query O(log n)
    Note: Lazy propagation ki wajah se range update fast hota hai.
*/
class SegmentTree2
{
    vector<int> tree, lazy; // tree aur lazy array
    int n;

    // ── push: pending lazy ko apply karo aur bachho tak pass karo ──
    //   1) Agar lazy[idx]==0 hai to kuch nahi — implicitly skip
    //   2) tree[idx] me lazy * (r-l+1) add karo — poore segment me apply
    //   3) Leaf nahi hai to lazy dono bachho ke lazy me += lazy[idx]
    //   4) Apna lazy clear karo — ab pending apply ho chuka hai
    void push(int idx, int l, int r)
    {
        if (lazy[idx])
        {
            tree[idx] += (r - l + 1) * lazy[idx];
            if (l != r)
            {
                lazy[2 * idx + 1] += lazy[idx];
                lazy[2 * idx + 2] += lazy[idx];
            }
            lazy[idx] = 0;
        }
    }

    // ── updateRange: range [ql,qr] ke har element me val add karo ──
    //   1) Pehle push() — current node ka pending lazy apply karo
    //   2) Case 1 NO overlap → return. Case 2 FULL → lazy lagao + push
    //   3) Case 3 PARTIAL → dono bachho me recurse karo
    //   4) Wapsi pe tree[idx] = left sum + right sum refresh (point query variant me optional)
    void updateRange(int idx, int l, int r, int ql, int qr, int val)
    {
        push(idx, l, r);
        if (qr < l || r < ql)  // Case 1
            return;
        if (ql <= l && r <= qr)  // Case 2: full overlap
        {
            lazy[idx] += val;
            push(idx, l, r);
            return;
        }
        int m = (l + r) / 2;  // Case 3
        updateRange(2 * idx + 1, l, m, ql, qr, val);
        updateRange(2 * idx + 2, m + 1, r, ql, qr, val);
        tree[idx] = tree[2 * idx + 1] + tree[2 * idx + 2];
    }

    // ── pointQuery: index pos ki current value kya hai ──
    //   1) Raaste me har node pe push() — pending lazy apply hota rahe
    //   2) pos <= mid → left child, warna right child me jao
    //   3) Leaf (l==r) pe pahunch ke tree[idx] return — yahi final value hai
    int pointQuery(int idx, int l, int r, int pos)
    {
        push(idx, l, r);
        if (l == r)
            return tree[idx];
        int m = (l + r) / 2;
        return (pos <= m) ? pointQuery(2 * idx + 1, l, m, pos) : pointQuery(2 * idx + 2, m + 1, r, pos);
    }

public:
    // ── SegmentTree2: constructor — range update + point query tree ──
    //   1) n = size store, tree aur lazy dono 4*n size allocate
    //   2) Lazy 0 se init — shuru me koi pending add nahi (empty tree)
    SegmentTree2(int size)
    {
        n = size;
        tree.resize(4 * n);
        lazy.resize(4 * n);
    }
    void update(int l, int r, int val) { updateRange(0, 0, n - 1, l, r, val); }
    int query(int pos) { return pointQuery(0, 0, n - 1, pos); }
};

// ========================== Variation 3 ===========================
/*
    SegmentTree3:
    Purpose: Range Update & Range Query (Lazy Propagation)
    Kab use kare: Jab aapko kisi range me value add karni ho aur kisi bhi range ka sum nikalna ho.
    Example: Range [l, r] me sabhi elements ko +x kar do, fir kisi bhi range ka sum puchho.
    Complexity: Update O(log n), Query O(log n)
    Note: Lazy propagation dono operation ko efficient banata hai.
*/
class SegmentTree3
{
    vector<int> tree, lazy;
    int n;

    // ── push: pending lazy apply karo aur bachho tak pass karo ──
    //   1) lazy[idx]!=0 ho to tree[idx] me lazy*(segment size) add karo
    //   2) Leaf nahi hai to lazy dono bachho ke lazy me += lazy[idx]
    //   3) Apna lazy 0 kar do — pending ab apply ho chuka hai
    void push(int idx, int l, int r)
    {
        if (lazy[idx])
        {
            tree[idx] += (r - l + 1) * lazy[idx];
            if (l != r)
            {
                lazy[2 * idx + 1] += lazy[idx];
                lazy[2 * idx + 2] += lazy[idx];
            }
            lazy[idx] = 0;
        }
    }

    // ── updateRange: range [ql,qr] me val add karo ──
    //   1) push() se pehle pending clear karo
    //   2) Case 1 NO overlap → return. Case 2 FULL → lazy += val, push
    //   3) Case 3 PARTIAL → dono bachho me recurse
    //   4) Wapsi pe parent sum refresh — range query ke liye zaroori hai
    void updateRange(int idx, int l, int r, int ql, int qr, int val)
    {
        push(idx, l, r);
        if (qr < l || r < ql)  // Case 1
            return;
        if (ql <= l && r <= qr)  // Case 2
        {
            lazy[idx] += val;
            push(idx, l, r);
            return;
        }
        int m = (l + r) / 2;  // Case 3
        updateRange(2 * idx + 1, l, m, ql, qr, val);
        updateRange(2 * idx + 2, m + 1, r, ql, qr, val);
        tree[idx] = tree[2 * idx + 1] + tree[2 * idx + 2];
    }

    // ── rangeQuery: range [ql,qr] ka sum nikalo ──
    //   1) push() se current node ki value sahi karo
    //   2) Case 1 NO overlap → 0. Case 2 FULL → tree[idx]
    //   3) Case 3 PARTIAL → dono bachho ka sum jodo
    int rangeQuery(int idx, int l, int r, int ql, int qr)
    {
        push(idx, l, r);
        if (qr < l || r < ql)  // Case 1
            return 0;
        if (ql <= l && r <= qr)  // Case 2
            return tree[idx];
        int m = (l + r) / 2;  // Case 3
        return rangeQuery(2 * idx + 1, l, m, ql, qr) + rangeQuery(2 * idx + 2, m + 1, r, ql, qr);
    }

public:
    // ── SegmentTree3: constructor — range update + range sum tree ──
    //   1) n = size, tree aur lazy 4*n size allocate
    //   2) Lazy 0 init — empty tree, baad me range updates se bharega
    SegmentTree3(int size)
    {
        n = size;
        tree.resize(4 * n);
        lazy.resize(4 * n);
    }
    void update(int l, int r, int val) { updateRange(0, 0, n - 1, l, r, val); }
    int query(int l, int r) { return rangeQuery(0, 0, n - 1, l, r); }
};

// ========================== Variation 4 ===========================
/*
    PersistentSegmentTree:
    Purpose: Persistent Segment Tree (Har update ke baad purana version safe rehta hai)
    Kab use kare: Jab aapko array ke purane versions par bhi query karni ho, ya undo/rollback type ka kaam ho.
    Example: Har update ke baad ek naya version banta hai, kisi bhi version par query kar sakte ho.
    Complexity: Build O(n), Update O(log n) (per version), Query O(log n)
    Note: Memory thoda jyada lagta hai, lekin har update ke liye purana data safe rehta hai.
*/
// Yaha array-based (2*idx+1) ke bajaye POINTER-based nodes use hote hain,
// kyunki har update pe sirf raaste ke O(log n) naye nodes bante hain aur
// baaki purane nodes share ho jaate hain (isi se purana version safe rehta hai).
struct Node
{
    int val;
    Node *left, *right;
    // ── Node (leaf): ek element ki value store karo ──
    //   1) val = v set karo, left/right nullptr (leaf ke koi bacche nahi)
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
    // ── Node (internal): do bachho se parent banao ──
    //   1) left aur right pointers set karo
    //   2) val = left->val + right->val (sum merge)
    //   3) nullptr child ho to skip (safe guard)
    Node(Node *l, Node *r) : left(l), right(r), val(0)
    {
        if (l)
            val += l->val;
        if (r)
            val += r->val;
    }
};
class PersistentSegmentTree
{
    int n;
    // ── build: version 0 ka poora tree recursively banao ──
    //   1) Base case l==r → naya leaf Node(arr[l]) return
    //   2) mid se segment ko do halves me todo
    //   3) Left aur right subtree recursively build karo
    //   4) Naya internal Node(left, right) return — sum auto-merge
    Node *build(vector<int> &arr, int l, int r)
    {
        if (l == r)
            return new Node(arr[l]);
        int m = (l + r) / 2;
        return new Node(build(arr, l, m), build(arr, m + 1, r));
    }
    // ── update: path-copy se naya node chain banao ──
    //   1) Leaf (l==r) → bilkul naya Node(val), purana leaf reuse nahi
    //   2) pos left me → naya left banao, right PURANA node->right reuse
    //   3) pos right me → left PURANA reuse, naya right banao
    //   4) Sirf O(log n) naye nodes — baaki purane subtrees share hote hain
    Node *update(Node *node, int l, int r, int pos, int val)
    {
        if (l == r)
            return new Node(val);
        int m = (l + r) / 2;
        if (pos <= m)
            return new Node(update(node->left, l, m, pos, val), node->right);
        else
            return new Node(node->left, update(node->right, m + 1, r, pos, val));
    }
    // ── query: kisi version ke root se range [ql,qr] ka sum ──
    //   1) Case 1 NO overlap (qr<l || r<ql) → 0 return
    //   2) Case 2 FULL overlap (ql<=l && r<=qr) → node->val return
    //   3) Case 3 PARTIAL → left sum + right sum combine
    int query(Node *node, int l, int r, int ql, int qr)
    {
        if (qr < l || r < ql)  // Case 1
            return 0;
        if (ql <= l && r <= qr)  // Case 2
            return node->val;
        int m = (l + r) / 2;  // Case 3
        return query(node->left, l, m, ql, qr) + query(node->right, m + 1, r, ql, qr);
    }

public:
    vector<Node *> versions;
    // ── PersistentSegmentTree: constructor — version 0 banao ──
    //   1) n = arr.size() store karo
    //   2) build() se original array ka tree banao
    //   3) versions[0] = us tree ka root pointer
    PersistentSegmentTree(vector<int> &arr)
    {
        n = arr.size();
        versions.push_back(build(arr, 0, n - 1));
    }
    // ── updateVersion: base version se naya version banao ──
    //   1) versions[version] ka root lo
    //   2) update() se path-copy karke naya root banao
    //   3) Naya root versions me push — purana version safe rehta hai
    void updateVersion(int version, int pos, int val)
    {
        versions.push_back(update(versions[version], 0, n - 1, pos, val));
    }
    // ── query: kisi version par range [l,r] ka sum ──
    int query(int version, int l, int r)
    {
        return query(versions[version], 0, n - 1, l, r);
    }
};

// ========================== Variation 5 ===========================
/*
    SegmentTreeBinarySearch:
    Purpose: Segment Tree with Binary Search (Prefix sum >= x ka pehla index)
    Kab use kare: Jab aapko array ke prefix sum par binary search karna ho, ya kisi threshold tak pahunchne ka index chahiye.
    Example: Array ke prefix sum me pehla index jahan sum >= x ho.
    Complexity: Build O(n), Query O(log n)
    Note: Useful for order statistics, lower_bound type queries.
*/
class SegmentTreeBinarySearch
{
    vector<int> tree;
    int n;
    // ── build: prefix-sum segment tree bottom-up banao ──
    //   1) Leaf pe tree[idx] = arr[l]
    //   2) Internal pe left + right child ka sum parent me store
    //   3) Poori array [0, n-1] par recursively build
    void build(vector<int> &arr, int idx, int l, int r)
    {
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
    // ── find: pehla index jahan prefix sum >= x ho ──
    //   1) Agar is segment ka sum < x → -1 (yaha answer nahi milega)
    //   2) Leaf pe pahunch → yahi wo index hai, return l
    //   3) Left child ka sum >= x → answer left me hai, left me jao
    //   4) Warna left poora kha lo, bachi requirement (x - leftSum) right me dhoondo
    int find(int idx, int l, int r, int x)
    {
        if (tree[idx] < x)
            return -1;
        if (l == r)
            return l;
        int m = (l + r) / 2;
        if (tree[2 * idx + 1] >= x)
            return find(2 * idx + 1, l, m, x);
        return find(2 * idx + 2, m + 1, r, x - tree[2 * idx + 1]);
    }

public:
    // ── SegmentTreeBinarySearch: constructor — prefix tree build ──
    SegmentTreeBinarySearch(vector<int> &arr)
    {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 0, 0, n - 1);
    }
    // Wrapper: pehla index jahan prefix sum >= x
    int findPrefixGE(int x) { return find(0, 0, n - 1, x); }
};

// ========================== Variation 6 ===========================
/*
    SegmentTreeBeats:
    Purpose: Segment Tree Beats (Conditional Min Update)
    Kab use kare: Jab aapko kisi range ke sabhi elements ko ek value se kam karna ho (agar wo value se jyada hain).
    Example: Range [l, r] me sabhi elements ko min(x, arr[i]) bana do.
    Complexity: Update O(log n) (amortized), Query O(log n)
    Note: Ye advanced segment tree hai, competitive programming me use hota hai.
*/
class SegmentTreeBeats
{
    struct Node
    {
        int max1 = 0, max2 = 0, cnt = 0, sum = 0; // max1: max value, max2: second max, cnt: max1 ki count, sum: segment ka sum
    };
    vector<Node> tree;
    int n;

    // ── merge: do child nodes ko parent me combine karo (Beats ke liye) ──
    //   1) sum = a.sum + b.sum (simple addition)
    //   2) Agar dono ka max1 same → count add, max2 = max of second maxes
    //   3) Agar a.max1 > b.max1 → max1=a, max2=max(a.max2, b.max1)
    //   4) Warna ulta — b ka max1 bada hai
    Node merge(Node a, Node b)
    {
        Node res;
        res.sum = a.sum + b.sum;
        if (a.max1 == b.max1)
        {
            res.max1 = a.max1;
            res.max2 = max(a.max2, b.max2);
            res.cnt = a.cnt + b.cnt;
        }
        else if (a.max1 > b.max1)
        {
            res.max1 = a.max1;
            res.max2 = max(a.max2, b.max1);
            res.cnt = a.cnt;
        }
        else
        {
            res.max1 = b.max1;
            res.max2 = max(a.max1, b.max2);
            res.cnt = b.cnt;
        }
        return res;
    }

    // ── build: array se Beats tree banao ──
    //   1) Leaf pe max1=arr[l], max2=-1, cnt=1, sum=arr[l]
    //   2) Internal pe dono bachho ko build karke merge() se parent banao
    void build(vector<int> &a, int idx, int l, int r)
    {
        if (l == r)
        {
            tree[idx] = {a[l], -1, 1, a[l]};
            return;
        }
        int m = (l + r) / 2;
        build(a, 2 * idx + 1, l, m);
        build(a, 2 * idx + 2, m + 1, r);
        tree[idx] = merge(tree[2 * idx + 1], tree[2 * idx + 2]);
    }

    // ── push: parent ka max cap bachho tak utaaro ──
    //   1) Dono bachho pe check karo — agar child.max1 > parent.max1
    //   2) Child ke max1 wale cnt elements ko parent.max1 pe cap karo
    //   3) Sum se (purana max1 - naya cap) * cnt ghatao
    //   4) Child.max1 = parent.max1 set karo
    void push(int idx, int l, int r)
    {
        for (int child : {2 * idx + 1, 2 * idx + 2})
        {
            if (tree[child].max1 > tree[idx].max1)
            {
                tree[child].sum -= (tree[child].max1 - tree[idx].max1) * tree[child].cnt;
                tree[child].max1 = tree[idx].max1;
            }
        }
    }

    // ── updateMin: range [ql,qr] ke har element ko min(element, x) banao ──
    //   1) BREAK: no overlap ya max1<=x (koi element x se bada nahi)
    //   2) TAG: full overlap + max2<x → sirf max1 wale ko x pe cap, O(1)
    //   3) Warna push + dono bachho me recurse + merge se parent refresh
    void updateMin(int idx, int l, int r, int ql, int qr, int x)
    {
        if (tree[idx].max1 <= x || qr < l || r < ql)
            return;
        if (ql <= l && r <= qr && tree[idx].max2 < x)
        {
            tree[idx].sum -= (tree[idx].max1 - x) * tree[idx].cnt;
            tree[idx].max1 = x;
            return;
        }
        int m = (l + r) / 2;
        push(idx, l, r);
        updateMin(2 * idx + 1, l, m, ql, qr, x);
        updateMin(2 * idx + 2, m + 1, r, ql, qr, x);
        tree[idx] = merge(tree[2 * idx + 1], tree[2 * idx + 2]);
    }

public:
    // ── SegmentTreeBeats: constructor — conditional min update tree ──
    SegmentTreeBeats(vector<int> &a)
    {
        n = a.size();
        tree.resize(4 * n);
        build(a, 0, 0, n - 1);
    }
    void rangeMinUpdate(int l, int r, int x)
    {
        updateMin(0, 0, n - 1, l, r, x);
    }
};

// ========================== Variation 7 ===========================
/*
    MergeSortTree:
    Purpose: Merge Sort Tree (Range me kisi value se kam kitne hain)
    Kab use kare: Jab aapko kisi range me x se kam ya x se jyada elements ki count chahiye ho.
    Example: Range [l, r] me kitne elements < x hain.
    Complexity: Build O(n log n), Query O(log^2 n)
    Note: Har segment me sorted array store hota hai.
*/
class MergeSortTree
{
    vector<vector<int>> tree;
    int n;

    // ── build: har segment me sorted array store karo ──
    //   1) Leaf pe tree[idx] = {a[l]} — ek element ka sorted array
    //   2) Internal pe dono bachho ko build karo
    //   3) merge() se dono sorted arrays ko jod ke ek sorted array banao
    //   4) Parent me ye merged sorted array store — O(n log n) total build
    void build(vector<int> &a, int idx, int l, int r)
    {
        if (l == r)
        {
            tree[idx] = {a[l]};
            return;
        }
        int m = (l + r) / 2;
        build(a, 2 * idx + 1, l, m);
        build(a, 2 * idx + 2, m + 1, r);
        merge(tree[2 * idx + 1].begin(), tree[2 * idx + 1].end(),
              tree[2 * idx + 2].begin(), tree[2 * idx + 2].end(),
              back_inserter(tree[idx]));
    }

    // ── query: range [ql,qr] me x se kam kitne elements ──
    //   1) Case 1 NO overlap → 0 return
    //   2) Case 2 FULL overlap → lower_bound se x ki position = count of < x
    //   3) Case 3 PARTIAL → dono bachho ki count jod ke return
    int query(int idx, int l, int r, int ql, int qr, int x)
    {
        if (qr < l || r < ql)  // Case 1
            return 0;
        if (ql <= l && r <= qr)  // Case 2: sorted array pe binary search
            return lower_bound(tree[idx].begin(), tree[idx].end(), x) - tree[idx].begin();
        int m = (l + r) / 2;  // Case 3
        return query(2 * idx + 1, l, m, ql, qr, x) +
               query(2 * idx + 2, m + 1, r, ql, qr, x);
    }

public:
    // ── MergeSortTree: constructor — sorted arrays wala seg tree ──
    MergeSortTree(vector<int> &a)
    {
        n = a.size();
        tree.resize(4 * n);
        build(a, 0, 0, n - 1);
    }
    int countLessThan(int l, int r, int x)
    {
        return query(0, 0, n - 1, l, r, x);
    }
};

// ========================== Variation 8 ===========================
/*
    SegmentTree2D:
    Purpose: 2D Segment Tree (Matrix ke liye range sum queries)
    Kab use kare: Jab aapko 2D matrix me kisi submatrix ka sum nikalna ho.
    Example: Matrix ke kisi rectangle region ka sum.
    Complexity: Build O(n*m*log n*log m), Query O(log n * log m)
    Note: 2D queries ke liye use hota hai, memory jyada lagti hai.
*/
class SegmentTree2D
{
    vector<vector<int>> tree;
    int n, m;

    // ── buildY: ek X-node ke andar column (Y) dimension pe tree banao ──
    //   1) Column leaf (ly==ry): X leaf ho to mat[lx][ly], warna X-bachho ka sum
    //   2) Column internal: do column-bachho ko build karke sum merge
    //   3) tree[idxX][idxY] me us column-segment ka sum store hota hai
    void buildY(int idxX, int idxY, int lx, int rx, int ly, int ry, vector<vector<int>> &mat)
    {
        if (ly == ry)
        {
            if (lx == rx)
                tree[idxX][idxY] = mat[lx][ly];
            else
                tree[idxX][idxY] = tree[2 * idxX + 1][idxY] + tree[2 * idxX + 2][idxY];
            return;
        }
        int my = (ly + ry) / 2;
        buildY(idxX, 2 * idxY + 1, lx, rx, ly, my, mat);
        buildY(idxX, 2 * idxY + 2, lx, rx, my + 1, ry, mat);
        tree[idxX][idxY] = tree[idxX][2 * idxY + 1] + tree[idxX][2 * idxY + 2];
    }

    // ── buildX: row (X) dimension pe outer tree banao ──
    //   1) X internal ho to pehle dono row-bachho ko recursively build karo
    //   2) Phir is X-node ke liye poori column range [0, m-1] par buildY chalao
    //   3) Har X-node ke paas ek poora nested Y-tree hota hai
    void buildX(int idxX, int lx, int rx, vector<vector<int>> &mat)
    {
        if (lx != rx)
        {
            int mx = (lx + rx) / 2;
            buildX(2 * idxX + 1, lx, mx, mat);
            buildX(2 * idxX + 2, mx + 1, rx, mat);
        }
        buildY(idxX, 0, lx, rx, 0, m - 1, mat);
    }

public:
    // ── SegmentTree2D: constructor — matrix se 2D seg tree banao ──
    //   1) n=rows, m=cols store karo
    //   2) tree = 4*n rows × 4*m cols ka 2D array allocate
    //   3) buildX(0, 0, n-1) se root se poora tree build karo
    SegmentTree2D(vector<vector<int>> &mat)
    {
        n = mat.size();
        m = mat[0].size();
        tree.assign(4 * n, vector<int>(4 * m));
        buildX(0, 0, n - 1, mat);
    }
    // Query function yahan nahi diya gaya, aap add kar sakte hain
};

// ========================== Variation 9 ===========================
/*
    SegmentTreeString:
    Purpose: Segment Tree for Strings (Character frequency in range)
    Kab use kare: Jab aapko string ke kisi range me kisi character ki frequency chahiye ho.
    Example: String ke range [l, r] me 'a' kitni baar aaya hai?
    Complexity: Build O(n), Query O(log n)
    Note: Har segment me 26 size ka array store hota hai (a-z).
*/
class SegmentTreeString
{
    vector<vector<int>> tree;
    int n;

    // ── build: string se char-frequency segment tree banao ──
    //   1) Leaf pe sirf s[l]-'a' wale slot me 1, baaki 26 slots 0
    //   2) Internal pe har char (0..25) ke liye left+right count jodo
    //   3) Har node ek 26-size frequency array hai
    void build(const string &s, int idx, int l, int r)
    {
        if (l == r)
        {
            tree[idx][s[l] - 'a'] = 1;
            return;
        }
        int m = (l + r) / 2;
        build(s, 2 * idx + 1, l, m);
        build(s, 2 * idx + 2, m + 1, r);
        for (int i = 0; i < 26; ++i)
            tree[idx][i] = tree[2 * idx + 1][i] + tree[2 * idx + 2][i];
    }

    // ── query: range [ql,qr] me character c ki frequency ──
    //   1) Case 1 NO overlap → 0 return
    //   2) Case 2 FULL overlap → seedha tree[idx][c] return
    //   3) Case 3 PARTIAL → dono bachho ki frequency jod ke return
    int query(int idx, int l, int r, int ql, int qr, int c)
    {
        if (qr < l || r < ql)  // Case 1
            return 0;
        if (ql <= l && r <= qr)  // Case 2
            return tree[idx][c];
        int m = (l + r) / 2;  // Case 3
        return query(2 * idx + 1, l, m, ql, qr, c) + query(2 * idx + 2, m + 1, r, ql, qr, c);
    }

public:
    // ── SegmentTreeString: constructor — char frequency tree ──
    SegmentTreeString(const string &s)
    {
        n = s.size();
        tree.assign(4 * n, vector<int>(26));
        build(s, 0, 0, n - 1);
    }
    int frequency(int l, int r, char ch)
    {
        return query(0, 0, n - 1, l, r, ch - 'a');
    }
};

// ========================== Variation 10 ===========================
/*
    SegmentTreeBitwise:
    Purpose: Bitwise Segment Tree (Range XOR queries)
    Kab use kare: Jab aapko array ke kisi range ka XOR nikalna ho.
    Example: Range [l, r] ka XOR.
    Complexity: Build O(n), Query O(log n)
    Note: XOR queries ke liye use hota hai, sum ki jagah XOR hota hai.
*/
class SegmentTreeBitwise
{
    vector<int> tree;
    int n;

    // ── build: array se XOR segment tree banao ──
    //   1) Leaf pe tree[idx] = a[l]
    //   2) Internal pe left XOR ^ right XOR parent me store
    //   3) XOR associative hai isliye range query me combine easy hai
    void build(vector<int> &a, int idx, int l, int r)
    {
        if (l == r)
        {
            tree[idx] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(a, 2 * idx + 1, l, m);
        build(a, 2 * idx + 2, m + 1, r);
        tree[idx] = tree[2 * idx + 1] ^ tree[2 * idx + 2];
    }

    // ── query: range [ql,qr] ka XOR nikalo ──
    //   1) Case 1 NO overlap → 0 return (XOR identity: x^0=x)
    //   2) Case 2 FULL overlap → seedha tree[idx] return
    //   3) Case 3 PARTIAL → left XOR ^ right XOR combine
    int query(int idx, int l, int r, int ql, int qr)
    {
        if (qr < l || r < ql)  // Case 1
            return 0;
        if (ql <= l && r <= qr)  // Case 2
            return tree[idx];
        int m = (l + r) / 2;  // Case 3
        return query(2 * idx + 1, l, m, ql, qr) ^ query(2 * idx + 2, m + 1, r, ql, qr);
    }

public:
    // ── SegmentTreeBitwise: constructor — XOR range query tree ──
    SegmentTreeBitwise(vector<int> &a)
    {
        n = a.size();
        tree.resize(4 * n);
        build(a, 0, 0, n - 1);
    }
    int rangeXOR(int l, int r)
    {
        return query(0, 0, n - 1, l, r);
    }
};

// ========================== Common Main Function ===========================
// Sabhi segment tree variations ka demo yahan diya gaya hai
int main()
{
    // Variation 1: Point Update & Range Query (Sum)
    vector<int> arr = {1, 2, 3, 4, 5};
    SegmentTree1 st1(arr);
    cout << "Sum [1,3]: " << st1.query(1, 3) << endl;              // 2+3+4 = 9
    st1.update(2, 10);                                             // arr[2] = 10
    cout << "Sum [1,3] after update: " << st1.query(1, 3) << endl; // 2+10+4 = 16

    // Variation 2: Range Update & Point Query (Lazy)
    SegmentTree2 st2(5);
    st2.update(1, 3, 5);                                 // [1,3] me 5 add karo
    cout << "Point Query [2]: " << st2.query(2) << endl; // 5

    // Variation 3: Range Update & Range Query (Lazy)
    SegmentTree3 st3(5);
    st3.update(0, 4, 2);                                    // sabhi me 2 add karo
    cout << "Range Sum [0,4]: " << st3.query(0, 4) << endl; // 10

    // Variation 4: Persistent Segment Tree
    vector<int> arr4 = {1, 2, 3, 4};
    PersistentSegmentTree pst(arr4);
    pst.updateVersion(0, 2, 10);                                      // version 1 ban gaya
    cout << "Sum [0,3] in version 0: " << pst.query(0, 0, 3) << endl; // 10
    cout << "Sum [0,3] in version 1: " << pst.query(1, 0, 3) << endl; // 1+2+10+4=17

    // Variation 5: Segment Tree with Binary Search
    vector<int> arr5 = {1, 2, 3, 4};
    SegmentTreeBinarySearch stbs(arr5);
    cout << "First prefix sum >= 6: " << stbs.findPrefixGE(6) << endl; // index 2

    // Variation 6: Segment Tree Beats (Conditional Min Update)
    vector<int> arr6 = {5, 3, 8, 6};
    SegmentTreeBeats stb(arr6);
    stb.rangeMinUpdate(0, 3, 4); // sabko max 4 tak le aao
    // No direct query, demo ke liye skip

    // Variation 7: Merge Sort Tree
    vector<int> arr7 = {1, 5, 2, 6, 3};
    MergeSortTree mst(arr7);
    cout << "Count < 4 in [0,4]: " << mst.countLessThan(0, 4, 4) << endl; // 3

    // Variation 8: 2D Segment Tree
    vector<vector<int>> mat = {{1, 2}, {3, 4}};
    SegmentTree2D st2d(mat);
    // No direct query, demo ke liye skip

    // Variation 9: Segment Tree for Strings
    string s = "abacaba";
    SegmentTreeString sts(s);
    cout << "Frequency of 'a' in [0,6]: " << sts.frequency(0, 6, 'a') << endl; // 4

    // Variation 10: Bitwise Segment Tree (XOR)
    vector<int> arr10 = {1, 2, 3, 4};
    SegmentTreeBitwise stbw(arr10);
    cout << "XOR [1,3]: " << stbw.rangeXOR(1, 3) << endl; // 2^3^4 = 5

    return 0;
}
