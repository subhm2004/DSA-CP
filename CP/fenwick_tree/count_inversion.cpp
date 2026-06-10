#include <iostream>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// INVERSION COUNT — Merge Sort Approach (BIT nahi, comparison method)
// ────────────────────────────────────────────────────────────────────────────
// Inversion = pair (i, j) jahan i < j lekin arr[i] > arr[j]
// Merge sort ke time jab right half ka element pehle aaye,
// matlab left me jitne bache hain sab usse bade hain -> inversion count.
// ════════════════════════════════════════════════════════════════════════════

class Solution
{
public:
    // ── mergeSort: divide & conquer inversion count ──
    //   1) base case: left >= right to 0 return — ek element me inversion nahi
    //   2) mid nikalo, left half [left..mid] aur right [mid+1..right] recursively sort + count
    //   3) dono halves ke inversion counts add karo
    //   4) merge() call karo — yahan cross-half inversions count hote hain
    long long mergeSort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return 0;

        int mid = left + (right - left) / 2;
        long long count = 0;

        count += mergeSort(nums, left, mid);
        count += mergeSort(nums, mid + 1, right);
        count += merge(nums, left, mid, right);

        return count;
    }

    // ── merge: do sorted halves merge karo, inversion count karo ──
    //   1) i = left half start, j = right half start; temp array me merge karo
    //   2) agar nums[i] <= nums[j] to left element pehle daalo — koi inversion nahi
    //   3) warna nums[j] chhota hai left ke bache sab se — count += (mid - i + 1)
    //   4) bache elements temp me daalo, phir nums[left..right] me copy back
    long long merge(vector<int> &nums, int left, int mid, int right)
    {
        vector<int> temp;
        int i = left, j = mid + 1;
        long long count = 0;

        while (i <= mid && j <= right)
        {
            if (nums[i] <= nums[j])
            {
                temp.push_back(nums[i++]);
            }
            else
            {
                temp.push_back(nums[j++]);
                count += (mid - i + 1);  // left me [i..mid] sab nums[j] se bade = inversions
            }
        }

        while (i <= mid)
            temp.push_back(nums[i++]);
        while (j <= right)
            temp.push_back(nums[j++]);

        for (int k = 0; k < (int)temp.size(); ++k)
            nums[k + left] = temp[k];

        return count;
    }

    // ── countInversions: wrapper — poori array ke inversions ──
    //   1) mergeSort ko poori array [0..n-1] pe call karo
    //   2) return value = total inversion count
    //   3) array sorted bhi ho jaati hai as side effect
    long long countInversions(vector<int> &nums)
    {
        return mergeSort(nums, 0, nums.size() - 1);
    }
};

// ── main: sample array pe inversion count print ──
int main()
{
    vector<int> arr = {2, 4, 1, 3, 5};
    Solution sol;
    cout << "Number of inversions: " << sol.countInversions(arr) << endl;
    return 0;
}
