// Newton Raphson Method to find sqaure root of a number
#include <bits/stdc++.h>
using namespace std;

int binary_search_sqrt(int num)
{
    int left = 0;
    int right = num;
    int ans = 0;
    while (left <= right)
    {
        int mid = (left + right) >> 1;
        if (1LL * mid * mid <= num)
        {
            ans = mid;
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return ans;
}

double sqrt_newton(double n)
{
    const double eps = 1e-15; // precision
    double x = 1;             // initial guess
    for (;;)
    {
        double nx = (x + n / x) / 2; // Newton iteration
        if (abs(x - nx) < eps)
            break; // stop when change is very small
        x = nx;
    }
    return x;
}

int main()
{
    double n = 10.0;
    cout << fixed << setprecision(15); // show 15 digits after decimal
    cout << "Square root of " << n << " = " << sqrt_newton(n) << "\n";
    return 0;
}
// The above code implements the Newton-Raphson method to find the square root of a number `n` with high precision. The `binary_search_sqrt` function is a helper function that uses binary search to find the integer part of the square root, but it is not used in the main function. The `sqrt_newton` function performs the Newton-Raphson iteration until the change in value is less than a specified epsilon, ensuring a precise result.
// The main function demonstrates the usage of the `sqrt_newton` function by calculating and printing the square root of 10 with 15 decimal places of precision.
// Note that the `binary_search_sqrt` function can be used to find the integer part of the square root if needed, but in this implementation, we directly use the Newton-Raphson method for a more accurate result.
// The code is written in C++14 and uses standard libraries for input/output and mathematical operations.
// Time Complexity: O(log(n)) for the binary search part and O(log(1/eps)) for the Newton-Raphson iteration, where `eps` is the precision. Overall, the method is efficient for finding square roots with high precision.
// Space Complexity: O(1) as we are using only a constant amount of extra space for variables.
// Example Output:
// Square root of 10.000000000000000 = 3.162277660168380
