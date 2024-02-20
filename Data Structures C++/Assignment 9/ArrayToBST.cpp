#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return sortedArrayToBST(nums, 0, nums.size() - 1);
    }

private:
    TreeNode* sortedArrayToBST(vector<int>& nums, int left, int right) {
        if (left > right) return nullptr;

        int mid = left + (right - left) / 2;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = sortedArrayToBST(nums, left, mid - 1);
        root->right = sortedArrayToBST(nums, mid + 1, right);

        return root;
    }
};

void printTree(TreeNode* root) {
    if (root == nullptr) return;
    cout << root->val << " ";
    printTree(root->left);
    printTree(root->right);
}

int main() {
    Solution solution;

    //Case 1: Empty array
    vector<int> nums1 = {};
    TreeNode* root1 = solution.sortedArrayToBST(nums1);
    cout << "Edge Case 1: ";
    printTree(root1);
    cout << endl;

    //Case 2: Single element
    vector<int> nums2 = {7};
    TreeNode* root2 = solution.sortedArrayToBST(nums2);
    cout << "Edge Case 2: ";
    printTree(root2);
    cout << endl;

    //Case 3: Two elements
    vector<int> nums3 = {3, 5};
    TreeNode* root3 = solution.sortedArrayToBST(nums3);
    cout << "Edge Case 3: ";
    printTree(root3);
    cout << endl;

    //Case 4: Three elements
    vector<int> nums4 = {1, 3, 5};
    TreeNode* root4 = solution.sortedArrayToBST(nums4);
    cout << "Edge Case 4: ";
    printTree(root4);
    cout << endl;

    return 0;
}
