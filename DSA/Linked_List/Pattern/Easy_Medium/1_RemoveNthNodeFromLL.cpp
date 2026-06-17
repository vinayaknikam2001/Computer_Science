/*
LeetCode 19 = https://leetcode.com/problems/remove-nth-node-from-end-of-list/description/
Date = 15-June-2026
RevisedDate = NA
Solution = Referanced
TC = 1) O(N)
SC = 2) O(1)
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef unsigned long long ull;
    
    

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

/** Most Optimal Solution **/
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        ListNode *pPrevNode = nullptr, *pCrntNode = head;
        int i = 1;
        while (pCrntNode!=nullptr)
        {
            pPrevNode = (nullptr != pPrevNode) ? pPrevNode->next : pPrevNode;
            if (i == (n+1))
            {
                pPrevNode = head;
            }
            pCrntNode = pCrntNode->next;
            ++i;
        }
        if (nullptr != pPrevNode)
        {
            ListNode *pDelNode = pPrevNode->next;
            pPrevNode->next = pPrevNode->next->next;
            pDelNode->next = nullptr;
            delete pDelNode;
        }
        else
        {
            pPrevNode = head;
            head = head->next;
            pPrevNode->next = nullptr;
            delete pPrevNode;
        }


        return head;
    } 
};