/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : factorial.cpp
 * PROBLEM  : Factorial
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + recursive call on smaller input.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// FACTORIAL & COUNTING — Recursion ki basic building blocks
// ────────────────────────────────────────────────────────────────────────────
// factorial(n) = n * factorial(n-1), base case n==0 ya n==1
// counting(n) = n se 1 tak print — head recursion (pehle call, baad me print)
// Dono examples recursion stack samajhne ke liye perfect hain
// ════════════════════════════════════════════════════════════════════════════

// ── factorial: n! return karta hai ────────────────────────────────────────
//   1) base case — 0! aur 1! dono 1 hote hain
//   2) recursive step — n * factorial(n-1)
//   3) har call ek chhota subproblem solve karti hai
//   4) stack unwinding pe final answer milta hai
int factorial(int n) {
    if(n==0 || n==1) {  // base case — recursion ruk jao
        return 1;
    }
    int fact = n* factorial(n-1);  // chhota problem solve karo, multiply karo
    return fact;
}

// ── counting: n se 1 tak descending print ───────────────────────────────────
//   1) base case n==0 — kuch print mat karo
//   2) pehle current n print karo (head recursion)
//   3) phir counting(n-1) call karo
//   4) output: n n-1 n-2 ... 1
void counting(int n) {
    if(n==0) {
        return;
    }
    cout<< n<< " ";
    counting(n-1);  // chhote number pe jao
}

// ── main: user input leke counting demo ─────────────────────────────────────
//   1) n input lo
//   2) counting(n) se n se 1 tak print
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    counting(n);
    return 0;
}
