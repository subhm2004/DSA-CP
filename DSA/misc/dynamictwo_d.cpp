/*
 * ============================================================================
 * TOPIC    : Misc
 * FILE     : dynamictwo_d.cpp
 * PROBLEM  : Dynamictwo D
 * ABOUT    : Mixed DSA practice problems
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : Time: O(n*m)  |  Space: O(1) or O(n*m)
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;


/*
 * main()
 * Purpose : Entry point — demo/test for Dynamictwo D
 */
int main(){
    int row= 5;
    int col=3;
    int **arr= new int*[5];
    for(int i=0; i< row; i++){
        arr[i] = new int[col];
    }
    cout<< "2-D array is\n";
    for(int i=0; i< row; i++){
        for(int j=0; j< col; j++){
            cout<< arr[i][j]<< " ";
        }
        cout<< endl;
    }
    for(int i=0; i< row; i++){
        delete []arr[i];
    }
    delete []arr;
}
