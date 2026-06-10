#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LEETCODE 307 — Range Sum Query Mutable
// ────────────────────────────────────────────────────────────────────────────
// Problem: Array pe point update + range sum query
// Approach: Classic sum segment tree (point update, range query)
//   update(i, val)  -> leaf tak jao, wapas sum refresh
//   sumRange(l, r)  -> 3-case recursive range sum
// Complexity: build O(n) | update O(log n) | query O(log n)
// ════════════════════════════════════════════════════════════════════════════

class NumArray
{
    vector<long long> seg;
    int n;

    // ── build: leaf pe nums[i], internal pe left+right sum ────────────────────
    void build(const vector<int> &nums, int i, int l, int r)
    {
        if (l == r)
        {
            seg[i] = nums[l];
            return;
        }
        int mid = (l + r) / 2;
        build(nums, 2 * i + 1, l, mid);
        build(nums, 2 * i + 2, mid + 1, r);
        seg[i] = seg[2 * i + 1] + seg[2 * i + 2];
    }

    // ── update: index idx ki value val set karo ───────────────────────────────
    void update(int i, int l, int r, int idx, int val)
    {
        if (l == r)
        {
            seg[i] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid)
            update(2 * i + 1, l, mid, idx, val);
        else
            update(2 * i + 2, mid + 1, r, idx, val);
        seg[i] = seg[2 * i + 1] + seg[2 * i + 2];
    }

    // ── query: [ql,qr] range ka sum ───────────────────────────────────────────
    long long query(int ql, int qr, int i, int l, int r)
    {
        if (r < ql || l > qr)
            return 0;
        if (ql <= l && r <= qr)
            return seg[i];
        int mid = (l + r) / 2;
        return query(ql, qr, 2 * i + 1, l, mid) + query(ql, qr, 2 * i + 2, mid + 1, r);
    }

public:
    // ── NumArray: nums se segment tree build ──────────────────────────────────
    NumArray(vector<int> &nums)
    {
        n = (int)nums.size();
        seg.assign(4 * n, 0);
        if (n > 0)
            build(nums, 0, 0, n - 1);
    }

    void update(int index, int val)
    {
        update(0, 0, n - 1, index, val);
    }

    int sumRange(int left, int right)
    {
        return (int)query(left, right, 0, 0, n - 1);
    }
};

int main()
{
    vector<int> nums = {1, 3, 5, 7, 9, 11};
    NumArray arr(nums);

    cout << "sumRange(1,3) = " << arr.sumRange(1, 3) << "\n"; // 15
    arr.update(1, 10);
    cout << "after update(1,10), sumRange(1,3) = " << arr.sumRange(1, 3) << "\n"; // 22

    return 0;
}
