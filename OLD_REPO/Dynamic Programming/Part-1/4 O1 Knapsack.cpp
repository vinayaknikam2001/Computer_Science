//https://www.codingninjas.com/codestudio/problems/1072980?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website
//Self
#include <bits/stdc++.h>
using namespace std;

int func(int idx, int siz, int bagSiz, vector<int> vals, vector<int> wets, vector<vector<int>> &dp)
{
    if(idx < 0)
        return 0;
    if(dp[idx][bagSiz] != INT_MIN)
        return dp[idx][bagSiz];

    int pik=0, nPik=0;
    if(wets[idx] <= bagSiz)
        pik = vals[idx] + func(idx-1, siz, bagSiz-wets[idx], vals, wets, dp);
    nPik = 0 + func(idx-1, siz, bagSiz, vals, wets, dp);

    return dp[idx][bagSiz] = max(pik, nPik);
}

int maxProfit(vector<int> &values, vector<int> &weights, int n, int w)
{
    vector<vector<int>> dp(n+1, vector<int>(w+1, INT_MIN));
    return func(n-1, n, w, values, weights, dp);
}