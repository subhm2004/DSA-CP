/*
 * ============================================================================
 * TOPIC    : Binary Search
 * FILE     : painter_partition.cpp
 * PROBLEM  : Painter Partition
 * LEETCODE : 410 — Split Array Largest Sum
 * ABOUT    : Binary search templates and classic interview problems
 * APPROACH : Binary search on sorted array or on answer.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <numeric>
using namespace std;


/*
 * ispossiblesln()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int *arr, int& size, int& k, int mid
 * Returns : bool
 */
bool ispossiblesln(int *arr, int& size, int& k, int mid){
    int paintercount= 1;
    int boardlenalloc=0;
    // Iterate over all elements
    for(int i=0; i<size; i++){
        if(boardlenalloc+ arr[i]<= mid){
            boardlenalloc+= arr[i];
        }
        else {
            paintercount++;
            if(paintercount> k || arr[i]> mid){
                return false;
            }
            else {
                boardlenalloc=arr[i];
            }
        }
    }
}


/*
 * mintime()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int *arr, int& size, int& k
 * Returns : int
 */
int mintime(int *arr, int& size, int& k){
    int s=0;
    int e= accumulate(arr,arr+size, 0);
    int mid= s+(e-s)/2;
    int ans= -1;
    while(s<=e){
        if(ispossiblesln(arr,size,k,mid)){
            ans= mid;
            e= mid-1;
        }
        else {
            s= mid+1;
        }
        mid= s+(e-s)/2;
    }
    return ans;
}


/*
 * main()
 * Purpose : Entry point — demo/test for Painter Partition
 */
int main(){
    int arr[]= {5,10,30,20,15};
    int size= 5; // number of boards= length of array
    int k= 3;
    int ans= mintime(arr,size,k);
    cout<< ans<< endl;

}
