/*
 * ============================================================================
 * TOPIC    : Strings
 * FILE     : remove_occurrences.cpp
 * PROBLEM  : Remove Occurrences
 * LEETCODE : 1910 — Remove All Occurrences of a Substring
 * ABOUT    : String manipulation with STL
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <string>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// REMOVE ALL SUBSTRING OCCURRENCES — find + erase loop
// ────────────────────────────────────────────────────────────────────────────
// Funda: str.find(part) se position lo — nahi mila? npos pe stop
// Mil gaya to erase karo aur dubara find — jab tak sab hat jayein
// LeetCode 1910 — "abc" ko poori string se hatao
// ════════════════════════════════════════════════════════════════════════════

// ── removeoccur: substring ko repeatedly erase karo ────────────────────────
//   1) str aur part hardcode — "daabcbaabcbc", "abc"
//   2) find se pehli occurrence ki position lo
//   3) while pos != npos — erase(pos, part.length())
//   4) dubara find, final str return
string removeoccur() {
    string str = "daabcbaabcbc";
    string part = "abc";
    int pos = str.find(part); // pehli match ki jagah
    while(pos != string::npos) {
        str.erase(pos, part.length()); // substring hatao
        pos = str.find(part); // agli occurrence dhoondo
    }
    return str;
}

// ── main: cleaned string print ─────────────────────────────────────────────
//   1) removeoccur() call, result cout
int main() {
   string ans= removeoccur();
   cout<< ans<< endl;

}
