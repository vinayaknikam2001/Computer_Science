/*
LeetCode 457 = https://leetcode.com/problems/circular-array-loop/
Date = 19-May-2026
RevisedDate = NA
Solution = Self
TC = 
SC = 
Failed Test Cases:
1) [-2,1,-1,-2,-2]  //For this testcase there was a cycle in 1st and 2nd index so which is in opposite directions
2) [-1]             //For this test case -ve index was getting generated in getNextIndex Function.
*/
#include<bits/stdc++.h>
using namespace std;

class Solution 
{
    private:

    bool dfs(vector<vector<int>> &g_List, int iNode, vector<bool> bVisited, vector<bool> bRecStack, vector<int>&nums)
    {
        bVisited[iNode] = true;
        bRecStack[iNode] = true;
        bool ans = false;
        bool bSign1 = (nums[iNode] > 0);
        for (auto iVertex:g_List[iNode])
        {
            bool bSign2 = (nums[iVertex] > 0);
            if (bSign1 != bSign2)   //For test case 1 this check was added to avoid failure.
            {
                continue;
            }
            if (!bVisited[iVertex])
            {
                ans |= dfs(g_List, iVertex, bVisited, bRecStack, nums);
            }
            else if (bRecStack[iVertex])
            {
                return true;
            }
        }
        bRecStack[iNode] = false;
        return ans;
    }

public:
    bool circularArrayLoop(vector<int>& nums) 
    {
        size_t iSize = nums.size();
        vector<vector<int>> gList(iSize, vector<int>());

        auto getNextIndex = [] (int iVal, int i, int iSize) 
        {
            int iRes = 0;
            if (iVal > 0)
            {
                iRes = (i + iVal) % iSize;
            }
            else
            {
                iRes = (((i+iVal) % iSize) >= 0) ? (i+iVal)%iSize /*This %iSize was not there before added when failed test case 2*/
                : (iSize) - (abs(i+iVal) % iSize);
            }
            cout << "i" << i << " " << (i+iVal) << " " << iSize  << " : " <<(i+iVal)%iSize <<endl;
            return iRes;
        };

        for (int i=0; i<iSize; i++)
        {
            int iVal = nums[i];
            int idx = getNextIndex(iVal, i, iSize);
            if (i != idx) 
            {
                gList[i].push_back(idx);
            }
        }

        cout << "END!" << endl;
        vector<bool> bVisited(iSize, false), bRecStack(iSize, false);
        bool bRes = false;
        for (int i=0; i<iSize; i++)
        {
            if (!bVisited[i])
            {
                if (dfs(gList, i, bVisited, bRecStack, nums))
                {
                    bRes = true;
                    break;
                }
            }
        }

        return bRes;
    }
};


/*

2 2 3 1 
*/