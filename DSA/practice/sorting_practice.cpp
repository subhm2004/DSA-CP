/*
 * ============================================================================
 * TOPIC    : Practice
 * FILE     : sorting_practice.cpp
 * PROBLEM  : Sorting Practice
 * ABOUT    : General practice and mixed problems
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

class MergeSort
{
public:
    
    
    /*
     * sort()
     * Purpose : Standard DSA solution for this problem.
     * Params  : vector<int> &nums
     * Returns : void
     */
    void sort(vector<int> &nums)
    {
        mergeSort(nums, 0, nums.size() - 1);
    }

private:
    
    
    /*
     * mergeSort()
     * Purpose : Standard DSA solution for this problem.
     * Params  : vector<int> &nums, int low, int high
     * Returns : void
     */
    void mergeSort(vector<int> &nums, int low, int high)
    {
        if (low >= high)
            return;

        int mid = (low + high) / 2;
        mergeSort(nums, low, mid);
        mergeSort(nums, mid + 1, high);
        merge(nums, low, mid, high);
    }

    
    
    /*
     * merge()
     * Purpose : Standard DSA solution for this problem.
     * Params  : vector<int> &nums, int low, int mid, int high
     * Returns : void
     */
    void merge(vector<int> &nums, int low, int mid, int high)
    {
        vector<int> temp;
        int left = low, right = mid + 1;

        while (left <= mid && right <= high)
        {
            if (nums[left] <= nums[right])
                temp.push_back(nums[left++]);
            else
                temp.push_back(nums[right++]);
        }

        while (left <= mid)
            temp.push_back(nums[left++]);
        while (right <= high)
            temp.push_back(nums[right++]);

        for (int i = 0; i < (int)temp.size(); ++i)
        {
            nums[low + i] = temp[i];
        }
    }
};

class QuickSort
{
public:
    
    
    /*
     * sort()
     * Purpose : Standard DSA solution for this problem.
     * Params  : vector<int> &nums
     * Returns : void
     */
    void sort(vector<int> &nums)
    {
        quickSort(nums, 0, nums.size() - 1);
    }

private:
    
    
    /*
     * partition()
     * Purpose : Standard DSA solution for this problem.
     * Params  : vector<int> &nums, int low, int high
     * Returns : int
     */
    int partition(vector<int> &nums, int low, int high)
    {
        int pivot = nums[high];
        int i = low - 1;

        for (int j = low; j < high; j++)
        {
            if (nums[j] <= pivot)
            {
                i++;
                swap(nums[i], nums[j]);
            }
        }
        swap(nums[i + 1], nums[high]);
        return i + 1;
    }

    
    
    /*
     * quickSort()
     * Purpose : Standard DSA solution for this problem.
     * Params  : vector<int> &nums, int low, int high
     * Returns : void
     */
    void quickSort(vector<int> &nums, int low, int high)
    {
        if (low < high)
        {
            int pi = partition(nums, low, high);
            quickSort(nums, low, pi - 1);
            quickSort(nums, pi + 1, high);
        }
    }
};

class HeapSort
{
public:
    
    
    /*
     * sort()
     * Purpose : Standard DSA solution for this problem.
     * Params  : vector<int> &nums
     * Returns : void
     */
    void sort(vector<int> &nums)
    {
        int n = nums.size();

        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(nums, n, i);

        for (int i = n - 1; i > 0; i--)
        {
            swap(nums[0], nums[i]);
            heapify(nums, i, 0);
        }
    }

private:
    
    
    /*
     * heapify()
     * Purpose : Build heap; repeatedly extract min/max.
     * Params  : vector<int> &nums, int n, int i
     * Returns : void
     */
    void heapify(vector<int> &nums, int n, int i)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && nums[left] > nums[largest])
            largest = left;
        if (right < n && nums[right] > nums[largest])
            largest = right;

        if (largest != i)
        {
            swap(nums[i], nums[largest]);
            heapify(nums, n, largest);
        }
    }
};

class CountSort
{
public:
    
    
    /*
     * sort()
     * Purpose : Standard DSA solution for this problem.
     * Params  : vector<int> &nums
     * Returns : void
     */
    void sort(vector<int> &nums)
    {
        if (nums.empty())
            return;

        int maxVal = *max_element(nums.begin(), nums.end());
        int minVal = *min_element(nums.begin(), nums.end());
        int range = maxVal - minVal + 1;

        vector<int> count(range, 0);

        for (int num : nums)
        {
            count[num - minVal]++;
        }

        int index = 0;
        for (int i = 0; i < range; ++i)
        {
            while (count[i]-- > 0)
            {
                nums[index++] = i + minVal;
            }
        }
    }
};

class Solution
{
public:
    
    
    /*
     * sortArray()
     * Purpose : Standard DSA solution for this problem.
     * Params  : vector<int> &nums
     * Returns : vector<int>
     */
    vector<int> sortArray(vector<int> &nums)
    {
        MergeSort sorter;

        sorter.sort(nums);
        return nums;
    }
};



/*
 * main()
 * Purpose : Entry point — demo/test for Sorting Practice
 */
int main()
{
    Solution solution;
    vector<int> nums = {5, 2, 9, 1, 5, 6};

    cout << "Original array: ";
    for (int num : nums)
        cout << num << " ";
    cout << "\n";

    vector<int> sorted = solution.sortArray(nums);

    cout << "Sorted array: ";
    for (int num : sorted)
        cout << num << " ";
    cout << "\n";

    return 0;
}
