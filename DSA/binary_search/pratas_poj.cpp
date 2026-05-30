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



/*
 * possible()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : vector<int> cooksRanks, int P, int mid
 * Returns : bool
 */
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


/*
 * minTime()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : vector<int> cooksRank, int P
 * Returns : int
 */
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


/*
 * main()
 * Purpose : Entry point — demo/test for Pratas Poj
 */
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
