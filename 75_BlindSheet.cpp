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