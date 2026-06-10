/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : array_practice_3.cpp
 * PROBLEM  : Array Practice 3
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// UNION / NON-COMMON ELEMENTS — brute force with flag
// ────────────────────────────────────────────────────────────────────────────
// Funda: har arr[i] ke liye brr me dhundho — match nahi to union me daalo
// flag se track karo ki common mila ya nahi
// COMPLEX: Time O(n*m)  |  Space O(n+m) for ans vector
// ════════════════════════════════════════════════════════════════════════════

// ── main: do arrays ke non-matching elements union me daalo ────────────────
//   1) nested loop — arr[i] aur brr[j] compare
//   2) match mila to flag=0, break
//   3) flag==1 ho to dono elements ans me push_back
//   4) ans vector print karo
int main() {
    int arr[] = { 1,2,3,4,5};
    int sizearr = 5;
    int brr[] = { 2,4,5,6,7};
    int sizebrr = 5;
    vector<int>ans;
    int flag = 1;
    for(int i=0; i<sizearr; i++) {
      for(int j=0; j<sizebrr; j++) {
        if(arr[i] == brr[j]) {
            flag=0;
            break;
        }
        else if(flag == 1) {
            ans.push_back(arr[i]);
            ans.push_back(brr[j]);
        }
    }
}
cout<< "elements of new array are "<< endl;
for(int i=0; i< ans.size(); i++) {
    cout<< ans[i]<< " ";
}

}
