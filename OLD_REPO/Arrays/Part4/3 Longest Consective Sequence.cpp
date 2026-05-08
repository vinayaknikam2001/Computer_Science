// LeetCode = https://leetcode.com/problems/longest-consecutive-sequence/description/
// Self = Better Solution
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) 
    {
        sort(nums.begin(), nums.end());
        int ans = INT_MIN, iSeqLen = 1;
        if (nums.size() == 0) //To check if array is empty sequence corner case;
        {
            return 0;
        }

        for (int i=1; i<nums.size(); i++)
        {
            if (nums[i] == nums[i-1]) // To ignore repeating elements in an array;
                continue;
            if (nums[i] == (nums[i-1]+1))
            {
                iSeqLen++;
            }
            else
            {
                iSeqLen = 1;
            }

            ans = max(ans, iSeqLen);
        }


        return max(ans, iSeqLen); //Necessary when nums.size() == 1 for that taken max():);
    }
};


//Optimal Solution But rarely unordered_set<> require O(N) time complexity due to collision in searching.
//Also requires extra O(N) space for unordered_set<>;
//Quite useful when u don't want to modify input vector<>.
//Referanced.
class Solution {
public:
    int longestConsecutive(vector<int>& nums) 
    {
        unordered_set<int> uSet;
        for (auto i:nums) {
            uSet.insert(i);
        }

        int iCnt=0, iMaxCnt = 0;
        for (auto i:uSet)
        {
            if (uSet.find(i-1) == uSet.end())
            {
                int j=1; iCnt=1;
                while (uSet.find(i+j) != uSet.end())
                {
                    ++j; ++iCnt;
                }
            }
            iMaxCnt = max(iCnt, iMaxCnt);
        }

        return iMaxCnt;
    }
};