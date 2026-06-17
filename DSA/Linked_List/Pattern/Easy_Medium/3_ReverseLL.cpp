/*
LeetCode 206 = https://leetcode.com/problems/reverse-linked-list/description/
Date = 17-Jun-2026
RevisedDate = NA
Solution = Self
TC = 1) O(N)
SC = 1) O(1)    2) O(N) when done using recursion it takes stack space
*/


#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef unsigned long long ull;


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;b
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution 
{

    ListNode* reverseLL(ListNode* pCrntNode)
    {
        if (nullptr == pCrntNode || nullptr == pCrntNode->next)
        {
            return pCrntNode;
        }
        ListNode *pHeadNode = reverseLL(pCrntNode->next);
        //pHeadNode->next = 
        pCrntNode->next->next = pCrntNode;
        pCrntNode->next = nullptr;
        return pHeadNode;
    }

public:
    ListNode* reverseList(ListNode* head) 
    {
        //return reverseLL(head); //Using recursive method

        ListNode *pPrevNode = nullptr, *pCrntNode = head;

        while (nullptr != pCrntNode)
        {
            ListNode *pTMPNode = pCrntNode->next;
            pCrntNode->next = pPrevNode;
            pPrevNode = pCrntNode;
            pCrntNode = pTMPNode;
        }

        return pPrevNode;
    }
};
