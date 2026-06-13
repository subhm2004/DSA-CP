#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * OPERATION : SUM
 * VARIATION : Range Update + Range Query
 * LAZY      : YES (range add lazy propagation)
 * COMPLEXITY: build O(n) | range update O(log n) | range query O(log n)
 * ════════════════════════════════════════════════════════════════════════════
 * Sabse powerful sum variation: range me add bhi karo, range ka sum bhi maango.
 * Partial update ke baad parent ka sum refresh karna zaroori hai (variation 2 se alag).
 * ════════════════════════════════════════════════════════════════════════════
 */

class SumSeg_RangeUpdate_RangeQuery
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
    //     1) NO overlap    -> r < start || l > end  (query: identity 0 return)
    //     2) FULL overlap  -> start <= l && r <= end (query: segTree[i]; update: lazy += val)
    //     3) PARTIAL        -> dono bachho me recurse karo
    //
    //   SUM tree: merge = + (jodna), no-overlap identity = 0, lazy add har element me +val
    vector<ll> segTree, lazyAdd;
    int n;

    // ── build: array se sum tree banao ────────────────────────────────────────
    //   Params: i = current node, l/r = is node ka segment range
    //   1) l == r (leaf) -> segTree[i] = arr[l], return
    //   2) mid split, left aur right child dono ko recursively build karo
    //   3) parent ka sum = left child + right child (merge = +)
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
        segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];
    }

    // ── push: LAZY UPDATE = RANGE ADD (+v) | MERGE (query) = + ───────────────
    //   ⚠️ push me merge (+) NAHI lagta — push sirf pending ADD apply karta hai!
    //   lazyAdd[i] = har element me kitna +ADD pending hai
    //   1) lazyAdd[i] == 0 → return
    //   2) segTree[i] += lazyAdd[i] * (r - l + 1)   ← SUM rule: × length
    //   3) bachho: lazyAdd[child] += lazyAdd[i]
    //   4) lazyAdd[i] = 0
    void push(int i, int l, int r)
    {
        if (lazyAdd[i] != 0)
        {
            segTree[i] += (r - l + 1) * lazyAdd[i];
            if (l != r)
            {
                lazyAdd[2 * i + 1] += lazyAdd[i];
                lazyAdd[2 * i + 2] += lazyAdd[i];
            }
            lazyAdd[i] = 0;
        }
    }

    // ── update_Range: [start, end] me 'val' add karo ──────────────────────────
    //   Params: i, l, r = current node; start/end = update range; val = kitna add karna hai
    //   1) pehle push(i,l,r) — purana pending apply karo
    //   2) Case 1 NO overlap (r < start || l > end) -> return
    //   3) Case 2 FULL overlap (start <= l && r <= end) -> lazyAdd[i] += val, push, return
    //   4) Case 3 PARTIAL -> mid split, dono bachho me recurse, parent sum refresh (left + right)
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
        push(2 * i + 1, l, mid);       // partial ke baad bachho ka lazy pehle apply — stale segTree fix
        push(2 * i + 2, mid + 1, r);
        segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];
    }

    // ── query_Range: [start, end] ka sum nikaalo (lazy apply karte hue) ───────
    //   Params: i, l, r = current node; start/end = user ki maangi hui range
    //   1) push(i,l,r) pehle — warna pending lazy ki wajah se purana sum milega
    //   2) Case 1 NO overlap (r < start || l > end) -> identity 0 return
    //   3) Case 2 FULL overlap (start <= l && r <= end) -> seedha segTree[i] return
    //   4) Case 3 PARTIAL -> mid split, dono bachho ka sum lo aur jod do (+ merge)
    ll query_Range(int i, int l, int r, int start, int end)
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
        return query_Range(2 * i + 1, l, mid, start, end)
             + query_Range(2 * i + 2, mid + 1, r, start, end);
    }

public:
    // ── Constructor: segTree + lazy allocate, build se tree ready karo ────────
    //   1) n = arr.size(), segTree aur lazy dono ko 4*n size allocate karo
    //   2) lazy ko 0 se init karo — shuru me koi pending add nahi
    //   3) n > 0 ho to build() se sum tree ready — range update + range query dono chalenge
    SumSeg_RangeUpdate_RangeQuery(const vector<int> &arr)
    {
        n = (int)arr.size();
        segTree.resize(4 * max(n, 1));
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

    // ── Public wrapper: bahar se seedha range sum query ───────────────────────
    //   1) User sirf [l, r] range deta hai — root params khud set karte hain
    //   2) Private recursive query_Range() se total sum return karo
    ll query_Range(int l, int r)
    {
        return query_Range(0, 0, n - 1, l, r);
    }
};

int main()
{
    vector<int> arr = {5, 3, 8, 6, 1, 4, 7, 9, 2, 0};

    cout << "---- SUM | Range Update + Range Query ----\n";
    SumSeg_RangeUpdate_RangeQuery st(arr);
    st.update_Range(2, 6, 5);
    st.update_Range(0, 4, 10);
    cout << "Sum [0,4]: " << st.query_Range(0, 4) << endl;
    cout << "Sum [2,6]: " << st.query_Range(2, 6) << endl;

    return 0;
}
