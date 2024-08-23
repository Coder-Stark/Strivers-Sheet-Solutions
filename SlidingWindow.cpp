//SLIDING WINDOW

#include<bits/stdc++.h>
using namespace std;

//01. MAXIMUM STRONG PAIR XOR I                                          {T.C = O(N^2), S.C = O(1)}                    
//BRUTE FORCE
class Solution {
public:
    int maximumStrongPairXor(vector<int>& nums) {
        int n = nums.size();
        int maxXor = 0;
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                if(abs(nums[i]-nums[j]) <= min(nums[i], nums[j])){
                    maxXor = max(maxXor, nums[i]^nums[j]);
                }
            }
        }
        return maxXor;
    }
};
/*
Example 1:
Input: nums = [1,2,3,4,5]
Output: 7
Explanation: There are 11 strong pairs in the array nums: (1, 1), (1, 2), (2, 2), (2, 3), (2, 4), (3, 3), (3, 4), (3, 5), (4, 4), (4, 5) and (5, 5).
The maximum XOR possible from these pairs is 3 XOR 4 = 7.

Example 2:
Input: nums = [10,100]
Output: 0
Explanation: There are 2 strong pairs in the array nums: (10, 10) and (100, 100).
The maximum XOR possible from these pairs is 10 XOR 10 = 0 since the pair (100, 100) also gives 100 XOR 100 = 0.

Example 3:
Input: nums = [5,6,25,30]
Output: 7
Explanation: There are 6 strong pairs in the array nums: (5, 5), (5, 6), (6, 6), (25, 25), (25, 30) and (30, 30).
The maximum XOR possible from these pairs is 25 XOR 30 = 7 since the only other non-zero XOR value is 5 XOR 6 = 3.
*/


//02. SUBSTRING OF SIZE 3(K) WITH DISTINCT CHARACTERS                           {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int countGoodSubstrings(string s) {
        int k = 3, n = s.length();
        int i = 0, j = 0;
        unordered_map<int,int>mp;
        int count = 0;
        while(j < n){
            mp[s[j]]++;
            if(j-i+1 == k){
                if(mp.size() == k) count++;                 //all unique(mp size == 3)

                mp[s[i]]--;                                 //slide window
                if(mp[s[i]] == 0) mp.erase(s[i]);
                i++;
            }
            j++;
        }
        return count;
    }
};
/*
Example 1:
Input: s = "xyzzaz"
Output: 1
Explanation: There are 4 substrings of size 3: "xyz", "yzz", "zza", and "zaz". 
The only good substring of length 3 is "xyz".

Example 2:
Input: s = "aababcabc"
Output: 4
Explanation: There are 7 substrings of size 3: "aab", "aba", "bab", "abc", "bca", "cab", and "abc".
The good substrings are "abc", "bca", "cab", and "abc".
*/


//03. ALTERNATING GROUP I                                                 {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int numberOfAlternatingGroups(vector<int>& colors) {
        int n = colors.size();
        int count = 0;
        for(int i = 0 ; i < n ; i++){
            int prevIdx = (i-1+n) % n;               //circular (last - 1 + n = first)
            int nextIdx = (i+1) % n;
            if(colors[prevIdx] != colors[i] && colors[i] != colors[nextIdx]) count++;
        }
        return count;
    }
};
/*
Example 1:
Input: colors = [1,1,1]
Output: 0

Example 2:
Input: colors = [0,1,0,0,1]
Output: 3
*/


//04. DEFUSE THE BOMB                                                      {T.C = O(N*K), S.C = O(N)}
class Solution {
public:
    vector<int> decrypt(vector<int>& code, int k) {
        int n = code.size();
        vector<int>ans(n, 0);
        if(k == 0) return ans;

        for(int i = 0 ; i < n ; i++){
            int sum = 0, count = k , j = 0;
            if(k > 0){
                j = i+1;                           //nextIdx
                while(count--){
                    sum += code[j % n];
                    j++;
                }
            }else{ //k < 0
                j = i-1+n;                          //prevIdx
                while(count++){
                    sum += code[j % n];
                    j--;
                }
            }
            ans[i] = sum;
        }
        return ans;
    }
};
/*
Example 1:
Input: code = [5,7,1,4], k = 3
Output: [12,10,16,13]
Explanation: Each number is replaced by the sum of the next 3 numbers. The decrypted code is [7+1+4, 1+4+5, 4+5+7, 5+7+1]. Notice that the numbers wrap around.

Example 2:
Input: code = [1,2,3,4], k = 0
Output: [0,0,0,0]
Explanation: When k is zero, the numbers are replaced by 0. 

Example 3:
Input: code = [2,4,9,3], k = -2
Output: [12,5,6,13]
Explanation: The decrypted code is [3+9, 2+3, 4+2, 9+4]. Notice that the numbers wrap around again. If k is negative, the sum is of the previous numbers.
*/


//05. MAXIMUM LENGTH SUBSTRING WITH TWO OCCURRENCES                                {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int maximumLengthSubstring(string s) {
        int n = s.length();
        unordered_map<char, int>mp;
        int i = 0, j = 0;
        int maxLen = 0;
        while(j < n){
            mp[s[j]]++;
            while(mp[s[j]] == 3){                         //slide window
                mp[s[i]]--;
                i++;
            }
            maxLen = max(maxLen, j-i+1);                 //at most 2 (0, 1 , 2 ) occurance included
            j++;
        }
        return maxLen;
    }
};
/*
Example 1:
Input: s = "bcbbbcba"
Output: 4
Explanation:
The following substring has a length of 4 and contains at most two occurrences of each character: "bcbbbcba".

Example 2:
Input: s = "aaaa"
Output: 2
Explanation:
The following substring has a length of 2 and contains at most two occurrences of each character: "aaaa".
*/


//06. LONGEST NICE SUBSTRING                                              {T.C = O(N^2), S.C = O(N)}
class Solution {
public:
    bool isNice(vector<int>&upperCase, vector<int>&lowerCase){
        for(int i = 0 ;  i < 26 ; i++){
            if(upperCase[i] != 0 && lowerCase[i] == 0) return false;
            if(upperCase[i] == 0 && lowerCase[i] != 0) return false;
        }
        return true;
    }
    string longestNiceSubstring(string s) {
        string ans = "";
        int n = s.length();
        for(int i = 0 ; i < n ; i++){
            vector<int>upperCase(26, 0), lowerCase(26, 0);
            string currAns = "";
            for(int j = i ; j < n ; j++){
                currAns += s[j];
                if(s[j] >= 'A' && s[j] <= 'Z') upperCase[s[j]-'A']++;
                if(s[j] >= 'a' && s[j] <= 'z') lowerCase[s[j]-'a']++;
                if(isNice(upperCase, lowerCase) && ans.size() < currAns.size()) ans = currAns;
            }
        }
        return ans;
    }
};
/*
Example 1:
Input: s = "YazaAay"
Output: "aAa"
Explanation: "aAa" is a nice string because 'A/a' is the only letter of the alphabet in s, and both 'A' and 'a' appear.
"aAa" is the longest nice substring.

Example 2:
Input: s = "Bb"
Output: "Bb"
Explanation: "Bb" is a nice string because both 'B' and 'b' appear. The whole string is a substring.

Example 3:
Input: s = "c"
Output: ""
Explanation: There are no nice substrings.
*/


//07. FIND THE KTH BEAUTY OF A NUMBER                                       {T.C = O(N*K), S.C = O(N)}
class Solution {
public:
    int divisorSubstrings(int num, int k) {
        string str = to_string(num);

        int i = 0, j = 0, n = str.length();
        int count = 0;
        while(j < n){
            if(j-i+1 == k){
                int subDigit = stoi(str.substr(i, j-i+1));                //or (i, k)
                if(subDigit != 0 && num % subDigit == 0) count++;
                i++;
            }
            j++;
        }
        return count;
    }
};
/*
Example 1:
Input: num = 240, k = 2
Output: 2
Explanation: The following are the substrings of num of length k:
- "24" from "240": 24 is a divisor of 240.
- "40" from "240": 40 is a divisor of 240.
Therefore, the k-beauty is 2.

Example 2:
Input: num = 430043, k = 2
Output: 2
Explanation: The following are the substrings of num of length k:
- "43" from "430043": 43 is a divisor of 430043.
- "30" from "430043": 30 is not a divisor of 430043.
- "00" from "430043": 0 is not a divisor of 430043.
- "04" from "430043": 4 is not a divisor of 430043.
- "43" from "430043": 43 is a divisor of 430043.
Therefore, the k-beauty is 2.
*/


//08. MINIMUM RECOLORS TO GET K CONSECUTIVE BLACK BLOCKS                        {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int minimumRecolors(string blocks, int k) {
        int n = blocks.size();
        int i = 0, j = 0;
        int count = 0, minCount = INT_MAX;
        while(j < n){
            if(blocks[j] == 'W') count++;

            if(j-i+1 == k){
                minCount = min(minCount, count);
                if(blocks[i] == 'W') count--;
                i++;
            }
            j++;
        }
        return minCount;
    }
};
/*
Example 1:
Input: blocks = "WBBWWBBWBW", k = 7
Output: 3
Explanation:
One way to achieve 7 consecutive black blocks is to recolor the 0th, 3rd, and 4th blocks
so that blocks = "BBBBBBBWBW". 
It can be shown that there is no way to achieve 7 consecutive black blocks in less than 3 operations.
Therefore, we return 3.

Example 2:
Input: blocks = "WBWBBBW", k = 2
Output: 0
Explanation:
No changes need to be made, since 2 consecutive black blocks already exist.
Therefore, we return 0.
*/


//09. MINIMUM DIFFERENCE BETWEEN HIGHEST AND LOWEST OF K SCORES                {T.C = O(N*LOGN), S.C = O(1)}
class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        int n = nums.size();
        //base case
        if(k == 1) return 0;
        sort(nums.begin(), nums.end());
        int minDiff = INT_MAX;
        int i = 0, j = 0;
        while(j < n){
            if(j-i+1 == k){
                minDiff = min(minDiff, nums[j]-nums[i]);      //nums[j] = max, nums[i] = min
                i++;
            }
            j++;
        }
        return minDiff;
    }
};
/*
Example 1:
Input: nums = [90], k = 1
Output: 0
Explanation: There is one way to pick score(s) of one student:
- [90]. The difference between the highest and lowest score is 90 - 90 = 0.
The minimum possible difference is 0.

Example 2:
Input: nums = [9,4,1,7], k = 2
Output: 2
Explanation: There are six ways to pick score(s) of two students:
- [9,4,1,7]. The difference between the highest and lowest score is 9 - 4 = 5.
- [9,4,1,7]. The difference between the highest and lowest score is 9 - 1 = 8.
- [9,4,1,7]. The difference between the highest and lowest score is 9 - 7 = 2.
- [9,4,1,7]. The difference between the highest and lowest score is 4 - 1 = 3.
- [9,4,1,7]. The difference between the highest and lowest score is 7 - 4 = 3.
- [9,4,1,7]. The difference between the highest and lowest score is 7 - 1 = 6.
The minimum possible difference is 2.
*/


//10. LONGEST HARMONIOUS SUBSEQUENCE                                   {T.C = O(N*LOGN), S.C = O(1)}
class Solution {
public:
    int findLHS(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int i = 0, j = 0, maxLen = 0;
        while(j < n){
            if(nums[j]-nums[i] == 1) maxLen = max(maxLen, j-i+1);
            while(nums[j]-nums[i] > 1) i++;                     //Shrink window
            j++;
        }
        return maxLen;
    }
};
/*
Example 1:
Input: nums = [1,3,2,2,5,2,3,7]
Output: 5
Explanation: The longest harmonious subsequence is [3,2,2,2,3].

Example 2:
Input: nums = [1,2,3,4]
Output: 2

Example 3:
Input: nums = [1,1,1,1]
Output: 0
*/


//11. CONTAINS DUPLICATE II                                                   {T.C = O(N), S.C = O(N)}
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_set<int>st;
        int i = 0, j = 0;
        while(j < n){
            if(abs(j-i) > k){            //shrink window
                st.erase(nums[i]);
                i++;
            }
            if(st.count(nums[j])) return true;     //find prev return true(nums[i] == nums[j])
            st.insert(nums[j]);
            j++;
        }
        return false;
    }
};
/*
Example 1:
Input: nums = [1,2,3,1], k = 3
Output: true

Example 2:
Input: nums = [1,0,1,1], k = 1
Output: true

Example 3:
Input: nums = [1,2,3,1,2,3], k = 2
Output: false
*/


//12. MAXIMUM AVERAGE SUBARRAY                                             {T.C = O(N), S.C = O(1)}
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int n = nums.size();
        int i = 0, j = 0;
        double sum = 0, avg = 0, maxAvg = INT_MIN;
        while(j < n){
            sum += nums[j];
            if(j-i+1 == k){
                avg = sum / k;
                maxAvg = max(maxAvg, avg);

                sum -= nums[i];                 //shrink window
                i++;
            }
            j++;
        }
        return maxAvg;
    }
};
/*
Example 1:
Input: nums = [1,12,-5,-6,50,3], k = 4
Output: 12.75000
Explanation: Maximum average is (12 - 5 - 6 + 50) / 4 = 51 / 4 = 12.75

Example 2:
Input: nums = [5], k = 1
Output: 5.00000
*/


//13. SHORTEST SUBARRAY WITH OR AT LEAST K I                               {T.C = O(N^2), S.C = O(1)}
//BRUTE FORCE
class Solution {
public:
    int minimumSubarrayLength(vector<int>& nums, int k) {
        int n = nums.size();
        int minLen = INT_MAX;
        for(int i = 0 ; i < n; i++){
            int OrVal = 0, len = 0;
            for(int j = i ; j < n ; j++){
                OrVal |= nums[j];
                len++;
                if(OrVal >= k) minLen = min(minLen, len);           //or len => j-i+1
            }
        }
        return minLen == INT_MAX ? -1 : minLen;
    }
};
/*
Example 1:
Input: nums = [1,2,3], k = 2
Output: 1
Explanation:
The subarray [3] has OR value of 3. Hence, we return 1.

Example 2:
Input: nums = [2,1,8], k = 10
Output: 3
Explanation:
The subarray [2,1,8] has OR value of 11. Hence, we return 3.

Example 3:
Input: nums = [1,2], k = 0
Output: 1
Explanation:
The subarray [1] has OR value of 1. Hence, we return 1.
*/


//14. SHORTEST SUBARRAY WITH OR AT LEAST K II                               {T.C = O(N), S.C = O(N)}
class Solution {
public:
    bool bigWindow(int k, vector<int>& bitArr) {
        int bitArrVal = 0;
        for (int i = 0; i < 32; i++) {
            if (bitArr[i]) bitArrVal += (1 << i); // Use bitwise shift to build the integer
        }
        return bitArrVal >= k;
    }

    void addJorRemoveI(int val, vector<int>& bitArr, bool isValid) {
        int i = 0;
        while (val > 0) {
            int bit = val % 2;
            bitArr[i] += (isValid ? 1 : -1) * bit;
            val /= 2;
            i++;
        }
    }

    int minimumSubarrayLength(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> bitArr(32, 0);
        int i = 0, j = 0, minLen = INT_MAX;

        while (j < n) {
            addJorRemoveI(nums[j], bitArr, true);

            while (bigWindow(k, bitArr) && i <= j) {
                minLen = min(minLen, j - i + 1);
                addJorRemoveI(nums[i], bitArr, false); // Slide window
                i++;
            }
            j++;
        }

        return minLen == INT_MAX ? -1 : minLen; // Correct comparison operator
    }
};
/*
Example 1:
Input: nums = [1,2,3], k = 2
Output: 1
Explanation:
The subarray [3] has OR value of 3. Hence, we return 1.

Example 2:
Input: nums = [2,1,8], k = 10
Output: 3
Explanation:
The subarray [2,1,8] has OR value of 11. Hence, we return 3.

Example 3:
Input: nums = [1,2], k = 0
Output: 1
Explanation:
The subarray [1] has OR value of 1. Hence, we return 1.
*/


//15. LONGEST EVEN ODD SUBARRAY WITH THRESHOLD                             {T.C = O(N^2), S.C = O(1)}
class Solution {
public:
    int longestAlternatingSubarray(vector<int>& nums, int threshold) {
        int n = nums.size();
        int maxLen = 0;
        for(int i = 0 ; i < n ;i++){
            if(nums[i] % 2 == 0 && nums[i] <= threshold){
                int len = 1;
                for(int j = i ; j < n-1 ; j++){
                    if(nums[j] % 2 != nums[j+1] % 2 && nums[j+1] <= threshold){
                        len++;
                    }else break;
                }
                maxLen = max(maxLen, len);
            }
        }
        return maxLen;
    }
};
/*
Example 1:
Input: nums = [3,2,5,4], threshold = 5
Output: 3
Explanation: In this example, we can select the subarray that starts at l = 1 and ends at r = 3 => [2,5,4]. This subarray satisfies the conditions.
Hence, the answer is the length of the subarray, 3. We can show that 3 is the maximum possible achievable length.

Example 2:
Input: nums = [1,2], threshold = 2
Output: 1
Explanation: In this example, we can select the subarray that starts at l = 1 and ends at r = 1 => [2]. 
It satisfies all the conditions and we can show that 1 is the maximum possible achievable length.

Example 3:
Input: nums = [2,3,4,5], threshold = 4
Output: 3
Explanation: In this example, we can select the subarray that starts at l = 0 and ends at r = 2 => [2,3,4]. 
It satisfies all the conditions.
Hence, the answer is the length of the subarray, 3. We can show that 3 is the maximum possible achievable length.
*/


//16. COUNT NUMBER OF NICE SUBARRAYS
//USING MAP                                                             {T.C = O(N), S.C = O(N)}
class Solution {
public:
    //using map
    int numberOfSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int,int>mp;
        mp[0] = 1;                                  //0 count 1 initially
        int oddCount = 0, subArrCount = 0;
        for(auto it : nums){
            oddCount += (it % 2);                    //if odd add 1 else 0
            if(mp.count(oddCount-k)) subArrCount += mp[oddCount-k];   //not +1 (+freq(total subarray can form))
            mp[oddCount]++;
        }
        return subArrCount;
    }
};

//USING SLIDING WINDOW (EXACTLY K -> ATMOST (K) - ATMOST (K-1))              {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int atMostK(vector<int>&nums, int k){
        int n = nums.size();
        int oddCount = 0, subArrCount = 0;
        int i = 0, j = 0;
        while(j < n){
            oddCount += (nums[j] % 2);                  //if odd add 1 else add 0

            while(oddCount > k){
                oddCount -= (nums[i] % 2);             //subtract -1 if odd else 0
                i++;
            }
            subArrCount += (j-i+1);
            j++;
        }
        return subArrCount;
    }
    int numberOfSubarrays(vector<int>& nums, int k) {
        return atMostK(nums, k) - atMostK(nums, k-1);        //==> exactly k
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
Explanation: There are no odd numbers in the array.

Example 3:
Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2
Output: 16
*/


//17. MINIMUM OPERATIONS TO MAKE BINARY ARRAY ELEMENTS EQUAL TO ONE I        
//BRUTE FORCE I                                                             {T.C = O(N^2), S.C = O(1)}
class Solution {
public:
    //brute force
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int countFlips = 0;
        for(int i = 0 ; i < n-2 ; i++){
            if(nums[i] == 0){
                for(int j = i ; j < i+3 ; j++){
                    if(nums[j] == 0) nums[j] = 1;
                    else nums[j] = 0;
                }
                countFlips++;
            }
        }
        for(auto it : nums) if(it == 0) return -1;
        return countFlips;
    }
};

//OPTIMIZED APPROACH                                                        {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int countFlips = 0;
        for(int i = 0 ; i <= n-3 ; i++){            //k = 3
            if(nums[i] == 0){
                nums[i] = !nums[i];
                nums[i+1] = !nums[i+1];
                nums[i+2] = !nums[i+2];

                countFlips++;
            }
        }
        for(auto it : nums) if(it == 0) return -1;
        return countFlips;
    }
};
/*
Example 1:
Input: nums = [0,1,1,1,0,0]
Output: 3
Explanation:
We can do the following operations:
Choose the elements at indices 0, 1 and 2. The resulting array is nums = [1,0,0,1,0,0].
Choose the elements at indices 1, 2 and 3. The resulting array is nums = [1,1,1,0,0,0].
Choose the elements at indices 3, 4 and 5. The resulting array is nums = [1,1,1,1,1,1].

Example 2:
Input: nums = [0,1,1,1]
Output: -1
Explanation:
It is impossible to make all elements equal to 1.
*/


//18. NUMBER OF SUBARRAYS OF SIZE K AND AVERAGE GREATER THAN OR EQUAL TO THRESHOLD  {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        int n = arr.size();
        int count = 0;
        int i = 0 , j = 0;
        int sum = 0, avg = 0;
        while(j < n){
            sum += arr[j];

            if(j-i+1 == k){
                avg = sum/k;
                if(avg >= threshold) count++;
                
                sum -= arr[i];                           //slide window
                i++;
            }
            j++;
        }
        return count;
    }
};
/*
Example 1:
Input: arr = [2,2,2,2,5,5,5,8], k = 3, threshold = 4
Output: 3
Explanation: Sub-arrays [2,5,5],[5,5,5] and [5,5,8] have averages 4, 5 and 6 respectively. All other sub-arrays of size 3 have averages less than 4 (the threshold).

Example 2:
Input: arr = [11,13,17,23,29,31,7,5,2,3], k = 3, threshold = 5
Output: 6
Explanation: The first 6 sub-arrays of size 3 have averages greater than 5. Note that averages are not integers.
*/


//19. LONGEST SUBARRAY OF 1'S AFTER DELETING ONE ELEMENT                     {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int n = nums.size();
        int zeroCount = 0;
        int i = 0, j = 0;
        int maxLen = INT_MIN;
        while(j < n){
            if(nums[j] == 0) zeroCount++;

            while(zeroCount > 1){
                if(nums[i] == 0) zeroCount--;
                i++;
            }
            maxLen = max(maxLen, j-i);          //1 deleted (j-i+1 - 1 => j-i)
            j++;
        }
        return maxLen;
    }
};
/*
Example 1:
Input: nums = [1,1,0,1]
Output: 3
Explanation: After deleting the number in position 2, [1,1,1] contains 3 numbers with value of 1's.

Example 2:
Input: nums = [0,1,1,1,0,1,1,0,1]
Output: 5
Explanation: After deleting the number in position 4, [0,1,1,1,1,1,0,1] longest subarray with value of 1's is [1,1,1,1,1].

Example 3:
Input: nums = [1,1,1]
Output: 2
Explanation: You must delete one element.
*/


//20. NUMBER OF SUBSTRINGS CONTAINING ALL THREE CHARACTERS                   
//USING MAP                                                              {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int numberOfSubstrings(string s) {
        int n = s.length();
        unordered_map<int,int>mp;
        int count = 0;
        int i = 0, j = 0;
        while(j < n){
            mp[s[j]]++;

            while(mp.size() == 3){
                count += (n-j);                  //all valid substring in curr window

                mp[s[i]]--;                       //slide window
                if(mp[s[i]] == 0) mp.erase(s[i]);
                i++;
            }
            j++;
        }
        return count;
    }
};

//WITHOUT MAP                                                          {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int numberOfSubstrings(string s) {
        int n = s.length();
        int i = 0 , j = 0;
        int count = 0;
        vector<int>freq(3, 0);
        while(j < n){
            freq[s[j]-'a']++;
            while(freq[0] > 0 && freq[1] > 0  && freq[2] > 0){
                freq[s[i]-'a']--;
                count += (n-j);
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


//21. MAXIMIZE THE CONFUSION OF AN EXAM                                    
//SIMILAR TO (19)
//2 PASS SLIDING WINDOW                                                  {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int solveForT(string &s, int k) {
        int n = s.length();
        int maxLen = 0;                                  // Initialize to 0
        int i = 0, j = 0;
        int falseCount = 0;

        while (j < n) {
            if (s[j] == 'F') falseCount++;

            while (falseCount > k) {
                if (s[i] == 'F') falseCount--;
                i++;
            }

            maxLen = max(maxLen, j - i + 1); 
            j++;
        }
        return maxLen;
    }

    int solveForF(string &s, int k) {
        int n = s.length();
        int maxLen = 0;                             // Initialize to 0
        int i = 0, j = 0;
        int trueCount = 0;

        while (j < n) {
            if (s[j] == 'T') trueCount++;

            while (trueCount > k) {
                if (s[i] == 'T') trueCount--;
                i++;
            }

            maxLen = max(maxLen, j - i + 1); 
            j++;
        }
        return maxLen;
    }

    int maxConsecutiveAnswers(string answerKey, int k) {
        int checkT = solveForT(answerKey, k);
        int checkF = solveForF(answerKey, k);

        return max(checkT, checkF);
    }
};

//1 PASS SOLUTION                                                             {T.C = O(N), S.C = O(N)}
class Solution {
public:
    //1 pass sliding window
    int solve(string &s, int k){
        int n = s.size();
        unordered_map<char,int>mp;
        int maxLen = INT_MIN;
        int i = 0, j = 0;
        while(j < n){
            mp[s[j]]++;

            while(min(mp['T'], mp['F']) > k){
                mp[s[i]]--;
                i++;
            }
            maxLen = max(maxLen, j-i+1);
            j++;
        }
        return maxLen;
    }
    int maxConsecutiveAnswers(string answerKey, int k) {
        return solve(answerKey, k);
    }
};
/*
Example 1:
Input: answerKey = "TTFF", k = 2
Output: 4
Explanation: We can replace both the 'F's with 'T's to make answerKey = "TTTT".
There are four consecutive 'T's.

Example 2:
Input: answerKey = "TFFT", k = 1
Output: 3
Explanation: We can replace the first 'T' with an 'F' to make answerKey = "FFFT".
Alternatively, we can replace the second 'T' with an 'F' to make answerKey = "TFFF".
In both cases, there are three consecutive 'F's.

Example 3:
Input: answerKey = "TTFTTFTT", k = 1
Output: 5
Explanation: We can replace the first 'F' to make answerKey = "TTTTTFTT"
Alternatively, we can replace the second 'F' to make answerKey = "TTFTTTTT". 
In both cases, there are five consecutive 'T's.
*/


//22. MINIMUM SWAPS REQUIRED TO GROUP ALL 1s TOGETHER I                   {T.C = O(N), S.C = O(1)}
int minSwaps(int arr[], int n) {
    int count1 = 0;
    for(int i = 0 ; i < n; i++){
        if(arr[i] == 1) count1++;
    }
    int k = count1;                   //k = window size
    int i = 0, j = 0;
    int zeroCount = 0;
    int minSwap = INT_MAX;
    while(j < n){
        if(arr[j] == 0) zeroCount++;
        
        if(j-i+1 == k){
            minSwap = min(minSwap, zeroCount);
            
            if(arr[i] == 0) zeroCount--;       //slide window
            i++;
            
        }
        j++;
    }
    return minSwap == INT_MAX ? -1 : minSwap;
}
/*
Example 1:
Input : arr[ ] = {1, 0, 1, 0, 1}
Output : 1
Explanation:
Only 1 swap is required to group all 1's together. 
Swapping index 1 and 4 will give arr[] = {1, 1, 1, 0, 0}.

Example 2:
Input : arr[ ] = {1, 0, 1, 0, 1, 1} 
Output :  1
*/


//23. MINIMUM SWAPS REQUIRED TO GROUP ALL 1s TOGETHER II (CIRCULAR ARRAY)                  {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        int count1 = 0;
        for(auto it : nums){
            if(it == 1) count1++;
        }
        int k = count1;                         //size of window
        int i = 0 , j = 0;
        int zeroCount = 0;
        int minSwap = INT_MAX;
        while(j < 2*n){
            if(nums[j % n] == 0) zeroCount++;            //% for circular nature
            
            if(j-i+1 == k){
                minSwap = min(minSwap, zeroCount);

                if(nums[i % n] == 0) zeroCount--;        //slide window
                i++;
            }
            j++;
        }
        return minSwap == INT_MAX ? 0 : minSwap;
    }
};
/*
Example 1:
Input: nums = [0,1,0,1,1,0,0]
Output: 1
Explanation: Here are a few of the ways to group all the 1's together:
[0,0,1,1,1,0,0] using 1 swap.
[0,1,1,1,0,0,0] using 1 swap.
[1,1,0,0,0,0,1] using 2 swaps (using the circular property of the array).
There is no way to group all 1's together with 0 swaps.
Thus, the minimum number of swaps required is 1.

Example 2:
Input: nums = [0,1,1,1,0,0,1,1,0]
Output: 2
Explanation: Here are a few of the ways to group all the 1's together:
[1,1,1,0,0,0,0,1,1] using 2 swaps (using the circular property of the array).
[1,1,1,1,1,0,0,0,0] using 2 swaps.
There is no way to group all 1's together with 0 or 1 swaps.
Thus, the minimum number of swaps required is 2.

Example 3:
Input: nums = [1,1,0,0,1]
Output: 0
Explanation: All the 1's are already grouped together due to the circular property of the array.
Thus, the minimum number of swaps required is 0.
*/


//24. COUNT COMPLETE SUBARRAYS IN AN ARRAY                                  {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int countCompleteSubarrays(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int,int>mp1;
        for(auto it : nums) mp1[it]++;
        int diff = mp1.size();                  //total different numbers

        unordered_map<int,int>mp;
        int i = 0, j = 0;
        int count = 0;
        while(j < n){
            mp[nums[j]]++;

            while(mp.size() == diff){
                count += (n-j);                      //count all subarrays(in between subarrays)

                mp[nums[i]]--;                        //slide window
                if(mp[nums[i]] == 0) mp.erase(nums[i]);
                i++;
            }
            j++;
        }
        return count;
    }
};
/*
Example 1:
Input: nums = [1,3,1,2,2]
Output: 4
Explanation: The complete subarrays are the following: [1,3,1,2], [1,3,1,2,2], [3,1,2] and [3,1,2,2].

Example 2:
Input: nums = [5,5,5,5]
Output: 10
Explanation: The array consists only of the integer 5, so any subarray is complete. The number of subarrays that we can choose is 10.
*/


//25. GRUMPY BOOKSTORE OWNER                                            {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int n = customers.size();
        int k = minutes;
        int currUnSatCus = 0, maxSatCus = 0;
        int i = 0, j = 0;
        while(j < n){                                //take window with max unSatisfy(to resolve it using special case)
            currUnSatCus += customers[j]*grumpy[j];         //if g = 1 then add 1 else add 0

            if(j-i+1 == k){
                maxSatCus = max(maxSatCus, currUnSatCus);

                currUnSatCus -= customers[i]*grumpy[i];    //if g= 1 reduce customer
                i++;
            }
            j++;
        }
        for(int i = 0 ; i < n ; i++){                     //not include in window but 0(owner is not grumpy)
            if(grumpy[i] == 0) maxSatCus += customers[i];
        }
        return maxSatCus;
    }
};
/*
Example 1:
Input: customers = [1,0,1,2,1,1,7,5], grumpy = [0,1,0,1,0,1,0,1], minutes = 3
Output: 16
Explanation: The bookstore owner keeps themselves not grumpy for the last 3 minutes. 
The maximum number of customers that can be satisfied = 1 + 1 + 1 + 1 + 7 + 5 = 16.

Example 2:
Input: customers = [1], grumpy = [0], minutes = 1
Output: 1
*/


//26. MAX CONSECUTIVE ONES III                                         {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size();
        int countFlips = 0;
        int maxLen = INT_MIN;
        int  i = 0, j = 0;
        while(j < n){
            if(nums[j] == 0) countFlips++;

            while(countFlips > k){
                if(nums[i] == 0) countFlips--;
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


//27. BINARY SUBARRAYS WITH SUM                                          {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int atMostGoal(vector<int>&nums, int goal){
        int n = nums.size();
        int count = 0;
        int i = 0, j = 0;
        int sum = 0;
        //base case
        if(goal < 0) return 0;

        while(j < n){
            sum += nums[j];

            while(sum > goal){
                sum -= nums[i];
                i++;
            }
            count += (j-i+1);
            j++;
        }
        return count;
    }
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        return atMostGoal(nums, goal) - atMostGoal(nums, goal-1);    //=> exactly goals
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


//28. MAXIMUM SUM OF TWO NON-OVERLAPPING SUBARRAYS                             {T.C = O(N^2), S.C = O(1)}
//REVISIT (2 WINDOW SLIDE SIMULTANEOUSLY)
class Solution {
public:
    int solve(vector<int>& nums, int f, int s) {
        int n = nums.size();
        int i1 = 0, j1 = 0, sum1 = 0, maxSum1 = 0;

        
        while (j1 < f) {               // Calculate initial sum for the first window
            sum1 += nums[j1];
            j1++;
        }
        j1--;                         // j1 should point to the last element of the first window
        while (j1 < n) {              //slide window for first and find sum for second
            int sum2 = 0, maxSum2 = 0;
            int i2 = j1 + 1, j2 = j1 + 1;

            while (j2 - i2 + 1 <= s && j2 < n) {  // Calculate the maximum sum of the second subarray
                sum2 += nums[j2];
                if (j2 - i2 + 1 == s) {
                    maxSum2 = max(maxSum2, sum2);
                    sum2 -= nums[i2];
                    i2++;
                }
                j2++;
            }

           
            maxSum1 = max(maxSum1, sum1 + maxSum2);       // Calculate the overall maximum sum for both subarrays

            
            sum1 -= nums[i1];                         // Slide the first window
            i1++, j1++;
            if (j1 < n) {
                sum1 += nums[j1];
            }
        }

        return maxSum1;
    }

    int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
        return max(solve(nums, firstLen, secondLen), solve(nums, secondLen, firstLen));
    }
};
/*
Example 1:
Input: nums = [0,6,5,2,2,5,1,9,4], firstLen = 1, secondLen = 2
Output: 20
Explanation: One choice of subarrays is [9] with length 1, and [6,5] with length 2.

Example 2:
Input: nums = [3,8,1,3,2,1,8,9,0], firstLen = 3, secondLen = 2
Output: 29
Explanation: One choice of subarrays is [3,8,1] with length 3, and [8,9] with length 2.

Example 3:
Input: nums = [2,1,5,6,0,9,5,0,3,8], firstLen = 4, secondLen = 3
Output: 31
Explanation: One choice of subarrays is [5,6,0,9] with length 4, and [0,3,8] with length 3.
*/