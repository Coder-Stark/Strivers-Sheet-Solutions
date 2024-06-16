//SLIDING WINDOW AND TWO POINTERS COMBINED PROBLEM

#include<bits/stdc++.h>
using namespace std;


//MEDIUM PROBLEMS---------------------------------------------------------------------------------------
//192. LONGEST SUBSTRING WITHOUT REPEATING CHARACTERS              {T.C = O(N), S.C = O(N)}
//USE SET(UNIQUE), NOT PRESENT -INSERT(SEARCH MAXLEN), PRESENT(REMOVE FROM BACKWORD)
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int i = 0, j = 0, n = s.length();
        unordered_set<int>unSt;
        int maxLen = 0;
        while(j < n){
            if(!unSt.count(s[j])){
                unSt.insert(s[j]);
                maxLen = max(maxLen, j-i+1);            //maxwindow size
                j++;
            }else{  //unSt.count(s[j])
                while(unSt.count(s[j])){
                    unSt.erase(s[i]);
                    i++;
                }
            }
        }   
        return maxLen;
    }
};
/*
Example 1:
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Example 2:
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
*/


//193. MAX CONSECUTIVE ONES                              {T.C = O(N), S.C = O(1)}
//COUNT ZERO (IF COUNT > K) SHRINK WINDO, FIND MAXLEN(J-I+1)
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size();
        int zeroCount = 0;
        int i = 0, j = 0, maxLen = 0;
        while(j < n){
            if(nums[j] == 0){
                zeroCount++;
            }
            while(zeroCount > k){               //shrink window
                if(nums[i] == 0){
                    zeroCount--;
                }
                i++;
            }
            maxLen = max(maxLen, j-i+1);
            j++;
        }
        return maxLen;
    }
};
/*
Example 1:
Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
Output: 6
Explanation: [1,1,1,0,0,1,1,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.

Example 2:
Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
Output: 10
Explanation: [0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.
*/


//194. FRUITS INTO BASKETS
//BRUTE FORCE (USE SET(UNIQUE), CHECK ALL SUBARRAY, FIND MAXLEN(J-I+1))    {T.C = O(N^2), S.C = O(N)}
class Solution {
  public:
    int totalFruits(int N, vector<int> &fruits) {
        int maxLen = 0;
        for(int i = 0 ; i < N ; i++){
            unordered_set<int>st;                        //set use (because each subarray handle independently)
            for(int j = i ; j < N ; j++){
                st.insert(fruits[j]);
                if(st.size() <= 2){
                    maxLen = max(maxLen, j-i+1);
                }else{
                    break;
                }
            }
        }
        return maxLen;
    }
};

//OPTIMIZED (USING MAP) & SLIDING WINDOW                       {T.C = O(N), S.C = O(N)}
class Solution {
  public:
    int totalFruits(int N, vector<int> &fruits) {
        int n = fruits.size();
        int i = 0, j = 0, maxLen = 0;
        unordered_map<int, int>mp;
        while(j < n){
            mp[fruits[j]]++;
            
            if(mp.size() <= 2){
                maxLen = max(maxLen, j-i+1);
            }else{
                while(mp.size() > 2){
                    mp[fruits[i]]--;
                    if(mp[fruits[i]] == 0){
                        mp.erase(fruits[i]);
                    }
                    i++;
                }
            }
            j++;
        }
        return maxLen;
    }
};
/*
Example 1:
Input:
N = 3
fruits [ ] = { 2, 1, 2 }
Output: 3
Explanation: We can pick from all three trees. 

Example 2:
Input:
N = 6
fruits [ ] = { 0, 1, 2, 2, 2, 2 }
Output: 5
Explanation: It's optimal to pick from trees(0-indexed) [1,2,3,4,5].
*/


//195. LONGEST REPEATING CHARACTER REPLACEMENT               {T.C = O(N), S.C = O(N or 26)}
//KEEP TRACK OF MAX FREQ , CHECK WINDOW-MAXFREQ (MAXLEN ) ELSE SHRINK WINDOW
class Solution {
public:
    int characterReplacement(string s, int k) {
        int n = s.length();
        int i = 0, j = 0;
        int maxFreq = 0;
        int maxLen = 0;
        unordered_map<char, int>mp;
        while(j < n){
            mp[s[j]]++;
            maxFreq = max(maxFreq, mp[s[j]]);     //keep count of freq changed or have to change
            if((j-i+1)-maxFreq <= k){
                maxLen = max(maxLen, j-i+1);
            }else{
                mp[s[i]]--;
                if(mp[s[i]] == 0){
                    mp.erase(s[i]);
                }
                i++;
            }
            j++;
        }
        return maxLen;
    }
};

//USING FREQ VECTOR(CONSTANT SPACE (VECTOR(26 SIZE)))        {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int characterReplacement(string s, int k) {
        int n = s.length();
        int i = 0, j = 0;
        int maxFreq = 0;
        int maxLen = 0;
        vector<int>freq(26, 0);
        while(j < n){
            freq[s[j]-'A']++;
            maxFreq = max(maxFreq, freq[s[j]-'A']);     //keep count of freq changed or have to change
            if((j-i+1)-maxFreq <= k){
                maxLen = max(maxLen, j-i+1);
            }else{
                freq[s[i]-'A']--;
                i++;
            }
            j++;
        }
        return maxLen;
    }
};
/*
Example 1:
Input: s = "ABAB", k = 2
Output: 4
Explanation: Replace the two 'A's with two 'B's or vice versa.

Example 2:
Input: s = "AABABBA", k = 1
Output: 4
Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.
There may exists other ways to achieve this answer too.
*/


//196. BINARY SUBARRAYS WITH SUM    
//THIS APPROACH NOT WORK FOR (-VE) NUMBERS                           
//USING SLIDING WINDOW (SOLVE(N)-SOLVE(N-1) {FINDING SUBARRAY OF SUM <= K}) {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int solve(vector<int>&nums, int goal){       //find subarrays sum <= k 
        int n = nums.size();
        int i = 0, j = 0;
        int sum = 0;
        
        //base case                             //handle when goal = 0 (solve(0)-solve(-1){not possible})
        if(goal < 0){           
            return 0;
        }
        int totalSubArrCount = 0;
        while(j < n){
            sum += nums[j];

            while(sum > goal){
                sum -= nums[i];
                i++;
            }
            
            totalSubArrCount += (j-i+1);      //add length (in between length all subarray count)
            j++;
        }
        return totalSubArrCount;
    }
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        return solve(nums, goal)-solve(nums, goal-1);
    }
};

//196a. SUBARRAY SUM EQUALS K
//USING PREFIXSUM
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int>mp;                 //prefixSum                   
        // mp.insert({0, 1});                      //initialize 0 (edge case)
        mp[0] = 1;
        int sum = 0;
        int ans = 0;
        for(int i = 0 ; i < n ; i++){
            sum += nums[i];
            if(mp.count(sum-k)){
                ans += mp[sum-k];               //add freq not 1
            }
            mp[sum]++;
        }
        return ans;
    }
};

//196b. SAME AS ABOVE
//USE PREFIX SUM (NORMAL SLIDING WINDOW WILL FAIL)              {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        unordered_map<int, int>mp;            //{sum, val}
        mp[0] = 1;                            //input 0 1 only
        int currSum = 0;
        int totalSubArrCount = 0;
        for(auto it : nums){
            currSum += it;
            if(mp.count(currSum-goal)){
                totalSubArrCount += mp[currSum-goal];
            }
            mp[currSum]++;
        }
        return totalSubArrCount;
    }
};
/*
Example 1:
Input: nums = [1,0,1,0,1], goal = 2
Output: 4
Explanation: The 4 subarrays are bolded and underlined below:
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]

Example 2:
Input: nums = [0,0,0,0,0], goal = 0
Output: 15
*/


//SAME AS ABOVE                     
//197. COUNT NUMBER OF NICE SUBARRAYS        
//USING SLIDING WINDOW
class Solution {
public:
    int solve(vector<int>&nums, int k){
        int n = nums.size();
        int i = 0 , j = 0;
        int sum = 0;
        int totalSubArrCount = 0;
        while(j < n){
            sum += nums[j] % 2;                 //if

            while(sum > k){
                sum -= nums[i] % 2;
                i++;
            }
            totalSubArrCount += (j-i+1);
            j++;
        }
        return totalSubArrCount;
    }
    int numberOfSubarrays(vector<int>& nums, int k) {
        return solve(nums, k) - solve(nums, k-1);
    }
};

//USING PREFIXSUM                                            {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        int oddCount = 0;
        int totalSubArrCount = 0;
        unordered_map<int,int>mp;                       //prefixCount (prefixSum)
        mp[0] = 1;                                      //zero odd number with start
        for(auto it : nums){
            if(it % 2 != 0){
                oddCount++;
            }
            if(mp.count(oddCount-k)){
                totalSubArrCount += mp[oddCount-k];
            }
            mp[oddCount]++;
        }
        return totalSubArrCount;
    }
};
/*
Example 1:
Input: nums = [1,1,2,1,1], k = 3
Output: 2
Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].

Example 2:
Input: nums = [2,4,6], k = 1
Output: 0
Explanation: There is no odd numbers in the array.

Example 3:
Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2
Output: 16
*/


//198. NUMBER OF SUBSTRINGS CONTAINING ALL THREE CHARACTERS(ABC)   
//{T.C = O(N^2), S.C = O(1)}
//BRUTE FORCE (FREQ ARR, FREQ[CHAR-'A'] = Acount, FREQ[CHAR-'B'] = Bcount , FREQ[CHAR-'C'] = Ccount) == 3 count++
class Solution {
public:
    int numberOfSubstrings(string s) {
        int n = s.length();
        int count = 0;
        for(int i = 0 ; i < n ; i++){
            vector<int>freq(3, 0);                      //string only contains a b c
            for(int j = i ; j < n ; j++){
                freq[s[j]-'a'] = 1;
                if(freq[0]+freq[1]+freq[2] == 3){       //all abc present
                    count++;
                }
            }
        }
        return count;
    }
};

//USING SLIDING WINDOW                                 {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int numberOfSubstrings(string s) {
        int n = s.length();
        int i = 0 , j = 0;
        int count = 0;
        vector<int>freq(3, 0);
        while(j < n){
            freq[s[j]-'a']++;
            while(freq[0] > 0 && freq[1] > 0  && freq[2] > 0){    //a, b , c ? count > 0
                freq[s[i]-'a']--;
                count += (n-j);                        //find min window else already contains abc
                i++;

            }
            j++;
        }
        return count;
    }
};
/*
Example 1:
Input: s = "abcabc"
Output: 10
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again). 

Example 2:
Input: s = "aaacb"
Output: 3
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "aaacb", "aacb" and "acb". 

Example 3:
Input: s = "abc"
Output: 1
*/


//199. MAXIMUM POINTS YOU CAN OBTAINED FROM CARD           {T.C = O(N), S.C = O(1)}
//USE SIMPLE SLIDING WINDOW (STORE SUM ), SKIP N-K SUM AND REDUCE OR SHRINK FROM WINDOW
class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n = cardPoints.size();
        int i = 0 , j = 0;
        int sum = 0;
        int ans = 0;
        int totalSum = 0;
        for(int i = 0 ; i < n ; i++){
            totalSum += cardPoints[i];
        }
        if(k == n){                                 //all can be pop out
            return totalSum;
        }

        while(j < n){
            sum += cardPoints[j];
            if(j-i+1 < n-k){                       //skip n-k (all skip except 1st and last)
                j++;
            }else{
                ans = max(ans, totalSum-sum);   
                sum -= cardPoints[i];
                i++;
                j++;
            }
        }

        return ans;
    }
};
/*
Example 1:
Input: cardPoints = [1,2,3,4,5,6,1], k = 3
Output: 12
Explanation: After the first step, your score will always be 1. However, choosing the rightmost card first will maximize your total score. The optimal strategy is to take the three cards on the right, giving a final score of 1 + 6 + 5 = 12.

Example 2:
Input: cardPoints = [2,2,2], k = 2
Output: 4
Explanation: Regardless of which two cards you take, your score will always be 4.

Example 3:
Input: cardPoints = [9,7,7,9,7,7,9], k = 7
Output: 55
Explanation: You have to take all the cards. Your score is the sum of points of all cards.
*/


//HARD PROBLEMS----------------------------------------------------------------------------------------
//200. LONGEST SUBSTRINGS ATMOST K DISTINCT CHARACTERS           {T.C = O(N), S.C = O(N)}
//USE MAP, IF MPSIZE > K SHRINK WINDOW
class Solution{
  public:
    int longestKSubstr(string s, int k) {
        int n = s.length();
        int i = 0, j = 0;
        unordered_map<char,int>mp;
        int maxLen = -1;                            //return -1 if not found
        while(j < n){
            mp[s[j]]++;
            
            if(mp.size() == k){
                maxLen = max(maxLen, j-i+1);
            }
            while(mp.size() > k){
                mp[s[i]]--;
                if(mp[s[i]] == 0){
                    mp.erase(s[i]);
                }
                i++;
            }
            j++;
        }
        return maxLen;
    }
};
/*
Example 1:
Input:
S = "aabacbebebe", K = 3
Output: 
7
Explanation: 
"cbebebe" is the longest substring with 3 distinct characters.

Example 2:
Input: 
S = "aaaa", K = 2
Output: -1
Explanation: 
There's no substring with 2 distinct characters.
*/


//201. SUBARRAYS WITH K DIFFERENT INTEGERS                   {T.C = O(N), S.C = O(N)}
//FIND SUBARRAY (K & K-1) THEN SUBTRACT IT FOR FIND EXACT K
class Solution {
public:
    int solve(vector<int>&nums, int k){
        int n = nums.size();
        int i = 0, j = 0;
        int count = 0;
        unordered_map<int,int>mp;
        while(j < n){
            mp[nums[j]]++;
            while(mp.size() > k){
                mp[nums[i]]--;
                if(mp[nums[i]] == 0){
                    mp.erase(nums[i]);
                }
                i++;
            }
            count += (j-i+1);
            j++;
        }
        return count;
    }
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return solve(nums, k)-solve(nums, k-1);
    }
};
/*
Example 1:
Input: nums = [1,2,1,2,3], k = 2
Output: 7
Explanation: Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2]

Example 2:
Input: nums = [1,2,1,3,4], k = 3
Output: 3
Explanation: Subarrays formed with exactly 3 different integers: [1,2,1,3], [2,1,3], [1,3,4].
*/


//202. MINIMUM WINDOW SUBSTRING                             {T.C = O(N), S.C = O(N)}
//STORE T IN MAP, COUNT OF CHAR OF T IS > 0 IN S COUNT++ , ELSE MP--, IF COUNT == M, FIND MINLEN
class Solution {
public:
    string minWindow(string s, string t) {
        int n = s.length(), m = t.length();
        if(m > n){
            return "";
        }
        int reqCount = m;
        int i = 0, j = 0;
        int startIdx = 0;
        int minWin = INT_MAX;
        unordered_map<char,int>mp;
        for(auto it : t){
            mp[it]++;
        }
        while(j < n){
            if(mp[s[j]] > 0){                  //required (essential char)
                reqCount--;
            }
            mp[s[j]]--;
            while(reqCount == 0){             //all char found now shrink window
                int currWin = (j-i+1);
                if(currWin < minWin){
                    minWin = currWin;
                    startIdx = i;
                }
                mp[s[i]]++;
                if(mp[s[i]] > 0){            //essential char removed , req++
                    reqCount++;
                }
                i++;
            }
            j++;
        }
        return minWin == INT_MAX ? "" : s.substr(startIdx, minWin);    //(i to minlen)
    }
};
/*
Example 1:
Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.

Example 2:
Input: s = "a", t = "a"
Output: "a"
Explanation: The entire string s is the minimum window.

Example 3:
Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.
*/


//203. MINIMUM WINDOW SUBSEQUENCES                            {T.C = O(N), S.C = O(N)}
//COPIED
class Solution {
  public:
    string minWindow(string s1, string s2) {
        int n = s1.length(), m = s2.length();
        int minWin = INT_MAX, startIdx = -1;
        
        for(int i = 0; i <= n - m; i++){
            if(s1[i] != s2[0]){
                continue;
            }
            else{
                int p = i, j = 0;
                while(p < n && j < m){
                    if(s1[p] == s2[j]){
                        j++;
                    }
                    p++;
                }
                p--;
                int cur = p - i + 1;
                if(j == m && cur < minWin){
                    minWin = cur;
                    startIdx = i;
                }
            }
        }
        
        return startIdx == -1 ? "" : s1.substr(startIdx, minWin);
    }
};
/*
Example 1:
Input: 
str1: geeksforgeeks
str2: eksrg
Output: 
eksforg
Explanation: 
"eksforg" satisfies all required conditions. str2 is its subsequence and it is longest and leftmost among all possible valid substrings of str1.

Example 2:
Input: 
str1: abcdebdde 
str2: bde 
Output:  bcde 
Explanation:  "bcde" is the answer and "deb" is not a smaller window because the elements in the window must occur in order.
*/


/*-----------------------------------------THE END-----------------------------------------------------*/