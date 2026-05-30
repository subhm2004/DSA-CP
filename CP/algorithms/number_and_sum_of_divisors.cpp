#include <bits/stdc++.h>
using namespace std;

long long numberOfDivisors(long long num)
{
    long long total = 1;
    for (long long i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            int e = 0;
            while (num % i == 0)
            {
                e++;
                num /= i;
            }
            total *= (e + 1);
        }
    }
    if (num > 1)
        total *= 2; // Remaining prime factor
    return total;
}

long long SumOfDivisors(long long num)
{
    long long total = 1;
    for (long long i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            int e = 0;
            while (num % i == 0)
            {
                e++;
                num /= i;
            }
            long long sum = 1, pow = 1;
            while (e-- >= 0)
            {
                sum += pow;
                pow *= i;
            }
            total *= sum;
        }
    }
    if (num > 1)
        total *= (1 + num);
    return total;
}

int main()
{
    long long num;
    cout << "Enter a number: ";
    cin >> num;

    cout << "Number of divisors of " << num << ": " << numberOfDivisors(num) << endl;
    cout << "Sum of divisors of " << num << ": " << SumOfDivisors(num) << endl;

    return 0;
}
