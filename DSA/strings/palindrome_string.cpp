/*
 * ============================================================================
 * TOPIC    : Strings
 * FILE     : palindrome_string.cpp
 * PROBLEM  : Palindrome String
 * LEETCODE : 125 — Valid Palindrome
 * ABOUT    : String manipulation with STL
 * APPROACH : Two pointers from both ends or recursive check.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <string>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// PALINDROME CHECK — two pointers se start/end compare
// ────────────────────────────────────────────────────────────────────────────
// Funda: i start se, j end se — match ho to aage badho
// Mismatch pe pop_back try karte hain (incomplete logic — learning demo)
// ════════════════════════════════════════════════════════════════════════════

// ── pallindrome: two-pointer palindrome attempt ────────────────────────────
//   1) hardcoded string "abca" lo
//   2) i=0, j=length-1 se two pointers set karo
//   3) while i<j — match pe i++, j--; mismatch pe pop_back
//   4) bool return expected hai par code incomplete hai
bool pallindrome() {
    string str = "abca";
    int i=0;
    int j= str.length() - 1; // end pointer
    while(i<j) {
        if(str[i] == str[j]) {
            i++;   // aage badho
            j--;   // peeche badho
        }
        else if(str[i] != str[j]){
            str.pop_back(); // mismatch handle — demo only
        }
    }
    
}

// ── main: pallindrome result print ─────────────────────────────────────────
//   1) pallindrome() call karo
//   2) bool answer cout karo
int main() {
    bool ans = pallindrome();
    cout<< ans<< endl;
}
