#include <iostream>
#include <vector>
using namespace std;
typedef vector<vector<long long>> Matrix;

const int MOD = 1e9 + 7;

// Multiply two matrices
Matrix multiply_Matrices(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix ans(n, vector<long long>(n, 0));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k) {
                ans[i][j] = (ans[i][j] + A[i][k] * B[k][j]) % MOD;

                // Using __int128 to prevent overflow
                __int128 prod = (__int128)A[i][k] * B[k][j];
                ans[i][j] = (ans[i][j] + prod % MOD) % MOD;
            }

    return ans;
}


// Matrix exponentiation
Matrix matrix_Exponentiation(Matrix A, long long power) {
    int n = A.size();
    Matrix ans(n, vector<long long>(n, 0));

    for (int i = 0; i < n; ++i)
        ans[i][i] = 1;

    while (power > 0) {
        if (power % 2 == 1)
            ans = multiply_Matrices(ans, A);
        A = multiply_Matrices(A, A);
        power /= 2;
    }

    return ans;
}

// nth Fibonacci number
long long get_Fibonacci(long long n) {
    if (n == 0) return 0;
    Matrix base = {
        {1, 1},
        {1, 0}
    };
    Matrix result = matrix_Exponentiation(base, n - 1);
    return result[0][0];
}

// Print first n Fibonacci numbers
void print_first_n_fibonacci(long long n) {
    for (long long i = 0; i < n; ++i) {
        cout << "F(" << i << ") = " << get_Fibonacci(i) << '\n';
    }
}

int main() {
    long long n;
    cout << "Enter n: ";
    cin >> n;
    cout << "F(" << n << ") = " << get_Fibonacci(n) << '\n';
    // print_first_n_fibonacci(n+1);
    return 0;
}
