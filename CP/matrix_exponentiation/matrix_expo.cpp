#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

// ════════════════════════════════════════════════════════════════════════════
// MATRIX EXPONENTIATION — A^power nikalna (Binary Exponentiation on Matrix)
// ────────────────────────────────────────────────────────────────────────────
// Normal number ki tarah matrix ka bhi power nikal sakte hain:
//   A^0 = Identity matrix
//   A^n = A * A * ... (n times)  — lekin O(n) slow hai
//
// Binary exponentiation (same idea as fast power):
//   power odd hai  -> result me ek A multiply karo
//   har step pe    -> A = A * A, power /= 2
//
// Har multiply me MOD lagaya hai taaki overflow na ho.
// ════════════════════════════════════════════════════════════════════════════

using Matrix = vector<vector<long long>>;

// ── multiply_Matrices: do square matrices A aur B ka product C = A * B ────
//   1) n x n result matrix zero se initialize
//   2) har (i,j) ke liye k=0..n-1: result[i][j] += A[i][k]*B[k][j]
//   3) har addition ke baad MOD le lo — overflow avoid
//   4) classic O(n^3) matrix multiplication return karo
Matrix multiply_Matrices(const Matrix &A, const Matrix &B)
{
    int n = A.size();
    Matrix result(n, vector<long long>(n, 0));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            for (int k = 0; k < n; ++k)
            {
                result[i][j] = (result[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return result;
}

// ── matrix_Exponentiation: matrix A ki power 'power' nikalo (A^power) ───────
//   1) result = identity matrix (diagonal pe 1) — A^0 = I
//   2) jab tak power > 0: agar odd -> result *= A
//   3) har step: A = A*A, power /= 2 (binary exponentiation)
//   4) O(log power) matrix multiplies — Fibonacci/recurrence ke liye fast
Matrix matrix_Exponentiation(Matrix A, long long power)
{
    int n = A.size();
    Matrix result(n, vector<long long>(n, 0));

    // identity matrix — A^0 = I
    for (int i = 0; i < n; ++i)
    {
        result[i][i] = 1;
    }

    // exponentiation by squaring (binary exponentiation)
    while (power > 0)
    {
        if (power % 2 == 1)          // odd bit set -> result me ek A multiply
        {
            result = multiply_Matrices(result, A);
        }
        A = multiply_Matrices(A, A); // A ko square karo
        power /= 2;
    }

    return result;
}

// ── printMatrix: matrix ko console pe print karo ───────────────────────────
//   1) har row iterate karo
//   2) har cell print, row ke baad newline
//   3) debug / output ke liye simple helper
void printMatrix(const Matrix &matrix)
{
    for (const auto &row : matrix)
    {
        for (long long val : row)
        {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main()
{
    Matrix A = {
        {1, 1, 1, 0},
        {1, 2, 3, 4},
        {4, 5, 6, 7},
        {7, 8, 9, 10}};

    long long power = 3;

    Matrix result = matrix_Exponentiation(A, power);

    printMatrix(result);

    return 0;
}
