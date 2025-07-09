//https://www.codingninjas.com/codestudio/problems/893405?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website&leftPanelTab=0
//Self Solved 
//Best Optimised
#include <bits/stdc++.h> 


/*
SC = O(1)
TC = O(N)
*/
int maximumProfit(vector<int> &prices)
{
    int pre=prices[0], mxProfit=0;

    for(int &i:prices)
    {   
        if(i>=pre)
        {
            if(mxProfit < (i-pre))
                mxProfit = i-pre;
        }
        else 
            pre = i;
    }
    return mxProfit;
}