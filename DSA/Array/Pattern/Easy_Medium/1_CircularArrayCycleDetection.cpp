/*
LeetCode 457 = https://leetcode.com/problems/circular-array-loop/
Date = 19-May-2026
TC = 
SC = 
*/


class Solution 
{
    private:

    int getNextIndex(int i, vector<int>&nums, bool bSign)
    {
        int iSize = nums.size();
        int iVal = nums[i];
        int idx = (i + nums[i]) % iSize;
        idx = (idx < 0) ? iSize - abs(idx) : idx; 
        if (bSign != (iVal > 0) || idx == i)
        {
            idx = -1;
        }
        return idx;
    }


public:
    bool circularArrayLoop(vector<int>& nums) 
    { 
        vector<bool> bVisited(nums.size(), false);
        int iFast = 0, iSlow = 0;
        for (int i=0; i<nums.size(); ++i)
        {
            if (!bVisited[i])
            {
                iFast = iSlow = i;
                bVisited[i] = true;
                bool bSign = (nums[i] > 0);
                while (true)
                {
                    bVisited[iSlow] = true;
                    bVisited[iFast] = true;
                    iFast = getNextIndex(iFast, nums, bSign);
                    iSlow = getNextIndex(iSlow, nums, bSign);
                    if (iFast == -1 || iSlow == -1)
                    {
                        break;
                    }
                    iFast = getNextIndex(iFast, nums, bSign);
                    if (iFast == -1)
                    {
                        break;
                    }

                    if (iFast == iSlow)
                    {
                        return true;
                    }
                }
            }            
        }


        return false;
    }
};