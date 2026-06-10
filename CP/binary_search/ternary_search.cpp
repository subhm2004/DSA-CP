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

// ════════════════════════════════════════════════════════════════════════════
// TERNARY SEARCH — Unimodal function ka max/min dhundho
// ────────────────────────────────────────────────────────────────────────────
// [l,r] ko teen hisse me todo: m1 aur m2 (1/3 aur 2/3 points)
// Unimodal (pehle badhta phir ghata) -> worse third discard karo
// Integer: end me 2-3 points brute force se check
// Real: fixed iterations (200) se converge
// ════════════════════════════════════════════════════════════════════════════

// ── ternarySearchMax: unimodal f(x) ka maximum x dhundho ────────────────────
//   1) m1, m2 = range ke 1/3 aur 2/3 points
//   2) f(m1) < f(m2) -> max right side me -> l = m1
//   3) warna max left side me -> r = m2
//   4) r-l <= 2 pe loop band, [l..r] brute force best return
ll ternarySearchMax(ll l, ll r, function<ll(ll)> f) {
    while (r - l > 2) {
        ll m1 = l + (r - l) / 3;
        ll m2 = r - (r - l) / 3;
        if (f(m1) < f(m2))
            l = m1; // peak right me hai
        else
            r = m2; // peak left me hai
    }
    ll best = l;
    for (ll x = l; x <= r; x++)
        if (f(x) > f(best)) best = x;
    return best;
}

// ── ternarySearchMin: unimodal f(x) ka minimum x dhundho ────────────────────
//   1) same thirds split, par comparison ulta (min ke liye)
//   2) f(m1) > f(m2) -> min right me -> l = m1
//   3) warna r = m2
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

// ── ternarySearchReal: double domain pe approximate optimum ─────────────────
//   1) fixed iterations (200) me range narrow karo
//   2) har step me m1, m2 compare karke worse third hatao
//   3) (l+r)/2 return — approximate answer
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
    auto f = [](ll x) { return -(x - 7) * (x - 7) + 50; };
    cout << ternarySearchMax(0, 20, f) << endl; // 7

    auto g = [](double x) { return -(x - 2.5) * (x - 2.5); };
    cout << fixed << setprecision(4) << ternarySearchReal(0.0, 10.0, g) << endl;
    return 0;
}
