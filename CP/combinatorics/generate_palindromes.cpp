#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// GENERATE PALINDROMES — fixed length ke saare palindromic numbers
// ────────────────────────────────────────────────────────────────────────────
// Trick: first half generate karo, mirror karke full palindrome banao
//   Even length: abc → abccba (poora reverse append)
//   Odd length:  abc → abcba (middle digit double nahi — substr(1) se skip)
// Count length L: 9 * 10^((L-1)/2 - 1) for L>1  (leading zero nahi)
// COMPLEX: O(10^ceil(L/2)) per length
// ════════════════════════════════════════════════════════════════════════════

// ── generate_Palindromes: given length ke saare palindromes return ──
//   1) length=1 → 1..9 directly
//   2) halfLength = ceil(L/2), range [10^(h-1), 10^h)
//   3) har half ko string me convert, mirror karke full banao
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
            full += half;              // even: poora reverse append
        else
            full += half.substr(1);    // odd: middle digit ek hi baar

        palindromes.push_back(stoll(full));
    }

    return palindromes;
}

// ── printPalindromesAndCount: generate + print stats ──
void printPalindromesAndCount(int length)
{
    vector<long long> pals = generate_Palindromes(length);

    cout << "Palindromes of length " << length << ":\n";
    for (long long num : pals)
        cout << num << " ";
    cout << "\nTotal Count: " << pals.size() << "\n";
    cout << "Sum of Palindromes: " << accumulate(pals.begin(), pals.end(), 0LL) << "\n";
    cout << "Average of Palindromes: " << (pals.empty() ? 0 : accumulate(pals.begin(), pals.end(), 0LL) / pals.size()) << "\n";
}

int main()
{
    int length;
    cout << "Enter length: ";
    cin >> length;

    printPalindromesAndCount(length);
    return 0;
}
