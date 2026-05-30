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


/*
 * removekdup()
 * Purpose : Standard DSA solution for this problem.
 * Params  : string& str, int& k
 * Returns : string
 */
string removekdup(string& str, int& k){
    string ans= "";
    int i=0;
    while(i!= str.length()){
        if(ans.length()-k+1 > 0){
            for(int j=k-1; j>0;){
                if(str[i]== ans[ans.length()-j]){
                    j--;
                }
                ans.erase(ans.length()- k+1, 2);
            }
        }
        else{
            ans.push_back(str[i]);
        }
    }
    return ans;
}


/*
 * main()
 * Purpose : Entry point — demo/test for Remove K Duplicates
 */
int main(){
    string str= "deeedbbcccbdaa";
    int k= 3;
    string f= removekdup(str,k);
    cout<< f<< endl;


}
