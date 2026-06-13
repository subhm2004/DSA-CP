#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * 2D SEGMENT TREE — SUM
 * APPROACH : Tree of Trees  (outer rows + inner SegTree1D objects)
 * UPDATE   : Point (row, col) pe value set
 * QUERY    : Submatrix rectangle sum
 * LAZY     : NO
 * COMPLEX  : build O(n·m·log m) approx | update/query O(log n · log m)
 * ════════════════════════════════════════════════════════════════════════════
 * Samajhne ke liye best approach:
 *   Outer tree ke har node pe ek REAL 1D segment tree object hai.
 *   Wo 1D tree columns sambhaalta hai — bilkul 1D sum seg tree jaisa.
 *
 * Build trick (internal row node):
 *   left child ka col j + right child ka col j → merged[j] → parent ka 1D tree
 * ════════════════════════════════════════════════════════════════════════════
 */

// ── Inner 1D Segment Tree (columns ke liye) ─────────────────────────────────
class SegTree1D_Sum
{
private:
    vector<int> seg;
    int n;

    // ── Common 1D params ──
    //   i -> node index (root=0), l/r -> segment, ql/qr -> query range

    // ── build: column array se 1D sum tree banao ──
    //   1) leaf → seg[i] = arr[l]
    //   2) internal → mid split, bachho build, parent = left + right
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
        seg[i] = seg[2 * i + 1] + seg[2 * i + 2];
    }

    // ── update: column idx pe val set karo ──
    //   1) leaf pe val assign
    //   2) wapas aate waqt parent sum refresh
    void update(int i, int l, int r, int idx, int val)
    {
        if (l == r)
        {
            seg[i] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid)
        {
            update(2 * i + 1, l, mid, idx, val);
        }
        else
        {
            update(2 * i + 2, mid + 1, r, idx, val);
        }
        seg[i] = seg[2 * i + 1] + seg[2 * i + 2];
    }

    // ── query: columns [ql,qr] ka sum ──
    //   3-case: NO overlap→0 | FULL→seg[i] | PARTIAL→left+right
    int query(int i, int l, int r, int ql, int qr) const
    {
        if (r < ql || l > qr)
        {
            return 0;
        }
        if (ql <= l && r <= qr)
        {
            return seg[i];
        }
        int mid = (l + r) / 2;
        return query(2 * i + 1, l, mid, ql, qr) + query(2 * i + 2, mid + 1, r, ql, qr);
    }

public:
    // ── default ctor: empty (outer vector resize ke liye) ──
    SegTree1D_Sum() {}

    // ── arr se column tree banao ──
    SegTree1D_Sum(vector<int> &arr)
    {
        n = (int)arr.size();
        seg.assign(4 * max(n, 1), 0);
        if (n > 0)
        {
            build(arr, 0, 0, n - 1);
        }
    }

    // ── public: column idx update ──
    void update(int idx, int val)
    {
        update(0, 0, n - 1, idx, val);
    }

    // ── public: columns [l,r] sum ──
    int query(int l, int r) const
    {
        return query(0, 0, n - 1, l, r);
    }
};

// ── Outer 2D Segment Tree (rows ke upar tree of 1D trees) ───────────────────
class Seg2D_Sum_TreeOfTrees
{
private:
    vector<SegTree1D_Sum> rowTrees; // outer node i → poora column 1D tree
    vector<vector<int>> mat;
    int n, m;

    // ── build: outer row tree recursively banao ──
    //   1) leaf row (l==r) → us row ka 1D tree seedha mat[l] se banao
    //   2) internal row → pehle left/right row children build karo
    //   3) har column j ke liye merged[j] = left.query(j,j) + right.query(j,j)
    //   4) merged array se is outer node ka 1D column tree banao
    void build(int i, int l, int r)
    {
        if (l == r)
        {
            rowTrees[i] = SegTree1D_Sum(mat[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(2 * i + 1, l, mid);
        build(2 * i + 2, mid + 1, r);

        vector<int> merged(m);
        for (int j = 0; j < m; j++)
        {
            merged[j] = rowTrees[2 * i + 1].query(j, j) + rowTrees[2 * i + 2].query(j, j);
        }
        rowTrees[i] = SegTree1D_Sum(merged);
    }

    // ── update: cell (row,col) pe val set karo ──
    //   1) outer tree me row half choose karo (row <= mid → left)
    //   2) leaf row pe inner 1D tree me col update
    //   3) wapas aate waqt parent ke 1D tree me bhi col refresh:
    //      parent col = left child col + right child col
    void update(int i, int l, int r, int row, int col, int val)
    {
        if (l == r)
        {
            rowTrees[i].update(col, val);
            return;
        }
        int mid = (l + r) / 2;
        if (row <= mid)
        {
            update(2 * i + 1, l, mid, row, col, val);
        }
        else
        {
            update(2 * i + 2, mid + 1, r, row, col, val);
        }
        int newVal = rowTrees[2 * i + 1].query(col, col) + rowTrees[2 * i + 2].query(col, col);
        rowTrees[i].update(col, newVal);
    }

    // ── query: submatrix rows[r1..r2] × cols[c1..c2] ka sum ──
    //   Outer rows 3-case:
    //     NO overlap → 0
    //     FULL overlap → rowTrees[i].query(c1,c2)  (inner 1D column sum)
    //     PARTIAL → left + right row children
    int query(int i, int l, int r, int r1, int r2, int c1, int c2) const
    {
        if (r < r1 || l > r2)
        {
            return 0;
        }
        if (r1 <= l && r <= r2)
        {
            return rowTrees[i].query(c1, c2);
        }
        int mid = (l + r) / 2;
        return query(2 * i + 1, l, mid, r1, r2, c1, c2)
             + query(2 * i + 2, mid + 1, r, r1, r2, c1, c2);
    }

public:
    // ── constructor: matrix copy + outer tree build ──
    Seg2D_Sum_TreeOfTrees(vector<vector<int>> &matrix)
    {
        mat = matrix;
        n = (int)mat.size();
        m = (int)mat[0].size();
        rowTrees.resize(4 * max(n, 1));
        build(0, 0, n - 1);
    }

    // ── public: cell update + mat sync ──
    void update(int row, int col, int val)
    {
        mat[row][col] = val;
        update(0, 0, n - 1, row, col, val);
    }

    // ── public: submatrix sum ──
    int rectSum(int r1, int c1, int r2, int c2) const
    {
        return query(0, 0, n - 1, r1, r2, c1, c2);
    }
};

int main()
{
    vector<vector<int>> mat = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}};

    cout << "---- 2D SUM | Tree of Trees | Point Update + Submatrix Query ----\n";
    Seg2D_Sum_TreeOfTrees st(mat);

    cout << "Whole matrix sum: " << st.rectSum(0, 0, 3, 3) << endl;
    cout << "Submatrix [1,1]-[2,2]: " << st.rectSum(1, 1, 2, 2) << endl;

    st.update(1, 1, 100);
    cout << "After (1,1)=100: " << st.rectSum(1, 1, 2, 2) << endl;

    return 0;
}
