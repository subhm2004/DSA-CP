#include <iostream>
#include <vector>

using namespace std;

// Function to calculate sum of all substrings using memoization
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

// Wrapper function to initialize vector and call recursive function
long long sumOfSubstrings(const string &num)
{
    int n = num.length();
    vector<long long> dp(n, -1); // Memoization vector initialized with -1
    return sumOfSubstringsHelper(num, 0, 0, dp);
}

// Driver code
int main()
{
    string num;
    cout << "Enter a number: ";
    cin >> num; // User input

    // Function call
    cout << "Sum of all substrings: " << sumOfSubstrings(num) << endl;

    return 0;
}
