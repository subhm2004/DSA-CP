#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

// Matrix alias for cleaner code
using Matrix = vector<vector<long long>>;

// Function to multiply two square matrices
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

// Function to perform matrix exponentiation
Matrix matrix_Exponentiation(Matrix A, long long power)
{
    int n = A.size();
    Matrix result(n, vector<long long>(n, 0));

    // Identity matrix
    for (int i = 0; i < n; ++i)
    {
        result[i][i] = 1;
    }

    // Exponentiation by squaring
    while (power > 0)
    {
        if (power % 2 == 1)
        {
            result = multiply_Matrices(result, A);
        }
        A = multiply_Matrices(A, A);
        power /= 2;
    }

    return result;
}

// Function to print a matrix
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
