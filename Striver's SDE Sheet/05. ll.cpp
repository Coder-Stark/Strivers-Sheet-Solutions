#include<bits/stdc++.h>
using namespace std;


//DAY 5: LINKED LIST I-----------------------------------------------------------------------------------------------------
//25. REVERSE A LINKED LIST                                               {T.C = O(N), S.C = O(1)}
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = NULL;
        ListNode* curr = head;
        ListNode* next = NULL;

        while(curr){
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
};
/*
Example 1:
Input: head = [1,2,3,4,5]
Output: [5,4,3,2,1]

Example 2:
Input: head = [1,2]
Output: [2,1]

Example 3:
Input: head = []
Output: []
*/


//26. MIDDLE OF THE LINKED LIST                                                 {T.C = O(N), S.C = O(1)}
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        //base case
        if(!head) return head;
        
        ListNode* slow = head;
        ListNode* fast = head;

        while(fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
};
/*
Example 1:
Input: head = [1,2,3,4,5]
Output: [3,4,5]
Explanation: The middle node of the list is node 3.

Example 2:
Input: head = [1,2,3,4,5,6]
Output: [4,5,6]
Explanation: Since the list has two middle nodes with values 3 and 4, we return the second one.
*/


//27. MERGE 2 SORTED LINKED LIST                                            {T.C = O(N), S.C = O(N+M{RECURSIVE STACK})}
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        //base case
        if(!list1) return list2;
        if(!list2) return list1;

        if(list1->val <= list2->val){
            list1->next = mergeTwoLists(list1->next, list2);
            return list1;
        }else{
            list2->next = mergeTwoLists(list1, list2->next);
            return list2;
        }
    }
};
/*
Example 1:
Input: list1 = [1,2,4], list2 = [1,3,4]
Output: [1,1,2,3,4,4]

Example 2:
Input: list1 = [], list2 = []
Output: []

Example 3:
Input: list1 = [], list2 = [0]
Output: [0]
*/


//28. REMOVE NTH NODE FROM END OF LIST                                         {T.C = O(N), S.C = O(1)}
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(NULL);
        dummy->next = head;

        ListNode* slow = dummy;
        ListNode* fast = dummy;

        while(n--){                               //move fast n steps from beginning
            fast = fast->next;
        }
        while(fast->next){                       //then move fast and slow simultaneously     
            slow = slow->next;
            fast = fast->next;
        }
        slow->next = slow->next->next;           //slow->next is required node to delete

        return dummy->next;
    }
};
/*
Example 1:
Input: head = [1,2,3,4,5], n = 2
Output: [1,2,3,5]

Example 2:
Input: head = [1], n = 1
Output: []

Example 3:
Input: head = [1,2], n = 1
Output: [1]
*/


//29. ADD TWO NUMBERS (IN LINKED LIST)                                       {T.C = O(N), S.C = O(N)}
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(NULL);
        ListNode* temp = dummy;
        int carry = 0;
        while(l1 || l2 || carry){
            int sum = 0;
            if(l1){
                sum += l1->val;
                l1 = l1->next;
            }
            if(l2){
                sum += l2->val;
                l2 = l2->next;
            }
            sum += carry;
            carry = sum / 10;
            ListNode* extra = new ListNode(sum % 10);
            temp->next = extra;
            temp = temp->next;
        }
        return dummy->next;
    }
};
/*
Example 1:
Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [7,0,8]
Explanation: 342 + 465 = 807.

Example 2:
Input: l1 = [0], l2 = [0]
Output: [0]

Example 3:
Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
Output: [8,9,9,9,0,0,0,1]
*/


//30. DELETE NODE IN A LINKED LIST                                        {T.C = O(1), S.C = O(1)}
class Solution {
public:
    void deleteNode(ListNode* node) {
        node->val = node->next->val;
        node->next = node->next->next;
    }
};
/*
Example 1:
Input: head = [4,5,1,9], node = 5
Output: [4,1,9]
Explanation: You are given the second node with value 5, the linked list should become 4 -> 1 -> 9 after calling your function.

Example 2:
Input: head = [4,5,1,9], node = 1
Output: [4,5,9]
Explanation: You are given the third node with value 1, the linked list should become 4 -> 5 -> 9 after calling your function.
*/




