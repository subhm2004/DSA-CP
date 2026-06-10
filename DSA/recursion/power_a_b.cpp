/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : power_a_b.cpp
 * PROBLEM  : Power A B
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// POWER a^b — Naive vs Fast (Binary Exponentiation)
// ────────────────────────────────────────────────────────────────────────────
// Naive: b baar multiply — O(b) time
// Fast: b ko half karo — O(log b) time
// Even b -> a^(b/2) * a^(b/2); Odd b -> a * a^(b/2) * a^(b/2)
// ════════════════════════════════════════════════════════════════════════════

// ── power: naive recursive a^b (optimized nahi) ─────────────────────────────
//   1) base case b==0 -> 1
//   2) har step pe ek baar multiply — slow approach
int power(int& a, int b) { // not an optimised approach
    if(b==0) {
        return 1;
    }
   int ans = a* power(a, b-1);
}

// ── fastpower: binary exponentiation se a^b ─────────────────────────────────
//   1) base case b==0 -> 1
//   2) b even hai -> fastpower(a,b/2) * fastpower(a,b/2)
//   3) b odd hai -> a * fastpower(a,b/2) * fastpower(a,b/2)
//   4) har step pe exponent half — log time
int fastpower(int& a, int b) {
    if(b==0) {
        return 1;
    }
    if(b%2==0) { // even — do equal halves
        return fastpower(a,b/2) * fastpower(a, b/2);
    }
    else {
        return a* fastpower( a,  b/2) * fastpower(a, b/2);
    }
}

// ── main: base aur exponent input, fast power compute ───────────────────────
int main() {
    int a,b;
    cout<< "enter base and exponent"<< endl;
    cin>>a>> b;
    int final= fastpower(a,b);
    cout<< a<< " to the power "<< b<< " is "<< final<< endl;   

}
