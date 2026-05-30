#include <bits/stdc++.h>
using namespace std;

class PrefixSum2D
{
public:
    int n, m;
    vector<vector<int>> prefix; // prefix sum matrix

    PrefixSum2D(vector<vector<int>> &arr)
    {
        n = arr.size();
        m = arr[0].size();
        prefix.assign(n + 1, vector<int>(m + 1, 0));

        // build prefix sum (1-indexed)
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                prefix[i][j] = arr[i - 1][j - 1] + prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
            }
        }
    }

    // get sum of rectangle (a,b) to (c,d), inclusive
    // NOTE: (a,b) and (c,d) are 1-indexed
    int getSum(int a, int b, int c, int d)
    {
        return prefix[c][d] - prefix[a - 1][d] - prefix[c][b - 1] + prefix[a - 1][b - 1];
    }
};

int main()
{
    vector<vector<int>> arr = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}};

    PrefixSum2D ps(arr);

    // Example queries
    cout << "Sum (2,2) to (4,4) = " << ps.getSum(2, 2, 4, 4) << "\n";
    cout << "Sum (1,1) to (5,5) = " << ps.getSum(1, 1, 5, 5) << "\n";
    cout << "Sum (3,3) to (5,5) = " << ps.getSum(3, 3, 5, 5) << "\n";

    return 0;
}
