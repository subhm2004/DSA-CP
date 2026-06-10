/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : array_practice_2.cpp
 * PROBLEM  : Array Practice 2
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// XOR UNIQUE + ARRAY INTERSECTION — do problems ek file me
// ────────────────────────────────────────────────────────────────────────────
// unique(): XOR se woh element jo baaki sab se alag (odd frequency)
// main(): nested loop se arr aur brr ka intersection print
// COMPLEX: XOR O(n)  |  Intersection O(n*m)
// ════════════════════════════════════════════════════════════════════════════

// ── unique: XOR se unique element nikalo ───────────────────────────────────
//   1) ans = 0 se start karo
//   2) har element ko ans se XOR karo — pairs cancel ho jate hain
//   3) bacha hua ans hi unique element hai
int unique(vector<int>arr) {
    int ans=0;
    for(int i=0; i< arr.size(); i++) {
        ans = ans^arr[i];

    }
    return ans;
}



// ── main: do arrays ka common intersection print karo ──────────────────────
//   1) arr aur brr declare karo
//   2) nested loop — match ho to print
//   3) brute force approach, duplicates bhi aayenge
int main() {
   
    
    
    int arr[]  = {1,2,3,4,5};
    int sizearr = 5;
    int brr[] = { 2,5,6,7};
    int sizebrr = 4;
    
    for(int i=0; i< sizearr ; i++) {
        for(int j=0; j< sizebrr; j++) {
            if(arr[i]== brr[j]) {
                cout<< arr[i] << " ";

            }
        }
    }

}
