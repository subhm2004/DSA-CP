#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * SEGMENT TREE BEATS — Range chmin / chmax / add + Range Sum
 * ════════════════════════════════════════════════════════════════════════════
 *
 * PROBLEM TYPE (hard but famous in CP):
 *   Array par ye operations:
 *     1) Range add:     arr[i] += v
 *     2) Range chmin:   arr[i] = min(arr[i], v)   — ceiling lagao
 *     3) Range chmax:   arr[i] = max(arr[i], v)   — floor lagao
 *     4) Range sum query
 *
 * Example: arr = [5, 5, 5, 5]
 *   chmin(0,3, 3) → [3,3,3,3], sum=12
 *   add(1,2, 10)  → [3,13,13,3], sum=32
 *
 * NORMAL LAZY KYUN NAHI?
 *   chmin/chmax "non-uniform" hai — ek range me alag alag elements alag badalte hain.
 *   Beats me har node extra info rakhta hai: min, max, second min/max, count.
 *   Jab poora segment same nahi, sirf "top layer" (max ya min wale) ko tag karte hain.
 *   Worst case amortized O(log n) per operation (proof heavy, template yaad rakho).
 *
 * NODE FIELDS:
 *   sum, minv, maxv, secmn, secmx, mncnt, mxcnt
 *
 * Time: amortized O(log n) per update/query
 * ════════════════════════════════════════════════════════════════════════════
 */

struct BeatsNode {
    long long sum = 0;
    long long minv = 0, maxv = 0;
    long long secmn = (long long)4e18, secmx = (long long)-4e18;
    int mncnt = 0, mxcnt = 0;
    long long add = 0;
};

class SegmentTreeBeats {
private:
    int n;
    vector<BeatsNode> t;

    void pull(int o) {
        auto& p = t[o];
        const auto& L = t[o << 1], &R = t[o << 1 | 1];
        p.sum = L.sum + R.sum;
        p.minv = min(L.minv, R.minv);
        p.maxv = max(L.maxv, R.maxv);

        p.mncnt = p.mxcnt = 0;
        if (L.minv == p.minv) p.mncnt += L.mncnt;
        if (R.minv == p.minv) p.mncnt += R.mncnt;
        if (L.maxv == p.maxv) p.mxcnt += L.mxcnt;
        if (R.maxv == p.maxv) p.mxcnt += R.mxcnt;

        p.secmn = (long long)4e18;
        p.secmx = (long long)-4e18;
        for (long long v : {L.minv, R.minv}) if (v > p.minv) p.secmn = min(p.secmn, v);
        for (long long v : {L.secmn, R.secmn}) if (v > p.minv) p.secmn = min(p.secmn, v);
        for (long long v : {L.maxv, R.maxv}) if (v < p.maxv) p.secmx = max(p.secmx, v);
        for (long long v : {L.secmx, R.secmx}) if (v < p.maxv) p.secmx = max(p.secmx, v);
    }

    void applyAdd(int o, int len, long long v) {
        auto& p = t[o];
        p.sum += v * len;
        p.minv += v; p.maxv += v;
        if (p.secmn < (long long)4e18) p.secmn += v;
        if (p.secmx > (long long)-4e18) p.secmx += v;
        p.add += v;
    }

    void applyChmin(int o, long long v) {
        auto& p = t[o];
        p.sum += (v - p.maxv) * p.mxcnt;
        if (p.mncnt == p.mxcnt) p.minv = v;
        p.maxv = v;
        if (p.secmx < (long long)4e18) p.secmx = max(p.secmx, v);
    }

    void applyChmax(int o, long long v) {
        auto& p = t[o];
        p.sum += (v - p.minv) * p.mncnt;
        if (p.mncnt == p.mxcnt) p.maxv = v;
        p.minv = v;
        if (p.secmn < (long long)4e18) p.secmn = min(p.secmn, v);
    }

    void push(int o, int l, int r) {
        auto& p = t[o];
        if (p.add != 0) {
            int mid = (l + r) >> 1;
            applyAdd(o << 1, mid - l + 1, p.add);
            applyAdd(o << 1 | 1, r - mid, p.add);
            p.add = 0;
        }
    }

    void pushDown(int o, int l, int r) {
        push(o, l, r);
        int mid = (l + r) >> 1;
        auto& p = t[o];
        if (p.maxv < t[o << 1].maxv) applyChmin(o << 1, p.maxv);
        if (p.maxv < t[o << 1 | 1].maxv) applyChmin(o << 1 | 1, p.maxv);
        if (p.minv > t[o << 1].minv) applyChmax(o << 1, p.minv);
        if (p.minv > t[o << 1 | 1].minv) applyChmax(o << 1 | 1, p.minv);
    }

    void build(const vector<int>& a, int o, int l, int r) {
        if (l == r) {
            t[o].sum = t[o].minv = t[o].maxv = a[l];
            t[o].mncnt = t[o].mxcnt = 1;
            return;
        }
        int mid = (l + r) >> 1;
        build(a, o << 1, l, mid);
        build(a, o << 1 | 1, mid + 1, r);
        pull(o);
    }

    void rangeAdd(int o, int l, int r, int ql, int qr, long long v) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            applyAdd(o, r - l + 1, v);
            return;
        }
        pushDown(o, l, r);
        int mid = (l + r) >> 1;
        rangeAdd(o << 1, l, mid, ql, qr, v);
        rangeAdd(o << 1 | 1, mid + 1, r, ql, qr, v);
        pull(o);
    }

    void rangeChmin(int o, int l, int r, int ql, int qr, long long v) {
        // maxv <= v → sab pehle se cap ke neeche, kuch badalne ki zarurat nahi
        if (qr < l || r < ql || t[o].maxv <= v) return;
        // poora segment same max hai aur sirf max wale ko cap karna hai
        if (ql <= l && r <= qr && t[o].minv == t[o].maxv) {
            applyChmin(o, v);
            return;
        }
        if (ql <= l && r <= qr && t[o].secmx < v) {
            applyChmin(o, v);
            return;
        }
        pushDown(o, l, r);
        int mid = (l + r) >> 1;
        rangeChmin(o << 1, l, mid, ql, qr, v);
        rangeChmin(o << 1 | 1, mid + 1, r, ql, qr, v);
        pull(o);
    }

    void rangeChmax(int o, int l, int r, int ql, int qr, long long v) {
        // minv >= v → sab pehle se floor ke upar, noop
        if (qr < l || r < ql || t[o].minv >= v) return;
        if (ql <= l && r <= qr && t[o].minv == t[o].maxv) {
            applyChmax(o, v);
            return;
        }
        if (ql <= l && r <= qr && t[o].secmn > v) {
            applyChmax(o, v);
            return;
        }
        pushDown(o, l, r);
        int mid = (l + r) >> 1;
        rangeChmax(o << 1, l, mid, ql, qr, v);
        rangeChmax(o << 1 | 1, mid + 1, r, ql, qr, v);
        pull(o);
    }

    long long rangeSum(int o, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return t[o].sum;
        pushDown(o, l, r);
        int mid = (l + r) >> 1;
        return rangeSum(o << 1, l, mid, ql, qr)
             + rangeSum(o << 1 | 1, mid + 1, r, ql, qr);
    }

public:
    SegmentTreeBeats(const vector<int>& a) {
        n = (int)a.size();
        t.assign(4 * max(n, 1), {});
        if (n > 0) build(a, 1, 0, n - 1);
    }

    void rangeAdd(int L, int R, long long v) { rangeAdd(1, 0, n - 1, L, R, v); }
    void rangeChmin(int L, int R, long long v) { rangeChmin(1, 0, n - 1, L, R, v); }
    void rangeChmax(int L, int R, long long v) { rangeChmax(1, 0, n - 1, L, R, v); }
    long long rangeSum(int L, int R) { return rangeSum(1, 0, n - 1, L, R); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> arr = {5, 5, 5, 5};
    SegmentTreeBeats st(arr);

    cout << "Initial sum(0,3) = " << st.rangeSum(0, 3) << "\n";

    cout << "chmin(0,3, 3) -> sabko min(x,3)\n";
    st.rangeChmin(0, 3, 3);
    cout << "Sum = " << st.rangeSum(0, 3) << " (expected 12)\n";

    cout << "add(1,2, 10)\n";
    st.rangeAdd(1, 2, 10);
    cout << "Sum = " << st.rangeSum(0, 3) << " (expected 32)\n";

    cout << "chmax(0,1, 8)\n";
    st.rangeChmax(0, 1, 8);
    cout << "Sum = " << st.rangeSum(0, 3) << "\n";

    return 0;
}
