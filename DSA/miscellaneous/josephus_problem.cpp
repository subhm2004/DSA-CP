/*
 * ============================================================================
 * TOPIC    : Josephus Problem
 * FILE     : josephus_problem.cpp
 * PROBLEM  : n people in circle, every k-th eliminated — who survives?
 * REF      : https://cp-algorithms.com/others/josephus_problem.html
 * APPROACH : DP recurrence J(n,k) = (J(n-1,k) + k) mod n  (0-indexed)
 * COMPLEX  : O(n) iterative | O(k log n) when k << n | O(1) for k=2
 * ============================================================================
 *
 * STATEMENT
 * ---------
 * Numbers 1..n in a circle. Count k, remove that person, repeat from next.
 * Find the last survivor (1-indexed answer).
 *
 * RECURRENCE (0-indexed positions)
 * --------------------------------
 *   J(1, k) = 0
 *   J(n, k) = (J(n-1, k) + k) mod n
 *
 * 1-indexed: answer = J(n,k) + 1
 *
 * See josephus_problem.md for O(k log n), k=2 closed form, complexity proofs.
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ── O(n) — iterative (CP-Algo default, works for all n, k) ───────────────────
// Returns 1-indexed survivor
int josephusOn(int n, int k) {
    int res = 0; // J(0,*) unused; building up from J(1,k)=0 in 0-index
    for (int i = 1; i <= n; i++)
        res = (res + k) % i;
    return res + 1;
}

// ── O(n) — recursive (1-indexed CP-Algo snippet) ─────────────────────────────
int josephusRecursive(int n, int k) {
    return n > 1 ? (josephusRecursive(n - 1, k) + k - 1) % n + 1 : 1;
}

// ── O(k log n) — skip batches when k << n (0-indexed internally) ─────────────
int josephusFast(int n, int k) {
    if (n == 1) return 0;
    if (k == 1) return n - 1;
    if (k > n) return (josephusFast(n - 1, k) + k) % n;

    int removed = n / k;
    int res = josephusFast(n - removed, k);
    res -= n % k;
    if (res < 0)
        res += n;
    else
        res += res / (k - 1);
    return res;
}

int josephusFast1Indexed(int n, int k) {
    return josephusFast(n, k) + 1;
}

// ── O(1) — closed form for k = 2 (Flavius Josephus original) ───────────────
// J(n,2) = 1 + 2 * (n - 2^floor(log2 n))
int josephusK2(int n) {
    if (n == 1) return 1;
    int highestPower = 1 << (31 - __builtin_clz(n)); // largest 2^p <= n
    return 1 + 2 * (n - highestPower);
}

// ── Brute simulation — O(n²), for verifying small n only ─────────────────────
int josephusSimulate(int n, int k) {
    vector<int> circle(n);
    iota(circle.begin(), circle.end(), 1);
    int idx = 0;
    while (circle.size() > 1) {
        idx = (idx + k - 1) % (int)circle.size();
        circle.erase(circle.begin() + idx);
    }
    return circle[0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Josephus Problem ===\n\n";

    struct Test {
        int n, k, expected;
    };
    vector<Test> tests = {
        {7, 3, 4},   // CP-Algo table: J(7,3)=4
        {41, 3, 31}, // classic example
        {10, 2, 5},  // k=2
        {8, 2, 1},   // k=2, power of 2 → survivor 1
        {5, 1, 5},   // k=1 → last person n
    };

    cout << left << setw(6) << "n" << setw(6) << "k"
         << setw(12) << "O(n)" << setw(12) << "O(k logn)"
         << setw(12) << "simulate" << "k=2 formula\n";
    cout << string(58, '-') << '\n';

    for (auto [n, k, exp] : tests) {
        int a = josephusOn(n, k);
        int b = josephusFast1Indexed(n, k);
        int c = josephusSimulate(n, k);
        cout << setw(6) << n << setw(6) << k
             << setw(12) << a << setw(12) << b
             << setw(12) << c;
        if (k == 2)
            cout << setw(12) << josephusK2(n);
        cout << (a == exp && b == exp && c == exp ? "  OK" : "  MISMATCH")
             << '\n';
    }

    cout << "\nRecursion check J(7,3) = " << josephusRecursive(7, 3) << " (expected 4)\n";

    return 0;
}
