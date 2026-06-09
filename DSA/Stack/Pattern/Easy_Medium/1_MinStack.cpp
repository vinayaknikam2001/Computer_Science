/*
LeetCode 155 = https://leetcode.com/problems/min-stack/description/
Date = 09-Jun-2026
RevisedDate = NA
Solution = Referanced
TC = 1) O(1)    2) O(1)
SC = 2) O(N)    2) O(N)
*/



#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef unsigned long long ull;


/**Approch using O(N) Extra Space **/
class MinStack 
{
private:
    stack<pair<int, int>> m_STK;
public:
    MinStack() 
    {            
    }
    
    void push(int value)
    {
        pair<int, int> pr_Val;
        int iLastMin = INT_MAX;
        if (!m_STK.empty())
        {
            iLastMin = m_STK.top().second;
        }
        pr_Val.first = value;
        pr_Val.second = min(iLastMin, value);
        m_STK.push(pr_Val);
    }
    
    void pop() 
    {
        m_STK.pop();
    }
    
    int top() 
    {
        return m_STK.top().first;
    }
    
    int getMin() 
    {
        return m_STK.top().second;    
    }
};




/** Gemini Suggested code to optimize O(N) space little bit **/
class MinStack {
private:
    std::stack<int> stk;
    std::stack<int> minStk;

public:
    MinStack() {
        // Fast I/O trick for LeetCode
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(NULL);
    }
    
    void push(int val) {
        stk.push(val);
        // Push to minStk if it's empty OR val is less than or equal to current min
        if (minStk.empty() || val <= minStk.top()) {
            minStk.push(val);
        }
    }
    
    void pop() {
        // If the element being removed is the current minimum, pop it from minStk too
        if (stk.top() == minStk.top()) {
            minStk.pop();
        }
        stk.pop();
    }
    
    int top() {
        return stk.top();
    }
    
    int getMin() {
        return minStk.top();
    }
};





/** O(1) time and O (1) space complexity using mathematical formaule to keep track of minimum **/

typedef long long int lli;
typedef unsigned long long ull;
class MinStack 
{
private:

    stack<lli> m_STK;
    lli m_iMin;

public:
    MinStack() {
        m_iMin = INT_MAX;
    }
    
    void push(int value) 
    {
        if (m_STK.empty())
        {
            m_iMin = value;
        }
        if (value >= m_iMin)
        {
            m_STK.push(value);
        }
        else
        {
            lli iVal = (lli)(2 * (lli)value - m_iMin);
            m_STK.push(iVal);
            m_iMin = value;
        }
    }
    
    void pop() 
    {
        if (m_STK.top() < m_iMin)
        {
            m_iMin = (lli)(2 * m_iMin) - (lli)m_STK.top();
        }
        m_STK.pop();
    }
    
    int top() 
    {
        lli iRes = m_STK.top();
        if (m_STK.top() < m_iMin)
        {
            iRes = m_iMin;
        }
        return iRes;
    }
    
    int getMin() 
    {
        return m_iMin;
    }
};
