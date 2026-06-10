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

// ════════════════════════════════════════════════════════════════════════════
// LEETCODE 733 — Flood Fill
// ────────────────────────────────────────────────────────────────────────────
// Problem: Image me (sr, sc) se start karo, connected same-color pixels ko
//          naye color se replace karo (4-directional connectivity).
//
// Approach: DFS Flood Fill
//   - Starting pixel ka original color note karo
//   - Agar orig == new color to kuch mat karo (infinite loop avoid)
//   - DFS: valid cell + orig color ho to color change, 4 neighbors explore
//
// Complexity: Time O(m×n)  |  Space O(m×n) recursion stack worst case
// ════════════════════════════════════════════════════════════════════════════

// ── dfs: (i,j) se connected same-color region ko recolor karo ──
//   1) Bounds check + cell orig color hona chahiye, warna return
//   2) img[i][j] = color — current pixel paint karo
//   3) 4 directions me recursively dfs call — poora component fill
//   4) Already painted cells orig != honge — automatic stop
void dfs(vector<vector<int>> &img, int i, int j, int orig, int color) {
    int n = img.size(), m = img[0].size();
    if (i < 0 || j < 0 || i >= n || j >= m || img[i][j] != orig) return;  // invalid ya alag color
    img[i][j] = color;
    dfs(img, i + 1, j, orig, color);
    dfs(img, i - 1, j, orig, color);
    dfs(img, i, j + 1, orig, color);
    dfs(img, i, j - 1, orig, color);
}

// ── floodFill: starting pixel se poori connected region recolor ──
//   1) (sr,sc) ka original color nikalo
//   2) orig == color ho to image unchanged return (no-op)
//   3) dfs se connected component ko naye color se fill karo
//   4) Modified image return
vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color) {
    int orig = image[sr][sc];
    if (orig == color) return image;  // same color — infinite recursion avoid
    dfs(image, sr, sc, orig, color);
    return image;
}

int main() {
    vector<vector<int>> img = {{1,1,1},{1,1,0},{1,0,1}};
    auto ans = floodFill(img, 1, 1, 2);
    cout << ans[1][1] << " " << ans[0][0] << endl; // 2 2
    return 0;
}
