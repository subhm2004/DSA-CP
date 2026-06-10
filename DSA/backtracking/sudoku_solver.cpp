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

// ════════════════════════════════════════════════════════════════════════════
// SUDOKU SOLVER — 9×9 board me '.' cells ko valid digits se fill karo
// ────────────────────────────────────────────────────────────────────────────
// Funda: pehla empty cell dhundho, 1-9 try karo, valid ho to recurse
// Row, column aur 3×3 box teeno me duplicate nahi hona chahiye
// COMPLEX: Time O(9^empty)  |  Space O(81)
// ════════════════════════════════════════════════════════════════════════════

class Solution {
    // ── valid: cell (r,c) par ch place karna safe hai ya nahi ──────────────
    //   1) poori row aur column scan — same digit mile to false
    //   2) 3×3 box ka top-left (br, bc) nikalo
    //   3) box ke 9 cells check karo duplicate ke liye
    //   4) koi conflict nahi to true
    bool valid(vector<vector<char>> &b, int r, int c, char ch) {
        for (int i = 0; i < 9; i++)
            if (b[r][i] == ch || b[i][c] == ch) return false; // row/col clash
        int br = (r / 3) * 3, bc = (c / 3) * 3; // box ka starting corner
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (b[br + i][bc + j] == ch) return false; // 3×3 box me duplicate
        return true;
    }

    // ── solve: backtrack se poora board fill karo ──────────────────────────
    //   1) row-major order me pehla '.' cell dhundho
    //   2) '1' se '9' tak har digit try karo
    //   3) valid ho to place karo aur aage recurse
    //   4) solution mila to true; warna '.' restore karke backtrack
    //   5) koi digit fit nahi -> false (previous choice galat tha)
    bool solve(vector<vector<char>> &b) {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++) {
                if (b[i][j] != '.') continue; // filled cell — skip
                for (char ch = '1'; ch <= '9'; ch++) {
                    if (!valid(b, i, j, ch)) continue; // sudoku rule violate
                    b[i][j] = ch; // digit place karo
                    if (solve(b)) return true; // aage sab solve ho gaya
                    b[i][j] = '.'; // backtrack — ye digit kaam nahi aayi
                }
                return false; // is cell par koi valid digit nahi — upar wapas
            }
        return true; // koi empty cell nahi — board complete
    }

public:
    // ── solveSudoku: public wrapper — board in-place modify ────────────────
    //   1) solve() call — board reference se directly update
    void solveSudoku(vector<vector<char>> &board) { solve(board); }
};

// ── main: sample board solve karke verify ──────────────────────────────────
//   1) incomplete board define
//   2) solveSudoku call
//   3) solved cells print (expected 47 for pos [0][2] and [0][4])
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
