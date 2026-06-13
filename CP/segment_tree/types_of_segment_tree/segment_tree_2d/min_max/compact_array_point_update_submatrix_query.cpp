#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * OPERATION: MIN + MAX (dono ek saath)
 * APPROACH : Compact 2D arrays  stMin[vx][vy] + stMax[vx][vy]
 * UPDATE   : Point (x, y) pe value set — dono trees sync me update
 * QUERY    : Submatrix rectangle min/max  [x1..x2] × [y1..y2]
 * LAZY     : NO
 * COMPLEX  : build O(n·m) | update O(log n · log m) | query O(log n · log m)
 * ════════════════════════════════════════════════════════════════════════════
 * Outer tree ROWS pe, inner tree COLUMNS pe.
 * DO parallel 2D arrays:
 *   stMin[vx][vy] → row-node vx, col-node vy ka minimum
 *   stMax[vx][vy] → row-node vx, col-node vy ka maximum
 *
 * Column leaf + row internal: stMin = min(bachho), stMax = max(bachho).
 * Parent merges alag-alag min aur max trees ke liye.
 *
 * Flow:
 *   buildX (rows) → har row-node pe buildY (columns) — dono trees ek saath
 *   updateX → target row → updateY dono trees refresh
 *   queryX_Min / queryX_Max → rows 3-case → queryY_Min / queryY_Max
 * ════════════════════════════════════════════════════════════════════════════
 */

class Seg2D_MinMax_CompactArray
{
private:
    int n, m;                              // n = rows, m = cols
    vector<vector<int>> stMin;             // stMin[row_node][col_node]
    vector<vector<int>> stMax;             // stMax[row_node][col_node]
    static constexpr int MIN_ID = INT_MAX;
    static constexpr int MAX_ID = INT_MIN;

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
    //   DO trees sync me chalte hain — stMin (min) aur stMax (max).
    //   NO overlap: min → MIN_ID (INT_MAX) | max → MAX_ID (INT_MIN)

    // ── buildY: ek fix row-node vx ke andar column-tree build karo (dono trees) ─
    //   Params: vx fix hai (outer row-node), vy/sy/ey column recursion
    //   1) sy == ey (column leaf):
    //        row leaf (sx == ex) → stMin = stMax = mat[sx][sy] (ek cell pe min=max)
    //        row internal → stMin = min(row-bachho ka col min), stMax = max(row-bachho ka col max)
    //   2) column internal → mid split, left/right column subtrees build karo
    //   3) parent: stMin[vx][vy] = min(left, right) | stMax[vx][vy] = max(left, right)
    void buildY(int vx, int sx, int ex, int vy, int sy, int ey,
                const vector<vector<int>> &mat)
    {
        if (sy == ey)
        {
            if (sx == ex)
            {
                stMin[vx][vy] = stMax[vx][vy] = mat[sx][sy];
            }
            else
            {
                stMin[vx][vy] = min(stMin[2 * vx + 1][vy], stMin[2 * vx + 2][vy]);
                stMax[vx][vy] = max(stMax[2 * vx + 1][vy], stMax[2 * vx + 2][vy]);
            }
            return;
        }
        int my = (sy + ey) >> 1;
        buildY(vx, sx, ex, 2 * vy + 1, sy, my, mat);
        buildY(vx, sx, ex, 2 * vy + 2, my + 1, ey, mat);
        stMin[vx][vy] = min(stMin[vx][2 * vy + 1], stMin[vx][2 * vy + 2]);
        stMax[vx][vy] = max(stMax[vx][2 * vy + 1], stMax[vx][2 * vy + 2]);
    }

    // ── buildX: outer row dimension pe poora 2D tree build karo ──────────────
    //   1) agar sx != ex (row internal) → pehle left/right row children build karo
    //   2) har X-node (leaf ya internal) pe buildY se poora column tree banao
    //   3) dono stMin aur stMax har row-node pe complete inner Y-tree rakhte hain
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

    // ── queryY_Min: ek row-node ke andar columns [y1,y2] ka min ─────────────
    //   1) Case 1 NO overlap (y2 < sy || ey < y1) → MIN_ID (INT_MAX) return
    //   2) Case 2 FULL overlap (y1 <= sy && ey <= y2) → stMin[vx][vy] return
    //   3) Case 3 PARTIAL → left+right column query ka min lo
    int queryY_Min(int vx, int vy, int sy, int ey, int y1, int y2) const
    {
        if (y2 < sy || ey < y1)
        {
            return MIN_ID;
        }
        if (y1 <= sy && ey <= y2)
        {
            return stMin[vx][vy];
        }
        int my = (sy + ey) >> 1;
        return min(
            queryY_Min(vx, 2 * vy + 1, sy, my, y1, y2),
            queryY_Min(vx, 2 * vy + 2, my + 1, ey, y1, y2));
    }

    // ── queryY_Max: ek row-node ke andar columns [y1,y2] ka max ─────────────
    //   1) Case 1 NO overlap (y2 < sy || ey < y1) → MAX_ID (INT_MIN) return
    //   2) Case 2 FULL overlap (y1 <= sy && ey <= y2) → stMax[vx][vy] return
    //   3) Case 3 PARTIAL → left+right column query ka max lo
    int queryY_Max(int vx, int vy, int sy, int ey, int y1, int y2) const
    {
        if (y2 < sy || ey < y1)
        {
            return MAX_ID;
        }
        if (y1 <= sy && ey <= y2)
        {
            return stMax[vx][vy];
        }
        int my = (sy + ey) >> 1;
        return max(
            queryY_Max(vx, 2 * vy + 1, sy, my, y1, y2),
            queryY_Max(vx, 2 * vy + 2, my + 1, ey, y1, y2));
    }

    // ── queryX_Min: rectangle [x1..x2] × [y1..y2] ka total min ────────────
    //   1) Case 1 NO row overlap → MIN_ID (INT_MAX) return
    //   2) Case 2 FULL row overlap → poori row range cover, andar queryY_Min se col min
    //   3) Case 3 PARTIAL row overlap → left+right row subtrees ka min lo
    int queryX_Min(int vx, int sx, int ex, int x1, int x2, int y1, int y2) const
    {
        if (x2 < sx || ex < x1)
        {
            return MIN_ID;
        }
        if (x1 <= sx && ex <= x2)
        {
            return queryY_Min(vx, 0, 0, m - 1, y1, y2);
        }
        int mx = (sx + ex) >> 1;
        return min(
            queryX_Min(2 * vx + 1, sx, mx, x1, x2, y1, y2),
            queryX_Min(2 * vx + 2, mx + 1, ex, x1, x2, y1, y2));
    }

    // ── queryX_Max: rectangle [x1..x2] × [y1..y2] ka total max ────────────
    //   1) Case 1 NO row overlap → MAX_ID (INT_MIN) return
    //   2) Case 2 FULL row overlap → poori row range cover, andar queryY_Max se col max
    //   3) Case 3 PARTIAL row overlap → left+right row subtrees ka max lo
    int queryX_Max(int vx, int sx, int ex, int x1, int x2, int y1, int y2) const
    {
        if (x2 < sx || ex < x1)
        {
            return MAX_ID;
        }
        if (x1 <= sx && ex <= x2)
        {
            return queryY_Max(vx, 0, 0, m - 1, y1, y2);
        }
        int mx = (sx + ex) >> 1;
        return max(
            queryX_Max(2 * vx + 1, sx, mx, x1, x2, y1, y2),
            queryX_Max(2 * vx + 2, mx + 1, ex, x1, x2, y1, y2));
    }

    // ── updateY: ek row-node ke andar column y pe val set karo (dono trees) ─
    //   1) sy == ey (column leaf):
    //        row leaf → stMin = stMax = val | row internal → bachho se min/max refresh
    //   2) column internal → y <= mid se left/right child me jao
    //   3) wapas aate waqt parent: stMin = min(bachho), stMax = max(bachho)
    void updateY(int vx, int sx, int ex, int vy, int sy, int ey, int y, int val)
    {
        if (sy == ey)
        {
            if (sx == ex)
            {
                stMin[vx][vy] = stMax[vx][vy] = val;
            }
            else
            {
                stMin[vx][vy] = min(stMin[2 * vx + 1][vy], stMin[2 * vx + 2][vy]);
                stMax[vx][vy] = max(stMax[2 * vx + 1][vy], stMax[2 * vx + 2][vy]);
            }
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
        stMin[vx][vy] = min(stMin[vx][2 * vy + 1], stMin[vx][2 * vy + 2]);
        stMax[vx][vy] = max(stMax[vx][2 * vy + 1], stMax[vx][2 * vy + 2]);
    }

    // ── updateX: cell (x,y) pe val set karo ─────────────────────────────────
    //   1) row internal ho → x <= mid se left/right row child me jao
    //   2) har visited X-node pe updateY — dono trees sync me column tree update
    //   3) O(log n) row nodes × O(log m) column depth = O(log n · log m)
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
    // ── Seg2D_MinMax_CompactArray: constructor ──
    //   1) n rows, m cols store karo
    //   2) stMin ko MIN_ID, stMax ko MAX_ID se 4*n × 4*m allocate karo
    //   3) buildX(0, 0, n-1, mat) se root se dono 2D trees ready karo
    Seg2D_MinMax_CompactArray(const vector<vector<int>> &mat)
    {
        n = (int)mat.size();
        m = (int)mat[0].size();
        stMin.assign(4 * max(n, 1), vector<int>(4 * max(m, 1), MIN_ID));
        stMax.assign(4 * max(n, 1), vector<int>(4 * max(m, 1), MAX_ID));
        buildX(0, 0, n - 1, mat);
    }

    // ── update: public wrapper — cell (x,y) update ──
    //   user sirf coordinates + val deta hai; root vx=0 se dono trees updateX start
    void update(int x, int y, int val)
    {
        updateX(0, 0, n - 1, x, y, val);
    }

    // ── rectMin: public wrapper — submatrix min query ──
    //   (x1,y1) top-left, (x2,y2) bottom-right — inclusive bounds
    int rectMin(int x1, int y1, int x2, int y2) const
    {
        return queryX_Min(0, 0, n - 1, x1, x2, y1, y2);
    }

    // ── rectMax: public wrapper — submatrix max query ──
    //   (x1,y1) top-left, (x2,y2) bottom-right — inclusive bounds
    int rectMax(int x1, int y1, int x2, int y2) const
    {
        return queryX_Max(0, 0, n - 1, x1, x2, y1, y2);
    }
};

int main()
{
    vector<vector<int>> mat = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}};

    cout << "---- 2D MIN+MAX | Compact Array | Point Update + Submatrix Query ----\n";
    Seg2D_MinMax_CompactArray st(mat);

    cout << "Whole matrix min: " << st.rectMin(0, 0, 3, 3)
         << " | max: " << st.rectMax(0, 0, 3, 3) << endl; // 1 | 16
    cout << "Submatrix [1,1]-[2,2] min: " << st.rectMin(1, 1, 2, 2)
         << " | max: " << st.rectMax(1, 1, 2, 2) << endl; // 6 | 11

    st.update(1, 1, 100);
    cout << "After (1,1)=100, [1,1]-[2,2] min: " << st.rectMin(1, 1, 2, 2)
         << " | max: " << st.rectMax(1, 1, 2, 2) << endl;

    return 0;
}
