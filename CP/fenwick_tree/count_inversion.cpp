#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
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
                count += (mid - i + 1); // All remaining elements in left half are greater
            }
        }

        while (i <= mid)
            temp.push_back(nums[i++]);
        while (j <= right)
            temp.push_back(nums[j++]);

        for (int k = 0; k <= temp.size(); ++k)
            nums[k + left] = temp[k];

        return count;
    }

    long long countInversions(vector<int> &nums)
    {
        return mergeSort(nums, 0, nums.size() - 1);
    }
};

int main()
{
    vector<int> arr = {2, 4, 1, 3, 5};
    Solution sol;
    cout << "Number of inversions: " << sol.countInversions(arr) << endl;
    return 0;
}
