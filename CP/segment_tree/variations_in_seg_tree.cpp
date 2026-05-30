#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ---------------------- 1️⃣ Point Update + Range Query ----------------------
class SegmentTree_PointUpdate_RangeQuery
{
private:
    vector<ll> segTree;
    int n;

    void build(const vector<int> &arr, int i, int l, int r)
    {
        if (l == r)
        {
            segTree[i] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * i + 1, l, mid);
        build(arr, 2 * i + 2, mid + 1, r);
        segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];
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
        segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];
    }

    ll query_Range(int i, int l, int r, int start, int end)
    {
        if (r < start || l > end)
            return 0;
        if (start <= l && r <= end)
            return segTree[i];
        int mid = (l + r) / 2;
        return query_Range(2 * i + 1, l, mid, start, end) + query_Range(2 * i + 2, mid + 1, r, start, end);
    }

public:
    SegmentTree_PointUpdate_RangeQuery(const vector<int> &arr)
    {
        n = arr.size();
        segTree.resize(4 * n);
        build(arr, 0, 0, n - 1);
    }
    void update_Point(int idx, int val) { update_Point(0, 0, n - 1, idx, val); }
    ll query_Range(int l, int r) { return query_Range(0, 0, n - 1, l, r); }
};

// ---------------------- 2️⃣ Range Update + Point Query ----------------------
class SegmentTree_RangeUpdate_PointQuery
{
private:
    vector<ll> segTree, lazy;
    int n;

    void build(const vector<int> &arr, int i, int l, int r)
    {
        if (l == r)
        {
            segTree[i] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * i + 1, l, mid);
        build(arr, 2 * i + 2, mid + 1, r);
        segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];
    }

    void push(int i, int l, int r)
    {
        if (lazy[i] != 0)
        {
            segTree[i] += (r - l + 1) * lazy[i];
            if (l != r)
            {
                lazy[2 * i + 1] += lazy[i];
                lazy[2 * i + 2] += lazy[i];
            }
            lazy[i] = 0;
        }
    }

    void update_Range(int i, int l, int r, int start, int end, int val)
    {
        push(i, l, r);
        if (r < start || l > end)
            return;
        if (start <= l && r <= end)
        {
            lazy[i] += val;
            push(i, l, r);
            return;
        }
        int mid = (l + r) / 2;
        update_Range(2 * i + 1, l, mid, start, end, val);
        update_Range(2 * i + 2, mid + 1, r, start, end, val);
    }

    ll query_Point(int i, int l, int r, int idx)
    {
        push(i, l, r);
        if (l == r)
            return segTree[i];
        int mid = (l + r) / 2;
        if (idx <= mid)
            return query_Point(2 * i + 1, l, mid, idx);
        else
            return query_Point(2 * i + 2, mid + 1, r, idx);
    }

public:
    SegmentTree_RangeUpdate_PointQuery(const vector<int> &arr)
    {
        n = arr.size();
        segTree.resize(4 * n);
        lazy.assign(4 * n, 0);
        build(arr, 0, 0, n - 1);
    }
    void update_Range(int l, int r, int val) { update_Range(0, 0, n - 1, l, r, val); }
    ll query_Point(int idx) { return query_Point(0, 0, n - 1, idx); }
};

// ---------------------- 3️⃣ Range Update + Range Query ----------------------
class SegmentTree_RangeUpdate_RangeQuery
{
private:
    vector<ll> segTree, lazy;
    int n;

    void build(const vector<int> &arr, int i, int l, int r)
    {
        if (l == r)
        {
            segTree[i] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * i + 1, l, mid);
        build(arr, 2 * i + 2, mid + 1, r);
        segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];
    }

    void push(int i, int l, int r)
    {
        if (lazy[i] != 0)
        {
            segTree[i] += (r - l + 1) * lazy[i];
            if (l != r)
            {
                lazy[2 * i + 1] += lazy[i];
                lazy[2 * i + 2] += lazy[i];
            }
            lazy[i] = 0;
        }
    }

    void update_Range(int i, int l, int r, int start, int end, int val)
    {
        push(i, l, r);
        if (r < start || l > end)
            return;
        if (start <= l && r <= end)
        {
            lazy[i] += val;
            push(i, l, r);
            return;
        }
        int mid = (l + r) / 2;
        update_Range(2 * i + 1, l, mid, start, end, val);
        update_Range(2 * i + 2, mid + 1, r, start, end, val);
        segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];
    }

    ll query_Range(int i, int l, int r, int start, int end)
    {
        push(i, l, r);
        if (r < start || l > end)
            return 0;
        if (start <= l && r <= end)
            return segTree[i];
        int mid = (l + r) / 2;
        return query_Range(2 * i + 1, l, mid, start, end) + query_Range(2 * i + 2, mid + 1, r, start, end);
    }

public:
    SegmentTree_RangeUpdate_RangeQuery(const vector<int> &arr)
    {
        n = arr.size();
        segTree.resize(4 * n);
        lazy.assign(4 * n, 0);
        build(arr, 0, 0, n - 1);
    }
    void update_Range(int l, int r, int val) { update_Range(0, 0, n - 1, l, r, val); }
    ll query_Range(int l, int r) { return query_Range(0, 0, n - 1, l, r); }
};

// ---------------------- Main function ----------------------
int main()
{
    vector<int> arr = {5, 3, 8, 6, 1, 4, 7, 9, 2, 0};

    cout << "---- 1️⃣ Point Update + Range Query ----\n";
    SegmentTree_PointUpdate_RangeQuery st1(arr);
    st1.update_Point(2, 10); // arr[2]=10
    cout << "Sum [0,4]: " << st1.query_Range(0, 4) << endl;
    cout << "Sum [2,6]: " << st1.query_Range(2, 6) << endl;

    cout << "\n---- 2️⃣ Range Update + Point Query ----\n";
    SegmentTree_RangeUpdate_PointQuery st2(arr);
    st2.update_Range(2, 6, 5);
    st2.update_Range(0, 4, 10);
    cout << "Value at index 2: " << st2.query_Point(2) << endl;
    cout << "Value at index 5: " << st2.query_Point(5) << endl;

    cout << "\n---- 3️⃣ Range Update + Range Query ----\n";
    SegmentTree_RangeUpdate_RangeQuery st3(arr);
    st3.update_Range(2, 6, 5);
    st3.update_Range(0, 4, 10);
    cout << "Sum [0,4]: " << st3.query_Range(0, 4) << endl;
    cout << "Sum [2,6]: " << st3.query_Range(2, 6) << endl;

    return 0;
}
