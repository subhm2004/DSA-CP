/*
 * ============================================================================
 * TOPIC    : Binary Search
 * FILE     : pivot_element.cpp
 * PROBLEM  : Pivot Element
 * LEETCODE : 33 — Search in Rotated Sorted Array
 * ABOUT    : Binary search templates and classic interview problems
 * APPROACH : Binary search on sorted array or on answer.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;


/*
 * pivotindex()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : vector<int>&nums, int& n
 * Returns : int
 */
int pivotindex(vector<int>&nums, int& n) {
    int s=0, e= n-1;
    int mid= s+(e-s)/2;
    while(s<=e) {
        if(s==e) {
            return s;
        }
        else if(mid+1<n && nums[mid]> nums[mid+1] ) {
            return mid;
        }
        else if(mid-1>=0 && nums[mid]< nums[mid-1]){
            return mid-1;
        }
        else if(nums[mid]< nums[s]){
            e= mid-1;
        }
        else {
            s= mid+1;
        }
        mid= s+(e-s)/2;
    }
    return -1;
}


/*
 * binarysearch()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : vector<int>& nums, int s, int e, int& target
 * Returns : int
 */
int binarysearch(vector<int>& nums, int s, int e, int& target) {
    
    int mid= s+(e-s)/2;
    while(s<=e){
        if(nums[mid]== target) {
            return mid;
        }
        else if(nums[mid]> target){
            e= mid-1;
        }
        else {
            s= mid+1;
        }
        mid= s+(e-s)/2;
    }
}


/*
 * search()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : vector<int>& nums, int& n, int& target
 * Returns : int
 */
int search(vector<int>& nums, int& n, int& target) {
     int s=0, e = n-1;
     int index = pivotindex(nums, n);
     int ans=-1;
     if(target<= nums[index] && target>= nums[s]){
         ans= binarysearch(nums, 0, index, target);
     }
     else {
         ans= binarysearch(nums, index+1, n-1, target);
     }
     return ans;
}



/*
 * main()
 * Purpose : Entry point — demo/test for Pivot Element
 */
int main() {
    vector<int>nums;
    nums.push_back(12);
    nums.push_back(14);
    nums.push_back(16);
    nums.push_back(2);
    nums.push_back(4);
    nums.push_back(6);
    nums.push_back(8);
    nums.push_back(10);
    int n= nums.size();
    int target= 14;
    int f= search(nums, n , target);
    cout<< f<< endl;
}
