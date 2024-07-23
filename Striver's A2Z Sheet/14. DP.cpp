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
//358. SUBSET SUM PROBLEM
//
