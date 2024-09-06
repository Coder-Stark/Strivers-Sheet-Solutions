#include<bits/stdc++.h>
using namespace std;

//DAY 6: LINKED LIST II-----------------------------------------------------------------------------------------------------
//31. INTERSECTION OF 2 LINKED LIST                                    
//BRUTE FORCE  (STORE IN SET)                                                {T.C = O(N), S.C = O(N)}
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_set<ListNode*>st;
        ListNode* temp1 = headA;
        ListNode* temp2 = headB;
        while(temp1){
            st.insert(temp1);
            temp1 = temp1->next;
        }
        while(temp2){
            if(st.count(temp2)) return temp2;
            else temp2 = temp2->next;
        }
        return NULL;                                        //not intersecting
    }
};

//OPTIMAL APPROACH                                                             {T.C = O(N), S.C = O(1)}
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* temp1 = headA;
        ListNode* temp2 = headB;

        while(temp1 != temp2){
            temp1 = temp1->next;
            temp2 = temp2->next;
            if(temp1 == temp2) return temp1;
            if(temp1 == NULL) temp1 = headB;             //after ending 1 ll move to another head
            if(temp2 == NULL) temp2 = headA;
        }
        return temp1;
    }
};
/*
Example 1:
Input: intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
Output: Intersected at '8'
Explanation: The intersected node's value is 8 (note that this must not be 0 if the two lists intersect).
From the head of A, it reads as [4,1,8,4,5]. From the head of B, it reads as [5,6,1,8,4,5]. There are 2 nodes before the intersected node in A; There are 3 nodes before the intersected node in B.
- Note that the intersected node's value is not 1 because the nodes with value 1 in A and B (2nd node in A and 3rd node in B) are different node references. In other words, they point to two different locations in memory, while the nodes with value 8 in A and B (3rd node in A and 4th node in B) point to the same location in memory.

Example 2:
Input: intersectVal = 2, listA = [1,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
Output: Intersected at '2'
Explanation: The intersected node's value is 2 (note that this must not be 0 if the two lists intersect).
From the head of A, it reads as [1,9,1,2,4]. From the head of B, it reads as [3,2,4]. There are 3 nodes before the intersected node in A; There are 1 node before the intersected node in B.
*/


//32. LINKED LIST CYCLE                                                   {T.C = O(N), S.C = O(1)}
class Solution {
public:
    bool hasCycle(ListNode *head) {
        //base case
        if(!head) return false;

        ListNode* slow = head;
        ListNode* fast = head;
        while(slow->next && fast && fast->next){            //slow->next (not required)
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast) return true;
        }
        return false;
    }
};
/*
Example 1:
Input: head = [3,2,0,-4], pos = 1
Output: true
Explanation: There is a cycle in the linked list, where the tail connects to the 1st node (0-indexed).

Example 2:
Input: head = [1,2], pos = 0
Output: true
Explanation: There is a cycle in the linked list, where the tail connects to the 0th node.

Example 3:
Input: head = [1], pos = -1
Output: false
Explanation: There is no cycle in the linked list.
*/


//33. REVERSE NODES IN K GROUPS                                           {T.C = O(N), S.C = O(1)}
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        int len = 0;
        ListNode* temp = head;
        while(temp){
            temp = temp->next;
            len++;
        }

        //base case
        if(!head || len < k) return head;             //len < k return as it is
        
        ListNode* prev = NULL;
        ListNode* curr = head;
        ListNode* next = NULL;
        int count = 0;
        while(curr && count < k){                //reverse 1 to k element
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;

            count++;
        }

        if(next){                                   //recursive call
            head->next = reverseKGroup(next, k);
        }

        return prev;
    }
};
/*
Example 1:
Input: head = [1,2,3,4,5], k = 2
Output: [2,1,4,3,5]

Example 2:
Input: head = [1,2,3,4,5], k = 3
Output: [3,2,1,4,5]
*/


//34. PALINDROME LINKED LIST
//BRUTE FORCE (LL TO AA)                                                      {T.C = O(N), S.C = O(N)}
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        vector<int>llToArr;
        while(head){
            llToArr.push_back(head->val);
            head = head->next;
        }
        int n = llToArr.size();
        for(int i = 0 ; i < n/2 ; i++){
            if(llToArr[i] != llToArr[n-1-i]) return false;
        }
        return true;
    }
};


//OPTIMIZED APPROACH (LL)                                                     {T.C = O(N), S.C = O(1)}
class Solution {
public:
    ListNode* reverse(ListNode* head){
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
    bool isPalindrome(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while(fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
        }     
        ListNode* firstHalf  = head;
        ListNode* secondHalf = reverse(slow);              //reverse after curr slow pointer to end

        while(secondHalf){
            if(firstHalf->val != secondHalf->val) return false;
            firstHalf = firstHalf->next;
            secondHalf = secondHalf->next;
        }
        return true;
    }
};
/*
Example 1:
Input: head = [1,2,2,1]
Output: true

Example 2:
Input: head = [1,2]
Output: false
*/


//35. LINKED LIST CYCLE II                                                 {T.C = O(N), S.C = O(1)}
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        int count = 0;
        ListNode* slow = head;
        ListNode* fast = head;
        
        while(fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast){                          //cycle is present
                slow = head;                           //reset slow to zero
                while(slow != fast){                   //reach to required position
                    slow = slow->next;
                    fast = fast->next;
                }
                return slow;
            }
        }
        return NULL;
    }
};
/*
Example 1:
Input: head = [3,2,0,-4], pos = 1
Output: tail connects to node index 1
Explanation: There is a cycle in the linked list, where tail connects to the second node.

Example 2:
Input: head = [1,2], pos = 0
Output: tail connects to node index 0
Explanation: There is a cycle in the linked list, where tail connects to the first node.

Example 3:
Input: head = [1], pos = -1
Output: no cycle
Explanation: There is no cycle in the linked list.
*/


//36. FLATTENING A LINKED LIST                                                  {T.C = O(N*M), S.C = O(1)}
class Solution {
  public:
    Node* merge(Node* a, Node* b){
        Node* ans = new Node(-1);
        Node* temp = ans;
        
        while(a && b){
            if(a->data < b->data){
                temp->bottom = a;                //act bottom as next
                temp = temp->bottom;
                a = a->bottom;
            }else{
                temp->bottom = b;
                temp = temp->bottom;
                b = b->bottom;
            }
        }
        if(a) temp->bottom = a;
        else  temp->bottom = b;
        
        ans = ans->bottom;
        return ans;
    }
    Node *flatten(Node *root) {
        //base case
        if(!root || !root->next) return root;
        
        root->next = flatten(root->next);               //recursive call
        root = merge(root, root->next);
        
        return root;
    }
};
/*
Examples:
Input:
Output:  5-> 7-> 8- > 10 -> 19-> 20-> 22-> 28-> 30-> 35-> 40-> 45-> 50.
Explanation: The resultant linked lists has every node in a single level.(Note: | represents the bottom pointer.)

Input:
Output: 5-> 7-> 8-> 10-> 19-> 22-> 28-> 30-> 50
Explanation: The resultant linked lists has every node in a single level.(Note: | represents the bottom pointer.)
*/