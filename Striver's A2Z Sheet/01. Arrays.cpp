//ARRAYS
#include<bits/stdc++.h>
using namespace std;

//01. LARGEST ELEMENT IN THE ARRAY                               {T.C = O(N), S.C = O(1)}
int largestElement(vector<int> &arr, int n) {
    int maxi = arr[0];
    for(int i = 1 ; i < n ; i++){
        maxi = max(maxi, arr[i]);
    }
    return maxi;
}
/*
Given an array ‘arr’ of size ‘n’ find the largest element in the array.
Example:
Input: 'n' = 5, 'arr' = [1, 2, 3, 4, 5]
Output: 5
Explanation: From the array {1, 2, 3, 4, 5}, the largest element is 5.
*/


//02. SECOND LARGEST NUMBER
//BRUTE FORCE                                                  {T.C = O(N*LOGN), S.C = O(1)}
vector<int> getSecondOrderElements(int n, vector<int> a) {
    sort(a.begin(), a.end());
    return {a[n-2], a[1]};
}
//OPTIMIZED APPROACH                                           {T.C = O(N), S.C = O(1)}
vector<int> getSecondOrderElements(int n, vector<int> a) {
    int largest =  a[0];
    int secondLargest = INT_MIN;
    
    for(int i = 1 ; i < n ; i++){
        if(a[i] > largest){
            secondLargest = largest;                                  //stores current largest(second largest)
            largest = a[i];
        }else if(a[i] > secondLargest && a[i] < largest){
            secondLargest = a[i];
        }
    }
    int smallest = a[0];
    int secondSmallest = INT_MAX;
    for(int i = 1;  i < n ; i++){
        if(a[i] < smallest){
            secondSmallest = smallest;                          //stores current smallest element(may be second smallest)
            smallest = a[i];
        }else if(a[i] < secondSmallest && a[i] > smallest){
            secondSmallest = a[i];
        }
    }
    return {secondLargest, secondSmallest};
}
/*
Input: ‘n’ = 5, ‘a’ = [1, 2, 3, 4, 5]
Output: [4, 2]
The second largest element after 5 is 4, and the second smallest element after 1 is 2.
*/


//03. CHECK IF ARRAY IS SORTED AND ROTATED                                    {T.C = O(N), S.C = O(1)}
class Solution {
public:
    bool check(vector<int>& nums) {
        int n = nums.size();
        int count = 0;
        for(int i = 1; i < n ; i++){
            if(nums[i-1] > nums[i]){
                count++;
            }
        }
        if(nums[n-1] > nums[0]){
            count++;
        }
        return count <= 1;           //If it is breaking just once then it or it does't break even once then it is sorted
    }
};
/*
Example 1:
Input: nums = [3,4,5,1,2]
Output: true
Explanation: [1,2,3,4,5] is the original sorted array.
You can rotate the array by x = 3 positions to begin on the the element of value 3: [3,4,5,1,2].

Example 2:
Input: nums = [2,1,3,4]
Output: false
Explanation: There is no sorted array once rotated that can make nums.

Example 3:
Input: nums = [1,2,3]
Output: true
Explanation: [1,2,3] is the original sorted array.
You can rotate the array by x = 0 positions (i.e. no rotation) to make nums.
*/


//04. REMOVE DUPLICATES FROM SORTED ARRAY                                             {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        //base case
        if(n <= 1){
            return n;
        }

        int count = 1;
        for(int i = 1 ; i < n; i++){
            if(nums[i] != nums[count-1]){
                nums[count] = nums[i];                   //update current element
                count++;
            }
        }
        return count;
    }
};
/*
Example 1:
Input: nums = [1,1,2]
Output: 2, nums = [1,2,_]
Explanation: Your function should return k = 2, with the first two elements of nums being 1 and 2 respectively.
It does not matter what you leave beyond the returned k (hence they are underscores).

Example 2:
Input: nums = [0,0,1,1,1,2,2,3,3,4]
Output: 5, nums = [0,1,2,3,4,_,_,_,_,_]
Explanation: Your function should return k = 5, with the first five elements of nums being 0, 1, 2, 3, and 4 respectively.
It does not matter what you leave beyond the returned k (hence they are underscores).
*/


//05. ROTATE ARRAY                                                  {T.C = O(N), S.C = O(1)}
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;                         //if k > n then modulo for match index
                                                    //example 123456 , k = 2 => 456123
        reverse(nums.begin(), nums.begin()+(n-k));  //321456        
        reverse(nums.begin()+(n-k), nums.end());    //321654
        reverse(nums.begin(), nums.end());          //456123
    }
};
/*
Example 1:
Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]

Example 2:
Input: nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]
Explanation: 
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]
*/


//07. MOVE ZEROES                                                       {T.C = O(N), S.C = O(1)}
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        int i = 0, j = 0;
        while(i < n){
            if(nums[i] != 0){
                swap(nums[i], nums[j]);
                j++;
            }
            i++;
        }
    }
};
/*
Example 1:
Input: nums = [0,1,0,3,12]
Output: [1,3,12,0,0]

Example 2:
Input: nums = [0]
Output: [0]
*/


//08. LINEAR SEARCH                                             {T.C = O(N), S.C = O(1)}
int linearSearch(int n, int num, vector<int> &arr)
{
    for(int i = 0 ; i < n ; i++){
        if(arr[i] == num){
            return i;
        }
    }
    return -1;
}
/*
Example:
Input: ‘n’ = 5, ‘num’ = 4 
'arr' =  [6,7,8,4,1] 
Output: 3
Explanation:
4 is present at the 3rd index.
*/


//09. MERGE 2 SORTED ARRAY 
//09a. BRUTE FORCE (MAP)                                      {T.C = O(N*LOGN), S.C = O(N)}
vector < int > sortedArray(vector < int > a, vector < int > b) {
    set<int>st;
    for(int i = 0 ; i < a.size(); i++){
        st.insert(a[i]);                                         //inserting (logn)
    }
    for(int j = 0 ; j < b.size(); j++){
        st.insert(b[j]);
    }
    vector<int>ans(st.begin(), st.end());
    return ans;
}

//09b. USING 2 POINTERS                                                {T.C = O(N), S.C = O(N)}
vector < int > sortedArray(vector < int > a, vector < int > b) {
    int n = a.size();
    int m = b.size();
    int i = 0, j = 0;                        //starting pointer of both vectors
    vector<int>ans;
    while(i < n && j < m){
        if(a[i] <= b[j]){
            if(ans.empty() || ans.back() != a[i]){
                ans.push_back(a[i]);
            }
            i++;
        }else{
            if(ans.empty() || ans.back() != b[j]){
                ans.push_back(b[j]);
            }
            j++;
        }
    }
    while(i < n){
        if(ans.empty() || ans.back() != a[i]){
                ans.push_back(a[i]);
        }
        i++;
    }
    while(j < m){
        if(ans.empty() || ans.back() != b[j]){
                ans.push_back(b[j]);
        }
        j++;
    }
    return ans;
}
/*
Example:
Input: ‘n’ = 5 ‘m’ = 3
‘a’ = [1, 2, 3, 4, 6]
‘b’ = [2, 3, 5]
Output: [1, 2, 3, 4, 5, 6]
Explanation: Common elements in ‘a’ and ‘b’ are: [2, 3]
Distinct elements in ‘a’ are: [1, 4, 6]
Distinct elements in ‘b’ are: [5]
Union of ‘a’ and ‘b’ is: [1, 2, 3, 4, 5, 6]
*/


//10. MISSING NUMBER
//10a. BRUTE FORCE (SORTING)                                              {T.C = O(N*LOGN), S.C = O(1)}
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        if(nums[0] != 0){                        //handle first element
            return 0;
        }
        if(nums[n-1] != n){                     //handle last element
            return n;
        }
        for(int i = 1 ; i < n ; i++){           //handle rest of element
            if(nums[i] != i){
                return i;
            }
        }
        return -1;
    }
};

//10b. USING EXTRA SPACE                                               {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        vector<int>ans(n+1, -1);
        for(int i = 0 ; i < n ; i++){
            ans[nums[i]] = nums[i];
        }
        for(int i = 0 ; i < ans.size() ; i++){
            if(ans[i] == -1){
                return i;
            }
        }
        return -1;
    }
};
/*
Example 1:
Input: nums = [3,0,1]
Output: 2
Explanation: n = 3 since there are 3 numbers, so all numbers are in the range [0,3]. 2 is the missing number in the range since it does not appear in nums.

Example 2:
Input: nums = [0,1]
Output: 2
Explanation: n = 2 since there are 2 numbers, so all numbers are in the range [0,2]. 2 is the missing number in the range since it does not appear in nums.

Example 3:
Input: nums = [9,6,4,2,3,5,7,0,1]
Output: 8
Explanation: n = 9 since there are 9 numbers, so all numbers are in the range [0,9]. 8 is the missing number in the range since it does not appear in nums.
*/


//11. MAX CONSECUTIVE ONES                                   {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int n = nums.size();
        int maxi = 0;
        int count = 0;
        for(int i = 0 ; i < n ; i++){
            if(nums[i] == 1){
                count++;
                maxi = max(maxi, count);
            }else{
                count = 0;
            }
        }
        return maxi;
    }
};
/*
Example 1:
Input: nums = [1,1,0,1,1,1]
Output: 3
Explanation: The first two digits or the last three digits are consecutive 1s. The maximum number of consecutive 1s is 3.

Example 2:
Input: nums = [1,0,1,1,0,1]
Output: 2
*/


//12. SINGLE NUMBER                                                         {T.C = O(N), S.C = O(1)}
//XOR
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int xorAns = 0;
        for(int i = 0 ; i < nums.size() ; i++){
            xorAns =  xorAns^nums[i];
        }
        return xorAns;
    }
};
/*
Example 1:
Input: nums = [2,2,1]
Output: 1

Example 2:
Input: nums = [4,1,2,1,2]
Output: 4

Example 3:
Input: nums = [1]
Output: 1
*/


//13. LONGEST SUBARRAY WITH SUM K                                              {T.C = O(N), S.C = O(1)}
//SLIDING WINDOW
int longestSubarrayWithSumK(vector<int> a, long long k) {

    long long i = 0, j = 0, maxiLen = 0;
    long long sum = 0;
    long n = a.size();
    while (j < n) {
        sum += a[j];
        if (sum > k) {
            while (sum > k && i <= j) {
                sum -= a[i];
                i++;
            }
        }
        if (sum == k) {
            maxiLen = max(maxiLen, (j - i + 1));
        }
        j++;
    }
    return maxiLen;
}
/*
Sample Input 1 :
7 3
1 2 3 1 1 1 1


Sample Output 1 :
3


Explanation Of Sample Input 1 :
Subarrays whose sum = ‘3’ are:
[1, 2], [3], [1, 1, 1] and [1, 1, 1]
Here, the length of the longest subarray is 3, which is our final answer.
*/


//14. LONGEST SUBARRAY WITH SUM K (WITH -VE NUMBERS)                 {T.C = O(N*LOGN), S.C = O(N)}
//MAP
int getLongestSubarray(vector<int>& nums, int k){
    unordered_map<long long , int > mp;
    long long sum = 0;
    int maxLen = 0;
    for(int i = 0 ; i < nums.size(); i++){
        sum += nums[i];
        if(sum == k){
            maxLen = max(maxLen, i+1);
        }
        long long rem = sum - k;
        if(mp.find(rem) != mp.end()){
            int len = i - mp[rem];
            maxLen = max(maxLen, len);
        }
        if(mp.find(sum) == mp.end()){
            mp[sum] = i;
        }
    }
    return maxLen;
}
/*
Sample Input 1 :
2
3 5
2 3 5
3 1
-1 1 1
Sample Output 1 :
2
3
Explanation Of Sample Input 1 :
For the first case:
There are two subarrays with sum = 5, [2, 3] and [5]. Hence the length of the longest subarray is 2.

For the second case:
Longest subarray with sum = 1 is [1, -1, 1].
Sample Input 2 :
2
3 4
1 1 1
3 2
-50 0 52
Sample Output 2 :
0 
3
*/


//15. 2 SUM                                               {T.C = O(N), S.C = O(N)}
//MAP
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        /*
        int n = nums.size();
        unordered_map<int, int> mp;                          //{i, nums}
        for(int i = 0 ; i < n ; i++){
            mp[nums[i]] = i;
        }
        for(int i = 0 ; i < n ; i++){
            int complement = target-nums[i];
            if(mp.find(complement) != mp.end() && mp[complement] !=  i){
                return {i, mp[complement]};
            }
        }
        return {};
        */

        int n = nums.size();
        unordered_map<int, int>mp;                       //{i, nums}

        for(int i = 0; i < n ; i++){
            int compliment = target-nums[i];
            if(mp.count(compliment)){                     //or mp.find(compliment) != mp.end()
                return {mp[compliment], i};
            }
            mp[nums[i]] = i;
        }
        return {};
    }
};
/*
Example 1:
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].

Example 2:
Input: nums = [3,2,4], target = 6
Output: [1,2]

Example 3:
Input: nums = [3,3], target = 6
Output: [0,1]
*/

//16. SORT COLORS                                                       {T.C = O(N), S.C = O(1)}
//3 POINTERS(DUTCH NATIONAL FLAG ALGO)
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


//17. MAJORITY ELEMENT
//BRUTE FORCE (MAP)                                                             {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        unordered_map<int, int>mp;
        for(auto it : nums){
            mp[it]++;
            if(mp[it] > n/2){
                ans = it;
            }
        }
        return ans;
    }
};

//OPTIMISED APPROACH (TRAVERSAL & VARIABLES)                                    {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int count = 0;
        int element = 0;

        for(auto it : nums){
            if(count == 0){
                element = it;
            }
            if(it == element){
                count++;
            }else{
                count--;
            }
        }
        return element;
    }
};
/*
Example 1:
Input: nums = [3,2,3]
Output: 3

Example 2:
Input: nums = [2,2,1,1,1,2,2]
Output: 2
*/


//18. MAXIMUM SUBARRAY                                                  {T.C = O(N), S.C = O(1)}
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


//19. LONGEST SUBARRAY WITH SUM K                                                   {T.C = O(N), S.C = O(1)}
//SLIDING WINDOW
int longestSubarrayWithSumK(vector<int> a, long long k) {
    int n = a.size();
    int i = 0, j = 0;
    long long sum = 0;
    int maxLen = 0;
    while(j < n){
        sum += a[j];
        if(sum > k){
            while(sum > k){
                sum -= a[i];
                i++;
            }
        }
        if(sum == k){
            maxLen = max(maxLen, j-i+1);
        }
        j++;
    }
    return maxLen;
}
/*
Example :
Input: ‘n’ = 7 ‘k’ = 3
‘a’ = [1, 2, 3, 1, 1, 1, 1]
Output: 3
Explanation: Subarrays whose sum = ‘3’ are:
[1, 2], [3], [1, 1, 1] and [1, 1, 1]
Here, the length of the longest subarray is 3, which is our final answer.
*/


//20. BEST TIME TO BUY AND SELL STOCK (BUY 1 DAY, SELL ANOTHER DAY)                    {T.C = O(N), S.C = O(1)}
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


//21. REARRANGE ARRAY ELEMENTS BY SIGN                                      {T.C = O(N), S.C = O(N)}
//POSINDEX & NEGINDEX
class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        int n = nums.size();
        vector<int>ans(n);
        int posIdx = 0;
        int negIdx = 1;

        for(int i = 0 ; i < n ; i++){
            if(nums[i] > 0){
                ans[posIdx] = nums[i];
                posIdx += 2;
            }else{ //nums[i] < 0
                ans[negIdx] = nums[i];
                negIdx += 2;
            }
        }
        return ans;
    }
};
/*
Example 1:
Input: nums = [3,1,-2,-5,2,-4]
Output: [3,-2,1,-5,2,-4]
Explanation:
The positive integers in nums are [3,1,2]. The negative integers are [-2,-5,-4].
The only possible way to rearrange them such that they satisfy all conditions is [3,-2,1,-5,2,-4].
Other ways such as [1,-2,2,-5,3,-4], [3,1,2,-2,-5,-4], [-2,3,-5,1,-4,2] are incorrect because they do not satisfy one or more conditions.  

Example 2:
Input: nums = [-1,1]
Output: [1,-1]
Explanation:
1 is the only positive integer and -1 the only negative integer in nums.
So nums is rearranged to [1,-1].
*/


//22. NEXT PERMUTATION                                             {T.C = O(N), S.C = O(1)}
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


//23. SUPERIOR ELEMENTS                                                {T.C = O(N), S.C = O(N)}
//TRAVERSAL (REVERSE)
vector<int> superiorElements(vector<int>&a) {
    int n = a.size();
    vector<int>ans;
    int temp = a[n-1];
    ans.push_back(temp);
    for(int i = n-2 ; i >= 0 ; i--){
        if(a[i] > temp ){
            ans.push_back(a[i]);
        }
        temp = max(temp, a[i]);
    }
    return ans;
}
/*
Example
Input: a = [1, 2, 3, 2], n = 4
Output: 2 3
Explanation: 
a[ 2 ] = 3 is greater than a[ 3 ]. Hence it is a Superior Element. 
a[ 3 ] = 2 is the last element. Hence it is a Superior Element.
The final answer is in sorted order.
*/


//24. LONGEST CONSECUTIVE SEQUENCE                                {T.C = O(N), S.C = O(N)}
//SET
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n = nums.size();
        int maxLen = 0;
        unordered_set<int>st(nums.begin(), nums.end());
        for(int i = 0 ; i < n ; i++){
            if(st.find(nums[i]-1) == st.end()){
                int j = nums[i]+1;
                while(st.find(j) != st.end()){
                    j++;
                }
                maxLen = max(maxLen, j-nums[i]);
            }
        }
        return maxLen;
    }
};
/*
Example 1:
Input: nums = [100,4,200,1,3,2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.

Example 2:
Input: nums = [0,3,7,2,5,8,4,6,0,1]
Output: 9
*/


//25. SET MATRIX ZEROES                                          {T.C = O(N^2), S.C = O(N)}
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
                if(row[i] || col[j]){                //if row or col updated(to 1)
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


//26. ROTATE IMAGE                                             {T.C = O(N^2), S.C = O(1)}
//TRANSPOSE THEN REVERSE EACH ROW
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();

        //transpose of matrix
        for(int i = 0 ; i < n ; i++){
            for(int j = i ; j < n ; j++){            //j from i not 0
                swap(matrix[i][j], matrix[j][i]);
            }
        }

        //reverse each row
        for(int i = 0 ; i < n ; i++){
            int left = 0;
            int right = n-1;
            while(left < right){
                swap(matrix[i][left], matrix[i][right]);
                left++;
                right--;
            }
        }
    }
};
/*
Example 1:
Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[7,4,1],[8,5,2],[9,6,3]]

Example 2:
Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
*/


//27 SPIRAL MATRIX                                                 {T.C = O(N), S.C = O(N)}
//USING POINTERS (ROW, COL, SROW, EROW, SCOL, ECOL)
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int>ans;
        int r = matrix.size();
        int c = matrix[0].size();

        int sRow = 0, eRow = r-1;
        int sCol = 0, eCol = c-1;
        
        while(sRow <= eRow && sCol <= eCol){
            for(int i = sCol ; i <= eCol; i++){  //printing starting row
                ans.push_back(matrix[sRow][i]);
            }
            sRow++;

            for(int j = sRow ; j <= eRow; j++){  //printing ending column
                ans.push_back(matrix[j][eCol]);
            }
            eCol--;

            if(sRow <= eRow){                        //checks for overflow
                for(int i = eCol ; i >= sCol; i--){  //printing ending row
                    ans.push_back(matrix[eRow][i]);
                }
                eRow--;
            }

            if(sCol <= eCol){                        //checks for overflow
                for(int j = eRow ; j >= sRow; j--){  //printing starting col
                    ans.push_back(matrix[j][sCol]);
                }
                sCol++;
            }
        }

        return ans;
    }
};
/*
Example 1:
Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,3,6,9,8,7,4,5]

Example 2:
Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]
*/


//28. SUBARRAY SUM EQUALS K (-VE NUMBERS ALLOWED)
//BRUTE FORCE 1 (3 LOOPS)                                        {T.C = O(N^3), S.C = O(1)}
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        int count = 0;
        for(int s = 0 ; s < n ; s++){
            for(int e = s ; e < n ; e++){
                int sum = 0;
                for(int i = s ; i <= e ; i++){
                    sum += nums[i];
                }
                if(sum == k){
                    count++;
                }
            }
        }
        return count;
    }
};

//BRUTE FORCE 2 (2 LOOPS)                                        {T.C = O(N^2), S.C = O(1)}
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        int count = 0;
        for(int s = 0 ; s < n ; s++){
            int sum = 0;
            for(int e = s ; e < n ; e++){
                sum += nums[e];
                if(sum == k){
                    count++;
                }
            }
        }
        return count;
    }
};

//OPTIMIZED APPROACH (MAP)                                           {T.C = O(N), S.C = O(N)}
//PREFIX SUM (MAP) {FOR LOOP}
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int>mp;
        mp.insert({0, 1});                      //initialize 0 (edge case)
        int sum = 0;
        int ans = 0;
        for(int i = 0 ; i < n ; i++){
            sum += nums[i];
            if(mp.find(sum-k) != mp.end()){
                ans += mp[sum-k];               //add freq not 1
            }
            mp[sum]++;
        }
        return ans;
    }
};
/*
Example 1:
Input: nums = [1,1,1], k = 2
Output: 2

Example 2:
Input: nums = [1,2,3], k = 3
Output: 2
*/


//29. PASCAL'S TRIANGLE                                                  {T.C = O(N^2), S.C = O(N^2)}
//2 LOOP ( 2ND LOOP FROM 1 TO i , SUM(UPPER COL ELEMENT + DIAGONAL UP ELEMENT))
//APPLICATION (xCy => search in pascal table)
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>>ans(numRows);
        for(int i = 0 ; i < numRows ; i++){
            ans[i] = vector<int>(i+1, 1);                     //each row (i+1 elemnetn with starting 1)
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


/*
NOTE:
MAJORITY ELEMENT (K-1) = N/K
*/
//30a. MAJORITY ELEMENT I  (element > n/2)                                            
//BRUTE FORCE (MAP)                                                          {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        unordered_map<int, int>mp;
        for(auto it : nums){
            mp[it]++;
            if(mp[it] > n/2){
                ans = it;
            }
        }
        return ans;
    }
};

//BOYER-MOORE VOTING ALGORITHM                                       {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int count = 0;
        int element = 0;

        //assumption
        for(auto it : nums){
            if(it == element){
                count++;
            }
            else if(count == 0){
                element = it;
                count = 1;
            }else{
                count--;
            }
        }

        //verification not needed question tells uniqe answer always
        return element;                   //atast all cancel ecept 1 required anser
    }
};
/*
Example 1:
Input: nums = [3,2,3]
Output: 3

Example 2:
Input: nums = [2,2,1,1,1,2,2]
Output: 2
*/


//30b. MAJORITY ELEMENT II     (element > n/3)                                      
//BRUTE FORCE (MAP & SET)                                                     {T.C = O(N), S.C = O(N)}
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int , int>mp;
        unordered_set<int>st;
        vector<int>ans;
        for(auto it : nums){
            mp[it]++;
            if(mp[it] > (n/3)){
                st.insert(it);
            }
        }
        for(auto it : st){
            ans.push_back(it);
        }
        return ans;
    }
};

//BOYER-MOORE VOTING ALGORITHM                                          {T.C = O(N), S.C = O(1)}
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int n = nums.size();
        int count1 = 0, count2 = 0;
        int element1 = 0; int element2 = 0;

        for(auto it : nums){
            if(it == element1){
                count1++;
            }else if(it == element2){
                count2++;
            }
            else if(count1 == 0){         //this line alwas after incr to remove edge case
                element1 = it;
                count1 = 1;
            }else if(count2 == 0){
                element2 = it;
                count2 = 1;
            }
            else{
                count1--;
                count2--;
            }
        }

        //verification
        vector<int>ans;
        int freq1 = 0;
        int freq2 = 0;
        for(auto it : nums){
            if(it == element1){
                freq1++;
            }else if(it == element2){
                freq2++;
            }
        }

        if(freq1 > n/3){
            ans.push_back(element1);
        }
        if(freq2 > n/3){
            ans.push_back(element2);
        }

        return ans;
    }
};
/*
Example 1:
Input: nums = [3,2,3]
Output: [3]

Example 2:
Input: nums = [1]
Output: [1]

Example 3:
Input: nums = [1,2]
Output: [1,2]
*/


//31. 3SUM                                                        {T.C = O(N^2), S.C = O(N^2)}
//LOOP(3 SUM = 0 to n-2(3-1))
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        set<vector<int>>st;                            //for unique answers only
        sort(nums.begin(), nums.end());
        for(int i = 0 ; i < n-2 ; i++){
            int start = i+1;
            int end = n-1;
            while(start < end){
                int sum = nums[i]+nums[start]+nums[end];
                if(sum == 0){
                    st.insert({nums[i], nums[start], nums[end]});
                    start++, end--;
                }else if(sum < 0){
                    start++;
                }else{
                    end--;
                }
            }
        }
        vector<vector<int>>ans;
        for(auto it : st){
            ans.push_back(it);
        }
        return ans;
    }
};
/*
Example 1:
Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation: 
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not matter.

Example 2:
Input: nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.

Example 3:
Input: nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0.
*/


//32. 4SUM                                                        {T.C = O(N^3), S.C = O(N^2)}
//LOOP(4 SUM = 0 to n-3(4-1) then n-2)
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n = nums.size();
        set<vector<int>>st;                        //for unique quadruplets
        sort(nums.begin(), nums.end());
        for(int i = 0 ; i < n-3 ; i++){
            for(int j = i+1; j < n-2 ; j++){
                int start = j+1;
                int end = n-1;
                while(start < end){
                    long long sum = (long long)nums[i]+(long long)nums[j]+(long long)nums[start]+(long long)nums[end];
                    if(sum == target){
                        st.insert({nums[i], nums[j], nums[start], nums[end]});
                        start++, end--;
                    }else if(sum < target){
                        start++;
                    }else{
                        end--;
                    }
                }
            }
        }
        vector<vector<int>>ans;
        for(auto it : st){
            ans.push_back(it);
        }
        return ans;
    }
};
/*
Example 1:
Input: nums = [1,0,-1,0,-2,2], target = 0
Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]

Example 2:
Input: nums = [2,2,2,2,2], target = 8
Output: [[2,2,2,2]]
*/


//33. LONGEST SUBARRAY WITH ZERO SUM                                 {T.C = O(N), S.C = O(N)}
//SIMILAR TO (28)
//PREFIX SUM (MAP) {FOR LOOP}
int getLongestZeroSumSubarrayLength(vector<int> &arr){
	int n = arr.size();
	unordered_map<int, int>mp;
	int i = 0 , j = 0;
	int sum =0;
	int maxLen = 0;
	for(int i = 0 ; i < n ; i++){
		sum += arr[i];
		if(sum == 0){
			maxLen = max(maxLen, i+1);
		}else if(mp.find(sum) != mp.end()){
			maxLen = max(maxLen, i - mp[sum]);
		}else{
			mp[sum] = i;
		}
	}
	return maxLen;
}

//PREFIX SUM (MAP) {WHILE LOOP}
int getLongestZeroSumSubarrayLength(vector<int> &arr){
	int n = arr.size();
	unordered_map<int, int>mp;
	int  j = 0;
	int sum =0;
	int maxLen = 0;
	while(j < n){
		sum += arr[j];
		if(sum == 0){
			maxLen = max(maxLen, j+1);
		}else if(mp.find(sum) != mp.end()){
			maxLen = max(maxLen, j - mp[sum]);
		}else{
			mp[sum] = j;
		}
		j++;
	}
	return maxLen;
}
/*
For Example:
For N = 5, and Arr = {1, -1, 0, 0, 1}, 
We have the following subarrays with zero sums: 
{{1, -1}, {1, -1, 0}, {1, -1, 0, 0}, {-1, 0, 0, 1}, {0}, {0, 0}, {0}}
Among these subarrays, {1, -1, 0, 0} and {-1, 0, 0, 1} are the longest subarrays with their sum equal to zero. Hence the answer is 4.
*/


//34. SUBARRAY WITH GIVEN XOR                                    {T.C = O(N), S.C = O(N)}
//PREFIX XOR
int solve(vector<int> &A, int B) {
    int n = A.size();
    unordered_map<int, int>mp;
    mp[0] = 1;                                 //initialize map (0 , 1)
    int count = 0;
    int Xor = 0;
    for(int i = 0 ; i < n ; i++){
        Xor = Xor ^ A[i];
        int x = Xor ^ B;                       //find previous found
        count += mp[x];                        //if found increase count
        mp[Xor]++;
    }
    return count;
}
/*
Input 1:
 A = [4, 2, 2, 6, 4]
 B = 6

Input 2:
 A = [5, 6, 7, 8, 9]
 B = 5
*/


//35. MERGE INTERVALS                                                 {T.C = O(N*LOGN), S.C = O(N)}
//SORTING, i[0] <= temp[1] -->> temp[1] = max(i[1], temp[1])
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>>ans;                //stores final merged intervals ans
        //base case
        if(intervals.size() == 0){
            return ans;
        }
        //sort the intervals
        sort(intervals.begin(), intervals.end());
        vector<int>tempInterval = intervals[0];           //store temprory answer
        for(auto i : intervals){
            if(i[0] <= tempInterval[1]){
                tempInterval[1] = max(i[1], tempInterval[1]);
            }
            else{
                ans.push_back(tempInterval);
                tempInterval = i;
            }
        }
        ans.push_back(tempInterval);
        
        return ans;
    }
};
/*
Example 1:
Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].

Example 2:
Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.
*/


//36. MERGE SORTED ARRAY                                                  {T.C = O(N), S.C = O(1)}
//3 POINTERS(last of num1, last of num2 , and k= n+m-1) then fill from last index(greater element)
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m-1, j = n-1, k = n+m-1;
        while(i >= 0 && j >= 0){
            if(nums1[i] > nums2[j]){
                nums1[k] = nums1[i];             //first fill last index(greater element)
                k--, i--;
            }else{
                nums1[k] = nums2[j];
                k--, j--;
            }
        }
        while(i >= 0){
            nums1[k] = nums1[i];
            k--, i--;
        }
        while(j >= 0){
            nums1[k] = nums2[j];
            k--, j--;
        }
    }
};
/*
Example 1:
Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
Output: [1,2,2,3,5,6]
Explanation: The arrays we are merging are [1,2,3] and [2,5,6].
The result of the merge is [1,2,2,3,5,6] with the underlined elements coming from nums1.

Example 2:
Input: nums1 = [1], m = 1, nums2 = [], n = 0
Output: [1]
Explanation: The arrays we are merging are [1] and [].
The result of the merge is [1].

Example 3:
Input: nums1 = [0], m = 0, nums2 = [1], n = 1
Output: [1]
Explanation: The arrays we are merging are [] and [1].
The result of the merge is [1].
Note that because m = 0, there are no elements in nums1. The 0 is only there to ensure the merge result can fit in nums1.
*/


//37. MISSING AND REPEATING NUMBERS                                     {T.C = O(N), S.C = O(N)}
//MAP
#include<unordered_map>
vector<int> findMissingRepeatingNumbers(vector < int > a) {
    int n = a.size();
    unordered_map<int, int>mp;
    vector<int>ans(2);
    for(auto it : a){
        mp[it]++;
    }

    int rep = 0, mis = 0;
    for(int i = 1 ; i <= n ; i++){
        if(mp[i] == 2){
            rep = i;
        }
        if(mp[i] == 0){
            mis = i;
        }
    }
    return {rep, mis};
}
/*
Input: ‘N’ = 4
‘A’ = [1, 2, 3, 2]
Output: {2, 4}
Explanation: The integer appearing twice is ‘2’, and the integer missing is ‘4’.
*/


//38. NUMBER OF INVERSIONS / COUNT INVERSIONS                         {T.C = O(N), S.C = O(1)}
//MERGESORT
int merge(vector<int> &arr, int low, int mid, int high) {
    vector<int> temp; // temporary array
    int left = low;      // starting index of left half of arr
    int right = mid + 1;   // starting index of right half of arr

    //Modification 1: cnt variable to count the pairs:
    int cnt = 0;

    //storing elements in the temporary array in a sorted manner//

    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left]);
            left++;
        }
        else {
            temp.push_back(arr[right]);
            cnt += (mid - left + 1); //Modification 2
            right++;
        }
    }

    // if elements on the left half are still left //

    while (left <= mid) {
        temp.push_back(arr[left]);
        left++;
    }

    //  if elements on the right half are still left //
    while (right <= high) {
        temp.push_back(arr[right]);
        right++;
    }

    // transfering all elements from temporary to arr //
    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }

    return cnt; // Modification 3
}

int mergeSort(vector<int> &arr, int low, int high) {
    int cnt = 0;
    if (low >= high) return cnt;
    int mid = (low + high) / 2 ;
    cnt += mergeSort(arr, low, mid);  // left half
    cnt += mergeSort(arr, mid + 1, high); // right half
    cnt += merge(arr, low, mid, high);  // merging sorted halves
    return cnt;
}

int numberOfInversions(vector<int>&a, int n) {
   
    return mergeSort(a, 0, n - 1);      // Count the number of pairs:
}
/*
Input:
A = [5, 3, 2, 1, 4], N = 5
Output:
7
Explanation: 
The pairs satisfying the condition for inversion are (1, 2), (1, 3), (1, 4), (1, 5), (2, 3), (2, 4), and (3, 4). 
The number of inversions in the array is 7.
*/


//39. REVERSE PAIRS
//BRUTE FORCE                                       {T.C = O(N^2), S.C = O(1)}
class Solution {
public:
    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        int count = 0;
        for(int i = 0 ; i < n ; i++){
            for(int j = i+1 ; j < n ; j++){
                if(nums[i] > 2*(nums[j])){
                    count++;
                }
            }
        }
        return count;
    }
};

//MERGE SORT                                                        {T.C = O(N*LOGN), S.C = O(N)}
class Solution {
public:
    void merge(vector<int> &arr, int low, int mid, int high) {
        vector<int> temp;
        int left = low;     
        int right = mid + 1;  

        while (left <= mid && right <= high) {
            if (arr[left] <= arr[right]) {
                temp.push_back(arr[left]);
                left++;
            }
            else {
                temp.push_back(arr[right]);
                right++;
            }
        }

        while (left <= mid) {
            temp.push_back(arr[left]);
            left++;
        }
        while (right <= high) {
            temp.push_back(arr[right]);
            right++;
        }
        for (int i = low; i <= high; i++) {
            arr[i] = temp[i - low];
        }
}

    int countPairs(vector<int> &arr, int low, int mid, int high) {
        int right = mid + 1;
        int cnt = 0;
        for (int i = low; i <= mid; i++) {
            while (right <= high && arr[i] >(long long) 2 * (long long)arr[right]) right++;
            cnt += (right - (mid + 1));
        }
        return cnt;
    }

    int mergeSort(vector<int> &arr, int low, int high) {
        int cnt = 0;
        if (low >= high) return cnt;
        int mid = (low + high) / 2 ;
        cnt += mergeSort(arr, low, mid); 
        cnt += mergeSort(arr, mid + 1, high); 
        cnt += countPairs(arr, low, mid, high); 
        merge(arr, low, mid, high); 
        return cnt;
    }
    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        return mergeSort(nums, 0, n-1);
    }
};
/*
Example 1:
Input: nums = [1,3,2,3,1]
Output: 2
Explanation: The reverse pairs are:
(1, 4) --> nums[1] = 3, nums[4] = 1, 3 > 2 * 1
(3, 4) --> nums[3] = 3, nums[4] = 1, 3 > 2 * 1

Example 2:
Input: nums = [2,4,3,5,1]
Output: 3
Explanation: The reverse pairs are:
(1, 4) --> nums[1] = 4, nums[4] = 1, 4 > 2 * 1
(2, 4) --> nums[2] = 3, nums[4] = 1, 3 > 2 * 1
(3, 4) --> nums[3] = 5, nums[4] = 1, 5 > 2 * 1
*/


//40. MAXIMUM PRODUCT SUBARRAY                                     {T.C = O(N), S.C = O(1)}
//KADANE'S ALGO (LEFT TO RIGHT THEN RIGHT TO LEFT )
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int maxProd = INT_MIN;

        int prod = 1;
        for(int i = 0 ; i < n ; i++){             //left to right
            prod *= nums[i];
            maxProd = max(maxProd, prod);
            if(prod == 0){
                prod = 1;
            }
        }
        prod = 1;                            //reset
        for(int j = n-1 ; j >= 0 ; j--){          //rigth to left
            prod *= nums[j];
            maxProd = max(maxProd, prod);
            if(prod == 0){
                prod = 1;
            }
        }
        return maxProd;
    }
};
/*
Example 1:
Input: nums = [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.

Example 2:
Input: nums = [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
*/