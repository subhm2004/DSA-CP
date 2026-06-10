#include <iostream>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// MATRIX EXPONENTIATION — Binary Exponentiation for Matrices
// ────────────────────────────────────────────────────────────────────────────
// A^power nikalne ka efficient tareeka — brute force O(n³ * power) ki jagah
// O(n³ * log(power)) using binary exponentiation (exponentiation by squaring).
//
// Idea (same as fast power for numbers):
//   result = Identity matrix (I)
//   jab power odd ho -> result = result * A
//   A = A * A (square), power /= 2
//
// Matrix multiply: standard O(n³) — har cell (i,j) = sum of A[i][k]*B[k][j]
// MOD use karte hain taaki overflow na ho.
// Time: O(n³ log power)  |  Space: O(n²)
// ════════════════════════════════════════════════════════════════════════════

const int MOD = 1e9 + 7;  // Modulo — overflow prevent karne ke liye

// ── multiplyMatrices: do n×n matrices ka product return karo ─────────────
// Classic triple loop — result[i][j] += A[i][k] * B[k][j], har step pe % MOD.
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

// ── matrixExponentiation: A^power nikalo (binary exponentiation) ───────────
// result = Identity matrix se start.
// power odd hai to result *= A, phir A = A*A, power /= 2 — repeat.
vector<vector<long long>> matrixExponentiation(vector<vector<long long>>& A, long long power) {
    int n = A.size();
    vector<vector<long long>> result(n, vector<long long>(n, 0));

    // Step 1: result = Identity matrix (A^0 = I)
    for (int i = 0; i < n; ++i) {
        result[i][i] = 1;
    }

    // Step 2: binary exponentiation — number wale fast power jaisa
    while (power > 0) {
        if (power % 2 == 1) {
            result = multiplyMatrices(result, A); // odd bit — result me A multiply
        }
        A = multiplyMatrices(A, A);  // A square karo
        power /= 2;
    }
    
    return result;
}

// ── printMatrix: matrix ko readable format me print karo ───────────────────
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

    // A^power compute karo aur print karo
    vector<vector<long long>> result = matrixExponentiation(A, power);

    printMatrix(result);

    return 0;
}
