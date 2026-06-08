/*
LeetCode 18 = https://leetcode.com/problems/4sum/description/
Date = 06-June-2026
RevisedDate = NA

Need to optimise by removing set.

Solution = Referanced
TC = (O(nlogn) + O(N^3))
SC = O(N)
*/

typedef long long int lli;
class Solution {
public:

vector<vector<int>> fourSum(vector<int>& nums, int target) 
{
    sort(nums.begin(), nums.end());
    set<vector<int>> res;//--------------Set is necessary for unique quadruplets--------------//

    int n = nums.size();
    
    for(int i=0; i<n; ++i)
    {
        for(int j=i+1; j<n; ++j)
        {
            int st = j + 1;
            int end = n-1;
            
            while (st < end)
            {
                lli sum = 0;
                sum = (lli)nums[i] + (lli)nums[j] + (lli)nums[st] + (lli)nums[end];//----------Remember to use lli and typecast it properly---------
                if (sum == target)
                {
                    res.insert({nums[i], nums[j], nums[st], nums[end]});//----------It's necessary to use set inorder to get all unique quadruplets combinations...
                    ++st; --end;//-------------------------Remember to not to break from looop directly as there more possibilities might exist.
                }
                else if (sum < target)
                    ++st;
                else
                    --end;
            }
            
        }
    }

    vector<vector<int>> ans;
    for(auto v:res)
    {
        ans.push_back(v);
    }

    return ans;
}

};