/*
 * ============================================================================
 * TOPIC    : Vectors
 * FILE     : vector_practice_1.cpp
 * PROBLEM  : Vector Practice 1
 * ABOUT    : STL vector usage and applications
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// VECTOR INTERSECTION — do vectors ke common elements
// ────────────────────────────────────────────────────────────────────────────
// Funda: nested loop — crr[i]==drr[j] ho to ans me push
// Match ke baad crr[i]=INT_MIN — duplicate avoid (mark visited)
// find(): XOR helper (unused in main)
// COMPLEX: Time O(n*m)  |  Space O(intersection size)
// ════════════════════════════════════════════════════════════════════════════

// ── find: XOR se unique element (helper) ───────────────────────────────────
//   1) ans=0, har element XOR — pairs cancel
//   2) bacha hua unique element return
int find(vector<int> arr) {
    int ans=0;
    for(int i=0; i< arr.size(); i++) {
        ans = ans^ arr[i];
    }
    return ans;
}


// ── main: do vectors ka intersection nikalo ────────────────────────────────
//   1) crr aur drr vectors declare
//   2) nested loop match — ans push, crr[i] mark INT_MIN
//   3) intersection print
int main() {
    
   

    vector<int> crr{1,2,3,3,4,4};
    int sizecrr = 4;
    vector<int> drr{6,3,3,1,1,9,0};
    int sizedrr = 5;
    vector<int> ans;
    for(int i=0; i< crr.size(); i++) {
        for(int j=0; j< drr.size(); j++) {
            if(crr[i]== drr[j]) {
                
                ans.push_back(crr[i]); 
                crr[i] = INT_MIN;  // visited mark — duplicate avoid               
            }
        }
    }
    cout<< "intersection array is"<< endl;
    for(int i=0; i<ans.size(); i++) {
        cout<< ans[i]<< " ";

    }





}
