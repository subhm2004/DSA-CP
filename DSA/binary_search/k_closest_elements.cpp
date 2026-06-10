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



// ════════════════════════════════════════════════════════════════════════════
// K CLOSEST ELEMENTS — Window shrink (Leetcode 658)
// ────────────────────────────────────────────────────────────────────────────
// Sorted array — k elements ka window jiska target se distance min
// h-l>=k tab tak shrink — door wala end hatao
// Two pointer window technique
// ════════════════════════════════════════════════════════════════════════════


// ── closestpairs: k closest window ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
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



// ── main: demo ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int main(){
    vector<int>nums= {12,16,22,30,35,39,42,45,48,50,53,55,56};
    int k=4;
    int target= 35;
    closestpairs(nums,k,target);

}
