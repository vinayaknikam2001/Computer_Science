// Coding Ninjas = https://www.codingninjas.com/studio/problems/920321?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website&leftPanelTab=0
// Self Solved using normal approach
#include <bits/stdc++.h>
using namespace std;

// There is one more approach not mentioned here which is most optimistic using 2 pointer approach.....:->)

/*#########################------Normal Solution-----#############################*/
/*
TC = O(n*n) = O(nSquare)
SC = O(1)
*/
#include <bits/stdc++.h>

int LongestSubsetWithZeroSum(vector < int > arr) 
{
    int n = arr.size(), maxLen = 0;
    for(int i=0; i<n; ++i)
    {
        int sum = 0;
        for(int j=i; j<n; ++j)
        {
            sum += arr[j];
            int len = 0;

            if(sum == 0)
            {
                len = (j-i+1);
                maxLen = max(maxLen, len);
            }
        } 
    }

    return maxLen;
}


/*##########################--------------Optimal Solution-----#####################################*/
/*
TC = O(n*n(logn)) [using normal map]
TC = O(n) or O(nSquare) [using unordered_map]
SC = O(n)
*/
int LongestSubsetWithZeroSum(vector < int > arr) 
{
    int n = arr.size(), maxLen = 0, sum = 0;
    map<int, int> preSumMap;
    int k = 0;

    for (int i=0; i<n; ++i)
    {
        sum += arr[i];
        if (sum == k)
            maxLen = max(maxLen ,i + 1);
        
        int rem = sum - k;
        if (preSumMap.find(rem) != preSumMap.end())
        {
            int len = (i - preSumMap[rem]);
            maxLen = max(maxLen, len);
        } 
        
        /*Below test case is quiet important here we can directly insert in map ..
        but we checked if element already exist cause we want leftmost element in  array.
        i.e., longest possible subarray...
        */
        if (preSumMap.find(sum) == preSumMap.end()) 
        {
            preSumMap[sum] = i;
        }

    }

    return maxLen;
}