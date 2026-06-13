#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * OPERATION : GCD
 * VARIATION : Point Update + Range Query
 * LAZY      : NO
 * COMPLEXITY: build O(n log V) | point update O(log n) | range query O(log n)
 *             (V = max array value; har merge pe GCD call)
 * ════════════════════════════════════════════════════════════════════════════
 * ✅ VALID GCD variation — competitive programming me yahi commonly use hota hai.
 * Ek index ki value replace karo, kisi [L,R] range ka GCD nikaalo.
 * Merge = GCD(left, right), no-overlap identity = 0 (GCD(x,0)=x).
 * ════════════════════════════════════════════════════════════════════════════
 */

// ── computeGCD: Euclidean algorithm se do numbers ka GCD nikalo ───────────────
// Params: a, b = do integers jinka GCD chahiye
// Steps:
//   1) Agar b == 0 → GCD = a (base case)
//   2) Warna recursively computeGCD(b, a % b) — Euclidean algorithm
int computeGCD(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    return computeGCD(b, a % b);
}

class GcdSeg_PointUpdate_RangeQuery
{
private:
    vector<int> segTree; // har node pe uske segment ka GCD store hota hai
    int n;

    // Har recursive function me ye params baar baar aate hain, ek baar samajh le:
    //
    //   i (ya node) -> tree array me current node ka index (root = 0)
    //                  left child  = 2*i + 1
    //                  right child = 2*i + 2
    //   l   -> current node jis segment ka maalik hai uska LEFT end (actual arr index)
    //   r   -> current node jis segment ka maalik hai uska RIGHT end (actual arr index)
    //          matlab ye node array ke [l, r] hisse ko represent karta hai
    //   start/end -> user ne jo range query maangi uske left-right ends
    //   mid -> (l + r) / 2, segment ko do halves me todne ka point
    //   idx -> point update ke liye target array index
    //   val -> idx pe replace karne ki nayi value
    //
    // Har query me 3 case hote hain node [l,r] vs query [start,end]:
    //   1) NO overlap    -> node poori tarah query ke bahar  (r < start || l > end)
    //   2) FULL overlap  -> node poori tarah query ke andar  (start <= l && r <= end)
    //   3) PARTIAL       -> thoda andar thoda bahar -> dono bachho me recurse karo
    //
    // GCD properties:
    //   GCD(x, 0) = x  → no overlap me 0 return (identity)
    //   merge = GCD(left child GCD, right child GCD)

    // ── build: array se GCD segment tree banao (recursive) ──────────────────
    // Params: arr = input array, i = current node, l/r = segment bounds
    // Steps:
    //   1) Agar l == r (leaf) → segTree[i] = arr[l], return
    //   2) mid nikalo, left [l,mid] aur right [mid+1,r] recursively build karo
    //   3) Parent ka GCD = computeGCD(left child GCD, right child GCD)
    void build(vector<int> &arr, int i, int l, int r)
    {
        if (l == r)
        {
            segTree[i] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * i + 1, l, mid);
        build(arr, 2 * i + 2, mid + 1, r);
        segTree[i] = computeGCD(segTree[2 * i + 1], segTree[2 * i + 2]);
    }

    // ── update_Point: index idx ki value val replace karo ─────────────────────
    // Params: i = current node, l/r = segment bounds, idx = target index, val = nayi value
    // Steps:
    //   1) Agar l == r (leaf) → segTree[i] = val set karo, return
    //   2) mid nikalo — idx left half me hai ya right decide karo
    //   3) Sahi child me recursively update karo
    //   4) Wapas aate waqt parent ka GCD refresh: GCD(left, right)
    void update_Point(int i, int l, int r, int idx, int val)
    {
        if (l == r)
        {
            segTree[i] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid)
        {
            update_Point(2 * i + 1, l, mid, idx, val);
        }
        else
        {
            update_Point(2 * i + 2, mid + 1, r, idx, val);
        }
        segTree[i] = computeGCD(segTree[2 * i + 1], segTree[2 * i + 2]);
    }

    // ── query_Range: [start, end] range ka GCD nikaalo ──────────────────────
    // Params: i = current node, l/r = node segment, start/end = query range
    // Steps:
    //   1) NO overlap (r < start || l > end) → 0 return (GCD identity)
    //   2) FULL overlap (start <= l && r <= end) → seedha segTree[i] return
    //   3) PARTIAL → dono bachho se GCD mangaao, computeGCD se merge karo
    int query_Range(int i, int l, int r, int start, int end)
    {
        if (r < start || l > end)
        {
            return 0;
        }
        if (start <= l && r <= end)
        {
            return segTree[i];
        }
        int mid = (l + r) / 2;
        return computeGCD(
            query_Range(2 * i + 1, l, mid, start, end),
            query_Range(2 * i + 2, mid + 1, r, start, end));
    }

public:
    // ── GcdSeg_PointUpdate_RangeQuery: constructor ────────────────────────────
    // Params: arr = initial array (non-const ref — build modify kar sakta hai)
    // Steps:
    //   1) n = arr.size(), segTree vector 4*n size allocate
    //   2) Agar n > 0 hai to root i=0 se poori array [0, n-1] par build() call karo
    //   3) Ab point update aur range GCD query dono ready hain
    GcdSeg_PointUpdate_RangeQuery(vector<int> &arr)
    {
        n = (int)arr.size();
        segTree.resize(4 * max(n, 1));
        if (n > 0)
        {
            build(arr, 0, 0, n - 1);
        }
    }

    // ── update_Point: public wrapper — bahar se seedha point replace ──────────
    // Params: idx = array index, val = nayi value
    void update_Point(int idx, int val)
    {
        update_Point(0, 0, n - 1, idx, val);
    }

    // ── query_Range: public wrapper — bahar se seedha range GCD query ───────
    // Params: l, r = query range [l, r] inclusive
    int query_Range(int l, int r)
    {
        return query_Range(0, 0, n - 1, l, r);
    }
};

int main()
{
    vector<int> arr = {6, 12, 18, 24};

    cout << "---- GCD | Point Update + Range Query (VALID) ----\n";
    GcdSeg_PointUpdate_RangeQuery st(arr);
    cout << "Initial GCD [0,3]: " << st.query_Range(0, 3) << endl;

    st.update_Point(0, 30);
    cout << "After arr[0]=30, GCD [0,3]: " << st.query_Range(0, 3) << endl;

    st.update_Point(3, 3156);
    cout << "After arr[3]=3156, GCD [0,3]: " << st.query_Range(0, 3) << endl;

    return 0;
}
