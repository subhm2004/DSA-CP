#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * BITWISE AND / OR SEGMENT TREE — Point Update + Range Query
 * ════════════════════════════════════════════════════════════════════════════
 *
 * PROBLEM TYPE (non-invertible bitwise ops):
 *   1) Point update : arr[i] = val
 *   2) Range query  : arr[L..R] ka bitwise AND  ya  OR
 *
 * Example AND: arr = [12, 7, 14, 3]  (1100, 0111, 1110, 0011)
 *   AND(0,2) = 12 & 7 & 14 = 4
 *
 * Example OR:  arr = [1, 2, 4, 8]
 *   OR(1,3) = 2 | 4 | 8 = 14
 *
 * Kyun Segment Tree?
 *   AND/OR associative hain lekin INVERTIBLE nahi (Fenwick nahi chalega).
 *   GCD seg tree jaisa hi pattern — merge = & ya |
 *
 * Identity (no overlap):
 *   AND → sab bits 1 wala number  (~0 ya -1 for signed int — sab 1 bits)
 *   OR  → 0
 *
 * Kab use karo:
 *   Range bitwise AND/OR + point updates
 *   "Kitne bits set hain" type problems kabhi AND se nikalte hain
 *
 * Time: build O(n) | point update O(log n) | range query O(log n)
 * ════════════════════════════════════════════════════════════════════════════
 */

// ────────────────────────────────────────────────────────────────────────────
// Range AND Segment Tree
// ────────────────────────────────────────────────────────────────────────────
class AndSegmentTree {
private:
    int n;
    vector<int> tree;
    static constexpr int IDENTITY = -1;  // sab bits 1 → AND me koi effect nahi

    void build(const vector<int>& arr, int node, int l, int r) {
        if (l == r) {
            tree[node] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * node + 1, l, mid);
        build(arr, 2 * node + 2, mid + 1, r);
        tree[node] = tree[2 * node + 1] & tree[2 * node + 2];
    }

    void pointUpdate(int node, int l, int r, int idx, int val) {
        if (l == r) {
            tree[node] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) pointUpdate(2 * node + 1, l, mid, idx, val);
        else            pointUpdate(2 * node + 2, mid + 1, r, idx, val);
        tree[node] = tree[2 * node + 1] & tree[2 * node + 2];
    }

    int rangeAnd(int node, int l, int r, int ql, int qr) const {
        if (qr < l || r < ql) return IDENTITY;
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        return rangeAnd(2 * node + 1, l, mid, ql, qr)
             & rangeAnd(2 * node + 2, mid + 1, r, ql, qr);
    }

public:
    AndSegmentTree(const vector<int>& arr) {
        n = (int)arr.size();
        tree.assign(4 * max(n, 1), IDENTITY);
        if (n > 0) build(arr, 0, 0, n - 1);
    }

    void pointUpdate(int idx, int val) { pointUpdate(0, 0, n - 1, idx, val); }
    int rangeAnd(int L, int R) const { return rangeAnd(0, 0, n - 1, L, R); }
};

// ────────────────────────────────────────────────────────────────────────────
// Range OR Segment Tree
// ────────────────────────────────────────────────────────────────────────────
class OrSegmentTree {
private:
    int n;
    vector<int> tree;

    void build(const vector<int>& arr, int node, int l, int r) {
        if (l == r) {
            tree[node] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * node + 1, l, mid);
        build(arr, 2 * node + 2, mid + 1, r);
        tree[node] = tree[2 * node + 1] | tree[2 * node + 2];
    }

    void pointUpdate(int node, int l, int r, int idx, int val) {
        if (l == r) {
            tree[node] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) pointUpdate(2 * node + 1, l, mid, idx, val);
        else            pointUpdate(2 * node + 2, mid + 1, r, idx, val);
        tree[node] = tree[2 * node + 1] | tree[2 * node + 2];
    }

    int rangeOr(int node, int l, int r, int ql, int qr) const {
        if (qr < l || r < ql) return 0;  // OR identity
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        return rangeOr(2 * node + 1, l, mid, ql, qr)
             | rangeOr(2 * node + 2, mid + 1, r, ql, qr);
    }

public:
    OrSegmentTree(const vector<int>& arr) {
        n = (int)arr.size();
        tree.assign(4 * max(n, 1), 0);
        if (n > 0) build(arr, 0, 0, n - 1);
    }

    void pointUpdate(int idx, int val) { pointUpdate(0, 0, n - 1, idx, val); }
    int rangeOr(int L, int R) const { return rangeOr(0, 0, n - 1, L, R); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> arr = {12, 7, 14, 3};  // 1100, 0111, 1110, 0011

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n\n---- Range AND (Point Update + Range Query) ----\n";

    AndSegmentTree andSt(arr);
    cout << "AND(0,3) = " << andSt.rangeAnd(0, 3) << "  (12&7&14&3 = 0)\n";
    cout << "AND(0,2) = " << andSt.rangeAnd(0, 2) << "  (12&7&14 = 4)\n";
    cout << "AND(1,2) = " << andSt.rangeAnd(1, 2) << "  (7&14 = 6)\n";

    andSt.pointUpdate(0, 15);  // 1111
    cout << "\nPoint set arr[0]=15 → AND(0,2) = " << andSt.rangeAnd(0, 2) << " (15&7&14=6)\n";

    cout << "\n---- Range OR ----\n";
    vector<int> arr2 = {1, 2, 4, 8};
    OrSegmentTree orSt(arr2);
    cout << "Array: ";
    for (int x : arr2) cout << x << " ";
    cout << "\nOR(0,3) = " << orSt.rangeOr(0, 3) << "  (1|2|4|8 = 15)\n";
    cout << "OR(1,3) = " << orSt.rangeOr(1, 3) << "  (2|4|8 = 14)\n";

    orSt.pointUpdate(2, 0);
    cout << "Point set arr[2]=0 → OR(0,3) = " << orSt.rangeOr(0, 3) << "\n";

    return 0;
}
