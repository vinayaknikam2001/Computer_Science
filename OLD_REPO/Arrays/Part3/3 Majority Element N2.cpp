// LeetCode link = https://leetcode.com/problems/majority-element/description/
// Self
#include <bits/stdc++.h>
using namespace std;

/*
SC = O(1)
TC = O(N)
*/

#define MOD -10e9+1
class Solution {

public:
    int majorityElement(vector<int>& nums) 
    {
        int arr [] = { nums[0], 1 };

        for (int i=1; i<nums.size(); ++i)
        {
            if (nums[i] == arr[0])
                ++arr[1];
            else
                --arr[1];
            
            if (arr[1] == 0)
            {
                arr[0] = nums[i];
                ++arr[1];
            }
        }

        return arr[0];
    }
};