/*
 * @lc app=leetcode id=2 lang=cpp
 *
 * [2] Add Two Numbers
 */

// @lc code=start
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
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* result = new ListNode();
        ListNode* pre = result;
        ListNode* assend = result;
        while (l1 != nullptr && l2 != nullptr) {
            int value = l1->val + l2->val + assend->val;
            l2->val = value / 10;
            l1->val = value % 10;
            pre -> next = l1;
            pre = pre -> next;
            assend = l2;
            l1 = l1 -> next;
            l2 = l2 -> next;
        }
        if (l1 == nullptr) {
            l1 = l2;
        }
        while (l1 != nullptr) {
            int value = l1->val + assend->val;
            assend->val = value / 10;
            pre->next = l1;
            l1->val = value % 10;
            l1 = l1->next;
            pre = pre->next;
        }
        if (assend->val != 0) {
            pre->next = assend;
            assend->next = nullptr;
        }
        return result->next;
    }
};
// @lc code=end

/**
 * @brief 
 * 1568/1568 cases passed (11 ms)
 * Your runtime beats 96.2 % of cpp submissions
 * Your memory usage beats 99.35 % of cpp submissions (75.4 MB)
 * 
 */
