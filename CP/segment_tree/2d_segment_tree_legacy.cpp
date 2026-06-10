// 2D segment tree ka code
#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// 2D SEGMENT TREE (Sum) — "tree of trees" approach
// ────────────────────────────────────────────────────────────────────────────
// Idea: bahar wala (outer) tree ROWS pe bana hai. Outer tree ke har node ke
// andar ek poora 1D segment tree hota hai jo COLUMNS sambhaalta hai.
// Matlab outer node row-range [l, r] cover karta hai, aur uske andar ka 1D tree
// un saari rows ko column-wise sum karke rakhta hai.
//
// Recursion me jo params baar baar aate hain, ek baar samajh le:
//   i   -> tree array me current node ka index (root = 0)
//          left child  = 2*i + 1
//          right child = 2*i + 2
//   l   -> current node jis (row) segment ko cover karta hai uska LEFT  end
//   r   -> current node jis (row) segment ko cover karta hai uska RIGHT end
//          matlab ye outer node rows ke [l, r] hisse ka maalik hai
//   ql/qr (1D me)   -> query ka left/right column end
//   r1, r2          -> query me rows ka range  [r1, r2]
//   c1, c2          -> query me columns ka range [c1, c2]
//   mid             -> (l + r) / 2, segment ko do halves me todne ke liye
//
// Har recursion me wahi 3 case: NO overlap / FULL overlap / PARTIAL overlap.
// ════════════════════════════════════════════════════════════════════════════

// --------------------------------------------------------
// 1D Segment Tree (same as tera existing design, sum ke liye)
// Ye column dimension sambhaalta hai; outer 2D tree iske objects use karega.
// --------------------------------------------------------
class SegTree1D
{
private:
    vector<int> seg; // har node pe uske column-segment ka SUM (4*n size safe)
    int n;           // total columns

    // ── build: arr se 1D column-tree bottom-up banao ──
    //   1) Base case l==r → leaf hai, seg[i] = arr[l] set karo
    //   2) mid se segment ko left [l,m] aur right [m+1,r] me todo
    //   3) Dono bachho ko recursively build karo
    //   4) Parent ka sum = left child sum + right child sum
    void build(vector<int> &arr, int i, int l, int r)
    {
        if (l == r)
        {
            seg[i] = arr[l]; // leaf = us index ki value
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * i + 1, l, mid);     // left half
        build(arr, 2 * i + 2, mid + 1, r); // right half
        seg[i] = seg[2 * i + 1] + seg[2 * i + 2]; // sum = left + right
    }

    // ── update: column index idx pe value val set karo ──
    //   1) idx <= mid hai to left child me jao, warna right me
    //   2) Leaf (l==r) pe pahunch ke seg[i] = val assign karo
    //   3) Wapsi pe har ancestor ka sum = left + right refresh karo
    //   4) Sirf root se idx tak ka path change — O(log m) columns ke liye
    void update(int i, int l, int r, int idx, int val)
    {
        if (l == r)
        {
            seg[i] = val; // leaf mil gaya -> nayi value set
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid)
            update(2 * i + 1, l, mid, idx, val);     // idx left half me hai
        else
            update(2 * i + 2, mid + 1, r, idx, val); // idx right half me hai
        seg[i] = seg[2 * i + 1] + seg[2 * i + 2]; // parent ka sum refresh
    }

    // ── query: columns [ql,qr] ka sum nikalo ──
    //   1) Case 1 NO overlap (r<ql || l>qr) → 0 return
    //   2) Case 2 FULL overlap (ql<=l && r<=qr) → seedha seg[i] return
    //   3) Case 3 PARTIAL → dono bachho ka sum jod ke return
    int query(int i, int l, int r, int ql, int qr)
    {
        if (r < ql || l > qr) // Case 1: no overlap
            return 0;
        if (ql <= l && r <= qr) // Case 2: full overlap
            return seg[i];
        int mid = (l + r) / 2; // Case 3: partial -> dono taraf jao
        return query(2 * i + 1, l, mid, ql, qr) + query(2 * i + 2, mid + 1, r, ql, qr);
    }

public:
    // ── SegTree1D: default constructor — empty tree (outer 2D ke liye) ──
    //   1) Koi allocation nahi — sirf outer tree ke vector<SegTree1D> resize ke liye
    SegTree1D() {}

    // ── SegTree1D: arr se column tree banao ──
    //   1) n = arr.size(), seg vector 4*n size allocate
    //   2) Root i=0 se columns [0, n-1] par build() call karo
    SegTree1D(vector<int> &arr)
    {
        n = arr.size();
        seg.resize(4 * n);
        build(arr, 0, 0, n - 1);
    }

    // Public wrapper: column idx pe val set karo
    void update(int idx, int val)
    {
        update(0, 0, n - 1, idx, val);
    }

    // Public wrapper: columns [l,r] ka sum lao
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
    vector<SegTree1D> rowTrees; // outer tree ke har node ke liye ek poora 1D (column) tree
    vector<vector<int>> mat;    // original matrix (update ke time reference ke liye)
    int n, m;                   // n = rows, m = cols

    // ── build: outer tree — row dimension pe tree of trees banao ──
    //   1) Leaf (l==r) → sirf ek row, us row ka 1D SegTree1D seedha bana do
    //   2) Internal node → pehle dono row-halves recursively build karo
    //   3) Dono bachho se har column j ka value (query(j,j)) maang ke jodo
    //   4) Merged row se is outer node ka 1D column-tree banao
    void build(int i, int l, int r)
    {
        if (l == r)
        {
            rowTrees[i] = SegTree1D(mat[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(2 * i + 1, l, mid);     // upar wali rows
        build(2 * i + 2, mid + 1, r); // niche wali rows

        vector<int> merged(m);
        for (int j = 0; j < m; j++)
            merged[j] = rowTrees[2 * i + 1].query(j, j) + rowTrees[2 * i + 2].query(j, j);
        rowTrees[i] = SegTree1D(merged);
    }

    // ── update: cell (row,col) pe value val set karo ──
    //   1) Outer tree me row jis half me hai us child me recurse karo
    //   2) Leaf row pe pahunch ke us row ke 1D tree me col update karo
    //   3) Wapsi pe har parent ke 1D tree me bhi col refresh karo
    //   4) Parent col value = left child col + right child col (column-wise merge)
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

        int newVal = rowTrees[2 * i + 1].query(col, col) + rowTrees[2 * i + 2].query(col, col);
        rowTrees[i].update(col, newVal);
    }

    // ── query: submatrix rows[r1..r2] x cols[c1..c2] ka sum ──
    //   1) Outer tree pe rows ke 3 case: NO overlap → 0, FULL → inner 1D query
    //   2) FULL overlap (rows poori andar) → rowTrees[i].query(c1,c2) column sum
    //   3) PARTIAL → dono row-children ka sum jod ke return
    int query(int i, int l, int r, int r1, int r2, int c1, int c2)
    {
        if (r < r1 || l > r2) // rows ka no overlap
            return 0;
        if (r1 <= l && r <= r2)               // rows poori query ke andar
            return rowTrees[i].query(c1, c2); // ab andar wale 1D tree se cols ka sum

        int mid = (l + r) / 2; // partial -> rows ko todo
        return query(2 * i + 1, l, mid, r1, r2, c1, c2) + query(2 * i + 2, mid + 1, r, r1, r2, c1, c2);
    }

public:
    // ── SegTree2D: constructor — matrix se 2D segment tree banao ──
    //   1) mat copy karo, n=rows, m=cols store karo
    //   2) rowTrees vector 4*n size allocate (outer tree ke liye)
    //   3) Root i=0 se rows [0, n-1] par build() call karo
    SegTree2D(vector<vector<int>> &matrix)
    {
        mat = matrix;
        n = mat.size();
        m = mat[0].size();
        rowTrees.resize(4 * n);
        build(0, 0, n - 1);
    }

    // Public wrapper: cell update + mat sync rakho
    void update(int row, int col, int val)
    {
        mat[row][col] = val;
        update(0, 0, n - 1, row, col, val);
    }

    // Public wrapper: submatrix sum query
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