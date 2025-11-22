// LeetCode = https://leetcode.com/problems/find-the-duplicate-number/submissions/
// Normal using hashing could be solved..
// Referenced using floyd warshall's algorithm (Hare & Tortoise)
#include <bits/stdc++.h>
using namespace std;

/*
Here can not use calculation method cause they said element can be repeated n number times
There no guarantee that it will repeat only twice.
This algorithm will work only if there is guarantee of cycle is present in array.
*/
/*
When Map is used
SC = O(N)
TC = O(N)

When Floyd Warshall
SC = O(1)
TC = O(N)
*/

int findDuplicate(vector<int>& nums) 
{
    int iSlow = 0, iFast = 0;
    do
    {
        iSlow = nums[iSlow];
        iFast = nums[nums[iFast]];
    } while(iSlow != iFast);

    iFast = 0;
    while (iSlow != iFast)
    {
        iSlow = nums[iSlow];
        iFast = nums[iFast];
    }
    
    return nums[iSlow];
}