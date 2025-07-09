//GFG = https://www.geeksforgeeks.org/problems/quick-sort/1

class Solution {
  public:
    // Function to sort an array using quick sort algorithm.
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
    // Function that takes last element as pivot, places the pivot element at
    // its correct position in sorted array, and places all smaller elements
    // to left of pivot and all greater elements to right of pivot.
    int partition(vector<int>& arr, int low, int high) 
    {
        int iPivot = arr[low];
        int iLPtr = low, iRPtr = high;
        
        while (iLPtr < iRPtr)
        {
            while (arr[iLPtr] <= iPivot) ++iLPtr;
            while (arr[iRPtr] >  iPivot) --iRPtr;
            if (iLPtr < iRPtr)
                swap(arr[iLPtr], arr[iRPtr]);
        }
        swap(arr[low], arr[iRPtr]);
        
        return iRPtr;
    }
};