#include <iostream>
using namespace std;

const long long MOD = 1e9 + 7;

// ✅ Recursive Binary Exponentiation
double binary_Expo_Recursive(double a, long long b)
{
    if (b == 0)
        return 1.0;

    if (b < 0)
        return 1.0 / binary_Expo_Recursive(a, -b);

    double half = binary_Expo_Recursive(a, b >> 1);
    double result = half * half;
    if (b & 1)
        result *= a;

    return result;
}

// ✅ Iterative Binary Exponentiation
double binary_Expo_Iterative(double a, long long b)
{
    bool isNegative = (b < 0);
    if (isNegative)
        b = -b;

    double result = 1.0;
    while (b > 0)
    {
        if (b & 1)
            result *= a;
        a *= a;
        b >>= 1;
    }

    return isNegative ? 1.0 / result : result;
}

// ✅ Apply MOD to result properly
long long applyMod(double value)
{
    long long res = static_cast<long long>(value) % MOD;
    return (res + MOD) % MOD; // Ensure non-negative result
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
