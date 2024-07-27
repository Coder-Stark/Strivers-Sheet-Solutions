//DYNAMIC PROGRAMMING (DP)

#include<bits/stdc++.h>
using namespace std;


//INTRODUCTION TO DP-----------------------------------------------------------------------------------
//345. INTRODUCTION TO DP                                {T.C = O(N), S.C = O(N)}
//TOPDOWN(USE DP != -1) BOTTOM UP (USE FOR LOOP)
class Solution {
  public:
    int mod = 1e9+7;
    int dp[10001];
    long long solveMemTop(int n){
        //base case
        if(n == 0 || n == 1) return n;
        
        if(dp[n] != -1) return dp[n];
        
        return dp[n] = (solveMemTop(n-1) + solveMemTop(n-2) ) % mod;
        
    }
    long long int topDown(int n) {
        memset(dp, -1, sizeof(dp));
        return solveMemTop(n);                               //0 = initial index
    }
    
    long long solveMemBot(int n){
        //base case
        if((n == 0) || (n == 1)) return n;
        
        dp[0] = 0, dp[1] = 1;
        
        for(int i = 2 ; i <= n ; i++){
            dp[i] = ( dp[i-1] + dp[i-2]) % mod;
        }
        
        return dp[n];
    }
    long long int bottomUp(int n) {
        memset(dp, -1, sizeof(dp));
        return solveMemBot(n);
    }
};
/*
Example 1:
Input:
n = 5
Output: 5
Explanation: 0,1,1,2,3,5 as we can see 5th number is 5.

Example 2:
Input:
n = 6
Output: 8
Explanation: 0,1,1,2,3,5,8 as we can see 6th number is 8.
*/


//1D DP------------------------------------------------------------------------------------------------
//346. CLIMBING STAIRS                                     {T.C = O(N), S.C = O(N)}
//WE CAN CHOOSE EITHER 1 OR 2 STEPS SO ADD THERE RECURSIVE CALL.
class Solution {
public:
    int dp[46];
    int solveMem(int n){
        //base case
        if(n <= 1) return 1;                                      //at zero level 1 step is count

        if(dp[n] != -1) return dp[n];

        return dp[n] = solveMem(n-1) + solveMem(n-2);              //1 or 2 steps
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


//347. GEEK JUMP                                             {T.C = O(N), S.C = O(N)}
//HANDLE BASECASE(START == N : 0 , START == N-1 (RETURN HEIGHT DIFFERNCE (LAST & SECOND LAST)))
//WITH EVERY RECURSIVE CALL PASS ABS(HEIGHT DIFF), FINALLY RETURN MIN JUMP ENERGY.
class Solution {
  public:
    int dp[100001];
    int solveMem(vector<int>&height, int i, int n){
        //base case
        if(i == n) return 0;                                   //last position (no jump require)
        if(i == n-1) return abs(height[n]-height[n-1]);        //second last position
        
        if(dp[i] != -1) return dp[i];
        
        int jump1Energy = solveMem(height, i+1, n) + abs(height[i]-height[i+1]);
        int jump2Energy = solveMem(height, i+2, n) + abs(height[i]-height[i+2]);
        
        return dp[i] = min(jump1Energy, jump2Energy);
    }
    int minimumEnergy(vector<int>& height, int n) {
        memset(dp, -1, sizeof(dp));
        return solveMem(height, 0, n-1);            //reach n-1 (not n)
    }
};
/*
Example:
Input:
n = 4
height = {10 20 30 10}
Output:
20
Explanation:
Geek jump from 1st to 2nd stair(|20-10| = 10 energy lost).
Then a jump from the 2nd to the last stair(|10-20| = 10 energy lost).
so, total energy lost is 20 which is the minimum.
*/


//348. MINIMAL COST                                             {T.C = O(N*K), S.C = O(N)}
//TAKE FOR LOOP(1 TO K) INSIDE CHECK I+J < N , MAKE RECURSIVE CALL(JUMPCOST) STORE MINIMUM VAL.
class Solution {
  public:
    int dp[1001];
    int solveMem(vector<int>&height, int n, int k, int i){
        //base case
        if(i == n-1) return 0;
        
        if(dp[i] != -1) return dp[i];
        
        int minCost = INT_MAX;
        for(int j = 1 ; j <= k ; j++){
            if(i+j < n){
                int jumpCost = solveMem(height, n, k, i+j) + abs(height[i]-height[i+j]);
                minCost = min(minCost, jumpCost);
            }
        }
        return dp[i] = minCost;
    }
    int minimizeCost(vector<int>& height, int n, int k) {
        memset(dp, -1, sizeof(dp));
        return solveMem(height, n, k, 0);
    }
};
/*
Examples :
Input: n = 5, k = 3 heights = {10, 30, 40, 50, 20}
Output: 30
Explanation: Geek will follow the path 1->2->5, the total cost would be | 10-30| + |30-20| = 30, which is minimum

Input: n = 3, k = 1 heights = {10,20,10}
Output: 20
Explanation: Geek will follow the path 1->2->3, the total cost would be |10 - 20| + |20 - 10| = 20.
*/


//349. HOUSE ROBBER I                                         {T.C = O(N), S.C = O(N)}
//SIMPE INCL & EXCL, INCL(I+2{ADJACENT SKIP}) , EXCL(I+1{NEXT ELEMENT}), FINALLY RETURN MAX OF IT.
class Solution {
public:
    int dp[101];
    int solveMem(vector<int>&nums, int i){
        int n = nums.size();
        //base case
        if(i >= n) return 0;

        if(dp[i] != -1) return dp[i];

        int incl = nums[i] + solveMem(nums, i+2);            //adjacent skip
        int excl = 0       + solveMem(nums, i+1); 

        return dp[i] = max(incl, excl);
    }
    int rob(vector<int>& nums) {
        memset(dp, -1, sizeof(dp));
        return solveMem(nums, 0);                  //0 - initial index
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


//350. HOUSE ROBBER II                                         {T.C = O(N), S.C = O(N)}
//FOR CIRCULAR ,BREAK NUMS INTO TWO (0 TO N-1) & (1 TO N) THEN APPLY SIMPLE ABOVE
//SIMPE INCL & EXCL, INCL(I+2{ADJACENT SKIP}) , EXCL(I+1{NEXT ELEMENT}), FINALLY RETURN MAX OF IT.
class Solution {
public:
    int dp1[101], dp2[101];
    int solveMem(vector<int>&nums, int i, int n, int*dp){          //pass dp as pointer
        //base case
        if(i >= n) return 0;

        if(dp[i] != -1) return dp[i];

        int incl = nums[i] + solveMem(nums, i+2, n, dp);             //adjacent skip
        int excl = 0       + solveMem(nums, i+1, n, dp);

        return dp[i] = max(incl, excl);
    }
    int rob(vector<int>& nums) {
        memset(dp1, -1, sizeof(dp1));
        memset(dp2, -1, sizeof(dp2));
        
        int n = nums.size();
        if(n == 1) return nums[0];
        if(n == 2) return max(nums[0], nums[1]);

        int inclZeroIdx = solveMem(nums, 0, n-1, dp1);
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


//2D/3D DP AND DP ON GRIDS---------------------------------------------------------------------------
//351. GEEK'S TRAINING
//BRUTE FOR APPROACH                                                {T.C = O(N), S.C = O(1)}
//STORE FIRST ROW'S ELEMENT , THEN ITERATE ON VECTOR AND FIND MAX OF ALL ROW
class Solution {
  public:
    int maximumPoints(vector<vector<int>>& points, int n) {
        int a=points[0][0], b=points[0][1], c=points[0][2];
        
        for(int i=1; i<n; i++){                 //i = 0 already sets above
            int x = a, y = b, z = c;
            a = points[i][0] + max(y, z);
            b = points[i][1] + max(x, z);
            c = points[i][2] + max(x, y);
        }
        return max({a, b, c});
   }
};
/*
Example:
Input:
n = 3
points = [[1,2,5],[3,1,1],[3,3,3]]
Output:
11
Explanation:
Geek will learn a new move and earn 5 point then on second
day he will do running and earn 3 point and on third day
he will do fighting and earn 3 points so, maximum point is 11.

Example:
Input:
n = 3
points = [[1,2,5],[3,1,1],[3,2,3]]
Output:
11
Explanation:
Geek will learn a new move and earn 5 point then on second
day he will do running and earn 3 point and on third day
he will do running and earn 3 points so, maximum point is 11.
*/


//352. UNIQUE PATHS                                         {T.C = O(N*M), S.C = O(N*M)}
//HANDLE BOUNDARY CASES, IF(START = DEST : 1(WAY)) , RECURSIVE CALL(DOWN , RIGHT), STORE BOTH IN 2D DP.
class Solution {
public:
    int dp[101][101];
    int solveMem(int n, int m, int i, int j){
        //base case
        if(i == n || j == m) return 0;
        if(i == n-1 && j == m-1) return 1;             //start = dest (1 ways)

        if(dp[i][j] != -1) return dp[i][j];

        int down  = solveMem(n, m, i+1, j);
        int right = solveMem(n, m, i, j+1);

        return dp[i][j] = down + right;
    }
    int uniquePaths(int m, int n) {
        memset(dp, -1, sizeof(dp));
        return solveMem(n, m, 0, 0);                   //0, 0 = initial indexes
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


//353. UNIQUE PATHS II                                         {T.C = O(N*M), S.C = O(N*M)}
//HANDLE BOUNDARY CASES, IF(START = DEST : 1(WAY)) , RECURSIVE CALL(DOWN , RIGHT), STORE BOTH IN 2D DP.
class Solution {
public:
    int dp[101][101];
    int solveMem(vector<vector<int>>&matrix, int n, int m, int i, int j){
        //base case
        if(i >= n || j >= m || matrix[i][j] == 1) return 0;
        if(i == n-1 && j == m-1) return 1;               //start = dest

        if(dp[i][j] != -1) return dp[i][j];

        int down  = solveMem(matrix, n, m, i+1, j);
        int right = solveMem(matrix, n, m, i, j+1);

        return dp[i][j] = down+right;
    }
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        memset(dp, -1, sizeof(dp));
        int n = obstacleGrid.size(), m = obstacleGrid[0].size();
        return solveMem(obstacleGrid, n, m, 0, 0);                          //0, 0 = initial index
    }
};
/*Example 1:
Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
Output: 2
Explanation: There is one obstacle in the middle of the 3x3 grid above.
There are two ways to reach the bottom-right corner:
1. Right -> Right -> Down -> Down
2. Down -> Down -> Right -> Right

Example 2:
Input: obstacleGrid = [[0,1],[0,0]]
Output: 1
*/


//354. MINIMUM PATH SUM                                         {T.C = O(N*M), S.C = O(N*M)}
//SAME AS ABOVE (JUST WE HAVE TO FIND MIN PATH SUM ) , MAKE RECURSIVE CALL THEN FIND MIN AND ADD TO ELEMENT.
class Solution {
public:
    int dp[201][201];
    int solveMem(vector<vector<int>>&grid, int i, int j){
        int n = grid.size(), m = grid[0].size();
        //base case
        if(i >= n || j >= m) return INT_MAX;
        if(i == n-1 && j == m-1) return grid[i][j];             //start = dest

        if(dp[i][j] != -1) return dp[i][j];

        int down  = solveMem(grid, i+1, j);             //grid[i][j] + solveMem {gives overflow}
        int right = solveMem(grid, i, j+1);

        return dp[i][j] = grid[i][j] + min(down, right);
    }
    int minPathSum(vector<vector<int>>& grid) {
        memset(dp, -1, sizeof(dp));
        return solveMem(grid, 0, 0);                 //0,0 = initial index
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


//355. TRIANGLE                                             {T.C = O(N*M), S.C = O(N*M)}
//RECURSIVE CALL (DOWN{I+1}, DIAGONALLY(I+1, J+1)), STORE ITS MIN AND CURR.
class Solution {
public:
    int dp[201][201];
    int solveMem(vector<vector<int>>&triangle, int i, int j){
        int n = triangle.size();
        //base case
        if(i >= n) return 0;

        if(dp[i][j] != -1) return dp[i][j];

        int down = solveMem(triangle, i+1, j);      
        int diag = solveMem(triangle, i+1, j+1);    

        return dp[i][j] = triangle[i][j] + min(down, diag);
    }
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        memset(dp, -1, sizeof(dp));
        return solveMem(triangle, 0, 0);                      //0,0 = initial index(row, col)
    }
};
/*
Example 1:
Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
Output: 11
Explanation: The triangle looks like:
   2
  3 4
 6 5 7
4 1 8 3
The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined above).

Example 2:
Input: triangle = [[-10]]
Output: -10
*/


//356a. MINIMUM FALLING PATH SUM                                         {T.C = O(N^2), S.C = O(N^2)}            
//GIVES TLE (ON LEETCODE)
//TAKE FOR LOOP (ROW FIX, COL VAR), THEN CALL SOLVEMEM (DOWN, DOWNL, DOWR), FIND MIN PATH SUM(HANDLE BOUDARY CASES)
class Solution {
public:
    int dp[101][101];
    int solveMem(vector<vector<int>>&matrix, int i, int j){
        int n = matrix.size();                    //n == m
        //base case
        if(i >= n || j >= n || i < 0 || j < 0) return INT_MAX;    //out of boundary

        if(i == n-1) return matrix[i][j];            //reached to last row (return )
        
        if(dp[i][j] != -1) return dp[i][j];

        int down  = solveMem(matrix, i+1, j);
        int downL = solveMem(matrix, i+1, j-1);
        int downR = solveMem(matrix, i+1, j+1);

        return dp[i][j] = matrix[i][j] + min({down, downL, downR});
    }
    int minFallingPathSum(vector<vector<int>>& matrix) {
        memset(dp, -1, sizeof(dp));
        int n = matrix.size();
        int ans = INT_MAX;
        for(int j = 0 ; j < n ; j++){
            ans = min(ans, solveMem(matrix, 0, j));                   //i, 0 = starts from top row any col
        }
        return ans;
    }
};
/*
*/

//356b. MAXIMUM PATH SUM IN A MATRIX / MAXIMUM FALLING PATH SUM      {T.C = O(N^2), S.C = O(N^2)}            
//SAME ABOVE LOGIC JUST MIN->MAX
class Solution{
public:
    int dp[501][501];
    int solveMem(vector<vector<int>>&matrix, int i, int j){
        int n = matrix.size();
        //base case
        if(i >= n || i < 0 || j >= n || j < 0) return INT_MIN;  //boundary case
        
        if(i == n-1) return matrix[i][j];                    //reached to last col
        
        if(dp[i][j] != -1) return dp[i][j];
        
        int down  = solveMem(matrix, i+1, j);
        int downR = solveMem(matrix, i+1, j+1);
        int downL = solveMem(matrix, i+1, j-1);
        
        return dp[i][j] = matrix[i][j] + max({down, downR, downL});
    }
    int maximumPath(int N, vector<vector<int>> Matrix){      
        memset(dp, -1, sizeof(dp));
        int ans = INT_MIN;
        for(int j = 0 ; j < N ; j++){          //starting row same , col change
            ans = max(ans, solveMem(Matrix, 0, j));             //0 = first row, j = col
        }
        return ans;
    }
};
/*
Input: n = 2, mat = [[348, 391],[618, 193]]
Output: 1009
Explaination: The best path is 391 -> 618. It gives the sum = 1009.

Input: n = 2, mat = [[2, 2],[2, 2]]
Output: 4
Explaination: No matter which path is chosen, the output is 4.
*/


//357a. CHERRY PICKUP II                                            {T.C = O(N*M*M), S.C = O(N*M*M)}
//3D DP , ALL SAME LIKE ABOVE
class Solution {
public:
    int dp[71][71][71];                             //row, col1, col2
    int solveMem(vector<vector<int>>& grid, int row, int col1, int col2) {
        int n = grid.size(), m = grid[0].size();
        // Base case
        if (row >= n || col1 < 0 || col1 >= m || col2 < 0 || col2 >= m) return 0;

        if (dp[row][col1][col2] != -1) return dp[row][col1][col2];

        int cherry = grid[row][col1];                // Current cell value
        if (col1 != col2) cherry += grid[row][col2]; // same cell count only once 

        // Recursive case: Try all combinations of movements
        int ans = 0;
        for (int i = -1; i <= 1; ++i) {            // col1 has 3 choices: -1, 0, 1
            for (int j = -1; j <= 1; ++j) {        // col2 has 3 choices: -1, 0, 1
                int newRow = row + 1;
                int newCol1 = col1 + i;
                int newCol2 = col2 + j;

                if (newCol1 >= 0 && newCol1 < m && newCol2 >= 0 && newCol2 < m) {
                    ans = max(ans, solveMem(grid, newRow, newCol1, newCol2));
                }
            }
        }

        return dp[row][col1][col2] = cherry + ans;
    }

    int cherryPickup(vector<vector<int>>& grid) {
        memset(dp, -1, sizeof(dp));
        int n = grid.size(), m = grid[0].size();
        return solveMem(grid, 0, 0, m - 1); // Start at the first row, col1 at 0, col2 at m-1
    }
};
/*
Example 1:
Input: grid = [[3,1,1],
               [2,5,1],
               [1,5,5],
               [2,1,1]]
Output: 24
Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
Cherries taken by Robot #1, (3 + 2 + 5 + 2) = 12.
Cherries taken by Robot #2, (1 + 5 + 5 + 1) = 12.
Total of cherries: 12 + 12 = 24.

Example 2:
Input: grid = [[1,0,0,0,0,0,1],
               [2,0,0,0,0,3,0],
               [2,0,9,0,0,0,0],
               [0,3,0,5,4,0,0],
               [1,0,2,3,0,0,6]]
Output: 28
Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
Cherries taken by Robot #1, (1 + 9 + 5 + 2) = 17.
Cherries taken by Robot #2, (1 + 3 + 4 + 3) = 11.
Total of cherries: 17 + 11 = 28.
*/

//357b. CHOCOLATE PICKUPS                                                  {T.C = O(N*M*M), S.C = O(N*M*M)}
//SAME AS ABOVE
class Solution {
public:
    int dp[71][71][71];
    
    int solveMem(vector<vector<int>>& grid, int row, int col1, int col2) {
        int n = grid.size(), m = grid[0].size();
        // base case
        if (row >= n) return 0;
        
        if (dp[row][col1][col2] != -1) return dp[row][col1][col2];
        
        int chocolate = grid[row][col1]; // current cell
        if (col1 != col2) chocolate += grid[row][col2];
        
        int pathAns = 0;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int newR = row + 1;
                int newC1 = col1 + i;
                int newC2 = col2 + j;
                
                if (newC1 >= 0 && newC1 < m && newC2 >= 0 && newC2 < m) {
                    pathAns = max(pathAns, solveMem(grid, newR, newC1, newC2));
                }
            }
        }
        return dp[row][col1][col2] = pathAns + chocolate;
    }

    int solve(int n, int m, vector<vector<int>>& grid) {
        memset(dp, -1, sizeof(dp));
        return solveMem(grid, 0, 0, m - 1); // 0 = row, 0 = col1, m - 1 = col2
    }
};
/*
Input:
n = 4, m = 3
grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
Output:
24
Explanation:
Path of robot #1 and #2 are described in color green and blue respectively. Chocolates taken by Robot #1, (3 + 2 + 5 + 2) = 12. Chocolates taken by Robot #2, (1 + 5 + 5 + 1) = 12. Total of Chocolates: 12 + 12 = 24.
Expected Time Complexity: O(n * m * m)
Expected Space Complexity: O(n * m * m)
*/

//DP ON SUBSEQUENCES---------------------------------------------------------------------------
//358. SUBSET SUM PROBLEM                                    {T.C = O(N*SUM), S.C = O(N*SUM)}
//SIMPLE TAKE AND NON TAKE DP, INCLUDE SUM < 0 BASE CASE , ATLAST OR OF TAKE , NON TAKE.
class Solution{   
public:
    int dp[101][10001];
    bool solveMem(vector<int>&arr, int sum , int i){          //sum == target
        int n = arr.size();
        //base case
        if(sum == 0) return true;                         //not pick case
        if(i >= n || sum < 0) return false;               //sum < 0 for incl (sum - arr[i])
        
        if(dp[i][sum] != -1) return dp[i][sum];
        
        bool incl = solveMem(arr, sum-arr[i], i+1);
        bool excl = solveMem(arr, sum, i+1);
        
        return dp[i][sum] = incl || excl;
    }
    bool isSubsetSum(vector<int>arr, int sum){
        memset(dp, -1, sizeof(dp));
        return solveMem(arr, sum, 0);                    //0 = initial index
    }
};
/*
Example 1:
Input:
N = 6
arr[] = {3, 34, 4, 12, 5, 2}
sum = 9
Output: 1 
Explanation: Here there exists a subset with
sum = 9, 4+3+2 = 9.

Example 2:
Input:
N = 6
arr[] = {3, 34, 4, 12, 5, 2}
sum = 30
Output: 0 
Explanation: There is no subset with sum 30.
*/


//359. PARTITION EQUAL SUBSET SUM                               {T.C = O(N*SUM), S.C = O(N*SUM)}
//FIRST FIND TOTAL SUM THEN DIVIDE IT INTO 2 (TARGET{SINGLE}), ELSE ABOVE SAME CODE
class Solution {
public:
    int dp[201][20001];                         //sum (max limit = 200x100 = 20000)
    bool solveMem(vector<int>&nums, int sum , int i){            //sum == target
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

        if(sum % 2 != 0) return false;                   //partition not possible
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


//360. PARTITION ARRAY INTO TWO ARRAYS TO MINIMIZE THE SUM DIFFERENCE



//361. PERFECT SUM PROBLEM / COUNT SUBSET WITH SUM K  (FINDING WAYS)   {T.C = O(N*M), S.C = N*M}
//SIMILAR TO ABOVE JUST (BOOL (OR) => INCL + EXCL(WAYS)), BASE CASE CHANGE(I == N && SUM == 0){TRAVERSAL ALL}
class Solution{
	public:
	int mod = 1e9+7;
	vector<vector<int>>dp;
 	//int dp[1000001][1000001];                      //size exceeds
	int solveMem(int arr[], int n ,int sum, int i){
	   // int n = sizeof(arr)/sizeof(arr[0]);
	    //base case
	    if(i == n && sum == 0) return 1;                      //traverse all still 0 then 1
	    if(i >= n || sum < 0) return 0;                        //only positive sum is allowed
	    
	    if(dp[i][sum] != -1) return dp[i][sum];
	    
	    int incl = solveMem(arr, n, sum-arr[i], i+1);
	    int excl = solveMem(arr, n, sum, i+1);
	    
	    return dp[i][sum] = (incl % mod + excl % mod) % mod;
	}
	int perfectSum(int arr[], int n, int sum){
        // memset(dp, -1, sizeof(dp));
        dp = vector<vector<int>>(n, vector<int>(sum+1, -1));
        return solveMem(arr, n, sum, 0);                    //0 = initial index
	}
};
/*
Input: 
n = 6, arr = [5, 2, 3, 10, 6, 8], sum = 10
Output: 
3
Explanation: 
{5, 2, 3}, {2, 8}, {10} are possible subsets.

Input: 
n = 5, arr = [2, 5, 1, 4, 3], sum = 10
Output: 
3
Explanation: 
{2, 1, 4, 3}, {5, 1, 4}, {2, 5, 3} are possible subsets.
*/


//362. PARTITION WITH GIVEN DIFFERENCE                        {T.C = O(N*SUM), S.C = O(N*M)}
//SIMILAR TO ABOVE, JUST TARGET = SUM+D/2(INSTEAD OF SUM/2)
class Solution {
  public:
    int mod = 1e9+7;
    // int dp[500][25001];                         //max limit 10000
    int solveMem(vector<int>&arr, int sum, int i, vector<vector<int>>&dp){
	    int n = arr.size();
	    //base case
	    if(i == n && sum == 0) return 1;                      //traverse all still 0 then 1
	    if(i >= n || sum < 0) return 0;                        //only positive sum is allowed
	    
	    if(dp[i][sum] != -1) return dp[i][sum];
	    
	    int incl = solveMem(arr, sum-arr[i], i+1, dp);
	    int excl = solveMem(arr, sum, i+1, dp);
	    
	    return dp[i][sum] = (incl % mod + excl % mod) % mod;
	}
    int countPartitions(int n, int d, vector<int>& arr){
        int sum = 0;
        for(auto it : arr) sum += it;
        
        if((sum + d) % 2 != 0) return 0;              //odd cant be divide in partition
        
        int targetSum = (sum + d)/2;
	    vector<vector<int>>dp(n+1, vector<int>(targetSum+1, -1));
        return solveMem(arr, targetSum, 0, dp);
    }
};
/*
Example 1:
Input:
n = 4
d = 3
arr[] =  { 5, 2, 6, 4}
Output: 1
Explanation:
There is only one possible partition of this array. Partition : {6, 4}, {5, 2}. The subset difference between subset sum is: (6 + 4) - (5 + 2) = 3.

Example 2:
Input:
n = 4
d = 0 
arr[] = {1, 1, 1, 1} 
Output: 6 
Explanation:
we can choose two 1's from indices {0,1}, {0,2}, {0,3}, {1,2}, {1,3}, {2,3} and put them in S1 and remaning two 1's in S2.
Thus there are total 6 ways for partition the array arr. 
*/


//363a. ASSIGN COOKIES                                           
//SORTING & TWO POINTERS                                         {T.C = O(N*LOGN), S.C = O(1)}
//GREEDY APPROACH (SORT BOTH VECTOR), USE TWO POINTER(BOTH START), REQ <= HAVE COUNT++
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


//363b. 01 KNAPSACK PROBLEM                                         {T.C = O(N*W), S.C = O(N*W)}
//SIMPLE TAKE AND NOT TAKE PROBLM, WITH RECURSIVE CALL ADD VAL[I].
class Solution{
public:
    int dp[1001][1001];                           //N, W
    int solveMem(int wt[], int val[], int totalWt, int i, int n){
        // int n = sizeof(wt)/sizeof(wt[0]);           //not works (in arr required refernce n)
        //base case
        if(i >= n) return 0;                           //out of range
        
        if(dp[i][totalWt] != -1) return dp[i][totalWt];
        
        int incl = 0;
        if(totalWt >= wt[i]){
            incl = val[i] + solveMem(wt, val, totalWt-wt[i], i+1, n);  //not take more then once
        }
        int excl = 0 + solveMem(wt, val, totalWt, i+1, n);
        
        return dp[i][totalWt] = max(incl, excl);
    }
    int knapSack(int W, int wt[], int val[], int n) { 
       memset(dp, -1, sizeof(dp));
       return solveMem(wt, val, W, 0, n);              //0 = initial index
    }
};
/*
Example 1:
Input:
N = 3
W = 4
values[] = {1,2,3}
weight[] = {4,5,1}
Output: 3
Explanation: Choose the last item that weighs 1 unit and holds a value of 3. 

Example 2:
Input:
N = 3
W = 3
values[] = {1,2,3}
weight[] = {4,5,6}
Output: 0
Explanation: Every item has a weight exceeding the knapsack's capacity (3).
*/


//364. COIN CHANGE (FINDING MIN COINS REQ)                   {T.C = O(N*AMOUNT), S.C = O(N*AMOUNT)}
//SIMILAR TO ABOVE, HANDLE BASE CASE (IF SUM < 0) RETURN MAX, THEN HANDLE INCL CASE ONLY VALID CASE INCL.
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


//365. TARGET SUM                                                   {T.C = O(N*SUM), S.C = O(N*M)}
//JUST WRITE COUNTPARTITION PROBLEM (BOTTOM UP {TOP DOWN NOT WORKING})
class Solution {
public:
    int solveMem(int n, int target, vector<int>& arr, vector<vector<int>>& dp) {
        // Base cases
        if (n == 0) {
            if (target == 0 && arr[0] == 0) return 2; // Two ways to partition: include or exclude the element
            if (target == 0 || target == arr[0]) return 1; // One way to partition: include or exclude the element
            return 0; // No way to partition
        }

        if (dp[n][target] != -1)
            return dp[n][target];

        int excl = solveMem(n - 1, target, arr, dp);
        int incl = 0;
        if (arr[n] <= target){
            incl = solveMem(n - 1, target - arr[n], arr, dp);
        }
        // Store the sum of ways in the DP array and return it
        return dp[n][target] = (excl + incl);
    }
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        int totSum = 0;
        for(auto it : nums) totSum += it;

        // Checking for edge cases
        if (totSum - target < 0) return 0; // Not possible to achieve the target sum
        if ((totSum - target) % 2 == 1) return 0; // The difference between the total sum and target sum must be even

        int s2 = (totSum - target) / 2; // Calculate the required sum for each subset

        vector<vector<int>> dp(n, vector<int>(s2 + 1, -1)); // Initialize DP table
        return solveMem(n - 1, s2, nums, dp); // Call the helper function

    }
};
/*
Example 1:
Input: nums = [1,1,1,1,1], target = 3
Output: 5
Explanation: There are 5 ways to assign symbols to make the sum of nums be target 3.
-1 + 1 + 1 + 1 + 1 = 3
+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3
+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3

Example 2:
Input: nums = [1], target = 1
Output: 1
*/


//366. COIN CHANGE II (FINING TOTAL WAYS)                    {T.C = (N*AMOUNT), S.C = O(N*AMOUNT)}
//SIMILAR TO COIN CHANGE 1, JUST FINDING TOTAL WAYS {INCL + EXCL} (NOT MIN COINS { MIN(INCL, EXCL)})
class Solution {
public:
    int solveMem(vector<int>&coins, int amount, int i, vector<vector<int>>&dp){
        int n = coins.size();
        //base case
        if(amount == 0) return 1;
        if(i >= n || amount < 0) return 0;                  //out of bound or target < 0 return 0

        if(dp[i][amount] != -1) return dp[i][amount];

        int incl = 0;
        if(amount >= coins[i]){
            incl = solveMem(coins, amount-coins[i], i, dp);  //infinit supply (i not change)
        }
        int excl = solveMem(coins, amount, i+1, dp);

        return dp[i][amount] = incl + excl;                          //total ways
    }
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        vector<vector<int>>dp(n+1, vector<int>(amount+1, -1));
        return solveMem(coins, amount, 0, dp);                //0 = initial index
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


//367. KNAPSACK WITH DUPLICAT ITEM / UNBOUNDED KNAPSACK           {T.C = O(N*W), S.C = O(N*W)}
//SIMILAR TO 01 KNAPSACK, JUST AT INCL USE (I {INSTEAD OF I+1}){WE CAN CHOOSE SAME ELEMENT ANY NUMBER OF TIME}
class Solution{
public:
    int dp[1001][1001];
    int solveMem(int wt[], int val[], int totalWt, int i, int n){
        //base case
        if(i >= n) return 0;
        
        if(dp[i][totalWt] != -1) return dp[i][totalWt];
        
        int incl = 0;
        if(totalWt >= wt[i]){
            incl = val[i] + solveMem(wt, val, totalWt-wt[i], i, n);        // we can choose wt many time
        }
        int excl = 0 + solveMem(wt, val, totalWt, i+1, n);
        
        return dp[i][totalWt] = max(incl, excl);
    }
    int knapSack(int N, int W, int val[], int wt[]){
        memset(dp, -1, sizeof(dp));
        return solveMem(wt, val, W, 0, N);              //0 = initial index
    }
};
/*
Example 1:
Input: 
N = 2
W = 3
val = {1, 1}
wt = {2, 1}
Output: 
3
Explanation: 
1.Pick the 2nd element thrice.
2.Total profit = 1 + 1 + 1 = 3. Also the total weight = 1 + 1 + 1  = 3 which is <= 3.

Example 2:
Input: 
N = 4
W = 8
val[] = {6, 1, 7, 7}
wt[] = {1, 3, 4, 5}
Output: 
48
Explanation: 
The optimal choice is to pick the 1st element 8 times.
*/


//368. ROD CUTTING PROBLEM / VARIATION OF UNBOUNDED KNAPSACK        {T.C = O(N^2), S.C = O(N^2)}
//MEMOIZATION TOP DOWN (I TO N)
//SIMILAR TO ABOVE , REVERSE VAL AND WT LIKE ,IN INCL {LEN(VAL) INSTEAD OF PRICE(WT)} BECAUSE TARGET IS TO FIND MAX PRICE(WT)
class Solution{
  public:
    int dp[1001][1001];
    int solveMem(int price[], vector<int>len, int i, int totalLen){
        int n = len.size();
        //base case
        if(i >= n || totalLen == 0) return 0;                           //exceeds total len(out of bound)
        
        if(dp[i][totalLen] != -1) return dp[i][totalLen];
        
        int incl = 0;
        if(totalLen >= len[i]){                                        //in knapsack (w >= wt[i]){reverse in this}
            incl = price[i] + solveMem(price, len, i, totalLen-len[i]);     //i (unbounded knapsack){infinite supply}
        }
        int excl = 0 + solveMem(price, len, i+1, totalLen);
        
        return dp[i][totalLen] = max(incl, excl);
    }
    int cutRod(int price[], int n) {        
        vector<int>len(n);
        for(int i = 0 ; i < n ; i++){
            len[i] = i+1;
        }
        memset(dp, -1, sizeof(dp));
        return solveMem(price, len, 0, n);      //price[] == wt[], len[] = val[], n = W
    }
};


//USING TOP DOWN (N TO I)
class Solution{
  public:
    int dp[1002][1002];
    int solveMem(int price[], vector<int>&len, int n, int totalLen){
        //base case
        if(n == 0 || totalLen == 0) return 0;                           //exceeds total len(out of bound)
        
        if(dp[n][totalLen] != -1) return dp[n][totalLen];
        
        int incl = 0;
        if(totalLen >= len[n-1]){                                        //in knapsack (w >= wt[i]){reverse in this}
            incl = price[n-1] + solveMem(price, len, n, totalLen-len[n-1]);     //i (unbounded knapsack){infinite supply}
        }
        int excl = 0 + solveMem(price, len, n-1, totalLen);
        
        return dp[n][totalLen] = max(incl, excl);
    }
    int cutRod(int price[], int n) {        
        vector<int>len(n);
        for(int i = 0 ; i < n ; i++){
            len[i] = i+1;
        }
        memset(dp, -1, sizeof(dp));
        return solveMem(price, len, n, n);      //price[] == wt[], len[] = val[], n = W
    }
};
/*
Example 1:
Input:
N = 8
Price[] = {1, 5, 8, 9, 10, 17, 17, 20}
Output:
22
Explanation:
The maximum obtainable value is 22 by 
cutting in two pieces of lengths 2 and 
6, i.e., 5+17=22.

Example 2:
Input:
N=8
Price[] = {3, 5, 8, 9, 10, 17, 17, 20}
Output: 
24
Explanation: 
The maximum obtainable value is 
24 by cutting the rod into 8 pieces 
of length 1, i.e, 8*price[1]= 8*3 = 24. 
*/


//DP ON STRINGS-------------------------------------------------------------------------------
//369. LONGEST COMMON SUBSEQUENCES                           {T.C = O(N*M), S.C = O(N*M)}
//TOP DOWN (MEMOIZATION)
//TAKE POINTER TWO BOTH A, B (INITIAL), TAKE COUNT(VAR), IF A & B CHAR IS SAME COUNT+1 , ELSE MAX OF 
//BOTH TAKE AND NOT TAKE POINTERS,(I & J).
class Solution {
public:
    int dp[1001][1001];
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

//BOTTOM UP (TABULATION)                                     {T.C = O(N*M), S.C = O(N*M)}
class Solution {
public:
    int dp[1001][1001];
    int solveTab(string &a, string &b, int n, int m){
        //base case 1st row and 1st col of dp table is 0
        for(int i = 0 ; i < n+1 ; i++) dp[i][0] = 0;
        for(int j = 0 ; j < m+1 ; j++) dp[0][j] = 0;

        //fill rest of table
        for(int i = 1; i < n+1 ; i++){
            for(int j = 1 ; j < m+1 ; j++){
                if(a[i-1] == b[j-1]){                        //index from 0 not 1
                    dp[i][j] = 1 + dp[i-1][j-1];
                } 
                else{
                    dp[i][j] = 0 + max(dp[i-1][j], dp[i][j-1]);
                } 
            }
        }

        return dp[n][m];                                   //last box of table(LCS length)
    }
    int longestCommonSubsequence(string text1, string text2) {
        memset(dp, -1, sizeof(dp));
        int n = text1.size(), m = text2.size();
        return solveTab(text1, text2, n, m);             //n , m = size of both strings(dp table nXm)
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


//370. PRINT LONGEST COMMON SUBSEQUENCE                      {T.C = O(N*M), S.C = O(N*M)}
//SAME AS FINDING LENGTH OF LCS, JUST ADD CONDITION TO PRINT LCS
class Solution {
public:
    int dp[1001][1001];
    int solveTab(string &a, string &b, int n, int m){
        //base case 1st row and 1st col of dp table is 0
        for(int i = 0 ; i < n+1 ; i++) dp[i][0] = 0;
        for(int j = 0 ; j < m+1 ; j++) dp[0][j] = 0;

        //fill rest of table
        for(int i = 1; i < n+1 ; i++){
            for(int j = 1 ; j < m+1 ; j++){
                if(a[i-1] == b[j-1]){                        //index from 0 not 1
                    dp[i][j] = 1 + dp[i-1][j-1];
                } 
                else{
                    dp[i][j] = 0 + max(dp[i-1][j], dp[i][j-1]);
                } 
            }
        }
        //print lc string
        string lcs = "";
        int i = n , j = m;
        while(i > 0 && j > 0){
            if(a[i-1] == b[j-1]){
                lcs.push_back(a[i-1]);
                i--, j--;
            }else{
                if(dp[i-1][j] > dp[i][j-1]) i--;
                else j--;
            }
        }
        reverse(lcs.begin(), lcs.end());                  //curr string is in reverse order
        cout<<lcs<<" ";

        return dp[n][m];                                   //last box of table(LCS length)
    }
    int longestCommonSubsequence(string text1, string text2) {
        memset(dp, -1, sizeof(dp));
        int n = text1.size(), m = text2.size();
        return solveTab(text1, text2, n, m);             //n , m = size of both strings(dp table nXm)
    }
};
/*
Input
text1 =
"abcde"
text2 =
"ace"
Stdout
ace 
Output
3
Expected
3
*/