//RECURSION

#include<bits/stdc++.h>
using namespace std;


//GET A STRONG HOLD
//119. STRING TO INTEGER (ATOI) (RECURSIVE)                             {T.C = O(N), S.C = O(1)}
//FIRST HANDLE " " , + , - THEN MAKE RECURSIVE CALL OF ATOI
class Solution {
public:
    long atoi(string s, int sign, int i, long ans){
        if(sign*ans <= INT_MIN){
            return INT_MIN;
        }
        if(sign*ans >= INT_MAX){
            return INT_MAX;
        }
        if(i >= s.size() || s[i] < '0' || s[i] > '9'){
            return sign*ans;
        }
        ans = atoi(s, sign, i+1, (ans*10 + (s[i]-'0')));

        return ans;
    }
    int myAtoi(string s) {
        int n = s.length();
        int i = 0;
        int sign = 1;
        while(i < n && s[i] == ' '){          //ignore beginnig spaces
            i++;
        }
        if(s[i] == '+'){
            i++;
        }else if(s[i] == '-'){
            sign = -1;
            i++;
        }

        return atoi(s, sign, i, 0);           //0 = ans
    }
};
/*
Example 1:
Input: s = "42"
Output: 42
Explanation:
The underlined characters are what is read in and the caret is the current reader position.
Step 1: "42" (no characters read because there is no leading whitespace)
Step 2: "42" (no characters read because there is neither a '-' nor '+')
Step 3: "42" ("42" is read in)

Example 2:
Input: s = " -042"
Output: -42
Explanation:
Step 1: "   -042" (leading whitespace is read and ignored)
Step 2: "   -042" ('-' is read, so the result should be negative)
Step 3: "   -042" ("042" is read in, leading zeros ignored in the result)

Example 3:
Input: s = "1337c0d3"
Output: 1337
Explanation:
Step 1: "1337c0d3" (no characters read because there is no leading whitespace)
Step 2: "1337c0d3" (no characters read because there is neither a '-' nor '+')
Step 3: "1337c0d3" ("1337" is read in; reading stops because the next character is a non-digit)

Example 4:
Input: s = "0-1"
Output: 0
Explanation:
Step 1: "0-1" (no characters read because there is no leading whitespace)
Step 2: "0-1" (no characters read because there is neither a '-' nor '+')
Step 3: "0-1" ("0" is read in; reading stops because the next character is a non-digit)

Example 5:
Input: s = "words and 987"
Output: 0
Explanation:
Reading stops at the first non-digit character 'w'.
*/


//120. POW(X, N)                                                 {T.C = O(LOGN), S.C = O(LOGN)}
//HANDLE CASES ACCORDINGLY(-VE, EVEN , ODD)
class Solution {
public:
    double solve(double x, long n){
        //base case
        if(n == 0){                        //2^0 = 1
            return 1;
        }
        if(n < 0){                         //2^-1 = 1/2  
            return solve(1/x, -n);
        }
        if(n % 2 == 0){                   //2^8 = 2*2^4
            return solve(x*x , n/2);
        }else{
            return x*solve(x*x, (n-1)/2); //2^9 = 2*2(2^4)
        }
    }
    double myPow(double x, int n) {
        return solve(x, (long)n);
    }
};
/*
Example 1:
Input: x = 2.00000, n = 10
Output: 1024.00000

Example 2:
Input: x = 2.10000, n = 3
Output: 9.26100

Example 3:
Input: x = 2.00000, n = -2
Output: 0.25000
Explanation: 2-2 = 1/22 = 1/4 = 0.25
*/


//121. COUNT GOOD NUMBERS                                      {T.C = O(LOGN), S.C = O(LOGN)}
// //1 to 9  (5 even & val = even, 4 odd & val = prime) AND MAKE RECURSIVE CALL.
class Solution {
public:
    int mod = 1e9+7;

    long long power(long long x, long long y) {  // x^y
        if (y == 0) {                       // Base case: x^0 = 1
            return 1;
        }
        long long ans = power(x, y / 2);
        ans = (ans * ans) % mod;            // Square the result and take modulo

        if (y % 2 != 0) {                   // If y is odd, multiply by x one more time
            ans = (ans * x) % mod;
        }
        
        return ans;
    }

    int countGoodNumbers(long long n) {
        long long even = (n + 1)/2; 
        long long odd = n/2; 

        return (power(5, even) * power(4, odd)) % mod;          //1 to 9  (5 even & val = even, 4 odd & val = prime)
    }
};
/*
Example 1:
Input: n = 1
Output: 5
Explanation: The good numbers of length 1 are "0", "2", "4", "6", "8".

Example 2:
Input: n = 4
Output: 400

Example 3:
Input: n = 50
Output: 564908303
*/


//122. SORT A STACK                                                  {T.C = O(N^2), S.C = O(N)(call stack)}
//X > S.TOP() : S.PUSH(X) ELSE INSERTBOTTOM
void insertAtBottom(stack<int>&stk, int x){
    if(stk.empty() || x > stk.top()){            //extra x > stk.top() otherwise all same reverse stack
        stk.push(x);
        return;
    }
    
    int num = stk.top();
    stk.pop();
    insertAtBottom(stk, x);
    stk.push(num);
}
void SortedStack :: sort()
{
    if(stk.empty()){
        return;
    }
    
    int num = stk.top();
    stk.pop();

    //recursive call
    sort();                                     
    insertAtBottom(stk, num);
}
/*
Example 1:
Input:
Stack: 3 2 1
Output: 3 2 1

Example 2:
Input:
Stack: 11 2 32 3 41
Output: 41 32 11 3 2
*/


//123. REVERSE A STACK                                        {T.C = O(N^2), S.C = O(N)(CALL STACK)}
//SIMILAR AS ABOVE
class Solution{
public:
    void insertAtBottom(stack<int>&stk, int x){
        //base case
        if(stk.empty()){
            stk.push(x);
            return;
        }
        
        int num = stk.top();
        stk.pop();
        
        //recursive call
        insertAtBottom(stk, x);
        stk.push(num);
    }
    void Reverse(stack<int> &stk){
        //base case
        if(stk.empty()){
            return;
        }
        
        int num = stk.top();
        stk.pop();
        
        //recursive call
        Reverse(stk);
        insertAtBottom(stk, num);
    }
};
/*
Example 1:
Input:
St = {3,2,1,7,6}
Output:
{6,7,1,2,3}
Explanation:
Input stack after reversing will look like the stack in the output.

Example 2:
Input:
St = {4,3,9,6}
Output:
{6,9,3,4}
Explanation:
Input stack after reversing will look like the stack in the output.
*/


//SUBSEQUENCES PATTERN -------------------------------------------------------------------------------------
//124. CONSECUTIVE 1S NOT ALLOWED / GENERATE ALL BINARY STRINGS          {T.C = O(N), S.C = O(1)}
//..1  = ...0 , ...0 = SUM , SUM = ...0 + ...1
class Solution{
public:
	int mod = 1e9+7;
	ll countStrings(int n) {
	    ll zeroEnd = 1;
	    ll oneEnd = 1;
	    ll sum = zeroEnd + oneEnd;
	    
	    //base case
	    if(n == 1){
	        return sum;                       //2 ('0' & '1')
	    }
	    
	    int i = 2;
	    while(i <= n){
	        oneEnd = zeroEnd % mod;
	        zeroEnd = sum % mod;
	        sum = (oneEnd + zeroEnd) % mod;
	        i++;
	    }
	    return sum;
	}
};
/*
Example 1:
Input:
N = 3
Output: 5
Explanation:
5 strings are (000,
001, 010, 100, 101).

Example 2:
Input:
N = 2
Output: 3
Explanation: 
3 strings are (00,01,10).
*/


//125. GENERATE PARENTHESES                                     {T.C = O(2^N), S.C = O(N)}
//OPBR < N ? TEMP + '(' {OPBR+1} : CLBR + ')' {CLBR+1}
class Solution {
public:
    void solve(int n, vector<string>&ans, string temp, int opBr, int clBr){  //temp should be pass by value not by refence
        //base case
        if(temp.length() == n*2){                        //n*2 = pairs (opening + closing)
            ans.push_back(temp);
            return;
        }

        if(opBr < n){
            solve(n, ans, temp +'(', opBr+1, clBr);
        }
        if(clBr < opBr){
            solve(n, ans, temp +')', opBr, clBr+1);
        }
    }
    vector<string> generateParenthesis(int n) {
        vector<string>ans;
        string temp = "";
        solve(n, ans, temp, 0, 0);            //0 = opening bracket, 0 = closing bracket
        return ans;
    }
};
/*
Example 1:
Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]

Example 2:
Input: n = 1
Output: ["()"]
*/


//126. SUBSETS                                                        {T.C = O(2^N), S.C = O(N)}
//INCL & EXCL
class Solution {
private:
    void solve(vector<int>nums , vector<int>output , int index , vector<vector<int>> &ans){
        //base case
        if(index >= nums.size()){
            ans.push_back(output);
            return ;
        }

        //exclude
        solve(nums , output, index+1 , ans);

        //include
        int element = nums[index];
        output.push_back(element);
        solve(nums , output, index+1 , ans);
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> output;
        int index = 0; 
        vector<vector<int>> ans;

        solve(nums , output , index , ans);

        return ans;
    }
};

//USING BACKTRACK (POP BACK)
class Solution {
public:
    void solve(vector<int>&nums, vector<int>&temp, vector<vector<int>>&ans, int i){
        //base case
        if(i >= nums.size()){
            ans.push_back(temp);
            return;
        }

        //incl & excl
        int element = nums[i];
        temp.push_back(element);
        solve(nums, temp, ans, i+1);                 //incl

        temp.pop_back();
        solve(nums, temp, ans, i+1);      //excl
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int>temp;
        vector<vector<int>>ans;
        solve(nums, temp, ans, 0);           //0 = index

        return ans;
    }
};
/*
Example 1:
Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

Example 2:
Input: nums = [0]
Output: [[],[0]]
*/


//127. LEARN ALL PATTERNS OF SUBSEQUENCES                       
//THEORY


//128. PERFECT SUM PROBLEM / COUNT ALL SUBSEQUENCE WITH SUM K
//RECURSION (TLE)                                                        {T.C = O(2^N), S.C = O(1)}
class Solution{
	public:
	int solve(int arr[], int n, int sum, int i){
	    //base case
	    if(i == n && sum == 0){
	        return 1;
	    }
	    if(i >= n || sum < 0){                             //only positive allowed
	        return 0;
	    }
	    
	    //incl and excl
	    int incl = solve(arr, n, sum-arr[i], i+1);
	    int excl = solve(arr, n, sum, i+1);
	    
	    return incl + excl;
	}
	int perfectSum(int arr[], int n, int sum)
	{
        return solve(arr, n, sum, 0);                           // 0 = index
	}
};

//DP (MEMOIZATION)                                               {T.C = O(N*SUM), S.C = O(N*SUM)}
class Solution{
	public:
	int mod = 1e9+7;
	int solve(int arr[], int n, int sum, int i, vector<vector<int>>&dp){
	    //base case
	    if(i == n && sum == 0){
	        return 1;
	    }
	    if(i >= n || sum < 0){                             //only positive allowed
	        return 0;
	    }
	    
	    //if answer already present return it
	    if(dp[i][sum] != -1){
	        return dp[i][sum];
	    }
	    
	    //incl and excl
	    int incl = solve(arr, n, sum-arr[i], i+1, dp);
	    int excl = solve(arr, n, sum, i+1, dp);
	    
	    return dp[i][sum] = (incl % mod + excl % mod) % mod;
	}
	int perfectSum(int arr[], int n, int sum)
	{
	    vector<vector<int>>dp(n+1, vector<int>(sum+1, -1));
        return solve(arr, n, sum, 0, dp);                           // 0 = index
	}
};
/*
Example 1:
Input: 
N = 6
arr = [5, 2, 3, 10, 6, 8]
sum = 10
Output: 
3
Explanation: 
{5, 2, 3}, {2, 8}, {10} are possible subsets.

Example 2:
Input: 
N = 5
arr = [2, 5, 1, 4, 3]
sum = 10
Output: 
3
Explanation: 
{2, 1, 4, 3}, {5, 1, 4}, {2, 5, 3} are possible subsets.
*/


//129. SUBSET SUM
//RECURSION (TLE)                                                    {T.C = O(2^N), S.C = O(1)}
bool solve(vector<int>a, int n, int sum, int i){
    //base case
    if(i == n && sum == 0){
        return true;
    }
    if(i >= n || sum < 0){
        return false;
    }
    //incl && excl
    bool incl = solve(a, n, sum-a[i], i+1);
    bool excl = solve(a, n, sum, i+1);

    return incl || excl;
}
bool isSubsetPresent(int n, int k, vector<int> &a)
{
    return solve(a, n, k, 0);                                    //0 =  index
}

//DP (MEMOIZATION)                                                     {T.C = O(N*SUM), S.C = O(N*SUM)}
int dp[1001][1001];
bool solve(vector<int>&a, int n, int sum, int i){
    //base case
    if(i == n && sum == 0){
        return true;
    }
    if(i >= n || sum < 0){                       //sum < 0 only for negative range included
        return false;
    }

    //if already present return it
    if(dp[i][sum] != -1){
        return dp[i][sum];
    }
    
    //incl && excl
    bool incl = solve(a, n, sum-a[i], i+1);
    bool excl = solve(a, n, sum, i+1);

    return dp[i][sum] =  incl || excl;
}
bool isSubsetPresent(int n, int k, vector<int> &a)
{
    memset(dp, -1, sizeof(dp));
    return solve(a, n, k, 0);                                    //0 =  index
}
/*
Example 1:

Input: 
N = 6
arr = [5, 2, 3, 10, 6, 8]
sum = 10
Output: 
3
Explanation: 
{5, 2, 3}, {2, 8}, {10} are possible subsets.

Example 2:
Input: 
N = 5
arr = [2, 5, 1, 4, 3]
sum = 10
Output: 
3
Explanation: 
{2, 1, 4, 3}, {5, 1, 4}, {2, 5, 3} are possible subsets.
*/


//130. COMBINATION SUM   (UNIQUE)                                             {T.C = O(2^N*M), S.C = O(N*M)}
//RECURSION {i not i+1 (same element can be use any time)}
class Solution {
public:
    void solve(vector<int>&candidates, int target, vector<int>&temp, vector<vector<int>>&ans, int i){
        int n = candidates.size();
        //base case
        if(target == 0){
            ans.push_back(temp);
            return;
        }
        if(i >= n || target < 0){                //target == sum
            return;
        }

        //incl && excl
        int element = candidates[i];
        temp.push_back(element);
        solve(candidates, target-candidates[i], temp, ans, i);  //incl (i {same element can reuse})
        temp.pop_back();
        solve(candidates, target, temp, ans, i+1);                //excl
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int>temp;
        vector<vector<int>>ans;
        solve(candidates, target, temp, ans, 0);            //0 = currSum , 0 = index
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


//131. COMBINATION SUM II  (DUPLICATES)                                      {T.C = O(2^N*M), S.C = O(N*M)}
//RECURSION (SORT AND EXCL{NEXT INDEX = i+j{skipping index}})
class Solution {
public:
    void solve(vector<int>&candidates, int target, vector<int>&temp, vector<vector<int>>&ans, int i){
        int n = candidates.size();
        //base case
        if(target == 0){
            ans.push_back(temp);
            return;
        }
        if(i >= n || target < 0){                //target == sum
            return;
        }

        //incl && excl
        int element = candidates[i];
        temp.push_back(element);
        solve(candidates, target-candidates[i], temp, ans, i+1);  //incl (i {same element can reuse})
        temp.pop_back();

        /*
        //for skipping same elment
        int j = 1;
        while(i + j < n && candidates[i+j] == element){           //skip duplicates
            j++;
        }
        solve(candidates, target, temp, ans, i+j);                //excl {next index = i+j th}
        OR*/

        //for skipping same elment
        while(i + 1 < n && candidates[i] == candidates[i+1]){           //skip duplicates
            i++;
        }
        solve(candidates, target, temp, ans, i+1);  
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int>temp;
        vector<vector<int>>ans;
        sort(candidates.begin(), candidates.end());
        solve(candidates, target, temp, ans, 0);            //0 = currSum , 0 = index
        return ans;
    }
};
/*
Example 1:
Input: candidates = [10,1,2,7,6,1,5], target = 8
Output: 
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]

Example 2:
Input: candidates = [2,5,2,1,2], target = 5
Output: 
[
[1,2,2],
[5]
]
*/


//132. SUBSETS SUMS                                                      {T.C = O(2^N), S.C = O(N)}
//SIMPLE INCL & EXCL AND  i == n PUSH SUM IN ANS
class Solution {
  public:
    void solve(vector<int>&arr, int n, vector<int>&ans, int sum , int i){
        //base case
        if(i == n){
            ans.push_back(sum);
            return;
        }
            
        //incl & excl
        solve(arr, n, ans, sum + arr[i], i+1);             //incl
        solve(arr, n, ans, sum, i+1);                      //excl
    }
    vector<int> subsetSums(vector<int> arr, int n) {
        vector<int>ans;
        solve(arr, n, ans, 0, 0);                        //0 = sum , 0 = index
        return ans;
    }
};
/*
Example 1:
Input:
n = 2
arr[] = {2, 3}
Output:
0 2 3 5
Explanation:
When no elements is taken then Sum = 0.
When only 2 is taken then Sum = 2.
When only 3 is taken then Sum = 3.
When element 2 and 3 are taken then 
Sum = 2+3 = 5.

Example 2:
Input:
n = 3
arr = {5, 2, 1}
Output:
0 1 2 3 5 6 7 8
*/


//133a. SUBSETS I (UNIQUE)                                            {T.C = O(2^N), S.C = O(2^N)}
//INCL & EXCL (POP BACK)
class Solution {
public:
    void solve(vector<int>&nums, vector<int>&temp, vector<vector<int>>&ans, int i){
        //base case
        if(i >= nums.size()){
            ans.push_back(temp);
            return;
        }

        //incl & excl
        int element = nums[i];
        temp.push_back(element);
        solve(nums, temp, ans, i+1);                 //incl

        temp.pop_back();
        solve(nums, temp, ans, i+1);      //excl
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int>temp;
        vector<vector<int>>ans;
        solve(nums, temp, ans, 0);           //0 = index

        return ans;
    }
};
/*
Example 1:
Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

Example 2:
Input: nums = [0]
Output: [[],[0]]
*/


//133b. SUBSETS II (DUPLICATES)                                           {T.C = O(2^N), S.C = O(2^N)}
//INCL & EXCL (SORT AND SKIP SAME ELEMENT)
class Solution {
public:
    void solve(vector<int>&nums, vector<int>&temp, vector<vector<int>>&ans, int i){
        int n = nums.size();
        //base case
        if(i == n){
            ans.push_back(temp);
            return;
        }

        //incl & excl
        int element = nums[i];
        temp.push_back(element);
        solve(nums, temp, ans, i+1);                  //incl
        temp.pop_back();

        //for skipping same element
        while(i + 1 < n && nums[i] == nums[i+1]){
            i++;
        }
        solve(nums, temp, ans, i+1);                  //excl
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<int>temp;
        vector<vector<int>>ans;
        sort(nums.begin(), nums.end());
        solve(nums, temp, ans, 0);                     //0 = index
        return ans;
    }
};
/*
Example 1:
Input: nums = [1,2,2]
Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]

Example 2:
Input: nums = [0]
Output: [[],[0]]
*/


//134. COMBINATION SUM III                                            {T.C = O(2^N), S.C = O(N)}
//USE FOR LOOP(1 TO 9) THEN PUSH AND POP (INCL & EXCL)
class Solution {
public:
    void solve(int k, int sum, vector<int>&temp, vector<vector<int>>&ans, int i){
        //base case
        if(k == 0 && sum == 0){
            ans.push_back(temp);
            return;
        }
        if(k == 0 || sum < 0){
            return;
        }

        //incl & excl
        for(int j = i ; j <= 9 ; j++){
            temp.push_back(j);
            solve(k-1, sum-j, temp, ans, j+1);
            temp.pop_back();
        }                
    }
    vector<vector<int>> combinationSum3(int k, int n) {       //k = numbers , n = total sum
        vector<int>temp;
        vector<vector<int>>ans;
        solve(k, n, temp, ans, 1);                         //1 = start from 1 no. / index
        return ans;
    }
};
/*
Example 1:
Input: k = 3, n = 7
Output: [[1,2,4]]
Explanation:
1 + 2 + 4 = 7
There are no other valid combinations.

Example 2:
Input: k = 3, n = 9
Output: [[1,2,6],[1,3,5],[2,3,4]]
Explanation:
1 + 2 + 6 = 9
1 + 3 + 5 = 9
2 + 3 + 4 = 9
There are no other valid combinations.

Example 3:
Input: k = 4, n = 1
Output: []
Explanation: There are no valid combinations.
Using 4 different numbers in the range [1,9], the smallest sum we can get is 1+2+3+4 = 10 and since 10 > 1, there are no valid combination.
*/


//135. LETTER COMBINATIONS OF A PHONE NUMBER                        {T.C = O(2^N), S.C = O(N)}
//STORE KEY, VALUE IN MAP, USE FOR LOOP(0 TO N) THEN PUSH AND POP (INCL & EXCL)
class Solution {
private : 
    void solve(string digits ,vector<string> &ans ,string output ,string mapping[], int i){
        //base case
        if(i >= digits.length()){
            ans.push_back(output);
            return;
        }

        int number = digits[i] - '0';      //char to number
        string value = mapping[number];

        for(int j = 0 ; j <  value.length() ; j++){
            output.push_back(value[j]);
            solve(digits ,ans, output, mapping, i+1);                //i++ not j++
            output.pop_back();                //to backtrack and explore other combos
        }

    }
public:
    vector<string> letterCombinations(string digits) {
        vector<string> ans;
        string output = "";

        if(digits.length() == 0){
            return ans;
        }

        string mapping[10] = {"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};   //0 to 9 (10)
        
        solve(digits ,ans ,output ,mapping, 0);         //0 = starting i
        return ans;
    }
};
/*
Example 1:
Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

Example 2:
Input: digits = ""
Output: []

Example 3:
Input: digits = "2"
Output: ["a","b","c"]
*/


//TRYING OUT ALL COMBOS / HARD ----------------------------------------------------------------------------
//136. PALINDROME PARTITIONING                                            {T.C = O(N*2^N), S.C = O(N*2^N)}
//USE FOR LOOP(I TO N) CHECK IF PALINDROME THEN PUSH AND POP (INCL & EXCL)
class Solution {
public:
    bool isPalindrome(string &s, int i, int j){
        while(i <= j){
            if(s[i] != s[j]){
                return false;
            }
            i++, j--;
        }
        return true;
    }
    void solve(string &s, vector<string>&temp, vector<vector<string>>&ans, int i){
        int n = s.length();
        //base case
        if(i == n){
            ans.push_back(temp);
            return;
        }
        
        //incl & excl
        for(int j = i ; j < n ; j++){
            if(isPalindrome(s, i, j)){
                temp.push_back(s.substr(i, j-i+1));         //{initial index, length of substr}
                solve(s, temp, ans, j+1);
                temp.pop_back();
            }
        }
    }
    vector<vector<string>> partition(string s) {
        vector<string>temp;
        vector<vector<string>>ans;
        solve(s, temp, ans, 0);                     //0 = index
        return ans;
    }
};
/*
Example 1:
Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]

Example 2:
Input: s = "a"
Output: [["a"]]
*/


//137. WORD SEARCH                                                {T.C = O(N*M*4^L), S.C = O(N*M)}
//DFS - ITERATE ON MATRIX(2D) AND EXPLORE ALL DIRECTIONS USING DFS
class Solution {
public:
    bool dfs(vector<vector<char>>& board, string& word, int idx, int i, int j, vector<vector<bool>>& visited) {
        // Base case: Entire word found
        if (idx == word.length()) {
            return true;
        }

        // Boundary check and character match
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || visited[i][j] || board[i][j] != word[idx]) {
            return false;
        }

        // Mark cell as visited
        visited[i][j] = true;

        // Check in all 4 directions               
        bool found = dfs(board, word, idx + 1, i + 1, j, visited) ||
                     dfs(board, word, idx + 1, i - 1, j, visited) ||
                     dfs(board, word, idx + 1, i, j + 1, visited) ||
                     dfs(board, word, idx + 1, i, j - 1, visited);

         //direction vector not working                //it gives TLE
        /*
                for(auto it : directions){
            int newI = i + it[0];
            int newJ = j + it[1];

            if(dfs(board, word, idx+1, newI, newJ, vis)){
                return true;
            }
        }
        */
        
        // Mark cell as unvisited after exploration
        visited[i][j] = false;

        return found;
    }

    bool exist(vector<vector<char>>& board, string word) {
        int row = board.size();
        int col = board[0].size();

        // Initialize a visited matrix to track visited positions
        vector<vector<bool>> visited(row, vector<bool>(col, false));

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (dfs(board, word, 0, i, j, visited)) {
                    return true;
                }
            }
        }
        return false;
    }
};
/*
Example 1:
Input: board = [["A","B","C","E"],
                ["S","F","C","S"],
                ["A","D","E","E"]], 
       word = "ABCCED"
Output: true

Example 2:
Input: board = [["A","B","C","E"],
                ["S","F","C","S"],
                ["A","D","E","E"]], 
       word = "SEE"
Output: true

Example 3:
Input: board = [["A","B","C","E"],
                ["S","F","C","S"],
                ["A","D","E","E"]], 
       word = "ABCB"
Output: false
*/


//138. N QUEENS                                                  {T.C = O(N!), S.C = O(N^2)}
/*
1. every row must have 1 queen
2. every col must hanve 1 queen
3. none have been attack by any other (diagonlly attack can also happen)
*/
//check only 3 directions because we are filling from left to right
/*
    ^
    \      //left-up diagonal
    <- Q     //left row or same row
    /      //left-down diagonal
    V
*/
class Solution {
public:
    bool isSafe(vector<string>&board, int n, int col , int row){
        //left-up diagonal
        int x = row;
        int y = col;
        while(x >= 0 && y >= 0){
            if(board[x][y] == 'Q'){
                return false;
            }
            y--;
            x--;
        }

        //left row or same row
        x = row, y = col;               //reinitialize
        while( y >= 0){
            if(board[x][y] == 'Q'){
                return false;
            }
            y--;
        }

        //left-down diagonal
        x = row, y = col;               //reinitialize
        while(x < n && y >= 0){
            if(board[x][y] == 'Q'){
                return false;
            }
            y--;
            x++;
        }
        
        return true;
    }
    void solve(int n, vector<string>&board, vector<vector<string>>&ans, int col){
        //base case
        if(col == n){
            ans.push_back(board);
            return;
        }

        for(int row = 0 ; row < n ; row++){
            if(isSafe(board, n, col, row)){            //col = i, row = j
                board[row][col] = 'Q';                 //push
                solve(n, board, ans, col+1);
                board[row][col] = '.';                 //pop
            }
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        vector<string>board(n, string(n, '.'));         //board == temp
        vector<vector<string>>ans;
        solve(n, board, ans, 0);                        //0 = initial column / index
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


//139. RAT IN A MAZE PROBLEM                                        {T.C = O(4^N*M), S.C = O(N^M)}
//DFS - ITERATE ON MATRIX(2D) AND EXPLORE ALL DIRECTIONS USING DFS (ADD U, D, L, R)
class Solution{
    public:
    void dfs(vector<vector<int>>&m, int n , vector<string>&ans, vector<vector<int>>&vis, const string &s, int i , int j){
        //base case
        if(i < 0 || j < 0 || i >= n || j >= n || vis[i][j] == 1 || m[i][j] == 0 ){
            return;
        }
        
        if(i == n-1 && j == n-1){
            ans.push_back(s);
            return;
        }
        vis[i][j] = 1;                                      //1st time visit any element mark as 1
        
        //recursive calls in 4 directions
        dfs(m, n, ans, vis, s +'U', i-1, j);
        dfs(m, n, ans, vis, s +'D', i+1, j);
        dfs(m, n, ans, vis, s +'L', i, j-1);
        dfs(m, n, ans, vis, s +'R', i, j+1);
        
        vis[i][j] = 0;                                     //marks 0 after 1 path to again search new path / BACKTRACK
        
    }
    vector<string> findPath(vector<vector<int>> &m, int n) {
        vector<string>ans;
        vector<vector<int>>vis(n, vector<int>(n, 0));
        string s = "";
        dfs(m, n, ans, vis, s, 0, 0);            //0 = i, j
        sort(ans.begin(), ans.end());
        
        return ans ;
    }
};
/*
Example 1:
Input:
N = 4
m[][] = {{1, 0, 0, 0},
         {1, 1, 0, 1}, 
         {1, 1, 0, 0},
         {0, 1, 1, 1}}
Output:
DDRDRR DRDDRR
Explanation:
The rat can reach the destination at 
(3, 3) from (0, 0) by two paths - DRDDRR 
and DDRDRR, when printed in sorted order 
we get DDRDRR DRDDRR.

Example 2:
Input:
N = 2
m[][] = {{1, 0},
         {1, 0}}
Output:
-1
Explanation:
No path exists and destination cell is 
blocked.
*/


//140. WORD BREAK
//RECURSION                                                    {T.C = O(2^N), S.C = O(N)}
//STORE DICT STRINGS INTO SET(FAST FETCH) FOR LOOP (J = I : N) ? ST.FIND(TEMP) ? SOLVE(J+1): TRUE
class Solution {
public:
    bool solve(string s, unordered_set<string>&st, int i){
        int n = s.length();
        //base case
        if(i == n){
            return true;
        }

        string temp = "";
        for(int j = i ; j < s.size() ; j++){
            temp += s[j];
            if(st.find(temp) != st.end()){
                if(solve(s, st, j+1)){
                    return true;
                }
            }
        }
        return false;
    }
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string>st;
        int n = s.size();
        for(auto it : wordDict){
            st.insert(it);
        }
        return solve(s, st, 0);            //0 = initial i
    }
};

//DP (MEMOIZATION)                                                  {T.C = O(N), S.C = O(N)}
class Solution {
public:
    bool solveMem(int index , string s, unordered_set<string>&st, vector<int>&dp){
        //base case
        if(index == s.size()){
            return true;
        }

        //step3 if ans already present return it
        if(dp[index] != -1){
            return dp[index];
        }

        //step2 recursive call
        string temp;
        for(int i = index ; i < s.size() ; i++){
            temp += s[i];
            if(st.find(temp) != st.end()){
                if(solveMem(i+1, s, st, dp)){
                    return dp[index] = true;
                }
            }
        }
        dp[index] = false;
        return dp[index];
    }
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string>st;
        int n = s.size();
        //step1 create a dp vector
        vector<int>dp(n+1, -1);
        for(auto it : wordDict){
            st.insert(it);
        }
        return solveMem(0, s, st, dp);            //0 = initial index
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


//141. M COLORING PROBLEM                                                     {T.C = O(M^N*N^2), S.C = O(N)}
//DFS
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


//142. SUDOKU SOLVER                                                       {T.C = O(9^N), S.C = O(N)}
//TRAVERSE ON MATRIX IF IS VALID (3 CONDITIONS) PUT ELSE RECURSIVE CALLS
class Solution {
public:
    bool isValid(vector<vector<char>>&board, int row , int col, int ch){
        for(int i = 0 ; i < 9 ; i++){
            if(board[row][i] == ch){                            //check all cols have ch or not
                return false;
            }
            if(board[i][col] == ch){                            //check all rows have ch or not
                return false;
            }
            if(board[3*(row/3) + i/3][3*(col/3) + i % 3] == ch){//check all 3x3 sub boxes have ch or not
                return false;
            }
        }
        return true;
    }
    bool solve(vector<vector<char>>&board){
        for(int i = 0 ; i < board.size(); i++){
            for(int j = 0 ; j < board[0].size() ; j++){
                if(board[i][j] == '.'){
                    for(char ch = '1' ; ch <= '9' ; ch++){
                        if(isValid(board, i, j, ch)){
                            board[i][j] = ch;
                            if(solve(board) == true){
                                return true;
                            }
                            board[i][j] = '.';
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
Example 1:
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


//143. EXPRESSION ADD OPERATORS                                                   {T.C = O(N*4^N), S.C = O(N)}
//DFS
class Solution {
public:
    void dfs(string &num, int target, vector<string>& ans, string path, int64_t temp, int64_t prevNum, int i) {
        int n = num.length();
        // Base case
        if (i == n) {
            if (temp == target) {
                ans.push_back(path);
                return;
            }
        }
        for (int j = i; j < n; j++) {
            if (j > i && num[i] == '0') {  // Skip leading zeroes
                break;
            }
            int64_t currNum;
            try {
                currNum = stoll(num.substr(i, j - i + 1));  // stoll = string to long long
            } catch (const out_of_range& e) {
                // Handle the case where the number is out of the range for int64_t
                break;
            } catch (const invalid_argument& e) {
                // Handle the case where the conversion is invalid
                break;
            }

            if (i == 0) {
                dfs(num, target, ans, path + to_string(currNum), currNum, currNum, j + 1);
            } else {
                dfs(num, target, ans, path + "+" + to_string(currNum), temp + currNum, currNum, j + 1);
                dfs(num, target, ans, path + "-" + to_string(currNum), temp - currNum, -currNum, j + 1);
                dfs(num, target, ans, path + "*" + to_string(currNum), temp - prevNum + prevNum * currNum, prevNum * currNum, j + 1);
            }
        }
    }

    vector<string> addOperators(string num, int target) {
        vector<string> ans;
        dfs(num, target, ans, "", 0, 0, 0);  // "" = path, 0 = temp(ans), 0 = prevNum, 0 = index
        return ans;
    }
};
/*
Example 1:
Input: num = "123", target = 6
Output: ["1*2*3","1+2+3"]
Explanation: Both "1*2*3" and "1+2+3" evaluate to 6.

Example 2:
Input: num = "232", target = 8
Output: ["2*3+2","2+3*2"]
Explanation: Both "2*3+2" and "2+3*2" evaluate to 8.

Example 3:
Input: num = "3456237490", target = 9191
Output: []
Explanation: There are no expressions that can be created from "3456237490" to evaluate to 9191.
*/


/*--------------------------------------------------------- THE END ----------------------------------------------------------------*/