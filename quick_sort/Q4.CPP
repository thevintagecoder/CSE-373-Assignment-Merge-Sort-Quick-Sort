#include <iostream>
#include <vector>
#include <algorithm> // Includes the swap function

// Using the standard namespace for simplicity
using namespace std;


void sortColors(vector<int>& nums) {
    // Initializing the 'low' pointer for the next 0
    int low = 0;
    
    // Initializing the 'high' pointer for the next 2
    int high = nums.size() - 1;
    
    // Initializing the 'mid' pointer for the current element being checked
    int mid = 0;

    // Looping while the mid pointer has not crossed the high pointer
    while (mid <= high) {
        // Checking if the current element is 0 (Red)
        if (nums[mid] == 0) {
            // Swapping the current element with the element at the low index
            swap(nums[low], nums[mid]);
            
            // Moving the low boundary one step to the right
            low++;
            
            // Moving the mid pointer to check the next element
            mid++;
        } 
        // Checking if the current element is 1 (White)
        else if (nums[mid] == 1) {
            // Only moving the mid pointer forward since 1 is in place
            mid++;
        } 
        // The current element must be 2 (Blue)
        else { 
            // Swapping the current element with the element at the high index
            swap(nums[mid], nums[high]);
            
            // Moving the high boundary one step to the left
            high--;
            
            // Not moving the mid pointer as the swapped element needs inspection
        }
    }
}

// Main function to run the example independently
int main() {
    // Creating a vector representing the unsorted colors
    vector<int> colors = {2, 0, 2, 1, 1, 0, 2, 1, 0, 0, 2};
    
    // Printing the array before sorting for confirmation
    cout << "Original Colors: ";
    for (int color : colors) {
        cout << color << " ";
    }
    cout << endl;

    // Calling the function to sort the colors in-place
    sortColors(colors);

    // Printing the array after sorting to see the result
    cout << "Sorted Colors:   ";
    for (int color : colors) {
        cout << color << " ";
    }
    cout << endl;

    return 0;
}