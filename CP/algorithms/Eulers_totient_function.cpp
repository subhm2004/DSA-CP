#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// EULER'S TOTIENT FUNCTION φ(n)
// ────────────────────────────────────────────────────────────────────────────
// φ(n) = 1 se n tak kitne integers hain jo n ke saath coprime hain (gcd=1)
// Formula: φ(n) = n * Π(1 - 1/p) for each distinct prime p dividing n
//
// Do methods:
//   1) phi(n)     — single number, O(√n) factorization
//   2) phi_1_to_n — sieve style, O(n log log n) for all 1..n
// ════════════════════════════════════════════════════════════════════════════

// ── phi: single number ke liye φ(n) ─────────────────────────────────────────
//   1) result = n, har prime p | n ke liye result -= result/p
//   2) n ko p se completely divide karo
//   3) bacha hua prime factor handle karo
int phi(int n)
{
    int result = n;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

// ── phi_1_to_n: φ(1) se φ(n) tak sieve se compute ─────────────────────────
//   1) phi[i] = i initialize (sabse pehle assume coprime)
//   2) i prime hai agar phi[i] == i
//   3) har multiple j = i, 2i, 3i... pe phi[j] -= phi[j]/i
//      (i ke saare multiples se i wale count hatao)
vector<int> phi_1_to_n(int n)
{
    vector<int> phi(n + 1);
    for (int i = 0; i <= n; i++)
        phi[i] = i;

    for (int i = 2; i <= n; i++)
    {
        if (phi[i] == i) // i prime hai
        {
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
    return phi;
}

int main()
{
    int n;
    cout << "Enter a number: ";
    cin >> n;

    cout << "Euler's Totient Function of " << n << ": " << phi(n) << endl;

    cout << "Euler's Totient Function for all numbers from 1 to " << n << ":" << endl;
    vector<int> totients = phi_1_to_n(n);
    for (int i = 1; i <= n; i++)
    {
        cout << "φ(" << i << ") = " << totients[i] << endl;
    }

    return 0;
}
