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


/*
 * partitioning()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : vector<int> &arr2, int s, int e
 * Returns : void
 */
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
    // Iterate over all elements
    for(int i=0; i< arr2.size(); i++){
        cout<< arr2[i] << " ";

    }
    cout<< endl;
}


/*
 * inplacesorting()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : vector<int>&arr1, vector<int>& arr2
 * Returns : void
 */
void inplacesorting(vector<int>&arr1, vector<int>& arr2){
    int i=0, j=0;
    int s=0, e= arr2.size()-1;
    while(i<arr1.size()){
        if(arr1[i]<= arr2[j]){
            i++;
        }
        else {
            swap(arr1[i], arr2[j]);
            sort(arr2.begin(), arr2.end());
        }
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for In Place Sort
 */
int main(){
    vector<int>arr1{1,2,8,9,12,13};
    vector<int>arr2{3,4,7,10};
    inplacesorting(arr1,arr2);
    // Iterate over all elements
    for(int i=0; i< arr1.size(); i++){
        cout<< arr1[i]<< " ";
    }
    cout<< endl;
    // Iterate over all elements
    for(int i=0; i< arr2.size(); i++){
        cout<< arr2[i]<< " ";
    }
}
