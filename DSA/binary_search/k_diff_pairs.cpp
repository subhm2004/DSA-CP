/*
 * ============================================================================
 * TOPIC    : Binary Search
 * FILE     : k_diff_pairs.cpp
 * PROBLEM  : K Diff Pairs
 * LEETCODE : 532 — K-diff Pairs in an Array
 * ABOUT    : Binary search templates and classic interview problems
 * APPROACH : Binary search on sorted array or on answer.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <algorithm>
#include <set>
using namespace std;


/*
 * findpair()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int* arr, int& k, int& size
 * Returns : int
 */
int findpair(int* arr,int& k, int& size){
    sort(arr, arr+size);
    set<pair<int,int>> ans;
    int i=0, j=i+1;
    while(j<size){
        if(arr[j]-arr[i]==k){
            ans.insert(arr[i],arr[j]);
            i++;
            j++;
        }
        else if(arr[j]-arr[i]> k){
            i++;
        }
        else if(arr[j]-arr[i]< k){
            j++;
        }
        if(i==j){
            j++;
        }
    }
    return ans.size();
}


/*
 * binarysearch()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int *arr, int& size, int s, int x
 * Returns : int
 */
int binarysearch(int *arr, int& size, int s, int x){
    int e= size-1;
    int mid= s+(e-s)/2;
    while(s<=e){
        if(arr[mid]== x){
            return mid;
        }
        else if(arr[mid]> x){
            e= mid-1;
        }
        else {
            s= mid+ 1;
        }
        mid= s+(e-s)/2;
    }
    return -1;    
}


/*
 * findpairs()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int *arr, int& size, int & k
 * Returns : int
 */
int findpairs(int *arr, int& size, int & k){
    sort(arr, arr+size);
    set<pair<int,int>> ans;
    // Iterate over all elements
    for(int i=0; i< size-1; i++){
        if( binarysearch(arr,size,i+1, arr[i]+k)!=-1){
            ans.insert(arr[i], arr[i]+k);
        }
    }
    return ans.size();    
}


/*
 * main()
 * Purpose : Entry point — demo/test for K Diff Pairs
 */
int main(){
    int arr[]= {1,1,3,4,5};
    int size= 5;
    int k=2;
    int f= findpairs(arr,size,k);
    cout<< f<< endl;
}
