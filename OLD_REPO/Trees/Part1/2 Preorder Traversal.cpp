// LeetCode = https://leetcode.com/problems/binary-tree-preorder-traversal/

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
class Solution 
{
    void getPreorder(TreeNode *root, vector<int> &nodes)
    {
        if (root)
        {
            nodes.push_back(root->val);
            getPreorder(root->left, nodes);
            getPreorder(root->right, nodes);
        }
    }
public:
    vector<int> preorderTraversal(TreeNode* root) 
    {
        vector<int> nums;
        getPreorder(root, nums);
        return nums;    
    }
};