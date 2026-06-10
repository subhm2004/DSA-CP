/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : generate_parenthesis.cpp
 * PROBLEM  : Generate Parenthesis
 * LEETCODE : 22 — Generate Parentheses
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Backtrack valid '(' ')' strings.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// GENERATE PARENTHESES — n pairs valid brackets
// ────────────────────────────────────────────────────────────────────────────
// open > 0 -> '(' add kar sakte; close > open -> ')' add kar sakte
// Backtrack: push char, recurse, pop (undo)
// Valid tabhi jab har step pe close <= open (implicit via close>open check)
// ════════════════════════════════════════════════════════════════════════════

// ── generateparenthesis: valid n-pair strings generate ────────────────────────
//   1) open==0 && close==0 -> valid string, ans me store
//   2) open>0 -> '(' add, open--, recurse, pop
//   3) close>open -> ')' add, close--, recurse, pop
void generateparenthesis(string output, int& n, int open, int close, vector<string>& ans){
    if(open==0 && close==0){
        ans.push_back(output);
        for(int i=0; i<ans.size(); i++){
            cout<< ans[i]<< endl;
        }
        return;
    }
    if(open> 0){
        output.push_back('(');
        generateparenthesis(output,n,open-1, close, ans);
        output.pop_back();  // backtrack    
    }
    if(close> open){
        output.push_back(')');
        generateparenthesis(output,n,open, close-1, ans);
        output.pop_back();  // backtrack    
    }
}
    

// ── main: n=3 pairs ke valid strings ────────────────────────────────────────
int main(){
    int n=3;
    int open=-n;
    int close= n;
    string output= "";
    vector<string>ans;
    generateparenthesis(output,n,open,close,ans);
    for(int i=0; i<ans.size(); i++){
        cout<< ans[i]<< endl;
    }


    
    
}
