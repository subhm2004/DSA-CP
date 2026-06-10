#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// NUMBER & SUM OF DIVISORS — Prime Factorization se
// ────────────────────────────────────────────────────────────────────────────
// n = p1^e1 * p2^e2 * ...
//   count of divisors  = Π(ei + 1)
//   sum of divisors    = Π(1 + pi + pi^2 + ... + pi^ei)
// Dono O(√n) me prime factors nikaal ke formula apply karte hain
// ════════════════════════════════════════════════════════════════════════════

// ── numberOfDivisors: n ke kitne divisors hain ──────────────────────────────
//   1) har prime i | n ke liye exponent e count karo (kitni baar divide)
//   2) total *= (e + 1) — har prime ke liye (e+1) choices
//   3) bacha hua prime factor -> total *= 2
long long numberOfDivisors(long long num)
{
    long long total = 1;
    for (long long i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            int e = 0;
            while (num % i == 0)
            {
                e++;
                num /= i;
            }
            total *= (e + 1); // p^e ke liye (e+1) divisor choices
        }
    }
    if (num > 1)
        total *= 2; // last prime factor p^1 -> (1+1) = 2
    return total;
}

// ── SumOfDivisors: saare divisors ka sum ────────────────────────────────────
//   1) prime p^e ke liye geometric sum = 1 + p + p^2 + ... + p^e
//   2) loop se sum aur pow calculate karo
//   3) total *= har prime ka geometric sum
//   4) bacha prime -> total *= (1 + num)
long long SumOfDivisors(long long num)
{
    long long total = 1;
    for (long long i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            int e = 0;
            while (num % i == 0)
            {
                e++;
                num /= i;
            }
            long long sum = 1, pow = 1;
            while (e-- >= 0)
            {
                sum += pow; // 1 + i + i^2 + ... + i^e
                pow *= i;
            }
            total *= sum;
        }
    }
    if (num > 1)
        total *= (1 + num); // last prime p -> sum = 1 + p
    return total;
}

int main()
{
    long long num;
    cout << "Enter a number: ";
    cin >> num;

    cout << "Number of divisors of " << num << ": " << numberOfDivisors(num) << endl;
    cout << "Sum of divisors of " << num << ": " << SumOfDivisors(num) << endl;

    return 0;
}
