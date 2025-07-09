#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int JK(vector<int>& nums, int i, int iTarget)
    {
        if (i == iTarget)
        {
            return 0;
        }
        int iJmp = nums[i] + i;
        if (iJmp >= iTarget)
        {
            return 1;
        }
        int iMinJmp = 1e5;
        for (int j=i+1; j<=iJmp; ++j)
        {
            int Crnt = 1 + JK(nums, j, iTarget);
            iMinJmp = min(Crnt, iMinJmp);
        }
        return iMinJmp;
    }

    int jump(vector<int>& nums)
    {
        return JK(nums, 0, nums.size()-1);
    }
};


int main () 
{
    vector<int> v = {2,3,1,1,4};
    Solution s;
    cout << s.jump(v);
    return 0;
}