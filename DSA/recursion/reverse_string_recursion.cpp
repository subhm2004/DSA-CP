/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : reverse_string_recursion.cpp
 * PROBLEM  : Reverse String Recursion
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Swap from both ends or reverse links iteratively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// REVERSE STRING (Recursion) — Two pointers se swap
// ────────────────────────────────────────────────────────────────────────────
// i aur j dono ends se aate hain — swap karke i+1, j-1
// Base: i>j -> string reverse ho chuki
// Har step pe current state print (debug ke liye)
// ════════════════════════════════════════════════════════════════════════════

// ── printstr: string characters print karo ──────────────────────────────────
//   1) loop se har character cout
//   2) helper function — reverse ke beech state dekho
void printstr(string str) {
    cout<< "string is: "<< " ";
    for(int i=0; i< str.length(); i++) {
        cout<< str[i];
    }
    cout<< endl;
}

// ── reversestring: i aur j se recursive reverse ───────────────────────────────
//   1) pehle current string print (debug)
//   2) i>j -> base case, final string print
//   3) swap(str[i], str[j]) — ends swap
//   4) reversestring(str, i+1, j-1) — andar wala part
void reversestring(string& str, int i, int j) {
    printstr(str);
    if(i>j) {
        cout<< str << endl;
        return;
    }    
    swap(str[i], str[j]);  // dono ends swap
    reversestring(str, i+1, j-1);
}

// ── main: string reverse demo ───────────────────────────────────────────────
int main() {
    string str = "vanshika";
    int i=0, j= str.length()-1;
    reversestring(str,i,j);
}
