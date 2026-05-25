/*
LeetCode 151 = https://leetcode.com/problems/reverse-words-in-a-string/description/
Date = 23-May-2026
RevisedDate = 23-MAy-2026
Solution = Self
TC = 
SC = 
// Took a lot time for this 42 Mins.
*/


#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    string reverseWords(string s) 
    {
        stack<char> st;
        int n = s.size();
        string ans;
        bool bAddSpace = false;
        for (int i=n-1; i>=0; i--)
        {
            if (s[i] == ' ')
            {
                bAddSpace = (!st.empty()) ? true : bAddSpace;
                while (!st.empty())
                {
                    ans += st.top();
                    st.pop();
                }
                continue;
            }
            if (bAddSpace)
            {
                ans += ' ';
                bAddSpace = false;
            }
            st.push(s[i]);
        }

        while(!st.empty())
        {
            ans += st.top();
            st.pop();
        }
        
        return ans;
    }
};



//Revised C++ solution.
class Solution {
public:
    void addWord(string &str, stack<char>&stkWord)
    {
        bool bIsWord = !stkWord.empty();
        while (!stkWord.empty())
        {
            char c = stkWord.top();
            str += c;
            stkWord.pop();
        }
        if (bIsWord) {
            str += ' ';
        }
    }

    string reverseWords(string s) 
    {
        string res = "";
        stack<char> stkWord;
        int iSize = s.size();

        for (int i=iSize-1; i>=0; --i)
        {
            if (s[i] == ' ') 
            {
                addWord(res, stkWord);
                continue;
            }
            stkWord.push(s[i]);
        }
        addWord(res, stkWord);
        if (res[res.size()-1] == ' ')
        {
            res.pop_back();
        }

        return res;
    }
};