// yha par pair_hash function use nhi hota kyoki window size constant nhi hai or dynamic hai to hum isme values ko add krte hai na ki delete krte hai isliye hum direct hash values ko update krke lete hai
#include <bits/stdc++.h> // Leetcode 1392 Longest Happy Prefix ese hi hota hai agar isse kroge to nhi to wo question hai KMP se bhi ho skta hai LPS array se
using namespace std;     // isme size variable hai to MAX_WEIGHT ki jarurat nhi hai kyoki hum har iteration me power ko update krke rkhte hai
typedef long long ll;
// Double Hashing Rolling Hash to find longest prefix which is also suffix
class Rolling_Hash_Prefix_Suffix
{
public:
    const ll RADIX_1 = 26;
    const ll MOD_1 = 1e9 + 7;
    const ll RADIX_2 = 27;
    const ll MOD_2 = 1e9 + 33;

    // returns longest prefix == suffix (excluding full string)
    string longest_happy_prefix(const string &s)
    {
        ll n = s.size();
        if (n <= 1)
            return "";

        ll hash_prefix_1 = 0, hash_suffix_1 = 0;
        ll hash_prefix_2 = 0, hash_suffix_2 = 0;

        ll power_1 = 1, power_2 = 1;
        ll max_len = 0;

        for (ll len = 1; len < n; len++)
        {
            // prefix grow (left → right)
            // Naya character right side me add hota hai , purana hash left me shift hota hai (multiply by RADIX)
            hash_prefix_1 = (hash_prefix_1 * RADIX_1 + (s[len - 1] - 'a')) % MOD_1;
            hash_prefix_2 = (hash_prefix_2 * RADIX_2 + (s[len - 1] - 'a')) % MOD_2;

            // suffix grow (right → left)
            // Naya character left side me add hota hai , purana hash right me shift hota hai (multiply by RADIX)
            // Start from index n-1, add characters at the **beginning** (but hash maintains left-to-right position)
            hash_suffix_1 = (hash_suffix_1 + ((s[n - len] - 'a') * power_1) % MOD_1) % MOD_1;
            hash_suffix_2 = (hash_suffix_2 + ((s[n - len] - 'a') * power_2) % MOD_2) % MOD_2;

            // compare both hash pairs
            if (hash_prefix_1 == hash_suffix_1 && hash_prefix_2 == hash_suffix_2)
            {
                max_len = len;
            }
            // update powers at each iteration because window size is dynamic
            power_1 = (power_1 * RADIX_1) % MOD_1;
            power_2 = (power_2 * RADIX_2) % MOD_2;
        }

        return s.substr(0, max_len);
    }
};

int main()
{
    Rolling_Hash_Prefix_Suffix rh;
    cout << rh.longest_happy_prefix("ababab") << endl; // → "abab"
    cout << rh.longest_happy_prefix("level") << endl;  // → "l"
    cout << rh.longest_happy_prefix("abcd") << endl;   // → ""
}
