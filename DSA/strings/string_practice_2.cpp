/*
 * ============================================================================
 * TOPIC    : Strings
 * FILE     : string_practice_2.cpp
 * PROBLEM  : String Practice 2
 * ABOUT    : String manipulation with STL
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <string.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// ADJACENT DUPLICATE REMOVE — parameterized version
// ────────────────────────────────────────────────────────────────────────────
// Funda: ans string = stack — same adjacent char aaye to pop
// Input string pass hoti hai, result print hota hai
// ════════════════════════════════════════════════════════════════════════════

// ── removeduplicate: stack-style adjacent pair cancel ──────────────────────
//   1) str1 empty result string, i=0 se traverse
//   2) str1 non-empty aur match? pop_back, warna push
//   3) i++ har step, final str1 print
void removeduplicate(string& str){
    string str1= ""; // result stack
    int i=0;
    while(i!= str.length()){
        if(str1.length()>0){
            if(str[i]!= str1[str1.length()-1]){
                str1.push_back(str[i]); // alag char — add
            }
            else{
                str1.pop_back(); // duplicate pair — cancel
            }
        }
        else{
            str1.push_back(str[i]); // pehla char
        }
        i++;    
    }
    cout<< str1<< endl;
}

// ── main: sample "abbaca" pe test ───────────────────────────────────────────
//   1) str set karo, removeduplicate call
int main(){
    string str= "abbaca";
    removeduplicate(str);

}
