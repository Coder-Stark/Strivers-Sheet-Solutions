#include<bits/stdc++.h>
using namespace std;

//DAY 25: DP-----------------------------------------------------------------------------------------------------
//102. MAX PRODUCT SUBARRAY                                                      {T.C = O(N), S.C = O(1)}
//USING KADANE'S ALGO(LEFT TO RIGTH, RIGTH TO LEFT BOTH)
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int maxProd = INT_MIN;
        int prod = 1;
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


//103. LONGEST INCREASING SUBSEQUENCE                                     {T.C = O(N^2), S.C = O(N^2)}
//MEOMIZATION
class Solution {
public:
    int dp[2505][2505];
    int solveMem(vector<int>&nums, int i, int prev){
        int n = nums.size();
        //base case
        if(i >= n) return 0;

        if(dp[i][prev+1] != -1) return dp[i][prev+1];           //+1 for overcome invalid index

        int incl = 0;
        if(prev == -1 || nums[i] > nums[prev]) incl = 1 + solveMem(nums, i+1, i); //i become prevIdx
        int excl = 0 + solveMem(nums, i+1, prev);

        return dp[i][prev+1] = max(incl, excl);
    }
    int lengthOfLIS(vector<int>& nums) {
        memset(dp, -1, sizeof(dp));
        return solveMem(nums, 0, -1);           //0 = initial index, -1 = prev Idx
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


//104. LONGEST COMMON SUBSEQUENCE                                         {T.C = O(N*M), S.C = O(N*M)}
//TABULATION
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.size(), m = text2.size();
        int maxLen = 0;
        vector<vector<int>>dp(n+1, vector<int>(m+1, 0));
        for(int i = 1 ; i <= n ; i++){
            for(int j = 1; j <= m ; j++){
                if(text1[i-1] == text2[j-1]){
                    dp[i][j] = 1 + dp[i-1][j-1];
                    maxLen = max(maxLen, dp[i][j]);
                }else{
                    dp[i][j] = 0 + max(dp[i-1][j], dp[i][j-1]);      //for substring (dp[i][j] = 0)
                }
            }
        }
        return maxLen;
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


//105. 01 KNAPSACK                                                     {T.C = O(N*W), S.C = O(N*W)}
class Solution {
  public:
    int dp[1005][1005];                              //N, W(total weight)
    int solveMem(vector<int>&wt, vector<int>&val, int totalWt, int i){
        int n = val.size();
        //base case
        if(i >= n) return 0;
        
        if(dp[i][totalWt] != -1) return dp[i][totalWt];
        
        int incl = 0;
        if(totalWt >= wt[i]) incl = val[i] + solveMem(wt, val, totalWt-wt[i], i+1);
        int excl = 0 + solveMem(wt, val, totalWt, i+1);
        
        return dp[i][totalWt] = max(incl, excl);
    }
    int knapSack(int W, vector<int>& wt, vector<int>& val) {
        memset(dp, -1, sizeof(dp));
        return solveMem(wt, val, W, 0);                     //0 = initial index
    }
};
/*
Input: W = 4, val[] = {1,2,3}, wt[] = {4,5,1}
Output: 3
Explanation: Choose the last item that weighs 1 unit and holds a value of 3. 

Input: W = 3, val[] = {1,2,3}, wt[] = {4,5,6}
Output: 0
Explanation: Every item has a weight exceeding the knapsack's capacity (3).
*/


//106. EDIT DISTANCE                                                        {T.C = O(N*M), S.C = O(N*M)}
class Solution {
public:
    int dp[505][505];
    int solveMem(string &a, string &b, int i, int j){
        int n = a.length(), m = b.length();
        if(i == n) return m-j;                     //a exhaust return rest of string b
        if(j == m) return n-i;

        if(dp[i][j] != -1) return dp[i][j];

        if(a[i] == b[j]) return dp[i][j] = 0 + solveMem(a, b, i+1, j+1);   //skip
        else{
            int insert = solveMem(a, b, i, j+1);
            int deletee = solveMem(a, b, i+1, j); 
            int replace = solveMem(a, b, i+1, j+1);

            return dp[i][j] = 1 + min({insert, deletee, replace});
        }
    }
    int minDistance(string word1, string word2) {
        memset(dp, -1, sizeof(dp));
        return solveMem(word1, word2, 0, 0);        //0 = initial index of both string
    }
};
/*
Example 1:
Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation: 
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')

Example 2:
Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation: 
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')
*/


//107. MAX SUM INCREASING SUBSEQUENCE                                     {T.C = O(N^2), S.C = O(N^2)}
class Solution{
public:
    int solveMem(int arr[], int n, int i, int prev, vector<vector<int>>&dp){
        // base case
        if(i >= n) return 0;
        
        if(dp[i][prev+1] != -1) return dp[i][prev+1];
        
        int sum = 0;
        int incl = 0;
        if(prev == -1 || arr[i] > arr[prev]){
            incl = arr[i] + solveMem(arr, n, i+1, i, dp);  // i becomes prev
        } 
        int excl = solveMem(arr, n, i+1, prev, dp);
        
        return dp[i][prev+1] = max(incl, excl);
    }

    int maxSumIS(int arr[], int n){  
        // memset(dp, -1, sizeof(dp));                      //not working
        vector<vector<int>>dp(n+1, vector<int>(n+1, -1));
        return solveMem(arr, n, 0, -1, dp);
    }  
};
/*
Example 1:
Input: 
N = 5, arr[] = {1, 101, 2, 3, 100} 
Output: 
106
Explanation:
The maximum sum of a increasing sequence is obtained from {1, 2, 3, 100},

Example 2:
Input: 
N = 4, arr[] = {4, 1, 2, 3}
Output: 
6
Explanation:
The maximum sum of a increasing sequence is obtained from {1, 2, 3}.
*/


//108. MATRIX CHAIN MULTIPLICATION                                             {T.C = O(N^3), S.C = O(N^2)}
//PARTITION DP
class Solution{
public:
    int dp[101][101];
    int solveMem(int arr[], int i, int j){
        //base case
        if(i == j) return 0;                            //no operation required(single element)
        
        if(dp[i][j] != -1) return dp[i][j];
        
        int operations = 0, mini = INT_MAX;
        //loop of k from i to j-1
        for(int k = i ; k < j ; k++){
            operations = arr[i-1]*arr[k]*arr[j] + solveMem(arr, i, k) + solveMem(arr, k+1, j);
            mini = min(mini, operations);
        }
        
        return dp[i][j] = mini;
    }
    int matrixMultiplication(int N, int arr[]){
        memset(dp,-1, sizeof(dp));
        return solveMem(arr, 1, N-1);                    //1 = initial index (partition dp)
    }
};
/*
Example 1:
Input: N = 5
arr = {40, 20, 30, 10, 30}
Output: 26000
Explanation: There are 4 matrices of dimension 
40x20, 20x30, 30x10, 10x30. Say the matrices are 
named as A, B, C, D. Out of all possible combinations,
the most efficient way is (A*(B*C))*D. 
The number of operations are -
20*30*10 + 40*20*10 + 40*10*30 = 26000.

Example 2:
Input: N = 4
arr = {10, 30, 5, 60}
Output: 4500
Explanation: The matrices have dimensions 
10*30, 30*5, 5*60. Say the matrices are A, B 
and C. Out of all possible combinations,the
most efficient way is (A*B)*C. The 
number of multiplications are -
10*30*5 + 10*5*60 = 4500.
*/


//109. PALINDROMIC PARTITIONING                                             
//USING PARTITION DP (TLE)                                                    {T.C = O(N^3), S.C = O(N^2)}
class Solution{
public:
    int dp[505][505];
    bool isPalindrome(string s, int i, int j) {
        while (i < j) {
            if (s[i] != s[j]) {
                return false;
            }
            i++, j--;
        }
        return true;
    }
    int solveMem(string str, int i, int j) {
        // Base cases
        if (i >= j || isPalindrome(str, i, j)) return 0;
        
    
        if (dp[i][j] != -1) return dp[i][j];
        
        int mini = INT_MAX;
        for (int k = i; k < j; k++) {
            int temp = 1 + solveMem(str, i, k) + solveMem(str, k + 1, j);
            mini = min(mini, temp);
        }
    
        dp[i][j] = mini;  // Store the result in the memoization table
        return mini;
    }

    int palindromicPartition(string str){
        memset(dp, -1, sizeof(dp));
        int n = str.length();
        return solveMem(str, 0, n-1);                    //i = 0, j = n-1
    }
};
/*
Example 1:
Input: str = "ababbbabbababa"
Output: 3
Explaination: After 3 partitioning substrings 
are "a", "babbbab", "b", "ababa".

Example 2:
Input: str = "aaabba"
Output: 1
Explaination: The substrings after 1
partitioning are "aa" and "abba".
*/