#include <iostream>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// FIBONACCI via MATRIX EXPONENTIATION — O(log n) Fibonacci
// ────────────────────────────────────────────────────────────────────────────
// Fibonacci recurrence: F(n) = F(n-1) + F(n-2)
// Isse matrix form me likho:
//
//   | F(n)   |   | 1  1 |   | F(n-1) |
//   | F(n-1) | = | 1  0 | × | F(n-2) |
//
// Base matrix M = [[1,1],[1,0]]
// M^(n-1) × [F(1), F(0)]^T = [F(n), F(n-1)]^T
// Toh F(n) = (M^(n-1))[0][0]  (top-left element)
//
// Matrix exponentiation se M^(n-1) in O(log n) — brute O(n) se bahut tez!
// Time: O(log n)  |  Space: O(1) extra (2×2 matrix)
// ════════════════════════════════════════════════════════════════════════════

typedef vector<vector<long long>> Matrix;

const int MOD = 1e9 + 7;

// ── multiply_Matrices: do matrices ka product (% MOD) ──────────────────────
// __int128 use karte hain intermediate multiply me overflow avoid karne ke liye.
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


// ── matrix_Exponentiation: matrix ki power nikalo (binary exponentiation) ──
// Identity se start, odd power pe result multiply, matrix square, power /= 2.
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

// ── get_Fibonacci: nth Fibonacci number return karo ────────────────────────
// Base cases: F(0)=0. Base matrix [[1,1],[1,0]] ki power (n-1) nikalo.
// Result ka [0][0] element = F(n).
long long get_Fibonacci(long long n) {
    // Step 1: base case F(0) = 0
    if (n == 0) return 0;
    // Step 2: base matrix [[1,1],[1,0]] ki power (n-1) nikalo
    Matrix base = {
        {1, 1},
        {1, 0}
    };
    Matrix result = matrix_Exponentiation(base, n - 1);
    // Step 3: result[0][0] = F(n) — matrix multiplication se derive hota hai
    return result[0][0];
}

// ── print_first_n_fibonacci: F(0) se F(n-1) tak sab print karo ────────────
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
