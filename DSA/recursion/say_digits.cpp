/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : say_digits.cpp
 * PROBLEM  : Say Digits
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <math.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// SAY DIGITS — Number ko words me bolna (zero, one, two, ...)
// ────────────────────────────────────────────────────────────────────────────
// Last digit n%10 nikalo, n/10 pe recurse, phir arr[digit] print
// Tail recursion — pehle chhota number, baad me word print
// arr[0]="zero", arr[1]="one", ... mapping use hoti hai
// ════════════════════════════════════════════════════════════════════════════

// ── printdigit: number ke har digit ka word print ───────────────────────────
//   1) n==0 -> base case
//   2) digit = n%10 — last digit
//   3) n = n/10, recursive call — baaki digits
//   4) recursion wapas aate hi arr[digit] print
void printdigit(string arr[10], int& n) {
    if(n==0) {
        return;
    }
    int digit = n % 10;
    n= n/10;
    printdigit(arr, n);  // pehle left digits ke words
    cout<< arr[digit]<< endl;  // ab current digit ka naam
}

// ── main: number input, digit names print ───────────────────────────────────
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    string arr[10] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    printdigit(arr, n);    
}
