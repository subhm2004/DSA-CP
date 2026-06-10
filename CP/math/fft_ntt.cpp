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

// ════════════════════════════════════════════════════════════════════════════
// FFT (Fast Fourier Transform) + NTT (Number Theoretic Transform)
// ────────────────────────────────────────────────────────────────────────────
// Dono ka goal: do polynomials ka product (convolution) O(n log n) me
//   C[k] = Σ A[i] * B[k-i]  — har coefficient jahan i+j=k
//
// FFT: complex roots of unity, double precision — exact integer chahiye to careful
// NTT: mod 998244353, primitive root 3 — contest me zyada safe (no rounding error)
//
// Steps (dono similar):
//   1) size ko next power of 2 tak pad karo
//   2) bit-reversal permutation
//   3) butterfly loops (len = 2, 4, 8, ...)
//   4) pointwise multiply, inverse transform
// COMPLEX: O(n log n)
// ════════════════════════════════════════════════════════════════════════════

using cd = complex<double>;
const double PI = acos(-1);

// ── fft: in-place Cooley-Tukey FFT / inverse FFT ──
//   1) bit-reversal reorder — index i ka reversed j se swap
//   2) len = 2,4,8,... butterfly: u±v*ω
//   3) invert=true → angle negative, end me /n
void fft(vector<cd> &a, bool invert)
{
    int n = a.size();
    // Step 1: bit-reversal permutation
    for (int i = 1, j = 0; i < n; i++)
    {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            swap(a[i], a[j]);
    }
    // Step 2: butterfly — har stage pe len double
    for (int len = 2; len <= n; len <<= 1)
    {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len)
        {
            cd w(1);
            for (int j = 0; j < len / 2; j++)
            {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert)
        for (cd &x : a)
            x /= n;
}

// ── convolveFFT: polynomial multiplication via FFT ──
//   1) pad to power of 2
//   2) FFT both → pointwise multiply → inverse FFT
//   3) llround(real part) — chhote coeffs pe safe
vector<long long> convolveFFT(const vector<long long> &a, const vector<long long> &b)
{
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < (int)a.size() + (int)b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);
    vector<long long> res(a.size() + b.size() - 1);
    for (int i = 0; i < (int)res.size(); i++)
        res[i] = llround(fa[i].real());
    return res;
}

// ── NTT namespace: mod 998244353 (2^23 * 119 + 1), primitive root G=3 ──
//   Contest favorite mod — NTT friendly, primitive root exists
namespace NTT
{
const int MOD = 998244353;
const int G = 3;

int modPow(int a, long long e)
{
    long long r = 1, x = a;
    while (e)
    {
        if (e & 1)
            r = r * x % MOD;
        x = x * x % MOD;
        e >>= 1;
    }
    return (int)r;
}

// ── ntt: FFT ka mod version — same butterfly, integer arithmetic ──
void ntt(vector<int> &a, bool invert)
{
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++)
    {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1)
    {
        int w = modPow(G, (MOD - 1) / len); // len-th root of unity
        if (invert)
            w = modPow(w, MOD - 2);
        for (int i = 0; i < n; i += len)
        {
            long long wn = 1;
            for (int j = 0; j < len / 2; j++)
            {
                int u = a[i + j], v = (int)(a[i + j + len / 2] * wn % MOD);
                a[i + j] = u + v < MOD ? u + v : u + v - MOD;
                a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + MOD;
                wn = wn * w % MOD;
            }
        }
    }
    if (invert)
    {
        int inv_n = modPow(n, MOD - 2);
        for (int &x : a)
            x = (int)((long long)x * inv_n % MOD);
    }
}

// ── convolve: NTT se polynomial product mod MOD ──
vector<int> convolve(const vector<int> &a, const vector<int> &b)
{
    vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < (int)a.size() + (int)b.size())
        n <<= 1;
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

int main()
{
    // (1 + 2x + 3x²) * (4 + 5x) = 4 + 13x + 22x² + 15x³
    vector<long long> a = {1, 2, 3}, b = {4, 5};
    auto c = convolveFFT(a, b);
    cout << "FFT: ";
    for (long long x : c)
        cout << x << ' ';
    cout << endl;

    vector<int> p = {1, 2, 3}, q = {4, 5};
    auto r = NTT::convolve(p, q);
    cout << "NTT: ";
    for (int x : r)
        cout << x << ' ';
    cout << endl;
    return 0;
}
