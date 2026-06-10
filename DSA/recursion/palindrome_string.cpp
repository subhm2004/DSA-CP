/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : palindrome_string.cpp
 * PROBLEM  : Palindrome String
 * LEETCODE : 125 — Valid Palindrome
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Two pointers from both ends or recursive check.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// PALINDROME CHECK (Recursion) — Dono ends se compare
// ────────────────────────────────────────────────────────────────────────────
// str[i]==str[j] -> andar jao (i+1, j-1)
// Mismatch -> false; i>j -> true (saare match)
// Two-pointer recursion — O(n) time
// ════════════════════════════════════════════════════════════════════════════

// ── checkpallindrome: string palindrome hai ya nahi ───────────────────────
//   1) i>j -> saare chars match, return true
//   2) str[i]==str[j] -> recursive check andar
//   3) warna return false — mismatch mil gaya
bool checkpallindrome(string& str, int i, int j) {
    if(i>j) {
        return true;  // poora string check ho gaya
    }
    if(str[i]== str[j]) {
        checkpallindrome(str, i+1, j-1);  // andar wale chars check
    }
    else {
        return false;  // ends match nahi — palindrome nahi
    }
}

// ── main: palindrome check demo ────────────────────────────────────────────
int main() {
    string str = "aman";
    int i=0, j= str.length() -1;
    bool ans = checkpallindrome(str, i, j);
    cout<< ans<< endl;

}
