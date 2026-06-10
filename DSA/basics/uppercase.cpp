/*
 * ============================================================================
 * TOPIC    : Basics
 * FILE     : uppercase.cpp
 * PROBLEM  : Uppercase
 * ABOUT    : Fundamental DSA — loops, sorting, strings, character operations
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <string.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LOWERCASE TO UPPERCASE — ASCII arithmetic se convert
// ────────────────────────────────────────────────────────────────────────────
// Funda: 'a'=97, 'A'=65 — ch[i] - 'a' + 'A' se lowercase -> uppercase
// Har character pe formula lagao — in-place conversion
// COMPLEX: Time O(n)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── uppercase: string ke saare chars uppercase karo ────────────────────────
//   1) getline se string input
//   2) har char: ch[i] - 'a' + 'A' — lowercase to uppercase
//   3) same array me in-place update
void uppercase(char ch[100]) {
    cout<< "enter any string"<< endl;
    cin.getline(ch,100);
    for(int i=0; i<strlen(ch); i++) {
        ch[i]= ch[i]-'a'+'A';
    }
}


// ── main: input string uppercase karke print ───────────────────────────────
//   1) char array declare
//   2) uppercase() call, result print
int main() {
    char ch[100];
    uppercase(ch);
    cout<< ch;

}
