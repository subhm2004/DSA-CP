#include <bits/stdc++.h>
using namespace std;

// Computes φ(n) for a single number using prime factorization
int phi(int n)
{
    int result = n;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

// Computes φ(1) to φ(n) using the sieve method
vector<int> phi_1_to_n(int n)
{
    vector<int> phi(n + 1);
    for (int i = 0; i <= n; i++)
        phi[i] = i;

    for (int i = 2; i <= n; i++)
    {
        if (phi[i] == i)
        { // i is prime
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
    return phi;
}

int main()
{
    int n;
    cout << "Enter a number: ";
    cin >> n;

    cout << "Euler's Totient Function of " << n << ": " << phi(n) << endl;

    cout << "Euler's Totient Function for all numbers from 1 to " << n << ":" << endl;
    vector<int> totients = phi_1_to_n(n);
    for (int i = 1; i <= n; i++)
    {
        cout << "φ(" << i << ") = " << totients[i] << endl;
    }

    return 0;
}
