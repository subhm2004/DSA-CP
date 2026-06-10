/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : unique_occurrence.cpp
 * PROBLEM  : Unique Occurrence
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// UNIQUE OCCURRENCE + XOR DUPLICATE — frequency aur XOR
// ────────────────────────────────────────────────────────────────────────────
// uniqueocc(): 1,2,3 ki frequency count — sab alag ho to true
// duplicate(): XOR se odd-frequency element nikalo
// COMPLEX: Count O(n)  |  XOR O(n)
// ════════════════════════════════════════════════════════════════════════════

// ── printarray: array print karo ─────────────────────────────────────────────
//   1) label + elements space-separated print
void printarray(int arr[], int size) {
    cout<< "array is"<< " ";
    for(int i=0; i<size; i++) {
        cout<< arr[i]<< " ";

    }
    cout<< endl;
}


// ── uniqueocc: kya har value ki unique frequency hai? ──────────────────────
//   1) a,b,c counters — 1, 2, 3 (ya else) count
//   2) teeno frequencies print
//   3) a!=b && b!=c && c!=a ho to true — sab alag
bool uniqueocc(int arr[], int size) {
    int a=0, b=0, c=0;
    for(int i=0; i<size; i++) {
        if(arr[i] == 1) {
            a++;
        }
        else if(arr[i]==2) {
            b++;
    }
    else {
        c++;
    }
}
 cout<< "occurrence of 1 is "<< a<<" times"<< endl;
 cout<< "occurrence of 2 is "<< b<< " times" << endl;
 cout<< "occurrence of 3 is "<< c<<" times"<<  endl;
 if(a!=b && b!=c && c!=a) {
    return true;
 }
 else {
    return false;
 }

}


// ── duplicate: XOR se single odd-occurrence element ────────────────────────
//   1) ans=0, har element XOR — pairs cancel
//   2) bacha hua ans print — unique element
void duplicate(int arr[], int size) {
    int ans=0;
    for(int i=0; i<size; i++) {
        ans = ans^arr[i];
        cout<< ans<< " ";
    }    
}


// ── main: print array + XOR duplicate demo ─────────────────────────────────
//   1) array print
//   2) XOR se unique element trace
int main() {
    int arr[]= { 1, 2 ,3,3,4};
    int size = 5;
    printarray(arr, size);
    duplicate(arr, size);   
}
