#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// MERGE SORT TREE — Static array pe range queries
// ────────────────────────────────────────────────────────────────────────────
// Har node apne segment ke elements ka SORTED vector store karta hai.
// Build: leaf pe 1 element, internal pe left+right merge (merge sort jaisa)
//
// Queries (O(log² n)):
//   1) kthSmallest(l, r, k)  — BS on value + countLessEqual (1-indexed k)
//   2) countLess(l, r, x)    — range me kitne elements < x
//
// NOTE: Static array — point update expensive (O(n log n) rebuild).
//       Updates chahiye to PBDS / sqrt decomposition / persistent tree dekho.
// Space: O(n log n)
// ════════════════════════════════════════════════════════════════════════════

class MergeSortTree
{
    int n;
    int loVal, hiVal;         // array min/max — kth binary search bounds
    vector<vector<int>> tree; // tree[i] = sorted values in node i's segment

    // ── build: segment [l,r] ka sorted vector banao ───────────────────────────
    //   1) leaf -> single element vector
    //   2) left/right child build, phir merge into tree[i]
    void build(const vector<int> &arr, int i, int l, int r)
    {
        if (l == r)
        {
            tree[i] = {arr[l]};
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * i + 1, l, mid);
        build(arr, 2 * i + 2, mid + 1, r);

        const vector<int> &a = tree[2 * i + 1];
        const vector<int> &b = tree[2 * i + 2];
        tree[i].resize(a.size() + b.size());
        merge(a.begin(), a.end(), b.begin(), b.end(), tree[i].begin());
    }

    // ── countLessRec: [ql,qr] me kitne elements strictly < x ──────────────────
    int countLessRec(int ql, int qr, int x, int i, int l, int r) const
    {
        if (r < ql || l > qr)
            return 0;
        if (ql <= l && r <= qr)
            return (int)(lower_bound(tree[i].begin(), tree[i].end(), x) - tree[i].begin());

        int mid = (l + r) / 2;
        return countLessRec(ql, qr, x, 2 * i + 1, l, mid) +
               countLessRec(ql, qr, x, 2 * i + 2, mid + 1, r);
    }

    // ── countLessEqualRec: [ql,qr] me kitne elements <= x ───────────────────
    int countLessEqualRec(int ql, int qr, int x, int i, int l, int r) const
    {
        if (r < ql || l > qr)
            return 0;
        if (ql <= l && r <= qr)
            return (int)(upper_bound(tree[i].begin(), tree[i].end(), x) - tree[i].begin());

        int mid = (l + r) / 2;
        return countLessEqualRec(ql, qr, x, 2 * i + 1, l, mid) +
               countLessEqualRec(ql, qr, x, 2 * i + 2, mid + 1, r);
    }

public:
    // ── MergeSortTree: array se tree build ────────────────────────────────────
    MergeSortTree(const vector<int> &arr)
    {
        n = (int)arr.size();
        tree.assign(4 * n, {});
        if (n > 0)
        {
            loVal = *min_element(arr.begin(), arr.end());
            hiVal = *max_element(arr.begin(), arr.end());
            build(arr, 0, 0, n - 1);
        }
    }

    // ── kthSmallest: range me k-th smallest value (1-indexed) ─────────────────
    //   Binary search on answer: smallest v jahan count(<=v) >= k
    int kthSmallest(int l, int r, int k) const
    {
        int lo = loVal, hi = hiVal;
        while (lo < hi)
        {
            int mid = lo + (hi - lo) / 2;
            if (countLessEqualRec(l, r, mid, 0, 0, n - 1) >= k)
                hi = mid;
            else
                lo = mid + 1;
        }
        return lo;
    }

    int countLess(int l, int r, int x) const
    {
        return countLessRec(l, r, x, 0, 0, n - 1);
    }
};

int main()
{
    vector<int> arr = {5, 1, 2, 3, 4};
    MergeSortTree mst(arr);

    cout << "Array: ";
    for (int x : arr)
        cout << x << " ";
    cout << "\n\n";

    // same tests as k_smallest_number_in_range.cpp (brute) — compare results
    cout << "kth smallest [0,4], k=3 -> " << mst.kthSmallest(0, 4, 3) << "\n"; // 3
    cout << "kth smallest [1,4], k=2 -> " << mst.kthSmallest(1, 4, 2) << "\n"; // 2
    cout << "kth smallest [0,2], k=1 -> " << mst.kthSmallest(0, 2, 1) << "\n"; // 1

    cout << "\ncount < 3 in [0,4] -> " << mst.countLess(0, 4, 3) << "\n"; // 2 (1,2)
    cout << "count < 4 in [1,4] -> " << mst.countLess(1, 4, 4) << "\n";  // 3 (1,2,3)

    return 0;
}

/*
 * ════════════════════════════════════════════════════════════════════════════
 * MERGE SORT TREE — POORA GUIDE (Hinglish)
 * ════════════════════════════════════════════════════════════════════════════
 *
 * ┌─────────────────────────────────────────────────────────────────────────┐
 * │ 1) KYA HAI MERGE SORT TREE?                                             │
 * └─────────────────────────────────────────────────────────────────────────┘
 *
 * Normal segment tree har node pe EK value rakhta hai (sum, min, max, gcd...).
 * Merge Sort Tree har node pe us segment ke SAARE elements ka SORTED VECTOR
 * rakhta hai — jaise merge sort me do sorted halves merge hote hain, waise hi
 * tree build hota hai.
 *
 * Example array: [5, 1, 2, 3, 4]  (indices 0..4)
 *
 *                    [0 ───────────── 4]
 *                   tree[0] = {1,2,3,4,5}   ← poori array sorted
 *                   /                    \
 *          [0 ── 2]                      [3 ── 4]
 *     tree[1]={1,2,5}              tree[2]={3,4}
 *        /      \                     /      \
 *    [0] [1,2]                   [3]      [4]
 *    {5} {1,2}                   {3}      {4}
 *
 * Leaf pe 1 element, upar jaate waqt left+right merge → sorted list.
 *
 *
 * ┌─────────────────────────────────────────────────────────────────────────┐
 * │ 2) KAB USE KARO? (When to use)                                          │
 * └─────────────────────────────────────────────────────────────────────────┘
 *
 * ✅ USE KARO jab:
 *   • Static array hai (updates kam ya bilkul nahi)
 *   • Range [L,R] me K-th smallest chahiye
 *   • Range [L,R] me kitne elements < X hain (count / rank query)
 *   • Range [L,R] me kitne elements <= X hain
 *   • Inversion count jaisa: pair (i,j) jahan i<j aur arr[i]>arr[j] — offline
 *   • "Mo's algorithm + sort" type problems jahan order statistics chahiye
 *
 * ❌ MAT USE KARO jab:
 *   • Bahut saare point updates hain → rebuild expensive, O(n log n) har update
 *   • Sirf sum/min/max chahiye → normal seg tree ya Fenwick kaafi hai
 *   • Sirf prefix query chahiye → Fenwick O(n) space, zyada simple
 *   • Array static + sirf min/max → Sparse Table O(1) query, better
 *
 *
 * ┌─────────────────────────────────────────────────────────────────────────┐
 * │ 3) NORMAL SEG TREE vs MERGE SORT TREE vs FENWICK vs PBDS               │
 * └─────────────────────────────────────────────────────────────────────────┘
 *
 *   Structure          | Range Sum | Range Min | K-th in Range | Point Update
 *   -------------------|-----------|-----------|---------------|-------------
 *   Fenwick Tree       |    ✅     |     ❌    |      ❌       |     ✅
 *   Normal Seg Tree    |    ✅     |     ✅    |      ❌       |     ✅
 *   Merge Sort Tree    |    ❌*    |     ❌    |      ✅       |     ❌**
 *   PBDS (ordered ms)  |    ❌     |     ❌    |      ✅       |     ✅
 *
 *   * sum nikal sakte ho countLess se tricks se, lekin direct nahi
 *   ** update = poora subtree rebuild ya naya tree banana padta hai
 *
 *   PBDS (policy-based data structure) bhi k-th deta hai lekin GNU extension hai.
 *   Merge Sort Tree portable C++ hai aur offline/static queries ke liye best.
 *
 *
 * ┌─────────────────────────────────────────────────────────────────────────┐
 * │ 4) QUERIES KAISE KAAM KARTI HAIN?                                       │
 * └─────────────────────────────────────────────────────────────────────────┘
 *
 * A) countLess(L, R, x) — range me kitne elements STRICTLY < x
 *    ─────────────────────────────────────────────────────────────
 *    Segment tree pe recurse karo (same 3 cases: no/full/partial overlap).
 *    Full overlap pe: node ka sorted vector → lower_bound(x) = count < x
 *    Partial pe: left child + right child ka count jodo.
 *
 *    Example: arr = [5,1,2,3,4], countLess(0,4,3)
 *      → elements < 3 are {1,2} → answer = 2
 *
 * B) kthSmallest(L, R, k) — range me K-th smallest VALUE (1-indexed)
 *    ───────────────────────────────────────────────────────────────────
 *    Direct tree walk se galat ho sakta hai unsorted array pe.
 *    Isliye BINARY SEARCH ON ANSWER use karte hain:
 *
 *      lo = min value, hi = max value
 *      jab tak lo < hi:
 *        mid = (lo+hi)/2
 *        agar count(<= mid) >= k  → answer left half me (hi = mid)
 *        warna                    → answer right half me (lo = mid+1)
 *
 *    Example: arr = [5,1,2,3,4], range [0,4], k=3
 *      sorted range = {1,2,3,4,5} → 3rd smallest = 3 ✅
 *
 *    k=1 → 1 (sabse chhota)
 *    k=5 → 5 (sabse bada)
 *
 *
 * ┌─────────────────────────────────────────────────────────────────────────┐
 * │ 5) COMPLEXITY                                                           │
 * └─────────────────────────────────────────────────────────────────────────┘
 *
 *   Build        : O(n log n)     — har level pe total n merge work
 *   Space        : O(n log n)     — har element log n levels pe stored
 *   countLess    : O(log² n)     — O(log n) nodes × O(log n) binary search
 *   kthSmallest  : O(log² n)     — binary search × countLess per step
 *   Point Update : O(n log n)    — practically rebuild — isliye static use
 *
 *   n = 1e5 → build ~ 1e6 ops, query ~ 400 ops → contest me comfortable
 *
 *
 * ┌─────────────────────────────────────────────────────────────────────────┐
 * │ 6) CODE KAISE USE KARO? (Step by step)                                  │
 * └─────────────────────────────────────────────────────────────────────────┘
 *
 *   Step 1: Array ready karo
 *     vector<int> arr = {5, 1, 2, 3, 4};
 *
 *   Step 2: Tree build karo (constructor me build ho jata hai)
 *     MergeSortTree mst(arr);
 *
 *   Step 3: Queries maaro
 *     int kth = mst.kthSmallest(0, 4, 3);   // range [0,4], 3rd smallest
 *     int cnt = mst.countLess(1, 4, 3);     // [1,4] me kitne < 3
 *
 *   NOTE: indices 0-indexed hain, k is 1-indexed (k=1 → smallest)
 *
 *   LeetCode style wrapper:
 *     class Solution {
 *       MergeSortTree* tree;
 *     public:
 *       // nums se init, phir queries...
 *     };
 *
 *
 * ┌─────────────────────────────────────────────────────────────────────────┐
 * │ 7) REAL CONTEST PROBLEMS / PATTERNS                                     │
 * └─────────────────────────────────────────────────────────────────────────┘
 *
 *   • K-th smallest in range          → direct kthSmallest()
 *   • Count of elements < X in range  → direct countLess()
 *   • Inversion count (offline)       → coordinate compress + countLess
 *   • Number of pairs with diff <= D  → sort + two pointers OR merge sort tree
 *   • Range median                    → kthSmallest(l, r, (r-l+2)/2)
 *   • "How many values in [L,R] lie in [A,B]?"
 *       = countLessEqual(B) - countLess(A)
 *
 *
 * ┌─────────────────────────────────────────────────────────────────────────┐
 * │ 8) COMMON MISTAKES (galtiyan mat karna)                                 │
 * └─────────────────────────────────────────────────────────────────────────┘
 *
 *   ❌ Point update ke baad sirf ek leaf change karna — sorted vectors corrupt
 *   ❌ k ko 0-indexed samajhna — code me k=1 means smallest
 *   ❌ Tree walk se k-th nikalna bina binary search — unsorted array pe galat
 *   ❌ n=0 pe tree use karna — constructor me check karo
 *   ❌ Merge sort tree jahan Fenwick chal jaye — overkill + zyada memory
 *
 *
 * ┌─────────────────────────────────────────────────────────────────────────┐
 * │ 9) ALTERNATIVES AGAR UPDATE CHAHIYE                                     │
 * └─────────────────────────────────────────────────────────────────────────┘
 *
 *   • PBDS (GNU)           → order_of_key, insert, erase — O(log n) update
 *   • Sqrt decomposition   → O(sqrt n) query, O(1) update — simple
 *   • Persistent seg tree  → version history, functional updates
 *   • Wavelet tree         → advanced, same queries, better update support
 *   • Mo's algorithm       → offline range queries, O(n sqrt n)
 *
 *
 * ┌─────────────────────────────────────────────────────────────────────────┐
 * │ 10) YAAD RAKHNE WALI EK LINE                                            │
 * └─────────────────────────────────────────────────────────────────────────┘
 *
 *   "Static array + range me order statistics (k-th, count < x)
 *    chahiye → Merge Sort Tree.
 *    Sum/min/max chahiye → normal seg tree / Fenwick.
 *    Updates zyada hain → PBDS ya sqrt decomposition."
 *
 * ════════════════════════════════════════════════════════════════════════════
 */
