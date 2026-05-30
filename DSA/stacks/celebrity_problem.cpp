/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : celebrity_problem.cpp
 * PROBLEM  : Celebrity Problem
 * LEETCODE : 277 — Find the Celebrity
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : Eliminate non-celebrity in O(n) comparisons.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <stack>
using namespace std;


/*
 * celebrityperson()
 * Purpose : Eliminate non-celebrity in O(n) comparisons.
 * Params  : int arr[][3], int&n
 * Returns : int
 */
int celebrityperson(int arr[][3], int&n){
    stack<int>st;
    for(int i=0; i< n; i++){
        st.push(i);
    }
    while(st.size()!=1){
        int a= st.top();
        st.pop();
        int b= st.top();
        st.pop();
        if(arr[a][b]){
            st.push(b);
        }
        if(arr[b][a]) {
            st.push(a);
        }
    }
    int i= st.top();
    int j=0;
    while( j< n){
        if(arr[i][j]== 0 && (arr[j][i]== 1 && arr[i][i])==0){
            j++;  
        }
        else {
            return -1;
        }
    } 
    return i;  
}


/*
 * main()
 * Purpose : Entry point — demo/test for Celebrity Problem
 */
int main() {
    int n=3;
    int arr[3][3]= {
        {0,1,0},
        {0,0,0},
        {0,1,0},
    };
    
    int ans= celebrityperson(arr,n);
    cout<< ans << endl;
    
}
