/*
 * ============================================================================
 * TOPIC    : Combinatorics — Stirling Numbers
 * FILE     : stirling_numbers.cpp
 * PROBLEM  : Stirling numbers of 1st and 2nd kind
 * APPROACH : Recurrence relations + DP tables
 * COMPLEX  : Time: O(n^2)  |  Space: O(n^2)
 * ============================================================================
 *
 * 2nd kind S(n,k): ways to partition n elements into k non-empty subsets
 *   S(n,k) = k*S(n-1,k) + S(n-1,k-1)
 *
 * 1st kind s(n,k): permutations of n with k cycles
 *   s(n,k) = s(n-1,k-1) + (n-1)*s(n-1,k)
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// STIRLING NUMBERS — 1st kind (cycles) aur 2nd kind (partitions)
// ────────────────────────────────────────────────────────────────────────────
// S2(n,k): n elements ko exactly k non-empty subsets me baantne ke tareeke
//   n-th element: ya existing k subsets me jao (k choices) ya naya subset banao
// s1(n,k): n elements ki permutations me exactly k cycles
// COMPLEX: O(n²) DP table
// ════════════════════════════════════════════════════════════════════════════

const long long MOD = 1e9 + 7;

// ── stirlingTables: dono tables ek saath banao ──
//   S2[i][j] = j * S2[i-1][j] + S2[i-1][j-1]
//     → element i k existing groups me + naya group start
//   S1[i][j] = S1[i-1][j-1] + (i-1) * S1[i-1][j]
//     → naya cycle start OR kisi existing (i-1) cycle me attach
pair<vector<vector<long long>>, vector<vector<long long>>> stirlingTables(int n)
{
    vector<vector<long long>> S2(n + 1, vector<long long>(n + 1, 0));
    vector<vector<long long>> S1(n + 1, vector<long long>(n + 1, 0));

    S2[0][0] = 1; // 0 elements, 0 subsets — ek tareeka (empty)
    S1[0][0] = 1;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            S2[i][j] = (j * S2[i - 1][j] + S2[i - 1][j - 1]) % MOD;
            S1[i][j] = (S1[i - 1][j - 1] + (long long)(i - 1) * S1[i - 1][j]) % MOD;
        }
    }
    return {S1, S2};
}

int main()
{
    int n = 6;
    auto [s1, s2] = stirlingTables(n);

    int k = 3;
    cout << "Stirling 2nd kind S(" << n << "," << k << ") = " << s2[n][k] << endl;
    cout << "Stirling 1st kind s(" << n << "," << k << ") = " << s1[n][k] << endl;

    cout << "\nS2 table (partition into k subsets):\n";
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= i; j++)
            cout << s2[i][j] << " ";
        cout << endl;
    }
    return 0;
}
