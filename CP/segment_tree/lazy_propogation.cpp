#include <bits/stdc++.h> // Segment tree with lazy propagation
// This code implements a segment tree with lazy propagation for range updates and point updates.
// It allows for efficient range sum queries and updates on an array.
// The segment tree is built from an initial array, and it supports operations to update a range by adding a value,
// update a specific index to a new value, and query the sum of elements in a given range.
// This code is designed to be efficient for large arrays and multiple queries, making it suitable for competitive programming and algorithmic challenges.
using namespace std;
using ll = long long;

// ════════════════════════════════════════════════════════════════════════════
// RANGE SUM SEGMENT TREE + LAZY PROPAGATION
// ────────────────────────────────────────────────────────────────────────────
// Lazy ka funda: agar poore range [start,end] me val add karna hai, to har
// element tak jaana mehnga hai. Isliye node pe ek "pending add" (lazy) yaad
// rakh lete hain. Jab tab us node ke andar jaana pade tabhi (push karke) wo
// pending value bachho tak pahunchate hain. Isse range update O(log n) ho jaata.
//
// Recursive params (sab functions me common):
//   i        -> tree array me current node ka index (root = 0,
//               left = 2*i+1, right = 2*i+2)
//   l, r     -> ye node jis segment ka maalik hai uska [l, r] (actual index)
//   start,end-> query/update ki range (user ne jo maangi)
// ════════════════════════════════════════════════════════════════════════════
class SegmentTree // Range Sum Segment Tree with Lazy Propagation
{
private:
    vector<ll> segTree; // stores sum in range  (har node pe uske segment ka sum)
    vector<ll> lazy;    // lazy propagation array (pending add jo abhi tak apply nahi hua)
    int n;

    // ── build: array se sum segment tree banao ──
    //   1) l==r pe leaf — segTree[i] = arr[l], seedha array value copy
    //   2) mid = (l+r)/2 se segment do halves me todo
    //   3) pehle left child [l,mid] build, phir right child [mid+1,r] build
    //   4) parent ka sum = left child sum + right child sum
    void build(const vector<int> &arr, int i, int l, int r)
    {
        if (l == r)  // leaf node — ek hi element, koi bachha nahi
        {
            segTree[i] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * i + 1, l, mid);       // left subtree [l, mid]
        build(arr, 2 * i + 2, mid + 1, r);   // right subtree [mid+1, r]
        segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];  // parent = bachho ka sum
    }

    // ── push: lazy propagation — pending add apply karo ──
    //   1) lazy[i] != 0 matlab is segment ke har element me 'lazy[i]' add pending hai
    //   2) segTree[i] += (r-l+1)*lazy[i] — kitne elements * kitna add = total sum badhega
    //   3) internal node ho to wahi lazy bachho ke lazy me += karo (abhi niche apply nahi)
    //   4) lazy[i] = 0 — is node ka pending clear, ab segTree[i] updated hai
    void push(int i, int l, int r)
    {
        if (lazy[i] != 0)
        {
            segTree[i] += (r - l + 1) * lazy[i];  // har element me lazy add → total sum itna badhega
            if (l != r)  // internal node — lazy niche defer karo
            {
                lazy[2 * i + 1] += lazy[i];
                lazy[2 * i + 2] += lazy[i];
            }
            lazy[i] = 0;  // pending apply ho gaya
        }
    }

    // ── update_Range: [start,end] me har element me val add karo ──
    //   1) push(i,l,r) — pehle purana pending apply karo
    //   2) Case 1 NO overlap (r<start || l>end) — return, kuch mat karo
    //   3) Case 2 FULL overlap — lazy[i]+=val, push turant, return (O(1) yahan)
    //   4) Case 3 PARTIAL — mid split, dono bachho recurse, parent sum refresh
    void update_Range(int i, int l, int r, int start, int end, int val) // Update range [start, end] by adding val
    {
        push(i, l, r);
        if (r < start || l > end)  // Case 1: NO overlap
            return;
        if (start <= l && r <= end)  // Case 2: FULL overlap — poora node update range ke andar
        {
            lazy[i] += val;           // pending me daalo, abhi har leaf tak nahi jaoge
            push(i, l, r);            // turant apply taaki segTree[i] query me sahi dikhe
            return;
        }
        int mid = (l + r) / 2;  // Case 3: PARTIAL overlap
        update_Range(2 * i + 1, l, mid, start, end, val);
        update_Range(2 * i + 2, mid + 1, r, start, end, val);
        segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];  // bachhe badle — parent sum refresh
    }

    // ── query_Range: [start,end] ka sum nikalo ──
    //   1) push pehle — warna lazy pending sum me count nahi hua hoga
    //   2) Case 1 NO overlap — 0 return (sum identity, merge me koi effect nahi)
    //   3) Case 2 FULL overlap — seedha segTree[i] return, aur recurse nahi
    //   4) Case 3 PARTIAL — left + right dono ka sum jod ke return karo
    ll query_Range(int i, int l, int r, int start, int end)
    {
        push(i, l, r);
        if (r < start || l > end)  // Case 1: NO overlap
            return 0;
        if (start <= l && r <= end)  // Case 2: FULL overlap
            return segTree[i];
        int mid = (l + r) / 2;  // Case 3: PARTIAL overlap
        return query_Range(2 * i + 1, l, mid, start, end) +
               query_Range(2 * i + 2, mid + 1, r, start, end);
    }

    // ── update_Index: point update — idx ki value replace karo ──
    //   1) har level pe push — raaste ka saara pending lazy clear ho
    //   2) l==r pe leaf — segTree[i] = new_val (overwrite, add nahi)
    //   3) idx <= mid ho to left child, warna right child me jao
    //   4) wapas aate waqt parent sum = left sum + right sum refresh karo
    void update_Index(int i, int l, int r, int idx, int new_val)
    {
        push(i, l, r);
        if (l == r)  // leaf mil gaya — yahi target index
        {
            segTree[i] = new_val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid)
            update_Index(2 * i + 1, l, mid, idx, new_val);    // idx left half me
        else
            update_Index(2 * i + 2, mid + 1, r, idx, new_val); // idx right half me

        segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];  // parent sum refresh
    }

public:
    // ── SegmentTree: constructor — array se tree build karo ──
    //   1) n = arr.size() store karo
    //   2) segTree size 4*n, lazy bhi 4*n (sab 0 se start)
    //   3) build(arr, 0, 0, n-1) se root se poora tree banao
    SegmentTree(const vector<int> &arr)
    {
        n = arr.size();
        segTree.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(arr, 0, 0, n - 1);
    }

    // ─── Public wrappers: bahar se call, i/l/r khud root se set ───

    // ── update_Range: public — [l,r] me val add karo ──
    //   1) user sirf range aur value deta hai
    //   2) andar i=0, l=0, r=n-1 se recursive update shuru hota hai
    void update_Range(int l, int r, int val)
    {
        update_Range(0, 0, n - 1, l, r, val);
    }

    // ── update_Index: public — ek index overwrite karo ──
    //   1) idx aur new_val lo
    //   2) root node se point update recursion start — lazy push raaste me hota hai
    void update_Index(int idx, int new_val)
    {
        update_Index(0, 0, n - 1, idx, new_val);
    }

    // ── querySum: public — [l,r] ka sum lao ──
    //   1) query_Range ko root se call karo
    //   2) andar 3-case + lazy push handle hota hai, result return
    ll querySum(int l, int r)
    {
        return query_Range(0, 0, n - 1, l, r);
    }
};
int main()
{
    vector<int> arr = {5, 3, 8, 6, 1, 4, 7, 9, 2, 0};
    SegmentTree st(arr);

    cout << "Initial sum [0, 9]: " << st.querySum(0, 9) << endl;

    // 🔁 Multiple Range Updates
    st.update_Range(2, 6, 5);  // +5 to [2,6]
    st.update_Range(0, 4, 10); // +10 to [0,4]
    st.update_Range(5, 9, -3); // -3 to [5,9]
    st.update_Range(3, 8, 7);  // +7 to [3,8]

    // 🎯 Multiple Point Updates (overwrite value)
    st.update_Index(2, 10); // arr[2] = 10
    st.update_Index(5, 25); // arr[5] = 25
    st.update_Index(9, 50); // arr[9] = 50

    // ❓ Range Queries
    cout << "Sum [0, 4]: " << st.querySum(0, 4) << endl;
    cout << "Sum [2, 6]: " << st.querySum(2, 6) << endl;
    cout << "Sum [5, 9]: " << st.querySum(5, 9) << endl;
    cout << "Sum [0, 9]: " << st.querySum(0, 9) << endl;
    cout << "Sum [3, 8]: " << st.querySum(3, 8) << endl;

    return 0;
}