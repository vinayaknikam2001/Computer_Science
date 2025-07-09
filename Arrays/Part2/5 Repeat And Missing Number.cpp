// CodingNinjas = https://www.codingninjas.com/studio/problems/873366?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website&leftPanelTab=1
// Referenced
#include <bits/stdc++.h>
typedef long long int lli;
typedef unsigned long long ull;

/*
SC = O(1)
TC = O(N) //To calulate actual sum.
*/

pair<int,int> missingAndRepeating(vector<int> &arr, int n)
{
    lli N = arr.size();
    lli iExpSum = ((N * (N + 1)) / 2);
    lli iExpSQRSum = ((N * (N+1) * (2*N+1)) / 6);
    lli iActSum = 0, iActSQRSum = 0;
    lli iMissing = 0, iRepeating = 0;

    for(lli i:arr)
    {
        iActSum += i;
        iActSQRSum += (i*i);
    }
        
    lli iDiff = iExpSum-iActSum ; //Diffrence is M-R (Missing-Repeating)
    lli iTotal = (iExpSQRSum - iActSQRSum) / iDiff;

    iMissing = (iDiff + iTotal) / 2;
    iRepeating = iTotal - iMissing;

    return {int(iMissing), int(iRepeating)};
}