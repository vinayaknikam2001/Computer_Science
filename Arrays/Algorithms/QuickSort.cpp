//GFG = https://www.geeksforgeeks.org/problems/quick-sort/1


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
        swap(arr[low], arr[iRPtr]);             //!IMP
        
        return iRPtr;
    }
};