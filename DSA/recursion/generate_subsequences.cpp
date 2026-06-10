/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : generate_subsequences.cpp
 * PROBLEM  : Generate Subsequences
 * LEETCODE : 78 — Subsets / Subsequence variant
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Include/exclude each element — recursive branching.
 * COMPLEX  : Time: O(2^n)  |  Space: O(n)
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// GENERATE SUBSEQUENCES — String ke saare subsequences
// ────────────────────────────────────────────────────────────────────────────
// Har index pe: exclude (ans same) ya include (ans me char add)
// subsequence2: backtracking style — push, recurse, pop
// Order preserve hota hai — subsequence me relative order same
// ════════════════════════════════════════════════════════════════════════════

// ── subsequence: include/exclude without backtrack pop ───────────────────────
//   1) i==str.length() -> ans print, return
//   2) exclude — subsequence(str, ans, i+1)
//   3) include — ans.push_back, subsequence(str, ans, i+1)
void subsequence(string str, string ans, int i ) {
    if(i== str.length()) {
        cout<< ans<< " ";
        return;
    }
     subsequence(str, ans, i+1);  // exclude str[i]

    ans.push_back(str[i]);
    subsequence(str, ans, i+1);  // include str[i]
    
}

// ── subsequence2: backtracking — push/pop style ───────────────────────────────
//   1) base — ans print
//   2) include branch — push, recurse, pop (undo)
//   3) exclude branch — seedha i+1
void subsequence2(string str, string ans, int i){
    if(i>= str.length()){
        cout<< ans<< endl;
        return;
    }
    char ch= str[i];
    ans.push_back(ch);
    subsequence2(str,ans,i+1);  // include
    ans.pop_back();             // backtrack — undo include
    subsequence2(str,ans,i+1);  // exclude
}

// ── main: subsequences of "abc" print ───────────────────────────────────────
int main() {
    string str= "abc";
    string ans= "";
    int i=0;
    subsequence2(str,ans, i);

}
