/*
 * ============================================================================
 * TOPIC    : Backtracking — N-Queens II (count only)
 * FILE     : n_queens_ii.cpp
 * PROBLEM  : Count distinct solutions for n-queens
 * LEETCODE : 52 — N-Queens II
 * APPROACH : Same as N-Queens; count instead of store boards
 * COMPLEX  : Time: O(n!)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// N-QUEENS II — n×n board par queens place karke total solutions count karo
// ────────────────────────────────────────────────────────────────────────────
// Funda: har row me ek queen; col + dono diagonals track karke conflict avoid
// Board store nahi karte — sirf valid placements count karte hain
// COMPLEX: Time O(n!)  |  Space O(n)
// ════════════════════════════════════════════════════════════════════════════

class Solution {
    int ans = 0;
    vector<bool> col, diag1, diag2;

    // ── solve: row-by-row backtrack karke valid placements count ───────────
    //   1) base case: saari rows fill -> ans++ aur return
    //   2) current row ke har column c try karo
    //   3) col, diag1, diag2 check — attack ho to skip
    //   4) queen place karo (flags true), next row recurse
    //   5) backtrack: flags false karke agla column try
    void solve(int row, int n) {
        if (row == n) {
            ans++; // ek valid complete board mil gaya
            return;
        }
        for (int c = 0; c < n; c++) {
            int d1 = row - c + n - 1, d2 = row + c; // diagonal indices normalize
            if (col[c] || diag1[d1] || diag2[d2]) continue; // is column/diag pe queen hai
            col[c] = diag1[d1] = diag2[d2] = true; // queen place — attack zones mark
            solve(row + 1, n);
            col[c] = diag1[d1] = diag2[d2] = false; // backtrack — queen hatao
        }
    }

public:
    // ── totalNQueens: tracking arrays init karke solve chalao ──────────────
    //   1) col size n, diag arrays size 2n-1 set karo
    //   2) row 0 se backtracking start
    //   3) final count return
    int totalNQueens(int n) {
        col.assign(n, false);
        diag1.assign(2 * n - 1, false);
        diag2.assign(2 * n - 1, false);
        solve(0, n);
        return ans;
    }
};

// ── main: n=4 par solutions count print ──────────────────────────────────────
//   1) Solution object banao
//   2) totalNQueens(4) call — expected output 2
int main() {
    Solution s;
    cout << s.totalNQueens(4) << endl; // 2
    return 0;
}
