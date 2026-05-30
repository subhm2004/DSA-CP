/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : maximum_ones.cpp
 * PROBLEM  : Maximum Ones
 * LEETCODE : 485 — Max Consecutive Ones
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <limits.h>
#include <vector>
using namespace std;


/*
 * maximumones()
 * Purpose : Iterate with two pointers / sliding window / prefix sum.
 * Params  : int arr[][3], int&m, int& n, vector<int>&ans
 * Returns : void
 */
void maximumones(int arr[][3], int&m , int& n, vector<int>&ans) {
    int onecount = INT_MIN;
    int row = -1;
    for(int i=0; i<m; i++) {
        int count = 0;
        for(int j=0; j<n; j++) {
            if(arr[i][j] ==1){
                count++;
            }
        }
        if(onecount< count) {
            row = i;
        }
        if(onecount < count){
            onecount = count;
        }    
    }
    ans.push_back(onecount);
    ans.push_back(row);
}


/*
 * main()
 * Purpose : Entry point — demo/test for Maximum Ones
 */
int main() {
    int arr[][3] = {{1,0,0},{0,0,0}, {1,1,1}, {0,1,1}};
    int m= 4, n=3;
    vector<int>ans;
    
    maximumones(arr , m,n,ans);
    // Iterate over all elements
    for(int i=0; i< ans.size(); i++) {
        cout<< ans[i]<< " ";
    }
}
