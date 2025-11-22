//https://www.codingninjas.com/codestudio/problems/631055?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website&leftPanelTab=1
//Self Solved
//Using normal approach
#include <bits/stdc++.h>
using namespace std;

/*
SC = O(1)
TC = O(N) + O(N) = O(N)
*/ 
void sort012(int *arr, int n)
{
    map<int, int> mp;
    for(int i=0; i<n; i++)
        mp[arr[i]]++;
    
    int cnt0 = mp[0], cnt1 = mp[1], cnt2 = mp[2]; 
    for(int i=0; i<n; i++)
    {
        if(cnt0) {
            arr[i] = 0;
            cnt0--;
        }
        else if (cnt1) {
            arr[i] = 1;
            cnt1--;
        }
        else {
            arr[i] = 2;
        }
    }

}

//Optimised Approach Reduces Time complexity by Half using "Dutch National Flag Algorithm"
//Referenced
inline void swap(int &n1, int &n2)
{
    int tmp = n1;
    n1 = n2;
    n2 = tmp;
}


/*
SC = O(1)
TC = O(N)
*/

void sort012(int *arr, int n)
{
   int hi=n-1, lo=0, mid=0;
   while(mid <= hi)
   {
        if(arr[mid] == 0){
            swap(arr[lo], arr[mid]);
            lo++; mid++; 
        }
        else if(arr[mid] == 1)
            mid++;
        else {
            swap(arr[mid], arr[hi]);
            hi--;   // Remember on this there is no need to increment mid++;
                    // Cause after swapping there will be new element in mid
                    // decrement hi cause yu swapped value 2 to the end...
        }
   }
}   
