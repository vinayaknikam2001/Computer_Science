// https://www.codingninjas.com/codestudio/problems/minimum-path-sum_985349?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website&leftPanelTab=0
// https://leetcode.com/problems/minimum-path-sum/description/
// Self Solved
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

ull calcMin(vector<vector<int>> &grid, int i, int j, vector<vector<ull>> &dp)
{
    if (0==i && 0==j)
    {
        return grid[i][j];
    }
    if (i < 0 || j < 0)
    {
        return INT_MAX;
    }
    if (INT_MIN != dp[i][j]) 
    {
        return dp[i][j];
    }

    ull leftSum = INT_MAX, upSum = INT_MAX;
    leftSum = (ull)grid[i][j] + calcMin(grid, i, j-1, dp);
    upSum = (ull)grid[i][j] + calcMin(grid, i-1, j, dp);

    return dp[i][j] = min(leftSum, upSum);
}

int minSumPath(vector<vector<int>> &grid) 
{
    int iRows = grid.size(), iCols = grid[0].size();
    vector<vector<ull>> dp(iRows, vector<ull>(iCols, INT_MIN));
    return calcMin(grid, iRows-1, iCols-1, dp);
}