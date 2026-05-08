// https://www.codingninjas.com/codestudio/problems/800284?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website&leftPanelTab=0
// Self Solved Wrong ans in sample test because silly mistake of (i-1 in func call...
/*
    //Mistake 1
	nPik = func(i-1, rodSize, price, dp);
    if((i+1) <= rodSize)
        pik = price[i] + func(i-1, rodSize-(i+1), price, dp);


    //Mistake 2 (During Revision)
    In below line
    pik = price[i] + func(i, (rodSize-i+1), price, dp);
    Example:
    Let a=10 and b=3:
    1. (a - b + 1): 
       ( a - b + 1 = 10 - 3 + 1 = 7 + 1 = 8)

    2. a - (b + 1):
       (a - (b + 1) = 10 - (3 + 1) = 10 - 4 = 6)

    Conclusion:
    The placement of parentheses changes the order of operations and, therefore, the result

*/


#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long int lli;



lli func(int i, int rodSize,  vector<int> &price, vector<vector<lli>> &dp)
{
    if(rodSize == 0)
        return 0;

    if(i == 0)
        return rodSize * price[i];
    
    if(dp[i][rodSize] != INT_MIN)
        return dp[i][rodSize];

    int pik = 0, nPik = 0;
    nPik = func(i-1, rodSize, price, dp);
    if((i+1) <= rodSize)
        pik = price[i] + func(i, rodSize-(i+1), price, dp);

    return dp[i][rodSize] = max(pik, nPik);
}

int cutRod(vector<int> &price, int n)
{
    int m = price.size();
    vector<vector<lli>> dp(m, vector<lli>(n+1, INT_MIN));
    return func(m-1, n, price, dp);
}
