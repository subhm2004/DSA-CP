#include <iostream>
#include <vector>

using namespace std;

// sumOfSubstringsHelper — digit string ke saare numeric substrings ka sum (memoized).
// Step 1: Base case i == n → 0 return (saare digits process ho gaye).
// Step 2: dp[i] cached ho to turant return — overlapping subproblems avoid.
// Step 3: current = (i+1)*digit + 10*prev — naya digit purane substrings me append.
// Step 4: current + recursive(i+1, current) store karke return.
long long sumOfSubstringsHelper(const string &num, int i, long long prev, vector<long long> &dp)
{
    // Base case: If we have processed all digits
    if (i == num.length())
        return 0;

    // If already computed, return stored result
    if (dp[i] != -1)
        return dp[i];

    int digit = num[i] - '0';

    // Compute the current sum using the formula
    long long current = (i + 1) * digit + 10 * prev;

    // Store and return result with recursive call
    return dp[i] = current + sumOfSubstringsHelper(num, i + 1, current, dp);
}

// sumOfSubstrings — wrapper: dp array init karke helper ko call karo.
// Step 1: n-sized dp vector -1 se bharo (uncomputed marker).
// Step 2: index 0, prev 0 se recursion shuru — total sum return.
long long sumOfSubstrings(const string &num)
{
    int n = num.length();
    vector<long long> dp(n, -1); // Memoization vector initialized with -1
    return sumOfSubstringsHelper(num, 0, 0, dp);
}

// main — user se number input lo aur saare substrings ka sum print karo.
int main()
{
    string num;
    cout << "Enter a number: ";
    cin >> num; // User input

    // Function call
    cout << "Sum of all substrings: " << sumOfSubstrings(num) << endl;

    return 0;
}
