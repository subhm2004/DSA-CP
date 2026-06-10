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
    






// ════════════════════════════════════════════════════════════════════════════
// BINARY SEARCH PRACTICE — Saare BS patterns ek file me
// ────────────────────────────────────────────────────────────────────────────
// First/last occ, missing, peak, pivot, sqrt, quotient, k-diff
// Interview prep — har pattern alag function
// ════════════════════════════════════════════════════════════════════════════


// ── firstocc: first occ ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
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



// ── lastocc: last occ ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
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



// ── missingelement: missing ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
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



// ── peakelement: peak ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
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



// ── pivotindex: pivot ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
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



// ── search: rotated search ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
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



// ── sqrt: sqrt ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
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



// ── quotient: quotient ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
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



// ── nearlysorted: nearly sorted ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
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



// ── kdiffpairs: k-diff ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
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



// ── binarysearch: BS ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
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



// ── findpairs: pairs ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
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



// ── main: demo ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int main(){

    int n=66;
    int arr[]= {3,1,4,1,5};
    int size= 5;
    int k=2;
    int target= 50;

}
