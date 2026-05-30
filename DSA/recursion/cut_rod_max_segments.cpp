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


/*
 * maxsegment()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int n, int x, int y, int z
 * Returns : int
 */
int maxsegment(int n, int x, int y, int z ){
    // Base case: n == 0
    if(n==0){
        return 0;
    }
    if(n<0){
        return INT_MIN;
    }
    int a= maxsegment(n-x,x,y,z) +1;
    int b= maxsegment(n-y,x,y,z) +1;
    int c= maxsegment(n-z,x,y,z) +1;
    int ans= max(a, max(b,c));
    return ans;
}


/*
 * main()
 * Purpose : Entry point — demo/test for Cut Rod Max Segments
 */
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
