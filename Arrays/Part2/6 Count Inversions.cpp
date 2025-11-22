// CodeStudio Link = https://www.codingninjas.com/studio/problems/count-inversions_615?leftPanelTab=1
// Referenced
#include <bits/stdc++.h>
using namespace std; 


/*
SC = N(log(N))
TC = N(log(N))
*/

void merge(long long *v, int iStart, int iMid, int iEnd, int &cnt, int iN)
{
    int arr[iN] = {0};
    int i=iStart, j=iMid+1, k=0;

    while(i <= iMid && j <= iEnd)
    {
        if(v[i] <= v[j])
        {
            arr[k] = v[i]; ++i;
        }
        else
        {
            arr[k] = v[j]; ++j;
            cnt += (iMid - i+1);
        }
        ++k;
    }

    while(i<=iMid)
    {
        arr[k] = v[i];
        ++i; ++k;
    }
    while(j<=iEnd)
    {
        arr[k] = v[j];
        ++j; ++k;
    }

    for(int i=iStart; i<=iEnd; ++i)
    {
       v[i] = arr[i-iStart];
    }
}

void mergeSort(long long *v, int iStart, int iEnd, int &cnt, int n)
{
    if(iStart < iEnd)
    {
        int iMid = (iStart + iEnd) / 2;
        mergeSort(v, iStart, iMid, cnt, n);
        mergeSort(v, iMid+1 , iEnd, cnt ,n);
        merge(v, iStart, iMid, iEnd, cnt, n);
    }
}
long long getInversions(long long *arr, int n){
    // Write your code here.
    int cnt =0;
    mergeSort(arr, 0, n-1, cnt, n);
    return cnt;
}