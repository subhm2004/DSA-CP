#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * OPERATION : MIN + MAX (dono ek saath)
 * VARIATION : Point Update + Range Query
 * LAZY      : NO
 * COMPLEXITY: build O(n) | point update O(log n) | range min/max query O(log n)
 * ════════════════════════════════════════════════════════════════════════════
 * Ek hi tree me DO arrays rakhte hain:
 *   miniTree[i] → us segment ka MINIMUM
 *   maxiTree[i] → us segment ka MAXIMUM
 *
 * Kyun alag min/ max folders se better?
 *   Jab SAME array pe dono queries chahiye hon — ek build, do answers.
 *   Lazy EK hi hota hai (range update wale me); yahan lazy nahi chahiye.
 *
 * Ek index set karo → dono trees leaf pe update → parent pe min/max refresh.
 * ════════════════════════════════════════════════════════════════════════════
 */

class MinMaxSeg_PointUpdate_RangeQuery
{
private:
    vector<int> miniTree; // har node pe segment ka minimum
    vector<int> maxiTree; // har node pe segment ka maximum
    int n;
    static constexpr int MIN_ID = INT_MAX;
    static constexpr int MAX_ID = INT_MIN;

    // ── Common recursive params (ek baar padh lo) ───────────────────────────
    //   i          -> tree array me current node ka index (root = 0)
    //                   left child = 2*i + 1, right child = 2*i + 2
    //   l, r       -> ye node array ke [l, r] segment ko represent karta hai
    //   start, end -> user ne jo query range maangi uske left-right ends
    //   idx        -> point update ke liye target array index
    //   mid        -> (l + r) / 2, segment split point
    //
    // DO trees sync me chalte hain — miniTree (min) aur maxiTree (max).
    // Har query me node [l,r] vs query [start,end] — 3 case:
    //   1) NO overlap    -> min: MIN_ID (INT_MAX) | max: MAX_ID (INT_MIN)
    //   2) FULL overlap  -> seedha miniTree[i] ya maxiTree[i] return
    //   3) PARTIAL       -> dono bachho se answer lo, min/max merge karo

    // ── build: dono trees ek saath array se banao ───────────────────────────
    //   1) l == r ho to leaf — miniTree[i] = maxiTree[i] = arr[l] (ek element pe min=max)
    //   2) mid se segment todo, left aur right child dono ko recursively build karo
    //   3) parent pe miniTree[i] = min(leftMini, rightMini) merge karo
    //   4) parent pe maxiTree[i] = max(leftMaxi, rightMaxi) merge karo
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

    // ── update_Point: idx ki value val set karo — dono trees update ───────
    //   1) l == r ho to leaf — miniTree[i] = maxiTree[i] = val set karo, return
    //   2) idx left half [l,mid] me hai to left child me jao, warna right child me
    //   3) sirf ek raasta root se leaf tak — O(log n)
    //   4) wapas aate waqt dono trees refresh:
    //      miniTree[i] = min(bachho ka min), maxiTree[i] = max(bachho ka max)
    void update_Point(int i, int l, int r, int idx, int val)
    {
        if (l == r)
        {
            miniTree[i] = maxiTree[i] = val;
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
        miniTree[i] = min(miniTree[2 * i + 1], miniTree[2 * i + 2]);
        maxiTree[i] = max(maxiTree[2 * i + 1], maxiTree[2 * i + 2]);
    }

    // ── query_Min: [start, end] ka minimum nikaalo ──────────────────────────
    //   1) Case 1 NO overlap (r < start || l > end) — MIN_ID (INT_MAX) return
    //   2) Case 2 FULL overlap (start <= l && r <= end) — seedha miniTree[i] return
    //   3) Case 3 PARTIAL — left aur right dono ka min lo, chhota return karo
    int query_Min(int i, int l, int r, int start, int end)
    {
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
    //   1) Case 1 NO overlap (r < start || l > end) — MAX_ID (INT_MIN) return
    //   2) Case 2 FULL overlap (start <= l && r <= end) — seedha maxiTree[i] return
    //   3) Case 3 PARTIAL — left aur right dono ka max lo, bada return karo
    int query_Max(int i, int l, int r, int start, int end)
    {
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
    // ── MinMaxSeg_PointUpdate_RangeQuery: constructor ──
    //   1) n = arr.size() store karo
    //   2) miniTree ko MIN_ID (INT_MAX), maxiTree ko MAX_ID (INT_MIN) se 4*n allocate
    //   3) n > 0 ho to build() se dono trees ek saath ready karo
    //   4) Ab point update + range min/max query dono chalenge
    MinMaxSeg_PointUpdate_RangeQuery(const vector<int> &arr)
    {
        n = (int)arr.size();
        miniTree.assign(4 * max(n, 1), MIN_ID);
        maxiTree.assign(4 * max(n, 1), MAX_ID);
        if (n > 0)
        {
            build(arr, 0, 0, n - 1);
        }
    }

    // ── update_Point: public wrapper — bahar se seedha point update ───────
    //   1) user idx aur val deta hai
    //   2) root (i=0, l=0, r=n-1) se dono trees ek saath update hote hain
    void update_Point(int idx, int val)
    {
        update_Point(0, 0, n - 1, idx, val);
    }

    // ── query_Min: public wrapper — bahar se seedha range min query ───────
    //   1) user [l, r] deta hai
    //   2) root se query_Min start — andar 3-case logic handle hota hai
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

    cout << "---- MIN+MAX | Point Update + Range Query ----\n";
    MinMaxSeg_PointUpdate_RangeQuery st(arr);
    cout << "Min [0,4]: " << st.query_Min(0, 4) << " | Max [0,4]: " << st.query_Max(0, 4) << endl;

    st.update_Point(2, 15);
    cout << "After arr[2]=15:\n";
    cout << "  Min [0,4]: " << st.query_Min(0, 4) << " | Max [0,4]: " << st.query_Max(0, 4) << endl;
    cout << "  Min [2,6]: " << st.query_Min(2, 6) << " | Max [2,6]: " << st.query_Max(2, 6) << endl;

    return 0;
}
