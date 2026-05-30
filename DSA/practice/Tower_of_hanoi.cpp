/*
 * ============================================================================
 * TOPIC    : Practice
 * FILE     : tower_of_hanoi.cpp
 * PROBLEM  : Tower Of Hanoi
 * ABOUT    : General practice and mixed problems
 * APPROACH : Move n-1 disks, move largest, move n-1 back.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <cmath>  // for pow
using namespace std;

class Solution {
public:
    
    
    /*
     * Tower_of_hanoi()
     * Purpose : Move n-1 disks, move largest, move n-1 back.
     * Params  : int n, int from, int to, int aux
     * Returns : long long
     */
    long long Tower_of_hanoi(int n, int from, int to, int aux) {
        if (n == 1) {
            cout << "move disk " << n << " from rod " << from << " to rod " << to << endl;
            return 1;
        }

        long long count = 0;
        count += Tower_of_hanoi(n - 1, from, aux, to);
        cout << "move disk " << n << " from rod " << from << " to rod " << to << endl;
        count++;
        count += Tower_of_hanoi(n - 1, aux, to, from);

        return count;
    }
};



/*
 * main()
 * Purpose : Entry point — demo/test for Tower Of Hanoi
 */
int main() {
    int N;
    cout << "Enter number of disks: ";
    cin >> N;

    Solution obj;
    long long totalMoves = obj.Tower_of_hanoi(N, 1, 3, 2);
    
    long long expectedMoves = pow(2, N) - 1;

    cout << "Total moves (by function): " << totalMoves << endl;
    cout << "Expected moves (2^" << N << " - 1): " << expectedMoves << endl;

    return 0;
}
