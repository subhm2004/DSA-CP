#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * OPERATION : MIN + MAX (dono ek saath)
 * VARIATION : Range Update + Point Query
 * LAZY      : YES (range add — EK lazy, dono trees pe apply)
 * COMPLEXITY: build O(n) | range update O(log n) | point query O(log n)
 * ════════════════════════════════════════════════════════════════════════════
 * Range me +val add karo → har element badhta hai → min bhi +val, max bhi +val.
 * Isliye EK hi lazy array kaafi hai — push pe miniTree[i] += lazy, maxiTree[i] += lazy.
 *
 * Point query pe leaf tak jaate waqt saare pending lazy push ho jaate hain.
 * Leaf pe mini = maxi = actual value (ek element pe min aur max same).
 * ════════════════════════════════════════════════════════════════════════════
 */

class MinMaxSeg_RangeUpdate_PointQuery
{
private:
    vector<int> miniTree, maxiTree, lazyAdd;
    int n;
    static constexpr int MIN_ID = INT_MAX;
    static constexpr int MAX_ID = INT_MIN;

    // ── Common recursive params (ek baar padh lo) ───────────────────────────
    //   i          -> tree array me current node ka index (root = 0)
    //                   left child = 2*i + 1, right child = 2*i + 2
    //   l, r       -> ye node array ke [l, r] segment ko represent karta hai
    //   start, end -> user ne jo update range maangi uske left-right ends
    //   idx        -> point query ke liye target array index
    //   mid        -> (l + r) / 2, segment split point
    //
    // DO trees (miniTree + maxiTree) + EK shared lazy array.
    // Range add uniform hai — sab elements +val → min aur max dono +val.
    // Har range update me node [l,r] vs update [start,end] — 3 case:
    //   1) NO overlap    -> return
    //   2) FULL overlap  -> lazyAdd[i] += val, push, return
    //   3) PARTIAL       -> dono bachho me recurse (parent refresh nahi — point query hai)

    // ── build: dono trees array se banao ──────────────────────────────────
    //   1) l == r ho to leaf — miniTree[i] = maxiTree[i] = arr[l]
    //   2) mid se segment todo, left aur right child recursively build karo
    //   3) parent pe miniTree[i] = min(leftMini, rightMini)
    //   4) parent pe maxiTree[i] = max(leftMaxi, rightMaxi) — lazy abhi 0 hai
    void build(const vector<int> &arr, int i, int l, int r)
    {
        if (l == r)
        {
            miniTree[i] = maxiTree[i] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * i + 1, l, mid);
        build(arr, 2 * i + 2, mid + 1, r);
        miniTree[i] = min(miniTree[2 * i + 1], miniTree[2 * i + 2]);
        maxiTree[i] = max(maxiTree[2 * i + 1], maxiTree[2 * i + 2]);
    }

    // ── push: LAZY UPDATE = RANGE ADD (+v) | MERGE = min + max ───────────────
    //   ⚠️ push me min()/max() NAHI lagta — push sirf pending ADD apply karta hai!
    //   lazyAdd[i] = har element me kitna +ADD pending
    //   1) lazyAdd[i] == 0 → return
    //   2) miniTree[i] += lazyAdd[i]  AND  maxiTree[i] += lazyAdd[i]
    //   3) bachho: lazyAdd[child] += lazyAdd[i]
    //   4) lazyAdd[i] = 0
    void push(int i, int l, int r)
    {
        if (lazyAdd[i] != 0)
        {
            miniTree[i] += lazyAdd[i];
            maxiTree[i] += lazyAdd[i];
            if (l != r)
            {
                lazyAdd[2 * i + 1] += lazyAdd[i];
                lazyAdd[2 * i + 2] += lazyAdd[i];
            }
            lazyAdd[i] = 0;
        }
    }

    // ── update_Range: [start, end] me +val add karo ───────────────────────
    //   1) pehle push(i,l,r) — purana pending lazy dono trees me apply karo
    //   2) Case 1 NO overlap (r < start || l > end) — return
    //   3) Case 2 FULL overlap (start <= l && r <= end) — lazyAdd[i] += val, push, return
    //   4) Case 3 PARTIAL — mid split, dono bachho me recurse
    //      NOTE: point-query variant — wapas parent min/max refresh nahi karte
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

    // ── query_Point: index idx ki current value (mini = maxi at leaf) ───────
    //   1) har level pe push(i,l,r) — raaste ka saara pending lazy clear ho jaaye
    //   2) l == r ho to leaf — miniTree[i] hi actual value (ek element pe min=max)
    //   3) idx <= mid ho to left child me jao, warna right child me
    //   4) leaf tak pohoch ke miniTree[i] return — maxiTree[i] bhi same hoga
    int query_Point(int i, int l, int r, int idx)
    {
        push(i, l, r);
        if (l == r)
        {
            return miniTree[i];
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
    // ── MinMaxSeg_RangeUpdate_PointQuery: constructor ──
    //   1) n = arr.size() store karo
    //   2) miniTree (MIN_ID), maxiTree (MAX_ID), lazy (0) — teeno 4*n allocate
    //   3) n > 0 ho to build() se dono trees ready karo
    //   4) Ab range add update + point value query dono chalenge
    MinMaxSeg_RangeUpdate_PointQuery(const vector<int> &arr)
    {
        n = (int)arr.size();
        miniTree.assign(4 * max(n, 1), MIN_ID);
        maxiTree.assign(4 * max(n, 1), MAX_ID);
        lazyAdd.assign(4 * max(n, 1), 0);
        if (n > 0)
        {
            build(arr, 0, 0, n - 1);
        }
    }

    // ── update_Range: public wrapper — bahar se seedha range add ──────────
    //   1) user [l, r] aur val deta hai
    //   2) root (i=0, l=0, r=n-1) se EK shared lazy ke saath update start
    void update_Range(int l, int r, int val)
    {
        update_Range(0, 0, n - 1, l, r, val);
    }

    // ── query_Point: public wrapper — bahar se seedha point value query ─────
    //   1) user sirf idx deta hai
    //   2) root se leaf tak jao — raaste me saare lazy push ho jaate hain
    int query_Point(int idx)
    {
        return query_Point(0, 0, n - 1, idx);
    }
};

int main()
{
    vector<int> arr = {5, 3, 8, 6, 1, 4, 7, 9, 2, 0};

    cout << "---- MIN+MAX | Range Update + Point Query ----\n";
    MinMaxSeg_RangeUpdate_PointQuery st(arr);
    st.update_Range(2, 6, 5);
    st.update_Range(0, 4, 10);
    cout << "Value at index 2: " << st.query_Point(2) << endl;
    cout << "Value at index 5: " << st.query_Point(5) << endl;

    return 0;
}
