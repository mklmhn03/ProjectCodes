#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

vector<int> targetIndices(vector<int>& nums, int target) {
    vector<int> result;
    sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == target) result.push_back(i);
    }

    return result;
}


int main() {
    // Test Case 1: Basic test case with multiple occurrences of target
    {
        vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
        int target = 5;
        vector<int> expected = {6, 7};  // Indices of '5' after sorting
        assert(targetIndices(nums, target) == expected);
    }

    // Test Case 2: Empty vector
    {
        vector<int> nums;
        int target = 7;
        vector<int> expected = {};  // No occurrences of '7' in an empty vector
        assert(targetIndices(nums, target) == expected);
    }

    // Test Case 3: No occurrence of target
    {
        vector<int> nums = {2, 4, 6, 8, 10};
        int target = 3;
        vector<int> expected = {};  // No occurrences of '3' in the vector
        assert(targetIndices(nums, target) == expected);
    }

    // Test Case 4: All elements are the target
    {
        vector<int> nums = {7, 7, 7, 7, 7};
        int target = 7;
        vector<int> expected = {0, 1, 2, 3, 4};  // Indices of '7' after sorting
        assert(targetIndices(nums, target) == expected);
    }

    cout << "All test cases passed successfully!" << endl;

    return 0;
}