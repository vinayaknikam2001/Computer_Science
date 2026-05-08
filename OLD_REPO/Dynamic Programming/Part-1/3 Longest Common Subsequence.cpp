//https://www.codingninjas.com/codestudio/problems/624879?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website
//https://leetcode.com/problems/longest-common-subsequence/
//Self Solved
#include <bits/stdc++.h>
using namespace std;

int func(int i1, int i2, string &s1, string &s2, vector<vector<int>> &dp)
{
    if(i1<0 || i2<0)
        return 0;
    if(dp[i1][i2] != INT_MIN)
        return dp[i1][i2];
    
    if(s1[i1] == s2[i2])
        return dp[i1][i2] =  1 + func(i1-1, i2-1, s1, s2, dp);
    else
        return dp[i1][i2] = max(func(i1-1, i2, s1, s2, dp), func(i1, i2-1, s1, s2, dp));
}

int lcs(string s, string t)
{
    int n1 = s.size(), n2 = t.size();
    vector<vector<int>> dp(n1,vector<int>(n2, INT_MIN));
	return func(n1-1, n2-1, s, t, dp);
}


//LeetCode = https://leetcode.com/problems/longest-common-subsequence/description/
class Solution {
public:

    int findLCS(int i, int j, string& s1, string &s2, vector<vector<int>> &dp)
    {
        if (i >= s1.size() || j >= s2.size())
        {
            return 0;
        }

        if (dp[i][j] != INT_MIN)
        {
            return dp[i][j];
        }

        int iPik = 0, iNPik = 0;
        if (s1[i] == s2[j])
        {
            iPik = 1 + findLCS(i+1, j+1, s1, s2, dp);
        }
        iNPik = 0 + max(findLCS(i+1, j, s1, s2, dp), findLCS(i, j+1, s1, s2, dp));

        return dp[i][j] = max(iPik, iNPik);
    }

    int longestCommonSubsequence(string text1, string text2) 
    {
        int n1 = text1.size();
        int n2 = text2.size();
        vector<vector<int>> dp(n1, vector<int>(n2, INT_MIN));
        return findLCS(0, 0, text1, text2, dp);
    }
};