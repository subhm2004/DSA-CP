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


/*
 * generateparenthesis()
 * Purpose : Backtrack valid '(' ')' strings.
 * Params  : string output, int& n, int open, int close, vector<string>& ans
 * Returns : void
 */
void generateparenthesis(string output, int& n, int open, int close, vector<string>& ans){
    if(open==0 && close==0){
        ans.push_back(output);
        // Iterate over all elements
        for(int i=0; i<ans.size(); i++){
            cout<< ans[i]<< endl;
        }
        return;
    }
    if(open> 0){
        output.push_back('(');
        generateparenthesis(output,n,open-1, close, ans);
        output.pop_back();    
    }
    if(close> open){
        output.push_back(')');
        generateparenthesis(output,n,open, close-1, ans);
        output.pop_back();    
    }
}
    


/*
 * main()
 * Purpose : Entry point — demo/test for Generate Parenthesis
 */
int main(){
    int n=3;
    int open=-n;
    int close= n;
    string output= "";
    vector<string>ans;
    generateparenthesis(output,n,open,close,ans);
    // Iterate over all elements
    for(int i=0; i<ans.size(); i++){
        cout<< ans[i]<< endl;
    }


    
    
}
