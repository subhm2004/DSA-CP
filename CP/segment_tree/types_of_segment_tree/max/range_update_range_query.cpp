#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * OPERATION : MAX
 * VARIATION : Range Update + Range Query
 * LAZY      : YES (range add lazy propagation)
 * COMPLEXITY: build O(n) | range update O(log n) | range query O(log n)
 * ════════════════════════════════════════════════════════════════════════════
 * Range me +val add karo aur range ka max bhi maango.
 * Partial update ke baad parent ka max refresh karna zaroori hai.
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
    //   MAX tree: merge = max(), identity = INT_MIN, lazy add se segment max +lazy se badhega
    vector<int> segTree, lazy;
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

    // ── push: lazy add apply karo — segment max bhi +lazy se badhega ──────────
    //   Params: i = current node, l/r = is node ka segment range
    //   1) lazy[i] == 0 ho to kuch pending nahi — seedha return
    //   2) segTree[i] += lazy[i] — range add se har element +lazy badhta hai, max bhi +lazy badhega
    //   3) leaf nahi (l != r) to wahi lazy dono bachho ke lazy me += karo
    //   4) apna lazy[i] = 0 kar do — pending clear
    void push(int i, int l, int r)
    {
        if (lazy[i] != 0)
        {
            segTree[i] += lazy[i];
            if (l != r)
            {
                lazy[2 * i + 1] += lazy[i];
                lazy[2 * i + 2] += lazy[i];
            }
            lazy[i] = 0;
        }
    }

    // ── update_Range: [start, end] me val add karo, parent max refresh ────────
    //   Params: i, l, r = current node; start/end = update range; val = kitna add karna hai
    //   1) pehle push(i,l,r) — purana pending apply karo
    //   2) Case 1 NO overlap (r < start || l > end) -> return
    //   3) Case 2 FULL overlap (start <= l && r <= end) -> lazy[i] += val, push, return
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
            lazy[i] += val;
            push(i, l, r);
            return;
        }
        int mid = (l + r) / 2;
        update_Range(2 * i + 1, l, mid, start, end, val);
        update_Range(2 * i + 2, mid + 1, r, start, end, val);
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
        lazy.assign(4 * max(n, 1), 0);
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

    cout << "---- MAX | Range Update + Range Query ----\n";
    MaxSeg_RangeUpdate_RangeQuery st(arr);
    st.update_Range(2, 6, 5);
    st.update_Range(0, 4, 10);
    cout << "Max [0,4]: " << st.query_Range(0, 4) << endl;
    cout << "Max [2,6]: " << st.query_Range(2, 6) << endl;

    return 0;
}
