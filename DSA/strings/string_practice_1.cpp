/*
 * ============================================================================
 * TOPIC    : Strings
 * FILE     : string_practice_1.cpp
 * PROBLEM  : String Practice 1
 * ABOUT    : String manipulation with STL
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <string>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// STRING PRACTICE — adjacent duplicate remove + substring remove
// ────────────────────────────────────────────────────────────────────────────
// Funda: stack-style ans string + find/erase for substring removal
// ════════════════════════════════════════════════════════════════════════════

// ── duplicate: for-loop se adjacent duplicates hatao ───────────────────────
//   1) str traverse — ans ka last == current? pop_back
//   2) warna push_back
//   3) final ans print — LeetCode 1047 style
void duplicate() {
    string str = "abbaca";
    string ans = "";
    for(int i=0; i< str.length(); i++) {
        if(ans.length() > 0 && str[i] == ans[ans.length()-1]) {
            ans.pop_back(); // pair cancel
        }
        else {
            ans.push_back(str[i]);
        }
    }
    cout<< ans<< endl;
}

// ── removepart: target substring repeatedly erase ────────────────────────────
//   1) str me "abc" dhoondo find se
//   2) while loop — mila to erase(i, 3)
//   3) cleaned str print
void removepart() {
    string str = "daabcbaabcbc";
    string target = "abc";
    int i=0;
    while(i < str.length()) {
        if(str.find(target)) { // target mila?
            str.erase(i,3); // 3 chars erase
        }
    }
    cout<< str;
}

// ── main: removepart demo ────────────────────────────────────────────────────
//   1) removepart() call karo
int main() {
    removepart();
}
