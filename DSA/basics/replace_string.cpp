/*
 * ============================================================================
 * TOPIC    : Basics
 * FILE     : replace_string.cpp
 * PROBLEM  : Replace String
 * ABOUT    : Fundamental DSA — loops, sorting, strings, character operations
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <string.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// REPLACE SPACES — string me space ko @ se replace
// ────────────────────────────────────────────────────────────────────────────
// Funda: har character scan — space ' ' mila to '@' daalo
// In-place replacement — extra space nahi chahiye
// COMPLEX: Time O(n)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── replace_space: spaces ko @ se replace karo ───────────────────────────
//   1) getline se string input
//   2) i=0 se '\0' tak — ch[i]==' ' ho to ch[i]='@'
//   3) in-place replace complete
void replace_space(char ch[100]) {
    cout<< "enter any string"<< endl;
    cin.getline(ch,100);
    int i=0;
    while(ch[i] != '\0') {
        if(ch[i] == ' ') {
            ch[i] = '@';
        }
        i++;
    }
}



// ── main: replace demo (call missing — print empty) ────────────────────────
//   1) char array declare
//   2) replace_space() call karna chahiye — abhi sirf print
int main() {
    char ch[100];
    cout<< ch;
    
}
