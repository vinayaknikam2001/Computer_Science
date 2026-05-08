//LeetCode = https://leetcode.com/problems/delete-node-in-a-linked-list/description/
//Brute solution self

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
    void deleteNode(ListNode* node) 
    {
        ListNode *pNode = node;
        ListNode *prevNode = NULL;
        while (pNode->next)
        {
            pNode->val = pNode->next->val;
            prevNode = pNode;
            pNode = pNode->next;
        }
        prevNode->next = NULL;
    }
};

//Optimal Soltion O(1)
//Referanced
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
    void deleteNode(ListNode* node) 
    {
        node->val = node->next->val;
        node->next = node->next->next;
    }
};