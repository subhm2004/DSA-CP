#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
using namespace std;

// Function to calculate Euler's Totient Function
int eulerTotient(int n)
{
    int result = n;
    for (int i = 2; i * i <= n; ++i)
    {
        if (n % i == 0)
        {
            // If i is a divisor of n, then subtract multiples of i
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    // If n is a prime number greater than 1
    if (n > 1)
        result -= result / n;

    return result;
}

// Function to calculate a^b % mod using exponentiation by squaring
int modExp(int a, int b, int mod)
{
    int result = 1;
    a = a % mod; // To handle cases where a >= mod

    while (b > 0)
    {
        if (b % 2 == 1) // If b is odd, multiply by a
            result = (result * a) % mod;
        a = (a * a) % mod; // Square the base
        b /= 2;            // Reduce exponent by half
    }

    return result;
}

// Function to verify Euler's Theorem: a^phi(n) % n == 1 if gcd(a, n) == 1
bool eulerTheorem(int a, int n)
{
    // Compute Euler's Totient function
    int phi_n = eulerTotient(n);

    // Check if gcd(a, n) == 1
    if (std::gcd(a, n) == 1)
    {
        // Verify Euler's Theorem: a^phi(n) % n should be 1
        int result = modExp(a, phi_n, n);
        return result == 1;
    }
    else
    {
        return false; // If a and n are not coprime, Euler's Theorem does not apply
    }
}

int main()
{
    int a, n;
    cout << "Enter two numbers (a and n): ";
    cin >> a >> n;

    if (eulerTheorem(a, n))
    {
        cout << "Euler's Theorem holds: a^φ(n) ≡ 1 (mod n)" << endl;
    }
    else
    {
        cout << "Euler's Theorem does not hold" << endl;
    }

    return 0;
}
