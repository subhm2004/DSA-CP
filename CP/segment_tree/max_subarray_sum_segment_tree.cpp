#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * MAX SUBARRAY SUM SEGMENT TREE — Kadane Merge + Range Query
 * ════════════════════════════════════════════════════════════════════════════
 *
 * PROBLEM:
 *   Array diya hai. Queries:
 *     1) Point update : arr[i] = val
 *     2) Range query  : [L,R] me MAXIMUM subarray sum (contiguous)
 *
 * Example: arr = [2, -1, 3, -2, 4]
 *   [L,R]=[0,4] → best subarray = [2,-1,3,-2,4] sum=6? 
 *   Actually: 2+(-1)+3+(-2)+4=6, or just [4]=4, or [2,-1,3]=4
 *   Best = 2+(-1)+3+(-2)+4 = 6  OR  subarray [3] at idx2 = 3...
 *   Kadane: max ending at each = 6 overall for full array
 *
 *   [0,2]: arr[0..2] = [2,-1,3] → best = 2+(-1)+3 = 4
 *   [3,4]: [-2,4] → best = 4 (sirf 4 lena better)
 *
 * NODE me 4 cheezein store (har segment ke liye):
 *   sum  → poora segment ka total sum
 *   pref → maximum prefix sum (left se shuru karke)
 *   suff → maximum suffix sum (right tak)
 *   best → maximum subarray sum is segment ke ANDAR (Kadane answer)
 *
 * MERGE (left segment A + right segment B):
 *   sum  = A.sum + B.sum
 *   pref = max(A.pref, A.sum + B.pref)
 *   suff = max(B.suff, A.suff + B.sum)
 *   best = max({A.best, B.best, A.suff + B.pref})
 *         ↑ cross-boundary subarray — left ka suffix + right ka prefix
 *
 * Kab use karo:
 *   "Maximum sum subarray in range [L,R]" with updates
 *   Interview favourite — Kadane O(n) sirf static array ke liye;
 *   updates + range queries → seg tree with 4-value nodes
 *
 * Time: build O(n) | point update O(log n) | range query O(log n)
 * ════════════════════════════════════════════════════════════════════════════
 */

struct Node {
    long long sum = 0;
    long long pref = 0, suff = 0, best = 0;

    // Empty identity — query me koi overlap nahi
    static Node empty() {
        const long long NEG = (long long)-4e18;
        return {0, NEG, NEG, NEG};
    }

    // Single element leaf — non-empty subarray: kam se kam ek element lena hi hai
    static Node fromVal(long long x) {
        return {x, x, x, x};
    }
};

class MaxSubarraySegTree {
private:
    int n;
    vector<Node> tree;

    static Node merge(const Node& a, const Node& b) {
        if (a.best <= (long long)-3e18) return b;
        if (b.best <= (long long)-3e18) return a;
        Node c;
        c.sum  = a.sum + b.sum;
        c.pref = max(a.pref, a.sum + b.pref);
        c.suff = max(b.suff, a.suff + b.sum);
        c.best = max({a.best, b.best, a.suff + b.pref});
        return c;
    }

    void build(const vector<int>& arr, int node, int l, int r) {
        if (l == r) {
            tree[node] = Node::fromVal(arr[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * node + 1, l, mid);
        build(arr, 2 * node + 2, mid + 1, r);
        tree[node] = merge(tree[2 * node + 1], tree[2 * node + 2]);
    }

    void pointUpdate(int node, int l, int r, int idx, int val) {
        if (l == r) {
            tree[node] = Node::fromVal(val);
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) pointUpdate(2 * node + 1, l, mid, idx, val);
        else            pointUpdate(2 * node + 2, mid + 1, r, idx, val);
        tree[node] = merge(tree[2 * node + 1], tree[2 * node + 2]);
    }

    Node rangeQuery(int node, int l, int r, int ql, int qr) const {
        if (qr < l || r < ql) return Node::empty();
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        return merge(
            rangeQuery(2 * node + 1, l, mid, ql, qr),
            rangeQuery(2 * node + 2, mid + 1, r, ql, qr)
        );
    }

public:
    MaxSubarraySegTree(const vector<int>& arr) {
        n = (int)arr.size();
        tree.assign(4 * max(n, 1), Node::empty());
        if (n > 0) build(arr, 0, 0, n - 1);
    }

    void pointUpdate(int idx, int val) {
        pointUpdate(0, 0, n - 1, idx, val);
    }

    long long maxSubarraySum(int L, int R) const {
        return rangeQuery(0, 0, n - 1, L, R).best;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> arr = {2, -1, 3, -2, 4};
    MaxSubarraySegTree st(arr);

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n\n-- Max subarray sum in range --\n";
    cout << "maxSubarray(0,4) = " << st.maxSubarraySum(0, 4) << "  (full array kadane)\n";
    cout << "maxSubarray(0,2) = " << st.maxSubarraySum(0, 2) << "  ([2,-1,3] → 4)\n";
    cout << "maxSubarray(3,4) = " << st.maxSubarraySum(3, 4) << "  ([-2,4] → 4)\n";
    cout << "maxSubarray(1,3) = " << st.maxSubarraySum(1, 3) << "  ([-1,3,-2] → 3)\n";

    cout << "\nPoint update: arr[3] = 5  → arr = [2,-1,3,5,4]\n";
    st.pointUpdate(3, 5);
    cout << "maxSubarray(0,4) = " << st.maxSubarraySum(0, 4) << "\n";
    cout << "maxSubarray(2,4) = " << st.maxSubarraySum(2, 4) << "  ([3,5,4] → 12)\n";

    // Classic kadane test
    vector<int> arr2 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    MaxSubarraySegTree st2(arr2);
    cout << "\nKadane classic: [-2,1,-3,4,-1,2,1,-5,4]\n";
    cout << "maxSubarray(0,8) = " << st2.maxSubarraySum(0, 8) << "  (expected 6: [4,-1,2,1])\n";
    cout << "maxSubarray(3,6) = " << st2.maxSubarraySum(3, 6) << "  ([4,-1,2,1] → 6)\n";

    return 0;
}
