/*
 * ============================================================================
 * TOPIC    : Basics
 * FILE     : basic_dsa.cpp
 * PROBLEM  : Basic Dsa
 * ABOUT    : Fundamental DSA — loops, sorting, strings, character operations
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// SEARCH IN NEARLY SORTED ARRAY — modified binary search
// ────────────────────────────────────────────────────────────────────────────
// Funda: nearly sorted = har element apni sorted position se ±1 off ho sakta
// BS me mid, mid±1 teen jagah check — target mila to return
// COMPLEX: Time O(log n)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── nearlysorted: nearly sorted array me target dhundho ───────────────────
//   1) i,j window me BS — mid = i+(j-i)/2
//   2) arr[mid], arr[mid±1] teeno pe target check
//   3) arr[mid]>target -> left (j=mid-2), warna right (i=mid+2)
//   4) nahi mila to -1
int nearlysorted(vector<int>arr,  int target) {
    int i=0;
    int j= arr.size() -1;
    int mid= i+(j-i)/2;
    while(i<=j) {
        if(arr[mid]== target) {
            return mid;
        }
        else if(arr[mid+1]== target) {
            return mid+1;
        }
        else if(arr[mid-1]== target) {
            return mid-1;
        }
        else if(arr[mid]> target) {
            j= mid-2;  // nearly sorted — 2 step left
        }
        else {
            i= mid+2;  // nearly sorted — 2 step right
        }
        mid = i+(j-i)/2;
    }
    return -1;
   }
   
   
// ── main: nearly sorted search demo ────────────────────────────────────────
//   1) nearly sorted vector
//   2) target search — index print
   int main() {
    vector<int> arr = {10,3,40,20,50,80,70};
    int target = 70;
    int ans= nearlysorted(arr,target);
    cout<< "index of target element is "<< ans<< endl;
    return 0;
   }
