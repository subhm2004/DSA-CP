/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : two_sum.cpp
 * PROBLEM  : Two Sum
 * LEETCODE : 1 — Two Sum
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Hash map or two pointers to find pair with target sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// TWO SUM — pair with target sum (brute + optimal)
// ────────────────────────────────────────────────────────────────────────────
// twosum(): brute O(n²) nested loop
// twosum2(): sort + two pointers O(n log n) — sorted array pe optimal
// mergesort/merge: divide & conquer sorting helper
// COMPLEX: Two-pointer O(n log n)  |  Brute O(n²)
// ════════════════════════════════════════════════════════════════════════════

// ── twosum: brute force pair dhundho ───────────────────────────────────────
//   1) outer i, inner j=i+1 — duplicate pairs avoid
//   2) arr[i]+arr[j]==sum ho to true
//   3) koi pair nahi to false
bool twosum(int arr[], int& size, int& sum) {
    for(int i=0; i< size-1; i++) {
        for(int j=i+1; j< size; j++) {
            if(arr[i] + arr[j]== sum) {
                return true;
            }
        }
    }
    return false;
}


// ── bubblesort: adjacent swap sorting ──────────────────────────────────────
//   1) n rounds — har round me largest right end pe
//   2) inner loop me arr[j] > arr[j+1] ho to swap
//   3) size-i-1 tak — sorted suffix skip
void bubblesort(int arr[], int size) {
    for(int i=0; i<size; i++) {
        for(int j=0; j< size-i-1; j++) {
            if(arr[j]> arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}


// ── printarray: array elements print ───────────────────────────────────────
//   1) size tak loop, space-separated print
void printarray(int arr[], int size) {
    for(int i=0; i< size; i++) {
        cout<< arr[i] << " ";
    }
}


// ── merge: do sorted halves ko merge karo ──────────────────────────────────
//   1) mid nikalo, left[] aur right[] temp arrays banao
//   2) dono halves copy karo
//   3) two-pointer merge — chhota pehle arr me daalo
//   4) bachi elements copy karo
void merge(int arr[], int& s, int& e) {
    int mid = s+(e-s)/2;
    int length1 = mid -s+1;
    int length2= e- mid;
    int* left= new int[length1];
    int* right = new int[length2];
    int k=s;
    for(int i=0; i<length1; i++) {
        left[i] = arr[k];
        k++;
    }
    k = mid+1;
    for(int i= 0; i< length2; i++) {
        right[i] = arr[k];
        k++;
    }
    int i=0, j=0;
    int mainindex = s;
    while(i< length1 && j< length2) {
        if(left[i]< right[j]) {
            arr[mainindex++] = left[i++] ;
        }
        else {
            arr[mainindex++] = right[j++];
        }   
    }
    while(i< length1) {
        arr[mainindex++] = left[i++];
    }
    while(j< length2){
        arr[mainindex++] = right[j++];
    }
}


// ── mergesort: divide & conquer sort ───────────────────────────────────────
//   1) base case: s>=e return
//   2) mid pe split — left aur right recursively sort
//   3) merge() se sorted halves combine
void mergesort(int arr[], int s, int& e) {
    if(s>=e) {
        return;
    }
    int mid = s+(e-s)/2;
    mergesort(arr, s, mid);
    mergesort(arr, mid+1, e);
    merge(arr, s, e);
}


// ── twosum2: sort + two pointers se pair dhundho ───────────────────────────
//   1) mergesort se array sort karo
//   2) i=0 (left), j=size-1 (right) — two pointer window
//   3) sum match -> print pair; bada sum -> j--; chhota -> i++
void twosum2(int arr[], int& size,int& s, int& e, int& sum) {
    mergesort(arr, s, e);
    printarray(arr, size);
    cout<< endl;
    int i=0, j= size-1;
    while(i<j) {
        if(arr[i] + arr[j] == sum) {
            cout<< arr[i]<< " "<< arr[j]<< endl;
            break;
        }
        else if(arr[i] + arr[j] > sum) {
            j--;
        }
        else {
            i++;
        }
    }
}


// ── main: twosum2 demo — target sum 16 ─────────────────────────────────────
//   1) unsorted array
//   2) sort + two pointer pair search
int main() {
    int arr[] = {1,45,4,6,10,8};
    int size = 6;
    int s=0, e= size-1;
    int sum = 16;
    twosum2(arr, size, s, e, sum);
    
}
