/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : sort_in_array.cpp
 * PROBLEM  : Sort In Array
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;


/*
 * main()
 * Purpose : Entry point — demo/test for Sort In Array
 */
int main() {
    vector<int>arr{1,0,1,1,0,1,1,0,0,0,1,0};
    int zero= 0, one =0;
    // Iterate over all elements
    for(int i=0; i<arr.size(); i++) {
        if(arr[i] == 0) {
            zero++;
        }
        else {
            one++;
        }
    }
    cout<< zero<< endl;
    cout<< one<< endl;

    vector<int>brr; // size insert krne par uss size ka element 0 consider ho rha h

    for(int i=0; i< one; i++) {
        brr.push_back(1);
    }
    cout<< endl;
    for(int i = 0; i < one; i++) {
        cout<< brr[i] << " ";
    }
    cout<< endl;
    for(int i=0; i<zero; i++) {
        brr.push_back(0);
    }
    cout<< "elements of final array are "<<endl;
    // Iterate over all elements
    for(int i=0; i< brr.size(); i++) {
        cout<< brr[i] << " ";
    }

}
