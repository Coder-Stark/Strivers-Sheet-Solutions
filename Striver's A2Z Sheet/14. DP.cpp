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
//LCS PATTERN========================================================================================
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
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                } 
            }
        }
        //print LCS string
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


//371. LONGEST COMMON SUBSTRING                                {T.C = O(N*M), S.C = O(N*M)}
//USING BOTTOM UP (TABULATION)
//SIMILAR TO SUBSEQUENCE , IN ELSE CASE (NOT MATCH CHAR) RESET THE TABLE TO 0 AND AGAIN SEARCH FOR MAXLEN
class Solution {
public:
    int dp[1001][1001];
    int solveTab(string &a, string &b, int n, int m){
        //base fill row and col with 0
        for(int i = 0 ; i < n+1 ; i++) dp[i][0] = 0;
        for(int j = 0 ; j < m+1 ; j++) dp[0][j] = 0;
        
        int maxLen = 0;
        //fill remaining table
        for(int i = 1; i < n+1 ; i++){
            for(int j = 1 ; j < m+1 ; j++){
                if(a[i-1] == b[j-1]){
                    dp[i][j] = 1 + dp[i-1][j-1];
                    maxLen = max(maxLen, dp[i][j]);
                }else{
                    dp[i][j] = 0;                          //reset (in subsequence {max(dp[i-1][j], dp[i][j-1])})
                }
            }
        }
        return maxLen;                           
    }
    int longestCommonSubstr(string s1, string s2, int n, int m) {
        return solveTab(s1, s2, n, m);
    }
};
/*
Example 1:
Input: S1 = "ABCDGH", S2 = "ACDGHR", n = 6, m = 6
Output: 4
Explanation: The longest common substring
is "CDGH" which has length 4.

Example 2:
Input: S1 = "ABC", S2 "ACB", n = 3, m = 3
Output: 1
Explanation: The longest common substrings
are "A", "B", "C" all having length 1.
*/


//372. LONGEST PALINDROMIC SUBSEQUENCE                          {T.C = O(N^2), S.C = O(N^2)}
//BOTTOM UP (TABULATION)
//JUST MAKE REVERSE STRING AND PASS AS IT AS TO LCS (PALINDROME => FIRST AND LAST CHAR SAME)
class Solution {
public:
    int dp[1001][1001];
    int solveTab(string &a, string &b, int n){
        //fill first row and first col 0
        for(int i = 0 ; i < n+1 ; i++) dp[i][0] = 0;
        for(int j = 0 ; j < n+1 ; j++) dp[0][j] = 0;

        //fill remaining table
        for(int i = 1 ; i < n+1 ; i++){
            for(int j = 1 ; j < n+1 ; j++){
                if(a[i-1] == b[j-1]){
                    dp[i][j] = 1 + dp[i-1][j-1];
                }else{
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        return dp[n][n];
    }
    int longestPalindromeSubseq(string s) {
        int n = s.length();                   //n = m
        string original = s;
        reverse(s.begin(), s.end());
        return solveTab(original, s, n);                 //s is now reversed string
    }
};
/*
Example 1:
Input: s = "bbbab"
Output: 4
Explanation: One possible longest palindromic subsequence is "bbbb".

Example 2:
Input: s = "cbbd"
Output: 2
Explanation: One possible longest palindromic subsequence is "bb".
*/


//373. MINIMUM INSERTION STEPS TO MAKE A STRING PALINDROME          {T.C = O(N^2), S.C = O(N^2)}
//BOTTOM UP (TABULATION)
//FIND LPS(ABOVE CODE), THEN JUST SUBTRACT TOTAL LENGTH-LPS
class Solution {
public:
    int dp[501][501];
    int solveTab(string &a, string &b, int n){
        //base case fill first row & col with 0
        for(int i = 0 ; i < n+1 ; i++) dp[i][0] = 0;
        for(int j = 0 ; j < n+1 ; j++) dp[0][j] = 0;

        //fill remaining table
        for(int i = 1 ; i < n+1 ; i++){
            for(int j = 1 ; j < n+1 ; j++){
                if(a[i-1] == b[j-1]){
                    dp[i][j] = 1 + dp[i-1][j-1];
                }else{
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        return dp[n][n];
    }
    int longestPalindromeSubseq(string &s){                 //lps
        int n = s.length();
        string original = s;
        reverse(s.begin(), s.end());
        return solveTab(original, s, n);                  //s is now reverse string
    }
    int minInsertions(string s) {
        int n = s.length();
        int lps = longestPalindromeSubseq(s);
        return n - lps;                                 //min insertion req n-lps(all except already palindromes char)
    }
};
/*
Example 1:
Input: s = "zzazz"
Output: 0
Explanation: The string "zzazz" is already palindrome we do not need any insertions.

Example 2:
Input: s = "mbadm"
Output: 2
Explanation: String can be "mbdadbm" or "mdbabdm".

Example 3:
Input: s = "leetcode"
Output: 5
Explanation: Inserting 5 characters the string becomes "leetcodocteel".
*/


//374. DELETE OPERATION FOR TWO STRING                         {T.C = O(N*M), S.C = O(N*M)}
//BOTTOM UP(TABULATION)
//FIND LCS , RETURN N-LCS(DELETION REQ), M-LCS(INSERTION REQ)
class Solution {
public:
    int dp[501][501];
    int solveTab(string &a, string &b, int n, int m){
        //base case fill 1st row and col 0   (it is optional part)
        for(int i = 0 ; i < n+1 ; i++) dp[i][0] = 0;
        for(int j = 0 ; j < m+1 ; j++) dp[0][j] = 0;

        //fill rest of table
        for(int i = 1; i < n+1 ; i++){
            for(int j = 1 ; j < m+1 ; j++){
                if(a[i-1] == b[j-1]){
                    dp[i][j] = 1 + dp[i-1][j-1];
                }else{
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        return dp[n][m];
    }
    int minDistance(string word1, string word2) {
        int n = word1.length(), m = word2.length();
        int lcs = solveTab(word1, word2, n, m);
        return (n-lcs) + (m-lcs);                          //deletion(word1), insertion(word2)
    }
};
/*
Example 1:
Input: word1 = "sea", word2 = "eat"
Output: 2
Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".

Example 2:
Input: word1 = "leetcode", word2 = "etco"
Output: 4
*/


//375. SHORTEST COMMON SUPERSEQUENCE (SCS)                       {T.C = O(N*M), S.C = O(N*M)}
//BOTTOM UP(TABULATION)
//SCS LENGTH = N+M-LCS
//FOR PRINT PRINT ACCORDINGLY BELOW
class Solution {
public:
    int dp[1001][1001];
    string solveTab(string &a, string &b, int n, int m){
        //base case fill 1st row and col 0
        for(int i = 0 ; i < n+1; i++) dp[i][0] = 0;
        for(int j = 0 ; j < m+1; j++) dp[0][j] = 0;

        //fill remaining table
        for(int i = 1; i < n+1; i++){
            for(int j = 1 ; j < m+1; j++){
                if(a[i-1] == b[j-1]){
                    dp[i][j] = 1 + dp[i-1][j-1];
                }else{
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }

        //print the SCS
        int i = n, j = m;
        string ans = "";
        while(i > 0 && j > 0){
            if(a[i-1] == b[j-1]){
                ans.push_back(a[i-1]);
                i--, j--;
            }else{
                if(dp[i-1][j] > dp[i][j-1]){
                    ans.push_back(a[i-1]);
                    i--;
                }else{
                    ans.push_back(b[j-1]);
                    j--;
                }
            }
        }
        while(i > 0){                                 //print remaining char or row or col
            ans.push_back(a[i-1]);
            i--;
        }
        while(j > 0){
            ans.push_back(b[j-1]);
            j--;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
    string shortestCommonSupersequence(string str1, string str2) {
        int n = str1.size(), m = str2.size();
        return solveTab(str1, str2, n, m);
    }
};
/*
Example 1:
Input: str1 = "abac", str2 = "cab"
Output: "cabac"
Explanation: 
str1 = "abac" is a subsequence of "cabac" because we can delete the first "c".
str2 = "cab" is a subsequence of "cabac" because we can delete the last "ac".
The answer provided is the shortest such string that satisfies these properties.

Example 2:
Input: str1 = "aaaaaaaa", str2 = "aaaaaaaa"
Output: "aaaaaaaa"
*/


//STRING MATCHING PATTERN===========================================================================
//376. DISTINCT SUBSEQUENCES                                       {T.C = O(N*M), S.C = O(N*M)}
//TOP DOWN (MEMOIZATION)
//HAND BASE CASE (T EXHAUST(REQ STRING MATCHED RETURN 1), S EXHAUST(REQ STRING NOT ENOUGH LEN TO MATCH))
//IF CHAR SAME THEN ICREASE BOTH POINTER + S POINTER(MULTIPLE ANS), ELSE INCREASE ONLY S POINTER
class Solution {
public:
    int dp[1001][1001];
    int solveMem(string &a, string &b, int i, int j){
        int n = a.length(), m = b.length();
        //base case
        if(j >= m) return 1;                            //t exhaust (all char of t matches)
        if(i >= n) return 0;                            //s exhaust but not t(not enough char to match)

        if(dp[i][j] != -1) return dp[i][j];

        if(a[i] == b[j]){
            dp[i][j] = solveMem(a, b, i+1, j+1) + solveMem(a, b, i+1, j);
        }else{
            dp[i][j] = solveMem(a, b, i+1, j);
        }

        return dp[i][j];
    }
    int numDistinct(string s, string t) {
        memset(dp, -1, sizeof(dp));
        return solveMem(s, t, 0, 0);                    //0, 0 = initial index of both string
    }
};
/*
Example 1:
Input: s = "rabbbit", t = "rabbit"
Output: 3
Explanation:
As shown below, there are 3 ways you can generate "rabbit" from s.
rabbbit
rabbbit
rabbbit

Example 2:
Input: s = "babgbag", t = "bag"
Output: 5
Explanation:
As shown below, there are 5 ways you can generate "bag" from s.
babgbag
babgbag
babgbag
babgbag
babgbag
*/


//377. EDIT DISTANCE                                           {T.C = O(N*M), S.C = O(N*M)}
//TOP DOWN (MEMOIZATION)
//BASE CASE(A FULLY TRAVERSED REMAINING LENGTH OF ANOTHER IS ANS SIMILARLY FOR OTHER), IF CHAR MATCH
//MOVE BOTH POINTERS, ELSE (INSERT{J+1}, DELETE{I+1}, REPLACE(I+1, J+1)), TAKE MIN OF ALL.
class Solution {
public:
    int dp[501][501];
    int solveMem(string &a, string &b, int i, int j) {
        int n = a.length(), m = b.length();

        // Base case
        if (i == n) return m-j;                     //string1 is fully traversed now rest(m-j length is ans)
        if (j == m) return n-i;                    //string2 is fully traversed now rest(m-i length is ans)

        if (dp[i][j] != -1) return dp[i][j];

        int miniOp = INT_MAX;
        // Recursive call
        if (a[i] == b[j]) {
            miniOp = solveMem(a, b, i + 1, j + 1);
        } else { // Min of insert, delete, replace
            int insertOp = solveMem(a, b, i, j + 1);   //It increments the index j of b while keeping the index i of a the same
            int deleteOp = solveMem(a, b, i + 1, j);   //It increments the index i of a while keeping the index j of b the same
            int replacOp = solveMem(a, b, i + 1, j + 1);//It increments the index i of a as well as index j of b

            miniOp = 1 + min({insertOp, deleteOp, replacOp});         //1 (current operation + other)         
        }

        //step2 store ans in dp
        return dp[i][j] = miniOp;
    }

    int minDistance(string word1, string word2) {
        memset(dp, -1, sizeof(dp));
        return solveMem(word1, word2, 0, 0);                  //0, 0 = starting index of both strings
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


//378. WILDCARD MATCHING                                              {T.C = O(N*M), S.C = O(N*M)}
//TOP DOWN (MEMOIZATION)
//FIRST SWITCH CALL FOR MEMOIZATION (P->S (CONVERT PATTERN TO STRING)), THEN CHECK BASE CASES, THEN IF CHAR MATCH
//OR ? THEN INCREASE BOTH POINTER ELSE IF * (EMPTY OR DELETE FOR ANOTHER), ELSE FALSE.
class Solution {
public:
    int dp[2001][2001];
    
    bool solveMem(string &a, string &b, int i, int j) {
        int n = a.length(), m = b.length();
        // base case
        if(i >= n && j >= m) return true;                    // both s and pattern exhaust
        if(i >= n && j < m) return false;                    // s exhaust pattern not (not possible there is something to compare)
        if(i < n && j >= m) {                                // s not exhaust pattern exhaust if all * ? t : f
            for(int k = i; k < n; k++) {                     // all should be * else false
                if(a[k] != '*') return false;
            }
            return true;
        }

        if(dp[i][j] != -1) return dp[i][j];

        if(a[i] == b[j] || a[i] == '?') {
            dp[i][j] = solveMem(a, b, i+1, j+1);
        } else if(a[i] == '*') {
            dp[i][j] = solveMem(a, b, i+1, j) || solveMem(a, b, i, j+1);  // empty (* = '') or delete that char (b[j] = b[j+1]) to match
        } else {
            dp[i][j] = false;
        }

        return dp[i][j];
    }

    bool isMatch(string s, string p) {
        memset(dp, -1, sizeof(dp));
        return solveMem(p, s, 0, 0);            //switched the order of s and p (convert p->s)
    }
};
/*
Example 1:
Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".

Example 2:
Input: s = "aa", p = "*"
Output: true
Explanation: '*' matches any sequence.

Example 3:
Input: s = "cb", p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.
*/


//DP ON STOCKS--------------------------------------------------------------------------------------------
//379. BEST TIME TO BUY AND SELL STOCK I (ONE DAY BUY & ANOTHER DAY SELL)   {T.C = O(N), S.C = O(1)}
//SIMPLE ITERATION, KEEP MINI(STARTING ELE), MAXPROFIT = 0, TRAVERSE ELE, PROFIT = I-MINI, UPDATE MAXPROFIT
//UPDATE MINI FINALLY RETURN MAXPROFIT
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int mini = prices[0];
        int maxPft = 0;

        for(int i = 1 ; i < prices.size() ; i++){              //0 = mini
            int profit = prices[i] - mini;
            maxPft = max(maxPft, profit);
            mini = min(mini, prices[i]);                //for updating mini element
        }
        return maxPft;
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


//380. BEST TIME TO BUY AND SELL STOCK II (ONE DAY BUY & SELL MULTIPLE TIMES) {T.C = O(N {N*CONSTANT}), S.C = O(N)}
//TOP DOWN (MEMOIZATION)
//BUY (BUYKARO, SKIPKARO), SELL (SELLKARO, SKIPKARO)
class Solution {
public:
    vector<vector<int>>dp;
    int solveMem(vector<int>&prices, int i, int buy){
        int n = prices.size();
        //base case (out of bound)
        if(i == n) return 0;

        if(dp[i][buy] != -1) return dp[i][buy];

        int maxProfit = 0;
        if(buy){
            int buyKaro  = -prices[i] + solveMem(prices, i+1, 0);     //0 = next we have to sell
            int skipKaro = 0          + solveMem(prices, i+1, 1);     //1 = next we have to buy
            maxProfit = max(buyKaro, skipKaro);
        }else{
            int sellKaro = prices[i]  + solveMem(prices, i+1, 1);      
            int skipKaro = 0          + solveMem(prices, i+1, 0); 
            maxProfit = max(sellKaro , skipKaro);
        }

        return dp[i][buy] = maxProfit;
    }
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        dp.resize(n+1, vector<int>(2, -1));
        return solveMem(prices, 0, 1);                //0 = initial index, 1 = buy allowed(0 not allowed)
    }
};
/*
Example 1:
Input: prices = [7,1,5,3,6,4]
Output: 7
Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.
Total profit is 4 + 3 = 7.

Example 2:
Input: prices = [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
Total profit is 4.

Example 3:
Input: prices = [7,6,4,3,1]
Output: 0
Explanation: There is no way to make a positive profit, so we never buy the stock to achieve the maximum profit of 0.
*/


//381. BEST TIME TO BUY AND SELL STOCK III (ONE DAY BUY & SELL LIMITED TIMES) {T.C = O(N {N*2(LIMIT)}), S.C = O(N)}
//TOP DOWN (MEMOIZATION)
//BUY (BUYKARO, SKIPKARO), SELL (SELLKARO(LIMIT--), SKIPKARO)
class Solution {
public:
    vector<vector<vector<int>>>dp;
    int solveMem(vector<int>&prices, int i, int buy, int limit){
        int n = prices.size();
        //base case
        if(i >= n || limit == 0) return 0;

        if(dp[i][buy][limit] != -1) return dp[i][buy][limit];

        int maxProfit = 0;
        if(buy){
            int buyKaro  = -prices[i] + solveMem(prices, i+1, 0, limit);
            int skipKaro = 0          + solveMem(prices, i+1, 1, limit);
            maxProfit = max(buyKaro, skipKaro);
        }else{
            int sellKaro = +prices[i] + solveMem(prices, i+1, 1, limit-1);   //only in that case limit reduces
            int skipKaro = 0          + solveMem(prices, i+1, 0, limit);
            maxProfit = max(sellKaro, skipKaro);
        }
        return dp[i][buy][limit] = maxProfit;
    }
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        dp.resize(n+1, vector<vector<int>>(2, vector<int>(3, -1)));  //3 = 0, 1, 2
        return solveMem(prices, 0, 1, 2);             //0 = initial index, 1 = buy allowed, 2 = limit of transactions(in this 2)
    }
};
/*
Example 1:
Input: prices = [3,3,5,0,0,3,1,4]
Output: 6
Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.

Example 2:
Input: prices = [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are engaging multiple transactions at the same time. You must sell before buying again.

Example 3:
Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
*/


//382. BEST TIME TO BUY AND SELL STOCK IV (ONE DAY BUY & SELL LIMITED TIMES) {T.C = O(N*K(LIMIT)), S.C = O(N*K)}
//TOP DOWN (MEMOIZATION)
//BUY (BUYKARO, SKIPKARO), SELL (SELLKARO(LIMIT--), SKIPKARO)
class Solution {
public:
    vector<vector<vector<int>>>dp;
    int solveMem(vector<int>&prices, int i, int buy, int limit){       //limit == k
        int n = prices.size();
        //base case
        if(i >= n || limit == 0) return 0;

        if(dp[i][buy][limit] != -1) return dp[i][buy][limit];

        int maxProfit = 0;
        if(buy){
            int buyKaro  = -prices[i] + solveMem(prices, i+1, 0, limit);
            int skipKaro = 0          + solveMem(prices, i+1, 1, limit);
            maxProfit = max(buyKaro, skipKaro);
        }else{
            int sellKaro = +prices[i] + solveMem(prices, i+1, 1, limit-1);   //only in that case limit reduces
            int skipKaro = 0          + solveMem(prices, i+1, 0, limit);
            maxProfit = max(sellKaro, skipKaro);
        }
        return dp[i][buy][limit] = maxProfit;
    }
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        dp.resize(n+1, vector<vector<int>>(2, vector<int>(k+1, -1)));
        return solveMem(prices, 0, 1, k);              //0 = initial index, 1 = buy allowed, k = limit
    }
};
/*
Example 1:
Input: k = 2, prices = [2,4,1]
Output: 2
Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.

Example 2:
Input: k = 2, prices = [3,2,6,5,0,3]
Output: 7
Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
*/


//383. BEST TIME TO BUY AND SELL STOCK V (ONE DAY BUY & SELL MULTIPLE TIMES WITH COOLDOWN PERIOND(1 DAY)) 
//SIMILAR TO BUY SELL II                                            {T.C = O(N {N*CONSTANT}), S.C = O(N)}
//TOP DOWN (MEMOIZATION)
//BUY (BUYKARO, SKIPKARO), SELL (SELLKARO(I+2(COOL DOWN 1 DAY)), SKIPKARO)
class Solution {
public:
    vector<vector<int>>dp;
    int solveMem(vector<int>&prices, int i, int buy){
        int n = prices.size();
        //base case
        if(i >= n) return 0;                         //out of bound

        if(dp[i][buy] != -1) return dp[i][buy];

        int maxProfit = 0;
        if(buy){
            int buyKaro = -prices[i]  + solveMem(prices, i+1, 0);
            int skipKaro = 0          + solveMem(prices, i+1, 1);
            maxProfit = max(buyKaro, skipKaro);
        }else{
            int sellKaro = +prices[i] + solveMem(prices, i+2, 1);      //cool down (1 day so skip next day)
            int skipKaro = 0          + solveMem(prices, i+1, 0);
            maxProfit = max(sellKaro, skipKaro); 
        }

        return dp[i][buy] = maxProfit;
    }
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        dp.resize(n+1, vector<int>(2, -1));            //2 = buy allowed(0 , 1)
        return solveMem(prices, 0, 1);                 //0 = initial index, 1 = buy allowed
    }
};
/*
Example 1:
Input: prices = [1,2,3,0,2]
Output: 3
Explanation: transactions = [buy, sell, cooldown, buy, sell]

Example 2:
Input: prices = [1]
Output: 0
*/


//384. BEST TIME TO BUY AND SELL STOCK VI (ONE DAY BUY & SELL MULTIPLE TIMES WITH FEE(ON EACH TRANSACTION)) 
//SIMILAR TO BUY SELL V                                            {T.C = O(N {N*CONSTANT}), S.C = O(N)}
//TOP DOWN (MEMOIZATION)
//BUY (BUYKARO, SKIPKARO), SELL (SELLKARO(-FEE(TRANSACTION FEE)), SKIPKARO)
class Solution {
public:
    vector<vector<int>>dp;
    int solveMem(vector<int>&prices, int fee, int i, int buy){
        int n = prices.size();
        //base case
        if(i >= n) return 0;                            //out of bound

        if(dp[i][buy] != -1) return dp[i][buy];

        int maxProfit = 0;
        if(buy){
            int buyKaro = -prices[i]  + solveMem(prices, fee, i+1, 0);
            int skipKaro = 0          + solveMem(prices, fee, i+1, 1);
            maxProfit = max(buyKaro, skipKaro);
        }else{
            int sellKaro = +prices[i] + solveMem(prices, fee, i+1, 1) - fee;   //deduct fee only on sell of stocks
            int skipKaro = 0          + solveMem(prices, fee, i+1, 0);
            maxProfit = max(sellKaro, skipKaro);
        }

        return dp[i][buy] = maxProfit;
    }
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        dp.resize(n+1, vector<int>(2, -1));             //2 = buy(1), sell(0)
        return solveMem(prices, fee, 0, 1);             //0 = initial index, 1 = buy allowed
    }
};
/*
Example 1:
Input: prices = [1,3,2,8,4,9], fee = 2
Output: 8
Explanation: The maximum profit can be achieved by:
- Buying at prices[0] = 1
- Selling at prices[3] = 8
- Buying at prices[4] = 4
- Selling at prices[5] = 9
The total profit is ((8 - 1) - 2) + ((9 - 4) - 2) = 8.

Example 2:
Input: prices = [1,3,7,5,10,3], fee = 3
Output: 6
*/


//DP ON LIS(LONGEST INCREASING SUBSEQUENCE)-----------------------------------------------------------------
//385. LONGEST INCREASING SUBSEQUECE (LIS)                          {T.C = O(N^2), S.C = O(N^2)}
//TOP DOWN (MEMOIZATION)
//TAKE CURR AND PREV POINTER THEN , SIMPLE INCL & EXCL AND FIND MAXLEN(INCL, EXCL)
class Solution {
public:
    int dp[2501][2501];
    int solveMem(vector<int>&nums, int i, int p){
        int n = nums.size();
        //base case
        if(i >= n) return 0;

        if(dp[i][p+1] != -1) return dp[i][p+1];                 //p+1 for avoid negative index

        int incl = 0;
        if(p == -1 || nums[i] > nums[p]) incl = 1 + solveMem(nums, i+1, i);      //i become prev index and currIdx++
        int excl = 0 + solveMem(nums, i+1, p);               //p will same (if not included curr )

        return dp[i][p+1] = max(incl, excl);
    }
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        memset(dp, -1, sizeof(dp));
        return solveMem(nums, 0, -1);              //0 = initial index, -1 = prev index
    }
};

//USING 1D DP VECTOR & 2 FOR LOOP(CURRIDX, PREVIDX)                  {T.C = O(N^2), S.C = O(N)}
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int>dp(n, 1);                         //initially all dp element 1(min LIS len)
        
        int maxLen = 1;                             //atleast 1 element is there
        for(int i = 0 ; i < n ;i++){                //i = currIdx
            for(int p = 0 ; p < i ; p++){           //p = prevIdx
                if(nums[p] < nums[i]){
                    dp[i] = max(dp[i], 1 + dp[p]);
                }
            }
            maxLen = max(maxLen, dp[i]);
        }
        return maxLen;
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


//389. PRINT LONGEST INCREASING SUBSEQUENCE                        {T.C = O(N^2), S.C = O(N^2)}
//TOP DOWN (MEMOIZATION)
//FIND LIS LEN(USING ABOVE ) THEN BY USING THATS CREATED DP TABLE WE PRINT LIS.
class Solution {
public:
    int dp[1001][1001];

    int solveMem(vector<int>& arr, int i, int p) {
        int n = arr.size();
        // base case
        if (i >= n) return 0;
        
        if (dp[i][p+1] != -1) return dp[i][p+1];
        
        int incl = 0, excl = 0;
        if (p == -1 || arr[i] > arr[p]) {
            incl = 1 + solveMem(arr, i + 1, i);  // i becomes prevIdx
        }
        excl = solveMem(arr, i + 1, p);  // p does not change
        
        return dp[i][p+1] = max(incl, excl);
    }

    vector<int> printLIS(vector<int>& arr) {
        vector<int> ans;
        int i = 0, p = -1, n = arr.size();
        while (i < n) {
            if (p == -1 || arr[i] > arr[p]) {
                // if(dp[i][p+1] == 1 + dp[i+1][i+1]);        //not handle last elment
                if (dp[i][p+1] == 1 + (i + 1 < n ? dp[i+1][i+1] : 0)) {
                    ans.push_back(arr[i]);
                    p = i;                                    //update prev to curr idx.
                }
            }
            i++;
        }
        return ans;
    }

    vector<int> longestIncreasingSubsequence(int n, vector<int>& arr) {
        memset(dp, -1, sizeof(dp));
        solveMem(arr, 0, -1);  // Calculate LIS Length
        return printLIS(arr);  // Print using solveMem created dp table
    }
};

//USING 1D DP VECTOR                                               {T.C = O(N^2), S.C = O(N)}
class Solution {
  public:
    vector<int> longestIncreasingSubsequence(int n, vector<int>& arr) {
        vector<int>dp(n, 1);                         //fill all dp vector with 1(minlen)
        vector<int>hash(n);
        iota(hash.begin(), hash.end(), 0);           //work like hash(n, i);
        
        int lastIdx = 0;
        int maxLen = 1;
        for(int i = 0 ; i < n; i++){
            for(int p = 0 ; p < i ; p++){
                if(arr[p] < arr[i] && dp[i] < 1 + dp[p]){
                    dp[i] = 1 + dp[p];
                    hash[i] = p;
                }
            }
            if(dp[i] > maxLen){
                maxLen = dp[i];
                lastIdx = i;
            }
        }
        
        //print
        vector<int>ans;
        ans.push_back(arr[lastIdx]);                    //push last element then backtrack for other
        while(hash[lastIdx] != lastIdx){                //hash[i] == i (breaking point of list) // backtrack
            lastIdx = hash[lastIdx];
            ans.push_back(arr[lastIdx]);
        }
        reverse(ans.begin(), ans.end());
        
        return ans;
    }
};
/*
Example 1:
Input:
n = 16
arr = [0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15]
Output:
0 4 6 9 13 15 
Explanation:
longest Increasing subsequence is 0 4 6 9 13 15  and the length of the longest increasing subsequence is 6.

Example 2:
Input:
n = 1
arr = [1]
Output:
1
*/


//390. LONGEST INCREASING SUBSEQUENCE (LIS) USING BINARY SEARCH         {T.C = O(N*LOGN), S.C = O(N)}
//TRAVERSE ARR, IF CURR > LAST ? SIMPLY PUSH AND LEN++, FIND SAME OR JUST GREATER ELEMENT(LOWER_BOUND)
//AND REPLACE ELEMENT, FINALLY RETURN MAXLEN.
class Solution{
public:
    //USING BINARY SEARCH (N*LOGN)
    int longestSubsequence(int n, int a[]){
        vector<int>ans;
        ans.push_back(a[0]);               //push 1st element
        int maxLen = 1;                    //intial len 1(1st element)
        for(int i = 1 ; i < n ;i++){
            if(a[i] > ans.back()){
                ans.push_back(a[i]);
                maxLen++;
            }else{                       //replace with same or just greater element
                int it = lower_bound(ans.begin(), ans.end(), a[i]) - ans.begin();
                ans[it] = a[i];
            }
        }
        return maxLen;
    }
};
/*
Example 1:
Input: n = 6, a[ ] = {5,8,3,7,9,1}
Output: 3
Explanation: There are more than one LIS in this array.  
One such Longest increasing subsequence is {5,7,9}.

Example 2:
Input: n = 16, a[ ] = {0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15}
Output: 6
Explanation: There are more than one LIS in this array. 
One such Longest increasing subsequence is {0,2,6,9,13,15}.
*/


//391. LARGEST DIVISIBLE SUBSET                                            {T.C = O(N^2), S.C = O(N)}
//FIRST SORT NUMS(IT BECOMES SAME AS LIS PRINT), JUST REPLACE (NUMS[I] > NUM[P] WITH NUMS[I] % NUMS[P] == 0)
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        sort(nums.begin(), nums.end());                     //then apply simple LIS
        int n = nums.size();
        vector<int>dp(n, 1);
        vector<int>hash(n);
        iota(hash.begin(), hash.end(), 0);                    //fill with i(0,1,2...)

        int lastIdx = 0;
        int maxLen = 1;
        for(int i = 0 ; i < n ; i++){
            for(int p = 0 ; p < i ; p++){
                if(nums[i] % nums[p] == 0 && dp[i] < 1 + dp[p]){   //LIS(nums[i] > nums[p])
                    dp[i] = 1 + dp[p];
                    hash[i] = p;
                }
            }
            if(dp[i] > maxLen){
                maxLen = dp[i];
                lastIdx = i;
            }
        }
        //print
        vector<int>ans;
        ans.push_back(nums[lastIdx]);                   //push last element first then backtrack for other
        while(hash[lastIdx] != lastIdx){                //backtrack
            lastIdx = hash[lastIdx];
            ans.push_back(nums[lastIdx]);
        }
        reverse(ans.begin(), ans.end());               //ans is in reverse order 

        return ans;
    }
};
/*
Example 1:
Input: nums = [1,2,3]
Output: [1,2]
Explanation: [1,3] is also accepted.

Example 2:
Input: nums = [1,2,4,8]
Output: [1,2,4,8]
*/


//392. LONGEST STRING CHAIN                                     
//USING 2D DP                                                          {T.C = O(N^2*L), S.C = O(N^2)}
class Solution {
public:
    int dp[1001][1001];
    bool isPossible(string &curr, string &prev){
        int n = curr.length(), m = prev.length();
        
        if(n != m+1) return false;                    //diff between string always 1(predecessor)
            
        //check proper subsequence
        int i = 0, j = 0;                      //i = prevPointer, j = currPointer
        while(i < m && j < n){
            if(prev[i] == curr[j]){
                i++;
            }
            j++;
        }
        return i == m;                         //all check
    }
    int solveMem(vector<string>&words, int i, int p){
        int n = words.size();
        //base case
        if(i >= n) return 0;
     
        if(dp[i][p+1] != -1) return dp[i][p+1];

        int incl = 0, excl = 0;
        if(p == -1 || isPossible(words[i], words[p])){     
            incl = 1 + solveMem(words, i+1, i);
        }
        excl = 0 + solveMem(words, i+1, p);

        return dp[i][p+1] = max(incl, excl);
    }
    int longestStrChain(vector<string>& words) {
        memset(dp, -1, sizeof(dp));

        auto lambda = [&](auto a, auto b){             //sort on basis of string length
            return a.length() < b.length();
        };
        sort(words.begin(), words.end(), lambda);

        return solveMem(words, 0, -1);                  //0 = currIdx, -1 = prevIdx
    }
};

//USING 1D DP                                                               {T.C = O(N^2*L), S.C = O(N)}
class Solution {
public:
    //USING 1D DP
    bool isPossible(string &curr, string &prev){
        int n = curr.length(), m = prev.length();
        //base case
        if(n != m+1) return false;                       //predecessor should be 1 lesser size only
        int i = 0, j = 0;
        while(i < m && j < n){               //i = prev, j= curr
            if(prev[i] == curr[j]) i++;
            j++;
        }
        return i == m;
    }
    int longestStrChain(vector<string>& words) {
        auto lambda = [&](auto &a, auto &b){
            return a.length() < b.length();
        };
        sort(words.begin(), words.end(), lambda);      //sort according to length
        int n = words.size();
        vector<int>dp(n, 1);
        
        int maxLen = 1;
        for(int i = 0 ; i < n ; i++){
            for(int p = 0 ; p < i ; p++){
                if(isPossible(words[i], words[p]) && dp[i] < 1 + dp[p]){
                    dp[i] = 1 + dp[p];
                }
            }
            maxLen = max(maxLen, dp[i]);
        }
        return maxLen;
    }
};
/*
Example 1:
Input: words = ["a","b","ba","bca","bda","bdca"]
Output: 4
Explanation: One of the longest word chains is ["a","ba","bda","bdca"].

Example 2:
Input: words = ["xbc","pcxbcf","xb","cxbc","pcxbc"]
Output: 5
Explanation: All the words can be put in a word chain ["xb", "xbc", "cxbc", "pcxbc", "pcxbcf"].

Example 3:
Input: words = ["abcd","dbqca"]
Output: 1
Explanation: The trivial word chain ["abcd"] is one of the longest word chains.
["abcd","dbqca"] is not a valid word chain because the ordering of the letters is changed.
*/


//393. LONGEST BITONIC SUBSEQUENCE                                         {T.C = O(N^2), S.C = O(N)}
//USING 1D DP
//WE FIND LIS FROM FRONT AND BACK(REVERSING) BOTH THEN IF DP'S VALUE > 1 ? (DP1(I) + DP2(N-1-I) -1) MAX
class Solution {
  public:
    int lis(vector<int>&nums, int n, vector<int>&dp){
        int maxLen = 1;
        for(int i = 0 ; i < n ; i++){
            for(int p = 0 ; p < i ; p++){
                if(nums[p] < nums[i] && dp[i] < 1 + dp[p]) dp[i] = 1 + dp[p];
            }
            maxLen = max(maxLen, dp[i]);
        }
        return maxLen;
    }
    int LongestBitonicSequence(int n, vector<int> &nums) {
        vector<int>dp1(n, 1), dp2(n, 1);
        int lisFrontLen = lis(nums, n, dp1);
        reverse(nums.begin(), nums.end());
        int lisBackLen  = lis(nums, n, dp2);
        
        int maxLenBitonic = 0;                           //bitonic(increasing, decreasing or both)
        for(int i = 0 ; i < n ; i++){
            // maxLenBitonic = max(maxLenBitonic, dp1[i]+dp2[n-1-i]-1);   //when only (inc & dec) allowed  
            if (dp1[i] > 1 && dp2[n - 1 - i] > 1) {
                maxLenBitonic = max(maxLenBitonic, dp1[i] + dp2[n - 1 - i] - 1);    //-1 for curr count twice
            }
        }
        return maxLenBitonic;
    }
};
/*
Input: n = 5, nums[] = [1, 2, 5, 3, 2]
Output: 5
Explanation: The sequence {1, 2, 5} is increasing and the sequence {3, 2} is decreasing so merging both we will get length 5.

Input: n = 8, nums[] = [1, 11, 2, 10, 4, 5, 2, 1]
Output: 6
Explanation: The bitonic sequence {1, 2, 10, 4, 2, 1} has length 6.
*/


//394. NUMBER OF LONGEST INCREASING SEQUENCE (LIS)                      {T.C = O(N^2), S.C = O(N)}
//USING 1D DP
//TAKE COUNT VECTOR(COUNT AT THAT POINTS LIS LENGTH), IF(PREV DP COUNT == SAME) COUNT += COUNT PREV ELSE UPDATE CURRCOUNT
//FINALLY TAKE FOR LOOP AND SEARCH DP[I] == MAXLEN , RETURN ITS COUNT[I].
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int>dp(n, 1), count(n, 1);           //count = no. of lis at that point (at that point lis)
        int maxLen = 1;
        for(int i = 0 ; i < n; i++){
            for(int p = 0 ; p < i ; p++){
                if(nums[p] < nums[i]){
                    if(dp[i] < 1 + dp[p]){
                        dp[i] = 1 + dp[i];
                        count[i] = count[p];
                    } 
                    else if(dp[i] == 1 + dp[p]) count[i] += count[p];
                }
            }
            maxLen = max(maxLen, dp[i]);
        }

        int totalMaxLIS = 0;
        for(int i = 0 ; i < n ; i++){
            if(dp[i] == maxLen) totalMaxLIS  += count[i];
        }
        return totalMaxLIS;
    }
};
/*
Example 1:
Input: nums = [1,3,5,4,7]
Output: 2
Explanation: The two longest increasing subsequences are [1, 3, 4, 7] and [1, 3, 5, 7].

Example 2:
Input: nums = [2,2,2,2,2]
Output: 5
Explanation: The length of the longest increasing subsequence is 1, and there are 5 increasing subsequences of length 1, so output 5.
*/


//MATRIX CHAIN MULTIPLICATION (MCM)/ PARTITION DP---------------------------------------------------------------------------
/*RULE
1. Starts with entire block / array (mark i(start), j(end))
2. Try all partitions. (run a loop for all partitions)
3. Return the Best 2 partions
*/
//395, 396. MATRIX CHAIN MULTIPLICATION                                         {T.C = O(N^3), S.C = O(N^2)}
//TOP DOWN (MEMOIZATION)
//BASE CASE(I == J (ONLY 1 ELEMENT {NO OPER REQ})), TAKE LOOP K(I TO J-1), FIND MIN OP (A[I-1]*A[K]*A[J]) + SOLVE(I,K), 
//+ SOLVE(K+1, J);
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


//397. MINIMUM COSTS TO CUT A STICK                                      {T.C = O(N^3), S.C = O(N^2)}
//TOP DOWN (MEMOIZATION)
//INSERT 0 & N IN CUTS VECTOR, THEN SORT, THEN APPLY MCM , LOOP OF K(I, J-1 ), ADD COST = CUTS[J]-CUTS[I] AND RECURSIVE CALL
// THEN FIND MIN COSTS.
class Solution {
public:
    int dp[105][105];                             //ON CUTS NOT LEN (SHOULD BE at least 103)
    int solve(vector<int>& cuts, int i, int j) {
        if(i >= j) return 0;                    //invalid case
        
        if(dp[i][j] != -1) return dp[i][j];
        
        int mini = INT_MAX;
        for(int k = i; k <= j-1; k++) {          //traverse on cuts only (not whole len)
            int cost = (cuts[j]-cuts[i-1]) + solve(cuts, i, k) + solve(cuts, k+1, j);
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
        return solve(cuts, 1, m-1);
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


//398. BURST BALLOONS                                                   {T.C = O(N^3), S.C = O(N^2)}
//TOP DOWN (MEMOIZATION)
//ADD 1 ON BEGIN AND END, THEN SAME AS ABOVE , JUST (ADD NUM[I-1]*NUMS[K]*NUMS[J] {ACCORDING TO QUESTION})
class Solution {
public:
    int dp[305][305];
    int solveMem(vector<int>&nums, int i, int j){
        //base case
        if(i >= j) return 0;

        if(dp[i][j] != -1) return dp[i][j];

        int coins = 0, maxCoins = INT_MIN;
        for(int k = i ; k <= j-1 ; k++){
            coins = nums[i-1]*nums[k]*nums[j] + solveMem(nums, i, k) + solveMem(nums, k+1, j);
            maxCoins = max(maxCoins, coins);
        }

        return dp[i][j] = maxCoins;
    }
    int maxCoins(vector<int>& nums) {
        nums.insert(nums.begin(), 1);             //insert 1 at beginnning
        nums.push_back(1);                        //insert 1 at end

        memset(dp, -1, sizeof(dp));
        int m = nums.size();
        return solveMem(nums, 1, m-1);           //1 = initial index (mcm), m-1 (j)
    }
};
/*
Example 1:
Input: nums = [3,1,5,8]
Output: 167
Explanation:
nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167

Example 2:
Input: nums = [1,5]
Output: 10
*/


//399. BOOLEAN EVALUATION                                                {T.C = O(N^3), S.C = O(N^2*2(T,F))}
//TOP DOWN (MEMOIZATION)
//INIITIAL INDEX = 0 (OTHER MCM 1) => NO INVALID AT START AND END ONLY(T, F), THEN SIMILAR TO MCM, FOR LOOP(K - I TO J-1)
//FIND LT,LF,RT,RF, AND CHECK ALL OPERATOR(&,|,^) , STORE WAYS OF TRUE IN DP.
int mod = 1e9+7;
int dp[205][205][2];                     //i,j, isTrue(t,f)
int solveMem(int i, int j, int isTrue, string &s) {
    //base case
    if(i>j) return 0;                      //invalid case
    if(i==j) {                             //check for char 'T', 'F'
        if(isTrue) return s[i]=='T';
        else return s[i] == 'F';
    }

    if(dp[i][j][isTrue] != -1) return dp[i][j][isTrue];

    long long ways = 0;
    for(int k=i; k<j; k++) {            //0 to n-1 (other mcm 1 to n-1)
        long long leftTrue = solveMem(i, k-1, 1, s);
        long long leftFalse = solveMem(i, k-1, 0, s);
        long long rightTrue = solveMem(k+1, j, 1, s);
        long long rightFalse = solveMem(k+1, j, 0, s);

        if(s[k] == '&') {                        //t-> t&t, f->t&f, f&f, t&f 
            if(isTrue) ways = (ways + (leftTrue*rightTrue)%mod)%mod;
            else ways = (ways + (leftFalse*rightTrue)%mod + (leftFalse*rightFalse)%mod + (leftTrue*rightFalse)%mod)%mod;
        }
        else if(s[k] == '|') {                   //t->t|t, t|f, f|t, f->f|f
            if(isTrue) ways = (ways + (leftTrue*rightTrue)%mod + (leftTrue*rightFalse)%mod + (leftFalse*rightTrue)%mod)%mod;
            else ways = (ways + (leftFalse*rightFalse)%mod)%mod;
        }else {                                  //t->t^f, f^t, f->t^t, f^f
            if(isTrue) ways = (ways + (leftTrue*rightFalse)%mod + (leftFalse*rightTrue)%mod)%mod;
            else ways = (ways + (leftTrue*rightTrue)%mod + (leftFalse*rightFalse)%mod)%mod;
        }
    }

    return dp[i][j][isTrue] = ways;
}

int evaluateExp(string & exp) {
    int n = exp.size();
    memset(dp, -1, sizeof(dp));
    return solveMem(0,n-1, 1, exp);             //0 in that case (other mcm 1)
}
/*
Sample Input 1 :
T^T^F    
Sample Output 1 :
0
Explanation For Sample Input 1:
There are total 2  ways to parenthesize this expression:
(i) (T^T)^(F) = F
(ii) (T)^(T^F) = F
Both ways will result in False, so we will return 0.

Sample Input 2 :
F|T^F
Sample Output 2 :
2
Explanation For Sample Input 2:
For the first test case:
There are total 2  ways to parenthesize this expression:
(i) (F|T)^(F) = T
(ii) (F)|(T^F) = T
Both ways will result in True, so we will return 2.
*/


//FRONT PARTITION=======================================================================================================
//400. PALINDROME PARTITIONING II                                          {T.C = O(N^2), S.C = O(N)}
//TOP DOWN (MEMOIZATION)
//DIFFERENT FROM NORMAL MCM, MAKE 1D DP, ITERATE ON STRING AND WITH STRING , CREATE PARTION AND CHECK FOR VALID 
//PALINDROME AND FIND MIN OF IT.
class Solution {
public:
    int dp[2005];
    /*
    bool isPalindrome(string &s){
        int n = s.length();
        for(int i = 0 ; i < n ; i++){
            if(s[i] != s[n-1-i]) return false;
        }
        return true;
    }
    */
    bool isPalindrome(string &s, int l, int r){
        while(l < r){
            if(s[l++] != s[r--]) return false;
        }
        return true;
    }
    int solveMem(string &s, int i){
        int n = s.length();
        //base case
        if(i == n) return 0;

        if(dp[i] != -1) return dp[i];

        // string temp = "";
        int minCost = INT_MAX, cost = 0;
        for(int j = i ; j < n ; j++){
            // temp += s[j];
            // if(isPalindrome(temp)){
            if(isPalindrome(s, i, j)){             //check string i to j
                cost = 1 + solveMem(s, j+1);       //next i = j+1
                minCost = min(cost, minCost);
            } 
        }
        return dp[i] = minCost;
    }
    int minCut(string s) {
        memset(dp, -1, sizeof(dp));
        return solveMem(s, 0)-1;                       //0 = initial index, -1 = exclude partition of after end string
    }
};
/*
Example 1:
Input: s = "aab"
Output: 1
Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.

Example 2:
Input: s = "a"
Output: 0

Example 3:
Input: s = "ab"
Output: 1
*/


//401. PARTITION ARRAY FOR MAXIMUM SUM                                   {T.C = O(N^2), S.C = O(N)}
//TOP DOWN (MEMOIZATION)
//USING FRONT PARTITION, LOOP(I TO I+K), FIND LEN, MAXELE, SUM(LEN*MAXLEN) THEN RECURSIVE CALL AND FIND MAXSUM.
class Solution {
public:
    int dp[505];
    int solveMem(vector<int>&arr, int i, int k){
        int n = arr.size();
        //base case
        if(i == n) return 0;

        if(dp[i] != -1) return dp[i];

        int len = 0,maxEle = INT_MIN, sum = 0, maxSum = INT_MIN;
        for(int j = i ; j < min(n, i+k) ; j++){
            len++;
            maxEle = max(maxEle, arr[j]);
            sum = len*maxEle + solveMem(arr, j+1, k);
            maxSum = max(maxSum, sum);
        }

        return dp[i] = maxSum;
    }
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        memset(dp, -1, sizeof(dp));
        return solveMem(arr, 0, k);                        //0 = initial index, k = maxLen subarray
    }
};
/*
Example 1:
Input: arr = [1,15,7,9,2,5,10], k = 3
Output: 84
Explanation: arr becomes [15,15,15,9,10,10,10]

Example 2:
Input: arr = [1,4,1,5,7,3,6,1,9,9,3], k = 4
Output: 83

Example 3:
Input: arr = [1], k = 1
Output: 1
*/


//DP ON SQUARES--------------------------------------------------------------------------------------------------------
//402. MAXIMAL RECTANGLE                                                 {T.C = O(N^2), S.C = O(N)}
//CREATE HISTOGRAM, FIND MAX RECTANGLE, FIND NEXT AND PREV SMALLER (L = H[I], W = NEXT[I]-PREV[I]-1).
class Solution {
public:
    //PSL(PREVIOUS SMALLER LEFT)
    vector<int>prevSmaller(vector<int>arr , int n){
        stack<int>stk;
        vector<int>ans(n);
        for(int i = 0 ; i < n ; i++){
            while(!stk.empty() && arr[i] <= arr[stk.top()]){
                stk.pop();
            }
            ans[i] = stk.empty() ? -1 : stk.top();
            stk.push(i);
        }
        return ans;
    }
    //NSR(NEXT SMALLER RIGHT)
    vector<int>nextSmaller(vector<int>arr , int n){
        stack<int>stk;
        vector<int>ans(n);

        for(int i = n-1 ; i >= 0 ; i--){
            while(!stk.empty() && arr[i] <= arr[stk.top()]){
                stk.pop();
            }
            ans[i] = stk.empty() ? n : stk.top();
            stk.push(i);
        }
        return ans;
    }

    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int>next = nextSmaller(heights, n);
        vector<int>prev = prevSmaller(heights, n);
        int maxArea = 0;
        for(int i = 0 ; i < n ; i++){
            //l = heights[i], b = (next[i]-prev[i]-1)
            maxArea = max(maxArea, heights[i]*(next[i]-prev[i]-1));
        }
        return maxArea;
    }
    int maximalRectangle(vector<vector<char>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        int maxi = 0;
        vector<int>histogram(m, 0);                          //height (initially all h=0)

        for(int i =  0 ; i < n ; i++){
            //to create histogram array
            for(int j = 0 ; j < m ; j++){
                if(matrix[i][j] == '1') histogram[j]++;      //increasing height
                else histogram[j] = 0;                       //reset heigth to 0
            }
            maxi = max(maxi, largestRectangleArea(histogram));
        }
        return maxi;
    }
};
/*
Example 1:
Input: matrix = [["1","0","1","0","0"],
                 ["1","0","1","1","1"],
                 ["1","1","1","1","1"],
                 ["1","0","0","1","0"]]
Output: 6
Explanation: The maximal rectangle is shown in the above picture.

Example 2:
Input: matrix = [["0"]]
Output: 0

Example 3:
Input: matrix = [["1"]]
Output: 1
*/


//403. COUNT SQUARE SUBMATRICES WITH ALL 1'S                                 {T.C = O(N^2), S.C = O(N^2)}
//TOP DOWN (MEMOIZATION {DP[0]})
//FILL DP TABLE, IF I == 0 OR J == 0 DP[I][J] = 1, ELSE 1 + MIN(UP, LEFT, UPPER LEFT), FIND SUM OF ALL DP TABLE(COUNTS)
class Solution {
public:
    int dp[305][305];
    int countSquares(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        memset(dp, 0, sizeof(dp));

        int sum = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (matrix[i][j] == 1) {
                    if (i == 0 || j == 0) {
                        dp[i][j] = 1;
                    } else {
                        dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
                    }
                    sum += dp[i][j];
                }
            }
        }
        return sum;
    }
};
/*
Example 1:
Input: matrix =
[
  [0,1,1,1],
  [1,1,1,1],
  [0,1,1,1]
]
Output: 15
Explanation: 
There are 10 squares of side 1.
There are 4 squares of side 2.
There is  1 square of side 3.
Total number of squares = 10 + 4 + 1 = 15.

Example 2:
Input: matrix = 
[
  [1,0,1],
  [1,1,0],
  [1,1,0]
]
Output: 7
Explanation: 
There are 6 squares of side 1.  
There is 1 square of side 2. 
Total number of squares = 6 + 1 = 7.
*/



/*-----------------------------------------------THE END---------------------------------------------------------------*/