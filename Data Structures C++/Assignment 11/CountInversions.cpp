#include <iostream>
#include <vector>
#include <algorithm> // For copy

int mergeInv(std::vector<int>& nums, std::vector<int>& left, std::vector<int>& right) {
    int i = 0, j = 0, count = 0;
    while (i < left.size() || j < right.size()) {
        if (i == left.size()) {
            nums[i + j] = right[j];
            j++;
        } else if (j == right.size()) {
            nums[i + j] = left[i];
            i++;
        } else if (left[i] <= right[j]) {
            nums[i + j] = left[i];
            i++;
        } else {
            nums[i + j] = right[j];
            j++;
            // Count inversions: all remaining elements in left are greater than the current element in right
            count += left.size() - i;
        }
    }
    return count;
}

int countInv(std::vector<int>& nums) {
    // Base case - one element, nothing to sort
    if (nums.size() > 1) {
        int mid = nums.size() / 2;
        std::vector<int> left(nums.begin(), nums.begin() + mid);
        std::vector<int> right(nums.begin() + mid, nums.end());

        int numInvLeft = countInv(left);
        int numInvRight = countInv(right);
        int numInvMerge = mergeInv(nums, left, right);

        return numInvLeft + numInvRight + numInvMerge;
    }
    return 0;
}

int main() {
    int n;
    std::vector<int> numvec{4, 5, 6, 1, 2, 3};
    n = countInv(numvec);
    std::cout << "Number of inversions " << n << std::endl; // Should be 9

    numvec = {1, 2, 3, 4, 5, 6};
    n = countInv(numvec);
    std::cout << "Number of inversions " << n << std::endl; // Should be 0

    numvec = {6, 5, 4, 3, 2, 1};
    n = countInv(numvec);
    std::cout << "Number of inversions " << n << std::endl; // Should be 15

    numvec = {0, 0, 0, 0, 0, 0};
    n = countInv(numvec);
    std::cout << "Number of inversions " << n << std::endl; // Should be 0
}
