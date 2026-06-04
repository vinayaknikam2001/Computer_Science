// LeetCode 13 = https://leetcode.com/problems/roman-to-integer/
// Self Solved
#include <bits/stdc++.h>
using namespace std;

class Solution 
{
private:
    map<char, short> romanMap;
public:

    Solution()
    {
        romanMap['I'] = 1;
        romanMap['V'] = 5;
        romanMap['X'] = 10;
        romanMap['L'] = 50;
        romanMap['C'] = 100;
        romanMap['D'] = 500;
        romanMap['M'] = 1000;
    }
    int romanToInt(string s) 
    {
        int i=0, iSize = s.size();
        int iSum = 0;
        while (i < iSize)
        {
            int n1=0, n2=0;
            n1 = romanMap[s[i]];
            if (i+1 < iSize)
            {
                if ( romanMap[s[i]] < romanMap[s[i+1]] )
                {
                    n2 = romanMap[s[i+1]];
                    ++i;
                }
            } 
            iSum += abs(n2 - n1);
            ++i;
        }
        return  iSum;
    }
};