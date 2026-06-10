#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// GCD SEGMENT TREE — Range GCD Query + Point Update
// ────────────────────────────────────────────────────────────────────────────
// Har recursive function me ye params common hain:
//   i      -> tree array me current node ka index (root = 0, left = 2*i+1, right = 2*i+2)
//   l, r   -> ye node array ke [l, r] segment ka maalik hai
//   start,end / idx -> query/update ki range ya single index
//
// GCD merge: parent ka GCD = GCD(left child ka GCD, right child ka GCD)
// No overlap pe 0 return karte hain (GCD(x, 0) = x, isliye safe hai)
// ════════════════════════════════════════════════════════════════════════════

// ── GCD: Euclidean algorithm se GCD nikalo ──
//   1) b == 0 ho to a hi GCD hai — base case
//   2) warna b aur a%b pe recursively call karo
//   3) Euclidean algo guaranteed O(log min(a,b)) me answer deta hai
//   4) segment tree me merge operation ke liye use hota hai
int GCD(int a, int b)
{
    if (b == 0)
        return a;
    return GCD(b, a % b);
}

class SegmentTree
{
private:
    vector<int> segTree;
    int n;

    // ── build: array se GCD segment tree banao ──
    //   1) l==r pe leaf — segTree[i] = arr[l] (single element ka GCD wahi element)
    //   2) mid split karke left [l,mid] aur right [mid+1,r] subtrees build karo
    //   3) parent ka GCD = GCD(left child GCD, right child GCD)
    //   4) bottom-up merge — har node apne segment ka overall GCD store karta hai
    void build(vector<int> &arr, int i, int l, int r)
    {
        if (l == r)  // leaf node
        {
            segTree[i] = arr[l];
            return;
        }

        int mid = (l + r) / 2;
        build(arr, 2 * i + 1, l, mid);
        build(arr, 2 * i + 2, mid + 1, r);
        segTree[i] = GCD(segTree[2 * i + 1], segTree[2 * i + 2]);  // merge: dono bachho ka GCD
    }

    // ── update_Point: index idx ki value replace karo ──
    //   1) l==r pe leaf — segTree[i] = val overwrite karo, return
    //   2) idx <= mid ho to left child me jao, warna right child me
    //   3) wapas aate waqt parent GCD = GCD(left, right) refresh karo
    //   4) sirf ek raasta root→leaf — O(log n) point update
    void update_Point(int i, int l, int r, int idx, int val)
    {
        if (l == r)  // leaf — target index mil gaya
        {
            segTree[i] = val;
            return;
        }

        int mid = (l + r) / 2;
        if (idx <= mid)
            update_Point(2 * i + 1, l, mid, idx, val);
        else
            update_Point(2 * i + 2, mid + 1, r, idx, val);

        segTree[i] = GCD(segTree[2 * i + 1], segTree[2 * i + 2]);  // parent GCD refresh
    }

    // ── query_Range: [start,end] ka GCD nikalo ──
    //   1) Case 1 NO overlap — 0 return (GCD(x,0)=x, isliye merge me safe identity)
    //   2) Case 2 FULL overlap — seedha segTree[i] return, aur recurse nahi
    //   3) Case 3 PARTIAL — left aur right subtree ka GCD lo, unka GCD return karo
    //   4) GCD associative hai — isliye partial merge se sahi answer milta hai
    int query_Range(int i, int l, int r, int start, int end)
    {
        if (r < start || l > end)  // Case 1: NO overlap
            return 0;

        if (start <= l && r <= end)  // Case 2: FULL overlap
            return segTree[i];

        int mid = (l + r) / 2;  // Case 3: PARTIAL overlap
        return GCD(
            query_Range(2 * i + 1, l, mid, start, end),
            query_Range(2 * i + 2, mid + 1, r, start, end));
    }

public:
    // ── SegmentTree: constructor — array se GCD tree build ──
    //   1) n = arr.size() store karo
    //   2) segTree size 4*n allocate karo (safe padding)
    //   3) build(arr, 0, 0, n-1) se root se poora tree construct karo
    SegmentTree(vector<int> &arr)
    {
        n = arr.size();
        segTree.resize(4 * n);
        build(arr, 0, 0, n - 1);
    }

    // ── update_Point: public wrapper — ek index overwrite ──
    //   1) idx aur val lo
    //   2) root (i=0) se point update recursion — O(log n)
    void update_Point(int idx, int val)
    {
        update_Point(0, 0, n - 1, idx, val);
    }

    // ── query_Range: public wrapper — [l,r] ka GCD ──
    //   1) user range deta hai
    //   2) andar 3-case recursive query — root se start, GCD return
    int query_Range(int l, int r)
    {
        return query_Range(0, 0, n - 1, l, r);
    }
};

int main()
{
    vector<int> arr = {6, 12, 18, 24};

    vector<vector<int>> queries =
        {
            {1, 30},
            {3, 3156},
            {0, 438}};

    SegmentTree seg(arr);

    cout << "Initial GCD of whole array: ";
    cout << seg.query_Range(0, arr.size() - 1) << endl;

    for (auto q : queries)
    {
        int idx = q[0];
        int val = q[1];

        seg.update_Point(idx, val);

        cout << "After updating index " << idx << " to " << val << endl;

        cout << "Current GCD of whole array: ";
        cout << seg.query_Range(0, arr.size() - 1) << endl;
    }

    return 0;
}
