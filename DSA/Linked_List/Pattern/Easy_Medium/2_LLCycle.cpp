/*
LeetCode 141 = https://leetcode.com/problems/linked-list-cycle/description/
Date = 16-June-2026
RevisedDate = NA
Solution = Referanced
TC = 1) O(N)
SC = 2) O(1)


Note: Floyd-Warshall's algo or Hare and tortoise algo.
*/



/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) 
    {
        ListNode *pSlow = (nullptr != head) ? head->next : head;
        ListNode *pFast = (nullptr != pSlow) ? pSlow->next : pSlow;

        bool bIsCycle = false;
        while (nullptr != pFast)
        {
            if (pFast == pSlow)
            {
                bIsCycle = true;
                break;
            }
            pFast = (nullptr != pFast->next) ? pFast->next->next : pFast->next;
            pSlow = pSlow->next;
        }

        return bIsCycle;
    }
};


