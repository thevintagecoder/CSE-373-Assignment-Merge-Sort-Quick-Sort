// Leetcode 88. Merge Sorted Array:


//Concept of in-place algorithm

//Lets say I am merging two hard-drives, and I can merge them only in hardware A

//The lists are already sorted 

//we cannot use any temporary hard-drive  here

//we cannot start from the first as it would mean shifting from one place to another which is complex

//that is why we merge from the back

//since 1st array already has empty spaces, it wont be an issue

//This ensures we never overwrite a file that we still need to compare

//That is why it is called n-place reverse merge


//we will use three pointers here: p1 (Last file in nums1), p2 (Last file in nums2)
//and p (Last spot in the merged list nums1)

//m is mentioned in the problem



#include <iostream>
#include <vector>
#include <algorithm> 


using namespace std;


void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {

    // 1. Initializing the three pointers

    // p1: Points to the last actual element of nums1
    int p1 = m - 1;
    
    // p2: Points to the last element of nums2
    int p2 = n - 1;
    
    // p: Points to the last position of the final merged array in nums1
    int p = m + n - 1;

    // 2. Core Loop will continue as long as there are elements left in nums2 to be merged.
    // We only need to ensure nums2 is fully merged; if nums1 still has elements, 
    // they are already in their correct relative position at the front of the array.


    while (p2 >= 0) {
        
        // this checks if there are still elements in the *initialized* part of nums1 AND
        // if the current element in nums1 is GREATER than the current element in nums2.
        if (p1 >= 0 && nums1[p1] > nums2[p2]) {
            
            // Case 1: nums1 has the larger element. Place it at the current empty spot (p).
            nums1[p] = nums1[p1];
            p1--; // Moves the nums1 pointer back
            
        } else {
            
            // Case 2: nums2 has the larger (or equal) element, OR nums1 is exhausted (p1 < 0).
            // Places the nums2 element at the current empty spot (p).
            nums1[p] = nums2[p2];
            p2--; // Moves the nums2 pointer back
        }
        
        // In either case, move the destination pointer back one spot.
        p--;
    }
}

// Main function to demonstrate the solution
int main() {
    // --- Example 1 ---
    vector<int> nums1_1 = {1, 2, 3, 0, 0, 0};
    int m1 = 3;
    vector<int> nums2_1 = {2, 5, 6};
    int n1 = 3;

    cout << "--- Example 1 ---" << endl;
    cout << "Before merge: nums1 = [1, 2, 3, 0, 0, 0], nums2 = [2, 5, 6]" << endl;
    merge(nums1_1, m1, nums2_1, n1);
    
    cout << "After merge: [";
    for (size_t i = 0; i < nums1_1.size(); ++i) {
        cout << nums1_1[i];
        if (i < nums1_1.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << " (Expected: 1, 2, 2, 3, 5, 6)" << endl;
    
    cout << "---------------------------" << endl;

    // --- Example 2: Edge Case (Empty nums1) ---
    vector<int> nums1_2 = {0}; // Needs to be size 1 (m+n)
    int m2 = 0;
    vector<int> nums2_2 = {1};
    int n2 = 1;

    cout << "--- Example 2 (Edge Case: Empty nums1) ---" << endl;
    cout << "Before merge: nums1 = [0], m=0, nums2 = [1], n=1" << endl;
    merge(nums1_2, m2, nums2_2, n2);

    cout << "After merge: [";
    for (size_t i = 0; i < nums1_2.size(); ++i) {
        cout << nums1_2[i];
        if (i < nums1_2.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << " (Expected: 1)" << endl;

    return 0;
}