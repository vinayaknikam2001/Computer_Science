//GFG = https://www.geeksforgeeks.org/problems/merge-sort/1
#include <bits\stdc++.h>
using namespace std;


/*
Merge Sort.
TC = n(log2(n))
SC = O(N)
*/


typedef long long int lli;
class Solution {
  public:
  
    void merge(vector<int>&arr, int iStart, int iMid, int iEnd)
    {
        int iSize = iEnd - iStart + 1, iLeft = iStart, iRight = iMid + 1;
        vector<int> i_arr(iSize, 0);
        
        int iIdx = 0;
        while ((iLeft <= iMid) && (iRight <= iEnd))
        {
            if (arr[iLeft] < arr[iRight])
            {
                i_arr[iIdx] = arr[iLeft];
                ++iLeft;
            }
            else
            {
                i_arr[iIdx] = arr[iRight];
                ++iRight;
            }
            ++iIdx;
        }
        
        while (iLeft <= iMid)
        {
            i_arr[iIdx] = arr[iLeft];
            ++iIdx; ++iLeft;
        }
        
        while (iRight <= iEnd)
        {
            i_arr[iIdx] = arr[iRight];
            ++iIdx; ++iRight;
        }
        
        for (int i=iStart; i<=iEnd; ++i)
        {
            arr[i] = i_arr[(i-iStart)];
        }
    }
  
    void mergeSort(vector<int>& arr, int l, int r) 
    {
        if (l < r)
        {
            int iMid = (l + r) / 2;
            mergeSort(arr, l, iMid);
            mergeSort(arr, iMid+1, r);
            merge(arr, l, iMid, r);
        }
    }
};