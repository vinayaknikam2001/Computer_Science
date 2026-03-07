//https://leetcode.com/problems/longest-increasing-subsequence/description/
//Referenced
/*
	As DP will be generated for a respective [idx] and [prev];
	and prev can be -ve so we are storing in +1 format in DP.
    Why we need 2D DP array previous is needed cause we decide.
    Based on previous wheather to consider current element as part of our subsequence or not.
    try focus on practical case storing in DP when return when iPrev is not there
*/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int func(int i, int iPrev, int iSize, vector<int> &nums, vector<vector<int>>& dp)
    {
        if (i >= iSize)
        {
            return 0;
        }
        //While returning also we are using iPrev+1 to handle case of -1;
        if (dp[i][iPrev+1] != INT_MIN)
        {
            return dp[i][iPrev+1];
        }

        int iPik = 0, iNPik = 0;

        if (iPrev == -1 || nums[iPrev] < nums[i])
        {
            iPik = 1 + func(i+1, i, iSize, nums, dp);
        }
        iNPik = 0 + func(i+1, iPrev, iSize, nums, dp);

        //While storing in DP array we will be using iPrev+1 to handle case on -1;
        return dp[i][iPrev+1] = max(iPik, iNPik);
    }

    int lengthOfLIS(vector<int>& nums) 
    {
        int iSize = nums.size();
        // Note Added iSize+1 because in DP array we are storing iPrev+1 to avoid -1 index;
        vector<vector<int>> dp(iSize+1, vector<int>(iSize+1, INT_MIN));
        return func(0, -1, iSize, nums, dp);
    }
};