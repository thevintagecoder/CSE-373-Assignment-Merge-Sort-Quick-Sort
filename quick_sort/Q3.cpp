#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>


using namespace std;


int partition(vector<int>& nums, int low, int high) {
    // Picking a random index for the pivot
    int random_index = low + (rand() % (high - low + 1));

    // Swapping the randomly chosen pivot to the end
    swap(nums[random_index], nums[high]);

    // Setting the pivot as the element now at the high index
    int pivot = nums[high];

    // This index is keeping track of the elements smaller than the pivot
    int i = low;

    // Looping through the array segment from the low index to one before the pivot
    for (int j = low; j < high; j++) {
        // Checking if the current element is smaller than the pivot
        if (nums[j] <= pivot) {
            // Swapping the smaller element to the left side
            swap(nums[i], nums[j]);

            // Moving the boundary for smaller elements
            i++;
        }
    }

    // Swapping the pivot into its final sorted position
    swap(nums[i], nums[high]);

    // Returning the final index of the pivot
    return i;
}


 // Implementing the Quickselect algorithm to find the element at the target index (k_prime).
 
int quickSelect(vector<int>& nums, int low, int high, int k_prime) {
    // The main loop is continuing until the low index meets the high index
    while (low <= high) {
        // Partitioning the current segment and getting the pivot's final index
        int pivotIndex = partition(nums, low, high);

        // Checking if the pivot is exactly at the target index we are looking for
        if (pivotIndex == k_prime) {
            // Returning the element at the target index
            return nums[pivotIndex];
        }

        // Checking if the pivot is positioned before the target index
        if (pivotIndex < k_prime) {
            // Discarding the left side and continuing the search on the right side
            low = pivotIndex + 1;
        }
        
        // The pivot is positioned after the target index
        else {
            // Discarding the right side and continuing the search on the left side
            high = pivotIndex - 1;
        }
    }

    // This line is a fallback and should not be reached in a correct implementation
    return -1; 
}

/**
 * Main function to find the Kth largest element.
 */
int findKthLargest(vector<int>& nums, int k) {
    // Initializing the random seed based on current time for randomization
    srand(time(0));

    // Calculating the target index (k_prime) for the k-th largest element.
    // k_prime = (n - k) is the 0-based index if the array was sorted ascending.
    int n = nums.size();
    int k_prime = n - k;

    // Calling the Quickselect method on the full array
    return quickSelect(nums, 0, n - 1, k_prime);
}

// Example usage
int main() {
    // Example 1: nums = [3, 2, 1, 5, 6, 4], k = 2
    vector<int> nums1 = {3, 2, 1, 5, 6, 4};
    int k1 = 2;
    int result1 = findKthLargest(nums1, k1);
    cout << "Input: [3, 2, 1, 5, 6, 4], k = 2" << endl;
    cout << "The " << k1 << "th largest element is: " << result1 << endl;

    cout << "--------------------" << endl;

    // Example 2: nums = [3, 2, 3, 1, 2, 4, 5, 5, 6], k = 4
    vector<int> nums2 = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    int k2 = 4;
    int result2 = findKthLargest(nums2, k2);
    cout << "Input: [3, 2, 3, 1, 2, 4, 5, 5, 6], k = 4" << endl;
    cout << "The " << k2 << "th largest element is: " << result2 << endl;

    return 0;
}