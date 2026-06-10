/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : sort_colors.cpp
 * PROBLEM  : Sort Colors
 * LEETCODE : 75 — Sort Colors
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Three pointers — Dutch National Flag (0,1,2).
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// SORT COLORS (0,1,2) — teen approaches ek file me
// ────────────────────────────────────────────────────────────────────────────
// sortcolors(): count karke push — O(n) extra space
// sortcolors2(): insertion sort — O(n²)
// sortcolors3(): Dutch National Flag — three pointers, O(n) O(1) ✓
// COMPLEX: DNF O(n) time O(1) space — optimal
// ════════════════════════════════════════════════════════════════════════════

// ── sortcolors: count 0s, 1s, 2s karke naya array banao ───────────────────
//   1) teen loops se 0, 1, 2 push_back
//   2) brute count approach — extra space use hota hai
void sortcolors(vector<int>&nums, int& n) {
    for(int i=0; i<n; i++) {
        nums.push_back(0);
    }
    for(int i=0; i<n; i++) {
        nums.push_back(1);
    }
    for(int i=0; i<n; i++) {
        nums.push_back(2);
    }    
}



// ── printarray: vector print karo ──────────────────────────────────────────
//   1) har element space-separated print
void printarray(vector<int>nums) {
    for(int i=0;i< nums.size(); i++) {
        cout<< nums[i]<< "  ";
    }
}


// ── sortcolors2: insertion sort se 0,1,2 sort ────────────────────────────────
//   1) i=1 se — current value uthao
//   2) j=i-1 se 0 tak — bade elements right shift
//   3) correct position pe place karo
void sortcolors2(vector<int>&nums) {
    for(int i=1; i<nums.size(); i++) {
        int value = nums[i];
        for(int j= i-1; j>=0; j--) {
            if(nums[j]> value) {
                swap(nums[j], nums[j+1]);
            }
        }
    }
}


// ── sortcolors3: Dutch National Flag — optimal in-place ────────────────────
//   1) j=low (0s region), i=mid (current), k=high (2s region)
//   2) nums[i]==0 -> swap with j, j++ i++
//   3) nums[i]==2 -> swap with k, k-- (i nahi badhao — swapped element check)
//   4) nums[i]==1 -> sirf i++
void sortcolors3(vector<int>&nums) {
    int n= nums.size();
    int j=0, k= n-1;
    int i=0;

        while(i<k) {
        if(nums[i] == 0) {
            swap(nums[i], nums[j]);
            j++;
            i++;
        }
        else if(nums[i] == 2) {
            swap(nums[i], nums[k]);
            k--;
        }
        else{
            i++;
        }
    }
}


// ── main: DNF approach demo ────────────────────────────────────────────────
//   1) unsorted 0,1,2 vector
//   2) sortcolors3() call — in-place sort
//   3) result print
int main() {
    vector<int> nums{1,2,0,1,0,2,2,1,0};
    sortcolors3(nums);
    printarray(nums);
}
