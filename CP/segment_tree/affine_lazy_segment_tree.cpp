#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * AFFINE LAZY SEGMENT TREE — Range (×a + b) Update + Range Sum Query
 * ════════════════════════════════════════════════════════════════════════════
 *
 * PROBLEM:
 *   Array par range update: har element x ko  a*x + b  bana do  (same a,b poori range me)
 *   Query: range sum
 *
 * Example: arr = [1, 2, 3, 4]
 *   Range [0,2] apply ×2 + 1  →  [3, 5, 7, 4]
 *   Sum(0,3) = 3+5+7+4 = 19
 *
 * LAZY COMPOSE:
 *   Pehle (mul1, add1), phir (mul2, add2) lagaya
 *   Effective: x → mul2*(mul1*x + add1) + add2 = (mul1*mul2)*x + (add1*mul2 + add2)
 *
 *   lazy_child = combine(parent_lazy, child_lazy)
 *
 * NODE UPDATE jab (mul, add) lagao segment length = len par:
 *   new_sum = mul * old_sum + add * len
 *
 * Time: build O(n) | range affine O(log n) | range sum O(log n)
 * ════════════════════════════════════════════════════════════════════════════
 */

class AffineLazySegTree {
private:
    struct Lazy {
        long long mul = 1, add = 0;
    };

    int n;
    vector<long long> sum;
    vector<Lazy> lazy;

    // combine: pehle outer (om, oa), phir inner (im, ia) → result inner pe apply hua, phir outer
    static Lazy combine(const Lazy& outer, const Lazy& inner) {
        return {inner.mul * outer.mul, inner.add * outer.mul + outer.add};
    }

    void apply(int node, int l, int r, const Lazy& tag) {
        int len = r - l + 1;
        sum[node] = sum[node] * tag.mul + tag.add * len;
        lazy[node] = combine(tag, lazy[node]);
    }

    void push(int node, int l, int r) {
        if (lazy[node].mul == 1 && lazy[node].add == 0) return;
        if (l == r) {
            lazy[node] = {1, 0};
            return;
        }
        int mid = (l + r) / 2;
        apply(2 * node + 1, l, mid, lazy[node]);
        apply(2 * node + 2, mid + 1, r, lazy[node]);
        lazy[node] = {1, 0};
    }

    void build(const vector<int>& arr, int node, int l, int r) {
        if (l == r) {
            sum[node] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * node + 1, l, mid);
        build(arr, 2 * node + 2, mid + 1, r);
        sum[node] = sum[2 * node + 1] + sum[2 * node + 2];
    }

    void rangeAffine(int node, int l, int r, int ql, int qr, long long mul, long long add) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            apply(node, l, r, {mul, add});
            return;
        }
        push(node, l, r);
        int mid = (l + r) / 2;
        rangeAffine(2 * node + 1, l, mid, ql, qr, mul, add);
        rangeAffine(2 * node + 2, mid + 1, r, ql, qr, mul, add);
        sum[node] = sum[2 * node + 1] + sum[2 * node + 2];
    }

    long long rangeSum(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return sum[node];
        push(node, l, r);
        int mid = (l + r) / 2;
        return rangeSum(2 * node + 1, l, mid, ql, qr)
             + rangeSum(2 * node + 2, mid + 1, r, ql, qr);
    }

public:
    AffineLazySegTree(const vector<int>& arr) {
        n = (int)arr.size();
        sum.assign(4 * max(n, 1), 0);
        lazy.assign(4 * max(n, 1), {});
        if (n > 0) build(arr, 0, 0, n - 1);
    }

    void rangeAffine(int L, int R, long long mul, long long add) {
        rangeAffine(0, 0, n - 1, L, R, mul, add);
    }

    long long rangeSum(int L, int R) {
        return rangeSum(0, 0, n - 1, L, R);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> arr = {1, 2, 3, 4};
    AffineLazySegTree st(arr);

    cout << "Initial sum(0,3) = " << st.rangeSum(0, 3) << "\n";

    cout << "Apply [0,2]: x -> 2*x + 1\n";
    st.rangeAffine(0, 2, 2, 1);
    cout << "Sum(0,3) = " << st.rangeSum(0, 3) << "  (expected 3+5+7+4=19)\n";

    cout << "Apply [1,3]: x -> x + 10\n";
    st.rangeAffine(1, 3, 1, 10);
    cout << "Sum(0,3) = " << st.rangeSum(0, 3) << "\n";

    return 0;
}
