/*
LeetCode 28 = https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/description/
Date = 04-Jun-2026
RevisedDate = NA
Solution = Referanced
TC = 1) Brute = O(N^2)  2) Best = O (N + M) using KMP algorithm
SC = 

Testcases for observation in KMP
Case 1)
Needle   = "ssads"
HeyStack =  "ssassads"

Case 2)
Needle   = "sasadbc"
HeyStack = "sasasadbc"

Case 3)
Needle = "AABAAA"
index:    0  1  2  3  4  5
pattern:  A  A  B  A  A  A
lps:      0  1  0  1  2  ?   ← computing lps[5]
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef unsigned long long ull;


//KMP Algo Optimal
class Solution 
{
    vector<int> buildLPS(string str)
    {
        vector<int> vecLPS(str.size(), 0);
        int i = 1, iSize = str.size(), len = 0;
        while (i < iSize)
        {
            if (str[i] == str[len])
            {
                vecLPS[i++] = ++len;
            }
            else
            {
                if (len != 0)
                {
                    len = vecLPS[len-1];    //IMP Case3) Why just fall back ?
                }
                else
                {
                    vecLPS[i++] = 0;
                }
            }
        }
        return std::move(vecLPS);
    }

public:
    int strStr(string haystack, string needle) 
    {
        vector<int> vecLPS = buildLPS(needle);
        int i=0, j=0, iSizeH = haystack.size(), iSizeN = needle.size();
        
        while (i < iSizeH)
        {
            if (haystack[i] == needle[j])
            {
                ++i; ++j;
            }

            if (j == iSizeN)
            {
                return (i-iSizeN);
            }
            else if (i < iSizeH && (haystack[i] != needle[j]))
            {
                if (j != 0)
                {
                    j = vecLPS[j-1];    //IMP Case3) Why just fall back ?
                }
                else
                {
                    ++i;
                }
            }
        }


        return -1;
    }
};