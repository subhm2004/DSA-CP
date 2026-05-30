/*
 * ============================================================================
 * TOPIC    : Practice
 * FILE     : misc_practice_1.cpp
 * PROBLEM  : Misc Practice 1
 * ABOUT    : General practice and mixed problems
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * solve()
 * Purpose : Standard DSA solution for this problem.
 * Params  : int *arr, int& size
 * Returns : void
 */
void solve(int *arr, int& size){
    cout<< "inside soleve: arr is"<< arr<< endl;
    cout<< "inside solve: &arr is"<< &arr<< endl;
}



/*
 * main()
 * Purpose : Entry point — demo/test for Misc Practice 1
 */
int main(){
    int arr[5]= {10,20,30,40,50};
    int size= 5;
    cout<< "insise main: arr is"<< arr<< endl;
    cout<< "inside main: &arr is"<< &arr<< endl;
    solve(arr,size);
     int (*ptr)[5]= &arr;
}
