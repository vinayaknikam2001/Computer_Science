//LeetCode = https://leetcode.com/problems/valid-anagram/
//Self
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) 
    {
        int sMap[26] = {0}, tMap[26] = {0};
        int i=0, j=0;

        for (auto ch : s) 
        {
            ++sMap[(ch-'a')];
        }

        for (auto ch : t)
        {
            ++tMap[(ch-'a')];
        }

        for (int i=0; i<26; ++i)
        {
            if (sMap[i] != tMap[i])
                return false;
        }

        return true;
    }
};