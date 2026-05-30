/*
 * ============================================================================
 * TOPIC    : Vectors
 * FILE     : vector_basics.cpp
 * PROBLEM  : Vector Basics
 * ABOUT    : STL vector usage and applications
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;


/*
 * main()
 * Purpose : Entry point — demo/test for Vector Basics
 */
int main() {
    vector<int> arr;
    arr.push_back(5);
    arr.push_back(7);
    cout<< arr.size() << endl;
    cout<< arr.capacity() << endl;
    
    // Iterate over all elements
    for(int i=0; i< arr.size(); i++) {
        cout<< arr[i]<< " ";
    }
    cout<< "\n";
    arr.pop_back();
    // Iterate over all elements
    for(int i=0; i< arr.size(); i++) {
        cout<< arr[i]<< " ";
    }
    cout<< endl;
    cout<< arr.size() << endl;
    cout<< arr.capacity() << endl;
    vector<int> brr{10, 20, 30};
    // Iterate over all elements
    for(int i=0; i< brr.size(); i++) {
        cout<< brr[i] << " ";
    }
    cout<< "\n";
    vector<int> crr(10, -2);
    // Iterate over all elements
    for(int i=0; i< crr.size(); i++) {
        cout<< crr[i]<< " ";
    }
    return 0;

}
