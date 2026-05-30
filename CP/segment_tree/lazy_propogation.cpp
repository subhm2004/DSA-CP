#include <bits/stdc++.h> // Segment tree with lazy propagation
// This code implements a segment tree with lazy propagation for range updates and point updates.
// It allows for efficient range sum queries and updates on an array.
// The segment tree is built from an initial array, and it supports operations to update a range by adding a value,
// update a specific index to a new value, and query the sum of elements in a given range.
// This code is designed to be efficient for large arrays and multiple queries, making it suitable for competitive programming and algorithmic challenges.
using namespace std;
using ll = long long;
class SegmentTree // Range Sum Segment Tree with Lazy Propagation
{
private:
    vector<ll> segTree; // stores sum in range
    vector<ll> lazy;    // lazy propagation array
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

    void update_Range(int i, int l, int r, int start, int end, int val) // Update range [start, end] by adding val
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
        return query_Range(2 * i + 1, l, mid, start, end) +
               query_Range(2 * i + 2, mid + 1, r, start, end);
    }

    void update_Index(int i, int l, int r, int idx, int new_val)
    {
        push(i, l, r);
        if (l == r)
        {
            segTree[i] = new_val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid)
            update_Index(2 * i + 1, l, mid, idx, new_val);
        else
            update_Index(2 * i + 2, mid + 1, r, idx, new_val);

        segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];
    }

public:
    SegmentTree(const vector<int> &arr)
    {
        n = arr.size();
        segTree.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(arr, 0, 0, n - 1);
    }

    void update_Range(int l, int r, int val)
    {
        update_Range(0, 0, n - 1, l, r, val);
    }

    void update_Index(int idx, int new_val)
    {
        update_Index(0, 0, n - 1, idx, new_val);
    }

    ll querySum(int l, int r)
    {
        return query_Range(0, 0, n - 1, l, r);
    }
};
int main()
{
    vector<int> arr = {5, 3, 8, 6, 1, 4, 7, 9, 2, 0};
    SegmentTree st(arr);

    cout << "Initial sum [0, 9]: " << st.querySum(0, 9) << endl;

    // 🔁 Multiple Range Updates
    st.update_Range(2, 6, 5);  // +5 to [2,6]
    st.update_Range(0, 4, 10); // +10 to [0,4]
    st.update_Range(5, 9, -3); // -3 to [5,9]
    st.update_Range(3, 8, 7);  // +7 to [3,8]

    // 🎯 Multiple Point Updates (overwrite value)
    st.update_Index(2, 10); // arr[2] = 10
    st.update_Index(5, 25); // arr[5] = 25
    st.update_Index(9, 50); // arr[9] = 50

    // ❓ Range Queries
    cout << "Sum [0, 4]: " << st.querySum(0, 4) << endl;
    cout << "Sum [2, 6]: " << st.querySum(2, 6) << endl;
    cout << "Sum [5, 9]: " << st.querySum(5, 9) << endl;
    cout << "Sum [0, 9]: " << st.querySum(0, 9) << endl;
    cout << "Sum [3, 8]: " << st.querySum(3, 8) << endl;

    return 0;
}