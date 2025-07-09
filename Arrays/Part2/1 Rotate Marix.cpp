// LeetCode = https://leetcode.com/problems/rotate-image/submissions/905140436/
// Referenced
class Solution {
public:


/*
SC = O(1)
TC = O(N^2) + O(N^2) = O(N^2)
*/
    void rotate(vector<vector<int>>& matrix) 
    {
        int n = matrix.size(), m = matrix[0].size();
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<i; j++)
                swap(matrix[i][j], matrix[j][i]);
        }

        for(auto &v:matrix)
            reverse(v.begin(), v.end());
    }
};