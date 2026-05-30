#include <bits/stdc++.h>
using namespace std;

// arr ke range [L, R] mein Kth smallest element dhundo
int kthSmallest(vector<int>& arr, int L, int R, int K) {
    // Us range ke elements ek alag vector mein lo
    vector<int> temp(arr.begin() + L, arr.begin() + R + 1);
    
    // Sort kar do
    sort(temp.begin(), temp.end());
    
    // Kth smallest matlab index K-1 (1-indexed hai K)
    return temp[K - 1];
}

int main() {
    vector<int> arr = {5, 1, 2, 3, 4};

    cout << kthSmallest(arr, 0, 4, 3) << endl; // 3
    cout << kthSmallest(arr, 1, 4, 2) << endl; // 2
    cout << kthSmallest(arr, 0, 2, 1) << endl; // 1
}
