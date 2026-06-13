#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * OPERATION : SUM
 * VARIATION : Range Update + Point Query
 * LAZY      : YES (range add lazy propagation)
 * COMPLEXITY: build O(n) | range update O(log n) | point query O(log n)
 * ════════════════════════════════════════════════════════════════════════════
 * Poori range [L,R] me +val add karo, kisi ek index ki current value maango.
 * Lazy array pending add store karta hai — har baar poori range walk nahi karni padti.
 * ════════════════════════════════════════════════════════════════════════════
 */

class SumSeg_RangeUpdate_PointQuery
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
    //     1) NO overlap    -> r < start || l > end  (kuch mat karo, seedha return)
    //     2) FULL overlap  -> start <= l && r <= end (lazyAdd[i] += val, push karo)
    //     3) PARTIAL        -> dono bachho me recurse karo
    //
    //   SUM tree: merge = + (jodna), lazy add har element me +val lagata hai
    vector<ll> segTree, lazyAdd; // segTree = sum, lazy = pending add jo bachho tak nahi pahuncha
    int n;

    // ── build: array se sum tree banao (lazy shuru me 0 rehta hai) ───────────
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

    // ── update_Range: [start, end] ke har element me 'val' add karo ───────────
    //   Params: i, l, r = current node; start/end = update range; val = kitna add karna hai
    //   1) pehle push(i,l,r) — is node pe purana pending apply karo
    //   2) Case 1 NO overlap (r < start || l > end) -> kuch mat karo, return
    //   3) Case 2 FULL overlap (start <= l && r <= end) -> lazyAdd[i] += val, push, return
    //   4) Case 3 PARTIAL -> mid split, dono bachho me recurse (parent sum refresh NAHI — sirf point query chahiye)
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

    // ── query_Point: index 'idx' ki current value kya hai ───────────────────
    //   Params: i, l, r = current node; idx = jis index ki value chahiye
    //   1) push(i,l,r) — raaste me saara pending lazy apply karo
    //   2) l == r (leaf) -> segTree[i] return (ek element ki value = uska sum)
    //   3) idx <= mid ho to left child me jao, warna right child me recurse karo
    ll query_Point(int i, int l, int r, int idx)
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
    // ── Constructor: segTree + lazy dono allocate, build se init ────────────
    //   1) n = arr.size(), segTree aur lazy dono ko 4*n size allocate karo
    //   2) lazy ko 0 se init karo — shuru me koi pending add nahi
    //   3) n > 0 ho to build() se initial array values tree me daal do
    SumSeg_RangeUpdate_PointQuery(const vector<int> &arr)
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

    // ── Public wrapper: bahar se seedha point query ───────────────────────────
    //   1) User sirf idx deta hai — root params khud set karte hain
    //   2) Private recursive query_Point() se us index ki current value return karo
    ll query_Point(int idx)
    {
        return query_Point(0, 0, n - 1, idx);
    }
};

int main()
{
    vector<int> arr = {5, 3, 8, 6, 1, 4, 7, 9, 2, 0};

    cout << "---- SUM | Range Update + Point Query ----\n";
    SumSeg_RangeUpdate_PointQuery st(arr);
    st.update_Range(2, 6, 5);  // [2,6] me +5
    st.update_Range(0, 4, 10); // [0,4] me +10
    cout << "Value at index 2: " << st.query_Point(2) << endl;
    cout << "Value at index 5: " << st.query_Point(5) << endl;

    return 0;
}
