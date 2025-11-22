// LeetCode = https://leetcode.com/problems/merge-intervals/
// Referenced
#include <bits/stdc++.h>
using namespace std;
/*
Read This First to Understand constrains========================================================================>
Some corner cases
[ [1,4], [0,4] ]
[ [15,18], [16,17] ]
Note :- One constrain not given in problem properly i.e.,
the intervals[i][0] < intervals[i][1] 
*/

class Solution {
public:


/*
SC = O(N*2)
TC = O(N*log(N)) + O (N*2) =  O(N*log(N)) + O (N)
*/

vector<vector<int>> merge(vector<vector<int>>& intervals) 
{
    int iPrev = 0, iStart = 0;
    int iSize = intervals.size();
    int iResIdx = 0;
    sort(intervals.begin(), intervals.end());   // [ [1,4], [0,4] ] To handle this test case we are sorting array...
    vector<vector<int>> vResult;

    for(int iIdx=0; iIdx<iSize; ++iIdx)
    {
        if(vResult.empty() || intervals[iIdx][0] > vResult.back()[1])
        {
            vResult.push_back(intervals[iIdx]);
        }
        else
        {
            vResult.back()[1] = max(vResult.back()[1], intervals[iIdx][1]); // [ [15,18], [16,17] ] to handle this test case we are taking max...
        }
    }
    return vResult;
}

};

