/*
 * ============================================================================
 * TOPIC    : Backtracking — Sudoku Solver
 * FILE     : sudoku_solver.cpp
 * PROBLEM  : Fill 9×9 sudoku board (empty = '.')
 * LEETCODE : 37 — Sudoku Solver
 * APPROACH : Backtrack empty cells; check row/col/box validity
 * COMPLEX  : Time: O(9^(empty cells))  |  Space: O(81)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
    bool valid(vector<vector<char>> &b, int r, int c, char ch) {
        for (int i = 0; i < 9; i++)
            if (b[r][i] == ch || b[i][c] == ch) return false;
        int br = (r / 3) * 3, bc = (c / 3) * 3;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (b[br + i][bc + j] == ch) return false;
        return true;
    }

    bool solve(vector<vector<char>> &b) {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++) {
                if (b[i][j] != '.') continue;
                for (char ch = '1'; ch <= '9'; ch++) {
                    if (!valid(b, i, j, ch)) continue;
                    b[i][j] = ch;
                    if (solve(b)) return true;
                    b[i][j] = '.';
                }
                return false;
            }
        return true;
    }

public:
    void solveSudoku(vector<vector<char>> &board) { solve(board); }
};

int main() {
    vector<vector<char>> board = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}};
    Solution().solveSudoku(board);
    cout << board[0][2] << board[0][4] << endl; // 47
    return 0;
}
