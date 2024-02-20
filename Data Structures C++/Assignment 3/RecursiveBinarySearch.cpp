#include <iostream>
#include <vector>
#include <cassert>

int binarySearch(const std::vector<int>& arr, int target, int left, int right) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int midVal = arr[mid];

        if (midVal == target) {
            if (mid == 0 || arr[mid - 1] != target) return mid;
            else right = mid - 1;
        }
        else if (midVal < target) left = mid + 1;
        else right = mid - 1;
    }

    return -1;
}

int recursiveBinarySearch(const std::vector<int>& arr, int target) {
    return binarySearch(arr, target, 0, arr.size() - 1);
}

int main() {
    std::vector<int> arr1 = {1, 3, 5, 7, 9, 11, 13, 15}; // Sorted vector

    // Test cases
    assert(recursiveBinarySearch(arr1, 7) == 3);  // Target is in the middle
    assert(recursiveBinarySearch(arr1, 1) == 0);  // Target is at the beginning
    assert(recursiveBinarySearch(arr1, 15) == 7); // Target is at the end
    assert(recursiveBinarySearch(arr1, 8) == -1); // Target does not exist

    std::vector<int> arr2 = {2, 4, 6, 6, 8, 10, 10}; // Sorted vector with duplicates

    // Test cases with duplicates
    assert(recursiveBinarySearch(arr2, 6) == 2);   // Target is in the middle of duplicates
    assert(recursiveBinarySearch(arr2, 2) == 0);   // Target is at the beginning
    assert(recursiveBinarySearch(arr2, 10) == 5);  // Target is at the end of duplicates
    assert(recursiveBinarySearch(arr2, 7) == -1);  // Target does not exist

    // Edge cases
    std::vector<int> arr3 = {}; // Empty vector

    assert(recursiveBinarySearch(arr3, 5) == -1);  // Target does not exist in an empty vector

    std::vector<int> arr4 = {5}; // Single element vector

    assert(recursiveBinarySearch(arr4, 5) == 0);   // Target is the only element

    std::vector<int> arr5 = {1, 1, 1, 1}; // Vector with all elements the same

    assert(recursiveBinarySearch(arr5, 1) == 0);  // Target is in the middle of duplicates

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}