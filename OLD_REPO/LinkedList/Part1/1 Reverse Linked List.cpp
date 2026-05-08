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
class Solution {
    ListNode *revHead;
public:

    Solution():revHead{NULL}{};

    ListNode* Reverse(ListNode* node)
    {
        if (node->next == nullptr)
        {
            return revHead = node;
        }

        ListNode *prevNode = node;
        ListNode* tail =  Reverse(node->next);
        tail->next = prevNode;
        prevNode->next = NULL;
        return prevNode;
    }
    ListNode* reverseList(ListNode* head) 
    {

        if (head != NULL)
        {            
            Reverse(head);
        }

        return revHead;    
    }
};