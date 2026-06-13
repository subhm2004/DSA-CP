#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * OPERATION : MAX
 * VARIATION : Point Update + Range Query
 * LAZY      : NO
 * COMPLEXITY: build O(n) | point update O(log n) | range query O(log n)
 * ════════════════════════════════════════════════════════════════════════════
 * Ek index ki value set karo, kisi bhi [L,R] range ka maximum nikaalo.
 * Merge = max(left, right), no-overlap identity = INT_MIN.
 * ════════════════════════════════════════════════════════════════════════════
 */

class MaxSeg_PointUpdate_RangeQuery
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
    //     1) NO overlap    -> r < start || l > end  (identity return: max ke liye INT_MIN)
    //     2) FULL overlap  -> start <= l && r <= end (seedha segTree[i] use karo)
    //     3) PARTIAL        -> dono bachho me recurse karo, max(leftAns, rightAns)
    //
    //   MAX tree: merge = max(), no-overlap identity = INT_MIN
    vector<int> segTree;
    int n;
    static constexpr int IDENTITY = INT_MIN; // no overlap me ye return hota hai

    // ── build: array se max segment tree banao ──────────────────────────────
    //   Params: i = current node index, l/r = is node ka segment range
    //   1) l == r (leaf) -> segTree[i] = arr[l], return
    //   2) mid = (l+r)/2, left child [l,mid] aur right child [mid+1,r] dono build karo
    //   3) parent ka max merge karo: segTree[i] = max(left child, right child)
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

    // ── update_Point: index idx ki value val set karo ─────────────────────────
    //   Params: i, l, r = current node; idx = jis index pe set karna hai; val = nayi value
    //   1) l == r -> leaf mil gaya (yahi wo index hai), segTree[i] = val, return
    //   2) mid split — idx <= mid ho to left child me jao, warna right child me
    //   3) wapas aate waqt parent ka max refresh: max(left child, right child)
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
        segTree[i] = max(segTree[2 * i + 1], segTree[2 * i + 2]);
    }

    // ── query_Range: [start, end] ka maximum nikaalo ────────────────────────
    //   Params: i, l, r = current node; start/end = user ki maangi hui range
    //   1) Case 1 NO overlap (r < start || l > end) -> IDENTITY (INT_MIN) return
    //   2) Case 2 FULL overlap (start <= l && r <= end) -> seedha segTree[i] return karo
    //   3) Case 3 PARTIAL -> mid split, dono bachho ka max lo, unka overall max return karo
    int query_Range(int i, int l, int r, int start, int end)
    {
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
    // ── Constructor: n allocate karo aur build() se max tree ready karo ─────
    //   1) n = arr.size(), segTree ko 4*n size allocate, sab nodes IDENTITY se init
    //   2) n > 0 ho to root (i=0) se poori array [0, n-1] par build() call karo
    //   3) Ab point update aur range max query dono ready hain
    MaxSeg_PointUpdate_RangeQuery(const vector<int> &arr)
    {
        n = (int)arr.size();
        segTree.assign(4 * max(n, 1), IDENTITY);
        if (n > 0)
        {
            build(arr, 0, 0, n - 1);
        }
    }

    // ── Public wrapper: bahar se seedha point update ────────────────────────
    //   1) User sirf idx aur val deta hai — root (i=0, l=0, r=n-1) khud set karte hain
    //   2) Private recursive update_Point() ko call karo
    void update_Point(int idx, int val)
    {
        update_Point(0, 0, n - 1, idx, val);
    }

    // ── Public wrapper: bahar se seedha range max query ─────────────────────
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

    cout << "---- MAX | Point Update + Range Query ----\n";
    MaxSeg_PointUpdate_RangeQuery st(arr);
    cout << "Max [0,4]: " << st.query_Range(0, 4) << endl;

    st.update_Point(2, 15);
    cout << "After arr[2]=15, max [0,4]: " << st.query_Range(0, 4) << endl;
    cout << "Max [2,6]: " << st.query_Range(2, 6) << endl;

    return 0;
}
