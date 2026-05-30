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


/*
 * main()
 * Purpose : Entry point — demo/test for Array Practice 3
 */
int main() {
    int arr[] = { 1,2,3,4,5};
    int sizearr = 5;
    int brr[] = { 2,4,5,6,7};
    int sizebrr = 5;
    vector<int>ans;
    int flag = 1;
    // Iterate over all elements
    for(int i=0; i<sizearr; i++) {
      // Iterate over all elements
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
// Iterate over all elements
for(int i=0; i< ans.size(); i++) {
    cout<< ans[i]<< " ";
}

}
