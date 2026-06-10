/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : shell_sort_gap_method.cpp
 * PROBLEM  : Shell Sort Gap Method
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// IN-PLACE MERGE SORT — Gap method se merge (Shell sort inspired)
// ────────────────────────────────────────────────────────────────────────────
// Gap se subarrays compare — galat order pe swap
// mergesort divide karta hai, inplacemerging gap se merge
// Gap half hota jata hai jab tak 1 na ho jaye
// ════════════════════════════════════════════════════════════════════════════

// ── inplacemerging: gap se adjacent pairs compare/swap ──────────────────────
//   1) gap = (e+1)/2 + (e+1)%2 — shuruati gap
//   2) i aur j=i+gap — compare, swap if needed
//   3) gap half karo jab tak gap>=1
void inplacemerging(vector<int> &arr, int& s, int& e){
    int gap= (e+1)/2 +(e+1)%2;
    while(gap>=1){
         int i=0;
         int j=i+gap;
         while(j<= e){
            if(arr[i]> arr[j]){
            swap(arr[i], arr[j]);
            i++;
            j++;
            }
            else{
            i++;
            j++;
            }
         }
         if(gap==1){
            return;  // final pass complete
         }
         gap= (gap/2)+ (gap%2);   // gap reduce   
    }
}

// ── mergesort: divide + in-place gap merge ──────────────────────────────────
//   1) s>=e -> base case
//   2) mid pe divide, dono halves sort
//   3) inplacemerging se merge
void mergesort(vector<int> &arr, int s, int e){
    if(s>=e){
        return;
    }
    int mid= s+(e-s)/2;
    mergesort(arr,s,mid);
    mergesort(arr,mid+1,e);
    inplacemerging(arr,s,e);
}

// ── main: in-place merge sort demo ──────────────────────────────────────────
int main(){
    vector<int>arr{1,2,8,9,12,13,3,4,7,10};
    int s=0, e= arr.size()-1;
    mergesort(arr,s,e);
    cout<< "Array after in place merging is"<< endl;
    for(int i=0; i< arr.size(); i++){
        cout<< arr[i]<< " ";
    }
}
