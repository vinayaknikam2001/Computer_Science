/*
LeetCode 239 = https://leetcode.com/problems/sliding-window-maximum/description/
Date = 14-May-2026
RevisedDate = NA
Solution = Referanced
TC = 
SC = 
*/
#include<bits/stdc++.h>
using namespace std;

class Solution 
{
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) 
    {
        deque<int> dq;
        vector <int> vecRes;
        for (int i=0; i<k; ++i)
        {
            while (!dq.empty() && nums[dq.back()] < nums[i])
            {
                dq.pop_back();
            }
            dq.push_back(i);
        }
        vecRes.push_back(nums[dq.front()]);

        for (int i=k; i<nums.size(); ++i)
        {
            while (!dq.empty() && dq.front() <= (i-k))
            {
                dq.pop_front();
            }

            while (!dq.empty() && nums[dq.back()] < nums[i])
            {
                dq.pop_back();
            }
            dq.push_back(i);
            vecRes.push_back(nums[dq.front()]);
        }

        return vecRes;
    }
};