/*
 * ============================================================================
 * TOPIC    : Binary Search
 * FILE     : search_2d_matrix.cpp
 * PROBLEM  : Search 2D Matrix
 * LEETCODE : 74 — Search a 2D Matrix
 * ABOUT    : Binary search templates and classic interview problems
 * APPROACH : Rotate/transpose matrix in-place or with extra space.
 * COMPLEX  : Time: O(n*m)  |  Space: O(1) or O(n*m)
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;



/*
 * searchMatrix()
 * Purpose : Rotate/transpose matrix in-place or with extra space.
 * Params  : const vector<vector<int>>& matrix, int target
 * Returns : pair<int, int>
 */
pair<int, int> searchMatrix(const vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) return {-1, -1};  // Return invalid index
    
    int rows = matrix.size();
    int cols = matrix[0].size();
    int left = 0;
    int right = rows * cols - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int midValue = matrix[mid / cols][mid % cols]; // Convert 1D index to 2D coordinates

        if (midValue == target) {
            return {mid / cols, mid % cols};  // Return the (row, col) of the target
        } else if (midValue < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return {-1, -1};  // Target not found
}



/*
 * main()
 * Purpose : Entry point — demo/test for Search 2D Matrix
 */
int main() {
    vector<vector<int>> matrix = {
        {1, 3, 5},
        {7, 9, 11},
        {13, 15, 17}
    };

    int target = 0;

    pair<int, int> result = searchMatrix(matrix, target);

    if (result.first != -1 && result.second != -1) {
        cout << "Target found at index: (" << result.first << ", " << result.second << ")" << endl;
    } else {
        cout << "Target not found in the matrix." << endl;
    }

    return 0;
}
