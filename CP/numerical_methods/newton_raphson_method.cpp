/*
 * ============================================================================
 * TOPIC    : Numerical Methods — Newton-Raphson
 * FILE     : newton_raphson_method.cpp
 * PROBLEM  : Find square root of a number with high precision
 * APPROACH : Newton iteration: x_next = (x + n/x) / 2
 * COMPLEX  : O(log(1/eps)) iterations  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// NEWTON-RAPHSON — Square root nikalo
// ────────────────────────────────────────────────────────────────────────────
// f(x) = x² - n = 0 solve karna hai
// Newton step: x_new = x - f(x)/f'(x) = (x + n/x) / 2
// Jab |x - x_new| < eps -> converge ho gaya
// Binary search wala helper integer part ke liye (optional)
// ════════════════════════════════════════════════════════════════════════════

// ── binary_search_sqrt: integer floor of sqrt(num) ──────────────────────────
//   1) lo=0, hi=num pe BS
//   2) mid*mid <= num -> ans=mid, lo=mid+1
//   3) warna hi=mid-1
int binary_search_sqrt(int num)
{
    int left = 0;
    int right = num;
    int ans = 0;
    while (left <= right)
    {
        int mid = (left + right) >> 1;
        if (1LL * mid * mid <= num)
        {
            ans = mid;
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return ans;
}

// ── sqrt_newton: n ka square root high precision se ────────────────────────
//   1) x = 1 initial guess (koi bhi positive guess chalega)
//   2) nx = (x + n/x) / 2 — Newton formula for sqrt
//   3) |x - nx| < eps pe stop
//   4) x return — sqrt(n) approximate
double sqrt_newton(double n)
{
    const double eps = 1e-15;
    double x = 1;
    for (;;)
    {
        double nx = (x + n / x) / 2;
        if (abs(x - nx) < eps)
            break;
        x = nx;
    }
    return x;
}

int main()
{
    double n = 10.0;
    cout << fixed << setprecision(15);
    cout << "Square root of " << n << " = " << sqrt_newton(n) << "\n";
    return 0;
}
