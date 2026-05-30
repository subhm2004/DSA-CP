// LC 1147 - Longest Chunked Palindrome Decomposition

// Recursive Mirror Splitting with Rolling Hash
#include <bits/stdc++.h> // Prefix hashing and Suffix hashing dono kr rhe hai
using namespace std;
typedef long long ll;

class Solution
{
public:
    int longestDecomposition(string text)
    {
        int n = text.size();

        // --------------------------
        // Double Hashing setup
        // --------------------------
        ll MOD_1 = 1e9 + 7;  // First modulo
        ll MOD_2 = 1e9 + 33; // Second modulo
        ll RADIX_1 = 26;     // Base 1
        ll RADIX_2 = 27;     // Base 2

        // --------------------------
        // Hash variables
        // --------------------------
        ll left_hash1 = 0, right_hash1 = 0; // forward and backward hashes for mod1
        ll left_hash2 = 0, right_hash2 = 0; // forward and backward hashes for mod2
        ll power_1 = 1, power_2 = 1;        // powers for backward hash

        int count = 0; // Number of mirror segments found

        // --------------------------
        // Iterate through string
        // --------------------------
        for (int i = 0; i < n; i++)
        {
            /**
             * Left Hash (forward hash):
             * left_hash = text[0]*RADIX^i + text[1]*RADIX^(i-1) + ... + text[i]*RADIX^0  (mod MOD)
             *
             * Hum left se rolling hash calculate kar rahe hain.
             * Har step me purana hash multiply by RADIX karke new character add karte hain.
             * Isse positional value automatically adjust ho jati hai.
             */
            left_hash1 = (left_hash1 * RADIX_1 + text[i]) % MOD_1;
            left_hash2 = (left_hash2 * RADIX_2 + text[i]) % MOD_2;

            /**
             * Right Hash (backward hash):
             * right_hash = text[n-1]*RADIX^0 + text[n-2]*RADIX^1 + ... + text[n-1-i]*RADIX^i  (mod MOD)
             *
             * Hum right se rolling hash calculate kar rahe hain.
             * Yahan har character ke liye explicit 'power' variable ka use hota hai,
             * taaki left hash ke corresponding powers se align ho jaye aur mirror check possible ho.
             */
            right_hash1 = (right_hash1 + power_1 * text[n - 1 - i]) % MOD_1;
            right_hash2 = (right_hash2 + power_2 * text[n - 1 - i]) % MOD_2;

            // Next step ke liye powers update kar rahe hain (sirf right hash ke liye)
            power_1 = (power_1 * RADIX_1) % MOD_1;
            power_2 = (power_2 * RADIX_2) % MOD_2;

            /**
             * Mirror segment detection:
             * Agar dono hashes match kar gaye → ek mirror segment mil gaya
             * Mirror segment ka matlab:
             * left substring [0..i] == right substring [n-1-i..n-1]
             */
            if (left_hash1 == right_hash1 && left_hash2 == right_hash2)
            {
                count++; // ek segment mil gaya

                // Next segment ke liye hashes aur powers reset kar rahe hain
                left_hash1 = left_hash2 = 0;
                right_hash1 = right_hash2 = 0;
                power_1 = power_2 = 1;
            }
        }

        return count; // Total mirror segments
    }
};

int main()
{
    Solution sol;

    string text1 = "ghiabcdefhelloadamhelloabcdefghi";
    cout << "Input: " << text1 << "\nOutput: " << sol.longestDecomposition(text1) << "\n\n";

    string text2 = "merchant";
    cout << "Input: " << text2 << "\nOutput: " << sol.longestDecomposition(text2) << "\n\n";

    string text3 = "antaprezatepzapreanta";
    cout << "Input: " << text3 << "\nOutput: " << sol.longestDecomposition(text3) << "\n\n";

    return 0;
}
