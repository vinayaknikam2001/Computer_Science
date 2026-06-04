/*
LeetCode 5 = https://leetcode.com/problems/longest-palindromic-substring/description/
Date = 25-May-2026
RevisedDate = NA
Solution = Referanced
TC = 1) Brute = O(N^3)  2) Better = O(N^2)   3) Best = O (N) using manacher's algorithm
SC = 
*/
#include <bits/stdc++.h>
using namespace std;

//Using Manacher's Algorithm
class Solution 
{
private:

    string stringTransform(const string &str)
    {
        string sRes = "#";
        for (char ch:str)
        {
            sRes += ch;
            sRes += '#';
        }
        return std::move(sRes);
    }

public:
    string longestPalindrome(string s) 
    {
        string sTrans = stringTransform(s);
        vector<int> vPal(sTrans.size(), 0);

        int iCenter = 0, iRight = 0;
        int iMax = INT_MIN, iCidx = 0;

        for (int i=0; i<sTrans.size(); ++i)
        {
            int iMirror = (2 * iCenter) - i;

            if (i < iRight)
            {
                vPal[i] = min(vPal[iMirror], (iRight-i));
            }

            while ((i - vPal[i] - 1) >= 0 
            && (i + vPal[i] + 1) < sTrans.size() 
            && (sTrans[i - vPal[i] - 1] == sTrans[i + vPal[i] + 1]))            
            {
                ++vPal[i];
            }

            if ((i + vPal[i]) > iRight)
            {
                iCenter = i;
                iRight = i + vPal[i];
            }
            if (vPal[i] > iMax)
            {
                iMax = vPal[i];
                iCidx  = i;
            }
        }

        string sRes = "";
        for (int i=(iCidx-iMax); i<=(iCidx+iMax); ++i)
        {
            if (sTrans[i] != '#')
            {
                sRes += sTrans[i];
            }
        }

        return sRes;
    }
};