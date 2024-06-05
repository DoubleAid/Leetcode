/*
 * @lc app=leetcode id=99 lang=cpp
 *
 * [99] Recover Binary Search Tree
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void recoverTree(TreeNode* root) {
        TreeNode* first = nullptr, *second = nullptr, *prev = nullptr, *temp = nullptr;
        while (root!= nullptr) {
            if (root->left != nullptr) {
                temp = root -> left;
                while(temp->right != nullptr && temp->right != root) {
                    temp = temp->right;
                }
                if (temp->right == nullptr) {
                    temp->right = root;
                    root = root -> left;
                } else {
                    if (prev != nullptr && prev->val > root -> val) {
                        if (first == nullptr) first = prev;
                        second = root;
                    }
                    temp->right = nullptr;
                    prev = root;
                    root = root->right;
                }
            } else {
                if (prev != nullptr && prev->val > root->val) {
                    if (first == nullptr) first = prev;
                    second = root;
                }
                prev = root;
                root = root->right;
            }
        }
        if (first != nullptr && second != nullptr) {
            swap(first->val, second->val);
        }
    }
};
// @lc code=end

// 1919/1919 cases passed (23 ms)
// Your runtime beats 50.12 % of cpp submissions
// Your memory usage beats 70.83 % of cpp submissions (60.4 MB)