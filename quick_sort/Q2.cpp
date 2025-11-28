#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>

using namespace std;

// This function is swapping two elements in the array
void swap(int& a, int& b) {
    int t = a;
    a = b;
    b = t;
}

// This function is partitioning the array around a pivot element
int partition(vector<int>& nums, int low, int high) {
    int pivot = nums[high]; // Choosing the last element as the pivot
    int i = (low - 1);      // Index for the smaller element

    // Looping through all elements from low to high-1
    for (int j = low; j <= high - 1; j++) {
        // Checking if the current element is smaller than the pivot
        if (nums[j] < pivot) {
            i++; // Incrementing the index of the smaller element
            swap(nums[i], nums[j]); // Swapping the current element with the element at i
        }
    }
    swap(nums[i + 1], nums[high]); // Swapping the pivot element into its correct sorted position
    return (i + 1); // Returning the partitioning index
}

// This function is implementing the QuickSort algorithm
void quickSort(vector<int>& nums, int low, int high) {
    // Checking if the low index is less than the high index
    if (low < high) {
        // Getting the partition index
        int pi = partition(nums, low, high);

        // Recursively sorting the elements before the partition
        quickSort(nums, low, pi - 1);
        // Recursively sorting the elements after the partition
        quickSort(nums, pi + 1, high);
    }
}

// This is the main function finding the maximum product of three numbers
long long maximumProduct(vector<int>& nums) {
    int n = nums.size();
    
    // Starting the QuickSort process to sort the array
    quickSort(nums, 0, n - 1);

    // After sorting, the potential candidates for maximum product are found at the ends

    // Candidate 1: Product of the three largest numbers
    // This is calculating the product of the last three elements (the largest positive numbers)
    long long candidate1 = (long long)nums[n - 1] * nums[n - 2] * nums[n - 3];

    // Candidate 2: Product of the two smallest and the single largest number
    // This is calculating the product of the first two elements (most negative numbers) and the last element
    long long candidate2 = (long long)nums[0] * nums[1] * nums[n - 1];

    // Comparing the two candidates to find the overall maximum product
    if (candidate1 > candidate2) {
        return candidate1;
    } else {
        return candidate2;
    }
}

int main() {
    // Creating a vector of integers for testing the function
    vector<int> nums1 = {1, 2, 3};
    // Printing the result for the first test case
    cout << "Input: {1, 2, 3}" << endl;
    cout << "Maximum Product: " << maximumProduct(nums1) << endl; 

    // Creating a second test case with negative numbers
    vector<int> nums2 = {-10, -5, 1, 2, 3};
    // Printing the result for the second test case
    cout << "Input: {-10, -5, 1, 2, 3}" << endl;
    cout << "Maximum Product: " << maximumProduct(nums2) << endl; 

    // Creating a third test case with all negative numbers
    vector<int> nums3 = {-1, -2, -3, -4};
    // Printing the result for the third test case
    cout << "Input: {-1, -2, -3, -4}" << endl;
    cout << "Maximum Product: " << maximumProduct(nums3) << endl; 

    return 0; // Returning 0 to indicate successful execution
}