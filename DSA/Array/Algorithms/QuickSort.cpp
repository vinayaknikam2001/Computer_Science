/*
GFG = https://www.geeksforgeeks.org/problems/quick-sort/1
Date = 08-Nov-2026
RevisedDate = NA
SC = O (1)
TC = Best Case O (N * log2(N)) 
     Worst Case O (N ^ 2)       {Check case 2 to understand worst case}

TestCases:
Case 1:
int arr[] = {6, 2, 3, 5, 9, 1}
Case 2:
int arr[] = {5, 4, ,3, 2, 1}
*/
#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    /*
    Failed one test case due to array index going out of bound.
    Code line which failed...
        while (arr[iLPtr] <= iPivot) ++iLPtr;
        while (arr[iRPtr] >  iPivot) --iRPtr;
    
    Solution provided
        while (arr[iLPtr] <= iPivot && iLPtr <= high) ++iLPtr;
        while (arr[iRPtr] >  iPivot && iRPtr >= low) --iRPtr;

    Time Complexity = O(nlog(n))
    Worst case Time = O(n^2) (when pivot is always the smallest/largest element)
    Space Complexity = O(1) Without considering stack space.
    */
    void quickSort(vector<int>& arr, int low, int high) 
    {
        if (low < high)
        {
            int iPivot = partition(arr, low, high);
            quickSort(arr, low, iPivot-1);
            quickSort(arr, iPivot+1, high);
        }
    }

  public:
    /* Places all smaller elements to left of pivot and all greater elements to right of pivot.
       Think how above mentioned logic is achieved in this code that's core idea behind quicksort .
    */
    int partition(vector<int>& arr, int low, int high) 
    {
        int iPivot = arr[low];
        int iLPtr = low, iRPtr = high;
        
        while (iLPtr < iRPtr)
        {
            while (arr[iLPtr] <= iPivot && iLPtr <= high) ++iLPtr;
            while (arr[iRPtr] >  iPivot && iRPtr >= low) --iRPtr;
            if (iLPtr < iRPtr)                  //!IMP
                swap(arr[iLPtr], arr[iRPtr]);   //!IMP
        }
        swap(arr[low], arr[iRPtr]);             //!IMP Why we swap with Right Ptr only check case 1.
        
        return iRPtr;
    }
};


int main ()
{

    Solution s;
    vector<int> vec = {5, 4, 3, 2, 1};
    s.quickSort(vec, 0 , 4);
    for (auto iVal:vec)
    {
        cout << iVal << " ";
    }
    return 0;
}