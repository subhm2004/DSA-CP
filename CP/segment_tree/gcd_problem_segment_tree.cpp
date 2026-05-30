#include <bits/stdc++.h>
using namespace std;

int GCD(int a, int b)
{
    if (b == 0)
        return a;

    return GCD(b, a % b);
}

class SegmentTree
{
private:
    vector<int> segTree;
    int n;

    void build(vector<int> &arr, int i, int l, int r)
    {
        if (l == r)
        {
            segTree[i] = arr[l];
            return;
        }

        int mid = (l + r) / 2;

        build(arr, 2 * i + 1, l, mid);
        build(arr, 2 * i + 2, mid + 1, r);

        segTree[i] = GCD(segTree[2 * i + 1], segTree[2 * i + 2]);
    }

    void update_Point(int i, int l, int r, int idx, int val)
    {
        if (l == r)
        {
            segTree[i] = val;
            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid)
            update_Point(2 * i + 1, l, mid, idx, val);
        else
            update_Point(2 * i + 2, mid + 1, r, idx, val);

        segTree[i] = GCD(segTree[2 * i + 1], segTree[2 * i + 2]);
    }

    int query_Range(int i, int l, int r, int start, int end)
    {
        if (r < start || l > end)
            return 0;

        if (start <= l && r <= end)
            return segTree[i];

        int mid = (l + r) / 2;

        return GCD(
            query_Range(2 * i + 1, l, mid, start, end),
            query_Range(2 * i + 2, mid + 1, r, start, end));
    }

public:
    SegmentTree(vector<int> &arr)
    {
        n = arr.size();
        segTree.resize(4 * n);

        build(arr, 0, 0, n - 1);
    }

    void update_Point(int idx, int val)
    {
        update_Point(0, 0, n - 1, idx, val);
    }

    int query_Range(int l, int r)
    {
        return query_Range(0, 0, n - 1, l, r);
    }
};

int main()
{
    vector<int> arr = {6, 12, 18, 24};

    vector<vector<int>> queries =
        {
            {1, 30},
            {3, 3156},
            {0, 438}};

    SegmentTree seg(arr);

    cout << "Initial GCD of whole array: ";
    cout << seg.query_Range(0, arr.size() - 1) << endl;

    for (auto q : queries)
    {
        int idx = q[0];
        int val = q[1];

        seg.update_Point(idx, val);

        cout << "After updating index " << idx << " to " << val << endl;

        cout << "Current GCD of whole array: ";
        cout << seg.query_Range(0, arr.size() - 1) << endl;
    }

    return 0;
}