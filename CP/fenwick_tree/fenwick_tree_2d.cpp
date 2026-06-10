/*
 * ============================================================================
 * TOPIC    : Fenwick Tree — 2D
 * FILE     : fenwick_tree_2d.cpp
 * PROBLEM  : 2D grid — point update + submatrix sum query
 * APPROACH : 2D BIT — update/add at (x,y), query prefix sum
 * COMPLEX  : Update/Query O(log n * log m)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// 2D FENWICK TREE — Point Update + Submatrix Sum
// ────────────────────────────────────────────────────────────────────────────
// 1D jaisa hi, bas do dimensions me LSB jump:
//   update: x += (x&-x), y += (y&-y)
//   query:  x -= (x&-x), y -= (y&-y)
//
// Rectangle sum = inclusion-exclusion on 4 prefix sums
// Sab 1-indexed (x, y >= 1)
// ════════════════════════════════════════════════════════════════════════════

struct Fenwick2D {
    int n, m;
    vector<vector<long long>> bit;

    // ── Fenwick2D: 2D BIT constructor ──
    //   1) n rows, m cols — dono 1-indexed use honge
    //   2) (n+1) x (m+1) bit matrix, sab 0 se initialize
    Fenwick2D(int n, int m) : n(n), m(m), bit(n + 1, vector<long long>(m + 1, 0)) {}

    // ── add: cell (x, y) pe 'val' add karo ──
    //   1) outer loop i = x se n: i += i&-i (row direction parent nodes)
    //   2) inner loop j = y se m: j += j&-j (col direction parent nodes)
    //   3) har bit[i][j] += val — 2D BIT me ek point update multiple nodes affect karta hai
    void add(int x, int y, long long val) {
        for (int i = x; i <= n; i += i & -i)       // row LSB jump
            for (int j = y; j <= m; j += j & -j)   // col LSB jump
                bit[i][j] += val;
    }

    // ── sum: prefix sum — rectangle (1,1) se (x,y) tak ──
    //   1) res = 0, i = x aur j = y se shuru
    //   2) dono dimensions me LSB se niche/left aate jao
    //   3) har bit[i][j] ko res me add karo
    //   4) result = top-left (1,1) se (x,y) tak ka total sum
    long long sum(int x, int y) const {
        long long res = 0;
        for (int i = x; i > 0; i -= i & -i)
            for (int j = y; j > 0; j -= j & -j)
                res += bit[i][j];
        return res;
    }

    // ── rectSum: submatrix (x1,y1) se (x2,y2) ka sum ──
    //   1) 2D inclusion-exclusion: 4 prefix sums ka combination
    //   2) sum(x2,y2) = bada rectangle include karo
    //   3) sum(x1-1,y2) aur sum(x2,y1-1) = extra top/left strips minus
    //   4) sum(x1-1,y1-1) = double-subtract fix — corner wapas add
    long long rectSum(int x1, int y1, int x2, int y2) const {
        return sum(x2, y2) - sum(x1 - 1, y2) - sum(x2, y1 - 1) + sum(x1 - 1, y1 - 1);
    }

    // ── setValue: (x,y) pe val set (yahan sirf add — diff se replace bhi ho sakta) ──
    //   1) is demo me grid fresh build ho raha hai, isliye seedha add(x,y,val)
    //   2) agar pehle se value hai to old value nikaal ke (val-old) add karna padega
    void setValue(int x, int y, long long val) {
        add(x, y, val);
    }
};

// ── main: 2D grid BIT demo ──
//   1) 4x4 grid BIT me daalo, submatrix sum query karo
//   2) ek cell update karke dubara query — change verify karo
int main() {
    int n = 4, m = 4;
    Fenwick2D fw(n, m);

    vector<vector<int>> grid = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            fw.add(i, j, grid[i - 1][j - 1]);

    cout << "Submatrix sum (2,2) to (3,3) = " << fw.rectSum(2, 2, 3, 3) << endl;

    fw.add(2, 2, 5);
    cout << "After +5 at (2,2): " << fw.rectSum(2, 2, 3, 3) << endl;
    return 0;
}
