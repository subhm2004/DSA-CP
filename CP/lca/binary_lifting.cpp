#include <bits/stdc++.h>
using namespace std;

class BinaryLifting
{
    int n, maxLog;
    vector<vector<int>> up; // up[i][j] -> 2^j-th ancestor of node i

public:
    BinaryLifting(int n, vector<int> &parent)
    {
        this->n = n;
        maxLog = log2(n) + 1;
        up.assign(n, vector<int>(maxLog, -1));

        // Initialize immediate parents (2^0-th ancestor)
        for (int i = 0; i < n; i++)
        {
            up[i][0] = parent[i];
        }

        // Compute binary lifting table
        for (int j = 1; j < maxLog; j++)
        {
            for (int i = 0; i < n; i++)
            {
                if (up[i][j - 1] != -1)
                {
                    up[i][j] = up[up[i][j - 1]][j - 1];
                }
            }
        }
    }

    // Find K-th ancestor of node u
    int getKthAncestor(int node, int k)
    {
        for (int j = 0; j < maxLog; j++)
        {
            if (k & (1 << j))
            { // Check if j-th bit is set in K
                node = up[node][j];
                if (node == -1)
                    return -1;
            }
        }
        return node;
    }
};

int main()
{
    int n = 10;
    vector<int> parent = {-1, 0, 0, 1, 1, 2, 2, 3, 3, 4}; // Tree structure

    BinaryLifting bl(n, parent);

    cout << "3rd ancestor of node 9: " << bl.getKthAncestor(9, 3) << endl; // Output: 0
    cout << "2nd ancestor of node 6: " << bl.getKthAncestor(6, 2) << endl; // Output: 0
    cout << "1st ancestor of node 8: " << bl.getKthAncestor(8, 1) << endl; // Output: 3

    return 0;
}
