/*
 * ============================================================================
 * TOPIC    : Basics
 * FILE     : palindrome.cpp
 * PROBLEM  : Palindrome
 * ABOUT    : Fundamental DSA — loops, sorting, strings, character operations
 * APPROACH : Two pointers from both ends or recursive check.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <string.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// PALINDROME CHECK — two pointers se start/end compare
// ────────────────────────────────────────────────────────────────────────────
// Funda: i=start, j=end — ch[i]==ch[j] hona chahiye har step pe
// Koi mismatch -> false; poora match -> true
// COMPLEX: Time O(n)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── pallindrome: kya string palindrome hai? ────────────────────────────────
//   1) getline se string input
//   2) i=0, j=len-1 — two pointer compare
//   3) mismatch pe false return, poora match pe true
bool pallindrome(char ch[100]) {
    cout<< "enter any string"<< endl;
    cin.getline(ch,100);
    int i=0, j= strlen(ch)-1;
    bool same= false;
    while(i<=j) {
        if(ch[i] == ch[j]) {
            same= true;
        }
        else {
            same = false;
            break;  // mismatch — palindrome nahi
        }
        i++;
        j--;
    }
    return same;
}


// ── main: palindrome check demo ────────────────────────────────────────────
//   1) char array input
//   2) true/false print
int main() {
    char ch[100];
    bool ans = pallindrome(ch);
    cout<< ans<< endl;
}
