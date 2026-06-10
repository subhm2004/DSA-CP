/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : fibonacci.cpp
 * PROBLEM  : Fibonacci
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + recursive call on smaller input.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// FIBONACCI — nth term via pure recursion
// ────────────────────────────────────────────────────────────────────────────
// Series: 0, 1, 1, 2, 3, 5, 8, ...
// fib(n) = fib(n-1) + fib(n-2) — do recursive calls har step pe
// Exponential time — DP se optimize ho sakta hai (yahan sirf recursion demo)
// ════════════════════════════════════════════════════════════════════════════

// ── fibonacci: nth Fibonacci term return ────────────────────────────────────
//   1) base case n==1 -> 0, n==2 -> 1
//   2) recursive — fib(n-1) + fib(n-2)
//   3) dono branches alag-alag subproblems solve karte hain
//   4) overlapping subproblems — isliye slow without memoization
int fibonacci(int n) {
    if(n==1) {
        return 0;  // pehla term
    }
    if(n==2) {
        return 1;  // doosra term
    }
    int fib = fibonacci(n-1) + fibonacci(n-2);
    return fib;
}

// ── main: nth term print karo ───────────────────────────────────────────────
int main() {
    int n;
    cout<< "enter number of last term of fibonacci series"<< endl;
    cin>> n;
    int ans = fibonacci(n);
    cout<< n<< " term of series is "<<ans<< endl;
    return 0;
}
