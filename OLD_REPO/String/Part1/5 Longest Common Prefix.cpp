//LeetCode = https://leetcode.com/problems/longest-common-prefix/description/
//Self
#include <bits/stdc++.h>
using namespace std;

/*
Time Complexity: O(S)
Where:
S = total number of characters in all strings = s₁ + s₂ + ... + sₙ
n = number of strings
m = length of the shortest string

Why?
The outer while loop iterates at most m times, where m is the length of the shortest string.
Inside the loop, for each character index i, you compare that character across all n strings → O(n) per character.
Worst case: all n strings are of length m and identical → total comparisons = n * m, which is bounded by O(S).
So, worst-case time complexity = O(S).

Space : O(1) If exclude the output string else O(m) where m is length of minimum string in Vector.
*/

class Solution {

    void getFirstCharacter(vector<string>& strs, char &ch, int &i)
    {
        ch = '\0';
        if (i < strs[0].size()) {
            ch = strs[0][i];
        }
    }
public:
    string longestCommonPrefix(vector<string>& strs) 
    {
        int size = strs.size(), i=0;
        string result = "";
        bool breakLoop = false;

        while (!breakLoop)
        {
            char firstChar;
            getFirstCharacter(strs, firstChar, i);
            for (int j=0; j<size; ++j)
            {
                if (i < strs[j].size()) {
                    breakLoop = (firstChar != strs[j][i]) ? true : false;
                    if (breakLoop) break;
                }
                else {
                    breakLoop = true; 
                    break;
                }
            }
            if (!breakLoop) {
                result += firstChar;
            }
            ++i;
        }

        return result;
    }
};