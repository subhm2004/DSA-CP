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


/*
 * inplacemerging()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : vector<int> &arr, int& s, int& e
 * Returns : void
 */
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
            return;
         }
         gap= (gap/2)+ (gap%2);   
    }
}


/*
 * mergesort()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : vector<int> &arr, int s, int e
 * Returns : void
 */
void mergesort(vector<int> &arr, int s, int e){
    if(s>=e){
        return;
    }
    int mid= s+(e-s)/2;
    mergesort(arr,s,mid);
    mergesort(arr,mid+1,e);
    inplacemerging(arr,s,e);
}


/*
 * main()
 * Purpose : Entry point — demo/test for Shell Sort Gap Method
 */
int main(){
    vector<int>arr{1,2,8,9,12,13,3,4,7,10};
    int s=0, e= arr.size()-1;
    mergesort(arr,s,e);
    cout<< "Array after in place merging is"<< endl;
    // Iterate over all elements
    for(int i=0; i< arr.size(); i++){
        cout<< arr[i]<< " ";
    }
}
