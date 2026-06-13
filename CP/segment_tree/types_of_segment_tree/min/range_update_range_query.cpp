#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * OPERATION : MIN
 * VARIATION : Range Update + Range Query
 * LAZY      : YES (range ADD lazy — lazyAdd = pending +ADD, MIN value nahi!)
 * COMPLEXITY: build O(n) | range update O(log n) | range query O(log n)
 * ════════════════════════════════════════════════════════════════════════════
 * segTree[i] = segment MIN | lazyAdd[i] = kitna +ADD pending hai
 * push: segTree[i] += lazyAdd[i]  (uniform add → min bhi +lazyAdd; SUM jaisa ×len NAHI)
 * Partial update ke baad parent min refresh = min(left, right).
 * ════════════════════════════════════════════════════════════════════════════
 */

class MinSeg_RangeUpdate_RangeQuery
{
private:
    vector<int> segTree, lazyAdd;
    int n;
    static constexpr int IDENTITY = INT_MAX;

    // ── Common recursive params (ek baar padh lo) ───────────────────────────
    //   i          -> tree array me current node ka index (root = 0)
    //                   left child = 2*i + 1, right child = 2*i + 2
    //   l, r       -> ye node array ke [l, r] segment ko represent karta hai
    //   start, end -> user ne jo update/query range maangi uske left-right ends
    //   mid        -> (l + r) / 2, segment split point
    //
    // Har update/query me node [l,r] vs range [start,end] — 3 case:
    //   1) NO overlap    -> r < start || l > end
    //   2) FULL overlap  -> start <= l && r <= end
    //   3) PARTIAL       -> thoda andar thoda bahar -> dono bachho me recurse

    // ── build: array se min tree banao ──────────────────────────────────────
    //   1) l == r ho to leaf — segTree[i] = arr[l], return
    //   2) mid se segment todo, left aur right child recursively build karo
    //   3) parent ka min = min(left child, right child) merge karo
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
        segTree[i] = min(segTree[2 * i + 1], segTree[2 * i + 2]);
    }

    // ── push: LAZY UPDATE = RANGE ADD (+v) | MERGE (query) = min ─────────
    //   ⚠️ push me merge (min) NAHI lagta — push sirf pending ADD apply karta hai!
    //   lazyAdd[i] = har element me kitna +ADD pending (MAX/MIN value NAHI!)
    //   1) lazyAdd[i] == 0 → return
    //   2) segTree[i] += lazyAdd[i]   ← MIN rule: sirf ek baar (× len NAHI!)
    //   3) bachho: lazyAdd[child] += lazyAdd[i]
    //   4) lazyAdd[i] = 0
    void push(int i, int l, int r)
    {
        if (lazyAdd[i] != 0)
        {
            segTree[i] += lazyAdd[i];
            if (l != r)
            {
                lazyAdd[2 * i + 1] += lazyAdd[i];
                lazyAdd[2 * i + 2] += lazyAdd[i];
            }
            lazyAdd[i] = 0;
        }
    }

    // ── update_Range: [start, end] me val add karo, parent min refresh ──────
    //   1) pehle push(i,l,r) — purana pending apply karo
    //   2) Case 1 NO overlap — return, kuch mat karo
    //   3) Case 2 FULL overlap — lazyAdd[i] += val, push, return
    //   4) Case 3 PARTIAL — dono bachho me recurse
    //   5) wapas aate waqt parent ka min = min(left child, right child) refresh karo
    //      (range query bhi karni hai isliye parent update zaroori hai)
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
        segTree[i] = min(segTree[2 * i + 1], segTree[2 * i + 2]);
    }

    // ── query_Range: [start, end] ka minimum nikaalo ──────────────────────
    //   1) pehle push(i,l,r) — warna pending lazy ki wajah se purana min milega
    //   2) Case 1 NO overlap — INT_MAX return (min identity, merge me ignore)
    //   3) Case 2 FULL overlap — seedha segTree[i] return, aur recurse nahi
    //   4) Case 3 PARTIAL — left/right dono ka min lo, chhota return karo
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
        return min(
            query_Range(2 * i + 1, l, mid, start, end),
            query_Range(2 * i + 2, mid + 1, r, start, end));
    }

public:
    // ── MinSeg_RangeUpdate_RangeQuery: constructor ──
    //   1) n = arr.size() store karo
    //   2) segTree (IDENTITY) aur lazy (0) dono 4*n size allocate karo
    //   3) n > 0 ho to build() se min tree ready karo
    //   4) Ab range add update + range min query dono chalenge
    MinSeg_RangeUpdate_RangeQuery(const vector<int> &arr)
    {
        n = (int)arr.size();
        segTree.assign(4 * max(n, 1), IDENTITY);
        lazyAdd.assign(4 * max(n, 1), 0);
        if (n > 0)
        {
            build(arr, 0, 0, n - 1);
        }
    }

    // ── update_Range: public wrapper — bahar se seedha range add ──────────
    //   1) user [l, r] aur val deta hai
    //   2) root (i=0, l=0, r=n-1) se recursive update start hota hai
    void update_Range(int l, int r, int val)
    {
        update_Range(0, 0, n - 1, l, r, val);
    }

    // ── query_Range: public wrapper — bahar se seedha range min query ─────
    //   1) user [l, r] deta hai
    //   2) root se query_Range call — andar 3-case logic + lazy push handle hota hai
    int query_Range(int l, int r)
    {
        return query_Range(0, 0, n - 1, l, r);
    }
};

int main()
{
    vector<int> arr = {5, 3, 8, 6, 1, 4, 7, 9, 2, 0};

    cout << "---- MIN | Range Update (+ADD lazy) + Range MIN Query ----\n";
    MinSeg_RangeUpdate_RangeQuery st(arr);
    st.update_Range(2, 6, 5);
    st.update_Range(0, 4, 10);
    cout << "Min [0,4]: " << st.query_Range(0, 4) << " (expected 13)\n";
    cout << "Min [2,6]: " << st.query_Range(2, 6) << " (expected 9)\n";

    return 0;
}
