// LeetCode Link = https://leetcode.com/problems/search-a-2d-matrix/submissions/
// Self Sovled

/*
SC = O(1)
TC = 1) We are traversing matrix in binary search becuase at each step there is division by 2 
        Time complexity = O(log2(n * M)) 
*/


class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) 
    {
        int m = matrix.size(), n = matrix[0].size();
        int iLeft = 0, iRight = (m * n) - 1;
        int iMid = 0;

        while(iLeft <= iRight)
        {
            int iMid = (iLeft + iRight) / 2;
            int i = iMid / n; int j = iMid % n;

            if (matrix[i][j] == target)
                return true;
            else if (target < matrix[i][j])
                iRight = iMid - 1;
            else 
                iLeft = iMid + 1;

        }

        return false;
    }
};



