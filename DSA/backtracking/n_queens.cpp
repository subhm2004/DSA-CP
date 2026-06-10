/*
 * ============================================================================
 * TOPIC    : Backtracking — N-Queens
 * FILE     : n_queens.cpp
 * PROBLEM  : Place n queens on n×n board so none attack
 * LEETCODE : 51 — N-Queens
 * APPROACH : Backtrack row by row; track cols and diagonals
 * COMPLEX  : Time: O(n!)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// N-QUEENS — n×n board par n queens place karo, koi attack na kare
// ────────────────────────────────────────────────────────────────────────────
// Funda: har row me exactly ek queen; col + diagonal arrays se O(1) check
// Valid board milne par string representation ans me save
// COMPLEX: Time O(n!)  |  Space O(n)
// ════════════════════════════════════════════════════════════════════════════

class Solution {
    vector<vector<string>> ans;
    vector<string> board;
    vector<bool> col, diag1, diag2;

    // ── solve: row-by-row queen place karke saari boards dhundho ───────────
    //   1) row == n -> poora board valid, ans me push
    //   2) har column c try karo current row me
    //   3) col/diag conflict ho to skip
    //   4) queen place ('Q'), flags true, next row recurse
    //   5) backtrack: '.' restore, flags false
    void solve(int row, int n) {
        if (row == n) {
            ans.push_back(board); // ek complete valid configuration
            return;
        }
        for (int c = 0; c < n; c++) {
            int d1 = row - c + n - 1, d2 = row + c; // diagonal index normalize
            if (col[c] || diag1[d1] || diag2[d2]) continue; // attack zone occupied
            col[c] = diag1[d1] = diag2[d2] = true;
            board[row][c] = 'Q'; // visual board me queen mark
            solve(row + 1, n);
            board[row][c] = '.'; // queen hatao
            col[c] = diag1[d1] = diag2[d2] = false; // attack zones free
        }
    }

public:
    // ── solveNQueens: board aur tracking arrays init, solve chalao ─────────
    //   1) n×n board '.' se fill
    //   2) col, diag1, diag2 arrays allocate
    //   3) row 0 se backtrack
    //   4) saari valid boards return
    vector<vector<string>> solveNQueens(int n) {
        board.assign(n, string(n, '.'));
        col.assign(n, false);
        diag1.assign(2 * n - 1, false);
        diag2.assign(2 * n - 1, false);
        solve(0, n);
        return ans;
    }
};

// ── main: n=4 par 2 solutions verify ───────────────────────────────────────
//   1) solveNQueens(4) call
//   2) solutions count print
int main() {
    Solution s;
    cout << s.solveNQueens(4).size() << endl; // 2
    return 0;
}
