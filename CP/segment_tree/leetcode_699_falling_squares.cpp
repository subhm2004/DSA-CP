#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LEETCODE 699 — Falling Squares
// ────────────────────────────────────────────────────────────────────────────
// Problem: Squares x-axis pe stack hote hain — har drop ke baad max height
// positions[i] = [left, side]  -> square covers x in [left, left+side)
// Approach: Coordinate compression (x-axis) + lazy max segment tree
//   base = range max on [left, left+side)
//   newH = base + side  -> poori range update
// Complexity: O(n log n)
// ════════════════════════════════════════════════════════════════════════════

class SegTreeMaxAssign
{
    int n;
    vector<int> tree;
    vector<int> lazy;

    // ── push: lazy chmax apply karo ───────────────────────────────────────────
    void push(int i, int l, int r)
    {
        if (lazy[i] == 0)
            return;
        tree[i] = max(tree[i], lazy[i]);
        if (l != r)
        {
            lazy[2 * i + 1] = max(lazy[2 * i + 1], lazy[i]);
            lazy[2 * i + 2] = max(lazy[2 * i + 2], lazy[i]);
        }
        lazy[i] = 0;
    }

    // ── query: [ql,qr] range max ──────────────────────────────────────────────
    int query(int ql, int qr, int i, int l, int r)
    {
        push(i, l, r);
        if (r < ql || l > qr)
            return 0;
        if (ql <= l && r <= qr)
            return tree[i];
        int mid = (l + r) / 2;
        return max(query(ql, qr, 2 * i + 1, l, mid),
                   query(ql, qr, 2 * i + 2, mid + 1, r));
    }

    // ── update: range pe height val (chmax lazy) ──────────────────────────────
    void update(int ql, int qr, int val, int i, int l, int r)
    {
        push(i, l, r);
        if (r < ql || l > qr)
            return;
        if (ql <= l && r <= qr)
        {
            lazy[i] = max(lazy[i], val);
            push(i, l, r);
            return;
        }
        int mid = (l + r) / 2;
        update(ql, qr, val, 2 * i + 1, l, mid);
        update(ql, qr, val, 2 * i + 2, mid + 1, r);
        tree[i] = max(tree[2 * i + 1], tree[2 * i + 2]);
    }

public:
    SegTreeMaxAssign(int n) : n(n), tree(4 * n, 0), lazy(4 * n, 0) {}

    int rangeMax(int l, int r) { return query(l, r, 0, 0, n - 1); }
    void rangeAssignMax(int l, int r, int val) { update(l, r, val, 0, 0, n - 1); }
};

class Solution
{
public:
    // ── fallingSquares: har square drop ke baad global max height ─────────────
    //   1) left aur left+side se x coordinates compress
    //   2) har square: base = max height in uski x-range
    //   3) newH = base + side, range update, ans push
    vector<int> fallingSquares(vector<vector<int>> &positions)
    {
        vector<int> coords;
        for (const vector<int> &p : positions)
        {
            coords.push_back(p[0]);
            coords.push_back(p[0] + p[1]);
        }
        sort(coords.begin(), coords.end());
        coords.erase(unique(coords.begin(), coords.end()), coords.end());

        auto getId = [&](int x) {
            return (int)(lower_bound(coords.begin(), coords.end(), x) - coords.begin());
        };

        int m = (int)coords.size();
        SegTreeMaxAssign seg(m);
        vector<int> ans;
        int best = 0;

        for (const vector<int> &p : positions)
        {
            int left = p[0], side = p[1];
            int l = getId(left);
            int r = getId(left + side) - 1;
            if (r < l)
                r = l;

            int base = seg.rangeMax(l, r);
            int newH = base + side;
            seg.rangeAssignMax(l, r, newH);
            best = max(best, newH);
            ans.push_back(best);
        }

        return ans;
    }
};

int main()
{
    Solution sol;

    // LC example: [[1,2],[2,3],[6,1]] -> [2,5,5]
    vector<vector<int>> positions = {{1, 2}, {2, 3}, {6, 1}};
    vector<int> res = sol.fallingSquares(positions);

    cout << "Heights after each square: ";
    for (int h : res)
        cout << h << " ";
    cout << "\n";

    return 0;
}
