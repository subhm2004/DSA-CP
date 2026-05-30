/*
 * ============================================================================
 * TOPIC    : Greedy
 * FILE     : job_sequencing.cpp
 * PROBLEM  : Job Sequencing
 * LEETCODE : 435 — Non-overlapping Intervals (scheduling variant)
 * ABOUT    : Greedy choice problems
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <bits/stdc++.h> // for max profit
using namespace std;

typedef tuple<char, int, int> Job; // {id, deadline, profit}



/*
 * compareByProfit()
 * Purpose : Standard DSA solution for this problem.
 * Params  : Job a, Job b
 * Returns : bool
 */
bool compareByProfit(Job a, Job b)
{
    return get<2>(a) > get<2>(b); // Compare based on profit
}



/*
 * printJobScheduling()
 * Purpose : Standard DSA solution for this problem.
 * Params  : vector<Job> jobs
 * Returns : void
 */
void printJobScheduling(vector<Job> jobs)
{
    int n = jobs.size();

    sort(jobs.begin(), jobs.end(), compareByProfit);

    int maxDeadline = 0;
    for (int i = 0; i < n; i++)
    {
        maxDeadline = max(maxDeadline, get<1>(jobs[i]));
    }

    vector<int> slots(maxDeadline + 1, -1); // -1 indicates the slot is free

    vector<char> jobSequence;
    int totalProfit = 0;

    for (int i = 0; i < n; i++)
    {
        char id = get<0>(jobs[i]);
        int deadline = get<1>(jobs[i]);
        int profit = get<2>(jobs[i]);

        for (int j = deadline; j > 0; j--)
        {
            if (slots[j] == -1)
            {
                slots[j] = i;
                jobSequence.push_back(id);
                totalProfit += profit;
                break;
            }
        }
    }

    cout << "Job sequence: ";
    for (char job : jobSequence)
    {
        cout << job << " ";
    }
    cout << "\nTotal Profit: " << totalProfit << endl;
}



/*
 * main()
 * Purpose : Entry point — demo/test for Job Sequencing
 */
int main()
{
    vector<Job> jobs = {
        {'a', 2, 100},
        {'b', 1, 19},
        {'c', 2, 27},
        {'d', 1, 25},
        {'e', 3, 15}};

    cout << "Following is the maximum profit sequence of jobs:\n";
    printJobScheduling(jobs);

    return 0;
}
