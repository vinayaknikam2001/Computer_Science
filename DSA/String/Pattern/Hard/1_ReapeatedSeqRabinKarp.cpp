/*
LeetCode 187 = https://leetcode.com/problems/repeated-dna-sequences/description/
Date = 08-Jun-2026
RevisedDate = NA
Solution = RabinKarp Referanced (Problem Self)
TC = 1) O(N*K)      2) O(N)
SC = 



IMP****= More things to learn in this problem can be solved unsing bit masking and Hashing more optimized ways.
*/



#include <bits/stdc++.h>
using namespace std;



//Approach 1 Rabin Karp using single hash technique
#define TEN 10
typedef long long int lli;
typedef unsigned long long ull;

constexpr lli BASE1 = 31, BASE2 = 37, MOD1 = 1e9+7, MOD2 = 1e9+9;

constexpr lli getPower(lli BASE, lli EXP, lli MOD)
{
    lli iRes = 1;
    for (int i=0; i<EXP; ++i)
    {
        iRes = (iRes * BASE) % MOD;
    }

    return iRes;
}

constexpr lli POW1 = getPower(BASE1, TEN-1, MOD1), POW2 = getPower(BASE2, TEN-1, MOD2);

class Solution 
{
public:
    vector<string> findRepeatedDnaSequences(string s) 
    {
        int iSize = s.size();
        //vector<int> vecHash(iSize, 0);
        set<int> resSet;
        unordered_map<lli, list<int>> ump1;
        vector<string> vecRes;
        if (iSize <= TEN)
        {
            return vecRes;
        }

        lli iHash1 = 0; //iHash2 = 0;
        
        for (int i=0; i<TEN; ++i)
        {
            iHash1 = (iHash1 * BASE1 + s[i]) % MOD1;
            //iHash2 = (iHash2 * BASE2 + s[i]) % MOD2;
        }
        ump1.emplace(iHash1, std::list<int>{0});

        for (int i=1; (i+TEN-1) < iSize; ++i)
        {
            iHash1 = (iHash1 - (lli)s[i-1] * POW1 % MOD1+ MOD1) % MOD1;
            iHash1 = (iHash1 * BASE1 + (lli)s[i+(TEN-1)]) % MOD1;

            auto itr = ump1.find(iHash1);
            if (itr == ump1.end())
            {
                ump1.emplace(iHash1, std::list<int>{i});
            }
            else
            {
                std::list<int> &lst = itr->second;
                bool bMatch = true;
                for (int iIdx:lst)
                {      
                    bMatch = true;              
                    for (int j=0; j<TEN; ++j)
                    {
                        if (s[i+j] != s[iIdx+j])
                        {
                            bMatch = false;                        
                            break;
                        }
                    }
                    if (bMatch)
                    {
                        resSet.insert(iIdx);                        
                        break;
                    }
                }
                if (!bMatch)
                {
                    lst.push_back(i);
                }
            }
        }

        for (auto iVal:resSet)
        {
            vecRes.push_back(s.substr(iVal, TEN));
        }

        return vecRes;
    }
};








//Rabin-Karp using Double Hash technique
#define TEN 10
typedef long long int lli;

constexpr lli BASE1 = 31, BASE2 = 37;
constexpr lli MOD1 = 1e9+7, MOD2 = 1e9+9;

constexpr lli getPower(lli BASE, lli EXP, lli MOD) {
    lli res = 1;
    for (int i = 0; i < EXP; ++i) res = res * BASE % MOD;
    return res;
}

constexpr lli POW1 = getPower(BASE1, TEN-1, MOD1);
constexpr lli POW2 = getPower(BASE2, TEN-1, MOD2);

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        int n = s.size();
        vector<string> res;
        if (n <= TEN) return res;

        // Store seen (h1,h2) pairs and whether already added to result
        // value: false = seen once, true = already added to result
        unordered_map<lli, unordered_map<lli, bool>> seen;

        lli h1 = 0, h2 = 0;
        for (int i = 0; i < TEN; ++i) {
            h1 = (h1 * BASE1 + s[i]) % MOD1;
            h2 = (h2 * BASE2 + s[i]) % MOD2;
        }
        seen[h1][h2] = false;

        for (int i = 1; i + TEN - 1 < n; ++i) {
            // Roll hash 1
            h1 = (h1 - (lli)s[i-1] * POW1 % MOD1 + MOD1) % MOD1;
            h1 = (h1 * BASE1 + s[i + TEN - 1]) % MOD1;
            // Roll hash 2
            h2 = (h2 - (lli)s[i-1] * POW2 % MOD2 + MOD2) % MOD2;
            h2 = (h2 * BASE2 + s[i + TEN - 1]) % MOD2;

            auto it = seen.find(h1);
            if (it == seen.end()) {
                seen[h1][h2] = false;         // first time seeing this h1
            } else {
                auto it2 = it->second.find(h2);
                if (it2 == it->second.end()) {
                    it->second[h2] = false;   // h1 seen before but not h2
                } else if (!it2->second) {
                    res.push_back(s.substr(i, TEN));  // true match, add once
                    it2->second = true;        // mark so we don't add again
                }
                // if it2->second == true: already in result, skip
            }
        }
        return res;
    }
};