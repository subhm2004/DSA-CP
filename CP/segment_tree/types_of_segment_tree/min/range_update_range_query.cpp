#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * OPERATION : MIN
 * VARIATION : Range Update + Range Query
 * LAZY      : YES (range add lazy propagation)
 * COMPLEXITY: build O(n) | range update O(log n) | range query O(log n)
 * ════════════════════════════════════════════════════════════════════════════
 * Range me +val add karo aur range ka min bhi maango.
 * Partial update ke baad parent ka min refresh karna zaroori hai.
 * ════════════════════════════════════════════════════════════════════════════
 */

class MinSeg_RangeUpdate_RangeQuery
{
private:
    vector<int> segTree, lazy;
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

    // ── push: lazy add apply karo — segment min bhi +lazy se badhega ────────
    //   1) lazy[i] == 0 ho to kuch pending nahi — return
    //   2) segTree[i] += lazy[i] — uniform range add se min bhi utna hi badhega
    //   3) internal node (l != r) ho to lazy bachho ke lazy me += pass karo
    //   4) lazy[i] = 0 — apna pending clear, node ab sahi value pe hai
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

    // ── update_Range: [start, end] me val add karo, parent min refresh ──────
    //   1) pehle push(i,l,r) — purana pending apply karo
    //   2) Case 1 NO overlap — return, kuch mat karo
    //   3) Case 2 FULL overlap — lazy[i] += val, push, return
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
            lazy[i] += val;
            push(i, l, r);
            return;
        }
        int mid = (l + r) / 2;
        update_Range(2 * i + 1, l, mid, start, end, val);
        update_Range(2 * i + 2, mid + 1, r, start, end, val);
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
        lazy.assign(4 * max(n, 1), 0);
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

    cout << "---- MIN | Range Update + Range Query ----\n";
    MinSeg_RangeUpdate_RangeQuery st(arr);
    st.update_Range(2, 6, 5);
    st.update_Range(0, 4, 10);
    cout << "Min [0,4]: " << st.query_Range(0, 4) << endl;
    cout << "Min [2,6]: " << st.query_Range(2, 6) << endl;

    return 0;
}
