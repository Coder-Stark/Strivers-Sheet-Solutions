//LINKED LIST
#include<bits/stdc++.h>
using namespace std;


//1D LINKED LIST-----------------------------------------------------------------------------------
//88. INTRODUCTION TO LINKED LIST                                        {T.C = O(N), S.C = O(1)}
//CURR->NEXT = TEMP, CURR = CURR->NEXT
class Solution {
  public:
    Node* constructLL(vector<int>& arr) {
        int n = arr.size();
        //base case
        if(n == 0){
            return NULL;
        }
        Node* head = new Node(arr[0]);                //NULL print 0 1 2 ..
        Node* curr = head;
        for(int i = 1 ; i < n;  i++){
            Node* temp = new Node(arr[i]);
            curr->next = temp;
            curr = curr->next;
        }
        return head;
    }
};
/*
Example 1:
Input:
n = 5
arr = [1,2,3,4,5]
Output:
1 2 3 4 5
Explanation: Linked list for the given array will be 1->2->3->4->5.

Example 2:
Input:
n = 2
arr = [2,4]
Output:
2 4
Explanation: Linked list for the given array will be 2->4.
*/


//89. LINKED LIST INSERTION (BEGGINING & END)                           {T.C = O(1{BEG}, N(END)), S.C = O(1)}
class Solution{
  public:
    Node *insertAtBegining(Node *head, int x) {
       Node* temp = new Node(x);
       temp->next = head;
       return temp;
    }
    
    Node *insertAtEnd(Node *head, int x)  {
       Node* temp = new Node(x);
       if(!head){
           return temp;
       }
       Node* curr = head;
       while(curr->next){
           curr = curr->next;
       }
       curr->next = temp;
       return head;
    }
};
/*
input
1 2 3 5 6 
4
output
4 1 2 3 5 6 4
*/


//90. DELETE A NODE IN A LINKED LIST                                 {T.C = O(1), S.C = O(1)}
//JUST LINK NODE TO NEXT NODE DIRECTLY
class Solution {
public:
    void deleteNode(ListNode* node) {
        node->val = node->next->val;
        node->next = node->next->next;
        //or *node = *node->next;
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


//91. COUNT NODES OF LINKED LIST                                        {T.C = O(N), S.C = O(1)}
//SIMPLE TRAVERSAL ON LL
class Solution
{
    public:
    int getCount(struct Node* head){
        int count = 0;
        while(head){
            head = head->next;
            count++;
        }
        return count;
    }
};
/*
Example 1:
Input:
LinkedList: 1->2->3->4->5
Output: 5
Explanation: Count of nodes in the 
linked list is 5, which is its length.

Example 2:
Input:
LinkedList: 2->4->6->7->5->1->0
Output: 7
Explanation: Count of nodes in the
linked list is 7. Hence, the output
is 7.
*/


//92. SEARCH IN LINKED LIST                                          {T.C = O(N), S.C = O(1)}
//SIMPLE TRAVERSAL AND CHECK KEY
class Solution {
  public:
    bool searchKey(int n, struct Node* head, int key) {
        while(head){
            if(head->data == key){
                return true;
            }
            head = head->next;
        }
        return false;
    }
};
/*
Example:
Input:
n = 4
1->2->3->4
Key = 3
Output:
True
Explanation:
3 is present in Linked List, so the function returns true.
*/


//DOUBLY LINKED LIST -----------------------------------------------------------------------------------------
//93. INTRODUCTION TO DOUBLY LINKED LIST                                  {T.C = O(N), S.C = O(1)}
//CURR->NEXT = TEMP, TEMP->PREV = CURR, CURR = TEMP
class Solution {
  public:
    Node* constructDLL(vector<int>& arr) {
        int n = arr.size();
        if(n == 0){
            return NULL;
        }
        Node* head = new Node(arr[0]);
        Node* curr = head;
        for(int i = 1; i < n ;i++){
            Node* temp = new Node(arr[i]);
            curr->next = temp;
            temp->prev = curr;
            curr = temp;
        }
        return head;
    }
};
/*
Example 1:
Input:
n = 5
arr = [1,2,3,4,5]
Output:
1 2 3 4 5
Explanation: Linked list for the given array will be 1<->2<->3<->4<->5.

Example 2:
Input:
n = 1
arr = [1]
Output:
1
Explanation: Linked list for the given array will be 1.
*/


//94. DOUBLY LINKED LIST INSERTION AT GIVEN POSITION                          {T.C = O(N), S.C = O(1)}
//HANDLE (BEG, END, INBETWEEN)
void addNode(Node *head, int pos, int data)
{
    Node* temp = new Node(data);
    Node* curr = head;
    for(int i = 0 ; i < pos ; i++){         //reach to inserting position
        curr = curr->next;
    }
    if(!curr->next){                        //insert at end
        curr->next = temp;
        temp->prev = curr;
    }else{                                  //insert in between
        temp->next = curr->next;
        temp->prev = curr;
        curr->next->prev = temp;
        curr->next = temp;
    }
}
/*
Example 1:
Input:
LinkedList: 2<->4<->5
p = 2, x = 6 
Output: 2 4 5 6
Explanation: p = 2, and x = 6. So, 6 is
inserted after p, i.e, at position 3
(0-based indexing).

Example 2:
Input:
LinkedList: 1<->2<->3<->4
p = 0, x = 44
Output: 1 44 2 3 4
Explanation: p = 0, and x = 44 . So, 44
is inserted after p, i.e, at position 1
(0-based indexing).
*/


//95. DELETE NODE IN DOUBLY LINKED LIST                                  {T.C = O(N), S.C = O(1)}
//HANDLE (BEG, END, INBETWEEN)
class Solution
{
    public:
    Node* deleteNode(Node *head, int x)
    {
        Node* curr = head;
        int count = 1;
        if(count == x){
            curr->next->prev = NULL;
            return curr->next;
        }
        while(curr->next && count < x){
            curr = curr->next;
            count++;
        }
        curr->prev->next = curr->next;
        if(curr->next){
            curr->next->prev = curr->prev;
        }
        return head;
    }
};
/*
Example 1:
Input:
LinkedList = 1 <--> 3 <--> 4 
x = 3
Output: 1 3  
Explanation: After deleting the node at
position 3 (position starts from 1),
the linked list will be now as 1->3.

Example 2:
Input:
LinkedList = 1 <--> 5 <--> 2 <--> 9  
x = 1
Output: 5 2 9
*/


//96. REVERSE A DOUBLY LINKED LIST
//USING STACK                                                     {T.C = O(N), S.C = O(N)}
class Solution
{
    public:
    Node* reverseDLL(Node * head)
    {
        Node* curr = head;
        stack<int>stk;
        while(curr){
            stk.push(curr->data);
            curr = curr->next;
        }
        curr = head;
        while(curr){
            curr->data = stk.top();
            stk.pop();
            curr = curr->next;
        }
        return head;
    }
};

//USING LL                                                          {T.C = O(N), S.C = O(1)}
class Solution
{
    public:
    Node* reverseDLL(Node * head)
    {
        Node* prev = NULL;
        Node* curr = head;
        Node* forw = NULL;
        
        while(curr){
            forw = curr->next;
            curr->next = prev;
            curr->prev = forw;                   //extra line for dll else ll same
            prev = curr;
            curr = forw;
        }
        return prev;
    }
};
/*
Example 1:
Input:
LinkedList: 3 <--> 4 <--> 5
Output: 5 4 3

Example 2:
Input:
LinkedList: 75 <--> 122 <--> 59 <--> 196
Output: 196 59 122 75
*/


//97. MIDDLE OF THE LINKED LIST                                     {T.C = O(N), S.C = O(1)}
//2 POINTERS (SLOW & FAST)
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while(fast != NULL && fast->next != NULL){
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


//98. REVERSE LINKED LIST (ITERATIVE)                                    {T.C = O(N), S.C = O(1)}
//PREV, CURR, FORW
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = NULL;
        ListNode* curr = head;
        ListNode* forw = NULL;

        while(curr){
            forw = curr->next;
            curr->next = prev;
            prev = curr;
            curr = forw;
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


//99. REVERSE LINKED LIST (RECURSIVE)                                    {T.C = O(N), S.C = O(1)}
//NEWHEAD RECURSIVE CALL
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        //base case
        if(!head || !head->next){
            return head;
        }
        ListNode* newHead = reverseList(head->next);   //recursive call

        //handle 1st node
        head->next->next = head;
        head->next = NULL;
        
        return newHead;
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


//100. LINKED LIST CYCLE / DETECT A LOOP IN LL           {T.C = O(N), S.C = O(1)}
//2 POINTER (SLOW == FAST)
class Solution {
public:
    bool hasCycle(ListNode *head) {
        //base case
        if(!head){
            return false;
        }
        ListNode* slow = head;
        ListNode* fast = head;
        while(slow->next && fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast){
                return true;
            }
        }
        return  false;
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


//101. LINKED LIS CYCLE II  / FIND STARTING POINT IN LL            {T.C = O(N){sequential while loop}, S.C = O(1)}
//CHECK CYCLE AFTER THEN RESET SLOW TO HEAD AND MOVE SLOW & FAST MEETING POINT IS STARTING POINT
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast){
                slow = head;                        //reset slow to head and move simultaneously slow and fast (meeting point is starting cycle)
                while(slow != fast){
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


//102. FIND LENGTH OF LOOP                                         {T.C = O(N), S.C = O(1)}
//IF LOOP , COUNT = 1(SELF), SLOW = SLOW->NEXT, SLOW != FAST : COUNT++
int countNodesinLoop(struct Node *head)
{
    //base case
    if(!head || !head->next){               //1 node no loop
        return 0;
    }
    Node* slow = head;
    Node* fast = head;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast){                   //loop exist
            int count = 1;                  //count of self and update slow
            slow = slow->next;
            while(slow != fast){
                count++;
                slow = slow->next;
            }
            return count;
        }
    }
    return 0;
}
/*
Example 1:
Input:
N = 10
value[]={25,14,19,33,10,21,39,90,58,45}
C = 4
Output: 7
Explanation: The loop is 45->33. So
length of loop is 33->10->21->39->
90->58->45 = 7. The number 33 is
connected to the last node to form the
loop because according to the input the
4th node from the beginning(1 based
index) will be connected to the last
node for the loop.

Example 2:
Input:
N = 2
value[] = {1,0}
C = 1
Output: 2
Explanation: The length of the loop
is 2.
*/


//103. PALINDROME LINKED LIST                                    {T.C = O(N), S.C = O(1)}
//FIND MID, THEN REVERSE (MID->END) AND CHECK START->MID == MID->END
class Solution {
public:
    ListNode* reverse(ListNode* root){
        ListNode* prev = NULL;
        ListNode* curr = root;
        ListNode* forw = NULL;

        while(curr){
            forw = curr->next;
            curr->next = prev;
            prev = curr;
            curr = forw;
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
        ListNode* slowFront = reverse(slow);          //point to mid after list  
        ListNode* slowBack = head;
        while(slowFront){
            if(slowBack->val != slowFront->val){
                return false;
            }
            slowFront = slowFront->next;
            slowBack = slowBack->next;
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


//104. ODD EVEN LINKED LIST                                         {T.C = O(N), S.C = O(1)}
//ODD->NEXT= EVEN->NEXT, EVEN->NEXT = EVEN->NEXT->NEXT : CONNECT ODD & EVEN
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        //base case
        if(!head || !head->next){
            return head;
        }

        ListNode* odd = head;
        ListNode* even = head->next;
        ListNode* temp = even;                 //store head of even ll


        while(even && even->next){             //check second or next element 
            odd->next = even->next;
            even->next = even->next->next;
            odd = odd->next;
            even = even->next;
        }
        odd->next = temp;                     //connect odd->even list

        return head;
    }
};
/*
Example 1:
Input: head = [1,2,3,4,5]
Output: [1,3,5,2,4]

Example 2:
Input: head = [2,1,3,5,6,4,7]
Output: [2,3,6,7,1,5,4]
*/


//105. REMOVE NTH NODE FROM END OF LIST                                 {T.C = O(N), S.C = O(1)}
//DUMMY NODE , SLOW, FAST , REACH TO NTH NODE AND REMOVE (SLOW->NEXT = SLOW->NEXT->NEXT)
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode();
        dummy->next = head;
        ListNode* slow = dummy;
        ListNode* fast = dummy;

        //reach to that node which have to delete from last
        while(n--){
            fast = fast->next;
        }
        while(fast->next){                //move both slow and fast till fast points to end of list(null), slow->next should remove
            slow = slow->next;
            fast = fast->next;
        }

        slow->next = slow->next->next;    //remove links for that particular finding node

        return dummy->next;
    }
};

//WITHOUT DUMMY NODE (WITH DELETE KEYWORD)
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* slow = head;
        ListNode* fast = head;
        while(n--){                     //reach to prev of delete node
            fast = fast->next;
        }
        if(!fast){                      //n = sz of ll
            return head->next;
        }
        while(fast->next){
            slow = slow->next;
            fast = fast->next;
        }
        ListNode* delNode = slow->next;
        slow->next = slow->next->next;
        delete(delNode);

        return head;
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


//106. DELETE THE MIDDLE NODE OF A LINKED LIST                         {T.C = O(N), S.C = O(1)}               
//FIND MID (SLOW & FAST) STORE SLOW(TEMP) AND REMOVE IT (TEMP->NEXT = SLOW->NEXT){SLOW REMOVED}
class Solution {
public:
    ListNode* deleteMiddle(ListNode* head) {
        if(!head || !head->next){
            return NULL;
        }
        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* temp = NULL;

        while(fast && fast->next){
            temp = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        temp->next = slow->next;                       //middle element removed
        delete slow;
        return head;
    }
};
/*
Example 1:
Input: head = [1,3,4,7,1,2,6]
Output: [1,3,4,1,2,6]
Explanation:
The above figure represents the given linked list. The indices of the nodes are written below.
Since n = 7, node 3 with value 7 is the middle node, which is marked in red.
We return the new list after removing this node. 

Example 2:
Input: head = [1,2,3,4]
Output: [1,2,4]
Explanation:
The above figure represents the given linked list.
For n = 4, node 2 with value 3 is the middle node, which is marked in red.

Example 3:
Input: head = [2,1]
Output: [2]
Explanation:
The above figure represents the given linked list.
For n = 2, node 1 with value 1 is the middle node, which is marked in red.
Node 0 with value 2 is the only node remaining after removing node 1.
*/


//107. SORT LIST                                       {T.C = O(N*LOGN), S.C = O(1)}
//MERGE SORT; BREAK LIST INTO 2 PARTS (SLOW & FAST : TEMP->NEXT = NULL) THEN APPLY MERGE SORT(P1, P2 , P3(DUMMY))
class Solution {
public:
    ListNode* mergeList(ListNode* l1, ListNode* l2){
        ListNode* p1 = l1; 
        ListNode* p2 = l2;
        ListNode* dummyNode = new ListNode(-1);
        ListNode* p3 = dummyNode;
        //if both list is nonempty
        while(p1 && p2){
            if(p1->val < p2->val){
                p3->next = p1;
                p1 = p1->next;
            }else{ //p1->val >= p2->val
                p3->next = p2;
                p2 = p2->next;
            }
            p3 = p3->next;                                //move p3 for both above cases
        }
        while(p1){
            p3->next = p1;
            p1 = p1->next;
            p3 = p3->next;
        }
        while(p2){
            p3->next = p2;
            p2 = p2->next;
            p3 = p3->next;
        }
        return dummyNode->next;                          //original starts from next of dummy node
    }
    ListNode* sortList(ListNode* head) {
        //base case
        if(head == NULL || head->next == NULL){
            return head;                                    
        }
        //finding mid element
        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* temp = NULL;

        while(fast && fast->next){
            temp = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        temp->next = NULL;                          //end of a first left half (list divided)

        ListNode* l1 = sortList(head);              //left half
        ListNode* l2 = sortList(slow);              //right half

        return mergeList(l1, l2);
    }
};
/*
Example 1:
Input: head = [4,2,1,3]
Output: [1,2,3,4]

Example 2:
Input: head = [-1,5,3,4,0]
Output: [-1,0,3,4,5]

Example 3:
Input: head = []
Output: []
*/


//108. GIVEN A LINKED LIST OF 0S, 1S AND 2S, SORT IT                  {T.C = O(N), S.C = O(1)}
//STORE COUNT OF 0 1 2 THEN ADD 0 1 2 WITH COUNT IN TEMP
class Solution
{
    public:
    Node* segregate(Node *head) {
        
        int zeroCount = 0;
        int oneCount = 0;
        int twoCount = 0;
        
        Node* temp = head;
        
        while(temp != NULL){
            if(temp->data == 0){
                zeroCount++;
            }
            else if(temp->data == 1){
                oneCount++;
            }
            else{
                twoCount++;
            }
            
            temp = temp->next;
        }
        
        temp = head;
        
        while(temp != NULL){
            if(zeroCount != 0){
                temp->data = 0;
                zeroCount--;
            }
            else if(oneCount != 0){
                temp->data = 1;
                oneCount--;
            }
            else{
                temp->data = 2;
                twoCount--;
            }
            
            temp = temp->next;
        }
        
        return head;
    }
};
/*
Example 1:
Input:
N = 8
value[] = {1,2,2,1,2,0,2,2}
Output: 0 1 1 2 2 2 2 2
Explanation: All the 0s are segregated
to the left end of the linked list,
2s to the right end of the list, and
1s in between.

Example 2:
Input:
N = 4
value[] = {2,2,0,1}
Output: 0 1 2 2
Explanation: After arranging all the
0s,1s and 2s in the given format,
the output will be 0 1 2 2.
*/


//109. INTERSECTION OF TWO LINKED LISTS                                {T.C = O(N), S.C = O(N)}
//STORE L1 NODE IN SET THEN MATCH WITH L2
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_set<ListNode*>st;
        ListNode* temp1 = headA;
        while(temp1){
            st.insert(temp1);
            temp1 = temp1->next;
        }
        ListNode* temp2 = headB;
        while(temp2){
            if(st.find(temp2) != st.end()){
                return temp2;
            }
            temp2 = temp2->next;
        }
        return NULL;
    }
};

//WITHOUT EXTRA SPACE                                                 {T.C = O(N), S.C = O(1)}
//MOVE BOTH POINTER IF 1 OF THEM NULL POINT IT TO ANOTHER HEAD.
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* temp1 = headA;
        ListNode* temp2 = headB;
        while(temp1 != temp2){
            temp1 = temp1->next;
            temp2 = temp2->next;
            if(temp1 == temp2){                  //intersection point
                return temp1;              
            }
            if(temp1 == NULL){
                temp1 = headB;
            }else if(temp2 == NULL){
                temp2 = headA;
            }
        }
        return temp1;                            //may be 1st point intersection or NULL
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


//110. ADD 1 TO A NUMBER REPRESENTED AS LINKED LIST                     {T.C = O(N), S.C = O(1)}
//FIRST REVERSE LIST THEN HANDLE (9), AGAIN REVERSE .
class Solution {
public:
    Node* reverse(Node* head) {
        Node* prev = NULL;
        Node* curr = head;
        Node* forward = NULL;

        while (curr != NULL) {
            forward = curr->next;
            curr->next = prev;
            prev = curr;
            curr = forward;
        }
        return prev;
    }

    Node* addOne(Node* head) {
        // Reverse the linked list
        head = reverse(head);
        Node* curr = head;
        bool carry = true; // Initialize carry

        while (curr && carry) {
            if (curr->next == NULL && curr->data == 9) {
                curr->data = 1;
                Node* temp = new Node(0);
                temp->next = head;
                head = temp;
                carry = false; // No more carry needed
            } 
            else if (curr->data == 9) {
                curr->data = 0;
                curr = curr->next;
            } 
            else {
                curr->data = curr->data + 1;
                carry = false; // No more carry needed
            }
        }

        // Reverse the linked list again to get the correct order
        head = reverse(head);
        return head;
    }
};
/*
Example 1:
Input:
LinkedList: 4->5->6
Output: 457
Explanation: 4->5->6 represents 456 and when 1 is added it becomes 457. 

Example 2:
Input:
LinkedList: 1->2->3
Output: 124 
*/


//111. ADD TWO NUMBERS                                               {T.C = O(N), S.C = O(1)}
//CREATE DUMMY NODE (NULL) AND POINTER TEMP(DUMMY), SUM += CARRY, CARRY = SUM/10, IF CARRY NEW NODE, TEMP->NEXT = NEWNODE
class Solution {
public:
    /* already reverse order have given in question
    ListNode* reverse(ListNode* head){
        ListNode* prev = NULL;
        ListNode* curr = head;
        ListNode* forward = NULL;

        while(curr){                                  //curr == curr != NULL
            forward = curr->next;
            curr->next = prev;
            prev = curr;
            curr = forward;
        }
        return prev;
    }
    */
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // l1 = reverse(l1);
        // l2 = reverse(l2);
        int carry = 0;
        ListNode *dummy = new ListNode(NULL);
        ListNode *temp = dummy;

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
            carry = sum/10;
            ListNode* extra = new ListNode(sum % 10);
            temp->next = extra;
            temp = temp->next;
        }
        // return reverse(dummy->next);
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


//112a. REMOVE LINKED LIST ELEMENTS                                 {T.C = O(N), S.C = O(1)}
//CREATE DUMMY NODE & POINT TO (TEMP), TEMP->NEXT = TEMP->NEXT->NEXT (IF VAL OCCUR)
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        //by creating dummy node
        ListNode* dummy = new ListNode();
        dummy->next = head;
        ListNode* temp = dummy;
        while(temp && temp->next){
            if(temp->next->val == val){
                temp->next = temp->next->next;
            }else{
                temp = temp->next;
            }
        }
        return dummy->next;
    }
};
/*
Example 1:
Input: head = [1,2,6,3,4,5,6], val = 6
Output: [1,2,3,4,5]

Example 2:
Input: head = [], val = 1
Output: []

Example 3:
Input: head = [7,7,7,7], val = 7
Output: []
*/


//112b. DELETE ALL OCCURENCES OF A GIVEN KEY IN A DOUBLY LINKED LIST   {T.C = O(N), S.C = O(1)}
//SIMILAR ABOVE (EXTRA PREV)
class Solution {
  public:
    void deleteAllOccurOfX(struct Node** head_ref, int x) {
        Node* dummy = new Node();
        dummy->next = *head_ref;
        Node* prev = dummy;                               //prev == temp
        Node* curr = *head_ref;
        while(curr){
            if(curr->data == x){
                prev->next = curr->next;
                if(curr->next){
                    curr->next->prev = prev;
                }
                curr = prev->next;
            }else{
                prev = curr;
                curr = curr->next;
            }
        }
        // return dummy->next;
        *head_ref = dummy->next;
    }
};
/*
Example1:
Input: 
2<->2<->10<->8<->4<->2<->5<->2
2
Output: 
10<->8<->4<->5
Explanation: 
All Occurences of 2 have been deleted.

Example2:
Input: 
9<->1<->3<->4<->5<->1<->8<->4
9
Output: 
1<->3<->4<->5<->1<->8<->4
Explanation: 
All Occurences of 9 have been deleted.
*/


//113. FIND PAIRS WITH GIVEN SUM IN DOUBLY LINKED LIST                     {T.C = O(N), S.C = O(1)}
//2 POINTERS (START & END) FIND PAIRS (VAL1 + VAL2)
class Solution {
public:
    vector<pair<int, int>> findPairsWithGivenSum(Node *head, int target) {
        vector<pair<int,int>>v;
        Node* s = head;
        Node* e = head;
        while(e->next){                       //reach to end of dll
            e = e->next;
        }
        while(s->data < e->data){
           int val1 = s->data,
           int val2 = e->data;
           
           if(val1+val2==target){
               v.push_back({s->data,e->data});
               s=s->next;
               e=e->prev;
           }
           else if(val1+val2<target){
               s=s->next;
           }
           else {
               e=e->prev;
           }
        }
        return v;
    }
};
/*
Example 1:
Input:  
1 <-> 2 <-> 4 <-> 5 <-> 6 <-> 8 <-> 9
target = 7
Output: (1, 6), (2,5)
Explanation: We can see that there are two pairs 
(1, 6) and (2,5) with sum 7.
 
Example 2:
Input: 
1 <-> 5 <-> 6
target = 6
Output: (1,5)
Explanation: We can see that there is one pairs  (1, 5) with sum 6.
*/


//114. REMOVE DUPLICATES FROM A SORTED DOUBLY LINKED LIST               {T.C = O(N), S.C = O(1)}
//CREATE NEXTNODE(TEMP->NEXT), REACH TO END OF DUPLICATE AND CONNECT TEMP-NEXTNODE, ITS PREV OT TEMP
class Solution
{
public:

    Node * removeDuplicates(struct Node *head){
        Node* temp = head;
        while(temp && temp->next){
            Node* nextNode = temp->next;
            while(nextNode && nextNode->data == temp->data){       //reach to end of duplicate
                nextNode = nextNode->next;
            }
            temp->next = nextNode;                               //connect temp - nextNode
            if(nextNode){                                        //connect next prev to temp
                nextNode->prev = temp;
            }
            temp = temp->next;
        }
        return head;
    }
};
/*
Example 1:
Input:
n = 6
1<->1<->1<->2<->3<->4
Output:
1<->2<->3<->4
Explanation:
Only the first occurance of node with value 1 is 
retained, rest nodes with value = 1 are deleted.

Example 2:
Input:
n = 7
1<->2<->2<->3<->3<->4<->4
Output:
1<->2<->3<->4
Explanation:
Only the first occurance of nodes with values 2,3 and 4 are 
retained, rest repeating nodes are deleted.
*/


//115. REVERSE NODES IN K-GROUP                                 {T.C = O(N), S.C = O(1)}
//REVERSE 1 K ELEMENTS WITH COUNT (SIMPLE REVERSE) THEN APPLY RECURSION
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        //if size is less then k then not reverse ll
        int sz = 0;
        ListNode* temp = head;

        while(temp){
            temp = temp->next;
            sz++;
        }
        //---------------------------------------------

        //base case
        if(!head || sz < k){
            return head;
        }

        ListNode* prev = NULL;
        ListNode* curr = head;
        ListNode* forward = NULL;
        int count = 0;
        //reverse 1 k elements
        while(curr && count < k){
            forward = curr->next;
            curr->next = prev;
            prev = curr;
            curr = forward;
            count++;
        }

        //after k elements lets recursion do its work
        if(forward){
            head->next = reverseKGroup(forward, k);         //point recursive ans to head->next
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


//116. ROTATE LIST                                              {T.C = O(N), S.C = O(1)}
//EFFECTIVE ROTATE (K = K % LEN) , K = LEN-K, CURR = CURR->NEXT(K--): UPDATE CURR
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head || k == 0){
            return head;
        }
        ListNode* curr = head;        
        int len = 1;                            // Initialize the length of the list.

        while(curr->next != NULL){
            curr = curr->next;
            len++;
        }
        curr->next = head;

        k = k % len;                           //effective rotation
        k = len - k;

        
        while (k--) {                         // Traverse the list to find the new head after rotation.
            curr = curr->next;
        }

        // Update the head and break the circular connection to complete the rotation.
        head = curr->next;
        curr->next = nullptr;

        return head;
    }
};
/*
Example 1:
Input: head = [1,2,3,4,5], k = 2
Output: [4,5,1,2,3]

Example 2:
Input: head = [0,1,2], k = 4
Output: [2,0,1]
*/


//117. FLATTENING A LINKED LIST                                        {T.C = O(N*N*M), S.C = O(N)}
//MAKE RECURSIVE CALL AND MERGE (MATCH BOTTOM AND TEMP)
Node* merge(Node* a, Node* b){
        //create node for store ans
        Node* ans = new Node(-1);
        Node* temp = ans;
        
        while(a != NULL && b != NULL){
            if(a->data < b->data){
                temp->bottom = a;
                temp = temp->bottom;
                a = a->bottom;
            }
            else{
                temp->bottom = b;
                temp = temp->bottom;
                b = b->bottom;
            }
        }
        if(a){
            temp->bottom = a;
        }else{
            temp->bottom = b;
        }
        
        ans = ans->bottom;
        return ans;
    }
Node *flatten(Node *root)
{
   //base case
   if(root == NULL || root->next == NULL){
       return root;
   }
   
   //recursive call
   root->next = flatten(root->next);
   
   //merge
   root = merge(root, root->next);
   
   return root;
}
/*
Example 1:
Input:
5 -> 10 -> 19 -> 28
|     |     |     | 
7     20    22   35
|           |     | 
8          50    40
|                 | 
30               45
Output:  5-> 7-> 8- > 10 -> 19-> 20->
22-> 28-> 30-> 35-> 40-> 45-> 50.
Explanation:
The resultant linked lists has every 
node in a single level.
(Note: | represents the bottom pointer.)
 
Example 2:
Input:
5 -> 10 -> 19 -> 28
|          |                
7          22   
|          |                 
8          50 
|                           
30              
Output: 5->7->8->10->19->22->28->30->50
Explanation:
The resultant linked lists has every
node in a single level.

(Note: | represents the bottom pointer.)
*/


//118. COPY LIST WITH RANDOM POINTER                                {T.C = O(N), S.C = O(N)}
//DEEP COPY
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(!head){
            return head;
        }
        Node* newHead = new Node(0);
        Node* newCurr = newHead;
        Node* curr = head;

        unordered_map<Node*, Node*>mp;
        //copying simple pointers or ll to new ll
        while(curr){
            Node* temp = new Node(curr->val);
            mp.insert({curr, temp});

            newCurr->next = temp;
            newCurr = newCurr->next;
            curr = curr->next;  
        }

        //reset
        curr = head;
        newCurr = newHead->next;

        //copying random pointers
        while(curr){
            Node* random = curr->random;
            Node* newNode = mp[random];
            newCurr->random = newNode;

            newCurr = newCurr->next;
            curr = curr->next;
        }

        return newHead->next;
    }
};
/*
Example 1:
Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]

Example 2:
Input: head = [[1,1],[2,1]]
Output: [[1,1],[2,1]]

Example 3:
Input: head = [[3,null],[3,0],[3,null]]
Output: [[3,null],[3,0],[3,null]]
*/


/*------------------------------------------------- THE END -----------------------------------------------------------*/