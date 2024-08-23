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


//07. ROTATE IMAGE                                             {T.C = O(N), S.C = O(1)}
//REVERSE EACH ROW, COL THEN REVERSE EACH ROW
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        for(int i = 0 ; i < n ; i++){
            for(int j = i ; j < n ; j++){
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        //reverse each row
        for(int i = 0 ; i < n; i++){
            int start = 0;
            int end = n-1;
            while(start < end){
                swap(matrix[i][start], matrix[i][end]);
                start++, end--;
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


//08. MERGE INTERVALS                                                 {T.C = O(N*LOGN), S.C = O(N)}
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


//09. MERGE SORTED ARRAY                                                  {T.C = O(N), S.C = O(1)}
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


//10. FIND THE DUPLICATE NUMBER                                  {T.C = O(N), S.C = O(1)}
//SLOW AND FAST POINTER (LIKE LINKED LIST)
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = nums[0];
        int fast = nums[0];

        //move slow and fast (2 steps) untill they intersect
        do{                                       //execute atleast ones
            slow = nums[slow];
            fast = nums[nums[fast]];
        }while(slow != fast);

        slow = nums[0];                               //reset slow
        //move slow and fast (1 steps) untill they intersect again {intersecting point is duplicate}
        while(slow != fast){
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};
/*
Example 1:
Input: nums = [1,3,4,2,2]
Output: 2

Example 2:
Input: nums = [3,1,3,4,2]
Output: 3

Example 3:
Input: nums = [3,3,3,3,3]
Output: 3
*/


//11. REPEAT AND MISSING                                         {T.C = O(N), S.C = O(N)}
//MAP
pair<int,int> missingAndRepeating(vector<int> &arr, int n)
{
	unordered_map<int, int>mp;
	for(auto it : arr){
		mp[it]++;
	}
	int missing = -1, repeating = -1;
	for(int i = 1; i <= n ; i++){
		if(mp[i] == 0){
			missing = i;
		}
		else if(mp[i] == 2){
			repeating = i;
		}
		
		if(missing != -1 && repeating != -1){
			break;
		}
	}
	return {missing, repeating};
}

//USING MATHS FORMULA                                          {T.C = O(N), S.C = O(1)}
vector<int> findMissingRepeatingNumbers(vector<int> a) {
    long long n = a.size();

    // Find Sn and S2n:
    long long SN = (n * (n + 1)) / 2;
    long long S2N = (n * (n + 1) * (2 * n + 1)) / 6;

    // Calculate S and S2:
    long long S = 0, S2 = 0;
    for (int i = 0; i < n; i++) {
        S += a[i];
        S2 += (long long)a[i] * (long long)a[i];
    }

    //S-Sn = X-Y:
    long long val1 = S - SN;

    // S2-S2n = X^2-Y^2:
    long long val2 = S2 - S2N;

    //Find X+Y = (X^2-Y^2)/(X-Y):
    val2 = val2 / val1;

    //Find X and Y: X = ((X+Y)+(X-Y))/2 and Y = X-(X-Y),
    // Here, X-Y = val1 and X+Y = val2:
    long long x = (val1 + val2) / 2;
    long long y = x - val1;

    return {(int)x, (int)y};
}

int main()
{
    vector<int> a = {3, 1, 2, 5, 4, 6, 7, 5};
    vector<int> ans = findMissingRepeatingNumbers(a);
    cout << "The repeating and missing numbers are: {"
         << ans[0] << ", " << ans[1] << "}\n";
    return 0;
}
/*
Input
5
5 4 2 4 1 
Output
3 4
*/


//12. NUMBER OF INVERSIONS / COUNT INVERSIONS                         {T.C = O(N), S.C = O(1)}
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
    cnt += mergeSort(arr, low, mid);           // left half
    cnt += mergeSort(arr, mid + 1, high);      // right half
    cnt += merge(arr, low, mid, high);         // merging sorted halves
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


//19. 2 SUM                                               {T.C = O(N), S.C = O(N)}
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


//20a. 3 SUM                                                       {T.C = O(N^2), S.C = O(N^2)}
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


//20. 4 SUM                                                        {T.C = O(N^3), S.C = O(N^2)}
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


//21. LONGEST CONSECUTIVE SEQUENCE                               {T.C = O(N), S.C = O(N)}
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


//22a. LONGEST SUB-ARRAY WITH SUM K (VARIABLE SLIDIING WINDOW)                {T.C = O(N), S.C = O(1)}
//ONLY FOR POSITIVE INTEGERS
class Solution{
    public:
    int lenOfLongSubarr(int a[],  int n, int k) 
    { 
        int i = 0, j = 0;
        int sum = 0;
        int maxLen = 0;
        while(j < n){
            sum += a[j];
            if(sum == k){
                maxLen = max(maxLen, (j-i+1));
            }
            if(sum > k){
                while(sum > k){
                    sum -= a[i];
                    i++;
                }
            }
            j++;
        }
        return maxLen;
    } 
};

//22b. LONGEST SUB-ARRAY WITH SUM K (VARIABLE SLIDIING WINDOW)                {T.C = O(N), S.C = O(1)}
//FOR NEGATIVE NUMBERS
//BRUTE FORCE                                                                 {T.C = O(N^2), S.C = O(1)}
class Solution{
    public:
    int lenOfLongSubarr(int a[],  int n, int k) 
    { 
        int maxi = 0;
        for(int i = 0 ; i < n ; i++){
            int sum = 0;                               //sum is there not in top (reset sum)
            for(int j = i ; j < n ; j++){
                sum += a[j];
                if(sum == k){
                    maxi = max(maxi, j-i+1);
                }
            }
        }
        return maxi;
    } 
};

//OPTIMIZED APPROACH (USING MAP)                                               {T.C = O(N), S.C = O(N)}
class Solution{ 
    public:
    int lenOfLongSubarr(int a[],  int n, int k) 
    { 
        int maxLen = 0;
        int sum = 0;
        unordered_map<int, int>mp;
        for(int i = 0 ; i < n ; i++){
            sum += a[i];
            if(sum == k){
                maxLen = max(maxLen, i+1);              //for 0 based indexing             //length of subarray
            }
            if(mp.find(sum-k) != mp.end()){
                maxLen = max(maxLen, i-mp[sum-k]);
            }
            if(mp.find(sum) == mp.end()){               //prev not found sum
                mp[sum] = i;
            }
        }
        return maxLen;
    } 
};
/*
Input :
A[] = {10, 5, 2, 7, 1, 9}
K = 15
Output : 4
Explanation:
The sub-array is {5, 2, 7, 1}.
*/


//23. SUBARRAY WITH GIVEN XOR                                    {T.C = O(N), S.C = O(N)}
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


//24. LONGEST SUBSTRING WITHOUT REPEATING CHARACTERS                  {T.C = O(N), S.C = O(N)}
//MAP (VARIABLE SIZE SLIDIING WINDOW)
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.length();
        unordered_map<char, int>mp;
        int i = 0, j = 0, maxLen = 0;
        while(j < n){
            mp[s[j]]++;
            if(mp.size() == j-i+1){
                maxLen = max(maxLen, j-i+1);
            }
            if(mp.size() < j-i+1){                //remember its less then condition others have greater
                while(mp.size() < j-i+1){
                    mp[s[i]]--;
                    if(mp[s[i]] == 0){
                        mp.erase(s[i]);
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


/*-----------------------------------------------THE END---------------------------------------------------------------*/