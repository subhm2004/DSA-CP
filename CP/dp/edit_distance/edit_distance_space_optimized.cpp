/*
 * ============================================================================
 * TOPIC    : Edit Distance
 * FILE     : edit_distance_space_optimized.cpp
 * PROBLEM  : Edit distance with O(min(n,m)) space
 * APPROACH : Two rolling rows
 * COMPLEX  : Time: O(n * m)  |  Space: O(min(n, m))
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int minEditDistance(const string &a, const string &b) {
    if (a.size() < b.size())
        return minEditDistance(b, a);

    int m = b.size();
    vector<int> prev(m + 1), curr(m + 1);

    for (int j = 0; j <= m; j++)
        prev[j] = j;

    for (char ca : a) {
        curr[0] = prev[0] + 1;
        for (int j = 1; j <= m; j++) {
            if (ca == b[j - 1])
                curr[j] = prev[j - 1];
            else
                curr[j] = 1 + min({prev[j], curr[j - 1], prev[j - 1]});
        }
        prev = curr;
    }

    return prev[m];
}

int main() {
    string a = "intention", b = "execution";
    cout << "Edit distance = " << minEditDistance(a, b) << endl;
    return 0;
}
