#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
private:
    
    int partition(vector<int>& arr, int left, int right) {
        // Taking the last element as the pivot
        int pivotValue = arr[right];
        // i is keeping track of the position for the next element smaller than the pivot
        int i = left - 1;

        // Looping through all elements in the current range
        for (int j = left; j < right; ++j) {
            // Checking if the current element is smaller than the pivot
            if (arr[j] <= pivotValue) {
                // Moving the position for elements smaller than pivot one step to the right
                i++;
                // Swapping the element into the correct sorted position
                swap(arr[i], arr[j]);
            }
        }

        // Placing the pivot element at its final sorted position
        swap(arr[i + 1], arr[right]);
        // Returning the final index of the pivot
        return i + 1;
    }

    /**
     * The core Quickselect function to find the element at a specific index k.
     * k is the target index in the sorted array.
     */
    int quickselect(vector<int>& arr, int left, int right, int k) {
        // This is the main loop continuing until the element is found
        while (left <= right) {
            // Partitioning the current subarray
            int pivotIndex = partition(arr, left, right);

            // Checking if the pivot is exactly the element I am looking for
            if (pivotIndex == k) {
                // Returning the value at the target index
                return arr[pivotIndex];
            } 
            
            // Checking if the target index is in the left subarray
            if (pivotIndex > k) {
                // Discarding the right subarray and continuing search on the left
                right = pivotIndex - 1;
            } 
            
            // Checking if the target index is in the right subarray
            if (pivotIndex < k) {
                // Discarding the left subarray and continuing search on the right
                left = pivotIndex + 1;
            }
        }
        // This line is theoretically unreachable for valid inputs but C++ requires a return
        return -1;
    }

public:
    int thirdMaximum(vector<int>& nums) {
        // Using a set to automatically handle and remove duplicate numbers
        set<int> uniqueNumsSet(nums.begin(), nums.end());
        // Converting the unique numbers back into a vector for sorting and partitioning
        vector<int> uniqueNums(uniqueNumsSet.begin(), uniqueNumsSet.end());

        // Storing the count of unique numbers
        int n = uniqueNums.size();

        // Checking if there are fewer than three unique numbers
        if (n < 3) {
            // Returning the maximum number, which is the last element after sorting
            return uniqueNums[n - 1];
        }

        // Calculating the index for the 3rd maximum distinct number
        // The array is sorted ascendingly, so the 3rd max is at index N - 3
        int targetIndex = n - 3;
        
        // Calling Quickselect on the unique numbers array
        return quickselect(uniqueNums, 0, n - 1, targetIndex);
    }
};


int main() {
    Solution s;
    vector<int> nums1 = {3, 2, 1}; // Expected: 1
    vector<int> nums2 = {1, 2}; // Expected: 2 (max, since < 3 unique)
    vector<int> nums3 = {2, 2, 3, 1}; // Unique are {1, 2, 3}. Expected: 1

    cout << "Result 1: " << s.thirdMaximum(nums1) << endl;
    cout << "Result 2: " << s.thirdMaximum(nums2) << endl;
    cout << "Result 3: " << s.thirdMaximum(nums3) << endl;

    return 0;
}
