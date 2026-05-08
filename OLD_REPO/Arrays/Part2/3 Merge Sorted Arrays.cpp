#include <bits/stdc++.h>
using namespace std;
// LeetCode = https://leetcode.com/problems/merge-sorted-array/
// Brute-Force = self
// Optimal = Referenced

/*########################-------Brute-Force---------###############################*/

/*
SC = O(N + M)
TC = O(N + M)
*/
void mergeF(vector<int>& nums1, int m, vector<int>& nums2, int n) 
{
    vector<int> tmp(m,0);
    int i=0;
    for(auto &e:tmp)
        {e = nums1[i]; ++i;}
    
    int iPt1 = 0, iPt2 = 0;
    i=0;
    while (iPt1 < m && iPt2 < n)    
    {
        if(tmp[iPt1] < nums2[iPt2])
        {
            nums1[i] = tmp[iPt1]; ++iPt1;
        }
        else
        {
            nums1[i] = nums2[iPt2]; ++iPt2;
        }
        ++i;
    }

    if(iPt1>=m)
    {
        while(iPt2<n)
        {
            nums1[i] = nums2[iPt2];
            ++iPt2; ++i;
        }
    }
    if(iPt2>=n)
    {
        while(iPt1<m)
        {
            nums1[i] = tmp[iPt1];
            ++iPt1; ++i;
        }
    }
    
}

/*###########################----Optimal Approach-----#########################*/

/*
SC = O(1)
TC = 1) For outer loop we are reducing it by 2 every time = log2(N + M)
     2) For inner loop we are almost visiting all array son = O(N)
     = log2(N + M) + O(N + M)
*/
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) 
{
    int iSize = m+n;
    for(int i=m, j=0; i<iSize; ++i, ++j)
        nums1[i] = nums2[j];
    
    int iSeal = (iSize/2)+(iSize%2);
    while (iSeal>0)
    {
        int iLeft = 0; int iRight = iLeft + iSeal;
        while (iRight < iSize)
        {

            if(nums1[iLeft] > nums1[iRight])
            {
                swap(nums1[iLeft], nums1[iRight]);
            }
            ++iRight; ++iLeft;
        }
        if(iSeal==1) break;
        iSeal = (iSeal/2)+(iSeal%2);
    }
    
}

int main ()
{

    vector<int> v1(4, 0);
    v1[0] = 4;
    vector<int> v2 = {1,2,3};
    merge(v1, 1, v2, 3);

    for (auto i:v1)
    {
        cout<<i<<" ";
    }
    return 0;
}