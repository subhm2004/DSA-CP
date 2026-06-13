#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * ⚠️  WARNING — GCD RANGE LAZY (EDUCATIONAL ONLY)
 * ════════════════════════════════════════════════════════════════════════════
 * GCD does NOT support additive range lazy propagation mathematically!
 *
 * Range add ke baad segment GCD ko parent se refresh karna bhi kaam nahi karta
 * kyunki GCD(a+v, b+v) generally GCD(a,b)+v ke barabar NAHI hota.
 *
 * Kyun invalid hai?
 *   SUM me: range add ke baad parent sum = left sum + right sum  (sahi!)
 *   GCD me: range add ke baad GCD(left+v..., right+v...) ≠ purana GCD + k*v
 *   Parent refresh (computeGCD) bhi galat answer dega kyunki leaf values
 *   lazy add se corrupt ho chuki hain — GCD merge unpe sahi kaam nahi karta.
 *
 * ✅ Valid GCD file : gcd/point_update_range_query.cpp
 * 📚 Lazy + parent refresh pattern : sum/range_update_range_query.cpp
 * ════════════════════════════════════════════════════════════════════════════
 * OPERATION : GCD (⚠️ lazy add NOT mathematically valid)
 * VARIATION : Range Update + Range Query
 * LAZY      : YES (structure only — DO NOT use in contests for GCD!)
 * COMPLEXITY: O(log n) per op structurally, but GCD answers after range add WRONG
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

class GcdSeg_RangeUpdate_RangeQuery
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
    //   start, end -> user ne jo range update/query maangi uske left-right ends
    //   mid -> (l + r) / 2
    //   val -> range me har element par +val add (⚠️ GCD ke saath mathematically galat!)
    //
    // ⚠️ WARNING: Neeche push/update/query SUM lazy skeleton jaisa hai.
    // GCD range add ke baad answers UNRELIABLE honge — sirf pattern seekhne ke liye!

    // ── build: GCD tree banao ───────────────────────────────────────────────
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

    // ── update_Range: partial pe parent refresh — sum v3 jaisa skeleton ────
    // Params: i = current node, l/r = node segment, start/end = update range, val = add
    // Steps (SUM skeleton — GCD answers galat):
    //   1) push(i,l,r)
    //   2) NO overlap → return
    //   3) FULL overlap → lazyAdd[i] += val, push apply
    //   4) PARTIAL → recurse dono bachho me
    //   5) Parent GCD refresh — ⚠️ ye bhi GCD add ke liye galat answer dega
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
        push(2 * i + 1, l, mid);
        push(2 * i + 2, mid + 1, r);
        segTree[i] = computeGCD(segTree[2 * i + 1], segTree[2 * i + 2]); // refresh bhi GCD add ke liye galat
    }

    // ── query_Range: lazy apply karke GCD query — ⚠️ add ke baad unreliable ─
    // Params: i = current node, l/r = node segment, start/end = query range
    // Steps:
    //   1) push(i,l,r) — lazy apply
    //   2) NO overlap → 0 return (GCD identity)
    //   3) FULL overlap → segTree[i] return
    //   4) PARTIAL → dono bachho se GCD merge
    // ⚠️ Range add ke baad ye GCD mathematically sahi nahi hoga
    int query_Range(int i, int l, int r, int start, int end)
    {
        push(i, l, r);
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
    // ── GcdSeg_RangeUpdate_RangeQuery: constructor (⚠️ educational skeleton) ─
    // Params: arr = initial array
    // Steps:
    //   1) n = arr.size(), segTree + lazy allocate
    //   2) lazy 0 se init
    //   3) build() se GCD tree — lazy add ke baad answers unreliable
    GcdSeg_RangeUpdate_RangeQuery(const vector<int> &arr)
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

    // ── query_Range: public wrapper — ⚠️ lazy add ke baad GCD unreliable ─────
    // Params: l, r = query range [l, r] inclusive
    int query_Range(int l, int r)
    {
        return query_Range(0, 0, n - 1, l, r);
    }
};

int main()
{
    cout << "⚠️  GCD Range Update + Range Query — EDUCATIONAL LAZY SKELETON ONLY\n";
    cout << "Real GCD problems ke liye gcd/point_update_range_query.cpp use karo.\n";
    cout << "Lazy + parent refresh pattern: sum/range_update_range_query.cpp\n\n";

    vector<int> arr = {6, 12, 18, 24};
    GcdSeg_RangeUpdate_RangeQuery st(arr);
    cout << "Initial GCD [0,3]: " << st.query_Range(0, 3) << " (valid before lazy add)\n";

    st.update_Range(0, 2, 5);
    cout << "After lazy add (⚠️ unreliable): GCD [0,3] = " << st.query_Range(0, 3) << endl;

    return 0;
}
