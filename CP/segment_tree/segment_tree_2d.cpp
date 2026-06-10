/*
 * ============================================================================
 * TOPIC    : Segment Tree — 2D (Segment tree of segment trees)
 * FILE     : segment_tree_2d.cpp
 * PROBLEM  : 2D grid point update + submatrix sum
 * APPROACH : Outer segtree on rows, inner segtree on columns
 * COMPLEX  : O(log n * log m)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// 2D SEGMENT TREE (Compact Array Version)
// ────────────────────────────────────────────────────────────────────────────
// Idea: bahar wala tree ROWS (x) pe, andar wala COLUMNS (y) pe.
// st[vx][vy] = ek node jahan vx = row-tree ka index, vy = column-tree ka index.
//
// Params:
//   vx, tx, txx -> row dimension: current node index aur uska row range [tx, txx]
//   vy, ty, tyy -> col dimension: current node index aur uska col range [ty, tyy]
//   xl,xr / yl,yr -> query rectangle ke row/col bounds
// ════════════════════════════════════════════════════════════════════════════

struct SegTree2D {
    int n, m;
    vector<vector<long long>> st; // st[row_node][col_node]

    // ── SegTree2D: constructor — matrix se 2D tree build karo ──
    //   1) n = rows, m = cols store karo
    //   2) st ko 4*n rows × 4*m cols se allocate karo (dono dimensions ke liye safe padding)
    //   3) buildX(1, 0, n-1, a) se outer row-tree root (vx=1) se build shuru
    SegTree2D(const vector<vector<int>> &a) {
        n = a.size();
        m = a[0].size();
        st.assign(4 * max(n, 1), vector<long long>(4 * max(m, 1), 0));
        buildX(1, 0, n - 1, a);
    }

    // ── buildY: ek fix row-node ke andar column-tree build karo ──
    //   1) ty==tyy pe column leaf — st[vx][vy] = a[x][ty] (exact cell value)
    //   2) warna mid split karke left/right column subtrees build karo
    //   3) parent column node = left child sum + right child sum
    //   4) ye function ek fix row 'x' ke liye poora column dimension cover karta hai
    void buildY(int vx, int vy, int ty, int tyy, const vector<vector<int>> &a, int x) {
        if (ty == tyy) {  // column leaf — ek hi column index
            st[vx][vy] = a[x][ty];
            return;
        }
        int tmy = (ty + tyy) / 2;
        buildY(vx, vy * 2, ty, tmy, a, x);           // left column half
        buildY(vx, vy * 2 + 1, tmy + 1, tyy, a, x);  // right column half
        st[vx][vy] = st[vx][vy * 2] + st[vx][vy * 2 + 1];  // parent = bachho ka sum
    }

    // ── buildX: outer row dimension pe tree build karo ──
    //   1) tx==txx pe row leaf — us single row ke liye buildY se column-tree banao
    //   2) row internal ho to pehle left/right row subtrees recursively build karo
    //   3) har column index vy pe parent = left row child + right row child merge
    //   4) isse st[vx][vy] har row-node pe poora column sum store karta hai
    void buildX(int vx, int tx, int txx, const vector<vector<int>> &a) {
        if (tx == txx) {  // row leaf — ek hi row, ab column tree build karo
            buildY(vx, 1, 0, m - 1, a, tx);
            return;
        }
        int tmx = (tx + txx) / 2;
        buildX(vx * 2, tx, tmx, a);           // left row half
        buildX(vx * 2 + 1, tmx + 1, txx, a);  // right row half
        for (int vy = 1; vy < 4 * m; vy++)    // har column node pe row-bachho merge
            st[vx][vy] = st[vx * 2][vy] + st[vx * 2 + 1][vy];
    }

    // ── updateY: ek row-node ke andar column y pe val set karo ──
    //   1) ty==tyy pe column leaf — st[vx][vy] = val overwrite karo
    //   2) y <= mid ho to left column child, warna right column child me jao
    //   3) wapas aate waqt parent column sum = left + right refresh karo
    //   4) ye sirf ek fix row-node vx ke andar column dimension update karta hai
    void updateY(int vx, int vy, int ty, int tyy, int y, long long val) {
        if (ty == tyy) {  // column leaf — target column mil gaya
            st[vx][vy] = val;
            return;
        }
        int tmy = (ty + tyy) / 2;
        if (y <= tmy) updateY(vx, vy * 2, ty, tmy, y, val);
        else updateY(vx, vy * 2 + 1, tmy + 1, tyy, y, val);
        st[vx][vy] = st[vx][vy * 2] + st[vx][vy * 2 + 1];
    }

    // ── updateX: cell (x,y) pe val set karo ──
    //   1) tx==txx pe row leaf — target row mil gayi, andar updateY call karo
    //   2) row internal ho to x <= mid se left/right row child choose karo
    //   3) row child update ke baad har vy pe parent row merge refresh karo
    //   4) complexity O(log n * log m) — dono dimensions me ek-ek raasta
    void updateX(int vx, int tx, int txx, int x, int y, long long val) {
        if (tx == txx) {  // row leaf — ab column tree me y update karo
            updateY(vx, 1, 0, m - 1, y, val);
            return;
        }
        int tmx = (tx + txx) / 2;
        if (x <= tmx) updateX(vx * 2, tx, tmx, x, y, val);
        else updateX(vx * 2 + 1, tmx + 1, txx, x, y, val);
        for (int vy = 1; vy < 4 * m; vy++)  // row merge — har column index refresh
            st[vx][vy] = st[vx * 2][vy] + st[vx * 2 + 1][vy];
    }

    // ── queryY: ek row-node ke andar columns [yl,yr] ka sum ──
    //   1) Case 1 NO overlap (yl>tyy || yr<ty) — 0 return
    //   2) Case 2 FULL overlap (yl<=ty && tyy<=yr) — seedha st[vx][vy] return
    //   3) Case 3 PARTIAL — mid split, left+right column query ka sum jodo
    //   4) ye inner column-tree query hai — outer row already fix hai
    long long queryY(int vx, int vy, int ty, int tyy, int yl, int yr) const {
        if (yl > tyy || yr < ty) return 0;                    // Case 1: NO overlap
        if (yl <= ty && tyy <= yr) return st[vx][vy];          // Case 2: FULL overlap
        int tmy = (ty + tyy) / 2;                             // Case 3: PARTIAL overlap
        return queryY(vx, vy * 2, ty, tmy, yl, yr) + queryY(vx, vy * 2 + 1, tmy + 1, tyy, yl, yr);
    }

    // ── queryX: rectangle [xl..xr] × [yl..yr] ka sum ──
    //   1) Case 1 NO row overlap — 0 return
    //   2) Case 2 FULL row overlap — poori row range cover, andar queryY se column sum
    //   3) Case 3 PARTIAL row overlap — left+right row subtrees ka sum jodo
    //   4) outer 3-case rows pe, inner 3-case columns pe — nested segment tree
    long long queryX(int vx, int tx, int txx, int xl, int xr, int yl, int yr) const {
        if (xl > txx || xr < tx) return 0;                              // Case 1: NO row overlap
        if (xl <= tx && txx <= xr) return queryY(vx, 1, 0, m - 1, yl, yr);  // Case 2: FULL row overlap
        int tmx = (tx + txx) / 2;                                       // Case 3: PARTIAL row overlap
        return queryX(vx * 2, tx, tmx, xl, xr, yl, yr) + queryX(vx * 2 + 1, tmx + 1, txx, xl, xr, yl, yr);
    }

    // ── update: public wrapper — cell (x,y) update ──
    //   1) user sirf coordinates aur val deta hai
    //   2) updateX root row-node (vx=1) se start — poora 2D update handle hota hai
    void update(int x, int y, long long val) { updateX(1, 0, n - 1, x, y, val); }

    // ── rectSum: public wrapper — submatrix sum ──
    //   1) (x1,y1) se (x2,y2) rectangle ki bounds lo
    //   2) queryX root se call — O(log n * log m) me answer return
    long long rectSum(int x1, int y1, int x2, int y2) {
        return queryX(1, 0, n - 1, x1, x2, y1, y2);
    }
};

int main() {
    vector<vector<int>> a = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    SegTree2D st(a);
    cout << "Sum (0,0)-(1,1) = " << st.rectSum(0, 0, 1, 1) << endl;
    st.update(1, 1, 100);
    cout << "After update: " << st.rectSum(0, 0, 2, 2) << endl;
    return 0;
}
