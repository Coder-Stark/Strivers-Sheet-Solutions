#include<bits/stdc++.h>
using namespace std;

//DAY 26: DP2-----------------------------------------------------------------------------------------------------

//109. MINIMUM PATH SUM                                                {T.C = O(N^2), S.C = O(N^2)}
class Solution {
public:
    int dp[205][205];
    int solveMem(vector<vector<int>>&grid, int i , int j){
        int n = grid.size(), m = grid[0].size();
        //base case
        if(i >= n || j >= m) return INT_MAX;                  //not possible to find path
        if(i == n-1 && j == m-1) return grid[i][j];           //start == dest

        if(dp[i][j] != -1) return dp[i][j];

        int down = solveMem(grid, i+1, j);
        int right = solveMem(grid, i, j+1);

        return dp[i][j] = grid[i][j] + min(down, right);
    }
    int minPathSum(vector<vector<int>>& grid) {
        memset(dp, -1, sizeof(dp));
        return solveMem(grid, 0, 0);                 //0 = initial index
    }
};
/*
Example 1:
Input: grid = [[1,3,1],
               [1,5,1],
               [4,2,1]]
Output: 7
Explanation: Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.

Example 2:
Input: grid = [[1,2,3],
               [4,5,6]]
Output: 12
*/


//110. COIN CHANGE                                                           {T.C = O(N*AMOUNT), S.C = O(N*AMOUNT)}
class Solution {
public:
    int dp[15][10005];
    int solveMem(vector<int>&coins, int amount, int i){
        int n = coins.size();
        //base case
        if(amount == 0) return 0;
        if(i >= n || amount < 0) return INT_MAX;

        if(dp[i][amount] != -1) return dp[i][amount];

        int inclCoin = INT_MAX;
        if(amount >= coins[i]){
            int inclAns = solveMem(coins, amount-coins[i], i);   //use same coin
            if(inclAns != INT_MAX) inclCoin = inclAns+1;
        }
        int exclCoin = 0 + solveMem(coins, amount, i+1);

        return dp[i][amount] = min(inclCoin, exclCoin);
    }
    int coinChange(vector<int>& coins, int amount) {
        memset(dp, -1, sizeof(dp));
        int ans = solveMem(coins, amount, 0);              //0 = initial index
        return ans == INT_MAX ? -1 : ans;
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


//110. PARTITION EQUAL SUBSET SUM                                          {T.C = O(N*TARGET), S.C = O(N*TARGET)}
class Solution {
public:
    int dp[201][20001];                         //sum (max limit = 200x100 = 20000)
    bool solveMem(vector<int>&nums, int sum , int i){
        int n = nums.size();
        //base case
        if(sum == 0) return true;
        if(i >= n || sum < 0) return false;

        if(dp[i][sum] != -1) return dp[i][sum];

        int incl = solveMem(nums, sum-nums[i], i+1);
        int excl = solveMem(nums, sum, i+1);

        return dp[i][sum] = incl || excl;
    }
    bool canPartition(vector<int>& nums) {
        memset(dp, -1, sizeof(dp));
        int sum = 0;
        for(auto it : nums) sum += it;

        if(sum % 2 != 0) return false;                   //for odd, partition not possible
        int target = sum/2;                              //2 partition 

        return solveMem(nums, target, 0);             //0 = initial index
    }
};
/*
Example 1:
Input: nums = [1,5,11,5]
Output: true
Explanation: The array can be partitioned as [1, 5, 5] and [11].

Example 2:
Input: nums = [1,2,3,5]
Output: false
Explanation: The array cannot be partitioned into equal sum subsets.
*/


//111. MINIMUM COST TO CUT A STICK  / ROD CUTTING PROBLEM                        {T.C = O(N^2), S.C = O(N^2)}
class Solution {
public:
    int dp[105][105];                             //ON CUTS NOT LEN (SHOULD BE at least 103)
    int solve(vector<int>& cuts, int i, int j) {
        if(i >= j) return 0;                    //invalid case
        
        if(dp[i][j] != -1) return dp[i][j];
        
        int mini = INT_MAX;
        for(int k = i; k < j; k++) {          //traverse on cuts only (not whole len)
            int cost = (cuts[j]-cuts[i-1]) + solve(cuts, i, k) + solve(cuts, k+1, j);   //len of stick(j-i+1 {cuts[j]-cuts[i-1]})
            mini = min(mini, cost);
        }
        
        return dp[i][j] = mini;
        
    }
    
    int minCost(int n, vector<int>& cuts) {
        sort(cuts.begin(), cuts.end());                //required for this only
        cuts.insert(begin(cuts), 0);                   //insert 0 at beginning
        cuts.push_back(n);                             //insert n(len) at last

        memset(dp, -1, sizeof(dp));
        int m = cuts.size();
        return solve(cuts, 1, m-1);                     //partition dp (i = initial index, j = sz-1)
    }
};
/*
Example 1:
Input: n = 7, cuts = [1,3,4,5]
Output: 16
Explanation: Using cuts order = [1, 3, 4, 5] as in the input leads to the following scenario:
The first cut is done to a rod of length 7 so the cost is 7. The second cut is done to a rod of length 6 (i.e. the second part of the first cut), the third is done to a rod of length 4 and the last cut is to a rod of length 3. The total cost is 7 + 6 + 4 + 3 = 20.
Rearranging the cuts to be [3, 5, 1, 4] for example will lead to a scenario with total cost = 16 (as shown in the example photo 7 + 4 + 3 + 2 = 16).

Example 2:
Input: n = 9, cuts = [5,6,1,4,2]
Output: 22
Explanation: If you try the given cuts ordering the cost will be 25.
There are much ordering with total cost <= 25, for example, the order [4, 6, 5, 2, 1] has total cost = 22 which is the minimum possible.
*/


//112. EGG DROPPING PUZZLE                                             {T.C = O(E*F^2), S.C = O(E*F)}
class Solution{
public:
    int dp[205][205];
    int solveMem(int e, int f ){
        //base case
        if(f == 0 || f == 1) return f;
        if(e == 1) return f;
    
        if(dp[e][f] != -1) return dp[e][f];
        
        int mini = INT_MAX;
        for(int i = 1 ; i <= f ; i++){
            int temp = 1 + max(solveMem(e-1, i-1), solveMem(e, f-i)); //egg break, not break
            mini = min(mini, temp);
        }
        
        return dp[e][f] = mini;
    }
    int eggDrop(int e, int f) {
        memset(dp, -1, sizeof(dp));
        return solveMem(e, f);
    }
};
/*
Example 1:
Input:
N = 1, K = 2
Output: 2
Explanation: 
1. Drop the egg from floor 1. If it 
   breaks, we know that f = 0.
2. Otherwise, drop the egg from floor 2.
   If it breaks, we know that f = 1.
3. If it does not break, then we know f = 2.
4. Hence, we need at minimum 2 moves to
   determine with certainty what the value of f is.

Example 2:
Input:
N = 2, K = 10
Output: 4
*/


//113. WORD BREAK                                                           {T.C = O(N^2), S.C = O(N)}
class Solution {
public:
    int dp[305];
    bool solveMem(string &s, unordered_set<string>&st, int i){
        int n = s.length();
        //base case
        if(i >= n) return true;

        if(dp[i] != -1) return dp[i];

        string temp = "";
        for(int j = i ; j < n; j++){               //j = i not 0
            temp += s[j];
            if(st.count(temp)){
                if(solveMem(s, st, j+1)) return dp[i] = true;   //CHECK Further as well
            }
        }
        return dp[i] = false;                           //not valid found at last
    }
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string>st(wordDict.begin(), wordDict.end());
        memset(dp, -1, sizeof(dp));
        return solveMem(s, st, 0);                  //0 = initial index
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


//114. PALINDROMIC PARTIONING                                              {T.C = O(N^2), S.C = O(N)}
class Solution{
public:
    int dp[505];
    bool isPalindrome(string &s, int i, int j){
        while(i < j){
            if(s[i] != s[j]) return false;
            i++, j--;
        }
        return true;
    }
    int solveMem(string &s, int i){
        int n = s.length();
        if(i >= n) return 0;
        int minCuts = INT_MAX;
        
        if(dp[i] != -1) return dp[i];
        
        for(int j = i ; j < n ; j++){
            if(isPalindrome(s, i, j)){
                int cuts = 1 + solveMem(s, j+1);
                minCuts = min(minCuts, cuts);
            }
        }
        
        return dp[i] = minCuts;
    }
    int palindromicPartition(string str){
        memset(dp, -1, sizeof(dp));
        return solveMem(str, 0)-1;                 //0 = initial index , -1 for last index partition
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


//115. JOB SCHEDULING PROBLEM                                              {T.C = O(N^2), S.C = O(N)}
class Solution 
{
    public:
    vector<int> JobScheduling(Job arr[], int n) 
    { 
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
            
            for(int j = currDead ; j > 0 ; j--){  //put element reverse (betwen space may accumulate another)
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