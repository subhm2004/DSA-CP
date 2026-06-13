#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * ⚠️  WARNING — GCD RANGE LAZY (EDUCATIONAL ONLY)
 * ════════════════════════════════════════════════════════════════════════════
 * GCD does NOT support additive range lazy propagation mathematically!
 *
 * Agar poori range [L,R] me har element ko +v add karoge, to:
 *   GCD(a+v, b+v, ...) ≠ GCD(a,b,...) + k*v   (generally galat!)
 *
 * Kyun invalid hai?
 *   SUM me: sab elements +v → segment sum += v * len  (linear, predictable)
 *   GCD me: sab elements +v → naya GCD purane GCD se koi simple relation nahi rakhta
 *   Example: GCD(6,12)=6, +5 karne pe GCD(11,17)=1 — koi +k*v formula nahi!
 *
 * Isliye real GCD problems me sirf point_update_range_query.cpp use karo.
 * Ye file SUM ke lazy structure ko samajhne ke liye hai — same skeleton,
 * lekin GCD ke saath range add lazy logically valid NAHI hai.
 *
 * ✅ Valid GCD file : gcd/point_update_range_query.cpp
 * 📚 Lazy pattern seekhne ke liye : sum/range_update_point_query.cpp
 * ════════════════════════════════════════════════════════════════════════════
 * OPERATION : GCD (⚠️ lazy add NOT mathematically valid)
 * VARIATION : Range Update + Point Query
 * LAZY      : YES (structure only — DO NOT use in contests for GCD!)
 * COMPLEXITY: same as sum lazy O(log n) per op, but answers are WRONG for GCD
 * ════════════════════════════════════════════════════════════════════════════
 */

// ── computeGCD: Euclidean algorithm se GCD nikalo ───────────────────────────
// Params: a, b = do integers
// Steps:
//   1) b == 0 → return a
//   2) Warna computeGCD(b, a % b) recursively
int computeGCD(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    return computeGCD(b, a % b);
}

class GcdSeg_RangeUpdate_PointQuery
{
private:
    vector<int> segTree, lazyAdd; // segTree = GCD, lazy = pending add (⚠️ GCD ke liye invalid!)
    int n;

    // Har recursive function me ye params baar baar aate hain, ek baar samajh le:
    //
    //   i (ya node) -> tree array me current node ka index (root = 0)
    //                  left child  = 2*i + 1
    //                  right child = 2*i + 2
    //   l, r   -> current node ka segment [l, r]
    //   start, end -> user ne jo range update maangi uske left-right ends
    //   mid -> (l + r) / 2
    //   idx -> point query ke liye target index
    //   val -> range me har element par +val add (⚠️ GCD ke saath mathematically galat!)
    //
    // ⚠️ WARNING: Neeche push/update SUM lazy jaisa hai — GCD problems me mat use karo!
    // Sirf lazy propagation ka SKELETON samajhne ke liye rakha hai.

    // ── build: GCD tree banao (valid point-update version jaisa) ──────────────
    // Params: arr = input array, i = current node, l/r = segment bounds
    // Steps:
    //   1) l == r (leaf) → segTree[i] = arr[l]
    //   2) mid nikalo, dono bachho ko build karo
    //   3) Parent GCD = computeGCD(left, right)
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
        segTree[i] = computeGCD(segTree[2 * i + 1], segTree[2 * i + 2]);
    }

    // ── push: ⚠️ EDUCATIONAL — SUM lazy skeleton (GCD pe INVALID!) ───────────
    //   GCD pe range ADD lazy mathematically galat — sirf pattern seekhne ke liye
    //   Valid GCD: gcd/point_update_range_query.cpp (NO lazy)
    //   1) lazyAdd[i] == 0 → return
    //   2) segTree[i] += lazyAdd[i]  ← ⚠️ GCD ke liye galat, SUM/MAX jaisa add
    //   3) bachho: lazyAdd[child] += lazyAdd[i]
    //   4) lazyAdd[i] = 0
    void push(int i, int l, int r)
    {
        if (lazyAdd[i] != 0)
        {
            segTree[i] += lazyAdd[i]; // ⚠️ GCD pe mathematically invalid
            if (l != r)
            {
                lazyAdd[2 * i + 1] += lazyAdd[i];
                lazyAdd[2 * i + 2] += lazyAdd[i];
            }
            lazyAdd[i] = 0;
        }
    }

    // ── update_Range: SUM lazy jaisa range add — ⚠️ GCD problems me mat use karo ─
    // Params: i = current node, l/r = node segment, start/end = update range, val = add value
    // Steps (SUM skeleton — GCD answers galat honge):
    //   1) push(i,l,r) — pending lazy apply
    //   2) NO overlap → return
    //   3) FULL overlap → lazyAdd[i] += val, push se apply
    //   4) PARTIAL → dono bachho me recurse
    //   NOTE: point-query variant hai — parent GCD refresh nahi karte
    void update_Range(int i, int l, int r, int start, int end, int val)
    {
        push(i, l, r);
        if (r < start || l > end)
        {
            return;
        }
        if (start <= l && r <= end)
        {
            lazyAdd[i] += val;
            push(i, l, r);
            return;
        }
        int mid = (l + r) / 2;
        update_Range(2 * i + 1, l, mid, start, end, val);
        update_Range(2 * i + 2, mid + 1, r, start, end, val);
    }

    // ── query_Point: leaf tak jao, pending lazy apply karte hue ─────────────
    // Params: i = current node, l/r = segment bounds, idx = target index
    // Steps:
    //   1) push(i,l,r) — raaste me lazy apply (SUM pattern)
    //   2) l == r (leaf) → segTree[i] return
    //   3) idx left/right decide karke recurse
    // ⚠️ Range add ke baad ye value mathematically sahi GCD element nahi hogi
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
    // ── GcdSeg_RangeUpdate_PointQuery: constructor (⚠️ educational skeleton) ─
    // Params: arr = initial array
    // Steps:
    //   1) n = arr.size(), segTree + lazy allocate
    //   2) lazy 0 se init
    //   3) build() se GCD tree banao — build valid hai, lazy add invalid hai
    GcdSeg_RangeUpdate_PointQuery(const vector<int> &arr)
    {
        n = (int)arr.size();
        segTree.resize(4 * max(n, 1));
        lazyAdd.assign(4 * max(n, 1), 0);
        if (n > 0)
        {
            build(arr, 0, 0, n - 1);
        }
    }

    // ── update_Range: public wrapper — ⚠️ GCD range add, contests me mat use karo ─
    // Params: l, r = update range, val = har element par +val
    void update_Range(int l, int r, int val)
    {
        update_Range(0, 0, n - 1, l, r, val);
    }

    // ── query_Point: public wrapper — point value (lazy add ke baad unreliable) ─
    // Params: idx = target index
    int query_Point(int idx)
    {
        return query_Point(0, 0, n - 1, idx);
    }
};

int main()
{
    cout << "⚠️  GCD Range Update + Point Query — EDUCATIONAL LAZY SKELETON ONLY\n";
    cout << "Real GCD problems ke liye gcd/point_update_range_query.cpp use karo.\n";
    cout << "Lazy pattern seekhne ke liye sum/range_update_point_query.cpp dekho.\n\n";

    vector<int> arr = {6, 12, 18, 24};
    GcdSeg_RangeUpdate_PointQuery st(arr);
    cout << "Demo (values may not reflect true GCD math after range add):\n";
    st.update_Range(0, 2, 5);
    cout << "After lazy add +5 on [0,2], arr[0] reported as: " << st.query_Point(0) << endl;

    return 0;
}
