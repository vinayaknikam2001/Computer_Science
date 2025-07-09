// LeetCode = https://leetcode.com/problems/majority-element-ii/description/
// Referenced 

#define MOD -1e7+1

class Solution {
public:

/*
SC = O(1)
TC = O(2N) = O(N)
*/
    vector<int> majorityElement(vector<int>& nums) 
    {
    
        int n1 = MOD, n2 = MOD;
        int cnt1 = 0, cnt2 = 0;
        
        for(int i=0; i<nums.size(); ++i)
        {

            if (cnt1 == 0 && nums[i] != n2)///////////////////-----------Remeber this corner case
            {
                n1 = nums[i];
                ++cnt1;
            }
            else if (cnt2 == 0 && nums[i] != n1) ////////////-------------Remeber this corner case
            {
                n2 = nums[i];
                ++cnt2;
            }
            else if (nums[i] == n1)
            {
                ++cnt1;
            }
            else if (nums[i] == n2)
            {
                ++cnt2;
            }
            else
            {
                --cnt1; --cnt2;
            }


        }

        int tar = nums.size()/3;
        cnt1 = 0; cnt2 = 0;
        for(auto i:nums)
        {
            if (i == n1)
                ++cnt1;
            else if(i == n2)
                ++cnt2;
        }
        vector<int> ans;
        if (cnt1 > tar)
            ans.push_back(n1);
        if (cnt2 > tar)
            ans.push_back(n2);
        

        return ans;
    }
};