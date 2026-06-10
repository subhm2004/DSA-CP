/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : in_place_sort.cpp
 * PROBLEM  : In Place Sort
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// IN-PLACE MERGE — Do sorted arrays ko bina extra space merge
// ────────────────────────────────────────────────────────────────────────────
// arr1 aur arr2 sorted — arr1[i]>arr2[j] pe swap, arr2 sort
// partitioning: quick sort jaisa pivot placement
// Merge sort ka in-place variant practice
// ════════════════════════════════════════════════════════════════════════════

// ── partitioning: pivot ko sahi jagah pe rakho ──────────────────────────────
//   1) pivot = arr2[s], count chhote elements
//   2) swap se pivot sahi index pe
//   3) i,j se partition — galat elements swap
void partitioning(vector<int> &arr2, int s,int e){
    int pivotindex= s;
    int pivotelement= arr2[s];
    int count=0;
    for(int i=s+1; i<=e; i++){
        if(arr2[i]< arr2[s]){
            count++;
        }
    }
    int rightindex= s+count;
    swap(arr2[rightindex], arr2[pivotindex]);
    pivotindex= rightindex;
    int i=s, j= e;
    while(i< pivotindex && j> pivotindex){
        while(arr2[i]< arr2[pivotindex]){
            i++;
        }
        while (arr2[j]> arr2[pivotindex]){
            j--;
        }
        if(i< pivotindex && j> pivotindex){
            swap(arr2[i], arr2[j]);
        }
    }
    cout<< "second array is\n";
    for(int i=0; i< arr2.size(); i++){
        cout<< arr2[i] << " ";

    }
    cout<< endl;
}

// ── inplacesorting: arr1 aur arr2 ko merge karo in-place ────────────────────
//   1) arr1[i]<=arr2[j] -> i++ (theek order)
//   2) warna swap aur arr2 sort karo
void inplacesorting(vector<int>&arr1, vector<int>& arr2){
    int i=0, j=0;
    int s=0, e= arr2.size()-1;
    while(i<arr1.size()){
        if(arr1[i]<= arr2[j]){
            i++;
        }
        else {
            swap(arr1[i], arr2[j]);  // galat order — swap
            sort(arr2.begin(), arr2.end());  // arr2 dubara sorted
        }
    }
}

// ── main: in-place merge demo ───────────────────────────────────────────────
int main(){
    vector<int>arr1{1,2,8,9,12,13};
    vector<int>arr2{3,4,7,10};
    inplacesorting(arr1,arr2);
    for(int i=0; i< arr1.size(); i++){
        cout<< arr1[i]<< " ";
    }
    cout<< endl;
    for(int i=0; i< arr2.size(); i++){
        cout<< arr2[i]<< " ";
    }
}
