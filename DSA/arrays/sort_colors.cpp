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


/*
 * sortcolors()
 * Purpose : Iterate with two pointers / sliding window / prefix sum.
 * Params  : vector<int>&nums, int& n
 * Returns : void
 */
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



/*
 * printarray()
 * Purpose : Iterate with two pointers / sliding window / prefix sum.
 * Params  : vector<int>nums
 * Returns : void
 */
void printarray(vector<int>nums) {
    // Iterate over all elements
    for(int i=0;i< nums.size(); i++) {
        cout<< nums[i]<< "  ";
    }
}


/*
 * sortcolors2()
 * Purpose : Iterate with two pointers / sliding window / prefix sum.
 * Params  : vector<int>&nums
 * Returns : void
 */
void sortcolors2(vector<int>&nums) {
    // Iterate over all elements
    for(int i=1; i<nums.size(); i++) {
        int value = nums[i];
        for(int j= i-1; j>=0; j--) {
            if(nums[j]> value) {
                swap(nums[j], nums[j+1]);
            }
        }
    }
}


/*
 * sortcolors3()
 * Purpose : Iterate with two pointers / sliding window / prefix sum.
 * Params  : vector<int>&nums
 * Returns : void
 */
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


/*
 * main()
 * Purpose : Entry point — demo/test for Sort Colors
 */
int main() {
    vector<int> nums{1,2,0,1,0,2,2,1,0};
    sortcolors3(nums);
    printarray(nums);
}
