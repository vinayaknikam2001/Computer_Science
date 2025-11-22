// LeetCode = https://leetcode.com/problems/longest-substring-without-repeating-characters/description/
// Self using normal approach
#include <bits/stdc++.h>
using namespace std;

/*#########-------------Normal Approach--------------########*/
class Solution {
public:
int lengthOfLongestSubstring(string s) 
{
    int n = s.size();
    int maxLen = 0;

    for (int i=0; i<n; ++i)
    {
        set<char> subString;
        int len = 0;
        for (int j=i; j<n; ++j)
        {
            subString.insert(s[j]);
            ++len;
            if (len != subString.size())
                break;
            else
                maxLen = max(maxLen, len);
        }
    }

    return maxLen;
}
};


/*############------------Optimal Approach--------------##########*/

int lengthOfLongestSubstring(string s) 
{
    int n = s.size();
    int maxLen = 0, len = 0, left = 0, right = 0;
    vector<int> subMap(256, -1);

    while (right < n)
    {
        if (subMap[s[right]] != -1)
        {
//Below it is necessary to check max of repeating element index and our current left ptr.
//It's a corner case.
            left = max (subMap[s[right]] + 1, left);
        }
        
        subMap[s[right]] = right;

        len  = right - left + 1;
        maxLen = max(maxLen, len);
        
        ++right;
    }

    return maxLen;
}

