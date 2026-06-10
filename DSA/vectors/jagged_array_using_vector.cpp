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

// ════════════════════════════════════════════════════════════════════════════
// JAGGED ARRAY — vector<vector<int>> se variable-length rows
// ────────────────────────────────────────────────────────────────────────────
// Funda: har row alag size ki ho sakti hai — 2D vector of vectors
// vec1(10,1) = 10 elements sab 1; alag sizes push_back se jagged banao
// COMPLEX: Time O(total elements) print  |  Space O(total elements)
// ════════════════════════════════════════════════════════════════════════════

// ── main: jagged 2D vector banao aur print karo ────────────────────────────
//   1) alag size ke row vectors banao (10, 7, 7, 5 elements)
//   2) arr.push_back se rows add — jagged structure
//   3) nested loop se har row print — arr[i].size() alag ho sakta hai
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
    for(int i=0; i< arr.size(); i++) {
        for(int j=0; j< arr[i].size(); j++) {
            cout<< arr[i][j]<< " ";
        }
        cout<< endl;
    }
}
