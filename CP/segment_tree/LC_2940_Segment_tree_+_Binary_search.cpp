#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * LC 2940 — Find Building Where Alice and Bob Can Meet
 * Pattern : Segment Tree (Range Max INDEX) + Binary Search on Answer
 * ════════════════════════════════════════════════════════════════════════════
 *
 * PROBLEM (short):
 *   heights[i] = building i ki height
 *   Query (a, b): Alice building a se, Bob building b se start karte hain.
 *   Dono ko ek COMMON building j par milna hai jahan:
 *     heights[j] > heights[a]  AND  heights[j] > heights[b]
 *   Chahiye: sabse LEFT (chhota index) wala valid j.
 *   Agar nahi mila to -1.
 *
 * KEY INSIGHT:
 *   1) Agar a == b ya heights[max(a,b)] > heights[min(a,b)]
 *      → seedha max(a,b) answer (bob wali building pe hi mil sakte hain)
 *
 *   2) Warna humein range [max(a,b)+1, n-1] mein LEFTmost index chahiye
 *      jahan height > dono heights se.
 *
 *   3) "Leftmost valid index" = BINARY SEARCH on index
 *      + har step pe check: [l, mid] mein koi valid building hai?
 *
 *   4) Range check ke liye SEGMENT TREE:
 *      Har node apne segment ka MAX HEIGHT wale building ka INDEX store kare.
 *      Query [ql, qr] → us range mein sabse lambi building ka index.
 *
 * COMPLEXITY:
 *   Build  : O(n)
 *   Per query: O(log n) binary search × O(log n) seg query = O(log² n)
 *   Total  : O(n + q log² n)
 *
 * ════════════════════════════════════════════════════════════════════════════
 * SIMILAR LEETCODE PATTERNS (Segment Tree + Binary Search / Range Query)
 * ════════════════════════════════════════════════════════════════════════════
 *
 * ┌──────────┬────────────────────────────────────────┬─────────────────────┐
 * │ LC #     │ Title                                  │ Pattern             │
 * ├──────────┼────────────────────────────────────────┼─────────────────────┤
 * │ 2940     │ Find Building Where Alice & Bob Meet     │ ★ YEHI FILE —       │
 * │          │                                        │ Seg(max idx) + BS   │
 * ├──────────┼────────────────────────────────────────┼─────────────────────┤
 * │ 2407     │ Longest Increasing Subsequence II      │ Seg tree on VALUES  │
 * │          │                                        │ range max + coord.  │
 * │          │                                        │ compression         │
 * ├──────────┼────────────────────────────────────────┼─────────────────────┤
 * │ 2426     │ Number of Pairs Satisfying Inequality  │ Seg tree / BIT +    │
 * │          │                                        │ offline sort        │
 * ├──────────┼────────────────────────────────────────┼─────────────────────┤
 * │ 2736     │ Maximum Sum Queries                    │ Offline queries +   │
 * │          │                                        │ sorted + BIT/seg    │
 * ├──────────┼────────────────────────────────────────┼─────────────────────┤
 * │ 2926     │ Maximum Balanced Subsequence Sum       │ Seg tree + DP on    │
 * │          │                                        │ compressed values   │
 * ├──────────┼────────────────────────────────────────┼─────────────────────┤
 * │ 715      │ Range Module                           │ Dynamic seg tree —  │
 * │          │                                        │ range add/remove    │
 * ├──────────┼────────────────────────────────────────┼─────────────────────┤
 * │ 2276     │ Count Integers in Intervals            │ Seg tree / merge    │
 * │          │                                        │ intervals           │
 * ├──────────┼────────────────────────────────────────┼─────────────────────┤
 * │ 218      │ The Skyline Problem                    │ Seg tree + sweep    │
 * │          │                                        │ line (max in range) │
 * ├──────────┼────────────────────────────────────────┼─────────────────────┤
 * │ 699      │ Falling Squares                        │ Seg tree range max  │
 * │          │                                        │ (lazy / coord comp) │
 * ├──────────┼────────────────────────────────────────┼─────────────────────┤
 * │ 307      │ Range Sum Query — Mutable                │ Classic seg tree    │
 * │          │                                        │ (base template)     │
 * ├──────────┼────────────────────────────────────────┼─────────────────────┤
 * │ 904      │ Fruit Into Baskets                       │ Sliding Window —    │
 * │          │                                        │ max 2 types (alag   │
 * │          │                                        │ pattern, same family)│
 * ├──────────┼────────────────────────────────────────┼─────────────────────┤
 * │ 3477     │ Fruits Into Baskets II                   │ Brute simulation —  │
 * │          │                                        │ leftmost basket     │
 * │          │                                        │ dhundho O(n²)       │
 * ├──────────┼────────────────────────────────────────┼─────────────────────┤
 * │ 3479     │ Fruits Into Baskets III                  │ ★ SAME PATTERN —    │
 * │          │                                        │ Seg(range max) + BS │
 * │          │                                        │ leftmost basket j   │
 * │          │                                        │ jahan capacity >= x │
 * │          │                                        │ phir basket use=0   │
 * ├──────────┼────────────────────────────────────────┼─────────────────────┤
 * │ —        │ K-th Smallest in Range (CP)            │ Merge Sort Tree +   │
 * │          │ (k_smallest_number_in_range.cpp)       │ BS on answer        │
 * └──────────┴────────────────────────────────────────┴─────────────────────┘
 *
 * FRUITS INTO BASKETS SERIES (detail):
 * ───────────────────────────────────
 *   LC 904  → classic sliding window (at most 2 fruit TYPES in row)
 *   LC 3477 → II: har fruit ke liye leftmost free basket (capacity >= fruit)
 *               brute: nested loop O(n²) — chhote n ke liye kaafi
 *   LC 3479 → III: SAME problem as 3477, lekin n bada → Seg Tree + BS
 *               seg tree range MAX capacity rakhta hai
 *               BS se leftmost index jahan baskets[i] >= fruit
 *               mil gaya to update(i, 0) — basket used mark
 *
 *   3479 vs 2940 comparison:
 *     2940  → leftmost j where heights[j] > h[a] AND heights[j] > h[b]
 *     3479  → leftmost j where baskets[j] >= fruit (unused)
 *     Dono  → "leftmost valid index" + seg tree range query + binary search
 *
 * YAAD RAKHNE WALI LINE:
 *   "Leftmost / rightmost index dhundna ho jahan range mein koi
 *    condition satisfy ho → Binary Search on index + Segment Tree
 *    se O(log n) mein range check."
 *
 * ════════════════════════════════════════════════════════════════════════════
 */

class SegmentTree {
private:
    vector<int> segTree; // segTree[i] = is segment ka MAX height wale element ka INDEX
    vector<int> arr;     // original heights array (update ke liye copy rakhi hai)
    int n;

    /*
     * build(i, l, r)
     * ----------------
     * Har node par us segment [l,r] mein sabse ZYADA height wale
     * building ka INDEX store karo (value nahi, INDEX!).
     *
     * Kyun index? Kyunki answer mein humein position chahiye,
     * aur compare heights[idx] se karenge.
     *
     * Leaf: segTree[i] = l (khud ka index)
     * Internal: left aur right child ke indices compare → jinka arr[idx] bada
     */
    void build(int i, int l, int r) {
        if (l == r) {
            segTree[i] = l;
            return;
        }

        int mid = l + (r - l) / 2;
        build(2 * i + 1, l, mid);
        build(2 * i + 2, mid + 1, r);

        int leftIdx = segTree[2 * i + 1];
        int rightIdx = segTree[2 * i + 2];
        segTree[i] = (arr[leftIdx] >= arr[rightIdx]) ? leftIdx : rightIdx;
    }

    /*
     * query(i, l, r, ql, qr) → range [ql, qr] mein max height wala INDEX
     *
     * 3 cases (classic segment tree):
     *   1) No overlap     → -1
     *   2) Full overlap   → segTree[i] (poora segment query ke andar)
     *   3) Partial overlap → left + right merge, jiska height zyada
     */
    int query(int i, int l, int r, int ql, int qr) {
        if (r < ql || l > qr)
            return -1;
        if (ql <= l && r <= qr)
            return segTree[i];

        int mid = l + (r - l) / 2;
        int left = query(2 * i + 1, l, mid, ql, qr);
        int right = query(2 * i + 2, mid + 1, r, ql, qr);

        if (left == -1)  return right;
        if (right == -1) return left;
        return (arr[left] >= arr[right]) ? left : right;
    }

    /*
     * update(i, l, r, idx, value)
     * Point update — heights[idx] change ho to tree refresh
     * Leaf tak jao, wapas aate waqt parent mein max index update
     */
    void update(int i, int l, int r, int idx, int value) {
        if (l == r) {
            arr[idx] = value;
            segTree[i] = idx;
            return;
        }

        int mid = l + (r - l) / 2;
        if (idx <= mid)
            update(2 * i + 1, l, mid, idx, value);
        else
            update(2 * i + 2, mid + 1, r, idx, value);

        int leftIdx = segTree[2 * i + 1];
        int rightIdx = segTree[2 * i + 2];
        segTree[i] = (arr[leftIdx] >= arr[rightIdx]) ? leftIdx : rightIdx;
    }

public:
    SegmentTree(const vector<int>& input) {
        arr = input;
        n = arr.size();
        segTree.resize(4 * n);
        build(0, 0, n - 1);
    }

    // Public wrappers — recursive calls ko simple banao
    int query(int l, int r) { return query(0, 0, n - 1, l, r); }
    void update(int idx, int value) { update(0, 0, n - 1, idx, value); }
    int get(int idx) const { return arr[idx]; }
};

class Solution {
public:
  /*
   * leftmostBuildingQueries(heights, queries)
   * -----------------------------------------
   * Har query (a, b) ke liye leftmost meeting building dhundo.
   *
   * STEP A — trivial cases (segment tree ki zaroorat nahi):
   *   alice = min(a,b), bob = max(a,b)
   *   • a == b           → same building, answer = a
   *   • heights[bob] > heights[alice] → bob ki building dono se lambi hai,
   *                                       wahi milne ki jagah → answer = bob
   *
   * STEP B — hard case:
   *   Dono ko bob se aage kisi building par jana padega.
   *   Search space: indices [bob+1, n-1]
   *   Chahiye: LEFTmost index j where:
   *     heights[j] > heights[a]  AND  heights[j] > heights[b]
   *
   * STEP C — Binary Search on index (leftmost dhundna):
   *   l = bob+1, r = n-1, ans = INF
   *   while l <= r:
   *     mid = (l+r)/2
   *     idx = seg.query(l, mid)   → [l,mid] mein sabse lambi building
   *
   *     agar idx valid hai (height > dono):
   *       ans = min(ans, idx)   → ye candidate hai, aur left dhundho
   *       r = mid - 1
   *     else:
   *       l = mid + 1           → left half mein nahi, right try karo
   *
   * Example: heights = [6,4,8,5,2,7], query (0, 1)
   *   alice=0 (h=6), bob=1 (h=4) → heights[alice] > heights[bob], hard case
   *   search [2, 5]: leftmost j where h[j] > 6 AND h[j] > 4
   *   index 2 has h=8 > both → answer = 2
   */
    vector<int> leftmostBuildingQueries(vector<int>& heights,
                                        vector<vector<int>>& queries) {
        int n = heights.size();
        SegmentTree seg(heights);
        vector<int> result;

        for (auto& query : queries) {
            int a = query[0];
            int b = query[1];

            int alice = min(a, b);
            int bob = max(a, b);

            // ── STEP A: easy cases ──
            if (alice == bob || heights[bob] > heights[alice]) {
                result.push_back(bob);
                continue;
            }

            // ── STEP B + C: binary search + segment tree ──
            int l = max(a, b) + 1, r = n - 1;
            int ans = INT_MAX;

            while (l <= r) {
                int mid = (l + r) >> 1;
                int idx = seg.query(l, mid);   // [l, mid] ka tallest building

                // idx valid? → height dono se badi honi chahiye
                if (idx != -1 && heights[idx] > heights[a] &&
                    heights[idx] > heights[b]) {
                    ans = min(ans, idx);
                    r = mid - 1;   // left mein aur chhota index dhundho
                } else {
                    l = mid + 1;   // [l,mid] mein nahi mila, right half
                }
            }

            result.push_back(ans == INT_MAX ? -1 : ans);
        }

        return result;
    }
};

// ── Local demo (LeetCode submit pe main hata dena) ──
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> heights = {6, 4, 8, 5, 2, 7};
  /*
   * indices:           0  1  2  3  4  5
   * heights:           6  4  8  5  2  7
   *
   * query (0,1): alice=0, bob=1, h[0]=6 > h[1]=4 → hard case
   *   search [2,5], leftmost with h > 6 and h > 4 → index 2 (h=8) ✓
   *
   * query (0,3): alice=0, bob=3, h[3]=5 < h[0]=6 → hard case
   *   search [4,5] → index 5 (h=7) dono se bada → answer 5 ✓
   *
   * query (2,4): alice=2, bob=4, search [5,5] → h[5]=7 < h[2]=8 → -1 ✓
   */
    vector<vector<int>> queries = {{0, 1}, {0, 3}, {2, 4}};

    Solution sol;
    vector<int> ans = sol.leftmostBuildingQueries(heights, queries);

    cout << "heights: ";
    for (int h : heights) cout << h << " ";
    cout << "\n\nResults:\n";
    for (int i = 0; i < (int)queries.size(); ++i)
        cout << "query (" << queries[i][0] << ", " << queries[i][1]
             << ") -> " << ans[i] << "\n";

    return 0;
}
