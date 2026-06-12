#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * XOR SEGMENT TREE — Teen Classic Variations
 * ════════════════════════════════════════════════════════════════════════════
 *
 * XOR properties (yaad rakho):
 *   x ^ 0 = x        → identity (no overlap me 0 return)
 *   x ^ x = 0
 *   associative      → merge = left ^ right
 *   self-inverse     → arr[i] ^= v do baar = original
 *
 * Range XOR update ka matlab: har element arr[i] ^= val  (bits flip)
 *   SUM jaisa "+val" nahi — XOR lazy alag rule follow karta hai!
 *
 * Lazy XOR rule (important):
 *   Segment [l,r] length = len. Sab elements ^= v karoge to:
 *     segment_XOR ^= v   sirf jab len ODD ho
 *     kyunki v^v^v... (even baar) = 0, (odd baar) = v
 *
 * ────────────────────────────────────────────────────────────────────────────
 * KAB KONSA USE KARO? (Decision Guide)
 * ────────────────────────────────────────────────────────────────────────────
 *
 * 1️⃣ Point Update + Range XOR Query
 *    Update : arr[i] = val          (poori value set)
 *    Query  : arr[L..R] ka XOR
 *    Kab    : array me kabhi-kabhi ek index badalna ho, baar-baar range XOR maango
 *    Example: subarray XOR problems, toggle single element, CF "Xor queries"
 *    Lazy?  : NAHI — simple tree, O(log n) point set
 *
 * 2️⃣ Range XOR Update + Point Query
 *    Update : arr[L..R] ^= val        (range me har element ko flip)
 *    Query  : arr[i] ki current value
 *    Kab    : bahut range XOR updates, lekin sirf kuch indices ki value chahiye
 *    Example: "after Q range flips, what is arr[k]?"
 *    Lazy?  : HAAN — range flip poori range walk kiye bina
 *
 * 3️⃣ Range XOR Update + Range XOR Query
 *    Update : arr[L..R] ^= val
 *    Query  : arr[L..R] ka XOR
 *    Kab    : dono taraf range — flip bhi range me, XOR bhi range me
 *    Example: heavy range flip + range XOR queries (powerful, lazy must)
 *    Lazy?  : HAAN + query ke waqt push + partial update pe parent refresh
 *
 * SUM vs XOR lazy difference:
 *   SUM range += v  → segment_sum += v * len        (hamesha badhta hai)
 *   XOR range ^= v  → segment_xor ^= v  (sirf odd len) (parity matter karti hai)
 *
 * Fenwick/XOR note:
 *   Prefix XOR se range XOR nikal sakte ho: xor(0,R) ^ xor(0,L-1)
 *   Lekin range XOR UPDATE Fenwick se mushkil — isliye lazy seg tree best.
 *
 * Time: sab variations — build O(n), update/query O(log n)
 * ════════════════════════════════════════════════════════════════════════════
 */

// ════════════════════════════════════════════════════════════════════════════
// 1️⃣ Point Update + Range XOR Query
// ════════════════════════════════════════════════════════════════════════════
class XorSeg_PointUpdate_RangeQuery {
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
        tree[node] = tree[2 * node + 1] ^ tree[2 * node + 2];
    }

    // Point SET: arr[idx] = val (poori value replace)
    void pointSet(int node, int l, int r, int idx, int val) {
        if (l == r) {
            tree[node] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) pointSet(2 * node + 1, l, mid, idx, val);
        else            pointSet(2 * node + 2, mid + 1, r, idx, val);
        tree[node] = tree[2 * node + 1] ^ tree[2 * node + 2];
    }

    // Range XOR query — 3 cases: no overlap→0 | full→tree[node] | partial→recurse
    int rangeXor(int node, int l, int r, int ql, int qr) const {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        return rangeXor(2 * node + 1, l, mid, ql, qr)
             ^ rangeXor(2 * node + 2, mid + 1, r, ql, qr);
    }

public:
    XorSeg_PointUpdate_RangeQuery(const vector<int>& arr) {
        n = (int)arr.size();
        tree.assign(4 * max(n, 1), 0);
        if (n > 0) build(arr, 0, 0, n - 1);
    }

    void pointUpdate(int idx, int val) { pointSet(0, 0, n - 1, idx, val); }
    int rangeXor(int L, int R) const { return rangeXor(0, 0, n - 1, L, R); }
};

// ════════════════════════════════════════════════════════════════════════════
// 2️⃣ Range XOR Update + Point Query  (lazy XOR)
// ════════════════════════════════════════════════════════════════════════════
class XorSeg_RangeUpdate_PointQuery {
private:
    int n;
    vector<int> tree;  // segment XOR (internal consistency ke liye)
    vector<int> lazy;  // pending XOR flip sab elements par

    void build(const vector<int>& arr, int node, int l, int r) {
        if (l == r) {
            tree[node] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * node + 1, l, mid);
        build(arr, 2 * node + 2, mid + 1, r);
        tree[node] = tree[2 * node + 1] ^ tree[2 * node + 2];
    }

    // Lazy apply: segment [l,r] ke SAB elements ^= v
    // segment XOR tabhi flip jab length odd ho
    void apply(int node, int l, int r, int v) {
        int len = r - l + 1;
        if (len & 1) tree[node] ^= v;
        lazy[node] ^= v;
    }

    void push(int node, int l, int r) {
        if (lazy[node] == 0) return;
        int mid = (l + r) / 2;
        apply(2 * node + 1, l, mid, lazy[node]);
        apply(2 * node + 2, mid + 1, r, lazy[node]);
        lazy[node] = 0;
    }

    // Range XOR: [ql,qr] me har element ^= val
    void rangeXorUpdate(int node, int l, int r, int ql, int qr, int val) {
        push(node, l, r);
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            apply(node, l, r, val);
            return;
        }
        int mid = (l + r) / 2;
        rangeXorUpdate(2 * node + 1, l, mid, ql, qr, val);
        rangeXorUpdate(2 * node + 2, mid + 1, r, ql, qr, val);
        // sirf point query chahiye — parent refresh optional (yahan skip)
    }

    // Point query: index idx ki value — root se leaf, raaste me push
    int pointQuery(int node, int l, int r, int idx) {
        push(node, l, r);
        if (l == r) return tree[node];
        int mid = (l + r) / 2;
        if (idx <= mid) return pointQuery(2 * node + 1, l, mid, idx);
        return pointQuery(2 * node + 2, mid + 1, r, idx);
    }

public:
    XorSeg_RangeUpdate_PointQuery(const vector<int>& arr) {
        n = (int)arr.size();
        tree.assign(4 * max(n, 1), 0);
        lazy.assign(4 * max(n, 1), 0);
        if (n > 0) build(arr, 0, 0, n - 1);
    }

    void rangeXorUpdate(int L, int R, int val) {
        rangeXorUpdate(0, 0, n - 1, L, R, val);
    }

    int pointQuery(int idx) { return pointQuery(0, 0, n - 1, idx); }
};

// ════════════════════════════════════════════════════════════════════════════
// 3️⃣ Range XOR Update + Range XOR Query  (lazy XOR + parent refresh)
// ════════════════════════════════════════════════════════════════════════════
class XorSeg_RangeUpdate_RangeQuery {
private:
    int n;
    vector<int> tree;
    vector<int> lazy;

    void build(const vector<int>& arr, int node, int l, int r) {
        if (l == r) {
            tree[node] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * node + 1, l, mid);
        build(arr, 2 * node + 2, mid + 1, r);
        tree[node] = tree[2 * node + 1] ^ tree[2 * node + 2];
    }

    void apply(int node, int l, int r, int v) {
        int len = r - l + 1;
        if (len & 1) tree[node] ^= v;
        lazy[node] ^= v;
    }

    void push(int node, int l, int r) {
        if (lazy[node] == 0) return;
        int mid = (l + r) / 2;
        apply(2 * node + 1, l, mid, lazy[node]);
        apply(2 * node + 2, mid + 1, r, lazy[node]);
        lazy[node] = 0;
    }

    void rangeXorUpdate(int node, int l, int r, int ql, int qr, int val) {
        push(node, l, r);
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            apply(node, l, r, val);
            return;
        }
        int mid = (l + r) / 2;
        rangeXorUpdate(2 * node + 1, l, mid, ql, qr, val);
        rangeXorUpdate(2 * node + 2, mid + 1, r, ql, qr, val);
        tree[node] = tree[2 * node + 1] ^ tree[2 * node + 2];  // range query ke liye refresh
    }

    int rangeXor(int node, int l, int r, int ql, int qr) {
        push(node, l, r);
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        return rangeXor(2 * node + 1, l, mid, ql, qr)
             ^ rangeXor(2 * node + 2, mid + 1, r, ql, qr);
    }

public:
    XorSeg_RangeUpdate_RangeQuery(const vector<int>& arr) {
        n = (int)arr.size();
        tree.assign(4 * max(n, 1), 0);
        lazy.assign(4 * max(n, 1), 0);
        if (n > 0) build(arr, 0, 0, n - 1);
    }

    void rangeXorUpdate(int L, int R, int val) {
        rangeXorUpdate(0, 0, n - 1, L, R, val);
    }

    int rangeXor(int L, int R) {
        return rangeXor(0, 0, n - 1, L, R);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> arr = {1, 2, 3, 4, 5};

    // ── 1️⃣ Point Update + Range XOR ──────────────────────────────────────
    cout << "══════════════════════════════════════════════════════════\n";
    cout << "1️⃣ Point Update + Range XOR Query\n";
    cout << "   Use when: ek index SET karna ho, range XOR maango\n";
    cout << "══════════════════════════════════════════════════════════\n";
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    XorSeg_PointUpdate_RangeQuery st1(arr);
    cout << "XOR(0,4) = " << st1.rangeXor(0, 4) << "  (1^2^3^4^5 = 1)\n";
    cout << "XOR(1,3) = " << st1.rangeXor(1, 3) << "  (2^3^4 = 5)\n";

    st1.pointUpdate(0, 5);  // arr[0] = 5 set
    cout << "Point set arr[0]=5 → XOR(0,4) = " << st1.rangeXor(0, 4) << "\n";

    // ── 2️⃣ Range XOR Update + Point Query ────────────────────────────────
    cout << "\n══════════════════════════════════════════════════════════\n";
    cout << "2️⃣ Range XOR Update + Point Query\n";
    cout << "   Use when: range me ^= flip karo, kisi EK index ki value maango\n";
    cout << "══════════════════════════════════════════════════════════\n";

    XorSeg_RangeUpdate_PointQuery st2(arr);
    cout << "Start arr[2] = " << st2.pointQuery(2) << " (3)\n";

    st2.rangeXorUpdate(1, 3, 7);  // arr[1..3] ^= 7
    // arr: [1, 2^7=5, 3^7=4, 4^7=3, 5]
    cout << "Range [1,3] ^= 7:\n";
    cout << "  arr[1] = " << st2.pointQuery(1) << " (expected 5)\n";
    cout << "  arr[2] = " << st2.pointQuery(2) << " (expected 4)\n";
    cout << "  arr[3] = " << st2.pointQuery(3) << " (expected 3)\n";
    cout << "  arr[4] = " << st2.pointQuery(4) << " (unchanged 5)\n";

    // ── 3️⃣ Range XOR Update + Range XOR Query ────────────────────────────
    cout << "\n══════════════════════════════════════════════════════════\n";
    cout << "3️⃣ Range XOR Update + Range XOR Query\n";
    cout << "   Use when: range flip + range XOR dono heavy hon\n";
    cout << "══════════════════════════════════════════════════════════\n";

    XorSeg_RangeUpdate_RangeQuery st3(arr);
    cout << "Initial XOR(0,4) = " << st3.rangeXor(0, 4) << "\n";

    st3.rangeXorUpdate(0, 2, 10);  // [0,2] ^= 10
    // arr: [1^10=11, 2^10=8, 3^10=9, 4, 5]
    cout << "After [0,2] ^= 10:\n";
    cout << "  XOR(0,2) = " << st3.rangeXor(0, 2) << " (11^8^9 = 10)\n";
    cout << "  XOR(0,4) = " << st3.rangeXor(0, 4) << "\n";

    st3.rangeXorUpdate(2, 4, 6);
    cout << "After [2,4] ^= 6:\n";
    cout << "  XOR(2,4) = " << st3.rangeXor(2, 4) << "\n";
    cout << "  XOR(0,4) = " << st3.rangeXor(0, 4) << "\n";

    // ── Quick decision recap ─────────────────────────────────────────────
    cout << "\n══════════════════════════════════════════════════════════\n";
    cout << "QUICK PICK:\n";
    cout << "  arr[i] = val + range XOR     → 1️⃣ PointUpdate_RangeQuery\n";
    cout << "  arr[L..R] ^= v + arr[i] ask  → 2️⃣ RangeUpdate_PointQuery\n";
    cout << "  arr[L..R] ^= v + range XOR   → 3️⃣ RangeUpdate_RangeQuery\n";
    cout << "══════════════════════════════════════════════════════════\n";

    return 0;
}
