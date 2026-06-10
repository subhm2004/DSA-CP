/*
 * ============================================================================
 * TOPIC    : Strings
 * FILE     : remove_duplicates_string.cpp
 * PROBLEM  : Remove Duplicates String
 * LEETCODE : 1047 — Remove All Adjacent Duplicates In String
 * ABOUT    : String manipulation with STL
 * APPROACH : Hash set or sorting to find duplicates.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <string>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// ADJACENT DUPLICATES REMOVE — stack jaisa ans string use karo
// ────────────────────────────────────────────────────────────────────────────
// Funda: ans ka last char == current? to pop (cancel pair)
// Warna push karo — stack simulation with string
// LeetCode 1047 — abbaca → ca
// ════════════════════════════════════════════════════════════════════════════

// ── duplicate: adjacent pair cancel karo ───────────────────────────────────
//   1) str = "abbaca", ans = "" se start
//   2) har char pe — ans empty nahi aur match? pop_back
//   3) warna ans me push_back
//   4) i++ karke aage badho, final ans print
void duplicate() {
    string str = "abbaca";
    string ans = ""; // result stack
    int i=0;
    while(i< str.length()) {
        if(ans.length() >0) {
            if(str[i] != ans[ans.length()-1]) {
               ans.push_back(str[i]); // naya char add
            }
            else {
               ans.pop_back(); // adjacent duplicate — dono hatao
            }
        }
        else {
            ans.push_back(str[i]); // pehla char seedha daalo
        }
        i++;
    }    
    cout<< ans;       
}

// ── main: duplicate demo run ───────────────────────────────────────────────
//   1) duplicate() call — output "ca"
int main() {
    duplicate();
}
