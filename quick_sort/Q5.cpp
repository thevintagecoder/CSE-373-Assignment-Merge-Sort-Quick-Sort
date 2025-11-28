#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

// Using namespace std for convenience as requested
using namespace std;

// This is calculating the square of the Euclidean distance from the origin (0, 0)
// We are skipping the sqrt function because the relative order is the same
long long calculateDistanceSquared(const vector<int>& point) {
    // Calculating the x-coordinate squared
    long long x_sq = (long long)point[0] * point[0];
    // Calculating the y-coordinate squared
    long long y_sq = (long long)point[1] * point[1];
    // Returning the sum of the squares
    return x_sq + y_sq;
}

// This function is for partitioning the array around a pivot element
int partition(vector<vector<int>>& points, int low, int high, long long pivotDistance) {
    // Initializing the index for the element that is less than the pivot distance
    int i = low;
    
    // We are iterating through all elements from the start to the end of the partition
    for (int j = low; j <= high; ++j) {
        // Calculating the distance squared for the current point
        long long currentDistance = calculateDistanceSquared(points[j]);
        
        // Checking if the current point's distance is less than the pivot's distance
        if (currentDistance < pivotDistance) {
            // Swapping the current point with the point at index i
            swap(points[i], points[j]);
            // Moving the index i forward to mark the new boundary of the "less than" partition
            i++;
        }
    }
    
    // The index i now points to the first element greater than or equal to the pivot's distance
    // This function is returning the final position of the partition boundary
    return i;
}

// This is the core Quickselect function to find the K-th smallest element
void quickselect(vector<vector<int>>& points, int low, int high, int k) {
    // The base case is when the search range is invalid or we found the element
    if (low >= high) {
        // Returning from the function if the range is empty or a single element
        return;
    }

    // Creating a random number generator engine
    random_device rd;
    // Seeding the engine with a random device
    mt19937 gen(rd());
    // Defining the distribution to pick a pivot index randomly within the range
    uniform_int_distribution<> distrib(low, high);
    // Selecting a random pivot index within the current range
    int pivotIndex = distrib(gen);

    // Swapping the random pivot element to the end of the current range for simplicity
    swap(points[pivotIndex], points[high]);
    
    // Calculating the distance squared of the chosen pivot
    long long pivotDistance = calculateDistanceSquared(points[high]);

    // Partitioning the array and getting the final index of the pivot boundary
    // The partition moves all elements < pivotDistance to the left side
    int partitionIndex = partition(points, low, high - 1, pivotDistance);
    
    // Swapping the pivot element from the end to its correct sorted position
    swap(points[partitionIndex], points[high]);

    // Now, points[partitionIndex] is at its correct, final sorted position
    // The index 'partitionIndex' represents how many elements are smaller than the pivot
    
    // Checking if the partition index is exactly where we need the K-th element
    if (partitionIndex == k) {
        // If it is, we are done with the search
        return;
    } 
    
    // Checking if the K-th element is in the left subarray (meaning the pivot is too large)
    if (partitionIndex > k) {
        // Recursing on the left side of the pivot
        quickselect(points, low, partitionIndex - 1, k);
    } 
    
    // If the K-th element is not in the left side, it must be in the right side
    if (partitionIndex < k) {
        // Recursing on the right side of the pivot
        quickselect(points, partitionIndex + 1, high, k);
    }
}

// This is the main function exposed to solve the problem
vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
    // Starting the Quickselect process on the entire array from index 0 to size - 1
    // The function modifies the 'points' vector in place
    quickselect(points, 0, points.size() - 1, k);

    // The first K elements are now the K closest points
    // We are returning a new vector containing only the first K elements
    return vector<vector<int>>(points.begin(), points.begin() + k);
}

// The main function for running the code independently
int main() {
    // Setting up the vector of points as the input
    vector<vector<int>> points = {{1, 3}, {-2, 2}, {5, 8}, {0, 1}};
    // Defining the number of closest points we want to find
    int k = 2;

    // Printing the initial list of points
    cout << "Original Points:" << endl;
    // Iterating through the points to display them
    for (const auto& p : points) {
        // Displaying each point's coordinates
        cout << "(" << p[0] << ", " << p[1] << ") ";
    }
    // Printing a newline for separation
    cout << endl;

    // Calling the function to find the K closest points
    vector<vector<int>> closestPoints = kClosest(points, k);

    // Printing the result
    cout << "\nThe " << k << " closest points to the origin are:" << endl;
    // Iterating through the resulting closest points
    for (const auto& p : closestPoints) {
        // Displaying each closest point
        cout << "(" << p[0] << ", " << p[1] << ") ";
    }
    // Printing a final newline
    cout << endl;

    
    return 0;
}