// LeetCode = https://takeuforward.org/interviews/strivers-sde-sheet-top-coding-interview-problems/#google_vignette
// Self
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ans(2);
        unordered_map<int, int> ump;
        int idx = 0;
        for(auto i:nums)
        {
            if(ump.find((target-i)) != ump.end()){
                ans[0] = idx;
                ans[1] = ump[(target-i)];
            }
            ump[i] = idx;
            idx++;
        }
        
        return ans;
    }
};