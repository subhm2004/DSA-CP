/*
 * ============================================================================
 * TOPIC    : Basics
 * FILE     : reverse_string.cpp
 * PROBLEM  : Reverse String
 * ABOUT    : Fundamental DSA — loops, sorting, strings, character operations
 * APPROACH : Swap from both ends or reverse links iteratively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <string.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// REVERSE STRING — two pointers se in-place reverse
// ────────────────────────────────────────────────────────────────────────────
// Funda: i=start, j=end — swap ch[i] aur ch[j], andar badhao
// getline se string input, strlen se length
// COMPLEX: Time O(n)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── reversestring: char array reverse karo ─────────────────────────────────
//   1) cin.getline se string input
//   2) i=0, j=strlen-1 — two pointer swap
//   3) i++, j-- — poori string reverse in-place
void reversestring(char ch[100]) {
    cout<< "enter any string" << endl;
    cin.getline(ch,100);
    int i=0, j=strlen(ch) -1;
    while(i<=j) {
        swap(ch[i], ch[j]);
        i++;
        j--;
    }
}


// ── printstr: reversed string print ────────────────────────────────────────
//   1) strlen tak har character print
void printstr(char ch[100]) {
    for(int i=0; i<strlen(ch); i++) {
        cout<< ch[i];
    }
}


// ── main: input, reverse, print ────────────────────────────────────────────
//   1) char array declare
//   2) reversestring + printstr
int main() {
    char ch[100];   
    reversestring( ch);
    printstr(ch);

}
