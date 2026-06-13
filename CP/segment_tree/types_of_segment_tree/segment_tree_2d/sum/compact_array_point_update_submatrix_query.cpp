#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * 2D SEGMENT TREE — SUM
 * APPROACH : Compact 2D array  st[vx][vy]
 * UPDATE   : Point (x, y) pe value set
 * QUERY    : Submatrix rectangle sum  [x1..x2] × [y1..y2]
 * LAZY     : NO
 * COMPLEX  : build O(n·m) | update O(log n · log m) | query O(log n · log m)
 * ════════════════════════════════════════════════════════════════════════════
 * Outer tree ROWS pe, inner tree COLUMNS pe.
 * st[vx][vy] = row-node vx ke andar column-node vy ka stored sum.
 *
 * Flow:
 *   buildX (rows) → har row-node pe buildY (columns)
 *   updateX → target row dhoondo → updateY column update
 *   queryX  → rows 3-case → full overlap pe queryY columns 3-case
 * ════════════════════════════════════════════════════════════════════════════
 */

class Seg2D_Sum_CompactArray
{
private:
    int n, m;                         // n = rows, m = cols
    vector<vector<ll>> st;            // st[row_node][col_node]

    // ── Common 2D params (har recursive function me same meaning) ───────────
    //   ROW dimension (outer / X tree):
    //     vx        -> row tree me current node index (root = 0)
    //     sx, ex    -> ye row-node rows [sx, ex] cover karta hai
    //     x         -> point update ke liye target row
    //     x1, x2    -> query rectangle ke row bounds
    //
    //   COL dimension (inner / Y tree):
    //     vy        -> column tree me current node index (root = 0)
    //     sy, ey    -> ye col-node columns [sy, ey] cover karta hai
    //     y         -> point update ke liye target column
    //     y1, y2    -> query rectangle ke column bounds
    //
    //   Har dimension pe 3-case overlap (NO / FULL / PARTIAL) — 1D jaisa hi logic.

    // ── buildY: ek fix row-node vx ke andar column-tree build karo ──────────
    //   Params: vx fix hai (outer row-node), vy/sy/ey column recursion
    //   1) sy == ey (column leaf):
    //        agar row bhi leaf (sx == ex) → exact cell mat[sx][sy] copy karo
    //        warna row internal → left+right row-child ka is column ka sum lo
    //   2) column internal → mid split, left/right column subtrees build karo
    //   3) parent: st[vx][vy] = left col child + right col child (SUM merge)
    void buildY(int vx, int sx, int ex, int vy, int sy, int ey,
                const vector<vector<int>> &mat)
    {
        if (sy == ey)
        {
            st[vx][vy] = (sx == ex)
                             ? mat[sx][sy]
                             : st[2 * vx + 1][vy] + st[2 * vx + 2][vy];
            return;
        }
        int my = (sy + ey) >> 1;
        buildY(vx, sx, ex, 2 * vy + 1, sy, my, mat);
        buildY(vx, sx, ex, 2 * vy + 2, my + 1, ey, mat);
        st[vx][vy] = st[vx][2 * vy + 1] + st[vx][2 * vy + 2];
    }

    // ── buildX: outer row dimension pe poora 2D tree build karo ──────────────
    //   1) agar sx != ex (row internal) → pehle left/right row children build karo
    //   2) har X-node (leaf ya internal) pe buildY se poora column tree banao
    //   3) is template me har row-node apna complete inner Y-tree rakhta hai
    void buildX(int vx, int sx, int ex, const vector<vector<int>> &mat)
    {
        if (sx != ex)
        {
            int mx = (sx + ex) >> 1;
            buildX(2 * vx + 1, sx, mx, mat);
            buildX(2 * vx + 2, mx + 1, ex, mat);
        }
        buildY(vx, sx, ex, 0, 0, m - 1, mat);
    }

    // ── queryY: ek row-node ke andar columns [y1,y2] ka sum ─────────────────
    //   1) Case 1 NO overlap (y2 < sy || ey < y1) → 0 return (sum identity)
    //   2) Case 2 FULL overlap (y1 <= sy && ey <= y2) → st[vx][vy] return
    //   3) Case 3 PARTIAL → left+right column query ka sum jodo
    ll queryY(int vx, int vy, int sy, int ey, int y1, int y2) const
    {
        if (y2 < sy || ey < y1)
        {
            return 0;
        }
        if (y1 <= sy && ey <= y2)
        {
            return st[vx][vy];
        }
        int my = (sy + ey) >> 1;
        return queryY(vx, 2 * vy + 1, sy, my, y1, y2)
             + queryY(vx, 2 * vy + 2, my + 1, ey, y1, y2);
    }

    // ── queryX: rectangle [x1..x2] × [y1..y2] ka total sum ─────────────────
    //   1) Case 1 NO row overlap → 0 return
    //   2) Case 2 FULL row overlap → poori row range cover, andar queryY se col sum
    //   3) Case 3 PARTIAL row overlap → left+right row subtrees ka sum jodo
    ll queryX(int vx, int sx, int ex, int x1, int x2, int y1, int y2) const
    {
        if (x2 < sx || ex < x1)
        {
            return 0;
        }
        if (x1 <= sx && ex <= x2)
        {
            return queryY(vx, 0, 0, m - 1, y1, y2);
        }
        int mx = (sx + ex) >> 1;
        return queryX(2 * vx + 1, sx, mx, x1, x2, y1, y2)
             + queryX(2 * vx + 2, mx + 1, ex, x1, x2, y1, y2);
    }

    // ── updateY: ek row-node ke andar column y pe val set karo ──────────────
    //   1) sy == ey (column leaf):
    //        row leaf → val set | row internal → row-bachho ka col sum refresh
    //   2) column internal → y <= mid se left/right child me jao
    //   3) wapas aate waqt parent column sum = left + right
    void updateY(int vx, int sx, int ex, int vy, int sy, int ey, int y, ll val)
    {
        if (sy == ey)
        {
            st[vx][vy] = (sx == ex) ? val : st[2 * vx + 1][vy] + st[2 * vx + 2][vy];
            return;
        }
        int my = (sy + ey) >> 1;
        if (y <= my)
        {
            updateY(vx, sx, ex, 2 * vy + 1, sy, my, y, val);
        }
        else
        {
            updateY(vx, sx, ex, 2 * vy + 2, my + 1, ey, y, val);
        }
        st[vx][vy] = st[vx][2 * vy + 1] + st[vx][2 * vy + 2];
    }

    // ── updateX: cell (x,y) pe val set karo ─────────────────────────────────
    //   1) row internal ho → x <= mid se left/right row child me jao
    //   2) har visited X-node pe updateY — us row range ke liye column tree update
    //   3) O(log n) row nodes × O(log m) column depth = O(log n · log m)
    void updateX(int vx, int sx, int ex, int x, int y, ll val)
    {
        if (sx != ex)
        {
            int mx = (sx + ex) >> 1;
            if (x <= mx)
            {
                updateX(2 * vx + 1, sx, mx, x, y, val);
            }
            else
            {
                updateX(2 * vx + 2, mx + 1, ex, x, y, val);
            }
        }
        updateY(vx, sx, ex, 0, 0, m - 1, y, val);
    }

public:
    // ── Seg2D_Sum_CompactArray: constructor ──
    //   1) n rows, m cols store karo
    //   2) st ko 4*n × 4*m allocate karo (dono dimensions safe padding)
    //   3) buildX(0, 0, n-1, mat) se root se poora 2D tree ready karo
    Seg2D_Sum_CompactArray(const vector<vector<int>> &mat)
    {
        n = (int)mat.size();
        m = (int)mat[0].size();
        st.assign(4 * max(n, 1), vector<ll>(4 * max(m, 1), 0));
        buildX(0, 0, n - 1, mat);
    }

    // ── update: public wrapper — cell (x,y) update ──
    //   user sirf coordinates + val deta hai; root vx=0 se updateX start
    void update(int x, int y, ll val)
    {
        updateX(0, 0, n - 1, x, y, val);
    }

    // ── rectSum: public wrapper — submatrix sum query ──
    //   (x1,y1) top-left, (x2,y2) bottom-right — inclusive bounds
    ll rectSum(int x1, int y1, int x2, int y2) const
    {
        return queryX(0, 0, n - 1, x1, x2, y1, y2);
    }
};

int main()
{
    vector<vector<int>> mat = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}};

    cout << "---- 2D SUM | Compact Array | Point Update + Submatrix Query ----\n";
    Seg2D_Sum_CompactArray st(mat);

    cout << "Whole matrix sum: " << st.rectSum(0, 0, 3, 3) << endl;       // 136
    cout << "Submatrix [1,1]-[2,2]: " << st.rectSum(1, 1, 2, 2) << endl; // 34

    st.update(1, 1, 100);
    cout << "After (1,1)=100, [1,1]-[2,2]: " << st.rectSum(1, 1, 2, 2) << endl;

    return 0;
}
