/*
 * ============================================================================
 * TOPIC    : Binary Search
 * FILE     : k_closest_elements.cpp
 * PROBLEM  : K Closest Elements
 * LEETCODE : 658 — Find K Closest Elements
 * ABOUT    : Binary search templates and classic interview problems
 * APPROACH : Binary search on sorted array or on answer.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;


/*
 * closestpairs()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : vector<int>& nums, int& k, int& target
 * Returns : void
 */
void closestpairs(vector<int>& nums, int& k, int& target){
    int l=0, h= nums.size()-1;
    while(h-l >=k){
        if(abs(nums[l]-target)> abs(nums[h]-target)){
            l++;
        }
        else{
            h--;
        }
    }
    for(int i=0; i<k; i++){
        cout<< nums[l]<< endl;
        l++;
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for K Closest Elements
 */
int main(){
    vector<int>nums= {12,16,22,30,35,39,42,45,48,50,53,55,56};
    int k=4;
    int target= 35;
    closestpairs(nums,k,target);

}
