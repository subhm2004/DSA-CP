#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * OPERATION : MIN
 * VARIATION : Range Update + Point Query
 * LAZY      : YES (range add — har element me +val)
 * COMPLEXITY: build O(n) | range update O(log n) | point query O(log n)
 * ════════════════════════════════════════════════════════════════════════════
 * Poori range me +val add karo, ek index ki current value maango.
 * Range add se sab elements badhte hain — segment min bhi +val se badhega.
 * ════════════════════════════════════════════════════════════════════════════
 */

class MinSeg_RangeUpdate_PointQuery
{
private:
    vector<int> segTree, lazy;
    int n;
    static constexpr int IDENTITY = INT_MAX;

    // ── Common recursive params (ek baar padh lo) ───────────────────────────
    //   i          -> tree array me current node ka index (root = 0)
    //                   left child = 2*i + 1, right child = 2*i + 2
    //   l, r       -> ye node array ke [l, r] segment ko represent karta hai
    //   start, end -> user ne jo update range maangi uske left-right ends
    //   idx        -> point query ke liye target array index
    //   mid        -> (l + r) / 2, segment split point
    //
    // Har range update me node [l,r] vs update [start,end] — 3 case:
    //   1) NO overlap    -> r < start || l > end  -> kuch mat karo, return
    //   2) FULL overlap  -> start <= l && r <= end -> lazy[i] += val, push, return
    //   3) PARTIAL       -> dono bachho me recurse (yaha parent refresh nahi — point query hai)

    // ── build: array se min tree banao ──────────────────────────────────────
    //   1) l == r ho to leaf — segTree[i] = arr[l], return
    //   2) mid se left aur right halves me todo, dono bachho ko build karo
    //   3) parent ka min = min(left child, right child) — lazy abhi 0 hi rehta hai
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

    // ── push: pending lazy add apply karo aur bachho ko pass karo ───────────
    //   1) lazy[i] == 0 ho to kuch pending nahi — seedha return
    //   2) segTree[i] += lazy[i] — range add se poore segment ka min +lazy se badhega
    //   3) leaf nahi (l != r) ho to wahi lazy dono bachho ke lazy me += karo
    //   4) apna lazy[i] = 0 kar do — ab ye node up-to-date, pending clear
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

    // ── update_Range: [start, end] me har element me val add karo ───────────
    //   1) pehle push(i,l,r) — is node pe purana pending lazy apply karo
    //   2) Case 1 NO overlap (r < start || l > end) — ye subtree bahar hai, return
    //   3) Case 2 FULL overlap (start <= l && r <= end) — lazy[i] += val, push, return
    //   4) Case 3 PARTIAL — mid split, dono bachho me recurse
    //      NOTE: point-query variant hai — wapas parent min refresh nahi karte
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
    }

    // ── query_Point: index idx ki current value kya hai ─────────────────────
    //   1) har level pe push(i,l,r) — raaste ka saara pending lazy apply ho jaaye
    //   2) l == r ho to leaf mil gaya — segTree[i] hi actual value hai, return
    //   3) idx <= mid ho to left child me jao, warna right child me jao
    //   4) leaf tak pohoch ke value return — koi merge nahi chahiye
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
    // ── MinSeg_RangeUpdate_PointQuery: constructor ──
    //   1) n = arr.size() store karo
    //   2) segTree ko IDENTITY (INT_MAX) se, lazy ko 0 se 4*n size allocate karo
    //   3) n > 0 ho to build() se initial array values tree me daal do
    //   4) Ab range add update aur point value query dono ready hain
    MinSeg_RangeUpdate_PointQuery(const vector<int> &arr)
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
    //   2) root (i=0, l=0, r=n-1) se recursive update_Range start hota hai
    void update_Range(int l, int r, int val)
    {
        update_Range(0, 0, n - 1, l, r, val);
    }

    // ── query_Point: public wrapper — bahar se seedha point value query ─────
    //   1) user sirf idx deta hai
    //   2) root se leaf tak jao, raaste me saare lazy push ho jaate hain
    int query_Point(int idx)
    {
        return query_Point(0, 0, n - 1, idx);
    }
};

int main()
{
    vector<int> arr = {5, 3, 8, 6, 1, 4, 7, 9, 2, 0};

    cout << "---- MIN | Range Update + Point Query ----\n";
    MinSeg_RangeUpdate_PointQuery st(arr);
    st.update_Range(2, 6, 5);
    st.update_Range(0, 4, 10);
    cout << "Value at index 2: " << st.query_Point(2) << endl;
    cout << "Value at index 5: " << st.query_Point(5) << endl;

    return 0;
}
