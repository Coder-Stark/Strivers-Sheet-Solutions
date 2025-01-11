//75 BLIND SHEET
#include<bits/stdc++.h>
using namespace std;


//01. 2 SUM                                                        {T.C = O(N), S.C = O(N)}
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        unordered_map<int,int>mp;                      //element, index (not freq)
        for(int i = 0 ; i < n ; i++){
            int compliment = target - nums[i];
            if(mp.count(compliment)){
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


//02. BEST TIME TO BUY AND SELL STOCK I                            {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int mini = prices[0];
        int maxi = INT_MIN;
        for(int i = 0 ; i < n; i++){
            mini = min(mini, prices[i]);
            maxi = max(maxi, prices[i]-mini);
        }
        return maxi;
    }
};
/*
Example 1:
Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.

Example 2:
Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transactions are done and the max profit = 0.
*/


//03. CONTAINS DUPLICATES                                         {T.C = O(N), S.C = O(N)}
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_map<int,int>mp;
        for(auto it : nums) mp[it]++;

        if(mp.size() < nums.size()) return true;

        return false;
    }
};
/*
Example 1:
Input: nums = [1,2,3,1]
Output: true
Explanation:
The element 1 occurs at the indices 0 and 3.

Example 2:
Input: nums = [1,2,3,4]
Output: false
Explanation:
All elements are distinct.
*/


//04. PRODUCT OF ARRAY EXCEPT SELF                                             {T.C = O(N), S.C = O(N)}
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int>prefixMul(n, 1);
        for(int i = 1; i < n; i++){
            prefixMul[i] = prefixMul[i-1]*nums[i-1];        //exclude nums[i]
        }

        vector<int>suffixMul(n, 1);
        for(int i = n-2 ; i >= 0 ; i--){
            suffixMul[i] = suffixMul[i+1]*nums[i+1];       //exclude nums[i]
        }

        vector<int>ans(n);
        for(int i = 0 ; i < n; i++){
            ans[i] = prefixMul[i]*suffixMul[i];
        }
        return ans;
    }
};
/*
Example 1:
Input: nums = [1,2,3,4]
Output: [24,12,8,6]

Example 2:
Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]
*/


//05. MAXIMUM SUM SUBARRAY (KADANE'S ALGO)                                          {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        int sum = 0, maxSum = INT_MIN;
        for(int i = 0 ; i < n ;i++){
            sum += nums[i];
            maxSum = max(maxSum, sum);
            if(sum < 0) sum = 0;                 //reset sum
        }
        return maxSum;
    }
};
/*
Example 1:
Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: The subarray [4,-1,2,1] has the largest sum 6.

Example 2:
Input: nums = [1]
Output: 1
Explanation: The subarray [1] has the largest sum 1.

Example 3:
Input: nums = [5,4,-1,7,8]
Output: 23
Explanation: The subarray [5,4,-1,7,8] has the largest sum 23.
*/


//06. MAXIMUM PRODUCT SUBARRAY (KADANE'S ALGO)                                          {T.C = O(N), S.C = O(1)}
//USING KADANE'S ALGO(LEFT TO RIGTH, RIGTH TO LEFT BOTH)
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int prod = 1;
        int maxProd = INT_MIN;
        for(int i = 0 ; i < n ; i++){             //left to right
            prod *= nums[i];
            maxProd = max(maxProd, prod);
            if(prod == 0) prod = 1;
        }
        prod = 1;                                 //reset
        for(int i = n-1 ; i >= 0 ; i--){
            prod *= nums[i];
            maxProd = max(maxProd, prod);
            if(prod == 0) prod = 1;
        }

        return maxProd;
    }
};
/*
Example 1:
Input: nums = [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.

Example 2:
Input: nums = [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
*/


//07. FIND MINIMUM IN ROTATED SORTED ARRAY                         {T.C = O(LOGN), S.C = O(1)}
class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size();
        //base case
        if(nums[0] < nums[n-1]) return nums[0];
        int mini = INT_MAX;
        int start = 0, end = n-1;
        while(start <= end){
            int mid = (start+end)/2;
            if(nums[start] <= nums[mid]){               //ans lie on left half
                mini = min(mini, nums[start]);
                start = mid+1;
            }else{                                      //ans lie on right half
                mini = min(mini, nums[mid]);
                end = mid-1;
            }
        }
        return mini;
    }
};
/*
Example 1:
Input: nums = [3,4,5,1,2]
Output: 1
Explanation: The original array was [1,2,3,4,5] rotated 3 times.

Example 2:
Input: nums = [4,5,6,7,0,1,2]
Output: 0
Explanation: The original array was [0,1,2,4,5,6,7] and it was rotated 4 times.

Example 3:
Input: nums = [11,13,15,17]
Output: 11
Explanation: The original array was [11,13,15,17] and it was rotated 4 times. 
*/


//08. SEARCH IN ROTATED SORTED ARRAY                              {T.C = O(LOGN), S.C = O(1)}
//BINARY SEARCH ON INDEX
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int start = 0, end = n-1;
        while(start <= end){
            int midIdx = (start + end)/2;
            if(nums[midIdx] == target) return midIdx;
            else if(nums[start] <= nums[midIdx]){                  //left part is sorted
                if(nums[start] <= target && target <= nums[midIdx]) end = midIdx-1;  //ans in left 
                else start = midIdx+1;
            }else{ //nums[start] > nums[midIdx]                   //right part is sorted
                if(nums[midIdx] <= target && target <= nums[end]) start = midIdx+1;  //ans in right
                else end = midIdx-1;
            }
        }
        return -1;
    }
};
/*
Example 1:
Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4

Example 2:
Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1

Example 3:
Input: nums = [1], target = 0
Output: -1
*/


//09. 3 SUM                                                         {T.C = O(N^2), S.C = O(N)}
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


//10. CONTAINER WITH MOST WATER                                               {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int maxA = 0;
        int i = 0, j = n-1;
        while(i <= j){
            int h = min(height[i], height[j]);         //min height(hold water else flow)
            int w = j-i;
            int a = h*w;
            maxA  = max(maxA, a);
            if(height[i] <= height[j]) i++;
            else j--;
        }
        return maxA;
    }
};
/*
Example 1:
Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.

Example 2:
Input: height = [1,1]
Output: 1
*/


//11. SUM OF 2 INTEGERS                                            {T.C = O(1), S.C = O(1)}
class Solution {
public:
    int getSum(int a, int b) {
        while (b != 0) {
            int Xor = a ^ b;                // sum of bits where at least one is 1
            int carry = (a & b) << 1;       // carry where both bits are 1
            a = Xor;                        // update a to be the new sum
            b = carry;                      // update b to be the new carry
        }
        return a;                           // return sum when carry is 0
    }
};
/*
Example 1:
Input: a = 1, b = 2
Output: 3

Example 2:
Input: a = 2, b = 3
Output: 5
*/


//12. NUMBER OF 1 BITS / HAMMING WEIGHT                       
//USING STL                                                        {T.C = O(LOGN), S.C = O(1)}
class Solution {
public:
    int hammingWeight(int n) {
        return __builtin_popcount(n);
    }
};

//WITHOUT STL                                                     {T.C = O(LOGN), S.C = O(1)}
class Solution {
public:
    int hammingWeight(int n) {
        int countSetBits = 0;
        while(n){
            countSetBits += n % 2;
            n /= 2;
        }
        return countSetBits;
    }
};
/*
Example 1:
Input: n = 11
Output: 3
Explanation:
The input binary string 1011 has a total of three set bits.

Example 2:
Input: n = 128
Output: 1
Explanation:
The input binary string 10000000 has a total of one set bit.

Example 3:
Input: n = 2147483645
Output: 30
Explanation:
The input binary string 1111111111111111111111111111101 has a total of thirty set bits.
*/


//13. COUNTING BITS
//BRUTE FORCE                                                      {T.C = O(N*LOGN), S.C = O(N)}
class Solution {
public:
    int countSetBits(int n){
        int count = 0;
        while(n){
            count += n % 2;
            n /= 2;
        }
        return count;
    }
    vector<int> countBits(int n) {
        vector<int>ans(n+1);
        for(int i = 0; i <= n; i++){
            ans[i] = countSetBits(i);
        }
        return ans;
    }
};

//OPTIMAL APPROACH                                                  {T.C = O(N), S.C = O(N)}
//COUNT OF BITS OF NUM IS SAME AS ITS HALF(IF ODD THEN +1)
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int>ans(n+1);
        ans[0] = 0;                             
        for(int i = 1 ; i <= n ;i++){
            if(i % 2 == 0) ans[i] = ans[i/2];
            else ans[i] = ans[i/2]+1;
        }   
        return ans;
    }
};
/*
Example 1:
Input: n = 2
Output: [0,1,1]
Explanation:
0 --> 0
1 --> 1
2 --> 10

Example 2:
Input: n = 5
Output: [0,1,1,2,1,2]
Explanation:
0 --> 0
1 --> 1
2 --> 10
3 --> 11
4 --> 100
5 --> 101
*/


//14. MISSING NUMBER 
//USING MATHS FORMULA                                             {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int sum = (n*(n+1))/2;                        //0 to n numbers

        for(int i = 0 ; i < n;  i++){
            sum -= nums[i];
        }
        return sum;
    }
};
/*
Example 1:
Input: nums = [3,0,1]
Output: 2
Explanation: n = 3 since there are 3 numbers, so all numbers are in the range [0,3]. 2 is the missing number in the 
range since it does not appear in nums.

Example 2:
Input: nums = [0,1]
Output: 2
Explanation: n = 2 since there are 2 numbers, so all numbers are in the range [0,2]. 2 is the missing number in the 
range since it does not appear in nums.

Example 3:
Input: nums = [9,6,4,2,3,5,7,0,1]
Output: 8
Explanation: n = 9 since there are 9 numbers, so all numbers are in the range [0,9]. 8 is the missing number in the 
range since it does not appear in nums.
*/


//15. REVERSE BITS                                                  {T.C = O(1), S.C = O(1)}
class Solution {
public:
    bool findKthBitSet(int k, uint32_t n){
        if( ((1 << (k-1)) & n) != 0 ){      //first reach to set bit( which is 1 by shifting k-1) then take & with n
            return true;
        }
        return false;                       //(1.0 = 0)
    }
    uint32_t reverseBits(uint32_t n) {
        uint32_t ans = 0;
        for(int i = 1; i <= 32 ; i++){      //from 1 otherwise overflow
            if(findKthBitSet(i, n)){        //find kth bit is set(1) or not set(0)
                ans = 1 << (32-i) | ans;    //second last to second position or vice versa  by shifting element and take OR (ans keep building)
            }
        }
        return ans;
    }
};
/*
Example 1:
Input: n = 00000010100101000001111010011100
Output:    964176192 (00111001011110000010100101000000)
Explanation: The input binary string 00000010100101000001111010011100 represents the unsigned integer 43261596, so return 964176192 which its binary representation is 00111001011110000010100101000000.

Example 2:
Input: n = 11111111111111111111111111111101
Output:   3221225471 (10111111111111111111111111111111)
Explanation: The input binary string 11111111111111111111111111111101 represents the unsigned integer 4294967293, so return 3221225471 which its binary representation is 10111111111111111111111111111111.
*/


//16. CLIMBING STAIRS                                              {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int dp[50];
    int solveMem(int n){
        //base case
        if(n <= 1) return 1;                    //at 0 level 1 step count

        if(dp[n] != -1) return dp[n];

        int way1 = solveMem(n-1);
        int way2 = solveMem(n-2);

        return dp[n] = way1 + way2;
    }
    int climbStairs(int n) {
        memset(dp, -1, sizeof(dp));
        return solveMem(n);
    }
};
/*
Example 1:
Input: n = 2
Output: 2
Explanation: There are two ways to climb to the top.
1. 1 step + 1 step
2. 2 steps

Example 2:
Input: n = 3
Output: 3
Explanation: There are three ways to climb to the top.
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step
*/


//17. COIN CHANGE                                                      {T.C = O(N*TARGET), S.C = O(N*TARGET)}            
class Solution {
public:
    int dp[15][10005];
    int solveMem(vector<int>&coins, int target, int i){
        int n = coins.size();
        //base case
        if(target == 0) return 0;
        if(i >= n || target < 0) return INT_MAX;            //not possible

        if(dp[i][target] != -1) return dp[i][target];

        int inclCoin = INT_MAX;                                            //mincoin required initially INT_MAX(not 0 , 0 means no need of coins all set)
        if(target >= coins[i]){
            int val = solveMem(coins, target-coins[i], i); //same coin can take any times
            if(val != INT_MAX) inclCoin = 1 + val;
        }
        int exclCoin = 0 + solveMem(coins, target, i+1); 

        return dp[i][target] = min(inclCoin, exclCoin);
    }
    int coinChange(vector<int>& coins, int amount) {
        memset(dp, -1, sizeof(dp));
        int ans = solveMem(coins, amount, 0);         //0 = initial index
        if(ans == INT_MAX) return -1;
        return ans;
    }
};
/*
Example 1:
Input: coins = [1,2,5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1

Example 2:
Input: coins = [2], amount = 3
Output: -1

Example 3:
Input: coins = [1], amount = 0
Output: 0
*/


//18. LONGEST INCREASING SUBSEQUENCE                               {T.C = O(N^2), S.C = O(N^2)}
class Solution {
public:
    int dp[2501][2501];
    int solveMem(vector<int>&nums , int i, int prev){
        int n = nums.size();
        //base case
        if(i >= n) return 0;

        if(dp[i][prev+1] != -1) return dp[i][prev+1];       //+1 for handle out of bound

        int incl = INT_MIN;                                 //max len
        if(prev == -1 || nums[i] > nums[prev]){             //1st ele or next greater then prev
            incl  = 1 + solveMem(nums, i+1, i);             //prev becomes currIdx(i)
        }
        int excl = 0 + solveMem(nums, i+1, prev);

        return dp[i][prev+1] = max(incl, excl);
    }
    int lengthOfLIS(vector<int>& nums) {
        memset(dp, -1, sizeof(dp));
        return solveMem(nums, 0, -1);           //0 = initial index, -1 = prevIdx
    }
};
/*
Example 1:
Input: nums = [10,9,2,5,3,7,101,18]
Output: 4
Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.

Example 2:
Input: nums = [0,1,0,3,2,3]
Output: 4

Example 3:
Input: nums = [7,7,7,7,7,7,7]
Output: 1
*/


//19. LONGEST COMMON SUBSEQUENCE                       
//USING TABULATION                                                 {T.C = O(N^2), S.C = O(N^2)}
class Solution {
public:
    int dp[1005][1005];
    int solveTab(string &s1, string &s2, int n, int m){
        for(int i = 1 ; i < n+1; i++){
            for(int j = 1 ;j < m+1 ; j++){
                if(s1[i-1] == s2[j-1]) dp[i][j] = 1 + dp[i-1][j-1];
                else dp[i][j] = 0 + max(dp[i-1][j], dp[i][j-1]);
            }
        }
        return dp[n][m];
    }
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.size(), m = text2.size();
        return solveTab(text1, text2, n, m);
    }
};

//USING MEMOZATION                                                {T.C = O(N^2), S.C = O(N^2)}
class Solution {
public:
    int dp[1005][1005];
    int solveMem(string &a, string &b, int i, int j){
        int n = a.length(), m = b.length();
        //base case
        if(i >= n || j >= m) return 0;

        if(dp[i][j] != -1) return dp[i][j];

        int count = 0;
        if(a[i] == b[j]){
            count = 1 + solveMem(a, b, i+1, j+1);
        }else{  //a[i] != b[i]
            count = 0 + max(solveMem(a, b, i+1, j), solveMem(a, b, i, j+1));  //incl, excl
        }
        return dp[i][j] = count;
    }
    int longestCommonSubsequence(string text1, string text2) {
        memset(dp, -1, sizeof(dp));
        return solveMem(text1, text2, 0, 0);             //0 , 0 = initial index of both text
    }
};
/*
Example 1:
Input: text1 = "abcde", text2 = "ace" 
Output: 3  
Explanation: The longest common subsequence is "ace" and its length is 3.

Example 2:
Input: text1 = "abc", text2 = "abc"
Output: 3
Explanation: The longest common subsequence is "abc" and its length is 3.

Example 3:
Input: text1 = "abc", text2 = "def"
Output: 0
Explanation: There is no such common subsequence, so the result is 0.
*/


//20. WORD BREAK                                                  {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int dp[305];
    bool solveMem(string &s, unordered_set<string>&st, int i){
        int n = s.length();
        //base case
        if(i >= n) return true;                            //all find

        if(dp[i] != -1) return dp[i];

        string temp = "";
        for(int j = i ; j < n ; j++){                        //i not 0 (next word from currIdx)
            temp += s[j];
            if(st.count(temp)){
                if(solveMem(s, st, j+1)) return dp[i] = true;          //check of next word in dict
            }
        }
        return dp[i] = false;
    }
    bool wordBreak(string s, vector<string>& wordDict) {
        memset(dp, -1, sizeof(dp));
        unordered_set<string>st(wordDict.begin(), wordDict.end());
        return solveMem(s, st, 0);                       //0 = initial index
    }
};
/*
Example 1:
Input: s = "leetcode", wordDict = ["leet","code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".

Example 2:
Input: s = "applepenapple", wordDict = ["apple","pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
Note that you are allowed to reuse a dictionary word.

Example 3:
Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: false
*/


//21. COMBINATION SUM                                             {T.C = O(EXP / N^TARGET), S.C = O(N)}
class Solution {
public:
    void solve(vector<int>&cand, int target, vector<vector<int>>&ans, vector<int>&temp, int i){
        int n = cand.size();
        //base case
        if(target == 0){
            ans.push_back(temp);
            return;                                     //for next push
        }
        if(i >= n || target < 0) return;

        temp.push_back(cand[i]);
        solve(cand, target-cand[i], ans, temp, i);       //incl       // same element can use many times
        temp.pop_back();
        solve(cand, target, ans, temp, i+1);            //excl
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>>ans;
        vector<int>temp;
        sort(candidates.begin(), candidates.end());
        solve(candidates, target, ans, temp, 0);            //0 = initial index
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


//22. HOUSE ROBBER I                                               {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int dp[105];
    int solveMem(vector<int>&nums , int i){
        int n = nums.size();
        //base case
        if(i >= n) return 0;

        if(dp[i] != -1 ) return dp[i];
        int incl = nums[i] + solveMem(nums, i+2);       //adjacent skip
        int excl = 0 + solveMem(nums, i+1);

        return dp[i] = max(incl, excl);
    }
    int rob(vector<int>& nums) {
        memset(dp, -1, sizeof(dp));
        return solveMem(nums, 0);             //0 = initial index
    }
};
/*
Example 1:
Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
Total amount you can rob = 1 + 3 = 4.

Example 2:
Input: nums = [2,7,9,3,1]
Output: 12
Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
Total amount you can rob = 2 + 9 + 1 = 12.
*/


//23. HOUSE ROBBER II                                              {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int dp1[105], dp2[105];
    int solveMem(vector<int>&nums, int i, int n, int *dp){      //for work both dp by refernce *
        //base case
        if(i >= n) return 0;

        if(dp[i] != -1) return dp[i];

        int incl = nums[i] + solveMem(nums, i+2, n, dp);
        int excl = 0 + solveMem(nums, i+1, n, dp);

        return dp[i] = max(incl, excl);
    }
    int rob(vector<int>& nums) {
        memset(dp1, -1, sizeof(dp1));
        memset(dp2, -1, sizeof(dp2));
        int n = nums.size();

        if(n == 1) return nums[0];
        if(n == 2) return max(nums[0], nums[1]);

        int inclZeroIdx = solveMem(nums, 0, n-1, dp1);             //here n = size, for idx = n-2
        int exclZeroIdx = solveMem(nums, 1, n, dp2);

        return max(inclZeroIdx, exclZeroIdx);
    }
};
/*
Example 1:
Input: nums = [2,3,2]
Output: 3
Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2), because they are adjacent houses.

Example 2:
Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
Total amount you can rob = 1 + 3 = 4.

Example 3:
Input: nums = [1,2,3]
Output: 3
*/


//24. DECODE WAYS                                                  {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int dp[105];
    int solveMem(string &s, int i){
        int n = s.length();
        //base case
        if(i == n) return 1;                         //only 1 way to decode

        if(dp[i] != -1) return dp[i];

        int oneCharDecode = 0;                       //1 char decode (a to i)
        int twoCharDecode = 0;                       //2 char decode (11(j) to 26(z))
        if(s[i] != '0'){
            oneCharDecode = solveMem(s, i+1);
        }
        if(i+1 < n && (s[i] == '1' || (s[i] == '2' && s[i+1] <= '6'))){
            twoCharDecode = solveMem(s, i+2);        //skip two places
        }

        return dp[i] = oneCharDecode + twoCharDecode;
    }
    int numDecodings(string s) {
        memset(dp, -1, sizeof(dp));
        int n = s.length();
        //base case 
        if(s[0] == '0') return 0;                   //can't decode 05, 07...

        return solveMem(s, 0);                      //0 = initial index
    }
};
/*
Example 1:
Input: s = "12"
Output: 2
Explanation:
"12" could be decoded as "AB" (1 2) or "L" (12).

Example 2:
Input: s = "226"
Output: 3
Explanation:
"226" could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).
*/


//25. UNIQUE PATHS                                                  {T.C = O(N^2), S.C = O(N^2)}
class Solution {
public:
    int dp[105][105];
    int solveMem(int n, int m, int i, int j){
        //base case
        if(i >= n || j >= m) return 0;
        if(i == n-1 && j == m-1) return 1;          //start == destination (1 way)

        if(dp[i][j] != -1) return dp[i][j];

        int down = solveMem(n, m, i+1, j);
        int right= solveMem(n, m, i, j+1);

        return dp[i][j] = down + right;
    }
    int uniquePaths(int m, int n) {
        memset(dp, -1, sizeof(dp));
        return solveMem(n, m, 0, 0);
    }
};
/*
Example 1:
Input: m = 3, n = 7
Output: 28

Example 2:
Input: m = 3, n = 2
Output: 3
Explanation: From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
1. Right -> Down -> Down
2. Down -> Down -> Right
3. Down -> Right -> Down
*/


//26. JUMP GAME                                                   {T.C = O(N^2), S.C = O(N)}
class Solution {
public:
    int dp[10005];
    bool solveMem(vector<int>&nums, int i){
        int n = nums.size();
        //base case
        if(i == n-1) return true;
        if(i >= n) return false;

        if(dp[i] != -1) return dp[i];

        for(int j = 1 ; j <= nums[i] ; j++){              //1 = min jump, val = maxjump
            if(solveMem(nums, j+i) == true) return dp[i] = true;
        }
        return dp[i] = false;
    }
    bool canJump(vector<int>& nums) {
        memset(dp, -1, sizeof(dp));
        return solveMem(nums, 0);                //0 = initial index
    }
};
/*
Example 1:
Input: nums = [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.

Example 2:
Input: nums = [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.
*/


//26b. JUMP GAME II                                              {T.C = O(N^2), S.C = O(N)}
class Solution {
public:
    int dp[10005];
    int solveMem(vector<int>&nums, int i){
        int n = nums.size();
        //base case
        if(i >= n-1) return 0;                   //reach end or more

        if(dp[i] != -1) return dp[i];

        int minJump = 1e5;                        //INT_MAX not working
        for(int j = 1 ; j <= nums[i] ; j++){
            int jumps = 1 + solveMem(nums, j+i);
            minJump = min(minJump, jumps);
        }
        return dp[i] = minJump;
    }
    int jump(vector<int>& nums) {
        memset(dp, -1, sizeof(dp));
        return solveMem(nums, 0);                //0 = initial index
    }
};
/*
Example 1:
Input: nums = [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.

Example 2:
Input: nums = [2,3,0,1,4]
Output: 2
*/


//27. CLONE GRAPH                                              {T.C = O(V+E), S.C = O(V)}         
class Solution {
public:
    void dfs(Node* root, vector<Node*>&vis, Node*node){
        vis[node->val] = node;
        for(auto it : root->neighbors){
            if(!vis[it->val]){
                Node* newNode = new Node(it->val);
                node->neighbors.push_back(newNode);
                dfs(it, vis, newNode);
            }else{
                node->neighbors.push_back(vis[it->val]);
            }
        }
    }
    Node* cloneGraph(Node* root) {
        //base case
        if(!root) return NULL;
        Node* node = new Node(root->val);
        vector<Node*>vis(100, NULL);                         //n  = 100(max nodes constraints)
        dfs(root, vis, node);

        return node;
    }
};
/*
Example 1:
Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
Output: [[2,4],[1,3],[2,4],[1,3]]
Explanation: There are 4 nodes in the graph.
1st node (val = 1)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
2nd node (val = 2)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
3rd node (val = 3)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
4th node (val = 4)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).

Example 2:
Input: adjList = [[]]
Output: [[]]
Explanation: Note that the input contains one empty list. The graph consists of only one node with val = 1 and it does not have any neighbors.

Example 3:
Input: adjList = []
Output: []
Explanation: This an empty graph, it does not have any nodes.
*/


//28. COURSE SCHEDULE                                             {T.C = O(V+E), S.C = O(V+E)}
class Solution {
public:
    vector<int>topoSort(vector<vector<int>>&edges, int n){
        unordered_map<int,vector<int>>adj;
        for(auto it : edges) adj[it[1]].push_back(it[0]);     //a <- b (b first)
        
        vector<int>inDegree(n, 0);
        for(auto it : edges){
            inDegree[it[0]]++;                                  //a <- b
        }

        queue<int>q;
        for(int i = 0 ; i < n ;i++){
            if(inDegree[i] == 0) q.push(i);                    //push index not ele
        }

        vector<int>ans;
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            ans.push_back(frontNode);
            for(auto it : adj[frontNode]){
                inDegree[it]--;
                if(inDegree[it] == 0) q.push(it);
            }
        }
        return ans;
    }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int>topo = topoSort(prerequisites, numCourses);
        return topo.size() == numCourses;                   //all traverse, valid toposort
    }
};
/*
Example 1:
Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0. So it is possible.

Example 2:
Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.
*/


//29. PACIFIC ATLANTIC WATER FLOW                                 {T.C = O(N*M), S.C = O(N*M)}
class Solution {
public:
    vector<vector<int>>directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    bool isValid(int i, int j, int n, int m){
        return (i >= 0 && i < n && j >= 0 && j < m);
    }
    void dfs(vector<vector<int>>&grid, vector<vector<bool>>& vis, int i, int j) {
        int n = grid.size(), m = grid[0].size();
        vis[i][j] = true;
        for(auto it : directions){
            int newR = i + it[0];
            int newC = j + it[1];
 
            if(isValid(newR, newC, n, m) && !vis[newR][newC] && grid[newR][newC] >= grid[i][j]){   //new cell should high for water flow from outside to inside
                dfs(grid, vis, newR, newC);
            }
        }
    }
    /// main logic or trick for this problem : bahar se andar ki taraf jao
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        vector<vector<int>>ans;
        int n = heights.size(), m = heights[0].size();
        
        vector<vector<bool>> pacific(n, vector<bool>(m));
        vector<vector<bool>> atlantic(n, vector<bool>(m));
        
        for (int i = 0; i < n; i++) {
            dfs(heights, pacific, i, 0);               //pacific 1st col
            dfs(heights, atlantic, i, m-1);            //atlantic last col
        }
        
        for (int j = 0; j < m; j++) {
            dfs(heights, pacific, 0, j);              //pacific 1st row
            dfs(heights, atlantic, n-1, j);           //atlantic last col
        }

        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (pacific[i][j] && atlantic[i][j]) // agar uss particular point se dono oceans mai jaa paa rahe hai
                    ans.push_back({i,j});           // toh answer push kardo
            }
        }
        return ans;
    }
};
/*
Example 1:
Input: heights = [[1,2,2,3,5],
                  [3,2,3,4,4],
                  [2,4,5,3,1],
                  [6,7,1,4,5],
                  [5,1,1,2,4]]
Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
Explanation: The following cells can flow to the Pacific and Atlantic oceans, as shown below:
[0,4]: [0,4] -> Pacific Ocean 
       [0,4] -> Atlantic Ocean
[1,3]: [1,3] -> [0,3] -> Pacific Ocean 
       [1,3] -> [1,4] -> Atlantic Ocean
[1,4]: [1,4] -> [1,3] -> [0,3] -> Pacific Ocean 
       [1,4] -> Atlantic Ocean
[2,2]: [2,2] -> [1,2] -> [0,2] -> Pacific Ocean 
       [2,2] -> [2,3] -> [2,4] -> Atlantic Ocean
[3,0]: [3,0] -> Pacific Ocean 
       [3,0] -> [4,0] -> Atlantic Ocean
[3,1]: [3,1] -> [3,0] -> Pacific Ocean 
       [3,1] -> [4,1] -> Atlantic Ocean
[4,0]: [4,0] -> Pacific Ocean 
       [4,0] -> Atlantic Ocean
Note that there are other possible paths for these cells to flow to the Pacific and Atlantic oceans.

Example 2:
Input: heights = [[1]]
Output: [[0,0]]
Explanation: The water can flow from the only cell to the Pacific and Atlantic oceans.
*/


//30. NUMBER OF ISLANDS (IN A MATRIX)                             {T.C = O(N*M), S.C = O(N*M)}
class Solution {
public:
    vector<vector<int>>directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool isValid(int i, int j, int n, int m){
        return (i >= 0 && i < n && j >= 0 && j < m);
    }
    void dfs(vector<vector<char>>&grid, vector<vector<bool>>&vis, int i, int j){
        int n = grid.size(), m = grid[0].size();
        vis[i][j] = true;
        for(auto it : directions){
            int newR = i + it[0];
            int newC = j + it[1];

            if(isValid(newR, newC, n, m) && !vis[newR][newC] && grid[i][j] == '1'){
                dfs(grid, vis, newR, newC);
            } 
        }
    }
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>>vis(n, vector<bool>(m, false));
        int count = 0;
        for(int i = 0; i < n ; i++){
            for(int j = 0 ; j < m ; j++){
                if(!vis[i][j] && grid[i][j] == '1'){
                    count++;
                    dfs(grid, vis, i, j);
                }
            }
        }
        return count;
    }
};
/*
Example 1:
Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1

Example 2:
Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3
*/


//30b. CONNECTED COMPONENTS IN AN UNDIRECTED GRAPH              {T.C = O(V+E+CLOGC), S.C = O(V+E)}
class Solution {
  public:
    void dfs(unordered_map<int,vector<int>>&adj, vector<bool>&vis, vector<int>&components, int node){
        vis[node] = true;
        components.push_back(node);
        for(auto it : adj[node]){
            if(!vis[it]) dfs(adj, vis, components, it);
        }
    }
    vector<vector<int>> connectedcomponents(int v, vector<vector<int>>& edges) {
        unordered_map<int,vector<int>>adj;
        for(auto it : edges){
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }
        
        vector<bool>vis(v, false);
        // int components = 0;
        vector<vector<int>>ans;
        for(int i = 0 ; i < v ; i++){
            if(!vis[i]){
                vector<int>components;
                // components++;
                dfs(adj, vis, components, i);
                sort(components.begin(), components.end());           //sorting required in this particular ques
                ans.push_back(components);
            }
        }
        // return components;
        return ans;
    }
};
/*
Examples :
Input: e=3, v=5, edges = [{0, 1},{2, 1},{3, 4}]
Output: [[0, 1, 2],[3, 4]]
Explanation: 
Example of an undirected graph

Example 2:
Input: e=5, v=7, edges=[{0, 1},{6, 1},{2, 4},{2, 3},{3, 4}]
Output: [[0, 1, 6],[2, 3, 4],[5]]
*/


//31. LONGEST CONSECUTIVE SEQUENCE                               
//USING SET                                                       {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n = nums.size();
        int maxLen = 0;                           
        unordered_set<int>st(nums.begin(), nums.end());
        for(auto it : st){
            if(!st.count(it-1)){
                int count = 1;
                int nextEle = it;
                while(st.count(nextEle+1)){
                    count++;
                    nextEle++;
                }
                maxLen = max(maxLen, count);
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


//32. ALIEN DICTIONARY                                           {T.C = O(V+E), S.C = O(V+E)}
class Solution{
    public:
    vector<int>topoSort(int V , unordered_map<int, vector<int>>&adj){
        vector<int>ans;
        vector<int>inDegree(V, 0);
        
        //calculate indegrees for each nodes
        for(int i = 0 ; i < V ; i++){
            for(auto it : adj[i]){
                inDegree[it]++;
            }
        }
        
        queue<int>q;
        //push 0 indegree's in queue
        for(int i = 0 ; i < V ; i++){
            if(inDegree[i] == 0){
                q.push(i);
            }
        }
        
        //do dfs
        while(!q.empty()){
            int frontNode = q.front();
            q.pop();
            ans.push_back(frontNode);
            
            //reduce indegree of adjacent nodes after disconnection of node
            for(auto it : adj[frontNode]){
                inDegree[it]--;
                if(inDegree[it] == 0){
                    q.push(it);
                }
            }
        }
        return ans;
    }
    string findOrder(string dict[], int n, int k) {
        //create adjacency list
        unordered_map<int,vector<int>>adj;
        for(int i = 0 ; i < n-1 ; i++){             //compare till second last elemenent is possible
            string s1 = dict[i];
            string s2 = dict[i+1];
            int len = min(s1.size(), s2.size());    //compare till small string length
            for(int j = 0 ; j < len ; j++){
                if(s1[j] != s2[j]){                 //if char match skip
                    int u = s1[j]-'a';
                    int v = s2[j]-'a';
                    
                    adj[u].push_back(v);             //u before v (u -> v)
                    break;
                } 
            }
        }
        
        vector<int>topo = topoSort(k, adj);          //no. of v is k not n
        string ans = "";
        for(auto it : topo){
            ans = ans + char(it + 'a');
        }
        return ans;
    }
};
/*
Input:  n = 5, k = 4, dict = {"baa","abcd","abca","cab","cad"}
Output: 1
Explanation: Here order of characters is 'b', 'd', 'a', 'c' Note that words are sorted and in the given language "baa" comes before "abcd", therefore 'b' is before 'a' in output.
Similarly we can find other orders.

Input: n = 3, k = 3, dict = {"caa","aaa","aab"}
Output: 1
Explanation: Here order of characters is 'c', 'a', 'b' Note that words are sorted and in the given language "caa" comes before "aaa", therefore 'c' is before 'a' in output.
Similarly we can find other orders.
*/


//33. GRAPH VALID TREE                                           {T.C = O(V+E), S.C = O(V+E)}
//FOR TREE = GRAPH SHOULD = 1 COMPONENTS & NO CYCLE
bool dfsUnCycle(unordered_map<int,vector<int>>&adj, vector<bool>&vis, int node, int prev){
    vis[node] = true;
    for(auto it : adj[node]){
        if(!vis[it]){
            if(dfsUnCycle(adj, vis, it, node)) return true;              //node becomes prev
        }else if(it != prev) return true;           //visited but not parent (cycle present)
    }
    return false;
}
bool isCyclicSingleComp(unordered_map<int,vector<int>>&adj, int n){
    vector<bool>vis(n, false);
    int components = 0;
    bool hasCycle = false;
    for(int i = 0; i < n; i++){
        if(!vis[i]){
            components++;
            if(dfsUnCycle(adj, vis, i, -1)) hasCycle = true;
        } 
    }

    return (components == 1) && !hasCycle;        //tree = 1 component & no cycle
}
bool checkgraph(vector<vector<int>> edges, int n, int m){
    unordered_map<int,vector<int>>adj;
    for(auto it : edges){
        adj[it[0]].push_back(it[1]);
        adj[it[1]].push_back(it[0]);
    }
    return isCyclicSingleComp(adj, n);
}
/*
Sample Input 1 :
2
5
4
0 1
0 2
0 3
1 4
5
5
0 1
1 2
2 3
1 3
1 4
Sample Output 1 :
True
False
*/


//34. NUMBER OF CONNECTED COMPONENTS IN A GRAPH                  {T.C = O(V+E), S.C = O(V+E)}
class Solution {
  public:
    void dfs(unordered_map<int,vector<int>>&adj, vector<bool>&vis,  int node){
        vis[node] = true;
        for(auto it : adj[node]){
            if(!vis[it]) dfs(adj, vis, it);
        }
    }
    int connectedcomponents(int v, vector<vector<int>>& edges) {
        unordered_map<int,vector<int>>adj;
        for(auto it : edges){
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }
        
        vector<bool>vis(v, false);
        int components = 0;
        for(int i = 0 ; i < v ; i++){
            if(!vis[i]){
                components++;
                dfs(adj, vis, i);
            }
        }
        return components;
    }
};
/*
Input: e=3, v=5, edges = [{0, 1},{2, 1},{3, 4}]
Output: 2
Explanation: 
Example of an undirected graph

Example 2:
Input: e=5, v=7, edges=[{0, 1},{6, 1},{2, 4},{2, 3},{3, 4}]
Output: 3
*/


//35. INSERT INTERVAL                                             {T.C = O(N), S.C = O(N)}
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int n = intervals.size();
        vector<vector<int>>ans;
        int i = 0;
        while(i < n && intervals[i][1] < newInterval[0]){    //push before overlap intervals
            ans.push_back(intervals[i]);
            i++;
        }

        while(i < n && intervals[i][0] <= newInterval[1]){    //overlap intervals (update intervals then push)
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }
        ans.push_back(newInterval);

        while(i < n){                                       //after overlap intervals (rest of intervals)
            ans.push_back(intervals[i]);
            i++;
        }
        return ans;
    }
};
/*
Example 1:
Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]

Example 2:
Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
*/


//36. MERGE INTERVALS                                           {T.C = O(N*LOGN), S.C = O(N)}
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int n = intervals.size();
        sort(intervals.begin(), intervals.end());
        vector<vector<int>>ans;
        vector<int>tempInterval = intervals[0];
        for(int i = 1 ; i < n ;i++){
            if(tempInterval[1] >= intervals[i][0]){           //merge (prevEnd == currStart) also
                tempInterval[0] = min(tempInterval[0], intervals[i][0]);
                tempInterval[1] = max(tempInterval[1], intervals[i][1]);
            }else{
                ans.push_back(tempInterval);
                tempInterval = intervals[i];                 //move next
            }
        }
        ans.push_back(tempInterval);                   //for last interval
        return ans;
    }
};
/*
Example 1:
Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].

Example 2:
Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.
*/


//37. NON OVERALAPPING INTERVALS                                  {T.C = O(N*LOGN), S.C = O(1)}
//for erase overalap interval (we have to think greedly so sort on basis of ending (high have good chances to overlap more intervals))
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int n = intervals.size();
        auto lambda = [&](auto &a, auto &b){
            return (a[1] < b[1]);
        };
        int count = 0;
        sort(intervals.begin(), intervals.end(), lambda);   //large ending time , have more chance to overlap to other(better to remove that)
        vector<int>tempInterval = intervals[0];
        // for(auto it : intervals){               //in this 1st(tempInterval) intvl is also included
        for(int i = 1; i < n; i++){
            if(intervals[i][0] < tempInterval[1]){           //currentStart < prevEnd
                count++;
            }else{
                tempInterval = intervals[i];
            }
        }
        return count;
    }
};
/*
Example 1:
Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
Output: 1
Explanation: [1,3] can be removed and the rest of the intervals are non-overlapping.

Example 2:
Input: intervals = [[1,2],[1,2],[1,2]]
Output: 2
Explanation: You need to remove two [1,2] to make the rest of the intervals non-overlapping.

Example 3:
Input: intervals = [[1,2],[2,3]]
Output: 0
Explanation: You don't need to remove any of the intervals since they're already non-overlapping.
*/


//38. REPEATING AND MISSING                                     {T.C = O(N), S.C = O(N)} 
class Solution {
  public:
    vector<int> findTwoElement(vector<int>& arr) {
        int n = arr.size();
        unordered_map<int,int>mp;
        for(auto it : arr) mp[it]++;
        
        int repeating = -1, missing = -1;
        for(int i = 1 ; i <= n; i++){
            if(mp[i] == 2) repeating = i;
            if(mp[i] == 0) missing = i;
        }
        return {repeating, missing};
    }
};
/*
Input: arr[] = [2, 2]
Output: [2, 1]
Explanation: Repeating number is 2 and smallest positive missing number is 1.

Input: arr[] = [1, 3, 3] 
Output: [3, 2]
Explanation: Repeating number is 3 and smallest positive missing number is 2.

Input: arr[] = [4, 3, 6, 2, 1, 1]
Output: [1, 5]
Explanation: Repeating number is 1 and the missing number is 5.
*/


/*Definition of Interval:
class Interval {
public:
    int start, end;
    Interval(int start, int end) {
        this->start = start;
        this->end = end;
    }
}
*/
//39. MEETING ROOMS I                                             {T.C = O(N*LOGN), S.C = O(1)}
class Solution {
public:
    bool canAttendMeetings(vector<Interval>& intervals) {
        int n = intervals.size();
        //base case
        if(n == 0) return true;
        auto lambda = [&](auto &a, auto &b){
            return a.start < b.start;
        };
        sort(intervals.begin(), intervals.end(), lambda);           //according to start time
        Interval tempInterval = intervals[0];
        for(int i = 1 ; i < n ; i++){
            if(tempInterval.end > intervals[i].start) return false;
            else tempInterval = intervals[i];
        }
        return true;
    }
};
/*
Example 1:
Input: intervals = [(0,30),(5,10),(15,20)]
Output: false
Explanation:
(0,30) and (5,10) will conflict
(0,30) and (15,20) will conflict

Example 2:
Input: intervals = [(5,8),(9,15)]
Output: true
*/


//40. MEETING ROOMS II                                           {T.C = O(N*LOGN), S.C = O(N)}
class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        int n = intervals.size();
        //base case
        if(n == 0) return 0;                 //no interval
        
        auto lambda = [&](auto &a, auto &b){
            return a.start < b.start;
        };
        sort(intervals.begin(), intervals.end(), lambda);  //sort by start time
        
        priority_queue<int, vector<int>, greater<int>>minHeap;
        Interval tempInterval = intervals[0];
        minHeap.push(tempInterval.end);                  //push only end time of meet
        for(int i = 1 ; i < n ; i++){
            if(minHeap.top() <= intervals[i].start){       //pop curr for adjust next
                minHeap.pop();
            }
            minHeap.push(intervals[i].end);
        }
        return minHeap.size();                            //required minimum rooms
    }
};
/*
Example 1:
Input: intervals = [(0,40),(5,10),(15,20)]
Output: 2
Explanation:
day1: (0,40)
day2: (5,10),(15,20)

Example 2:
Input: intervals = [(4,9)]
Output: 1
*/


//41. REVERSE LINKED LIST                                        {T.C = O(N), S.C = O(1)}
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


//42. LINKED LIST CYCLE                                           {T.C = O(N), S.C = O(1)}
class Solution {
public:
    bool hasCycle(ListNode *head) {
        //base case
        if(!head) return false;

        ListNode* slow = head;
        ListNode* fast = head;
        while(fast && fast->next){            //all required
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


//43. MERGE 2 SORTED LIST                                         {T.C = O(N), S.C = O(1)}
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


//44. MERGE K SORTED ARRAYS                                       {T.C = O(N*LOGN), S.C = O(N)},N = K^2
class Solution{
public:
    typedef pair<int,pair<int,int>>P;
    vector<int> mergeKArrays(vector<vector<int>> arr, int K){
        int n = arr.size();               //n == m == K
        vector<P>temp;
        for(int row = 0 ; row < n ; row++){               //put 1, 2, 3.. k , col element
            temp.push_back({arr[row][0], {row, 0}});
        }
        
        priority_queue<P, vector<P>, greater<P>>minHeap(temp.begin(), temp.end()); //insert all ele of temp in minHeap
        vector<int>ans;                             //extract ans from heap and push in ans vec
        while(!minHeap.empty()){
            auto topNode = minHeap.top();
            minHeap.pop();
            int val = topNode.first;
            int row = topNode.second.first;
            int col = topNode.second.second;
            
            ans.push_back(val);
            
            if(col+1 < K) minHeap.push({arr[row][col+1], {row, col+1}});
        }
        return ans;
    }
};
/*
Input: k = 3, arr[][] = {{1,2,3},{4,5,6},{7,8,9}}
Output: 1 2 3 4 5 6 7 8 9
Explanation: Above test case has 3 sorted arrays of size 3, 3, 3 arr[][] = [[1, 2, 3],[4, 5, 6],[7, 8, 9]]. The merged list will be [1, 2, 3, 4, 5, 6, 7, 8, 9].

Input: k = 4, arr[][]={{1,2,3,4},{2,2,3,4},{5,5,6,6},{7,8,9,9}}
Output: 1 2 2 2 3 3 4 4 5 5 6 6 7 8 9 9 
Explanation: Above test case has 4 sorted arrays of size 4, 4, 4, 4 arr[][] = [[1, 2, 2, 2], [3, 3, 4, 4], [5, 5, 6, 6], [7, 8, 9, 9 ]]. The merged list will be [1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8, 9, 9].
*/


//45. REMOVE NTH NODE FROM THE END OF LINKED LIST               {T.C = O(N), S.C = O(1)}
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(NULL);
        dummy->next = head;

        ListNode* slow = dummy;
        ListNode* fast = dummy;
        
        while(n--){                                  //reach to nth from start node
            fast = fast->next;
        }

        while(fast->next){                           //move until list end & move simultaneously(slow , fast)
            slow = slow->next;
            fast = fast->next;
        }
        slow->next = slow->next->next;               //slow points to nth node from end

        return dummy->next;               //head
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


//45. REMOVE NTH NODE FROM THE START OF LINKED LIST               {T.C = O(N), S.C = O(1)}
class Solution {
  public:
    Node* deleteNode(Node* head, int x) {
        Node* curr = head;
        if(x == 1){
            curr = curr->next;
            return curr;
        }
        
        for(int i = 1 ; i < x-1 ; i++){
            curr = curr->next;
        }
        curr->next = curr->next->next;
        return head;
    }
};
/*
Input: Linked list: 1 -> 3 -> 4, x = 3
Output: 1 -> 3
Explanation: After deleting the node at the 3rd position (1-base indexing), the linked list is as 1 -> 3. 

Input: Linked list: 1 -> 5 -> 2 -> 9, x = 2 
Output: 1 -> 2 -> 9
Explanation: After deleting the node at 2nd position (1-based indexing), the linked list is as 1 -> 2 -> 9.
*/


//46. REORDER LIST                                               {T.C = O(N), S.C = O(1)}
class Solution {
public:
    ListNode* reverse(ListNode* node){
        ListNode* prev = NULL;
        ListNode* curr = node;
        ListNode* forw = NULL;

        while(curr){
            forw = curr->next;
            curr->next = prev;
            prev = curr;
            curr = forw;
        }
        return prev;
    }
    void reorderList(ListNode* head) {
        //base case
        if(!head || !head->next) return;

        ListNode* slow = head;
        ListNode* fast = head;

        while(fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
        }    
        ListNode* nextHalf = reverse(slow->next);    //next start from next of slow
        slow->next = NULL;                           //break prevHalf & nexHalf
        ListNode* prevHalf = head;

        while(prevHalf && nextHalf){
            ListNode* temp1 = prevHalf->next;
            ListNode* temp2 = nextHalf->next;

            prevHalf->next = nextHalf;
            nextHalf->next = temp1;

            prevHalf = temp1;
            nextHalf = temp2;
        }
    }
};
/*
Example 1:
Input: head = [1,2,3,4]
Output: [1,4,2,3]

Example 2:
Input: head = [1,2,3,4,5]
Output: [1,5,2,4,3]
*/


//47. SET MATRIX ZEROES                                          {T.C = O(N*M), S.C = O(N+M)}
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        vector<int>row(n, 0);
        vector<int>col(m, 0);
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < m ; j++){
                if(matrix[i][j] == 0){
                    row[i] = 1;                       //filling row and col vector
                    col[j] = 1;
                }
            }
        }

        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ;j < m ; j++){
                if(row[i] == 1 || col[j] == 1) matrix[i][j] = 0;      //any val of row, col = 1, set val to 0
            }
        }
    }
};
/*
Example 1:
Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
Output: [[1,0,1],[0,0,0],[1,0,1]]

Example 2:
Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
*/


//48. SPIRAL MATRIX                                               {T.C = O(N*M), S.C = O(N*M)}
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int>ans;
        int n = matrix.size(), m = matrix[0].size();
        int rStart = 0, cStart = 0;
        int rEnd = n-1, cEnd = m-1;

        while(rStart <= rEnd && cStart <= cEnd){
            //print first row
            for(int i = cStart ; i <= cEnd ; i++){
                ans.push_back(matrix[rStart][i]);
            }
            rStart++;
            //print last col
            for(int i = rStart ; i <= rEnd ; i++){
                ans.push_back(matrix[i][cEnd]);
            }
            cEnd--;
            //print last row (first check)
            if(rStart <= rEnd){
                for(int i = cEnd ; i >= cStart ; i--){
                    ans.push_back(matrix[rEnd][i]);
                }
                rEnd--;
            }
            //print 1st col
            if(cStart <= cEnd){
                for(int i = rEnd ; i >= rStart ; i--){
                    ans.push_back(matrix[i][cStart]);
                }
                cStart++;
            }
        }

        return ans;
    }
};
/*
Example 1:
Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,3,6,9,8,7,4,5]

Example 2:
Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]
*/


//49. ROTATE IMAGE                                               {T.C = O(N*M), S.C = O(1)}
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();             //n = m
        for(int i = 0 ; i < n; i++){                  //transpose of matrix
            for(int j = i ; j < n ; j++){
                swap(matrix[i][j], matrix[j][i]);
            }
        }

        //reverse each row
        for(int i = 0 ; i < n; i++){
            int l = 0, r = n-1;
            while(l <= r){
                swap(matrix[i][l], matrix[i][r]);
                l++, r--;
            }
        }
    }
};
/*
Example 1:
Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[7,4,1],[8,5,2],[9,6,3]]

Example 2:
Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
*/


//50. WORD SEARCH                                                     {T.C = O(4^N*N*M), S.C = O(N*M)}
class Solution {
public:
    bool isValid(int i, int j, int n, int m){
        return (i >= 0 && i < n && j >= 0 && j < m);
    }
    bool dfs(vector<vector<char>>&board, string &word, vector<vector<bool>>&vis, int i, int j, int idx){
        int n = board.size(), m = board[0].size();
        if(idx == word.length()) return true;                              //word found

        if(!isValid(i, j, n, m) || vis[i][j] || board[i][j] != word[idx]) return false;

        vis[i][j] = true;
        //Check in all 4 directions               
        bool found = dfs(board, word, vis, i + 1, j, idx+1) ||
                     dfs(board, word, vis, i - 1, j, idx+1) ||
                     dfs(board, word, vis, i, j + 1, idx+1) ||
                     dfs(board, word, vis, i, j - 1, idx+1);
        /*for this pruning is required
        for (auto it : directions) {
            int newI = i + it[0];
            int newJ = j + it[1];

            if (dfs(board, word, vis, newI, newJ, idx+1)) return true; 
        }
        */

        // Mark the current cell as unvisited after exploration
        vis[i][j] = false;                   //backtrack

        return found;
    }
    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size(), m = board[0].size();
        vector<vector<bool>>vis(n, vector<bool>(m, false));
        for(int i = 0 ; i < n; i++){
            for(int j = 0; j < m; j++){
                if(dfs(board, word, vis, i, j, 0)) return true;
            }
        }
        return false;
    }
};
/*
Example 1:
Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
Output: true

Example 2:
Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
Output: true

Example 3:
Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
Output: false
*/


//51. LONGEST SUBSTRING WITHOUT REPEATING CHARACTERS             {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.length();
        int maxLen = 0;
        unordered_map<int,int>mp;
        int i = 0, j = 0;
        while(j < n){
            mp[s[j]]++;

            while(mp[s[j]] > 1){                  //if freq > 1 remove it
                mp[s[i]]--;
                if(mp[s[i]] == 0) mp.erase(s[i]);
                i++;
            }
            maxLen = max(maxLen, j-i+1);
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


//52. LONGEST REPEATING CHARACTER REPLACEMENT                    {T.C = O(N), S.C = O(N)}    
class Solution {
public:
    int characterReplacement(string s, int k) {
        int n = s.length();
        unordered_map<int,int>mp;
        int maxLen = 0, maxFreq = 0;
        int i = 0, j = 0;

        while (j < n) {
            mp[s[j]]++;
            maxFreq = max(maxFreq, mp[s[j]]);

            if ((j-i+1) - maxFreq > k) {          //sz of currWin - freq (replacement required)   
                mp[s[i]]--;
                i++;
            }

            maxLen = max(maxLen, j-i+1);
            j++;
        }

        return maxLen;
    }
};
/*
Example 1:
Input: s = "ABAB", k = 2
Output: 4
Explanation: Replace the two 'A's with two 'B's or vice versa.

Example 2:
Input: s = "AABABBA", k = 1
Output: 4
Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.
There may exists other ways to achieve this answer too.
*/


//53. MINIMUM WINDOW SUBSTRING                                   {T.C = O(N), S.C = O(N)}
class Solution {
public:
    string minWindow(string s, string t) {
        int n = s.length(), m = t.length();
        unordered_map<int,int>mp;
        for(auto it : t) mp[it]++;
        int minLen = INT_MAX;
        int count = mp.size();
        int i = 0, j = 0, start = 0;
        while(j < n){
            if(mp.count(s[j])){
                mp[s[j]]--;
                if(mp[s[j]] == 0) count--;             //not erase 
            }
            while(count == 0){                    //shring window , finding minLen
                if(mp.count(s[i])){
                    mp[s[i]]++;
                    if(mp[s[i]] == 1){
                        count++;
                        if(minLen > j-i+1){
                            minLen = j-i+1;
                            start = i;           //window starting idx
                        }
                    }
                }
                i++;
            }
            j++;
        }
        return minLen == INT_MAX ? "" : s.substr(start, minLen);
    }
};
/*
Example 1:
Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.

Example 2:
Input: s = "a", t = "a"
Output: "a"
Explanation: The entire string s is the minimum window.

Example 3:
Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.
*/


//54. VALID ANAGRAM 
//BRUTE FORCE                                                    {T.C = O(N*LOGN), S.C = O(1)}
class Solution {
public:
    bool isAnagram(string s, string t) {
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t;
    }
};

//USING MAP                                                     {T.C = O(N), S.C = O(N)}
class Solution {
public:
    bool isAnagram(string s, string t) {
        //base case
        if(s.length() != t.length()) return false;
        unordered_map<char,int>mp;
        for(auto it : s){
            mp[it]++;
        }
        for(auto it : t){
            if(mp.count(it)){
                mp[it]--;
                if(mp[it] == 0) mp.erase(it);
            }
        }
        if(mp.empty()) return true;
        return false;
    }
};
/*
Example 1:
Input: s = "anagram", t = "nagaram"
Output: true

Example 2:
Input: s = "rat", t = "car"
Output: false
*/


//55. GROUP ANAGRAMS
//USING SORTING + MAP                                           {T.C = O(N*(M*LOGM)), S.C = O(N)}
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& s) {
        int n = s.size();
        unordered_map<string, vector<string>>mp;             //actual -> sorted vector push (actual)
        for(auto it : s){
            string temp = it;
            sort(temp.begin(), temp.end());
            mp[temp].push_back(it);
        }
        vector<vector<string>>ans;
        for(auto it : mp){
            ans.push_back(it.second);                      //push collected vectors
        }
        return ans;
    }
};

//WITHOUT SORTING (FREQUENCY VECTOR)                            {T.C = O(N*(M+26)), S.C = O(N)}
class Solution {
public:
    string generate(string &word){
        vector<int>freq(26, 0);
        for(auto it : word){
            freq[it-'a']++;
        }

        //search similar freq word (anagram)
        string newWord = "";
        for(int i = 0 ; i < 26 ; i++){
            if(freq[i] > 0) newWord += string(freq[i], i + 'a');  //+'a' for finding word(char)
        }
        return newWord;
    }
    vector<vector<string>> groupAnagrams(vector<string>& s) {
        int n = s.size();
        unordered_map<string, vector<string>>mp;             //actual -> sorted vector push (actual)
        for(auto it : s){
            string temp = it;
            // sort(temp.begin(), temp.end());
            // mp[temp].push_back(it);
            string newWord = generate(temp);
            mp[newWord].push_back(temp);
        }
        vector<vector<string>>ans;
        for(auto it : mp){
            ans.push_back(it.second);                      //push collected vectors
        }
        return ans;
    }
};
/*
Example 1:
Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
Explanation:
There is no string in strs that can be rearranged to form "bat".
The strings "nat" and "tan" are anagrams as they can be rearranged to form each other.
The strings "ate", "eat", and "tea" are anagrams as they can be rearranged to form each other.

Example 2:
Input: strs = [""]
Output: [[""]]

Example 3:
Input: strs = ["a"]
Output: [["a"]]
*/


//56. VALID PARENTHESES                                           {T.C = O(N), S.C = O(N)}
class Solution {
public:
    bool isValid(string s) {
        stack<char>stk;
        for(auto it : s){
            if(it == '(' ||  it == '{' || it == '[') stk.push(it);
            else if( !stk.empty() && ( (it == ')' && stk.top() == '(' ) || (it == ']' && stk.top() == '[') || (it == '}' && stk.top() == '{') )) stk.pop();
            else return false;
        }
        return stk.empty();
    }
};
/*
Example 1:
Input: s = "()"
Output: true

Example 2:
Input: s = "()[]{}"
Output: true

Example 3:
Input: s = "(]"
Output: false

Example 4:
Input: s = "([])"
Output: true
*/


//57. CHECK PALINDROME
class Solution {
public:
    bool isPalindrome(int x) {
        string s = to_string(x);
        int n = s.length();
        int i = 0, j = n-1;
        while(i < j){
            if(s[i] != s[j]) return false;
            i++, j--;
        }
        return true;
    }
};
/*
Example 1:
Input: x = 121
Output: true
Explanation: 121 reads as 121 from left to right and from right to left.

Example 2:
Input: x = -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.

Example 3:
Input: x = 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
*/

//58. LONGEST PALINDROMIC SUBSTRING
//USING DP                                                        {T.C = O(N^2), S.C = O(N^2)}
class Solution {
public:
    int dp[1005][1005];
    bool solveMem(string &s, int i, int j){
        //base case
        if(i >= j) return true;               //single char, or empty string is true

        if(dp[i][j] != -1) return dp[i][j];

        if(s[i] == s[j]) return dp[i][j] = solveMem(s, i+1, j-1);      //first , last match
        return false;
    }
    string longestPalindrome(string s) {
        memset(dp, -1, sizeof(dp));
        int n = s.length();
        int maxLen = 0;
        int startIdx = 0;
        for(int i = 0 ; i < n; i++){
            for(int j = i ; j < n ; j++){                         //SUBSTRING STARTING FROM i.
                if(solveMem(s, i, j)){
                    if(j-i+1 > maxLen){
                        maxLen = j-i+1;
                        startIdx = i;
                    }
                }
            }
        }
        return s.substr(startIdx, maxLen);
    }
};

//USING BOTTOM UP DP 
//(MIK TEMPLATE FOR PALINDROMES(COUNT, LONGEST PALINDROMIC SUBSTRING OR SUBSEQUENCE)) {T.C = O(N^2), S.C = O(N^2)}
class Solution {
public:
    //USING MIK BLUEPRINT
    int countSubstrings(string s) {
        int n = s.length();
        vector<vector<int>>dp(n, vector<int>(n, false));
        int count = 0;

        for(int l = 1 ; l <= n ; l++){
            for(int i = 0 ; i+l-1 < n; i++){                  //i+L-1(curr len of substring)
                int j = i+l-1;
                if(i == j)   dp[i][j] = true;                            //1 len string
                else if(i+1 == j) dp[i][j] = (s[i] == s[j]);             //2 len string
                else{
                    dp[i][j] = (s[i] == s[j] && dp[i+1][j-1] == true);   //>2 len string
                }

                if(dp[i][j] == true) count++;
            }
        }
        return count;
    }
};

//WITHOUT DP                                                     {T.C = O(N^2), S.C = O(N)}
class Solution {
public:
    string expandFromCenter(string &s, int left, int right){
        while(left >= 0 && right < s.length() && s[left] == s[right]){
            left--;
            right++;
        }
        return s.substr(left+1, right-left-1);          //(starting index, length)
    }
    string longestPalindrome(string s) {
        int n = s.length();

        //base case
        if(s.length() <= 1) return s;

        string maxStr = s.substr(0, 1);                 //(starting index, length)
        for(int i = 0 ; i < n-1 ; i++){
            string odd = expandFromCenter(s, i, i);     //partition on char
            string eve = expandFromCenter(s, i, i+1);   //partition in between char

            if(odd.length() > maxStr.length()){
                maxStr = odd;
            }
            if(eve.length() > maxStr.length()){
                maxStr = eve;
            }
        }
        return maxStr;
    }
};
/*
Example 1:
Input: s = "babad"
Output: "bab"
Explanation: "aba" is also a valid answer.

Example 2:
Input: s = "cbbd"
Output: "bb"
*/


//59. PALINDROMIC SUBSTRING                                      
//BRUTE FORCE                                                     {T.C = O(N^3), S.C = O(1)}
class Solution {
public:
    bool isPalindrome(const string &s){
        int n = s.length();
        int i = 0, j = n-1;
        while(i < j){
            if(s[i] != s[j]) return false;
            i++ , j--;
        }
        return true;
    }
    int countSubstrings(string s) {
        int n = s.length();
        int count = 0;
        for(int i = 0 ; i < n ; i++){
            for(int j = i ; j < n ; j++){
                if(isPalindrome(s.substr(i, j-i+1))) count++;
            }
        }
        return count;
    }
};

//SMART APPROACH                                                  {T.C = O(N^2), S.C = O(1)}
class Solution {
public:
    void checkOddAndEven(int i, int j, string &s, int &count){
        int n = s.length();
        while(i >= 0 && j < n && s[i] == s[j]){
            count++;
            i--, j++;
        }
    }
    int countSubstrings(string s) {
        int n = s.length();
        int count = 0;
        for(int i = 0 ; i < n ; i++){
            checkOddAndEven(i, i,   s, count);
            checkOddAndEven(i, i+1, s, count);
        }
        return count;
    }
};
/*
Example 1:
Input: s = "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".

Example 2:
Input: s = "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".
*/


//60. ENCODE AND DECODE STRINGS                                   {T.C = O(N), S.C = O(N)}
class Solution {
public:
    string encode(vector<string>& strs) {
        string encodeStr = "";
        for(auto it : strs){
            encodeStr += to_string(it.length()) + '#' + it;
        }
        return encodeStr;
    }

    vector<string> decode(string s) {
        vector<string>decodeStr;
        int i = 0;
        while(i < s.length()){
            int j = i;
            while(s[j] != '#') j++;

            int len = stoi(s.substr(i, j-i));
            string str = s.substr(j+1, len);
            decodeStr.push_back(str);
            i = j+1+len;
        }
        return decodeStr;
    }
};
/*
Example 1:
Input: ["neet","code","love","you"]
Output:["neet","code","love","you"]

Example 2:
Input: ["we","say",":","yes"]
Output: ["we","say",":","yes"]
*/


//61. MAXIMUM DEPTH / HEIGHT OF BINARY TREE                      {T.C = O(N), S.C = O(H)}
class Solution {
public:
    int maxDepth(TreeNode* root) {
        //base case
        if(!root) return 0;
        
        int left = maxDepth(root->left);
        int right = maxDepth(root->right);

        return max(left, right)+1;               //1 = for current level
    }
};
/*
Example 1:
Input: root = [3,9,20,null,null,15,7]
Output: 3

Example 2:
Input: root = [1,null,2]
Output: 2
*/


//62. SAME TREE                                                 {T.C = O(N), S.C = O(H)} 
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(!p && !q) return true;
        if(!p || !q) return false;

        if(p->val != q->val) return false;

        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};
/*
Example 1:
Input: p = [1,2,3], q = [1,2,3]
Output: true

Example 2:
Input: p = [1,2], q = [1,null,2]
Output: false

Example 3:
Input: p = [1,2,1], q = [1,1,2]
Output: false
*/


//63. INVERT BINARY TREE                                          {T.C = O(N), S.C = O(H)}
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(!root) return NULL;

        TreeNode* temp = root->left;
        root->left = root->right;
        root->right = temp;
        invertTree(root->left);
        invertTree(root->right);

        return root;
    }
};
/*
Example 1:
Input: root = [4,2,7,1,3,6,9]
Output: [4,7,2,9,6,3,1]

Example 2:
Input: root = [2,1,3]
Output: [2,3,1]

Example 3:
Input: root = []
Output: []
*/


//64. BINARY TREE MAXIMUM PATH SUM                               {T.C = O(N), S.C = O(H)}
class Solution {
public:
    int solve(TreeNode* root, int &maxi){
        //base case
        if(!root) return 0;

        int left = solve(root->left, maxi);
        int right = solve(root->right, maxi);
        
        int anyOnePath = max(left, right) + root->val;       //root->val == 1
        int onlyNode = root->val;
        int onlyPath = left + right + root->val;

        maxi = max({maxi, anyOnePath, onlyNode, onlyPath});
        
        return max(anyOnePath, onlyNode);                //onlyPath cant call for parent(its already ans)
        // return maxi;
    }
    int maxPathSum(TreeNode* root) {
        int maxi = INT_MIN;
        solve(root, maxi);
        return maxi;
    }
};
/*
Example 1:
Input: root = [1,2,3]
Output: 6
Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.

Example 2:
Input: root = [-10,9,20,null,null,15,7]
Output: 42
Explanation: The optimal path is 15 -> 20 -> 7 with a path sum of 15 + 20 + 7 = 42.
*/


//65. BINARY TREE LEVEL ORDER TRAVERSAL                         {T.C = O(N), S.C = O(N)} 
class Solution {
public:
    void lvlOrder(TreeNode* root, vector<vector<int>>&ans){
        //base case
        if(!root) return;

        queue<TreeNode*>q;
        q.push(root);
        while(!q.empty()){
            int sz = q.size();
            vector<int>lvlNodes;
            for(int i = 0 ; i < sz ; i++){
                auto frontNode = q.front();
                q.pop();
                lvlNodes.push_back(frontNode->val);
                if(frontNode->left) q.push(frontNode->left);
                if(frontNode->right)q.push(frontNode->right);
            }
            ans.push_back(lvlNodes);
        }
    }
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>>ans;
        lvlOrder(root, ans);
        return ans;
    }
};
/*
Example 1:
Input: root = [3,9,20,null,null,15,7]
Output: [[3],[9,20],[15,7]]

Example 2:
Input: root = [1]
Output: [[1]]

Example 3:
Input: root = []
Output: []
*/


//66. SERIALIZE AND DESERIALIZE BINARY TREE                      {T.C = O(N), S.C = O(N)}
class Codec {
public:
    void btToStr(TreeNode* root, string &serAns){
        // base case
        if(!root){
            serAns += "N ";  // for NULL
            return;
        }
        // using preorder
        serAns += to_string(root->val) + ' ';
        btToStr(root->left, serAns);
        btToStr(root->right, serAns);
    }

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string serAns = "";
        btToStr(root, serAns);
        return serAns;
    }

    TreeNode* strToBt(string &data, int &i){
        if(data[i] == 'N'){
            i += 2;  // skip 'N' and space
            return NULL;
        }

        string temp = "";
        while(data[i] != ' '){
            temp += data[i];
            i++;
        }
        //preorder
        TreeNode* root = new TreeNode(stoi(temp));
        i++;  // skip space
        root->left = strToBt(data, i);
        root->right = strToBt(data, i);

        return root;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int i = 0;
        return strToBt(data, i);
    }
};
/*
Example 1:
Input: root = [1,2,3,null,null,4,5]
Output: [1,2,3,null,null,4,5]

Example 2:
Input: root = []
Output: []
*/


//67. SUBTREE OF ANOTHER TREE                                   {T.C = O(N*M), S.C = O(H)}
class Solution {
public:
    bool isIdentical(TreeNode* p, TreeNode* q){
        //base case
        if(!p && !q) return true;
        if(!p || !q) return false;
        if(p->val != q->val) return false;
        
        return (isIdentical(p->left, q->left) && isIdentical(p->right, q->right));
    }
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if(!root) return false;
        if(root->val == subRoot->val){
            if(isIdentical(root, subRoot)) return true;
        }
        return (isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot));  //either side subtree present
    }
};
/*
Example 1:
Input: root = [3,4,5,1,2], subRoot = [4,1,2]
Output: true

Example 2:
Input: root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
Output: false
*/



//68a. CONSTRUCT BINARY TREE FROM PREORDER AND INORDER TRAVERSAL     {T.C = O(N), S.C = O(H)}
//PASS IDX BY REFERENCE , FIND ROOT IN PREORDER(START), SEARCH IN INORDER (LEFT, RIGTH SUBTREE), MAKE NEW ROOT
class Solution {
public:
    TreeNode* solve(vector<int>&preorder, vector<int>&inorder, int inOrStart, int inOrEnd , int &preOrIdx){
        //base case
        if(inOrStart > inOrEnd) return NULL;

        int rootVal = preorder[preOrIdx];
        preOrIdx++;
        int i = inOrStart;
        for(i = inOrStart ; i <= inOrEnd ; i++){           //search in inorder
            if(inorder[i] == rootVal) break;
        }

        TreeNode* root = new TreeNode(rootVal);
        //s__i-1 (i) i+1__e
        root->left = solve(preorder, inorder, inOrStart, i-1, preOrIdx);   
        root->right = solve(preorder, inorder, i+1, inOrEnd, preOrIdx);

        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();                  //n = m = inorder(same tree)
        int preOrIdx = 0;                              //pass by reference only
        return solve(preorder, inorder, 0, n-1, preOrIdx);    //0 = inOrStart, n-1 = inOrEnd
    }
};
/*
Example 1:
Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]

Example 2:
Input: preorder = [-1], inorder = [-1]
Output: [-1]
*/


//68b. CONSTRUCT BINARY TREE FROM POSTORDER AND INORDER TRAVERSAL     {T.C = O(N), S.C = O(H)}
//PASS IDX BY REFERENCE , FIND ROOT IN POSTORDER(START), SEARCH IN INORDER (LEFT, RIGTH SUBTREE), MAKE NEW ROOT
class Solution {
public:
    TreeNode* solve(vector<int>&inorder, vector<int>&postorder, int inOrStart, int inOrEnd, int &poOrIdx){
        //base case
        if(inOrStart > inOrEnd) return NULL;
        int rootVal = postorder[poOrIdx];
        poOrIdx--;
        int i = inOrStart;
        for(i = inOrStart ; i <= inOrEnd ; i++){
            if(inorder[i] == rootVal) break;
        }

        //NRL(REVERSE POST ORDER)
        TreeNode* root = new TreeNode(rootVal);
        root->right = solve(inorder, postorder, i+1, inOrEnd, poOrIdx);
        root->left = solve(inorder, postorder, inOrStart, i-1 , poOrIdx);

        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = inorder.size();
        int poOrIdx = n-1;
        return solve(inorder, postorder, 0, n-1 , poOrIdx);     //0 = inOrStart, n-1 = inOrEnd
    }
};
/*
Example 1:
Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
Output: [3,9,20,null,null,15,7]

Example 2:
Input: inorder = [-1], postorder = [-1]
Output: [-1]
*/


//69. VALIDATE BINARY SEARCH TREE                                {T.C = O(N), S.C = O(H)}
class Solution {
public:
    bool isValid(TreeNode* root, long long lowerBound, long long upperBound){
        //base case
        if(!root) return true;

        if(lowerBound >= root->val || root->val >= upperBound) return false;

        return isValid(root->left, lowerBound, root->val) && isValid(root->right, root->val, upperBound);
    }
    bool isValidBST(TreeNode* root) {
        return isValid(root, LLONG_MIN, LLONG_MAX);              //lower and upper bound (int wont work)
    }
};
/*
Example 1:
Input: root = [2,1,3]
Output: true

Example 2:
Input: root = [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.
*/


//70. KTH SMALLEST ELEMENT IN A BST                              {T.C = O(N), S.C = O(N)}
class Solution {
public:
    void treeToArr(TreeNode* root, vector<int>&vec){
        //base case
        if(!root) return;

        //inorder
        treeToArr(root->left, vec);
        vec.push_back(root->val);
        treeToArr(root->right, vec);
    }
    int kthSmallest(TreeNode* root, int k) {
        vector<int>vec;
        treeToArr(root, vec);

        return vec[k-1];
    }
};
/*
Example 1:
Input: root = [3,1,4,null,2], k = 1
Output: 1

Example 2:
Input: root = [5,3,6,2,4,null,null,1], k = 3
Output: 3
*/


//71. LOWEST COMMON ANCESTOR OF BST                              
//WITHOUT USING PROPERTIES OF BST (SIMPLE BT ALSO WORKS)       {T.C = O(N), S.C = O(H)}
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        //base case
        if(!root) return NULL;

        if(root->val == p->val || root->val == q->val) return root;

        TreeNode* leftSubTree = lowestCommonAncestor(root->left, p, q);
        TreeNode* rightSubTree= lowestCommonAncestor(root->right,p, q);

        if(leftSubTree && rightSubTree) return root;
        else if(!leftSubTree && rightSubTree) return rightSubTree;
        else if(leftSubTree && !rightSubTree) return leftSubTree;
        else return NULL;                             //!left && !right
    }
};

//USING BST PROPERTIES                                          {T.C = O(N), S.C = O(H)}
class Solution {
public:
    //using bst property 
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        //base case
        if(!root) return NULL;

        if(root->val > p->val && root->val > q->val){
            return lowestCommonAncestor(root->left, p, q);         //DIRECT RETURN
        } 
        else if(root->val < p->val && root->val < q->val){
            return lowestCommonAncestor(root->right,p, q);
        }
        return root;
    }
};
/*
Example 1:
Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
Output: 6
Explanation: The LCA of nodes 2 and 8 is 6.

Example 2:
Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
Output: 2
Explanation: The LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.

Example 3:
Input: root = [2,1], p = 2, q = 1
Output: 2
*/


//72.


//73. 


//74. TOP K FREQUENT ELEMENTS                                    {T.C = O(N), S.C = O(N)}
class Solution {
public:
    //USING MAXHEAP                                      {T.C = O(N*LOGN), S.C = O(N)}
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int>mp;
        for(auto it : nums) mp[it]++;

        priority_queue<pair<int,int>>maxHeap;                     //FREQ, ELE (REVERSE){SORT ON BASIS OF FREQ}
        for(auto it : mp) maxHeap.push({it.second, it.first});

        vector<int>ans;
        while(k--){
            ans.push_back(maxHeap.top().second);              //second is element
            maxHeap.pop();
        }
        return ans;
    }
};
/*
Example 1:
Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Example 2:
Input: nums = [1], k = 1
Output: [1]
*/


//75. FIND MEDIAN FROM DATA STREAM                               {T.C = O(N), S.C = O(N)}
class MedianFinder {
public:
    priority_queue<int>leftMaxHeap;
    priority_queue<int,vector<int>, greater<int>>rightMinHeap;
    MedianFinder() {}
    
    void addNum(int num) {
        if(leftMaxHeap.empty() || leftMaxHeap.top() > num) leftMaxHeap.push(num);
        else rightMinHeap.push(num);

        int n = leftMaxHeap.size(), m = rightMinHeap.size();
        if(n < m){
            leftMaxHeap.push(rightMinHeap.top());
            rightMinHeap.pop();
        }else if(abs(n-m) > 1){
            rightMinHeap.push(leftMaxHeap.top());
            leftMaxHeap.pop();
        }
    }
    double findMedian() {
        if(leftMaxHeap.size() == rightMinHeap.size()){
            return (leftMaxHeap.top() + rightMinHeap.top()) / 2.0;
        }
        return leftMaxHeap.top();                             //extra element in maxHeap(odd len)
    }
};
/*
Example 1:
Input
["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
[[], [1], [2], [], [3], []]
Output
[null, null, null, 1.5, null, 2.0]
Explanation
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.addNum(2);    // arr = [1, 2]
medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
medianFinder.addNum(3);    // arr[1, 2, 3]
medianFinder.findMedian(); // return 2.0
*/


/*----------------------------------------------THE END----------------------------------------------------------------*/