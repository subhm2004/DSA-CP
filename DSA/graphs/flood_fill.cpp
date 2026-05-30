/*
 * ============================================================================
 * TOPIC    : Graphs — Flood Fill
 * FILE     : flood_fill.cpp
 * PROBLEM  : Recolor connected component from starting pixel
 * LEETCODE : 733 — Flood Fill
 * APPROACH : DFS/BFS from (sr, sc); change same-color neighbors
 * COMPLEX  : Time: O(m*n)  |  Space: O(m*n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

void dfs(vector<vector<int>> &img, int i, int j, int orig, int color) {
    int n = img.size(), m = img[0].size();
    if (i < 0 || j < 0 || i >= n || j >= m || img[i][j] != orig) return;
    img[i][j] = color;
    dfs(img, i + 1, j, orig, color);
    dfs(img, i - 1, j, orig, color);
    dfs(img, i, j + 1, orig, color);
    dfs(img, i, j - 1, orig, color);
}

vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color) {
    int orig = image[sr][sc];
    if (orig == color) return image;
    dfs(image, sr, sc, orig, color);
    return image;
}

int main() {
    vector<vector<int>> img = {{1,1,1},{1,1,0},{1,0,1}};
    auto ans = floodFill(img, 1, 1, 2);
    cout << ans[1][1] << " " << ans[0][0] << endl; // 2 2
    return 0;
}
