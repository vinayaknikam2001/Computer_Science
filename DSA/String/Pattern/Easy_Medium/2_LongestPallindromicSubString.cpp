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


/*---------------------- Brute Forced Soluton ----------------------*/
/* This  solution got memory  limit exceeded... */
#define ARR_SIZE 1000
class Solution {

private:
    short dp[ARR_SIZE][ARR_SIZE];
public:

    bool isPal(string s, int st, int end)
    {
        if (st >= end)
            return true;

        if (dp[st][end] != -1)
            return dp[st][end];

        if (s[st] == s[end])
        {
            return dp[st][end] = isPal(s, st+1, end-1);
        } 
        else 
        {
            return dp[st][end] = false;
        }

    }

    string longestPalindrome(string s) 
    {
        int n = s.size();
        int st = 0, size = 1, maxLen = 1;
        memset(dp, -1, sizeof (dp));
        for (int i=0; i<n; ++i)
        {
            for (int j=i+1; j<n; ++j)
            {
                int len = j-i+1;
                if (isPal(s, i, j))
                {
                    if (len > maxLen)
                    {
                        maxLen = len;
                        st = i; size = len;
                    }
                }
            }
        }    

        string ans = s.substr(st, size); 
        return ans;
    }
};



/*----------------------- Optimal Solution ---------------------------*/
class Solution {
public:
    string longestPalindrome(string s) 
    {
        int n = s.size();
        if (n==1)
            return s;
        short start = 0, maxLen = 1;
        //For odd length string
        for (int i=0; i<(n-1); ++i)
        {
            short left=i, right=i;
            while (left >=0 && right < n)
            {
                if (s[left] == s[right]) {
                    --left; ++right;
                }                    
                else {
                    break;
                }
            }
            ++left; --right;
            short len = right-left+1;
            if (len > maxLen)
            {
                start = left; maxLen = len;
            }
        }

        //For even length string
        for (int i=0; i<(n-1); ++i)
        {
            short left=i, right=i+1;
            while (left >=0 && right < n)
            {
                if (s[left] == s[right]) {
                    --left; ++right;
                }
                else {
                    break;
                }
            }
            ++left; --right;
            short len = right-left+1;
            if (len > maxLen)
            {
                start = left; maxLen = len;
            }
        }

        return s.substr(start, maxLen);

    }
};



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