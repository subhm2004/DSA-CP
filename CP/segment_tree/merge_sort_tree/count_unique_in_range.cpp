#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * PROBLEM: Count Unique (Distinct) Elements in Range [L, R]
 * ════════════════════════════════════════════════════════════════════════════
 *
 * Diya hai:
 *   - Array size n
 *   - Q queries, har query = (L, R)
 *
 * Poochna hai:
 *   - [L..R] range me kitne ALAAG (unique/distinct) elements hain?
 *   - Duplicates sirf ek baar count hote hain
 *
 * Example: arr = [1, 2, 2, 3, 1, 4]
 *
 *   Query (0, 5): {1,2,2,3,1,4} → unique {1,2,3,4} → 4
 *   Query (1, 3): {2,2,3}       → unique {2,3}     → 2
 *   Query (4, 5): {1,4}           → unique {1,4}     → 2
 *   Query (0, 0): {1}             → unique {1}       → 1
 *
 * APPROACH: Merge Sort Tree + Collect + Sort + Count
 *   1) [L,R] ko O(log n) disjoint segments me todo
 *   2) Har segment ki values collect karo
 *   3) Sort karke adjacent compare → unique count
 *
 * Time per query: O((R-L+1) log(R-L+1))
 * NOTE: Bade n ke liye Mo's Algorithm better hai — O((n+Q)√n)
 * ════════════════════════════════════════════════════════════════════════════
 */

class MergeSortTree {
private:
    int n;
    vector<vector<int>> tree;

    /*
     * build(arr, node, l, r)
     * Har node = sorted vector (duplicates KE SAATH — unique abhi nahi)
     */
    void build(const vector<int>& arr, int node, int l, int r) {
        if (l == r) {
            tree[node] = {arr[l]};
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * node + 1, l, mid);
        build(arr, 2 * node + 2, mid + 1, r);
        const auto& a = tree[2 * node + 1];
        const auto& b = tree[2 * node + 2];
        tree[node].resize(a.size() + b.size());
        merge(a.begin(), a.end(), b.begin(), b.end(), tree[node].begin());
    }

    /*
     * collectRange(ql, qr, node, l, r, out)
     * -------------------------------------
     * [ql..qr] ki saari values out vector mein daalo.
     *
     * Full overlap → poora tree[node] copy karo (fast)
     * Partial → bachhon mein recurse
     *
     * Kyun double count nahi?
     *   Segment tree range ko DISJOINT full segments mein todta hai.
     *   Har array index exactly EK baar collect hota hai.
     */
    void collectRange(int ql, int qr, int node, int l, int r, vector<int>& out) const {
        if (r < ql || l > qr) return;
        if (ql <= l && r <= qr) {
            out.insert(out.end(), tree[node].begin(), tree[node].end());
            return;
        }
        int mid = (l + r) / 2;
        collectRange(ql, qr, 2 * node + 1, l, mid, out);
        collectRange(ql, qr, 2 * node + 2, mid + 1, r, out);
    }

    /*
     * countUniqueFromSorted(vals)
     * ---------------------------
     * vals sort karo, phir adjacent alag count karo.
     * {1,1,2,3,3} sorted → 3 unique (1, 2, 3)
     */
    static int countUniqueFromSorted(vector<int>& vals) {
        if (vals.empty()) return 0;
        sort(vals.begin(), vals.end());
        int unique = 1;
        for (int i = 1; i < (int)vals.size(); ++i)
            if (vals[i] != vals[i - 1]) unique++;
        return unique;
    }

public:
    /*
     * Constructor — tree build from array
     */
    MergeSortTree(const vector<int>& arr) {
        n = (int)arr.size();
        tree.assign(4 * max(n, 1), {});
        if (n > 0) build(arr, 0, 0, n - 1);
    }

    /*
     * countUnique(L, R)
     * -----------------
     * Step 1: collectRange → [L,R] ki saari values
     * Step 2: sort + adjacent unique count
     *
     * Example: collected {1,2,2,3,1,4} → sorted → unique = 4
     */
    int countUnique(int L, int R) const {
        if (n == 0 || L > R) return 0;
        vector<int> vals;
        vals.reserve(R - L + 1);
        collectRange(L, R, 0, 0, n - 1, vals);
        return countUniqueFromSorted(vals);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> arr = {1, 2, 2, 3, 1, 4};
    MergeSortTree mst(arr);

    vector<pair<int, int>> queries = {{0,5}, {1,3}, {4,5}, {2,4}, {0,0}};

    cout << "Array: ";
    for (int i = 0; i < (int)arr.size(); ++i)
        cout << "[" << i << "]=" << arr[i] << " ";
    cout << "\n\n-- Q Queries: count unique in [L,R] --\n";

    for (auto& [L, R] : queries)
        cout << "(" << L << "," << R << ") -> " << mst.countUnique(L, R) << "\n";

    return 0;
}
