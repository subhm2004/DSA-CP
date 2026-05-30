/*
 * ============================================================================
 * TOPIC    : Math — FFT & NTT
 * FILE     : fft_ntt.cpp
 * PROBLEM  : Polynomial multiplication / convolution mod prime
 * APPROACH : Cooley-Tukey FFT (double); NTT mod 998244353
 * COMPLEX  : O(n log n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> &a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert)
        for (cd &x : a) x /= n;
}

vector<long long> convolveFFT(const vector<long long> &a, const vector<long long> &b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < (int)a.size() + (int)b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);
    vector<long long> res(a.size() + b.size() - 1);
    for (int i = 0; i < (int)res.size(); i++)
        res[i] = llround(fa[i].real());
    return res;
}

// ── NTT (mod 998244353, primitive root 3) ───────────────────────────────────
namespace NTT {
const int MOD = 998244353;
const int G = 3;

int modPow(int a, long long e) {
    long long r = 1, x = a;
    while (e) {
        if (e & 1) r = r * x % MOD;
        x = x * x % MOD;
        e >>= 1;
    }
    return (int)r;
}

void ntt(vector<int> &a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        int w = modPow(G, (MOD - 1) / len);
        if (invert) w = modPow(w, MOD - 2);
        for (int i = 0; i < n; i += len) {
            long long wn = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i + j], v = (int)(a[i + j + len / 2] * wn % MOD);
                a[i + j] = u + v < MOD ? u + v : u + v - MOD;
                a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + MOD;
                wn = wn * w % MOD;
            }
        }
    }
    if (invert) {
        int inv_n = modPow(n, MOD - 2);
        for (int &x : a) x = (int)((long long)x * inv_n % MOD);
    }
}

vector<int> convolve(const vector<int> &a, const vector<int> &b) {
    vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < (int)a.size() + (int)b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);
    ntt(fa, false);
    ntt(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] = (int)((long long)fa[i] * fb[i] % MOD);
    ntt(fa, true);
    fa.resize(a.size() + b.size() - 1);
    return fa;
}
} // namespace NTT

int main() {
    vector<long long> a = {1, 2, 3}, b = {4, 5};
    auto c = convolveFFT(a, b);
    cout << "FFT: ";
    for (long long x : c) cout << x << ' ';
    cout << endl;

    vector<int> p = {1, 2, 3}, q = {4, 5};
    auto r = NTT::convolve(p, q);
    cout << "NTT: ";
    for (int x : r) cout << x << ' ';
    cout << endl;
    return 0;
}
