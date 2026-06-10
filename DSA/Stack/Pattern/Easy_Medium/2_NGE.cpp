/*
LeetCode 496 = https://leetcode.com/problems/next-greater-element-i/description/
Date = 10-Jun-2026
RevisedDate = NA
Solution = Referanced
TC = 
SC = 
*/


#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef unsigned long long ull;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) 
    {
        unordered_map<int, int> umpNGE;
        stack<int> stk;

        for (int i=(nums2.size()-1); i>=0; --i)
        {
            while (!stk.empty() && stk.top() <= nums2[i])
            {
                stk.pop();
            }
            if (!stk.empty())
            {
                umpNGE.emplace(nums2[i], stk.top());
            }
            stk.push(nums2[i]);
        }

        vector<int> vecRes(nums1.size(), -1);
        int i = 0;
        for (auto iVal:nums1)
        {
            auto itr = umpNGE.find(iVal);
            if (itr != umpNGE.end())
            {
                vecRes[i] = itr->second;
            }
            ++i;
        }

        return vecRes;
    }
};