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

// ════════════════════════════════════════════════════════════════════════════
// JOB SEQUENCING — Profit descending, deadline slots fill karo
// ────────────────────────────────────────────────────────────────────────────
// Jobs: {id, deadline, profit} — pehle profit se sort (greedy)
// Har job: deadline se 1 tak pehla khali slot dhundho
// Slot array: -1 = free — ek time pe ek hi job
// Total profit maximize — classic greedy scheduling
// ════════════════════════════════════════════════════════════════════════════

typedef tuple<char, int, int> Job; // {id, deadline, profit}

// ── compareByProfit: sort ke liye profit descending ────────────────────────
//   1) get<2>(a) > get<2>(b) — zyada profit pehle
bool compareByProfit(Job a, Job b)
{
    return get<2>(a) > get<2>(b);
}

// ── printJobScheduling: max profit job sequence print ──────────────────────
//   1) jobs profit se sort
//   2) maxDeadline nikalo — slots array size
//   3) har job: deadline se 1 tak pehla free slot (-1) dhundho
//   4) slot fill, profit add, sequence me id push
//   5) job sequence aur total profit print
void printJobScheduling(vector<Job> jobs)
{
    int n = jobs.size();

    sort(jobs.begin(), jobs.end(), compareByProfit);

    int maxDeadline = 0;
    for (int i = 0; i < n; i++)
    {
        maxDeadline = max(maxDeadline, get<1>(jobs[i]));
    }

    vector<int> slots(maxDeadline + 1, -1); // -1 = slot khali hai

    vector<char> jobSequence;
    int totalProfit = 0;

    for (int i = 0; i < n; i++)
    {
        char id = get<0>(jobs[i]);
        int deadline = get<1>(jobs[i]);
        int profit = get<2>(jobs[i]);

        for (int j = deadline; j > 0; j--) // deadline tak peeche se slot dhundho
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

// ── main: 5 jobs demo — max profit sequence ────────────────────────────────
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
