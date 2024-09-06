#include<bits/stdc++.h>
using namespace std;


//DAY 4: ARRAY IV -----------------------------------------------------------------------------------------------------
//19. 2 SUM                                               {T.C = O(N), S.C = O(N)}
//MAP
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        /*
        int n = nums.size();
        unordered_map<int, int> mp;                          //{i, nums}
        for(int i = 0 ; i < n ; i++){
            mp[nums[i]] = i;
        }
        for(int i = 0 ; i < n ; i++){
            int complement = target-nums[i];
            if(mp.find(complement) != mp.end() && mp[complement] !=  i){
                return {i, mp[complement]};
            }
        }
        return {};
        */

        int n = nums.size();
        unordered_map<int, int>mp;                       //{i, nums}

        for(int i = 0; i < n ; i++){
            int compliment = target-nums[i];
            if(mp.count(compliment)){                     //or mp.find(compliment) != mp.end()
                return {mp[compliment], i};
            }
            mp[nums[i]] = i;
        }
        return {};
    }
};
/*
Example 1:
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].

Example 2:
Input: nums = [3,2,4], target = 6
Output: [1,2]

Example 3:
Input: nums = [3,3], target = 6
Output: [0,1]
*/


//20a. 3 SUM                                                       {T.C = O(N^2), S.C = O(N^2)}
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        set<vector<int>>st;                            //for unique answers only
        sort(nums.begin(), nums.end());
        for(int i = 0 ; i < n-2 ; i++){
            int start = i+1;
            int end = n-1;
            while(start < end){
                int sum = nums[i]+nums[start]+nums[end];
                if(sum == 0){
                    st.insert({nums[i], nums[start], nums[end]});
                    start++, end--;
                }else if(sum < 0){
                    start++;
                }else{
                    end--;
                }
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


//20. 4 SUM                                                        {T.C = O(N^3), S.C = O(N^2)}
//LOOP(4 SUM = 0 to n-3(4-1) then n-2)
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n = nums.size();
        set<vector<int>>st;                        //for unique quadruplets
        sort(nums.begin(), nums.end());
        for(int i = 0 ; i < n-3 ; i++){
            for(int j = i+1; j < n-2 ; j++){
                int start = j+1;
                int end = n-1;
                while(start < end){
                    long long sum = (long long)nums[i]+(long long)nums[j]+(long long)nums[start]+(long long)nums[end];
                    if(sum == target){
                        st.insert({nums[i], nums[j], nums[start], nums[end]});
                        start++, end--;
                    }else if(sum < target){
                        start++;
                    }else{
                        end--;
                    }
                }
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
Input: nums = [1,0,-1,0,-2,2], target = 0
Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]

Example 2:
Input: nums = [2,2,2,2,2], target = 8
Output: [[2,2,2,2]]
*/


//21. LONGEST CONSECUTIVE SEQUENCE                               {T.C = O(N), S.C = O(N)}
//SET
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n = nums.size();
        int maxLen = 0;
        unordered_set<int>st(nums.begin(), nums.end());
        for(int i = 0 ; i < n ; i++){
            if(st.find(nums[i]-1) == st.end()){
                int j = nums[i]+1;
                while(st.find(j) != st.end()){
                    j++;
                }
                maxLen = max(maxLen, j-nums[i]);
            }
        }
        return maxLen;
    }
};
/*
Example 1:
Input: nums = [100,4,200,1,3,2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.

Example 2:
Input: nums = [0,3,7,2,5,8,4,6,0,1]
Output: 9
*/


//22a. LONGEST SUB-ARRAY WITH SUM K (VARIABLE SLIDIING WINDOW)                {T.C = O(N), S.C = O(1)}
//ONLY FOR POSITIVE INTEGERS
class Solution{
    public:
    int lenOfLongSubarr(int a[],  int n, int k) 
    { 
        int i = 0, j = 0;
        int sum = 0;
        int maxLen = 0;
        while(j < n){
            sum += a[j];
            if(sum == k){
                maxLen = max(maxLen, (j-i+1));
            }
            if(sum > k){
                while(sum > k){
                    sum -= a[i];
                    i++;
                }
            }
            j++;
        }
        return maxLen;
    } 
};

//22b. LONGEST SUB-ARRAY WITH SUM K (VARIABLE SLIDIING WINDOW)                {T.C = O(N), S.C = O(1)}
//FOR NEGATIVE NUMBERS
//BRUTE FORCE                                                                 {T.C = O(N^2), S.C = O(1)}
class Solution{
    public:
    int lenOfLongSubarr(int a[],  int n, int k) 
    { 
        int maxi = 0;
        for(int i = 0 ; i < n ; i++){
            int sum = 0;                               //sum is there not in top (reset sum)
            for(int j = i ; j < n ; j++){
                sum += a[j];
                if(sum == k){
                    maxi = max(maxi, j-i+1);
                }
            }
        }
        return maxi;
    } 
};

//OPTIMIZED APPROACH (USING MAP)                                               {T.C = O(N), S.C = O(N)}
class Solution{ 
    public:
    int lenOfLongSubarr(int a[],  int n, int k) 
    { 
        int maxLen = 0;
        int sum = 0;
        unordered_map<int, int>mp;
        for(int i = 0 ; i < n ; i++){
            sum += a[i];
            if(sum == k){
                maxLen = max(maxLen, i+1);              //for 0 based indexing             //length of subarray
            }
            if(mp.find(sum-k) != mp.end()){
                maxLen = max(maxLen, i-mp[sum-k]);
            }
            if(mp.find(sum) == mp.end()){               //prev not found sum
                mp[sum] = i;
            }
        }
        return maxLen;
    } 
};
/*
Input :
A[] = {10, 5, 2, 7, 1, 9}
K = 15
Output : 4
Explanation:
The sub-array is {5, 2, 7, 1}.
*/


//23. SUBARRAY WITH GIVEN XOR                                    {T.C = O(N), S.C = O(N)}
//PREFIX XOR
int solve(vector<int> &A, int B) {
    int n = A.size();
    unordered_map<int, int>mp;
    mp[0] = 1;                                 //initialize map (0 , 1)
    int count = 0;
    int Xor = 0;
    for(int i = 0 ; i < n ; i++){
        Xor = Xor ^ A[i];
        int x = Xor ^ B;                       //find previous found
        count += mp[x];                        //if found increase count
        mp[Xor]++;
    }
    return count;
}
/*
Input 1:
 A = [4, 2, 2, 6, 4]
 B = 6

Input 2:
 A = [5, 6, 7, 8, 9]
 B = 5
*/


//24. LONGEST SUBSTRING WITHOUT REPEATING CHARACTERS                  {T.C = O(N), S.C = O(N)}
//MAP (VARIABLE SIZE SLIDIING WINDOW)
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.length();
        unordered_map<char, int>mp;
        int i = 0, j = 0, maxLen = 0;
        while(j < n){
            mp[s[j]]++;
            if(mp.size() == j-i+1){
                maxLen = max(maxLen, j-i+1);
            }
            if(mp.size() < j-i+1){                //remember its less then condition others have greater
                while(mp.size() < j-i+1){
                    mp[s[i]]--;
                    if(mp[s[i]] == 0){
                        mp.erase(s[i]);
                    }
                    i++;
                }
            }
            j++;
        }
        return maxLen;
    }
};
/*
Example 1:
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Example 2:
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
*/