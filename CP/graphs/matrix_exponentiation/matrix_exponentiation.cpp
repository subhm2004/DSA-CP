#include <iostream>    // time complexity O(n^3 log (power))
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;  // Use a large prime for modulo operation if needed

// Function to multiply two 4x4 matrices
vector<vector<long long>> multiplyMatrices(const vector<vector<long long>>& A, const vector<vector<long long>>& B) {
    int n = A.size();  // Since we're working with 4x4 matrices
    vector<vector<long long>> result(n, vector<long long>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                result[i][j] = (result[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return result;
}

// Function to perform matrix exponentiation
vector<vector<long long>> matrixExponentiation(vector<vector<long long>>& A, long long power) {
    int n = A.size();  // Since we're working with 4x4 matrices
    vector<vector<long long>> result(n, vector<long long>(n, 0));

    // Initialize result as the identity matrix
    for (int i = 0; i < n; ++i) {
        result[i][i] = 1;
    }

    // Exponentiation by squaring
    while (power > 0) {
        if (power % 2 == 1) {
            result = multiplyMatrices(result, A);
        }
        A = multiplyMatrices(A, A);  // Square the matrix A
        power /= 2;
    }
    
    return result;
}

// Function to print a matrix
void printMatrix(const vector<vector<long long>>& matrix) {
    for (const auto& row : matrix) {
        for (long long val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    // Example 4x4 matrix A
    vector<vector<long long>> A = {
        {1, 1, 1, 0},
        {1, 2, 3, 4},
        {4, 5, 6, 7},
        {7, 8, 9, 10}
    };

    long long power = 3;  // Example exponent

    // Perform matrix exponentiation
    vector<vector<long long>> result = matrixExponentiation(A, power);

    // Print the resulting matrix
    printMatrix(result);

    return 0;
}
