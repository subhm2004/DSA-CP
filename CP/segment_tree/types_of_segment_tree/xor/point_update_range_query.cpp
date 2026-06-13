#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * OPERATION : XOR
 * VARIATION : Point Update + Range Query
 * LAZY      : NO
 * COMPLEXITY: build O(n) | point update O(log n) | range query O(log n)
 * ════════════════════════════════════════════════════════════════════════════
 * Ek index ki value SET karo, kisi [L,R] range ka XOR nikaalo.
 * Merge = left ^ right, no-overlap identity = 0 (kyunki x ^ 0 = x).
 * ════════════════════════════════════════════════════════════════════════════
 */

class XorSeg_PointUpdate_RangeQuery
{
private:
    vector<int> segTree; // har node pe uske segment ka XOR store hota hai
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
    //   val -> idx pe SET karne ki nayi poori value (replace, ^= nahi)
    //
    // Har query me 3 case hote hain node [l,r] vs query [start,end]:
    //   1) NO overlap    -> node poori tarah query ke bahar  (r < start || l > end)
    //   2) FULL overlap  -> node poori tarah query ke andar  (start <= l && r <= end)
    //   3) PARTIAL       -> thoda andar thoda bahar -> dono bachho me recurse karo
    //
    // XOR properties (yaad rakho):
    //   x ^ 0 = x  → no overlap me 0 return karte hain (identity)
    //   merge = left child XOR ^ right child XOR

    // ── build: array se XOR segment tree banao (recursive) ────────────────────
    // Params: arr = input array, i = current node index, l/r = segment bounds
    // Steps:
    //   1) Agar l == r (leaf) → segTree[i] = arr[l], return
    //   2) mid = (l+r)/2 nikalo, segment do halves me todo
    //   3) Left child [l, mid] aur right child [mid+1, r] ko recursively build karo
    //   4) Parent ka XOR = left child XOR ^ right child XOR
    void build(const vector<int> &arr, int i, int l, int r)
    {
        if (l == r)
        {
            segTree[i] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * i + 1, l, mid);
        build(arr, 2 * i + 2, mid + 1, r);
        segTree[i] = segTree[2 * i + 1] ^ segTree[2 * i + 2];
    }

    // ── update_Point: index idx ki value val SET karo (replace, not ^=) ───────
    // Params: i = current node, l/r = segment bounds, idx = target index, val = nayi value
    // Steps:
    //   1) Agar l == r (leaf mil gaya) → segTree[i] = val set karo, return
    //   2) mid = (l+r)/2 — idx left half me hai ya right decide karo
    //   3) idx <= mid → left child me jao, warna right child me
    //   4) Wapas aate waqt parent ka XOR refresh: left ^ right
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
        segTree[i] = segTree[2 * i + 1] ^ segTree[2 * i + 2];
    }

    // ── query_Range: [start, end] range ka XOR nikaalo ────────────────────────
    // Params: i = current node, l/r = node ka segment, start/end = query range
    // Steps:
    //   1) NO overlap (r < start || l > end) → 0 return (XOR identity)
    //   2) FULL overlap (start <= l && r <= end) → seedha segTree[i] return
    //   3) PARTIAL overlap → mid nikalo, dono bachho se XOR mangaao, unhe ^ karke jodo
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
        return query_Range(2 * i + 1, l, mid, start, end)
             ^ query_Range(2 * i + 2, mid + 1, r, start, end);
    }

public:
    // ── XorSeg_PointUpdate_RangeQuery: constructor ──────────────────────────
    // Params: arr = initial array jisse tree banana hai
    // Steps:
    //   1) n = arr.size(), segTree vector 4*n size allocate (safe upper bound)
    //   2) Agar n > 0 hai to root i=0 se poori array [0, n-1] par build() call karo
    //   3) Ab point update aur range XOR query dono ready hain
    XorSeg_PointUpdate_RangeQuery(const vector<int> &arr)
    {
        n = (int)arr.size();
        segTree.assign(4 * max(n, 1), 0);
        if (n > 0)
        {
            build(arr, 0, 0, n - 1);
        }
    }

    // ── update_Point: public wrapper — bahar se seedha point SET ──────────────
    // Params: idx = array index, val = nayi value
    // Root node (i=0, l=0, r=n-1) khud set karta hai
    void update_Point(int idx, int val)
    {
        update_Point(0, 0, n - 1, idx, val);
    }

    // ── query_Range: public wrapper — bahar se seedha range XOR query ───────
    // Params: l, r = query range [l, r] inclusive
    int query_Range(int l, int r)
    {
        return query_Range(0, 0, n - 1, l, r);
    }
};

int main()
{
    vector<int> arr = {1, 2, 3, 4, 5};

    cout << "---- XOR | Point Update + Range Query ----\n";
    XorSeg_PointUpdate_RangeQuery st(arr);
    cout << "XOR(0,4): " << st.query_Range(0, 4) << endl;
    cout << "XOR(1,3): " << st.query_Range(1, 3) << endl;

    st.update_Point(0, 5);
    cout << "After arr[0]=5, XOR(0,4): " << st.query_Range(0, 4) << endl;

    return 0;
}
