#include<iostream>
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
int sum = 0;

class Solution {
public:
    int rangeSumBST(TreeNode* root, int low, int high) {
        sum = 0;
        enterTree(root, low, high);
        return sum;
    }

    void enterTree(TreeNode* root, int low, int high) {
        if (root == nullptr) 
            return;
        if (root->val < low) {
            enterTree(root->right, low, high);
        } else if (root->val > high) {
            enterTree(root->left, low, high);
        } else {
            sum += root->val;
            enterTree(root->left, low, high);
            enterTree(root->right, low, high);
        }
    }
};