/*
 * ============================================================================
 * TOPIC    : Binary Search
 * FILE     : pratas_poj.cpp
 * PROBLEM  : Pratas Poj
 * LEETCODE : 410 — Split Array Largest Sum (binary search on answer)
 * ABOUT    : Binary search templates and classic interview problems
 * APPROACH : Binary search on sorted array or on answer.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;




// ════════════════════════════════════════════════════════════════════════════
// PRATA POJ — Min time for P pratas (BS on answer)
// ────────────────────────────────────────────────────────────────────────────
// Cook rank R — jth prata time = j*R
// possible(mid): mid time me P pratas ban sakte?
// MIN time pattern: possible -> ans=mid, e=mid-1
// ════════════════════════════════════════════════════════════════════════════


// ── possible: P pratas in mid time? ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
bool possible(vector<int> cooksRanks, int P, int mid)
{
    int currP = 0;
    for (int i = 0; i < cooksRanks.size(); i++)
    {
        int R = cooksRanks[i];
        int j = 1;
        int timetaken = 0;
        while (true)
        {
            if (timetaken + j * R <= mid)
            {
                currP++;
                timetaken += j * R;
                j++;
            }
            else
            {
                break;
            }
        }
        if (currP >= P)
        {
            return true;
        }
    }
    return false;
}



// ── minTime: min time BS ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int minTime(vector<int> cooksRank, int P)
{
    int start = 0;
    int highestRank = *max_element(cooksRank.begin(), cooksRank.end());
    int end = highestRank * (P * (P + 1) / 2);
    int ans = -1;
    while (start <= end)
    {
        int mid = start + (end - start) / 2;
        if (possible(cooksRank, P, mid))
        {
            ans = mid;
            end = mid - 1;
        }
        else
        {
            start = mid + 1;
        }
    }
    return ans;
}



// ── main: demo ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int P, C;
        cin >> P >> C;
        vector<int> cookRank;
        while (C--)
        {
            int R;
            cin >> R;
            cookRank.push_back(R);
        }
        cout << endl;
        cout << minTime(cookRank, P) << endl
             << endl;
    }
    return 0;
}
