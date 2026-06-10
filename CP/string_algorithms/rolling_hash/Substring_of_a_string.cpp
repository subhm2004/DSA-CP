#include <iostream>
#include <vector>
#include <string>
#include <numeric> // For accumulate()

using namespace std;

// getSubstrings — string/sequence ke saare contiguous substrings generate karo.
// Step 1: Har start index i ke liye end j = i+1 se n tak iterate karo.
// Step 2: s.substr(i, j-i) push karo — total n*(n+1)/2 substrings.
// Step 3: Template T se string, vector, etc. pe kaam karta hai.
template <typename T>
vector<T> getSubstrings(const T &s)
{
    int n = s.size();
    vector<T> substrings;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            substrings.push_back(s.substr(i, j - i));
        }
    }

    return substrings;
}

// getSubstrings (int overload) — number ke saare numeric substrings as integers.
// Step 1: int ko string me convert karo taaki digits pe iterate ho sake.
// Step 2: Har [i..j) substring ko stoi se int me convert karke vector me daalo.
// Step 3: Same O(n^2) brute enumeration — rolling hash nahi, sirf generation demo.
vector<int> getSubstrings(int num)
{
    string s = to_string(num); // Convert int to string
    vector<int> substrNumbers;
    int n = s.size();

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            substrNumbers.push_back(stoi(s.substr(i, j - i))); // Convert substring back to int
        }
    }

    return substrNumbers;
}

// main — string aur integer dono ke substrings generate karke count/sum print karo.
int main()
{
    // String substrings
    string s = "shubham";
    vector<string> substringsStr = getSubstrings(s);
    cout << "Total string substrings: " << substringsStr.size() << endl;
    cout << "String Substrings: ";
    for (const auto &sub : substringsStr)
    {
        cout << sub << " ";
    }
    cout << endl
         << endl;

    // Integer substrings
    int num = 12345;
    vector<int> substringsInt = getSubstrings(num);
    cout << "Total integer substrings: " << substringsInt.size() << endl;

    // Sum of all integer substrings
    int sum = accumulate(substringsInt.begin(), substringsInt.end(), 0);
    cout << "Sum of integer substrings: " << sum << endl;

    // Print all integer substrings
    cout << "Integer Substrings: ";
    for (const auto &num : substringsInt)
    {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}

// #include <iostream>
// using namespace std;

// void printSubstrings(string s, int start, int end)
// {
//     if (start == s.size())
//         return; // Base case: stop when start reaches the end

//     if (end > s.size())
//     {
//         // Move to the next starting character
//         printSubstrings(s, start + 1, start + 1);
//     }
//     else
//     {
//         // Print current substring and move to the next ending index
//         cout << s.substr(start, end - start) << endl;
//         printSubstrings(s, start, end + 1);
//     }
// }

// int main()
// {
//     string s = "shubham";
//     printSubstrings(s, 0, 0);
//     return 0;
// }
