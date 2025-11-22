// Leetcode = https://leetcode.com/problems/unique-paths/description/
// Self sovled
// Combionatrics approach referenced
#include <bits/stdc++.h>
using namespace std;

/*#####################----DP---#########################*/
class Solution {
public:

    int func(int x, int y, vector<vector<int>>&dp)
    {
        if (x == 0 && y == 0)
            return 1;
        if (x < 0 || y < 0)
            return 0;

        if (dp[x][y] != -1)
            return dp[x][y];

        int stp1 = 0, stp2 = 0;
        stp1 = func(x, y-1, dp);
        stp2 = func(x-1, y, dp);

        return dp[x][y] = stp1 + stp2;
    }

    int uniquePaths(int m, int n) 
    {
        vector<vector<int>> dp(m, vector<int>(n, -1));
        return func(m-1, n-1, dp);   
    }
};