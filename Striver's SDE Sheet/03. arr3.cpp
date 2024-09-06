#include<bits/stdc++.h>
using namespace std;

//DAY 3: ARRAY III -----------------------------------------------------------------------------------------------------
//13. SEARCH A 2D MATRIX                                      {T.C = O(LOG(M*N)), S.C = O(1)}
//BINARY SEARCH
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int row = matrix.size();
        int col = matrix[0].size();

        int start = 0;
        int end = row*col-1;

        while(start <= end){
            int mid = start + (end-start)/2;                 //(start+end)/2
            int element = matrix[mid/col][mid%col];          //mid/col = row, mid%col = col
            if(element == target){
                return true;
            }else if(element > target){
                end = mid-1;
            }else if(element < target){
                start = mid+1;
            }
        }
        return false;
    }
};
/*
Example 1:
Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
Output: true

Example 2:
Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
Output: false
*/


//14. POW(X, N)                                               {T.C = O(LOGN), S.C = O(1)}
//MATHS & RECURSION
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
            return x*solve(x*x, (n-1)/2); //2^9 = 2*(2*2^4)
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


/*
NOTE:
MAJORITY ELEMENT (K-1) = N/K
*/
//15. MAJORITY ELEMENT I  (element > n/2)                                            
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


//16. MAJORITY ELEMENT II     (element > n/3)                                      
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


//17. UNIQUE PATHS                                                     {T.C = O(N), S.C = O(N)}
//DP
class Solution {
public:
    int solveMem(int n, int m, vector<vector<int>>&dp, int i, int j){
        //base case (initial position is final position)
        if(i == n-1 && j == m-1){
            return 1;
        }
        //boundary case
        if(i >= n || j >= m){
            return 0;
        }
        
        //step3 if ans already present retur it
        if(dp[i][j] != -1){
            return dp[i][j];
        }

        int down = solveMem(n, m, dp, i+1, j);
        int right = solveMem(n, m, dp, i, j+1);

        //step2 store ans in dp
        dp[i][j] = down + right;                      //total count
        return dp[i][j];
    }
    int uniquePaths(int n, int m) {
        //step1 create a dp vector
        vector<vector<int>>dp(n+1, vector<int>(m+1, -1));
        return solveMem(n, m, dp, 0, 0);              //initial index = 0, 0
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


//18. REVERSE PAIRS
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