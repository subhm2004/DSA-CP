/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : cut_rod_max_segments.cpp
 * PROBLEM  : Cut Rod Max Segments
 * LEETCODE : 322 — Coin Change (rod cutting variant)
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// CUT ROD — Rod length n ko x, y, z segments me max pieces
// ────────────────────────────────────────────────────────────────────────────
// Teen sizes x, y, z — har step pe ek cut (+1 segment)
// max(a,b,c) where a=1+cut(n-x), b=1+cut(n-y), c=1+cut(n-z)
// n<0 -> invalid (INT_MIN); n==0 -> 0 segments
// ════════════════════════════════════════════════════════════════════════════

// ── maxsegment: maximum segments from rod length n ────────────────────────────
//   1) n==0 -> 0 segments
//   2) n<0 -> invalid, INT_MIN
//   3) teen options try — cut x, y, ya z size
//   4) max of teen + 1 return
int maxsegment(int n, int x, int y, int z ){
    if(n==0){
        return 0;
    }
    if(n<0){
        return INT_MIN;  // cut possible nahi
    }
    int a= maxsegment(n-x,x,y,z) +1;
    int b= maxsegment(n-y,x,y,z) +1;
    int c= maxsegment(n-z,x,y,z) +1;
    int ans= max(a, max(b,c));
    return ans;
}

// ── main: rod length aur segment sizes input ──────────────────────────────────
int main() {
    int n;
    cout<< " enter the length of rod"<< endl;
    cin>> n;
    int x,y,z;
    cout<< "enter the three parts"<< endl;
    cin>> x>> y>> z;
    int f = maxsegment(n,x,y,z);
    if(f<0){
        cout<< "length can't be cut"<< endl;
    }
    else{
        cout<<"maximum segment is: "<<  f<< endl;
    }
    
}
