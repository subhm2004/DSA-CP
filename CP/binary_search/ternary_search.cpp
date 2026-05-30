/*
 * ============================================================================
 * TOPIC    : Binary Search — Ternary Search
 * FILE     : ternary_search.cpp
 * PROBLEM  : Max/min of unimodal function on integer or real domain
 * APPROACH : Split [l,r] into thirds; discard worse third each step
 * COMPLEX  : O(log(r-l)) iterations
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// Maximize f(x) for x in [l, r] (unimodal: increases then decreases)
ll ternarySearchMax(ll l, ll r, function<ll(ll)> f) {
    while (r - l > 2) {
        ll m1 = l + (r - l) / 3;
        ll m2 = r - (r - l) / 3;
        if (f(m1) < f(m2))
            l = m1;
        else
            r = m2;
    }
    ll best = l;
    for (ll x = l; x <= r; x++)
        if (f(x) > f(best)) best = x;
    return best;
}

// Minimize unimodal (decreases then increases)
ll ternarySearchMin(ll l, ll r, function<ll(ll)> f) {
    while (r - l > 2) {
        ll m1 = l + (r - l) / 3;
        ll m2 = r - (r - l) / 3;
        if (f(m1) > f(m2))
            l = m1;
        else
            r = m2;
    }
    ll best = l;
    for (ll x = l; x <= r; x++)
        if (f(x) < f(best)) best = x;
    return best;
}

// Real-valued version (double)
double ternarySearchReal(double l, double r, function<double(double)> f, int it = 200) {
    while (it--) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        if (f(m1) < f(m2))
            l = m1;
        else
            r = m2;
    }
    return (l + r) / 2;
}

int main() {
    // f(x) = -(x-7)^2 + 50, max at x=7 on [0,20]
    auto f = [](ll x) { return -(x - 7) * (x - 7) + 50; };
    cout << ternarySearchMax(0, 20, f) << endl; // 7

    auto g = [](double x) { return -(x - 2.5) * (x - 2.5); };
    cout << fixed << setprecision(4) << ternarySearchReal(0.0, 10.0, g) << endl; // ~2.5
    return 0;
}
