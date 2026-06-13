#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * OPERATION: GCD
 * APPROACH : Compact 2D array  st[vx][vy]
 * UPDATE   : Point (x, y) pe value set
 * QUERY    : Submatrix rectangle GCD  [x1..x2] × [y1..y2]
 * LAZY     : NO  (GCD pe range add lazy mathematically invalid — 1D jaisa)
 * COMPLEX  : build O(n·m·log V) | update O(log n · log m) | query O(log n · log m)
 * ════════════════════════════════════════════════════════════════════════════
 * ✅ VALID — point update + submatrix GCD query.
 * Merge = GCD(a,b), no-overlap identity = 0  (gcd(x,0) = x).
 *
 * ⚠️ 2D rectangle ADD lazy is file me NAHI — gcd/ lazy files 1D me bhi invalid the.
 * ════════════════════════════════════════════════════════════════════════════
 */

// ── computeGCD: Euclidean algorithm ──
//   1) b == 0 → return a
//   2) warna computeGCD(b, a % b)
int computeGCD(int a, int b)
{
    a = abs(a);
    b = abs(b);
    if (b == 0)
    {
        return a;
    }
    return computeGCD(b, a % b);
}

// ── mergeGcd: do values ka GCD, identity 0 handle ──
//   gcd(0, x) = x — isliye query me no-overlap 0 safe hai
int mergeGcd(int a, int b)
{
    if (a == 0)
    {
        return b;
    }
    if (b == 0)
    {
        return a;
    }
    return computeGCD(a, b);
}

class Seg2D_Gcd_CompactArray
{
private:
    int n, m;
    vector<vector<int>> st;

    // ── Common 2D params ──
    //   vx/sx/ex, vy/sy/ey, x/y, x1/x2/y1/y2 — sum file jaisa
    //   GCD tree: merge = mergeGcd(), no-overlap identity = 0

    // ── buildY: column-tree build (GCD merge) ──
    //   1) column leaf → cell value ya row-bachho ka GCD
    //   2) column internal → bachho build, parent = mergeGcd(left, right)
    void buildY(int vx, int sx, int ex, int vy, int sy, int ey,
                const vector<vector<int>> &mat)
    {
        if (sy == ey)
        {
            st[vx][vy] = (sx == ex)
                             ? mat[sx][sy]
                             : mergeGcd(st[2 * vx + 1][vy], st[2 * vx + 2][vy]);
            return;
        }
        int my = (sy + ey) >> 1;
        buildY(vx, sx, ex, 2 * vy + 1, sy, my, mat);
        buildY(vx, sx, ex, 2 * vy + 2, my + 1, ey, mat);
        st[vx][vy] = mergeGcd(st[vx][2 * vy + 1], st[vx][2 * vy + 2]);
    }

    // ── buildX: outer row tree build ──
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

    // ── queryY: columns [y1,y2] ka GCD ──
    //   1) NO overlap → 0 (identity)
    //   2) FULL → st[vx][vy]
    //   3) PARTIAL → mergeGcd(left, right)
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
        return mergeGcd(
            queryY(vx, 2 * vy + 1, sy, my, y1, y2),
            queryY(vx, 2 * vy + 2, my + 1, ey, y1, y2));
    }

    // ── queryX: rectangle ka GCD ──
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
        return mergeGcd(
            queryX(2 * vx + 1, sx, mx, x1, x2, y1, y2),
            queryX(2 * vx + 2, mx + 1, ex, x1, x2, y1, y2));
    }

    // ── updateY: column y pe val set ──
    void updateY(int vx, int sx, int ex, int vy, int sy, int ey, int y, int val)
    {
        if (sy == ey)
        {
            st[vx][vy] = (sx == ex) ? val : mergeGcd(st[2 * vx + 1][vy], st[2 * vx + 2][vy]);
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
        st[vx][vy] = mergeGcd(st[vx][2 * vy + 1], st[vx][2 * vy + 2]);
    }

    // ── updateX: cell (x,y) update ──
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
    // ── constructor ──
    Seg2D_Gcd_CompactArray(const vector<vector<int>> &mat)
    {
        n = (int)mat.size();
        m = (int)mat[0].size();
        st.assign(4 * max(n, 1), vector<int>(4 * max(m, 1), 0));
        buildX(0, 0, n - 1, mat);
    }

    // ── update: cell set ──
    void update(int x, int y, int val)
    {
        updateX(0, 0, n - 1, x, y, val);
    }

    // ── rectGcd: submatrix GCD ──
    int rectGcd(int x1, int y1, int x2, int y2) const
    {
        return queryX(0, 0, n - 1, x1, x2, y1, y2);
    }
};

int main()
{
    vector<vector<int>> mat = {
        {12, 18, 24, 30},
        {8, 16, 20, 28},
        {6, 9, 15, 21},
        {4, 8, 12, 36}};

    cout << "---- 2D GCD | Compact Array | Point Update + Submatrix Query ----\n";
    Seg2D_Gcd_CompactArray st(mat);

    cout << "Whole matrix GCD: " << st.rectGcd(0, 0, 3, 3) << endl;
    cout << "Submatrix [0,0]-[1,1]: " << st.rectGcd(0, 0, 1, 1) << endl; // gcd(12,18,8,16)=2

    st.update(0, 0, 100); // 100, 18, 8, 16 → gcd = 2
    cout << "After (0,0)=100, [0,0]-[1,1]: " << st.rectGcd(0, 0, 1, 1) << endl;

    return 0;
}
