#include<bits/stdc++.h>
using namespace std;

//DAY 10: RECURSION  & BACK TRACKING-----------------------------------------------------------------------------------------------------
//55. PERMUTATIONS 
//PRINT ALL PERMUTATION OF ARRAY                                         {T.C = O(N*N!), S.C = O(N)}
class Solution {
public:
    void solve(vector<int>&nums, vector<vector<int>>&ans, int i){
        int n = nums.size();
        //base case
        if(i >= n){
            ans.push_back(nums);
            return;
        }

        for(int j = i ; j < n ; j++){
            swap(nums[j], nums[i]);               //fix 1 place and make rec for other
            solve(nums, ans, i+1);
            
            swap(nums[j], nums[i]);                //backtrack
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>>ans;
        solve(nums, ans, 0);                          //0 = initial index
        return ans;
    }
};
/*
Example 1:
Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

Example 2:
Input: nums = [0,1]
Output: [[0,1],[1,0]]

Example 3:
Input: nums = [1]
Output: [[1]]
*/

//PRINT ALL PERMUTATION OF STRING (UNIQUE & SORTED {USE SET})                             {T.C = O(N*N!), S.C = O(N)}
class Solution
{
	public:
	    void solve(string &s, set<string>&st, int i){
	        int n = s.length();
	        //base case
	        if(i == n){
	            st.insert(s);
	            return;
	        }
	        
	        for(int j = i ; j < n ; j++){
	            swap(s[j], s[i]);
	            solve(s, st, i+1);             
	            
	            swap(s[j], s[i]);               //back track
	        }
	    }
		vector<string>find_permutation(string S)
		{
		    set<string>st;
		    solve(S, st, 0);                     //0 = initial index
		    
		    
		    vector<string>ans;
		    for(auto &it : st){
		        ans.push_back(it);
		    }
		    return ans;
		}
};
/*
Example 1:
Input: ABC
Output:
ABC ACB BAC BCA CAB CBA
Explanation:
Given string ABC has permutations in 6 
forms as ABC, ACB, BAC, BCA, CAB and CBA .

Example 2:
Input: ABSG
Output:
ABGS ABSG AGBS AGSB ASBG ASGB BAGS 
BASG BGAS BGSA BSAG BSGA GABS GASB 
GBAS GBSA GSAB GSBA SABG SAGB SBAG 
SBGA SGAB SGBA
Explanation:
Given string ABSG has 24 permutations.
*/


//56. N-QUEEN (USING STRING)                                          {T.C = O(N!), S.C = O(N^2)}
class Solution {
public:
    //check leftDiagonalUp, left, leftDiagonalDown (filling from left to right)
    bool isSafe(vector<string>&board, int i, int j, int n){
        //check leftDiagonalUp
        int row = i, col = j;
        while(row >= 0 && col >= 0){
            if(board[row][col] == 'Q') return false;
            row--, col--;
        }
        
        //check left
        row = i, col = j;
        while(col >= 0){
            if(board[row][col] == 'Q') return false;
            col--;
        }

        //check leftDiagonalDown
        row = i, col = j;
        while(row < n && col >= 0){
            if(board[row][col] == 'Q') return false;
            row++, col--;
        }
        return true;
    }
    void solve(vector<vector<string>>&ans, vector<string>&board, int n, int j){
        //base case
        if(j == n) return ans.push_back(board);

        for(int i = 0 ; i < n ; i++){
            if(isSafe(board, i, j, n)){
                board[i][j] = 'Q';
                solve(ans, board, n, j+1);
                board[i][j] = '.';                   //reset 'Q' to  '.' backtrack
            } 
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>>ans;
        vector<string>board(n, string(n, '.'));     //2D grid
        solve(ans, board, n, 0);                    //0 = col
        return ans;
    }
};
/*
Example 1:
Input: n = 4
Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above

Example 2:
Input: n = 1
Output: [["Q"]]
*/

//N QUEEN USING INTEGER                                                    {T.C = O(N!), S.C = O(N^2)}
class Solution{
public:
    //check for leftDiagonalUp, left, leftDiagonalDown
    bool isSafe(vector<vector<int>>&board, int i, int j, int n){
        //leftDiagonalUp
        int row = i, col = j;
        while(row >= 0 && col >= 0){
            if(board[row][col] == 1) return false;
            row--, col--;
        }
        
        //left
        row = i, col = j;
        while(col >= 0){
            if(board[row][col] == 1) return false;
            col--;
        }
        
        //leftDiagonalDown
        row = i, col = j;
        while(row < n && col >= 0){
            if(board[row][col] == 1) return false;
            row++, col--;
        }
        
        return true;
    }
    void solve(vector<vector<int>>&ans, vector<int>&temp, vector<vector<int>>&board, int j, int n){
        //base case
        if(j == n){
            ans.push_back(temp);
            return;
        }
        
        for(int i = 0 ; i < n  ; i++){
            if(isSafe(board, i, j , n)){
                board[i][j] = 1;                      //instead of 'Q'
                temp.push_back(i+1);                   //1 based indexing
                
                solve(ans, temp, board, j+1, n);
                
                board[i][j] = 0;                      //instead of '.'
                temp.pop_back();
            }
        }
    }
    vector<vector<int>> nQueen(int n) {
        vector<vector<int>>ans;
        vector<int>temp;
        vector<vector<int>>board(n, vector<int>(n, 0));
        
        solve(ans, temp, board, 0, n);                     //0 = col
        return ans;
    }
};
/*
Input: 1
Output: [1]
Explaination: Only one queen can be placed in the single cell available.

Input: 4
Output: [[2 4 1 3 ],[3 1 4 2 ]]
Explaination: These are the 2 possible solutions.
*/


//57. SUDOKU SOLVER                                             {T.C = O(EXP), S.C = O(1)}
class Solution {
public:
    bool isValid(vector<vector<char>>&board, int row , int col, int ch){
        for(int i = 0 ; i < 9 ; i++){
            if(board[row][i] == ch) return false;        //check all cols have ch or not
                
            if(board[i][col] == ch) return false;        //check all rows have ch or not
                
            if(board[3*(row/3) + i/3][3*(col/3) + i % 3] == ch) return false;   //check all 3x3 sub boxes have ch or not
        }
        return true;
    }
    bool solve(vector<vector<char>>&board){
        int n = board.size(), m = board[0].size();

        for(int i = 0 ; i < n; i++){
            for(int j = 0 ; j < m; j++){
                if(board[i][j] == '.'){
                    for(char ch = '1' ; ch <= '9' ; ch++){
                        if(isValid(board, i, j, ch)){
                            board[i][j] = ch;
                            if(solve(board) == true) return true;

                            board[i][j] = '.';               //reset (backtrack)
                        }
                    }
                    return false;
                }
            }
        }
        return true;                                    //already filled all
    }
    void solveSudoku(vector<vector<char>>& board) {
        solve(board);
    }
};
/*
Input: board = [["5","3",".",".","7",".",".",".","."],
			    ["6",".",".","1","9","5",".",".","."],
				[".","9","8",".",".",".",".","6","."],
				["8",".",".",".","6",".",".",".","3"],
				["4",".",".","8",".","3",".",".","1"],
				["7",".",".",".","2",".",".",".","6"],
				[".","6",".",".",".",".","2","8","."],
				[".",".",".","4","1","9",".",".","5"],
				[".",".",".",".","8",".",".","7","9"]]
Output: [["5","3","4","6","7","8","9","1","2"],
		 ["6","7","2","1","9","5","3","4","8"],
		 ["1","9","8","3","4","2","5","6","7"],
		 ["8","5","9","7","6","1","4","2","3"],
		 ["4","2","6","8","5","3","7","9","1"],
		 ["7","1","3","9","2","4","8","5","6"],
		 ["9","6","1","5","3","7","2","8","4"],
		 ["2","8","7","4","1","9","6","3","5"],
		 ["3","4","5","2","8","6","1","7","9"]]
Explanation: The input board is shown above and the only valid solution is shown below:
*/


//58. M-COLORING PROBLEM                                                     {T.C = O(M^N), S.C = O(N)}
class Solution {
public:
    bool isSafe(bool graph[101][101], int m, int n, vector<int>& vis, int node, int col) {
        for (int i = 0; i < n; i++) {
            if (i != node && graph[i][node] && vis[i] == col) {
                return false;
            }
        }
        return true;
    }

    bool dfs(bool graph[101][101], int m, int n, vector<int>& vis, int node) {
        if (node == n) {
            return true;
        }
        
        for (int i = 1; i <= m; i++) {
            if (isSafe(graph, m, n, vis, node, i)) {
                vis[node] = i;
                if (dfs(graph, m, n, vis, node + 1)) {
                    return true;
                }
                vis[node] = 0;                     //backtrack / pop
            }
        }
        return false;
    }

    bool graphColoring(bool graph[101][101], int m, int n) {
        vector<int> vis(n, 0);
        return dfs(graph, m, n, vis, 0); // 0 == starting index
    }
};
/*
Example 1:
Input:
N = 4
M = 3
E = 5
Edges[] = {(0,1),(1,2),(2,3),(3,0),(0,2)}
Output: 1
Explanation: It is possible to colour the
given graph using 3 colours.

Example 2:
Input:
N = 3
M = 2
E = 3
Edges[] = {(0,1),(1,2),(0,2)}
Output: 0
*/


//59. RAT IN A MAZE PROBLEM-I                                               {T.C = O(EXP), S.C = O(N^2)}
class Solution {
  public:
    void dfs(vector<vector<int>>&mat, vector<vector<bool>>&vis, vector<string>&ans, string s, int i, int j){ //s pass by val not refrence
        int n = mat.size();
        //base cases
        if(i < 0 || i >= n || j < 0 || j >= n) return;      //invalid case
        if(mat[i][j] == 0 || vis[i][j] == true) return;
        if(i == n-1 && j == n-1){
            ans.push_back(s);
            return;
        } 
            
        vis[i][j] = true;
        dfs(mat, vis, ans, s+'U', i-1, j);
        dfs(mat, vis, ans, s+'D', i+1, j);
        dfs(mat, vis, ans, s+'L', i, j-1);
        dfs(mat, vis, ans, s+'R', i, j+1);
        
        vis[i][j] = false;                              //backtrack
    }
    vector<string> findPath(vector<vector<int>> &mat) {
        int n = mat.size();               //n=m
        vector<string>ans;
        string s = "";
        vector<vector<bool>>vis(n, vector<bool>(n, false));
        dfs(mat, vis, ans, s, 0, 0);                    //0 = i, 0 = j
        
        sort(ans.begin(), ans.end());
        return ans;
    }
};
/*
Input: mat[][] = [[1, 0, 0, 0],
                [1, 1, 0, 1], 
                [1, 1, 0, 0],
                [0, 1, 1, 1]]
Output: DDRDRR DRDDRR
Explanation: The rat can reach the destination at (3, 3) from (0, 0) by two paths - DRDDRR and DDRDRR, when printed in sorted order we get DDRDRR DRDDRR.

Input: mat[][] = [[1, 0],
                [1, 0]]
Output: -1
Explanation: No path exists and destination cell is blocked.
*/


//60. WORD BREAK I                                                       {T.C = O(N^2), S.C = O(N)}
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
                if(solveMem(s, st, j+1)) return dp[i] = true;
            }
        }
        return dp[i] = false;                           //not valid found at last
    }
    bool wordBreak(string s, vector<string>& wordDict) {
        memset(dp, -1, sizeof(dp));
        unordered_set<string>st(wordDict.begin(), wordDict.end());
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

//WORD BREAK II                                                          {T.C = O(2^N), S.C = O(2^N)} 
class Solution {
public:
    void solve(string &s, unordered_set<string>&st, vector<string>&ans, string &currStr, int i){
        int n = s.length();
        //base case
        if(i >= n){
            ans.push_back(currStr);
            return;
        }

        for(int j = i; j < n ; j++){
            string temp = s.substr(i, j-i+1);
            if(st.count(temp)){
                string orig = currStr;
                if(!currStr.empty()) currStr += " ";
                currStr += temp;
                solve(s, st, ans, currStr, j+1);

                currStr = orig;                          //reset / backtrack
            }
        }

    }
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string>st(wordDict.begin(), wordDict.end());
        vector<string>ans;
        string currStr = "";
        solve(s, st, ans, currStr, 0);                    //0 = initial index

        return ans;
    }
};
/*
Example 1:
Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
Output: ["cats and dog","cat sand dog"]

Example 2:
Input: s = "pineapplepenapple", wordDict = ["apple","pen","applepen","pine","pineapple"]
Output: ["pine apple pen apple","pineapple pen apple","pine applepen apple"]
Explanation: Note that you are allowed to reuse a dictionary word.

Example 3:
Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: []
*/