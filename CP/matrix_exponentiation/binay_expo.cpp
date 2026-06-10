#include <iostream>
using namespace std;

const long long MOD = 1e9 + 7;

// ════════════════════════════════════════════════════════════════════════════
// BINARY EXPONENTIATION — a^b fast calculate karna
// ────────────────────────────────────────────────────────────────────────────
// Naive: a ko b baar multiply -> O(b) slow
// Binary expo: O(log b)
//
// Idea (same as matrix expo):
//   b odd hai  -> result me ek 'a' multiply karo
//   har step   -> a = a*a, b = b/2
//
// Negative power: a^(-b) = 1 / a^b
// ════════════════════════════════════════════════════════════════════════════

// ── binary_Expo_Recursive: a^b recursive tarike se ─────────────────────────
//   1) base: b==0 -> 1 return; b<0 -> reciprocal (a^(-b))
//   2) half = a^(b/2) recursively nikalo
//   3) result = half*half; agar b odd (b&1) -> ek aur a multiply
//   4) divide-and-conquer — O(log b) recursive calls
double binary_Expo_Recursive(double a, long long b)
{
    if (b == 0)
        return 1.0;

    if (b < 0)
        return 1.0 / binary_Expo_Recursive(a, -b);

    double half = binary_Expo_Recursive(a, b >> 1);
    double result = half * half;
    if (b & 1)                 // last bit set -> ek extra a multiply
        result *= a;

    return result;
}

// ── binary_Expo_Iterative: a^b iterative (loop) tarike se ───────────────────
//   1) negative b ho to flag set, b = -b (baad me reciprocal)
//   2) result = 1; jab tak b > 0: odd bit -> result *= a
//   3) har step: a = a*a, b >>= 1
//   4) negative tha to 1/result return — same logic, loop me
double binary_Expo_Iterative(double a, long long b)
{
    bool isNegative = (b < 0);
    if (isNegative)
        b = -b;

    double result = 1.0;
    while (b > 0)
    {
        if (b & 1)             // current bit 1 -> result me a include
            result *= a;
        a *= a;                // base square
        b >>= 1;               // next bit
    }

    return isNegative ? 1.0 / result : result;
}

// ── applyMod: double result ko MOD ke andar lao (non-negative) ───────────────
//   1) double ko long long me cast, % MOD
//   2) negative ho to +MOD karke non-negative banao
//   3) modular arithmetic output ke liye helper
long long applyMod(double value)
{
    long long res = static_cast<long long>(value) % MOD;
    return (res + MOD) % MOD;
}

int main()
{
    double a = 2.0;
    long long b = -10;

    double rec = binary_Expo_Recursive(a, b);
    double iter = binary_Expo_Iterative(a, b);

    cout << "Recursive (raw): " << rec << ", mod: " << applyMod(rec) << endl;
    cout << "Iterative (raw): " << iter << ", mod: " << applyMod(iter) << endl;

    return 0;
}
