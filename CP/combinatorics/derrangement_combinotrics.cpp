#include <iostream>
#include <chrono>

using namespace std;

int derangement(int n)
{
    if (n == 0)
    {
        return 1;
    }
    else if (n == 1)
    {
        return 0;
    }
    else
    {
        return (n - 1) * (derangement(n - 1) + derangement(n - 2));
    }
}

int main()
{
    int n;
    cout << "Enter the value of n: ";
    cin >> n;

    // Start measuring time
    auto start = chrono::high_resolution_clock::now();

    int result = derangement(n);

    // Stop measuring time
    auto end = chrono::high_resolution_clock::now();

    // Calculate the elapsed time in microseconds
    chrono::duration<double, micro> execution_time = end - start;

    cout << "Derangement of " << n << " is: " << result << endl;
    cout << "Execution time: " << execution_time.count() << " microseconds" << endl;

    return 0;
}
