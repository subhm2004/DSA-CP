// All Segment Tree Variations
#include <bits/stdc++.h>
using namespace std;

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

    // segment tree build karne ka function
    void build(vector<int> &arr, int idx, int l, int r)
    {
        // agar leaf node hai toh direct value assign karo
        if (l == r)
        {
            tree[idx] = arr[l];
            return;
        }
        int m = (l + r) / 2;
        // left subtree build karo
        build(arr, 2 * idx + 1, l, m);
        // right subtree build karo
        build(arr, 2 * idx + 2, m + 1, r);
        // parent node me dono ka sum rakho
        tree[idx] = tree[2 * idx + 1] + tree[2 * idx + 2];
    }

    // kisi ek index par value update karne ka function
    void update(int idx, int l, int r, int pos, int val)
    {
        // agar leaf node hai toh value update karo
        if (l == r)
        {
            tree[idx] = val;
            return;
        }
        int m = (l + r) / 2;
        // jis side pos hai usi side update karo
        if (pos <= m)
            update(2 * idx + 1, l, m, pos, val);
        else
            update(2 * idx + 2, m + 1, r, pos, val);
        // parent node ka sum update karo
        tree[idx] = tree[2 * idx + 1] + tree[2 * idx + 2];
    }

    // range sum query ka function
    int query(int idx, int l, int r, int ql, int qr)
    {
        // agar query range se bahar hai toh 0 return karo
        if (qr < l || r < ql)
            return 0;
        // agar pura overlap hai toh value return karo
        if (ql <= l && r <= qr)
            return tree[idx];
        int m = (l + r) / 2;
        // left aur right dono side query karo
        return query(2 * idx + 1, l, m, ql, qr) + query(2 * idx + 2, m + 1, r, ql, qr);
    }

public:
    // constructor: tree build karo
    SegmentTree1(vector<int> &arr)
    {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 0, 0, n - 1);
    }
    // public update function
    void update(int pos, int val) { update(0, 0, n - 1, pos, val); }
    // public query function
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

    // lazy propagation ka push function
    void push(int idx, int l, int r)
    {
        // agar lazy value hai toh usko propagate karo
        if (lazy[idx])
        {
            tree[idx] += (r - l + 1) * lazy[idx]; // current segment me value add karo
            if (l != r)
            {
                // agar leaf nahi hai toh children me lazy value bhejo
                lazy[2 * idx + 1] += lazy[idx];
                lazy[2 * idx + 2] += lazy[idx];
            }
            lazy[idx] = 0; // apni lazy value clear karo
        }
    }

    // range update function
    void updateRange(int idx, int l, int r, int ql, int qr, int val)
    {
        push(idx, l, r); // pehle lazy propagate karo
        // agar overlap nahi hai toh kuch mat karo
        if (qr < l || r < ql)
            return;
        // agar pura overlap hai toh lazy value add karo aur propagate karo
        if (ql <= l && r <= qr)
        {
            lazy[idx] += val;
            push(idx, l, r);
            return;
        }
        int m = (l + r) / 2;
        // left aur right dono side update karo
        updateRange(2 * idx + 1, l, m, ql, qr, val);
        updateRange(2 * idx + 2, m + 1, r, ql, qr, val);
        // parent node ka sum update karo
        tree[idx] = tree[2 * idx + 1] + tree[2 * idx + 2];
    }

    // point query function
    int pointQuery(int idx, int l, int r, int pos)
    {
        push(idx, l, r); // lazy propagate karo
        if (l == r)
            return tree[idx];
        int m = (l + r) / 2;
        // jis side pos hai usi side query karo
        return (pos <= m) ? pointQuery(2 * idx + 1, l, m, pos) : pointQuery(2 * idx + 2, m + 1, r, pos);
    }

public:
    // constructor: tree aur lazy array initialize karo
    SegmentTree2(int size)
    {
        n = size;
        tree.resize(4 * n);
        lazy.resize(4 * n);
    }
    // public range update
    void update(int l, int r, int val) { updateRange(0, 0, n - 1, l, r, val); }
    // public point query
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

    // lazy propagation ka function
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

    // range update function
    void updateRange(int idx, int l, int r, int ql, int qr, int val)
    {
        push(idx, l, r);
        if (qr < l || r < ql)
            return;
        if (ql <= l && r <= qr)
        {
            lazy[idx] += val;
            push(idx, l, r);
            return;
        }
        int m = (l + r) / 2;
        updateRange(2 * idx + 1, l, m, ql, qr, val);
        updateRange(2 * idx + 2, m + 1, r, ql, qr, val);
        tree[idx] = tree[2 * idx + 1] + tree[2 * idx + 2];
    }

    // range sum query function
    int rangeQuery(int idx, int l, int r, int ql, int qr)
    {
        push(idx, l, r);
        if (qr < l || r < ql)
            return 0;
        if (ql <= l && r <= qr)
            return tree[idx];
        int m = (l + r) / 2;
        return rangeQuery(2 * idx + 1, l, m, ql, qr) + rangeQuery(2 * idx + 2, m + 1, r, ql, qr);
    }

public:
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
struct Node
{
    int val;            // is segment ka sum
    Node *left, *right; // left aur right child
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
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
    // tree build karne ka function
    Node *build(vector<int> &arr, int l, int r)
    {
        if (l == r)
            return new Node(arr[l]);
        int m = (l + r) / 2;
        return new Node(build(arr, l, m), build(arr, m + 1, r));
    }
    // update karne par naya node banta hai (purana safe rehta hai)
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
    // range sum query
    int query(Node *node, int l, int r, int ql, int qr)
    {
        if (qr < l || r < ql)
            return 0;
        if (ql <= l && r <= qr)
            return node->val;
        int m = (l + r) / 2;
        return query(node->left, l, m, ql, qr) + query(node->right, m + 1, r, ql, qr);
    }

public:
    vector<Node *> versions; // har version ka root yahan store hota hai
    PersistentSegmentTree(vector<int> &arr)
    {
        n = arr.size();
        versions.push_back(build(arr, 0, n - 1));
    }
    // naya version banao
    void updateVersion(int version, int pos, int val)
    {
        versions.push_back(update(versions[version], 0, n - 1, pos, val));
    }
    // kisi version par query karo
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
    // binary search style me index find karo
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
    SegmentTreeBinarySearch(vector<int> &arr)
    {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 0, 0, n - 1);
    }
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

    // do nodes ko merge karne ka function
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

    // tree build karne ka function
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

    // lazy propagation jaisa push function
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

    // range min update function
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

    // tree build karne ka function
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
        // left aur right ko merge karke sorted array banao
        merge(tree[2 * idx + 1].begin(), tree[2 * idx + 1].end(),
              tree[2 * idx + 2].begin(), tree[2 * idx + 2].end(),
              back_inserter(tree[idx]));
    }

    // range me x se kam kitne hain wo count karo
    int query(int idx, int l, int r, int ql, int qr, int x)
    {
        if (qr < l || r < ql)
            return 0;
        if (ql <= l && r <= qr)
            return lower_bound(tree[idx].begin(), tree[idx].end(), x) - tree[idx].begin();
        int m = (l + r) / 2;
        return query(2 * idx + 1, l, m, ql, qr, x) +
               query(2 * idx + 2, m + 1, r, ql, qr, x);
    }

public:
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

    // y direction me build karo
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

    // x direction me build karo
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

    // tree build karne ka function
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

    // kisi character ki frequency query karo
    int query(int idx, int l, int r, int ql, int qr, int c)
    {
        if (qr < l || r < ql)
            return 0;
        if (ql <= l && r <= qr)
            return tree[idx][c];
        int m = (l + r) / 2;
        return query(2 * idx + 1, l, m, ql, qr, c) + query(2 * idx + 2, m + 1, r, ql, qr, c);
    }

public:
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

    // tree build karne ka function
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

    // range XOR query function
    int query(int idx, int l, int r, int ql, int qr)
    {
        if (qr < l || r < ql)
            return 0;
        if (ql <= l && r <= qr)
            return tree[idx];
        int m = (l + r) / 2;
        return query(2 * idx + 1, l, m, ql, qr) ^ query(2 * idx + 2, m + 1, r, ql, qr);
    }

public:
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
