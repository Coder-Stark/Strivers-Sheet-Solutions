//LINKED LIST

#include<bits/stdc++.h>
using namespace std;


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


//DAY 7: LINKED LIST AND ARRAYS-----------------------------------------------------------------------------------------
//37. ROTATE LIST                                                         {T.C = O(N), S.C = O(1)}
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        //base case
        if(!head || k == 0) return head;
        
        ListNode* curr = head;
        int len = 1;
        while(curr->next){
            curr = curr->next;
            len++;
        }
        curr->next = head;                               //make circular connection(end to head)
        k = k % len;                                     //move circularly
        k = len-k;                                       //move right 2(5) == left 3(5-2)

        while(k--){
            curr = curr->next;
        }
        head = curr->next;                             //update head and break circular ll
        curr->next = NULL;

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


//38. COPY LIST WITH RANDOM POINTERS                                    {T.C = O(N), S.C = O(N)}
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(!head) return head;
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


//39. 3 SUM                                                               {T.C = O(N^2), S.C = O(N^2)}
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        set<vector<int>>st;                              //unique ans required
        for(int i = 0 ; i < n-2 ; i++){
            int start = i+1;
            int end = n-1;
            while(start < end){
                int sum = nums[i] + nums[start] + nums[end];
                if(sum == 0){
                    st.insert({nums[i], nums[start], nums[end]}); 
                    start++, end--;
                } 
                else if(sum < 0) start++;
                else end--;
            }
        }
        vector<vector<int>>ans;
        for(auto it : st){
            ans.push_back(it);
        }
        return ans;
    }
};
/*
Example 1:
Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation: 
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not matter.

Example 2:
Input: nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.

Example 3:
Input: nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0.
*/


//40. TRAPPING RAIN WATER                                                      {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        vector<int>prefixSum(n), suffixSum(n);                                //max left and right hights
        for(int i = 1 ; i < n ; i++){
            prefixSum[i] = max(prefixSum[i-1] , height[i-1]);
        }
        for(int i = n-2 ; i >= 0 ; i--){
            suffixSum[i] = max(suffixSum[i+1], height[i+1]);
        }
        int ans = 0;
        for(int i = 0 ; i < n ;i++){
            int waterLevel = min(prefixSum[i], suffixSum[i]);
            if(waterLevel >= height[i]){
                ans += waterLevel-height[i];
            }
        }
        return ans;
    }
};
/*
Example 1:
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.

Example 2:
Input: height = [4,2,0,3,2,5]
Output: 9
*/


//41. REMOVE DUPLICATES FROM THE SORTED ARRAY                                   {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int count = 1;                                     //unique element index
        int n = nums.size();
        if(n <= 1){
            return n;
        }
        for(int i = 1 ; i < nums.size() ; i++){
            if(nums[i] != nums[count-1]){                 //its unique
                nums[count] = nums[i];
                count++;
            }
        }
        return count;
    }
};
/*
Example 1:
Input: nums = [1,1,2]
Output: 2, nums = [1,2,_]
Explanation: Your function should return k = 2, with the first two elements of nums being 1 and 2 respectively.
It does not matter what you leave beyond the returned k (hence they are underscores).

Example 2:
Input: nums = [0,0,1,1,1,2,2,3,3,4]
Output: 5, nums = [0,1,2,3,4,_,_,_,_,_]
Explanation: Your function should return k = 5, with the first five elements of nums being 0, 1, 2, 3, and 4 respectively.
It does not matter what you leave beyond the returned k (hence they are underscores).
*/


//42. MAX CONSECUTIVE ONES                                                {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int maxi = 0;
        int count = 0, n = nums.size();
        for(int i = 0 ; i < n; i++){
            if(nums[i] == 1){
                count++;
                maxi = max(maxi, count);
            }else count = 0;
        }
        return maxi;
    }
};
/*
Example 1:
Input: nums = [1,1,0,1,1,1]
Output: 3
Explanation: The first two digits or the last three digits are consecutive 1s. The maximum number of consecutive 1s is 3.

Example 2:
Input: nums = [1,0,1,1,0,1]
Output: 2
*/


//DAY 8: GREEDY ALGORITHM-------------------------------------------------------------------------------------------------
//43. N MEETINGS IN ONE ROOM                                                  {T.C = O(N*LOGN), S.C = O(N)}
class Solution{
public:
    int maxMeetings(int start[], int end[], int n){
        vector<pair<int,int>>v;
        
        for(int i = 0 ; i < n ; i++){
            v.push_back({start[i], end[i]});
        }
        
        auto lambda = [&](auto a, auto b){     //increasing sort of end time
            return a.second < b.second;
        };
        sort(v.begin(), v.end(), lambda);
        
        int count = 1;
        int ansEnd = v[0].second;            //end time of last selected meeting
        for(int i = 1 ; i < n ; i++){
            if(v[i].first > ansEnd){
                count++;
                ansEnd = v[i].second;
            }
        }
        return count;
    }
};
/*
Input: n = 6, start[] = [1, 3, 0, 5, 8, 5], end[] =  [2, 4, 6, 7, 9, 9]
Output: 4
Explanation: Maximum four meetings can be held with given start and end timings. The meetings are - (1, 2), (3, 4), (5,7) and (8,9)

Input: n = 3, start[] = [10, 12, 20], end[] = [20, 25, 30]
Output: 1
Explanation: Only one meetings can be held with given start and end timings.
*/


//44. MINIMUM PLATFORMS (TWO POINTERS)                                     {T.C = O(N*LOGN), S.C = O(1)}
class Solution{
public:
    //USING 2 POINTERS
    int findPlatform(int arr[], int dep[], int n)
    {
        // Sort the arrival and departure times in ascending order
        sort(arr, arr + n);
        sort(dep, dep + n);
    
        int platforms = 1;               // At least one platform is required
        int maxPlatforms = 1;            // Keep track of the maximum number of platforms needed
    
        int arrivalIndex = 1;            //arr[0] = req 1 platfrom handled above
        int departureIndex = 0;
    
        while (arrivalIndex < n && departureIndex < n) {
            if (arr[arrivalIndex] <= dep[departureIndex]) {   //new train arrived and req platform
                platforms++;                                 // Increment the number of platforms needed
                maxPlatforms = max(maxPlatforms, platforms);
                arrivalIndex++;
            } else {
                platforms--;                                 // Reduce the number of platforms needed
                departureIndex++;
            }
        }
    
        return maxPlatforms;
    }
};
/*
Input: n = 6, arr[] = {0900, 0940, 0950, 1100, 1500, 1800}, 
            dep[] = {0910, 1200, 1120, 1130, 1900, 2000}
Output: 3
Explanation: There are three trains during the time 0940 to 1200. So we need minimum 3 platforms.

Input: n = 3, arr[] = {0900, 1235, 1100}, 
            dep[] = {1000, 1240, 1200}
Output: 1
Explanation: All train times are mutually exlusive. So we need only one platform

Input: n = 3, arr[] = {1000, 0935, 1100}, 
            dep[] = {1200, 1240, 1130}
Output: 3
Explanation: All 3 trains have to be their from 11:00 to 11:30
*/


//45. JOB SEQUENCING PROBLEM                                                {T.C = O(N*LOGN), S.C = O(N)}
class Solution {
public:
    vector<int> JobScheduling(Job arr[], int n) { 
        auto lambda = [&](auto a, auto b){   //decreasing sort of profit
            return a.profit > b.profit;
        };
        sort(arr, arr+n, lambda);
        int maxDeadline = INT_MIN;
        for(int i = 0 ; i < n ; i++){
            maxDeadline = max(maxDeadline, arr[i].dead);
        }
        vector<int>schedule(maxDeadline+1, -1);        //1 based indexing
        
        int jobCount = 0, maxProfit = 0;
        for(int i = 0 ; i < n; i++){
            int currId = arr[i].id;
            int currDead = arr[i].dead;
            int currProfit = arr[i].profit;
            
            for(int j = currDead ; j > 0 ; j--){  //put element reverse (between space may accumulate another)
                if(schedule[j] == -1){
                    jobCount++;
                    schedule[j] = currId;
                    maxProfit += currProfit;
                    break;
                }
            }
        }
        return {jobCount, maxProfit};
    } 
};
/*
Input: Jobs = [[1,4,20],[2,1,1],[3,1,40],[4,1,30]]
Output: 2 60
Explanation: Job1 and Job3 can be done with maximum profit of 60 (20+40).

Input: Jobs = [[1,2,100],[2,1,19],[3,2,27],[4,1,25],[5,1,15]]
Output: 2 127
Explanation: 2 jobs can be done with maximum profit of 127 (100+27).
*/


//46. FRACTIONAL KNAPSACK                                                {T.C = O(N*LOGN), S.C = O(N)}
class Solution
{
    public:
    double fractionalKnapsack(int W, Item arr[], int n)
    {
        //create vector {v/w, Item<v , w>}
        vector<pair<double, Item>>v;
        for(int i = 0 ; i < n ; i++){
            double perUnitValue = (1.0* arr[i].value / arr[i].weight);
            pair<double, Item>p = {perUnitValue, arr[i]};
            v.push_back(p);
        }
        
        //sort vector
        auto lambda = [&](auto a, auto b){     //decreasing sort of  per unit value
            return a.first > b.first;
        };
        sort(v.begin(), v.end(), lambda);
        
        double totalValue = 0;
        for(int i = 0 ; i < n ; i++){
            if(v[i].second.weight > W){
                //fractional part
                totalValue = totalValue + W * v[i].first;     // w * v/w
                W = 0;
            }
            else{
                //full part
                totalValue = totalValue + v[i].second.value;
                W = W - v[i].second.weight;
            }
        }
        return totalValue;
    }
};
/*
Input: n = 3, w = 50, value[] = [60,100,120], weight[] = [10,20,30]
Output: 240.000000
Explanation: Take the item with value 60 and weight 10, value 100 and weight 20 and split the third item with value 120 and weight 30, to fit it into weight 20. so it becomes (120/30)*20=80, so the total value becomes 60+100+80.0=240.0 Thus, total maximum value of item we can have is 240.00 from the given capacity of sack. 

Input: n = 2, w = 50, value[] = [60,100], weight[] = [10,20]
Output: 160.000000
Explanation: Take both the items completely, without breaking. Total maximum value of item we can have is 160.00 from the given capacity of sack.
*/


//47. COIN CHANGE                                                            {T.C = O(N*M), S.C = O(N*M)}
class Solution {
public:
    int dp[13][10001];
    int solveMem(vector<int>&coins, int sum, int i){
        int n = coins.size();
        //base case
        if(sum == 0) return 0;                     //NO TAKE ANY COIN(0)
        if(i >= n || sum < 0) return INT_MAX;
        
        if(dp[i][sum] != -1) return dp[i][sum];

        int incl = INT_MAX;
        if(sum >= coins[i]){
            int inclAns = solveMem(coins, sum-coins[i], i);     //use same coin(i)
            if(inclAns != INT_MAX) incl = inclAns+1;            //increase count of coin
        }
        int excl = 0 + solveMem(coins, sum, i+1);

        return dp[i][sum] = min(incl, excl);

    }
    int coinChange(vector<int>& coins, int amount) {
        memset(dp, -1, sizeof(dp));
        int ans = solveMem(coins, amount, 0);                  //0 = initial index
        return ans == INT_MAX ? -1 : ans;                 
    }
};
/*
Example 1:
Input: amount = 5, coins = [1,2,5]
Output: 4
Explanation: there are four ways to make up the amount:
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1

Example 2:
Input: amount = 3, coins = [2]
Output: 0
Explanation: the amount of 3 cannot be made up just with coins of 2.

Example 3:
Input: amount = 10, coins = [10]
Output: 1
*/


//48. ASSIGN COOKIES                                                         {T.C = O(N*LOGN), S.C = O(1)}
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        int n = g.size(), m = s.size();
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int i = 0, j = 0, count = 0;
        while(i < n && j < m){
            if(g[i] <= s[j]){                    //req <= have
                count++;
                i++;
            }
            j++;
        }
        return count;
    }
};
/*
Example 1:
Input: g = [1,2,3], s = [1,1]
Output: 1
Explanation: You have 3 children and 2 cookies. The greed factors of 3 children are 1, 2, 3. 
And even though you have 2 cookies, since their size is both 1, you could only make the child whose greed factor is 1 content.
You need to output 1.

Example 2:
Input: g = [1,2], s = [1,2,3]
Output: 2
Explanation: You have 2 children and 3 cookies. The greed factors of 2 children are 1, 2. 
You have 3 cookies and their sizes are big enough to gratify all of the children, 
You need to output 2.
*/


//DAY 9: RECURSION -----------------------------------------------------------------------------------------------------
//49. SUBSET SUM                                                              {T.C = O(2^N), S.C = O(N)}
class Solution {
  public:
    void solve(vector<int>&arr, vector<int>&ans, int sum, int i){
        int n = arr.size();
        if(i == n){
            ans.push_back(sum);
            return;
        }
        
        solve(arr, ans, sum+arr[i], i+1);         //incl
        solve(arr, ans, sum, i+1);                //excl
    }
    vector<int> subsetSums(vector<int> arr, int n) {
        vector<int>ans;
        solve(arr, ans,  0, 0);           //0 = initial index, 0 = sum
        return ans;
    }
};
/*
Example 1:
Input:
n = 2
arr[] = {2, 3}
Output:
0 2 3 5
Explanation:
When no elements is taken then Sum = 0.
When only 2 is taken then Sum = 2.
When only 3 is taken then Sum = 3.
When element 2 and 3 are taken then 
Sum = 2+3 = 5.

Example 2:
Input:
n = 3
arr = {5, 2, 1}
Output:
0 1 2 3 5 6 7 8
*/


//50. SUBSETS II                                                               {T.C = O(2^N), S.C = O(N*M)}
class Solution {
public:
    void solve(vector<int>&nums, vector<int>&temp, vector<vector<int>>&ans, int i){
        int n = nums.size();
        //base case
        if(i == n){
            ans.push_back(temp);
            return;
        }

        //incl & excl
        int element = nums[i];
        temp.push_back(element);
        solve(nums, temp, ans, i+1);                  //incl
        temp.pop_back();                              //backtrack

        //for skipping same element
        while(i + 1 < n && nums[i] == nums[i+1]){
            i++;
        }
        solve(nums, temp, ans, i+1);                  //excl
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<int>temp;
        vector<vector<int>>ans;
        sort(nums.begin(), nums.end());
        solve(nums, temp, ans, 0);                     //0 = index
        return ans;
    }
};
/*
Example 1:
Input: nums = [1,2,2]
Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]

Example 2:
Input: nums = [0]
Output: [[],[0]]
*/


//51. COMBINATION SUM                                                     {T.C = O(2^N), S.C = O(N)}
class Solution {
public:
    void solve(vector<int>&cand, int target, vector<vector<int>>&ans, vector<int>&temp, int i){
        int n = cand.size();
        //base case
        if(target == 0){
            ans.push_back(temp);
            return;
        }
        if(i >= n || target < 0) return;
        
        temp.push_back(cand[i]);
        solve(cand, target-cand[i], ans, temp, i);     //same element can be use
        temp.pop_back();
        solve(cand, target, ans, temp, i+1);
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>>ans;
        vector<int>temp;
        sort(candidates.begin(), candidates.end());
        solve(candidates, target, ans, temp, 0);
        return ans;
    }
};
/*
Example 1:
Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation:
2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
7 is a candidate, and 7 = 7.
These are the only two combinations.

Example 2:
Input: candidates = [2,3,5], target = 8
Output: [[2,2,2,2],[2,3,3],[3,5]]

Example 3:
Input: candidates = [2], target = 1
Output: []
*/


//52. COMBINATION SUM II (DISTINCT ELEMENT)                                {T.C = O(2^N*K), S.C = O(N)}
class Solution {
public:
    void solve(vector<int>&cand, int target, vector<vector<int>>&ans, vector<int>&temp, int idx){
        int n = cand.size();
        //base case
        if(target == 0){
            ans.push_back(temp);
            return;
        }
        if(idx >= n || target < 0) return;

        //incl & excl with not same element
        for(int i = idx ; i < n ; i++){
            if(i > idx && cand[i] == cand[i-1]) continue;       //skip same element

            temp.push_back(cand[i]);
            solve(cand, target-cand[i], ans, temp, i+1);
            temp.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>>ans;
        vector<int>temp;
        sort(candidates.begin(), candidates.end());             //for disqualify same element
        solve(candidates, target, ans, temp, 0);
        return ans;
    }
};
/*
Example 1:
Input: candidates = [10,1,2,7,6,1,5], target = 8
Output: 
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]

Example 2:
Input: candidates = [2,5,2,1,2], target = 5
Output: 
[
[1,2,2],
[5]
]
*/