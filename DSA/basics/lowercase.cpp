/*
 * ============================================================================
 * TOPIC    : Basics
 * FILE     : lowercase.cpp
 * PROBLEM  : Lowercase
 * ABOUT    : Fundamental DSA — loops, sorting, strings, character operations
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <string.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// UPPERCASE TO LOWERCASE — ASCII arithmetic se convert
// ────────────────────────────────────────────────────────────────────────────
// Funda: 'A'=65, 'a'=97 — difference 32
// ch[i] - 'A' + 'a' se uppercase -> lowercase
// COMPLEX: Time O(n)  |  Space O(1) in-place
// ════════════════════════════════════════════════════════════════════════════

// ── lowercase: string ke saare chars lowercase karo ────────────────────────
//   1) getline se string input
//   2) har char pe ASCII formula: ch[i] - 'A' + 'a'
//   3) in-place conversion — same array me
void lowercase(char ch[00]){
    cout<< "enter any string"<< endl;
    cin.getline(ch,100);
    for(int i=0; i<strlen(ch); i++) {
        ch[i] = ch[i] - 'A' + 'a';
    }
 }


// ── main: input string lowercase karke print ─────────────────────────────────
//   1) char array declare
//   2) lowercase() call, result print
int main() {
    char ch[100];
    lowercase(ch);
    cout<< ch;
}
