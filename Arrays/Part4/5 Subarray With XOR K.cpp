// Coding Ninjas = https://www.codingninjas.com/studio/problems/subarrays-with-xor-k_6826258?utm_source=striver&utm_medium=website&utm_campaign=a_zcoursetuf&leftPanelTab=0
// Self using Normal approach (Not Accepted remained TLE on codingninjas)
// Referenced using optimal approach
#include <bits/stdc++.h>
using namespace std;

/*#############---------Normal Approach-----------#############*/

/*
TC = O(nSquare)
SC = O(1)
*/
int subarraysWithSumK(vector < int > a, int b) 
{
    int iCnt = 0, n = a.size();

    for (int i=0; i<n; ++i)
    {
        int xSum = 0;
        for (int j=i; j<n; ++j)
        {
            xSum = (j == i) ? a[j]: (xSum ^ a[j]);
            if (xSum == b)
                ++iCnt;
        }
    }

    return iCnt;
}



/*#######################---------Optimal Approach-----------######################*/

/*
TC = O(n * (logn)) [using normal map]
TC = O(n) or O(nSquare) [using unordered_map]
SC = O(n)
*/
#include <bits/stdc++.h>
int subarraysWithSumK(vector < int > a, int b) 
{
    int iCnt = 0, n = a.size();
    map<int, int> xSumMap;

    int xSum = 0;
    for (int i=0; i<n; ++i)
    {
        xSum ^= a[i];

        if (xSum == b)
            ++iCnt;
        
        int xRem = xSum ^ b;
        if (xSumMap.find(xRem) != xSumMap.end())
        {
            iCnt += xSumMap[xRem];
        }
        xSumMap[xSum]++;
    }

    return iCnt;
}