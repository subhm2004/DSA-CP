#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * RANGE ASSIGN LAZY SEGMENT TREE — Range Set + Range Add + Range Sum
 * ════════════════════════════════════════════════════════════════════════════
 *
 * PROBLEM TYPE (painting / lazy assign):
 *   1) Range ASSIGN : arr[L..R] = val   (sab ko same value set)
 *   2) Range ADD    : arr[L..R] += val  (optional, often saath me aata hai)
 *   3) Range SUM query
 *
 * Example: arr = [1, 2, 3, 4, 5]
 *   assign(1, 3, 10)  →  [1, 10, 10, 10, 5]
 *   sum(0, 4)         →  36
 *   add(2, 4, 2)      →  [1, 10, 12, 12, 7]
 *   sum(1, 3)         →  34
 *
 * LAZY RULES (priority):
 *   ASSIGN hamesha ADD se strong hai.
 *   assign(v) ke baad purane add clear ho jaate hain us segment par.
 *   push karte waqt pehle SET bhejo, phir ADD.
 *
 * lazySet[i] = LLONG_MIN  →  koi pending assign nahi
 *
 * Kab use karo:
 *   "Poori range ko X set karo" + sum/min queries
 *   Painting array, hotel booking range fill, CF range set problems
 *
 * Time: build O(n) | range assign/add O(log n) | range sum O(log n)
 * ════════════════════════════════════════════════════════════════════════════
 */

class RangeAssignLazySegTree {
private:
    static constexpr ll NO_SET = (ll)-4e18;

    int n;
    vector<ll> sum;
    vector<ll> lazyAdd;
    vector<ll> lazySet;

    void applySet(int node, int l, int r, ll val) {
        int len = r - l + 1;
        sum[node] = val * len;
        lazySet[node] = val;
        lazyAdd[node] = 0;  // assign ne purana add overwrite kar diya
    }

    void applyAdd(int node, int l, int r, ll val) {
        sum[node] += val * (r - l + 1);
        if (lazySet[node] != NO_SET)
            lazySet[node] += val;  // pending assign value ko bhi add karo
        else
            lazyAdd[node] += val;
    }

    void push(int node, int l, int r) {
        if (l == r) {
            lazySet[node] = NO_SET;
            lazyAdd[node] = 0;
            return;
        }
        int mid = (l + r) / 2;
        if (lazySet[node] != NO_SET) {
            applySet(2 * node + 1, l, mid, lazySet[node]);
            applySet(2 * node + 2, mid + 1, r, lazySet[node]);
            lazySet[node] = NO_SET;
        }
        if (lazyAdd[node] != 0) {
            applyAdd(2 * node + 1, l, mid, lazyAdd[node]);
            applyAdd(2 * node + 2, mid + 1, r, lazyAdd[node]);
            lazyAdd[node] = 0;
        }
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

    void rangeAssign(int node, int l, int r, int ql, int qr, ll val) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            applySet(node, l, r, val);
            return;
        }
        push(node, l, r);
        int mid = (l + r) / 2;
        rangeAssign(2 * node + 1, l, mid, ql, qr, val);
        rangeAssign(2 * node + 2, mid + 1, r, ql, qr, val);
        sum[node] = sum[2 * node + 1] + sum[2 * node + 2];
    }

    void rangeAdd(int node, int l, int r, int ql, int qr, ll val) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            applyAdd(node, l, r, val);
            return;
        }
        push(node, l, r);
        int mid = (l + r) / 2;
        rangeAdd(2 * node + 1, l, mid, ql, qr, val);
        rangeAdd(2 * node + 2, mid + 1, r, ql, qr, val);
        sum[node] = sum[2 * node + 1] + sum[2 * node + 2];
    }

    ll rangeSum(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return sum[node];
        push(node, l, r);
        int mid = (l + r) / 2;
        return rangeSum(2 * node + 1, l, mid, ql, qr)
             + rangeSum(2 * node + 2, mid + 1, r, ql, qr);
    }

public:
    RangeAssignLazySegTree(const vector<int>& arr) {
        n = (int)arr.size();
        sum.assign(4 * max(n, 1), 0);
        lazyAdd.assign(4 * max(n, 1), 0);
        lazySet.assign(4 * max(n, 1), NO_SET);
        if (n > 0) build(arr, 0, 0, n - 1);
    }

    void rangeAssign(int L, int R, ll val) { rangeAssign(0, 0, n - 1, L, R, val); }
    void rangeAdd(int L, int R, ll val)     { rangeAdd(0, 0, n - 1, L, R, val); }
    ll rangeSum(int L, int R)               { return rangeSum(0, 0, n - 1, L, R); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> arr = {1, 2, 3, 4, 5};
    RangeAssignLazySegTree st(arr);

    cout << "Initial array: ";
    for (int x : arr) cout << x << " ";
    cout << "\nSum(0,4) = " << st.rangeSum(0, 4) << " (15)\n";

    cout << "\nassign(1,3, 10) → [1, 10, 10, 10, 5]\n";
    st.rangeAssign(1, 3, 10);
    cout << "Sum(0,4) = " << st.rangeSum(0, 4) << " (36)\n";
    cout << "Sum(1,3) = " << st.rangeSum(1, 3) << " (30)\n";

    cout << "\nadd(2,4, 2) → [1, 10, 12, 12, 7]\n";
    st.rangeAdd(2, 4, 2);
    cout << "Sum(1,3) = " << st.rangeSum(1, 3) << " (34)\n";
    cout << "Sum(0,4) = " << st.rangeSum(0, 4) << " (42)\n";

    cout << "\nassign(0,4, 0) → sab zero\n";
    st.rangeAssign(0, 4, 0);
    cout << "Sum(0,4) = " << st.rangeSum(0, 4) << " (0)\n";

    return 0;
}
