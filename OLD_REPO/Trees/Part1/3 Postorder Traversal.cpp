//LeetCode =  https://leetcode.com/problems/binary-tree-postorder-traversal/submissions/1268935152/

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
    void getPostorder(TreeNode *root, vector<int>& nodes)
    {
        if (root)
        {
            getPostorder(root->left, nodes);
            getPostorder(root->right, nodes);
            nodes.push_back(root->val);
        }
    }
public:
    vector<int> postorderTraversal(TreeNode* root) 
    {
        vector<int> nodes;
        getPostorder(root, nodes);
        return nodes;    
    }
};