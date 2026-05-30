#include <bits/stdc++.h>
using namespace std;

class SegmentTree
{
public:
    int n;
    vector<int> mini_segtree;
    vector<int> maxi_segtree;
    vector<int> lazy;

    SegmentTree(int _n)
    {
        n = _n;
        mini_segtree.assign(4 * n, 0);
        maxi_segtree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    void push(int i, int l, int r)
    {
        if (lazy[i] != 0)
        {
            mini_segtree[i] += lazy[i];
            maxi_segtree[i] += lazy[i];

            if (l != r)
            {
                lazy[2 * i + 1] += lazy[i];
                lazy[2 * i + 2] += lazy[i];
            }
            lazy[i] = 0;
        }
    }

    void range_update(int ql, int qr, int i, int l, int r, int val)
    {
        push(i, l, r);

        if (r < ql || l > qr)
            return;

        if (ql <= l && r <= qr)
        {
            lazy[i] += val;
            push(i, l, r);
            return;
        }

        int mid = (l + r) / 2;
        range_update(ql, qr, 2 * i + 1, l, mid, val);
        range_update(ql, qr, 2 * i + 2, mid + 1, r, val);

        mini_segtree[i] = min(mini_segtree[2 * i + 1], mini_segtree[2 * i + 2]);
        maxi_segtree[i] = max(maxi_segtree[2 * i + 1], maxi_segtree[2 * i + 2]);
    }

    int min_query(int ql, int qr, int i, int l, int r)
    {
        push(i, l, r);

        if (r < ql || l > qr)
            return INT_MAX;

        if (ql <= l && r <= qr)
            return mini_segtree[i];

        int mid = (l + r) / 2;
        return min(
            min_query(ql, qr, 2 * i + 1, l, mid),
            min_query(ql, qr, 2 * i + 2, mid + 1, r));
    }

    int max_query(int ql, int qr, int i, int l, int r)
    {
        push(i, l, r);

        if (r < ql || l > qr)
            return INT_MIN;

        if (ql <= l && r <= qr)
            return maxi_segtree[i];

        int mid = (l + r) / 2;
        return max(
            max_query(ql, qr, 2 * i + 1, l, mid),
            max_query(ql, qr, 2 * i + 2, mid + 1, r));
    }

    int point_query(int idx, int i, int l, int r)
    {
        push(i, l, r);

        if (l == r)
            return mini_segtree[i];

        int mid = (l + r) / 2;
        if (idx <= mid)
            return point_query(idx, 2 * i + 1, l, mid);
        else
            return point_query(idx, 2 * i + 2, mid + 1, r);
    }

    // wrappers
    void range_update(int l, int r, int val)
    {
        range_update(l, r, 0, 0, n - 1, val);
    }

    int rangeMin(int l, int r)
    {
        return min_query(l, r, 0, 0, n - 1);
    }

    int rangeMax(int l, int r)
    {
        return max_query(l, r, 0, 0, n - 1);
    }

    int get_val(int idx)
    {
        return point_query(idx, 0, 0, n - 1);
    }
};

int main()
{
    // ---- Hard coded test cases ----

    int n = 8;
    SegmentTree seg(n);

    cout << "Initially all values are 0\n\n";

    // add 5 to range [2,6]
    seg.range_update(2, 6, 5);
    cout << "After range_update(2, 6, 5)\n";

    cout << "Min [0,7] = " << seg.rangeMin(0, 7) << "\n";
    cout << "Max [0,7] = " << seg.rangeMax(0, 7) << "\n\n";

    // add -3 to range [4,7]
    seg.range_update(4, 7, -3);
    cout << "After range_update(4, 7, -3)\n";

    cout << "Min [0,7] = " << seg.rangeMin(0, 7) << "\n";
    cout << "Max [0,7] = " << seg.rangeMax(0, 7) << "\n\n";

    // add 10 to range [0,3]
    seg.range_update(0, 3, 10);
    cout << "After range_update(0, 3, 10)\n";

    cout << "Min [0,7] = " << seg.rangeMin(0, 7) << "\n";
    cout << "Max [0,7] = " << seg.rangeMax(0, 7) << "\n\n";

    cout << "Point values:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "index " << i << " -> " << seg.get_val(i) << "\n";
    }

    cout << "\nSome sub-range queries:\n";
    cout << "Min [2,5] = " << seg.rangeMin(2, 5) << "\n";
    cout << "Max [2,5] = " << seg.rangeMax(2, 5) << "\n";

    return 0;
}
