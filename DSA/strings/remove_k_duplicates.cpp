/*
 * ============================================================================
 * TOPIC    : Strings
 * FILE     : remove_k_duplicates.cpp
 * PROBLEM  : Remove K Duplicates
 * LEETCODE : 1209 — Remove All Adjacent Duplicates in String II
 * ABOUT    : String manipulation with STL
 * APPROACH : Hash set or sorting to find duplicates.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <string.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// REMOVE K ADJACENT DUPLICATES — jab k same chars lagatar aayein to hatao
// ────────────────────────────────────────────────────────────────────────────
// Funda: ans string me build karo — k consecutive match pe block erase
// LeetCode 1209 — k=3 pe "ddd" jaisi triples remove
// ════════════════════════════════════════════════════════════════════════════

// ── removekdup: k-adjacent duplicate block erase ───────────────────────────
//   1) ans empty, i se str traverse karo
//   2) ans me k-1 chars match? to poora block erase karo
//   3) warna str[i] ko ans me push karo
//   4) final ans return — cleaned string
string removekdup(string& str, int& k){
    string ans= "";
    int i=0;
    while(i!= str.length()){
        if(ans.length()-k+1 > 0){
            for(int j=k-1; j>0;){
                if(str[i]== ans[ans.length()-j]){
                    j--; // pichle k-1 chars match check
                }
                ans.erase(ans.length()- k+1, 2); // k-block hatao
            }
        }
        else{
            ans.push_back(str[i]); // abhi k-block nahi bana
        }
    }
    return ans;
}

// ── main: sample string pe k=3 test ────────────────────────────────────────
//   1) str aur k set karo, removekdup call
//   2) result print karo
int main(){
    string str= "deeedbbcccbdaa";
    int k= 3;
    string f= removekdup(str,k);
    cout<< f<< endl;


}
