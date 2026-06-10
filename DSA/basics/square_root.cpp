/*
 * ============================================================================
 * TOPIC    : Basics
 * FILE     : square_root.cpp
 * PROBLEM  : Square Root
 * ABOUT    : Fundamental DSA — loops, sorting, strings, character operations
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// SQUARE ROOT — binary search on sorted array of squares
// ────────────────────────────────────────────────────────────────────────────
// Funda: arr[i]=i, arr[mid]*arr[mid] vs n compare karo
// mid*mid > n -> left half, < n -> ans=mid right, == n -> return
// COMPLEX: Time O(log n)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── sqrt: BS se integer square root ────────────────────────────────────────
//   1) i=0, j=size-1 — search space 0..10
//   2) mid*mid > n -> j=mid-1 (zyada bada)
//   3) mid*mid < n -> ans=mid, i=mid+1 (aur bada try)
//   4) mid*mid == n -> exact root return
int sqrt(int arr[], int size, int n) {
    int i=0, j=size-1;
    int mid = i+ (j-i)/2;
    int ans=0;
    while(i<=j) {
        if (arr[mid]* arr[mid] > n) {
            j= mid-1;
        }
        else if(arr[mid]* arr[mid] < n) {
            ans= mid;
            i= mid+1;
        }
        else if(arr[mid]* arr[mid] == n) {
            return mid;
        }
        mid= i+ (j-i)/2;
    }
    return ans;

}


// ── main: sqrt(10) ka integer part ─────────────────────────────────────────
//   1) arr = {0,1,...,10} — squares ke liye indices
//   2) n=10, BS se floor(sqrt) print
int main() {
    int n=10;
    int arr[] = {0,1,2,3,4,5,6,7,8,9,10};
    int size = 11;
    int binary = sqrt(arr, size, n);
    cout<< " integral part of sqrt of " << n << " is "<< binary<< endl;
    return 0;
}
