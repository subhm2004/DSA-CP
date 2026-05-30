/*
 * ============================================================================
 * TOPIC    : Binary Search
 * FILE     : odd_occurrence_binary_search.cpp
 * PROBLEM  : Odd Occurrence Binary Search
 * LEETCODE : 540 — Single Element in a Sorted Array
 * ABOUT    : Binary search templates and classic interview problems
 * APPROACH : Binary search — eliminate half the search space each step.
 * COMPLEX  : Time: O(log n)  |  Space: O(1)
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;


/*
 * oddoccurence()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : vector<int>& arr
 * Returns : int
 */
int oddoccurence(vector<int>& arr) {
    int s=0, e= arr.size()-1;
    int mid= s+(e-s)/2;
    while(s<=e) {
        if(s==e){
            return s;
        }
        if(mid&1){ //fast method to check odd/even number
            if(mid-1>0 && arr[mid]== arr[mid-1]){
                s= mid+1;
            }
            else {
                e= mid-1;
            }
        }
        else {
            if(mid+1< arr.size() && arr[mid]== arr[mid+1]){
                s= mid+2;
            }
            else{
                e= mid;
            }
        }
        mid= s+(e-s)/2;
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Odd Occurrence Binary Search
 */
int main(){
    vector<int>arr= {10,10,5,5,2,2,5,5,20,20,10,10,11,11,1};
    int ans= oddoccurence(arr);
    cout<< ans<< endl;
}
