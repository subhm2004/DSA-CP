#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * OPERATION : MIN
 * VARIATION : Point Update + Range Query
 * LAZY      : NO
 * COMPLEXITY: build O(n) | point update O(log n) | range query O(log n)
 * ════════════════════════════════════════════════════════════════════════════
 * Ek index ki value set karo, kisi bhi [L,R] range ka minimum nikaalo.
 * Merge = min(left, right), no-overlap identity = INT_MAX.
 * ════════════════════════════════════════════════════════════════════════════
 */

class MinSeg_PointUpdate_RangeQuery
{
private:
    vector<int> segTree;
    int n;
    static constexpr int IDENTITY = INT_MAX;

    // ── Common recursive params (ek baar padh lo) ───────────────────────────
    //   i          -> tree array me current node ka index (root = 0)
    //                   left child = 2*i + 1, right child = 2*i + 2
    //   l, r       -> ye node array ke [l, r] segment ko represent karta hai
    //   start, end -> user ne jo query range maangi uske left-right ends
    //   idx        -> point update ke liye target array index
    //   mid        -> (l + r) / 2, segment ko do halves me todne ka point
    //
    // Har query me node [l,r] vs query [start,end] — 3 case:
    //   1) NO overlap    -> r < start || l > end  -> INT_MAX return (min identity)
    //   2) FULL overlap  -> start <= l && r <= end -> seedha segTree[i] return
    //   3) PARTIAL       -> thoda andar thoda bahar -> dono bachho me recurse

    // ── build: array se min segment tree banao (recursive) ──────────────────
    //   1) l == r ho to leaf hai — seedha arr[l] segTree[i] me daal do, return
    //   2) mid = (l+r)/2 se segment ko left [l,mid] aur right [mid+1,r] me todo
    //   3) left child (2*i+1) aur right child (2*i+2) dono ko recursively build karo
    //   4) parent ka min = min(left child ka min, right child ka min) — merge rule
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

    // ── update_Point: index idx ki value val set karo ───────────────────────
    //   1) l == r ho to leaf mil gaya — segTree[i] = val set karo, return
    //   2) mid nikalo, idx left half [l,mid] me hai to left child me jao
    //   3) warna right child [mid+1,r] me jao — sirf ek raasta, O(log n)
    //   4) wapas aate waqt parent ka min = min(left child, right child) refresh karo
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
        segTree[i] = min(segTree[2 * i + 1], segTree[2 * i + 2]);
    }

    // ── query_Range: [start, end] ka minimum nikaalo ──────────────────────
    //   1) Case 1 NO overlap (r < start || l > end) — INT_MAX return (min identity)
    //   2) Case 2 FULL overlap (start <= l && r <= end) — seedha segTree[i] return
    //   3) Case 3 PARTIAL — mid split, left aur right dono ka min lo, chhota return karo
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
        return min(
            query_Range(2 * i + 1, l, mid, start, end),
            query_Range(2 * i + 2, mid + 1, r, start, end));
    }

public:
    // ── MinSeg_PointUpdate_RangeQuery: constructor ──
    //   1) n = arr.size() store karo
    //   2) segTree ko 4*n size se allocate karo, sab nodes IDENTITY (INT_MAX) se init
    //   3) n > 0 ho to root (i=0) se poori array [0, n-1] par build() call karo
    //   4) Ab point update aur range min query dono ready hain
    MinSeg_PointUpdate_RangeQuery(const vector<int> &arr)
    {
        n = (int)arr.size();
        segTree.assign(4 * max(n, 1), IDENTITY);
        if (n > 0)
        {
            build(arr, 0, 0, n - 1);
        }
    }

    // ── update_Point: public wrapper — bahar se seedha point update ───────
    //   1) user sirf idx aur val deta hai
    //   2) andar wale recursive call me i=0, l=0, r=n-1 automatically pass hota hai
    void update_Point(int idx, int val)
    {
        update_Point(0, 0, n - 1, idx, val);
    }

    // ── query_Range: public wrapper — bahar se seedha range min query ─────
    //   1) user sirf [l, r] range deta hai
    //   2) root (i=0) se full array bounds [0, n-1] ke saath query_Range start hota hai
    int query_Range(int l, int r)
    {
        return query_Range(0, 0, n - 1, l, r);
    }
};

int main()
{
    vector<int> arr = {5, 3, 8, 6, 1, 4, 7, 9, 2, 0};

    cout << "---- MIN | Point Update + Range Query ----\n";
    MinSeg_PointUpdate_RangeQuery st(arr);
    cout << "Min [0,4]: " << st.query_Range(0, 4) << endl;

    st.update_Point(2, 0);
    cout << "After arr[2]=0, min [0,4]: " << st.query_Range(0, 4) << endl;
    cout << "Min [2,6]: " << st.query_Range(2, 6) << endl;

    return 0;
}
