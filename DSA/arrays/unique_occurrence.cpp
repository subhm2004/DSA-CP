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


/*
 * printarray()
 * Purpose : Iterate with two pointers / sliding window / prefix sum.
 * Params  : int arr[], int size
 * Returns : void
 */
void printarray(int arr[], int size) {
    cout<< "array is"<< " ";
    // Iterate over all elements
    for(int i=0; i<size; i++) {
        cout<< arr[i]<< " ";

    }
    cout<< endl;
}


/*
 * uniqueocc()
 * Purpose : Iterate with two pointers / sliding window / prefix sum.
 * Params  : int arr[], int size
 * Returns : bool
 */
bool uniqueocc(int arr[], int size) {
    int a=0, b=0, c=0;
    // Iterate over all elements
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


/*
 * duplicate()
 * Purpose : Hash set or sorting to find duplicates.
 * Params  : int arr[], int size
 * Returns : void
 */
void duplicate(int arr[], int size) {
    int ans=0;
    // Iterate over all elements
    for(int i=0; i<size; i++) {
        ans = ans^arr[i];
        cout<< ans<< " ";
    }    
}


/*
 * main()
 * Purpose : Entry point — demo/test for Unique Occurrence
 */
int main() {
    int arr[]= { 1, 2 ,3,3,4};
    int size = 5;
    printarray(arr, size);
    duplicate(arr, size);   
}
