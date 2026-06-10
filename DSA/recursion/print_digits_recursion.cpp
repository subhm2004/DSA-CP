/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : print_digits_recursion.cpp
 * PROBLEM  : Print Digits Recursion
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// PRINT DIGITS — Number ke digits left-to-right print
// ────────────────────────────────────────────────────────────────────────────
// Pehle n/10 pe jao (chhota number), phir n%10 print — tail recursion
// Example: 123 -> pehle 12 solve, phir 3 print, phir 2, phir 1
// Order maintain hota hai kyunki print recursion ke baad hota hai
// ════════════════════════════════════════════════════════════════════════════

// ── printdigit: number n ke digits print ────────────────────────────────────
//   1) n==0 -> base case, return
//   2) pehle printdigit(n/10) — left digits pehle
//   3) phir n%10 print — current last digit
void printdigit(int n) {
    if(n==0) {
        return ;
    }
     int a = n/10;
    printdigit(a);  // pehle chhote number ke digits
    int rem = n%10;
    cout<< "digit" << rem<< endl;  // ab current digit print
}

// ── main: user number input, digits print ───────────────────────────────────
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    printdigit(n);    
}
