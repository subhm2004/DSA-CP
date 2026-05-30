/*
 * ============================================================================
 * TOPIC    : Trie + Backtracking — Word Search
 * FILE     : word_search.cpp
 * PROBLEM  : Find if word exists in character grid
 * LEETCODE : 79 — Word Search
 * APPROACH : DFS from each cell; mark visited with '#'
 * COMPLEX  : Time: O(m*n*4^L)  |  Space: O(L)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

bool dfs(vector<vector<char>> &board, string &word, int idx, int i, int j) {
    if (idx == (int)word.size()) return true;
    int n = board.size(), m = board[0].size();
    if (i < 0 || j < 0 || i >= n || j >= m || board[i][j] != word[idx]) return false;

    char save = board[i][j];
    board[i][j] = '#';
    int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
    bool found = false;
    for (int d = 0; d < 4; d++)
        if (dfs(board, word, idx + 1, i + dx[d], j + dy[d])) {
            found = true;
            break;
        }
    board[i][j] = save;
    return found;
}

bool exist(vector<vector<char>> &board, string word) {
    for (int i = 0; i < (int)board.size(); i++)
        for (int j = 0; j < (int)board[0].size(); j++)
            if (dfs(board, word, 0, i, j)) return true;
    return false;
}

int main() {
    vector<vector<char>> board = {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    cout << (exist(board, "ABCCED") ? "YES" : "NO") << endl;
    return 0;
}
