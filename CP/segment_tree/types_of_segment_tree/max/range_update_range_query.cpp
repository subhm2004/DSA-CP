#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * OPERATION : MAX
 * VARIATION : Range Update + Range Query
 * LAZY      : YES (range ADD lazy — ⚠️ lazy me MAX nahi, ADD pending hai!)
 * COMPLEXITY: build O(n) | range update O(log n) | range query O(log n)
 * ════════════════════════════════════════════════════════════════════════════
 * ⚠️ CONFUSION MAT KARO — do alag cheezein:
 *
 *   segTree[i]  →  is segment ka MAXIMUM (query ka answer yahi hai)
 *   lazyAdd[i]  →  har element me kitna +ADD pending hai (MAX value NAHI!)
 *
 * Range me +val add karo → segment ke SAARE elements +val → MAX bhi +val badhega.
 * Isliye push me:  segTree[i] += lazyAdd[i]     (sirf ek baar!)
 * SUM wale me hota: segTree[i] += lazy * len    (sum ke liye multiply — MAX me NAHI)
 *
 * Partial update ke baad parent ka max refresh = max(left child, right child).
 * ════════════════════════════════════════════════════════════════════════════
 */

class MaxSeg_RangeUpdate_RangeQuery
{
private:
    // ── Common recursive params (har function me same meaning) ─────────────────
    //   i     -> tree array me current node ka index (root = 0)
    //            left child = 2*i + 1, right child = 2*i + 2
    //   l, r  -> current node ka segment range [l, r] (actual array indices)
    //   start, end -> user ki query/update range ke left-right ends
    //   mid   -> (l + r) / 2, segment ko do halves me todne ka point
    //
    //   Range ops me 3 cases (node [l,r] vs user range [start,end]):
    //     1) NO overlap    -> r < start || l > end  (query: IDENTITY INT_MIN return)
    //     2) FULL overlap  -> start <= l && r <= end (query: segTree[i]; update: lazy += val)
    //     3) PARTIAL        -> dono bachho me recurse karo, max(leftAns, rightAns)
    //
    //   MAX tree: segTree = segment MAX | lazyAdd = pending +ADD (SUM jaisa *len NAHI)
    vector<int> segTree, lazyAdd;
    int n;
    static constexpr int IDENTITY = INT_MIN;

    // ── build: array se max tree banao ────────────────────────────────────────
    //   Params: i = current node, l/r = is node ka segment range
    //   1) l == r (leaf) -> segTree[i] = arr[l], return
    //   2) mid split, left aur right child dono ko recursively build karo
    //   3) parent ka max = max(left child, right child)
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
        segTree[i] = max(segTree[2 * i + 1], segTree[2 * i + 2]);
    }

    // ── push: pending +ADD lazy apply karo (⚠️ yahan max() NAHI lagta!) ───────
    //
    //   segTree[i]  = is segment ka MAXIMUM (stored answer)
    //   lazyAdd[i]  = har element me kitna +ADD abhi pending hai
    //
    //   Kyun += aur max() nahi?
    //     {3,8,5} max=8, sabko +5 → {8,13,10} max=13 = 8+5
    //     max(8,5)=8 ❌  |  8+5=13 ✅
    //
    //   max() sirf merge me: segTree[i] = max(left, right)  (build/query/refresh)
    void push(int i, int l, int r)
    {
        if (lazyAdd[i] == 0)
        {
            return; // kuch pending nahi
        }

        int add = lazyAdd[i]; // pehle save karo — niche lazyAdd[i]=0 hoga

        // RANGE ADD apply: segment max bhi utna hi badhega (× len NAHI — wo SUM ka rule)
        segTree[i] += add;

        if (l != r) // internal node — pending add bachho tak pass karo
        {
            lazyAdd[2 * i + 1] += add;
            lazyAdd[2 * i + 2] += add;
        }
        // leaf pe bachho me pass nahi — leaf = ek hi element, yahi pe apply ho gaya

        lazyAdd[i] = 0; // is node ka pending clear — ab segTree[i] updated hai
    }

    // ── update_Range: [start, end] me val add karo, parent max refresh ────────
    //   Params: i, l, r = current node; start/end = update range; val = kitna add karna hai
    //   1) pehle push(i,l,r) — purana pending apply karo
    //   2) Case 1 NO overlap (r < start || l > end) -> return
    //   3) Case 2 FULL overlap (start <= l && r <= end) -> lazyAdd[i] += val, push, return
    //   4) Case 3 PARTIAL -> mid split, dono bachho me recurse, parent max refresh (max of children)
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
        segTree[i] = max(segTree[2 * i + 1], segTree[2 * i + 2]);
    }

    // ── query_Range: [start, end] ka maximum nikaalo ──────────────────────────
    //   Params: i, l, r = current node; start/end = user ki maangi hui range
    //   1) push(i,l,r) pehle — warna pending lazy ki wajah se purana max milega
    //   2) Case 1 NO overlap (r < start || l > end) -> IDENTITY (INT_MIN) return
    //   3) Case 2 FULL overlap (start <= l && r <= end) -> seedha segTree[i] return
    //   4) Case 3 PARTIAL -> mid split, dono bachho ka max lo, unka overall max return karo
    int query_Range(int i, int l, int r, int start, int end)
    {
        push(i, l, r);
        if (r < start || l > end)
        {
            return IDENTITY;
        }
        if (start <= l && r <= end)
        {
            return segTree[i];
        }
        int mid = (l + r) / 2;
        return max(
            query_Range(2 * i + 1, l, mid, start, end),
            query_Range(2 * i + 2, mid + 1, r, start, end));
    }

public:
    // ── Constructor: segTree + lazy allocate, build se max tree ready karo ────
    //   1) n = arr.size(), segTree (IDENTITY se) aur lazy (0 se) dono 4*n size allocate
    //   2) lazy ko 0 se init karo — shuru me koi pending add nahi
    //   3) n > 0 ho to build() se max tree ready — range update + range max query dono chalenge
    MaxSeg_RangeUpdate_RangeQuery(const vector<int> &arr)
    {
        n = (int)arr.size();
        segTree.assign(4 * max(n, 1), IDENTITY);
        lazyAdd.assign(4 * max(n, 1), 0);
        if (n > 0)
        {
            build(arr, 0, 0, n - 1);
        }
    }

    // ── Public wrapper: bahar se seedha range update ──────────────────────────
    //   1) User [l, r] aur val deta hai — root (i=0, l=0, r=n-1) khud set karte hain
    //   2) Private recursive update_Range() ko call karo
    void update_Range(int l, int r, int val)
    {
        update_Range(0, 0, n - 1, l, r, val);
    }

    // ── Public wrapper: bahar se seedha range max query ───────────────────────
    //   1) User sirf [l, r] range deta hai — root params khud set karte hain
    //   2) Private recursive query_Range() se maximum return karo
    int query_Range(int l, int r)
    {
        return query_Range(0, 0, n - 1, l, r);
    }
};

int main()
{
    vector<int> arr = {5, 3, 8, 6, 1, 4, 7, 9, 2, 0};

    cout << "---- MAX | Range Update (+ADD lazy) + Range MAX Query ----\n";
    MaxSeg_RangeUpdate_RangeQuery st(arr);

    // arr = {5,3,8,6,1,4,7,9,2,0}
    st.update_Range(2, 6, 5);  // [2..6] += 5  →  {5,3,13,11,6,9,12,9,2,0}
    st.update_Range(0, 4, 10); // [0..4] += 10 →  {15,13,23,21,16,9,12,9,2,0}

    cout << "Max [0,4]: " << st.query_Range(0, 4) << " (expected 23)\n";
    cout << "Max [2,6]: " << st.query_Range(2, 6) << " (expected 23)\n";
    cout << "Max [7,9]: " << st.query_Range(7, 9) << " (expected 9)\n";

    return 0;
}
