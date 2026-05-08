// https://www.codingninjas.com/codestudio/problems/630471?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website&leftPanelTab=0
// Self Solved
/*
Please check leetcode problem also it's complex than code studio.
*/


#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long lli;


lli func(int idx, int *den, int tar, vector<vector<lli>> &dp)
{
   
    if(idx == 0)
    {
        if(tar%den[idx] == 0)
            return 1;
        else 
            return 0;   
    }
    if(dp[idx][tar] != -1)
        return dp[idx][tar];

    lli pik = 0, nPik = 0;
    nPik = func(idx-1, den, tar, dp);
    if(den[idx] <= tar)
        pik = func(idx, den, tar-den[idx], dp);
    
    return dp[idx][tar] = pik+nPik;
    
}

long countWaysToMakeChange(int *denominations, int n, int value)
{
    vector<vector<lli>> dp(n, vector<lli>(value+1, -1));
    return func(n-1, denominations, value, dp);
}



//LeetCode = https://leetcode.com/problems/coin-change/
class Solution {
public:
    
    pair<bool,int> fewestCoins(int i, int amount, vector<int> &coins, vector<vector<pair<bool, int>>>&dp)
    {
        if (amount == 0) {
            return {true, 0};
        }
        if (i == 0) {
            bool bFound = (amount % coins[i] == 0);
            int count = (bFound) ? (amount/coins[i]) : 0;
            return {bFound, count};
        }

        if (dp[i][amount].second != INT_MIN) return dp[i][amount];

        pair<bool, int> pikAmount = {false, 0}, nPikAmount = {false, 0};
        
        if (amount >= coins[i]) {
            pikAmount = fewestCoins(i, (amount-coins[i]), coins, dp);
            if (pikAmount.first) ++pikAmount.second;
        }
        nPikAmount = fewestCoins(i-1, amount, coins, dp);
        //if (nPikAmount.first) ++nPikAmount.second;

        if (pikAmount.first && nPikAmount.first) {
            if (pikAmount.second < nPikAmount.second) return dp[i][amount] = pikAmount;
            else return dp[i][amount] = nPikAmount;
        }
        else if (pikAmount.first) {
            return dp[i][amount] = pikAmount;
        }
        else if (nPikAmount.first) {
            return dp[i][amount] = nPikAmount;
        }
        else {
            return dp[i][amount] = {false, 0};
        }
    }

    int coinChange(vector<int>& coins, int amount) 
    {
        vector<vector<pair<bool, int>>> dp(coins.size(), vector<pair<bool, int>>(amount+1, {false, INT_MIN}));
        pair<bool, int> Ans = fewestCoins(coins.size()-1, amount, coins, dp);
        return (Ans.first) ? Ans.second : -1;
    }
};