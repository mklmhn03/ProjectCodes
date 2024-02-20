#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <cassert>

using namespace std;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> nextGreater;
        stack<int> s;

        for (int num : nums2) {
            while (!s.empty() && s.top() < num) {
                nextGreater[s.top()] = num;
                s.pop();
            }
            s.push(num);
        }

        vector<int> result;
        result.reserve(nums1.size());

        for (int num : nums1) {
            if (auto it = nextGreater.find(num); it != nextGreater.end()) {
                result.push_back(it->second);
            } else {
                result.push_back(-1);
            }
        }

        return result;
    }
};

int main() {
    Solution solution;
    
    // Test Case 1: Regular case with positive integers
    vector<int> nums1 = {4, 1, 2};
    vector<int> nums2 = {1, 3, 4, 2};
    vector<int> expected1 = {-1, 3, -1};
    vector<int> result1 = solution.nextGreaterElement(nums1, nums2);
    assert(result1 == expected1);

    // Test Case 2: nums1 and nums2 both empty
    vector<int> empty1, empty2;
    vector<int> expected2;
    vector<int> result2 = solution.nextGreaterElement(empty1, empty2);
    assert(result2 == expected2);

    // Test Case 3: nums1 empty, nums2 non-empty
    vector<int> empty3;
    vector<int> nums3 = {1, 2, 3};
    vector<int> expected3;
    vector<int> result3 = solution.nextGreaterElement(empty3, nums3);
    assert(result3 == expected3);

    // Test Case 4: nums1 non-empty, nums2 empty
    vector<int> nums4 = {4, 3, 2};
    vector<int> empty4;
    vector<int> expected4 = {-1, -1, -1};
    vector<int> result4 = solution.nextGreaterElement(nums4, empty4);
    assert(result4 == expected4);

    // Test Case 5: All elements in nums2 are greater
    vector<int> nums5 = {1, 2, 3, 4};
    vector<int> nums6 = {5, 6, 7, 8};
    vector<int> expected5 = {-1, -1, -1, -1};
    vector<int> result5 = solution.nextGreaterElement(nums5, nums6);
    assert(result5 == expected5);

    // Test Case 6: All elements in nums2 are smaller
    vector<int> nums7 = {1, 2, 3, 4};
    vector<int> nums8 = {0, -1, -2, -3};
    vector<int> expected6 = {-1, -1, -1, -1};
    vector<int> result6 = solution.nextGreaterElement(nums7, nums8);
    assert(result6 == expected6);

    cout << "All test cases passed!" << endl;
    return 0;
}
