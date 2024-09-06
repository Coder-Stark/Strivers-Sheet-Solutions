#include<bits/stdc++.h>
using namespace std;


//DAY 9: RECURSION -----------------------------------------------------------------------------------------------------
//49. SUBSET SUM                                                              {T.C = O(2^N), S.C = O(N)}
class Solution {
  public:
    void solve(vector<int>&arr, vector<int>&ans, int sum, int i){
        int n = arr.size();
        if(i == n){
            ans.push_back(sum);
            return;
        }
        
        solve(arr, ans, sum+arr[i], i+1);         //incl
        solve(arr, ans, sum, i+1);                //excl
    }
    vector<int> subsetSums(vector<int> arr, int n) {
        vector<int>ans;
        solve(arr, ans,  0, 0);           //0 = initial index, 0 = sum
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


//50. SUBSETS II                                                               {T.C = O(2^N), S.C = O(N*M)}
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
        temp.pop_back();                              //backtrack

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


//51. COMBINATION SUM                                                     {T.C = O(2^N), S.C = O(N)}
class Solution {
public:
    void solve(vector<int>&cand, int target, vector<vector<int>>&ans, vector<int>&temp, int i){
        int n = cand.size();
        //base case
        if(target == 0){
            ans.push_back(temp);
            return;
        }
        if(i >= n || target < 0) return;
        
        temp.push_back(cand[i]);
        solve(cand, target-cand[i], ans, temp, i);     //same element can be use
        temp.pop_back();
        solve(cand, target, ans, temp, i+1);
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>>ans;
        vector<int>temp;
        sort(candidates.begin(), candidates.end());
        solve(candidates, target, ans, temp, 0);
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


//52. COMBINATION SUM II (DISTINCT ELEMENT)                                {T.C = O(2^N*K), S.C = O(N)}
class Solution {
public:
    void solve(vector<int>&cand, int target, vector<vector<int>>&ans, vector<int>&temp, int idx){
        int n = cand.size();
        //base case
        if(target == 0){
            ans.push_back(temp);
            return;
        }
        if(idx >= n || target < 0) return;

        //incl & excl with not same element
        for(int i = idx ; i < n ; i++){
            if(i > idx && cand[i] == cand[i-1]) continue;       //skip same element

            temp.push_back(cand[i]);
            solve(cand, target-cand[i], ans, temp, i+1);
            temp.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>>ans;
        vector<int>temp;
        sort(candidates.begin(), candidates.end());             //for disqualify same element
        solve(candidates, target, ans, temp, 0);
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


//53. PALINDROME PARTITIONING                                             {T.C = O(2^N), S.C = O(N)}
class Solution {
public:
    bool isPalindrome(string &s, int i, int j){
        while(i < j){
            if(s[i] != s[j]) return false;
            i++, j--;
        }
        return true;
    }
    void solve(string &s, vector<vector<string>>&ans, vector<string>&temp, int i){
        int n = s.length();
        //base case
        if(i == n) return ans.push_back(temp);

        //incl & excl
        for(int j = i ; j < n; j++){
            if(isPalindrome(s, i, j)){
                temp.push_back(s.substr(i, j-i+1));
                solve(s, ans, temp, j+1);                 //j+1 for next index
                temp.pop_back();                          //backtrack
            } 
        }
    }
    vector<vector<string>> partition(string s) {
        vector<vector<string>>ans;
        vector<string>temp;
        int n = s.length();
        solve(s, ans, temp, 0);
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


//54. PERMUTATION SEQUENCE                                                   {T.C = O(N^2), S.C = O(N)}
class Solution {
public:
    string getPermutation(int n, int k) {
        int fact = 1;
        vector<int>num;
        for(int i = 1; i < n ; i++){        //find total permutation
            fact = fact*i;
            num.push_back(i);
        }
        num.push_back(n);
        string ans = "";
        k = k-1;                           //0 based indexing
        while(true){
            ans += to_string(num[k/fact]);
            num.erase(num.begin() + k/fact);
            if(num.size() == 0) break;
            k = k % fact;
            fact = fact / num.size(); 
        }
        return ans;
    }
};
/*
Example 1:
Input: n = 3, k = 3
Output: "213"

Example 2:
Input: n = 4, k = 9
Output: "2314"

Example 3:
Input: n = 3, k = 1
Output: "123"
*/