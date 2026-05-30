#include <iostream>
#include <vector>
using namespace std;

void printBaseK(int n, int k)
{
    if (n == 0)
    {
        cout << "0" << endl; // Edge case for n = 0
        return;
    }

    vector<int> digits; // To store digits in base k

    while (n > 0)
    {
        digits.push_back(n % k); // Store remainder (digit in base k)
        n /= k;                  // Move to the next digit
    }

    // Print the representation in correct order
    cout << "Base-" << k << " representation: ";
    for (int i = digits.size() - 1; i >= 0; i--)
    { // Reverse order without iterators
        cout << digits[i];
    }
    cout << endl;
}

int main()
{
    int n, k;
    cout << "Enter a number: ";
    cin >> n;
    cout << "Enter base (k): ";
    cin >> k;

    if (k < 2)
    {
        cout << "Base must be at least 2." << endl;
        return 0;
    }

    printBaseK(n, k); // Convert and print base-k representation

    return 0;
}
