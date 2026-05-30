/*
 * ============================================================================
 * TOPIC    : Probability DP
 * FILE     : dice_roll_expectation.cpp
 * PROBLEM  : Expected rolls to reach target sum with n-sided die
 * APPROACH : dp[s] = expected rolls from sum s to reach target
 * COMPLEX  : Time: O(target * faces)  |  Space: O(target)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

double expectedRolls(int n, int target) {
    vector<double> dp(target + 1, 0.0);
    dp[target] = 0.0;

    for (int s = target - 1; s >= 0; s--) {
        double sum = 0;
        for (int face = 1; face <= n; face++) {
            if (s + face <= target)
                sum += 1.0 + dp[s + face];
            else
                sum += 1.0; // overshoot — still counts as one roll
        }
        dp[s] = sum / n;
    }
    return dp[0];
}

int main() {
    int faces = 6, target = 10;
    cout << fixed << setprecision(4);
    cout << "Expected rolls (" << faces << "-sided die, target " << target
         << ") = " << expectedRolls(faces, target) << endl;
    return 0;
}
