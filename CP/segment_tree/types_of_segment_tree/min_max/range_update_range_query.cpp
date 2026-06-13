#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * OPERATION : MIN + MAX (dono ek saath)
 * VARIATION : Range Update + Range Query
 * LAZY      : YES (range add — EK lazy, dono trees sync)
 * COMPLEXITY: build O(n) | range update O(log n) | range min/max query O(log n)
 * ════════════════════════════════════════════════════════════════════════════
 * Sabse common min-max combo — range add + range min + range max dono.
 * Partial update ke baad parent refresh:
 *   miniTree[i] = min(leftMini, rightMini)
 *   maxiTree[i] = max(leftMaxi, rightMaxi)
 *
 * Yehi pattern ../min_max_segment_tree.cpp me bhi hai (parent folder).
 * ════════════════════════════════════════════════════════════════════════════
 */

class MinMaxSeg_RangeUpdate_RangeQuery
{
private:
    vector<int> miniTree, maxiTree, lazy;
    int n;
    static constexpr int MIN_ID = INT_MAX;
    static constexpr int MAX_ID = INT_MIN;

    // ── Common recursive params (ek baar padh lo) ───────────────────────────
    //   i          -> tree array me current node ka index (root = 0)
    //                   left child = 2*i + 1, right child = 2*i + 2
    //   l, r       -> ye node array ke [l, r] segment ko represent karta hai
    //   start, end -> user ne jo update/query range maangi uske left-right ends
    //   mid        -> (l + r) / 2, segment split point
    //
    // DO trees (miniTree + maxiTree) + EK shared lazy array.
    // Range add uniform hai — push pe dono trees me +lazy lagta hai.
    // Har update/query me node [l,r] vs range [start,end] — 3 case:
    //   1) NO overlap    -> update: return | query min: MIN_ID | query max: MAX_ID
    //   2) FULL overlap  -> seedha node value return ya lazy lagao
    //   3) PARTIAL       -> dono bachho me recurse, merge/refresh karo

    // ── build: dono trees ek saath banao ──────────────────────────────────
    //   1) l == r ho to leaf — miniTree[i] = maxiTree[i] = arr[l]
    //   2) mid se segment todo, left aur right child recursively build karo
    //   3) parent pe miniTree[i] = min(leftMini, rightMini)
    //   4) parent pe maxiTree[i] = max(leftMaxi, rightMaxi)
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

    // ── push: lazy add dono trees me lagao (EK shared lazy) ─────────────────
    //   1) lazy[i] == 0 ho to kuch pending nahi — return
    //   2) miniTree[i] += lazy[i] aur maxiTree[i] += lazy[i] — dono sync me update
    //   3) internal node (l != r) ho to lazy bachho ke lazy me += pass karo
    //   4) lazy[i] = 0 — pending clear, dono trees ab sahi values pe hain
    void push(int i, int l, int r)
    {
        if (lazy[i] != 0)
        {
            miniTree[i] += lazy[i];
            maxiTree[i] += lazy[i];
            if (l != r)
            {
                lazy[2 * i + 1] += lazy[i];
                lazy[2 * i + 2] += lazy[i];
            }
            lazy[i] = 0;
        }
    }

    // ── update_Range: [start, end] me +val, partial pe parent refresh ─────
    //   1) pehle push(i,l,r) — purana pending dono trees me apply karo
    //   2) Case 1 NO overlap — return
    //   3) Case 2 FULL overlap — lazy[i] += val, push, return
    //   4) Case 3 PARTIAL — dono bachho me recurse
    //   5) wapas aate waqt dono trees refresh:
    //      miniTree[i] = min(bachho ka min), maxiTree[i] = max(bachho ka max)
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
        miniTree[i] = min(miniTree[2 * i + 1], miniTree[2 * i + 2]);
        maxiTree[i] = max(maxiTree[2 * i + 1], maxiTree[2 * i + 2]);
    }

    // ── query_Min: [start, end] ka minimum nikaalo ──────────────────────────
    //   1) pehle push(i,l,r) — warna pending lazy ki wajah se purana min milega
    //   2) Case 1 NO overlap — MIN_ID (INT_MAX) return (min identity)
    //   3) Case 2 FULL overlap — seedha miniTree[i] return
    //   4) Case 3 PARTIAL — left/right dono ka min lo, chhota return karo
    int query_Min(int i, int l, int r, int start, int end)
    {
        push(i, l, r);
        if (r < start || l > end)
        {
            return MIN_ID;
        }
        if (start <= l && r <= end)
        {
            return miniTree[i];
        }
        int mid = (l + r) / 2;
        return min(
            query_Min(2 * i + 1, l, mid, start, end),
            query_Min(2 * i + 2, mid + 1, r, start, end));
    }

    // ── query_Max: [start, end] ka maximum nikaalo ──────────────────────────
    //   1) pehle push(i,l,r) — pending lazy apply karo warna max galat aayega
    //   2) Case 1 NO overlap — MAX_ID (INT_MIN) return (max identity)
    //   3) Case 2 FULL overlap — seedha maxiTree[i] return
    //   4) Case 3 PARTIAL — dono bachho ka max lo, bada return karo
    int query_Max(int i, int l, int r, int start, int end)
    {
        push(i, l, r);
        if (r < start || l > end)
        {
            return MAX_ID;
        }
        if (start <= l && r <= end)
        {
            return maxiTree[i];
        }
        int mid = (l + r) / 2;
        return max(
            query_Max(2 * i + 1, l, mid, start, end),
            query_Max(2 * i + 2, mid + 1, r, start, end));
    }

public:
    // ── MinMaxSeg_RangeUpdate_RangeQuery: constructor ──
    //   1) n = arr.size() store karo
    //   2) miniTree (MIN_ID), maxiTree (MAX_ID), lazy (0) — teeno 4*n allocate
    //   3) n > 0 ho to build() se dono trees ready karo
    //   4) Ab range add + range min + range max teeno chalenge
    MinMaxSeg_RangeUpdate_RangeQuery(const vector<int> &arr)
    {
        n = (int)arr.size();
        miniTree.assign(4 * max(n, 1), MIN_ID);
        maxiTree.assign(4 * max(n, 1), MAX_ID);
        lazy.assign(4 * max(n, 1), 0);
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

    // ── query_Min: public wrapper — bahar se seedha range min query ───────
    //   1) user [l, r] deta hai
    //   2) root se query_Min start — andar 3-case logic + lazy push handle hota hai
    int query_Min(int l, int r)
    {
        return query_Min(0, 0, n - 1, l, r);
    }

    // ── query_Max: public wrapper — bahar se seedha range max query ───────
    //   1) user [l, r] deta hai
    //   2) root se query_Max start — result directly return
    int query_Max(int l, int r)
    {
        return query_Max(0, 0, n - 1, l, r);
    }
};

int main()
{
    vector<int> arr = {5, 3, 8, 6, 1, 4, 7, 9, 2, 0};

    cout << "---- MIN+MAX | Range Update + Range Query ----\n";
    MinMaxSeg_RangeUpdate_RangeQuery st(arr);
    st.update_Range(2, 6, 5);
    st.update_Range(0, 4, 10);
    cout << "Min [0,4]: " << st.query_Min(0, 4) << " | Max [0,4]: " << st.query_Max(0, 4) << endl;
    cout << "Min [2,6]: " << st.query_Min(2, 6) << " | Max [2,6]: " << st.query_Max(2, 6) << endl;

    return 0;
}
