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

class Solution {
    vector<vector<string>> ans;
    vector<string> board;
    vector<bool> col, diag1, diag2;

    void solve(int row, int n) {
        if (row == n) {
            ans.push_back(board);
            return;
        }
        for (int c = 0; c < n; c++) {
            int d1 = row - c + n - 1, d2 = row + c;
            if (col[c] || diag1[d1] || diag2[d2]) continue;
            col[c] = diag1[d1] = diag2[d2] = true;
            board[row][c] = 'Q';
            solve(row + 1, n);
            board[row][c] = '.';
            col[c] = diag1[d1] = diag2[d2] = false;
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        board.assign(n, string(n, '.'));
        col.assign(n, false);
        diag1.assign(2 * n - 1, false);
        diag2.assign(2 * n - 1, false);
        solve(0, n);
        return ans;
    }
};

int main() {
    Solution s;
    cout << s.solveNQueens(4).size() << endl; // 2
    return 0;
}
