#include<bits/stdc++.h>
using namespace std;

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
