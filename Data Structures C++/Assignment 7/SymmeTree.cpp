#include <iostream>
#include <cassert>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) return true;
        return isSymmetric(root->left, root->right);
    }
    
    bool isSymmetric(TreeNode* left, TreeNode* right) {
        if (left == nullptr && right == nullptr) return true;
        if (left == nullptr || right == nullptr) return false;
        if (left->val != right->val) return false;
        
        return isSymmetric(left->left, right->right) && isSymmetric(left->right, right->left);
    }
};

int main() {
    // Create nodes
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(2);
    root1->left->left = new TreeNode(3);
    root1->left->right = new TreeNode(4);
    root1->right->left = new TreeNode(4);
    root1->right->right = new TreeNode(3);

    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(2);
    root2->left->right = new TreeNode(3);
    root2->right->right = new TreeNode(3);

    TreeNode* root3 = new TreeNode(1);
    root3->left = new TreeNode(2);
    root3->right = new TreeNode(2);
    root3->left->right = new TreeNode(3);
    root3->right->left = new TreeNode(3);

    Solution sol;

    // Test cases
    assert(sol.isSymmetric(root1) == true);  // Symmetric tree
    assert(sol.isSymmetric(root2) == false); // Not symmetric tree
    assert(sol.isSymmetric(root3) == true); // Symmetric tree

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
