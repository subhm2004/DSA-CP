/*
 * ============================================================================
 * TOPIC    : Binary Search
 * FILE     : binary_search_practice.cpp
 * PROBLEM  : Binary Search Practice
 * ABOUT    : Binary search templates and classic interview problems
 * APPROACH : Binary search — eliminate half the search space each step.
 * COMPLEX  : Time: O(log n)  |  Space: O(1)
 * ============================================================================
 */

 #include <iostream>
#include <algorithm>
 #include <set>
 using namespace std;
    





/*
 * firstocc()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int *arr, int& size, int& target
 * Returns : int
 */
int firstocc(int *arr, int& size, int& target){
    int s=0, e= size-1;
    int mid= s+(e-s)/2;
    int ans=-1;
    while(s<=e){
        if(arr[mid]== target){
            ans= mid;
            e= mid-1;
        }
        else if(arr[mid]> target){
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
 * lastocc()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int *arr, int& size, int& target
 * Returns : int
 */
int lastocc(int *arr, int& size, int& target){
    int s=0, e= size-1;
    int mid= s+(e-s)/2;
    int ans= -1;
    while(s<=e){
        if(arr[mid]== target){
            ans= mid;
            s= mid+1;    
        }
        else if(arr[mid]> target){
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
 * missingelement()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int *arr, int& size
 * Returns : int
 */
int missingelement(int *arr, int& size){
    int s=0, e= size-1;
    int mid= s+(e-s)/2;
    while(s<=e){
        if(arr[mid]== mid+1){

            s= mid+1;
        }
        else if(arr[mid]== mid+2){
            if(s==e){
                return arr[mid]-1;
            }
            e= mid;
        }
        mid= s+(e-s)/2;
    }
}


/*
 * peakelement()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int *arr, int& size
 * Returns : int
 */
int peakelement(int *arr, int& size){
    int s=0, e= size-1;
    int mid= s+(e-s)/2;
    while(s<e){
    if(arr[mid+1]>arr[mid] ){
        s= mid+1;
    }
    else if(arr[mid+1]< arr[mid]){
        e= mid;
    }
    mid= s+(e-s)/2;
    }
    return mid;
}


/*
 * pivotindex()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int* arr, int& size
 * Returns : int
 */
int pivotindex(int* arr, int& size){
    int s=0, e= size-1;
    int mid= s+(e-s)/2;
    while(s<=e){
        if(s==e){
            return s;
        }
        if(arr[mid]> arr[mid+1] && mid+1< size){
            return mid;
        }
        else if(arr[mid]< arr[mid-1] && mid-1>=0){
            return mid-1;
        }
        else if(arr[mid]< arr[s]){
            e= mid-1;
        }
        else {
            s= mid+1;
        }
        mid= s+(e-s)/2;
    }
}


/*
 * search()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int *arr, int& size, int& target
 * Returns : int
 */
int search(int *arr, int& size, int& target){
    int s=0, e= size-1;
    int index= pivotindex(arr,size);
    if(target>= arr[s] && target<= arr[index]){
        return binarysearch(arr,size,s,index,target);
    }
    else if(target>= arr[index+1] && target< arr[size-1]){
        return binarysearch(arr,size,index+1,size-1, target);
    }
}


/*
 * sqrt()
 * Purpose : Binary search — eliminate half the search space each step.
 * Params  : int& n
 * Returns : int
 */
int sqrt(int& n){
    int s=0, e= n;
    int mid= s+(e-s)/2;
    int ans= -1;
    while(s<=e){
        if(mid*mid > n){
            e= mid-1;
        }
        else {
            ans = mid;
            s= mid+1;
        }
        mid= s+(e-s)/2;
    }
    return ans;
}


/*
 * quotient()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int& dividend, int& divisor
 * Returns : int
 */
int quotient(int& dividend, int& divisor){
    int s=0, e= dividend;
    int mid= s+(e-s)/2;
    int ans= -1;
    while(s<=e){
        if(mid*divisor> dividend){
            e= mid-1;
        }
        else {
            ans= mid;
            s= mid+1;
        }
        mid= s+(e-s)/2;
    }
    return ans;
}


/*
 * nearlysorted()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int *arr, int& size, int& target
 * Returns : int
 */
int nearlysorted(int *arr, int& size, int& target){
    int s=0, e= size-1;
    int mid= s+(e-s)/2;
    while(s<=e){
        if(arr[mid]== target){
            return mid;
        }
        else if(arr[mid+1]== target){
            return mid+1;
        }
        else if(arr[mid-1]== target){
            return mid-1;
        }
        else if(arr[mid]> target){
            e= mid-2;
        }
        else {
            s= mid+2;
        }
        mid= s+(e-s)/2;
    }
    return mid;
}


/*
 * kdiffpairs()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int *arr, int& size, int& k
 * Returns : int
 */
int kdiffpairs(int *arr, int& size, int& k){
    sort(arr,arr+size);
    int i=0;
    int j= i+1;
    set<pair<int,int>>ans;
    while(i<=j){
        if(arr[j]-arr[i]==k){
            ans.insert(arr[i], arr[j]);
            i++;
            j++;
        }
        else if(arr[j]- arr[i]> k){
            i++;
        }
        else {
            j++;
        }
        if (i==j){
            j++;
        }
    }
    return ans.size();
}


/*
 * binarysearch()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int *arr, int& size, int s, int e, int target
 * Returns : int
 */
int binarysearch(int *arr, int& size, int s, int e, int target){
    int mid= s+(e-s)/2;
    while(s<=e){
        if(arr[mid]== target){
            return mid;
        }
        else if(arr[mid]> target){
            e= mid-1;
        }
        else {
            s= mid+1;
        }
        mid= s+(e-s)/2;
    }
    return -1;
}


/*
 * findpairs()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int *arr, int& size, int& k
 * Returns : int
 */
int findpairs(int *arr, int& size, int& k){
    set<pair<int,int>>ans;
    // Iterate over all elements
    for(int i=0; i<size-1; i++){
        if(binarysearch(arr, size, i+1, size-1, arr[i]+k)!=-1){
            ans.insert({arr[i], arr[i]+k});
        }
    }
    return ans.size();
}


/*
 * main()
 * Purpose : Entry point — demo/test for Binary Search Practice
 */
int main(){

    int n=66;
    int arr[]= {3,1,4,1,5};
    int size= 5;
    int k=2;
    int target= 50;

}
