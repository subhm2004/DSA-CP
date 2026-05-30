/*
 * ============================================================================
 * TOPIC    : Binary Search on Answer
 * FILE     : prata_cooking_time.cpp
 * PROBLEM  : P pratas, C cooks with ranks — minimum time (POJ PRATA)
 * APPROACH : BS on answer (time), simulate pratas cooked
 * COMPLEX  : Time: O(C log(maxTime))  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

bool canCook(const vector<int> &ranks, int pratas, long long time) {
    long long cooked = 0;
    for (int r : ranks) {
        long long t = 0, batch = 1;
        while (t + batch * r <= time) {
            t += batch * r;
            cooked += batch;
            batch++;
        }
    }
    return cooked >= pratas;
}

long long minCookTime(vector<int> ranks, int pratas) {
    long long lo = 0;
    long long hi = 1LL * (*max_element(ranks.begin(), ranks.end())) * pratas * (pratas + 1) / 2;
    long long ans = hi;

    while (lo <= hi) {
        long long mid = lo + (hi - lo) / 2;
        if (canCook(ranks, pratas, mid)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}

int main() {
    vector<int> ranks = {1, 2, 3, 4};
    int pratas = 10;
    cout << "Minimum cooking time = " << minCookTime(ranks, pratas) << endl;
    return 0;
}
