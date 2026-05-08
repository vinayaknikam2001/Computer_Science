//LeetCode = https://leetcode.com/problems/maximum-depth-of-binary-tree/description/
//Self Solved
class Solution {
public:
    int maxDepth(TreeNode* root) 
    {
        if (root == NULL) return 0;
        
        int leftCnt = 0, rightCnt = 0;
        leftCnt = 1 + maxDepth(root->left);
        rightCnt = 1 + maxDepth(root->right);

        return max(leftCnt, rightCnt);
    }
};