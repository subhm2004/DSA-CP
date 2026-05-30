/*
 * ============================================================================
 * TOPIC    : Vectors
 * FILE     : jagged_array_using_vector.cpp
 * PROBLEM  : Jagged Array Using Vector
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
 * Purpose : Entry point — demo/test for Jagged Array Using Vector
 */
int main() {
    vector<vector<int> > arr;
    vector<int>vec1(10,1);
    vector<int>vec2(7,0);
    vector<int>vec3(7,1);
    vector<int>vec4(5,-1);
    arr.push_back(vec1);
    arr.push_back(vec2);
    arr.push_back(vec3);
    arr.push_back(vec4);
    cout<< "vector of vector is"<< endl;
    // Iterate over all elements
    for(int i=0; i< arr.size(); i++) {
        // Iterate over all elements
        for(int j=0; j< arr[i].size(); j++) {
            cout<< arr[i][j]<< " ";
        }
        cout<< endl;
    }
}
