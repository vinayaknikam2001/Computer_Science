//LeetCode = https://leetcode.com/problems/string-to-integer-atoi/
//Self
//Problem includes lot of corner cases
#include <bits/stdc++.h>
using namespace std;

#define MIN_INT_32 -2147483648
#define MAX_INT_32 2147483648-1
class Solution {
public:
    int myAtoi(string s) 
    {
        /*
        1> Ignore spaces.
        2> OnceNoStarted After that ignore any invalid character.
        3>
        */            
        int iSize = s.size();
        bool bNumStart = false, bSigned = false, bZeroEnd = false;
        short iSign = 1;
        long long int iDecimalPlace = 10, iNumber = 0;
        short iDecimalCnt = 0;

        for (int i=0; i<iSize; ++i)
        {            
            if (s[i] == ' ' && (!bNumStart)) 
            {
                continue;
            }
            
            if (s[i] == '+' || s[i] == '-') 
            {
                if (bNumStart || bSigned) {
                    break;
                }
                iSign = (s[i]=='-') ? -1 : 1;
                bSigned = true;
                bNumStart = true;
                continue;
            }

            short iDiff = s[i] - '0';
            if (iDiff > 9 || iDiff < 0)
            {
                break;
            }
            
            bNumStart = true;
            bZeroEnd = (iDiff != 0) ? true: bZeroEnd;
            if (iDecimalCnt > 10)
            {
                break;
            }
            iNumber = (long long int)((iNumber * iDecimalPlace) + iDiff);
            if (bZeroEnd) {
                ++iDecimalCnt;
            }
        }

        iNumber *= iSign;
        iNumber  = (iNumber < MIN_INT_32) ? MIN_INT_32 : iNumber;
        iNumber  = (iNumber > MAX_INT_32) ? MAX_INT_32 : iNumber;
        return iNumber;
    }
};