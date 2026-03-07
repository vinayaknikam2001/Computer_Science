//LeetCode = 
//Self
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) 
    {
        int size = haystack.size();
        int needleSize = needle.size();
        int result = -1;

        for (int i=0; i<size; ++i)
        {
            bool found = false;
            int k = i;
            for (int j=0; j<needleSize; ++j, ++k)
            {
                if (haystack[k] == needle[j]) 
                {
                    if (j == (needleSize-1))
                        found = true;
                }
                else break;
            }
            if (found)
            {
                result = i; break;
            }
        }

        return result;

    }
};



//More better and cleaner code for same problem.
class Solution {
public:
    int strStr(string haystack, string needle) 
    {
        int size = haystack.size();
        int needleSize = needle.size();
        int result = -1;

        for (int i=0; i<size; ++i)
        {
            for (int j=0; j<needleSize; ++j)
            {
                if (haystack[i+j] != needle[j]) {break;}
                else if (j == (needleSize-1)) {return result = i;}
            }
        }

        return result;

    }
};