#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * OPERATION : XOR
 * VARIATION : Range Update + Point Query
 * LAZY      : YES (range XOR flip — har element ^= val)
 * COMPLEXITY: build O(n) | range update O(log n) | point query O(log n)
 * ════════════════════════════════════════════════════════════════════════════
 * Poori range me har element ^= val (bits flip), ek index ki value maango.
 *
 * XOR lazy rule (SUM se alag!):
 *   segment_XOR ^= v  SIRF jab segment length ODD ho
 *   kyunki v^v^v... even baar = 0, odd baar = v
 *   lazy[i] ^= v HAMESHA (pending flip bachho tak pass hoga)
 * ════════════════════════════════════════════════════════════════════════════
 */

class XorSeg_RangeUpdate_PointQuery
{
private:
    vector<int> segTree, lazy; // segTree = segment XOR, lazy = pending XOR flip sab elements par
    int n;

    // Har recursive function me ye params baar baar aate hain, ek baar samajh le:
    //
    //   i (ya node) -> tree array me current node ka index (root = 0)
    //                  left child  = 2*i + 1
    //                  right child = 2*i + 2
    //   l, r   -> current node ka segment [l, r] (actual array indices)
    //   start, end -> user ne jo range update maangi uske left-right ends
    //   mid -> (l + r) / 2, segment ko do halves me todne ka point
    //   idx -> point query ke liye target array index
    //   val/v -> range update me har element par ^= karne ki value (bits flip)
    //
    // Har range update me 3 case hote hain node [l,r] vs update [start,end]:
    //   1) NO overlap    -> skip (r < start || l > end)
    //   2) FULL overlap  -> apply() lagao, return
    //   3) PARTIAL       -> dono bachho me recurse karo
    //
    // XOR lazy rule (SUM se alag — yaad rakho!):
    //   SUM range += v  → segment_sum += v * len  (hamesha badhta hai)
    //   XOR range ^= v  → segTree[i] ^= v SIRF jab len ODD ho
    //                     lazy[i] ^= v HAMESHA (pending flip store)

    // ── build: array se XOR tree banao (lazy shuru me 0 rehta hai) ────────────
    // Params: arr = input array, i = current node, l/r = segment bounds
    // Steps:
    //   1) Agar l == r (leaf) → segTree[i] = arr[l], return
    //   2) mid nikalo, left [l,mid] aur right [mid+1,r] recursively build karo
    //   3) Parent ka XOR = left child XOR ^ right child XOR
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

    // ── apply: segment [l,r] ke SAB elements ^= v (XOR lazy ka core rule) ───
    // Params: i = current node, l/r = segment bounds, v = flip value
    // Steps:
    //   1) len = r - l + 1 nikalo (segment ki length)
    //   2) Agar len ODD hai → segTree[i] ^= v  (v^v^v odd baar = v, even baar = 0)
    //   3) lazy[i] ^= v HAMESHA — pending flip store karo (bachho tak baad me pass hoga)
    // NOTE: SUM me segTree += v*len hota tha; XOR me parity matter karti hai!
    void apply(int i, int l, int r, int v)
    {
        int len = r - l + 1;
        if (len & 1)
        {
            segTree[i] ^= v;
        }
        lazy[i] ^= v;
    }

    // ── push: node i pe pada pending lazy XOR bachho tak pass karo ───────────
    // Params: i = current node, l/r = segment bounds
    // Steps:
    //   1) Agar lazy[i] == 0 → kuch pending nahi, return
    //   2) mid = (l+r)/2 nikalo
    //   3) apply() se left child [l,mid] aur right child [mid+1,r] par lazy[i] pass karo
    //   4) lazy[i] = 0 — apna pending clear (ab bachho ke paas hai)
    void push(int i, int l, int r)
    {
        if (lazy[i] == 0)
        {
            return;
        }
        int mid = (l + r) / 2;
        apply(2 * i + 1, l, mid, lazy[i]);
        apply(2 * i + 2, mid + 1, r, lazy[i]);
        lazy[i] = 0;
    }

    // ── update_Range: [start, end] me har element ^= val ─────────────────────
    // Params: i = current node, l/r = node segment, start/end = update range, val = flip value
    // Steps:
    //   1) Pehle push(i,l,r) — apna pending lazy apply karo taaki node sahi ho
    //   2) NO overlap → return (kuch mat karo)
    //   3) FULL overlap → apply(i,l,r,val) lagao, return
    //   4) PARTIAL → mid nikalo, dono bachho me recurse
    //   NOTE: yaha sirf point query chahiye — wapas aate waqt parent XOR refresh NAHI karte
    void update_Range(int i, int l, int r, int start, int end, int val)
    {
        push(i, l, r);
        if (r < start || l > end)
        {
            return;
        }
        if (start <= l && r <= end)
        {
            apply(i, l, r, val);
            return;
        }
        int mid = (l + r) / 2;
        update_Range(2 * i + 1, l, mid, start, end, val);
        update_Range(2 * i + 2, mid + 1, r, start, end, val);
    }

    // ── query_Point: index idx ki current value kya hai ───────────────────────
    // Params: i = current node, l/r = segment bounds, idx = target index
    // Steps:
    //   1) push(i,l,r) — raaste me saara pending lazy apply karo
    //   2) Agar l == r (leaf) → segTree[i] return (yahi arr[idx] ki value hai)
    //   3) mid nikalo — idx left me hai to left child, warna right child me jao
    int query_Point(int i, int l, int r, int idx)
    {
        push(i, l, r);
        if (l == r)
        {
            return segTree[i];
        }
        int mid = (l + r) / 2;
        if (idx <= mid)
        {
            return query_Point(2 * i + 1, l, mid, idx);
        }
        else
        {
            return query_Point(2 * i + 2, mid + 1, r, idx);
        }
    }

public:
    // ── XorSeg_RangeUpdate_PointQuery: constructor ──────────────────────────
    // Params: arr = initial array
    // Steps:
    //   1) n = arr.size(), segTree aur lazy dono 4*n size allocate
    //   2) lazy ko 0 se init — shuru me koi pending XOR flip nahi
    //   3) build() se initial array values tree me daal do
    XorSeg_RangeUpdate_PointQuery(const vector<int> &arr)
    {
        n = (int)arr.size();
        segTree.assign(4 * max(n, 1), 0);
        lazy.assign(4 * max(n, 1), 0);
        if (n > 0)
        {
            build(arr, 0, 0, n - 1);
        }
    }

    // ── update_Range: public wrapper — bahar se seedha range XOR flip ───────
    // Params: l, r = update range [l,r], val = har element par ^= karne ki value
    void update_Range(int l, int r, int val)
    {
        update_Range(0, 0, n - 1, l, r, val);
    }

    // ── query_Point: public wrapper — bahar se seedha point value query ─────
    // Params: idx = jis index ki value chahiye
    int query_Point(int idx)
    {
        return query_Point(0, 0, n - 1, idx);
    }
};

int main()
{
    vector<int> arr = {1, 2, 3, 4, 5};

    cout << "---- XOR | Range Update + Point Query ----\n";
    XorSeg_RangeUpdate_PointQuery st(arr);
    cout << "Start arr[2] = " << st.query_Point(2) << endl;

    st.update_Range(1, 3, 7);
    cout << "After [1,3] ^= 7:\n";
    cout << "  arr[1] = " << st.query_Point(1) << " (expected 5)\n";
    cout << "  arr[2] = " << st.query_Point(2) << " (expected 4)\n";
    cout << "  arr[3] = " << st.query_Point(3) << " (expected 3)\n";

    return 0;
}
