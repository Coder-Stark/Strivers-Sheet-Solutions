#include<bits/stdc++.h>
using namespace std;


//DAY 14: STACK AND QUEUES 2 --------------------------------------------------------------------------------------------
//82. HELP CLASSMATE / NEXT SMALLER ELEMENT                         {T.C = O(N), S.C = O(N)}
//USING MONOTANIC STACK
class Solution{
    public:
    vector<int> help_classmate(vector<int> arr, int n){ 
        vector<int>ans(n, -1);
        stack<int>stk;
        for(int i = n-1 ;  i >= 0 ; i--){
            while(!stk.empty() && stk.top() >= arr[i]) stk.pop();  //top >= arr ? pop : push ans
            if(!stk.empty()) ans[i] = stk.top();

            stk.push(arr[i]);
        }
        return ans;
    } 
};
/*
Input: N = 5, arr[] = {3, 8, 5, 2, 25}
Output: 2 5 2 -1 -1
Explanation: 
1. Roll number 1 has 3 marks. The first person 
who has less marks than him is roll number 4, 
who has 2 marks.
2. Roll number 2 has 8 marks, he helps student 
with 5 marks.
3. Roll number 3 has 5 marks, he helps student 
with 2 marks.
4. Roll number 4 and 5 can not pick anyone as 
no student with higher roll number has lesser 
marks than them. This is denoted by -1.
Output shows the marks of the weaker student that 
each roll number helps in order. ie- 2,5,2,-1,-1
*/


//83. LRU CACHE

//84. LFU CACHE


//85. AREA OF LARGEST RECTANGLE IN A HISTOGRAM
//BRUTE FORCE                                                      {T.C = O(N^2), S.C = O(1)}
int largestarea(int arr[], int n) {
    int maxArea = 0;
    for(int i = 0; i < n; i++) {
          int minHeight = INT_MAX;
          for (int j = i; j < n; j++) {
            minHeight = min(minHeight, arr[j]);
            maxArea = max(maxArea, minHeight * (j - i + 1));
          }
    }
    return maxArea;
}

//USING STACK                                                      {T.C = O(N), S.C = O(N)}
class Solution {
public:
    vector<int> nextSmallerIdx(vector<int> arr, int n) {
        stack<int> stk;
        vector<int> ans(n);
        for(int i = n-1; i >= 0; i--) {                   //for next reverse traversal
            while(!stk.empty() && arr[stk.top()] >= arr[i]) stk.pop();
            ans[i] = stk.empty() ? n : stk.top();        //for not nextsmalleridx put n
            stk.push(i);
        }
        return ans;
    }
    vector<int> prevSmallerIdx(vector<int> arr, int n) {
        stack<int> stk;
        vector<int> ans(n);
        for(int i = 0; i < n; i++) {                      //for prev forward traversal
            while(!stk.empty() && arr[stk.top()] >= arr[i]) stk.pop();
            ans[i] = stk.empty() ? -1 : stk.top();        //for not prevSmalleridx put -1
            stk.push(i);
        }
        return ans;
    }
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int> nsi = nextSmallerIdx(heights, n);
        vector<int> psi = prevSmallerIdx(heights, n);
        
        int maxArea = 0;  // Initial area should be 0
        for(int i = 0; i < n; i++) {
            //l = heights[i] ; w = next[i]-prev[i]+1, 
            maxArea = max(maxArea, (heights[i]*(nsi[i] - psi[i] - 1)));   
        }
        return maxArea;
    }
};

/*
Example 1:
Input: heights = [2,1,5,6,2,3]
Output: 10
Explanation: The above is a histogram where width of each bar is 1.
The largest rectangle is shown in the red area, which has an area = 10 units.

Example 2:
Input: heights = [2,4]
Output: 4
*/


//86. SLIDING WINDOW MAXIMUM 
class Solution {
//BRUTE FORCE                                                       {T.C = O(N^2), S.C = O(N)}
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int>ans;
        for(int i = 0 ; i < n-k+1 ; i++){                 //last window starting idx = n-k+1
            int maxi = INT_MIN;
            for(int j = i ; j < i+k ; j++){
                maxi = max(maxi, nums[j]);
            }
            ans.push_back(maxi);
        }
        return ans;
    }
};

//USING SLDING WINDOW + MAXHEAP                                           {T.C = O(N*LOGK), S.C = O(N+K)}
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int>ans;
        priority_queue<pair<int,int>>maxHeap;
        int i = 0, j = 0;
        while(j < n){
            maxHeap.push({nums[j], j});

            if(j-i+1 == k && !maxHeap.empty()){
                while(!maxHeap.empty() && j-maxHeap.top().second + 1 > k){
                    maxHeap.pop();                         //if max ele is removing element then pop
                }
                ans.push_back(maxHeap.top().first);
                i++;
            }
            j++;
        }
        return ans;
    }
};

//USING DEQUE                                                           {T.C = O(N), S.C = O(N)}
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int>ans;
        deque<int>dq;                        //store ans in decreasing order
        //for first window
        for(int i = 0 ; i < k ; i++){
            while(!dq.empty() && dq.back() < nums[i]){
                dq.pop_back();
            }
            dq.push_back(nums[i]);
        }
        ans.push_back(dq.front());
        //for all next windows
        for(int i = k ; i < n ; i++){
            //remove previous element
            if(dq.front() == nums[i-k]){
                dq.pop_front();
            }

            //same as above
            while(!dq.empty() && dq.back() < nums[i]){
                dq.pop_back();
            }
            dq.push_back(nums[i]);
            ans.push_back(dq.front());                  //push all top elements
        }
        return ans;
    }
};
/*
Example 1:
Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation: 
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

Example 2:
Input: nums = [1], k = 1
Output: [1]
*/


//87. MIN STACK
class MinStack {
public:
    stack<int>s, b;          //s = stores original elements, b = stores minimum elements
    MinStack() {}
    
    void push(int val) {
        s.push(val);
        if(!b.empty()) val = min(val, b.top());
        b.push(val);
    }
    
    void pop() {                                     //for maintaining consistancy pop from both
        s.pop();
        b.pop();
    }
    
    int top() {
        return s.top();
    }
    
    int getMin() {
        return b.top();
    }
};
/*
Input
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]
Output
[null,null,null,null,-3,null,0,-2]
Explanation
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin(); // return -3
minStack.pop();
minStack.top();    // return 0
minStack.getMin(); // return -2
*/


//88. ROTTING ORANGES                                                 {T.C = O(N*M), S.C = O(N*M)}
class Solution {
public:
    vector<vector<int>>directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool isValid(int newR, int newC, int n, int m){
        return (newR >= 0 && newR < n && newC >= 0 && newC < m);
    }
    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        queue<pair<pair<int,int>, int>>q;                 //{{row, col}, time}
        vector<vector<bool>>vis(n, vector<bool>(m, false));
        int countFresh = 0;
        for(int i = 0 ; i < n; i++){
            for(int j = 0 ; j < m ; j++){
                if(grid[i][j] == 2){
                    q.push({{i, j}, 0});                   //0 time to rott (already rotten)
                    vis[i][j] = true;
                }
                
                if(grid[i][j] == 1) countFresh++;
            }
        }

        int count = 0;
        int totalTime = 0;
        //bfs
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            int row = frontNode.first.first;
            int col = frontNode.first.second;
            int time = frontNode.second;
            totalTime = max(totalTime, time);
            
            for(auto it : directions){
                int newR = row + it[0];
                int newC = col + it[1];

                if(isValid(newR, newC, n, m) && !vis[newR][newC] && grid[newR][newC] == 1){ //1 fresh (to rotten time+1)
                    vis[newR][newC] = true;
                    q.push({{newR, newC}, time+1});
                    count++;
                }
            }
        }

        if(count != countFresh) return -1;

        return totalTime;
    }
};
/*
Example 1:
Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
Output: 4

Example 2:
Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation: The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.

Example 3:
Input: grid = [[0,2]]
Output: 0
Explanation: Since there are already no fresh oranges at minute 0, the answer is 
*/


//89. ONLINE STOCK SPAN (COUNT OF PREV ELEMENT < CURR)                          {T.C = O(N), S.C = O(N)}
class StockSpanner {
public:
    stack<pair<int, int>>stk;
    StockSpanner() {}
    
    int next(int price) {
        int span = 1;                   //current span(minimum value before curr) is 1 
        while(!stk.empty() && stk.top().first <= price){
            span += stk.top().second;
            stk.pop();
        }
        stk.push({price, span});
        return span;
    }
};
/*
Example 1:
Input
["StockSpanner", "next", "next", "next", "next", "next", "next", "next"]
[[], [100], [80], [60], [70], [60], [75], [85]]
Output
[null, 1, 1, 1, 2, 1, 4, 6]
Explanation
StockSpanner stockSpanner = new StockSpanner();
stockSpanner.next(100); // return 1
stockSpanner.next(80);  // return 1
stockSpanner.next(60);  // return 1
stockSpanner.next(70);  // return 2
stockSpanner.next(60);  // return 1
stockSpanner.next(75);  // return 4, because the last 4 prices (including today's price of 75) were less than or equal to today's price.
stockSpanner.next(85);  // return 6
*/


//90. MAXIMUM OF MINIMUM FOR EVERY WINDOW SIZE                        {T.C = O(N), S.C = O(N)}
class Solution{
    public:
    vector<int> nextSmallerIdx(vector<int> arr, int n) {
        stack<int> stk;
        vector<int> ans(n);
        for (int i = n - 1; i >= 0; i--) {             // Reverse traversal for next smaller
            while (!stk.empty() && arr[stk.top()] >= arr[i]) {
                stk.pop();
            }
            ans[i] = stk.empty() ? n : stk.top();       // If no next smaller, set to n
            stk.push(i);
        }
        return ans;
    }

    vector<int> prevSmallerIdx(vector<int> arr, int n) {
        stack<int> stk;
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {                    // Forward traversal for previous smaller
            while (!stk.empty() && arr[stk.top()] >= arr[i]) {
                stk.pop();
            }
            ans[i] = stk.empty() ? -1 : stk.top();       // If no previous smaller, set to -1
            stk.push(i);
        }
        return ans;
    }

    vector<int> maxOfMin(int arr[], int n) {
        // Convert arr[] to vector<int> to use the updated functions
        vector<int> arrVec(arr, arr + n);
        
        // Calculate the previous and next smaller indices
        vector<int> leftSmaller = prevSmallerIdx(arrVec, n);   // Left smaller elements
        vector<int> rightSmaller = nextSmallerIdx(arrVec, n);  // Right smaller elements
        
        vector<int> ans(n, 0);                                 // Initialize answer array
        
        for (int i = 0; i < n; i++) {
            int windowSize = rightSmaller[i] - leftSmaller[i] - 1;  // Calculate window size
            ans[windowSize - 1] = max(ans[windowSize - 1], arr[i]);  // Update result for this window size
        }
        
        // Make sure each element in `ans` represents the maximum of the minimum values for all window sizes >= current
        for (int i = n - 2; i >= 0; i--) {
            ans[i] = max(ans[i + 1], ans[i]);
        }
        
        return ans;
    }
};
/*
Example 1:
Input:
N = 7
arr[] = {10,20,30,50,10,70,30}
Output: 70 30 20 10 10 10 10 
Explanation: 
1.First element in output indicates maximum of minimums of all windows of size 1.
2.Minimums of windows of size 1 are {10},{20}, {30}, {50},{10}, {70} and {30}. Maximum of these minimums is 70. 
3. Second element in output indicates maximum of minimums of all windows of size 2. 
4. Minimums of windows of size 2 are {10}, {20}, {30}, {10}, {10}, and {30}.
5. Maximum of these minimums is 30  Third element in output indicates maximum of minimums of all windows of size 3. 
6. Minimums of windows of size 3 are {10}, {20}, {10}, {10} and {10}.
7.Maximum of these minimums is 20. Similarly other elements of output are computed.

Example 2:
Input:
N = 3
arr[] = {10,20,30}
Output: 30 20 10
Explanation: First element in output indicates maximum of minimums of all windows of size 1.Minimums of windows of size 1 
are {10} , {20} , {30}. Maximum of these minimums are 30 and similarly other outputs can be computed
*/


//91. THE CELEBRITY PROBLEM                                              
//BRUTE FORCE                                                       {T.C = O(N^2), S.C = O(N)}
class Solution {
  public:
    int celebrity(vector<vector<int> >& mat) {
        int n = mat.size();                     //n == m
        vector<int>iKnow(n, 0);
        vector<int>knowMe(n, 0);
        
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                if(mat[i][j] == 1){
                    iKnow[i]++, knowMe[j]++;            //mat[i][j] -> i->j (i know j )
                }
            }
        }
        
        for(int i = 0 ; i < n ; i++){
            if(knowMe[i] == n-1 && iKnow[i] == 0) return i;
        }
        return -1;
    }
};

//USING STACK                                                        {T.C = O(N), S.C = O(N)}
//according to matrix
/*
1. ignore diagonal
2. 1 knows no one
3. all knows 1 , so 1 is celebrity
*/

/*
celebrity = row => all 0's
          = col => all 1's except diagonal element
*/
class Solution 
{
    private:
    bool knows(vector<vector<int> >& M,int a , int b, int n){
        return M[a][b] == 1 ? true : false;
    }
    
    public:
    int celebrity(vector<vector<int>>& M){
        int n = M.size();           //n == m
        stack<int>stk;
        
        //put all elements in stack
        for(int i = 0 ; i < n ; i++) stk.push(i);
        
        
        //get 2 person and compare them
        while(stk.size() > 1){
            int a = stk.top();
            stk.pop();
            
            int b = stk.top();
            stk.pop();
            
            if(knows(M,a,b,n)) stk.push(b);    //a knows b , so a is not celebrity, push again b in stack
            else stk.push(a);                  //b knows a , so b is not celebrity, push  again a in stack    
        }
        
        //(potential candidate left) single element left verify it , as a celebraty 
        int potentialCandidate = stk.top();
        
        //row check all should 0
        int zeroCount = 0;
        for(int i = 0 ; i < n ; i++){
            if(M[potentialCandidate][i] == 0){ 
                zeroCount++;
            }
        }
        //all zero
        if(zeroCount != n){
            return -1;
        }

        //col check all should 1
        int oneCount = 0;
        for(int i = 0 ; i < n ; i++){
            if(M[i][potentialCandidate] == 1){  
                oneCount++;
            }
        }
        //all one except diagonal
        if(oneCount != n-1 ){           //except digonal all 1
            return -1;
        }
        
        return potentialCandidate;
    }
};
/*
Input: mat[][] = [[0 1 0],
                [0 0 0], 
                [0 1 0]]
Output: 1
Explanation: 0th and 2nd person both know 1. Therefore, 1 is the celebrity. 

Input: mat[][] = [[0 1],
                [1 0]]
Output: -1
Explanation: The two people at the party both know each other. None of them is a celebrity.
*/