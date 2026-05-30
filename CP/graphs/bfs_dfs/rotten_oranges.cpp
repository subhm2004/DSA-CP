#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int bfs(vector<vector<int>>& grid, queue<pair<int, int>>& q,
            int& count_fresh) {
        int count = 0;
        vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int rows = grid.size();
        int cols = grid[0].size();

        while (!q.empty()) {
            ++count;
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                auto [x, y] = q.front();
                q.pop();

                for (auto [dx, dy] : dirs) {
                    int newX = x + dx, newY = y + dy;

                    if (newX < 0 || newY < 0 || newX >= rows || newY >= cols ||
                        grid[newX][newY] == 0 || grid[newX][newY] == 2) {
                        continue;
                    }

                    grid[newX][newY] = 2;
                    q.push({newX, newY});
                    count_fresh--;
                }
            }
        }

        return count_fresh == 0 ? count - 1 : -1;
    }

    int orangesRotting(vector<vector<int>>& grid) {
        if (grid.empty())
            return 0;

        int rows = grid.size();
        int cols = grid[0].size();
        queue<pair<int, int>> q;
        int count_fresh = 0;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == 2) {
                    q.push({i, j});
                } else if (grid[i][j] == 1) {
                    count_fresh++;
                }
            }
        }

        if (count_fresh == 0)
            return 0;

        return bfs(grid, q, count_fresh);
    }
};

int main() {
    // Hardcoded values for the grid
    vector<vector<int>> grid = {
        {2, 1, 1},
        {1, 1, 0},
        {0, 1, 1}
    };

    Solution sol;
    int result = sol.orangesRotting(grid);
    cout << "Minimum minutes to rot all oranges: " << result << endl;

    return 0;
}
