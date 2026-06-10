/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : permutations_of_string.cpp
 * PROBLEM  : Permutations Of String
 * LEETCODE : 46 — Permutations
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Fix one char; recurse on remaining positions.
 * COMPLEX  : Time: O(n!)  |  Space: O(n)
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// STRING PERMUTATIONS — Saare arrangements generate
// ────────────────────────────────────────────────────────────────────────────
// Index fix karo — har j>=index se swap karke recurse
// Wapas aate waqt swap undo — original string restore
// n! permutations — backtracking with swap trick
// ════════════════════════════════════════════════════════════════════════════

// ── permutations: index se saari permutations ────────────────────────────────
//   1) index>=length -> current string print (ek permutation)
//   2) j=index se end — swap(index,j), recurse, swap back
//   3) har position pe har possible char fix karo
void permutations(string &str, int index){
    if(index>= str.length()){
        cout<< str << endl;
        return;
    }
    for(int j=index; j<str.length();j++){
        swap(str[index],str[j]);       // j ko index pe fix karo
        permutations(str,index+1);    // baaki permute
        swap(str[index],str[j]);        // undo — original restore
    }
}

// ── main: "abcd" ke permutations ────────────────────────────────────────────
int main(){
    string str= "abcd";
    int index= 0;
    permutations(str,index);
}
