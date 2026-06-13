#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * OPERATION: XOR
 * APPROACH : Compact 2D array  st[vx][vy]
 * UPDATE   : Point (x, y) pe value set
 * QUERY    : Submatrix rectangle XOR  [x1..x2] × [y1..y2]
 * LAZY     : NO  (2D rectangle XOR lazy alag advanced topic)
 * COMPLEX  : build O(n·m) | update O(log n · log m) | query O(log n · log m)
 * ════════════════════════════════════════════════════════════════════════════
 * 1D xor/ folder ka 2D version.
 * Merge = XOR (^), no-overlap identity = 0  (x ^ 0 = x).
 *
 * Outer tree ROWS pe, inner tree COLUMNS pe — sum/max jaisa skeleton.
 * ════════════════════════════════════════════════════════════════════════════
 */

class Seg2D_Xor_CompactArray
{
private:
    int n, m;
    vector<vector<int>> st;

    // ── Common 2D params (har recursive function me same meaning) ───────────
    //   vx, sx, ex  -> row tree node + row range
    //   vy, sy, ey  -> col tree node + col range
    //   x, y        -> point update cell
    //   x1,x2,y1,y2 -> query rectangle (inclusive)
    //
    //   XOR tree: merge = ^ , no-overlap identity = 0
    //   Har dimension pe 3-case: NO overlap / FULL overlap / PARTIAL

    // ── buildY: ek fix row-node vx ke andar column-tree build karo ──────────
    //   1) column leaf (sy==ey):
    //        row leaf → mat[sx][sy] | row internal → left ^ right row-child
    //   2) column internal → mid split, bachho build
    //   3) parent merge: st[vx][vy] = left col child ^ right col child
    void buildY(int vx, int sx, int ex, int vy, int sy, int ey,
                const vector<vector<int>> &mat)
    {
        if (sy == ey)
        {
            st[vx][vy] = (sx == ex)
                             ? mat[sx][sy]
                             : st[2 * vx + 1][vy] ^ st[2 * vx + 2][vy];
            return;
        }
        int my = (sy + ey) >> 1;
        buildY(vx, sx, ex, 2 * vy + 1, sy, my, mat);
        buildY(vx, sx, ex, 2 * vy + 2, my + 1, ey, mat);
        st[vx][vy] = st[vx][2 * vy + 1] ^ st[vx][2 * vy + 2];
    }

    // ── buildX: outer row dimension pe poora 2D tree build karo ──────────────
    //   1) row internal → left/right row children pehle build
    //   2) har X-node pe buildY se poora column tree banao
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

    // ── queryY: ek row-node ke andar columns [y1,y2] ka XOR ─────────────────
    //   1) NO overlap → 0 return (XOR identity)
    //   2) FULL overlap → st[vx][vy] return
    //   3) PARTIAL → left ^ right column query
    int queryY(int vx, int vy, int sy, int ey, int y1, int y2) const
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
             ^ queryY(vx, 2 * vy + 2, my + 1, ey, y1, y2);
    }

    // ── queryX: rectangle [x1..x2] × [y1..y2] ka total XOR ─────────────────
    //   1) NO row overlap → 0
    //   2) FULL row overlap → queryY se column XOR
    //   3) PARTIAL → left ^ right row subtrees
    int queryX(int vx, int sx, int ex, int x1, int x2, int y1, int y2) const
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
             ^ queryX(2 * vx + 2, mx + 1, ex, x1, x2, y1, y2);
    }

    // ── updateY: ek row-node ke andar column y pe val set karo ──────────────
    //   1) column leaf → val set ya row-bachho ka XOR refresh
    //   2) column internal → left/right child recurse
    //   3) parent: left ^ right
    void updateY(int vx, int sx, int ex, int vy, int sy, int ey, int y, int val)
    {
        if (sy == ey)
        {
            st[vx][vy] = (sx == ex) ? val : st[2 * vx + 1][vy] ^ st[2 * vx + 2][vy];
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
        st[vx][vy] = st[vx][2 * vy + 1] ^ st[vx][2 * vy + 2];
    }

    // ── updateX: cell (x,y) pe val set karo ─────────────────────────────────
    //   1) row internal → sahi row child me jao
    //   2) har visited X-node pe updateY call
    void updateX(int vx, int sx, int ex, int x, int y, int val)
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
    // ── constructor: matrix se 2D XOR tree build ──
    Seg2D_Xor_CompactArray(const vector<vector<int>> &mat)
    {
        n = (int)mat.size();
        m = (int)mat[0].size();
        st.assign(4 * max(n, 1), vector<int>(4 * max(m, 1), 0));
        buildX(0, 0, n - 1, mat);
    }

    // ── update: cell (x,y) pe value set ──
    void update(int x, int y, int val)
    {
        updateX(0, 0, n - 1, x, y, val);
    }

    // ── rectXor: submatrix rectangle ka XOR ──
    int rectXor(int x1, int y1, int x2, int y2) const
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

    cout << "---- 2D XOR | Compact Array | Point Update + Submatrix Query ----\n";
    Seg2D_Xor_CompactArray st(mat);

    cout << "Whole matrix XOR: " << st.rectXor(0, 0, 3, 3) << endl;
    cout << "Submatrix [1,1]-[2,2]: " << st.rectXor(1, 1, 2, 2) << endl; // 6^7^10^11

    st.update(1, 1, 100);
    cout << "After (1,1)=100, [1,1]-[2,2]: " << st.rectXor(1, 1, 2, 2) << endl;

    return 0;
}
