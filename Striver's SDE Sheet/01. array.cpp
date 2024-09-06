//ARRAYS
#include<bits/stdc++.h>
using namespace std;

//01. SET MATRIX ZEROES                                          {T.C = O(N^2), S.C = O(N)}
//TRAVERSAL (2 NESTED LOOP)
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<int>row(n+1, 0);
        vector<int>col(m+1, 0);

        for(int i = 0 ; i < n ; i++){                   //mark 0's row or col = 1 
            for(int j = 0 ; j < m ; j++){
                if(matrix[i][j] == 0){
                    row[i] = 1;
                    col[j] = 1;
                }
            }
        }

        for(int i = 0 ; i < n ; i++){                 //if marks of row or col == 1 then its element = 0
            for(int j = 0 ; j < m; j++){
                if(row[i] == 1 || col[j] == 1){                //if row or col updated(to 1)
                    matrix[i][j] = 0;
                }
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


//02. PASCAL'S TRIANGLE                                                  {T.C = O(N^2), S.C = O(N^2)}
//2 LOOP ( 2ND LOOP FROM 1 TO i , SUM(UPPER COL ELEMENT + DIAGONAL UP ELEMENT))
//APPLICATION (xCy => search in pascal table)
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>>ans(numRows);
        for(int i = 0 ; i < numRows ; i++){
            ans[i] = vector<int>(i+1, 1);                     //each row (i+1 element with starting 1)
            for(int j = 1 ; j < i ; j++){                     //1st and last is 1 always
                ans[i][j] = ans[i-1][j] + ans[i-1][j-1];      //just above col element + diagonal up
            }
        }
        return ans;
    }
};
/*
Example 1:
Input: numRows = 5
Output: [[1],
         [1,1],
         [1,2,1],
         [1,3,3,1],
         [1,4,6,4,1]]

Example 2:
Input: numRows = 1
Output: [[1]]
*/


//03. NEXT PERMUTATION                                             {T.C = O(N), S.C = O(1)}
//TRAVERSAL(REVERSE)
/*
1. Find golaIdx {(golaIdx)arr[i-1] < arr[i]} from reverse traversal
2. Again reverse traverse and find just greater then value of golaValue and find its idx.
3. swap golaIdx value and just greater idx value.
4. finally reverse rest of after golaIdx(not included) value.
*/
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();

        int golaIdx = -1;
        //find blue circle element ({golaIdx}arr[i-1] < arr[i] from last)
        for(int i = n-1 ; i > 0 ; i--){
            if(nums[i-1] < nums[i]){
                golaIdx = i-1;
                break;
            }
        }

        if(golaIdx != -1){
            int swapIdx = golaIdx;
            for(int i = n-1 ; i >= golaIdx + 1 ; i--){
                if(nums[i] > nums[golaIdx]){
                    swapIdx = i;
                    break;
                }
            }
            swap(nums[golaIdx], nums[swapIdx]);
        }

        reverse(nums.begin()+golaIdx+1 , nums.end());
    }
};
/*
Example 1:
Input: nums = [1,2,3]
Output: [1,3,2]

Example 2:
Input: nums = [3,2,1]
Output: [1,2,3]

Example 3:
Input: nums = [1,1,5]
Output: [1,5,1]
*/


//04. MAXIMUM SUBARRAY                                                {T.C = O(N), S.C = O(1)}
//KADANE'S ALGO
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        int sum = 0;
        int maxSum = INT_MIN;
        for(int i = 0 ; i < n ; i++){
            sum += nums[i];
            maxSum = max(maxSum, sum);
            if(sum < 0){
                sum = 0;
            }
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


//05. SORT COLORS OR (SORT AN ARRAY OF 0'S , 1'S AND 2'S)                {T.C = O(N), S.C = O(1)}
//3 POINTERS(LOW, MID, HIGH)
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int low = 0, mid = 0, high = nums.size()-1;
        while(mid <= high){
            if(nums[mid] == 0){
                swap(nums[low], nums[mid]);
                low++, mid++;
            }else if(nums[mid] == 1){
                mid++;
            }else{ //nums[mid] == 2
                swap(nums[high], nums[mid]);
                high--;
            }
        }
    }
};
/*
Example 1:
Input: nums = [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]

Example 2:
Input: nums = [2,0,1]
Output: [0,1,2]
*/


//06. BEST TIME TO BUY AND SELL STOCK (BUY 1 DAY, SELL ANOTHER DAY)                    {T.C = O(N), S.C = O(1)}
//KADANE'S ALGO (FINDING MAX PROFIT INSTEAD OF SUM)
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int mini = prices[0];
        int maxPft = 0;

        for(int i = 1 ; i < prices.size() ; i++){
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
