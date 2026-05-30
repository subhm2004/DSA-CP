#include <bits/stdc++.h>
using namespace std;

// 1. Function to generate all palindromes of given length
vector<long long> generate_Palindromes(int length)
{
    vector<long long> palindromes;

    if (length == 1)
    {
        for (int i = 1; i <= 9; i++)
            palindromes.push_back(i);
        return palindromes;
    }

    int halfLength = (length + 1) / 2;
    long long start = pow(10, halfLength - 1);
    long long end = pow(10, halfLength);

    for (long long i = start; i < end; i++)
    {
        string half = to_string(i);
        string full = half;

        reverse(half.begin(), half.end());
        if (length % 2 == 0)
            full += half;
        else
            full += half.substr(1); // skip the middle digit for odd-length

        palindromes.push_back(stoll(full));
    }

    return palindromes;
}

// 2. Function to print all palindromes of given length and count them
void printPalindromesAndCount(int length)
{
    vector<long long> pals = generate_Palindromes(length);

    cout << "Palindromes of length " << length << ":\n";
    for (long long num : pals)
    {
        cout << num << " ";
    }
    cout << "\nTotal Count: " << pals.size() << "\n";
    cout << "Sum of Palindromes: " << accumulate(pals.begin(), pals.end(), 0LL) << "\n";
    cout << "Average of Palindromes: " << (pals.empty() ? 0 : accumulate(pals.begin(), pals.end(), 0LL) / pals.size()) << "\n";
}

// Example usage
int main()
{
    int length;
    cout << "Enter length: ";
    cin >> length;

    printPalindromesAndCount(length);
    return 0;
}
