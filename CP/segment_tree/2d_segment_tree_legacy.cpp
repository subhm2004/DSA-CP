// 2D segment tree ka code
#include <bits/stdc++.h>
using namespace std;

// --------------------------------------------------------
// 1D Segment Tree (same as tera existing design, sum ke liye)
// --------------------------------------------------------
class SegTree1D
{
private:
    vector<int> seg;
    int n;

    void build(vector<int> &arr, int i, int l, int r)
    {
        if (l == r)
        {
            seg[i] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * i + 1, l, mid);
        build(arr, 2 * i + 2, mid + 1, r);
        seg[i] = seg[2 * i + 1] + seg[2 * i + 2]; // sum
    }

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

    int query(int i, int l, int r, int ql, int qr)
    {
        if (r < ql || l > qr)
            return 0;
        if (ql <= l && r <= qr)
            return seg[i];
        int mid = (l + r) / 2;
        return query(2 * i + 1, l, mid, ql, qr) + query(2 * i + 2, mid + 1, r, ql, qr);
    }

public:
    SegTree1D() {}
    SegTree1D(vector<int> &arr)
    {
        n = arr.size();
        seg.resize(4 * n);
        build(arr, 0, 0, n - 1);
    }

    void update(int idx, int val)
    {
        update(0, 0, n - 1, idx, val);
    }

    int query(int l, int r)
    {
        return query(0, 0, n - 1, l, r);
    }
};

// --------------------------------------------------------
// 2D Segment Tree
// Har row ke liye ek 1D SegTree bana diya
// Rows ke upar bhi ek outer tree hai
// --------------------------------------------------------
class SegTree2D
{
private:
    vector<SegTree1D> rowTrees; // har node ke liye ek 1D tree
    vector<vector<int>> mat;    // original matrix (update ke liye)
    int n, m;                   // n = rows, m = cols

    // Outer tree build: row dimension pe
    void build(int i, int l, int r)
    {
        if (l == r)
        {
            // Leaf node = directly us row ka segment tree
            rowTrees[i] = SegTree1D(mat[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(2 * i + 1, l, mid);
        build(2 * i + 2, mid + 1, r);

        // Inner node = merged row banao (element-wise sum)
        vector<int> merged(m);
        for (int j = 0; j < m; j++)
            merged[j] = rowTrees[2 * i + 1].query(j, j) + rowTrees[2 * i + 2].query(j, j);
        rowTrees[i] = SegTree1D(merged);
    }

    // Point update: (row, col) pe naya value
    void update(int i, int l, int r, int row, int col, int val)
    {
        if (l == r)
        {
            rowTrees[i].update(col, val);
            return;
        }
        int mid = (l + r) / 2;
        if (row <= mid)
            update(2 * i + 1, l, mid, row, col, val);
        else
            update(2 * i + 2, mid + 1, r, row, col, val);

        // Parent update: dono children ka sum us col pe
        int newVal = rowTrees[2 * i + 1].query(col, col) + rowTrees[2 * i + 2].query(col, col);
        rowTrees[i].update(col, newVal);
    }

    // Range query: row[r1..r2], col[c1..c2] ka sum
    int query(int i, int l, int r, int r1, int r2, int c1, int c2)
    {
        if (r < r1 || l > r2)
            return 0;
        if (r1 <= l && r <= r2)
            return rowTrees[i].query(c1, c2); // pure row range

        int mid = (l + r) / 2;
        return query(2 * i + 1, l, mid, r1, r2, c1, c2) + query(2 * i + 2, mid + 1, r, r1, r2, c1, c2);
    }

public:
    SegTree2D(vector<vector<int>> &matrix)
    {
        mat = matrix;
        n = mat.size();
        m = mat[0].size();
        rowTrees.resize(4 * n);
        build(0, 0, n - 1);
    }

    // update(row, col, newVal)
    void update(int row, int col, int val)
    {
        mat[row][col] = val;
        update(0, 0, n - 1, row, col, val);
    }

    // query(r1, c1, r2, c2) = sum of submatrix
    int query(int r1, int c1, int r2, int c2)
    {
        return query(0, 0, n - 1, r1, r2, c1, c2);
    }
};

// --------------------------------------------------------
// Main
// --------------------------------------------------------
int main()
{
    vector<vector<int>> mat = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}};

    SegTree2D seg(mat);

    // Poori matrix ka sum
    cout << "Sum of whole matrix: ";
    cout << seg.query(0, 0, 3, 3) << endl; // 136

    // Submatrix [1..2][1..2] ka sum
    cout << "Sum of rows[1..2] cols[1..2]: ";
    cout << seg.query(1, 1, 2, 2) << endl; // 6+7+10+11 = 34

    // Update (1,1) = 100
    seg.update(1, 1, 100);
    cout << "After update (1,1)=100: ";
    cout << "Sum of rows[1..2] cols[1..2]: ";
    cout << seg.query(1, 1, 2, 2) << endl; // 100+7+10+11 = 128

    return 0;
}