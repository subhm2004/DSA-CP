/*
 * ============================================================================
 * TOPIC    : Number Theory — ModInt
 * FILE     : mod_int.cpp
 * PROBLEM  : Modular arithmetic wrapper for contest math
 * APPROACH : Template struct with + - * / and pow()
 * COMPLEX  : O(1) ops, O(log exp) for pow
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

template <int MOD = 1'000'000'007>
struct ModInt {
    int v;
    ModInt(long long x = 0) : v((int)((x % MOD + MOD) % MOD)) {}

    int val() const { return v; }

    ModInt &operator+=(ModInt o) {
        v += o.v;
        if (v >= MOD) v -= MOD;
        return *this;
    }
    ModInt &operator-=(ModInt o) {
        v -= o.v;
        if (v < 0) v += MOD;
        return *this;
    }
    ModInt &operator*=(ModInt o) {
        v = (int)((long long)v * o.v % MOD);
        return *this;
    }

    friend ModInt operator+(ModInt a, ModInt b) { return a += b; }
    friend ModInt operator-(ModInt a, ModInt b) { return a -= b; }
    friend ModInt operator*(ModInt a, ModInt b) { return a *= b; }

    static ModInt pow(ModInt a, long long e) {
        ModInt r = 1;
        while (e > 0) {
            if (e & 1) r *= a;
            a *= a;
            e >>= 1;
        }
        return r;
    }

    friend ModInt inv(ModInt a) { return pow(a, MOD - 2); }

    friend ModInt operator/(ModInt a, ModInt b) { return a * inv(b); }

    friend ostream &operator<<(ostream &os, ModInt x) { return os << x.v; }
};

using Mint = ModInt<1'000'000'007>;

int main() {
    Mint a = 100000007, b = 999999937;
    cout << a * b << endl;
    cout << Mint::pow(a, 100) << endl;
    cout << a / b << endl;
    return 0;
}
