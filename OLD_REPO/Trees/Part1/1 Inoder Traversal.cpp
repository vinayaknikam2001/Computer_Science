//LeetCode = https://leetcode.com/problems/binary-tree-inorder-traversal/

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

    void getInorder(TreeNode *root, vector<int> &nodes)
    {
        if (root)
        {
            getInorder(root->left, nodes);
            nodes.push_back(root->val);
            getInorder(root->right, nodes);
        }
    }

    vector<int> inorderTraversal(TreeNode* root) 
    {
        vector<int> nodes;
        getInorder(root, nodes);
        return nodes;    
    }
};