#include<bits/stdc++.h>
using namespace std;

//DAY 11: BINARY SEARCH -----------------------------------------------------------------------------------------------------
//61. FIND NTH ROOT
//BRUTE FORCE                                                          {T.C = O(M*N), S.C = O(1)}
int NthRoot(int n, int m) {
  for(int i = 1 ; i <= m ;i++){
    if(pow(i, n) == m) return i;
  }
  return -1;
}

//USING BINARY SEARCH                                                  {T.C = O(N*LOGM), S.C = O(1)}
int NthRoot(int n, int m) {
  int start = 1, end = m;
  while(start <= end){
    int mid = (start + end)/2;
    double ans = pow(mid, n);                             //POW RETURN FLOATING NUMBER
    if(ans == m) return mid;
    else if(ans < m) start = mid+1;
    else end = mid-1;
  }
  return -1;
}
/*
Input: ‘n’ = 3, ‘m’ = 27
Output: 3
Explanation: 
3rd Root of 27 is 3, as (3)^3 equals 27.
*/


//62. MEDIAN IN A ROW WISE SORTED MATRIX
//BRUTE FORCE (TLE)                                                        {T.C = O(N*M(LOG(N*M)), S.C = O(N+M))}
class Solution{   
public:
    int median(vector<vector<int>> &matrix, int R, int C){
        vector<int>ans;
        for(int i = 0 ; i < R; i++){
            for(int j = 0 ; j < C ; j++){
                ans.push_back(matrix[i][j]);
            }
        }
        sort(ans.begin(), ans.end());
        int n = ans.size();
        return ans[n/2];
    }
};

//USING BINARY SERACH (ON VALUE)                                            {T.C = O(RANGE*RLOGC), S.C = O(1)}
class Solution{   
public:
    //BINARY SEARCH ON ANSWER
    int median(vector<vector<int>> &matrix, int R, int C){
        int start = INT_MAX;           //range of value (low to max val)
        int end   = INT_MIN;
        for(int i = 0 ; i < R ; i++){  //low = 1st col and high = last col (row wise sorted)
            start = min(start, matrix[i][0]);
            end   = max(end  , matrix[i][C-1]);
        }
        
        int desired = (R*C + 1)/2;                            //median (add)
        while(start <= end){
            int mid = (start+end)/2;
            int countSmaller = 0;
            
            for(int i = 0 ; i < R ; i++){    //find count of elements smaller then mid
                //upper_bound gives just greater element or equal to  of x(before that all smaller)
                countSmaller += upper_bound(matrix[i].begin(), matrix[i].end(), mid) - matrix[i].begin(); //-m[i].begin() for find val not iterator
            }
            
            if(countSmaller < desired) start = mid+1;
            else end = mid-1;
        }
        return start;                              //start gives median
    }
};
/*
Example 1:
Input:
R = 3, C = 3
M = [[1, 3, 5], 
     [2, 6, 9], 
     [3, 6, 9]]
Output: 5
Explanation: Sorting matrix elements gives 
us {1,2,3,3,5,6,6,9,9}. Hence, 5 is median. 

Example 2:
Input:
R = 3, C = 1
M = [[1], [2], [3]]
Output: 2
Explanation: Sorting matrix elements gives 
us {1,2,3}. Hence, 2 is median.
*/


//63. SINGLE ELEMENT IN A SORTED ARRAY
//BRUTE FORCE USING MAP                                                {T.C = O(N), S.C = O(N)}
class Solution {
public:
    //brute force (using map)
    int singleNonDuplicate(vector<int>& nums) {
        // unordered_map<int,int>mp(nums.begin(), nums.end());
        unordered_map<int,int>mp;
        for(auto it : nums){
            mp[it]++;
        }
        for(auto it : mp){
            if(it.second == 1) return it.first;
        }
        return -1;
    }
};

//USING BINARY SEARCH (IDX)                                              {T.C = O(LOGN), S.C = O(1)}
class Solution {
public:
    //(evenIdx, x,  oddIdx) same then eliminate left part
    //(oddIdx, x, evenIdx) same then eliminate right part
    int singleNonDuplicate(vector<int>& nums) {
        int n = nums.size();
        //base cases
        if(n == 1) return nums[0];
        if(nums[0] != nums[1]) return nums[0];                //1st element is single element
        if(nums[n-1] != nums[n-2]) return nums[n-1];          //last element is single

        int start = 0, end = n-2;               //shirnk space(handled above)  //not n-1(checking mid+1)
        while(start <= end){
            int midIdx = start + (end-start)/2;
            if(nums[midIdx-1] != nums[midIdx] && nums[midIdx] != nums[midIdx+1]) return nums[midIdx];  //left and right both not match(single element)
            else if((midIdx % 2 == 1 && nums[midIdx-1] == nums[midIdx] ) ||
                     (midIdx % 2 == 0 && nums[midIdx] == nums[midIdx+1])  ){      //left sorted (eleminate left)
                start = midIdx+1;
            }else{
                end = midIdx-1;
            }
        }

        return -1;
    }
};
/*
Example 1:
Input: nums = [1,1,2,3,3,4,4,8,8]
Output: 2

Example 2:
Input: nums = [3,3,7,7,10,11,11]
Output: 10
*/


//64. SEARCH IN ROTATED SORTED ARRAY                                       {T.C = O(LOGN), S.C = O(1)}
//BINARY SEARCH ON INDEX
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int start = 0, end = n-1;
        while(start <= end){
            int midIdx = (start + end)/2;
            if(nums[midIdx] == target) return midIdx;
            else if(nums[start] <= nums[midIdx]){                  //left part is sorted
                if(nums[start] <= target && target <= nums[midIdx]) end = midIdx-1;  //ans in left 
                else start = midIdx+1;
            }else{ //nums[start] > nums[midIdx]                   //right part is sorted
                if(nums[midIdx] <= target && target <= nums[end]) start = midIdx+1;  //ans in right
                else end = midIdx-1;
            }
        }
        return -1;
    }
};
/*
Example 1:
Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4

Example 2:
Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1

Example 3:
Input: nums = [1], target = 0
Output: -1
*/


//65. MEDIAN OF TWO SORTED ARRAY                                           {T.C = O(LOG(MIN{N,M})), S.C = O(1)}
//BINARY SEARCH ON VALUE
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        if(n > m) return findMedianSortedArrays(nums2, nums1);  //n should be smaller 

        int start = 0, end = n;
        while(start <= end){
            int Px = (start+end)/2;
            int Py = (m+n+1)/2 - Px;       //total left part(m+n+1 ele)

            //left partition(x1,y1)
            int x1 = (Px == 0) ? INT_MIN : nums1[Px-1];   //px-1 (last index of half partition)
            int y1 = (Py == 0) ? INT_MIN : nums2[Py-1];

            //right partition(x2, y2)
            int x2 = (Px == n) ? INT_MAX : nums1[Px];
            int y2 = (Py == m) ? INT_MAX : nums2[Py];

            if(x1 <= y2 && y1 <= x2){
                if((m+n) % 2 == 1) return max(x1, y1);   //odd(total length)
                else return (max(x1,y1) + min(x2, y2)) / 2.0;
            }else if(x1 > y2) end = Px-1;
            else start = Px+1;
        }
        return -1;
    }
};
/*
Example 1:
Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.

Example 2:
Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
*/


//66. KTH ELEMENT OF 2 ARRAYS                                          
//TWO POINTERS + EXTRA SPACE                                               {T.C = O(N+M), S.C = O(N+M)}
class Solution {
  public:
    int kthElement(int k, vector<int>& arr1, vector<int>& arr2) {
        int n = arr1.size(), m = arr2.size();
        vector<int>arr3;
        int i = 0, j = 0;
        while(i < n && j < m){
            if(arr1[i] < arr2[j]){
                arr3.push_back(arr1[i]);
                i++;
            }else{
                arr3.push_back(arr2[j]);
                j++;
            }
        }
        while(i < n){                               //arr2 exhausted push arr1 directly
            arr3.push_back(arr1[i]);
            i++;
        }
        while(j < m){                              //arr1 exhausted push arr2 directly
            arr3.push_back(arr2[j]);
            j++;
        }
        return arr3[k-1];
    }
};

//USING BINARY SEARCH ON VALUES (LIKE MEDIAN IN 2 SORTED ARRAYS)             {T.C = O(LOG(MIN{M, N})), S.C = O(1)}
class Solution {
  public:
    int kthElement(int k, vector<int>& arr1, vector<int>& arr2) {
        int n = arr1.size(), m = arr2.size();
        if(n > m) return kthElement(k, arr2, arr1);              //n should be smaller
        
        // int start = 0, end = n;                        //for median
        int start = max(0, k-m), end = min(k, n);
        while(start <= end){
            int Px = (start + end)/2;                     //just after partition
            int Py = k-Px;                                //(n+m+1)/2-Px (in median)
            
            //left partitian
            int x1 = (Px == 0) ? INT_MIN : arr1[Px-1];    // x1 | x2
            int y1 = (Py == 0) ? INT_MIN : arr2[Py-1];    // y1 | y2
            
            //right partition
            int x2 = (Px == n) ? INT_MAX : arr1[Px];
            int y2 = (Py == m) ? INT_MAX : arr2[Py]; 
            
            
            /*
            //for finding medain logic rest all same
            if(x1 <= y2 && y1 <= x2){                     //criss cross check
                if((n+m)/2 % 2 == 1) return max(x1, y1);  //odd total len
                else return (max(x1, y1) + min(x2, y2)) / 2.0;
            }
            */
            if(x1 <= y2 && y1 <= x2) return max(x1, y1);     //return kth element
            else if(x1 > y2) end = Px-1;
            else start = Px+1;
        }
        return -1;
    }
};
/*
Examples :
Input: k = 5, arr1[] = [2, 3, 6, 7, 9], arr2[] = [1, 4, 8, 10]
Output: 6
Explanation: The final combined sorted array would be - 1, 2, 3, 4, 6, 7, 8, 9, 10. The 5th element of this array is 6.

Input: k = 7, arr1[] = [100, 112, 256, 349, 770], arr2[] = [72, 86, 113, 119, 265, 445, 892]
Output: 256
Explanation: Combined sorted array is - 72, 86, 100, 112, 113, 119, 256, 265, 349, 445, 770, 892. 7th element of this array is 256.
*/


//67. ALLOCATE MINIMUM PAGES  (min(max))                                               {T.C = O(N*LOGN), S.C = O(1)}
//BINARY SEARCH ON VALUE
class Solution {
  public:
    bool isValid(int arr[], int n, int k, int maxPage){
        int studentCount = 1, pageSum = 0;
        for(int i = 0 ; i < n; i++){
            if(arr[i] > maxPage) return false;          //not allowed
            
            if(arr[i] + pageSum <= maxPage) pageSum += arr[i];
            else{
                studentCount++;
                if(studentCount > k) return false;
                else pageSum = arr[i];
            }
        }
        return true;
    }
    long long findPages(int n, int arr[], int k) {
        //base case
        if(n < k) return -1;                    //pages < students (not possible)
        long long ans = -1;                     //not possible to partition
        int maxEle = 0, sum = 0;
        for(int i = 0 ; i < n ; i++){
            maxEle = max(maxEle, arr[i]);
            sum += arr[i];
        }
        
        int start = maxEle;                         //lowest range
        int end   = sum;
        
        while(start <= end){
            int mid = (start + end)/2;
            
            if(isValid(arr, n, k, mid)){
                ans = mid;
                end = mid-1;                          //FINDING min of maxpage
            }else{
                start = mid+1;
            }
        }
        return ans;
    }
};
/*
Input: n = 4, arr[] = [12, 34, 67, 90], m = 2
Output: 113
Explanation: Allocation can be done in following ways:
{12} and {34, 67, 90} Maximum Pages = 191
{12, 34} and {67, 90} Maximum Pages = 157
{12, 34, 67} and {90} Maximum Pages =113.
Therefore, the minimum of these cases is 113, which is selected as the output.

Input: n = 3, arr[] = [15, 17, 20], m = 5
Output: -1
Explanation: Allocation can not be done.
*/


//68. AGGRESSIVE COW      (max(min))                                                   {T.C = O(N*LOGN), S.C = O(1)}
//similar to allocation books problem
class Solution {
public:
    bool isValid(vector<int>&stalls, int n, int k , int minDis){
        int cowCount = 1, lastPos = stalls[0];

        for(int i = 1 ; i < n; i++){               //0 handle above
            if(stalls[i]-lastPos >= minDis){
                cowCount++;
                if(cowCount == k) return true;
                lastPos = stalls[i];
            }
        }
        return false;
    }
    int solve(int n, int k, vector<int> &stalls) {
        sort(stalls.begin(), stalls.end());       //sort is neccessary
        int start = 0;
        int end   = stalls[n-1];
        
        int ans = -1;
        while(start <= end){
            int mid = (start + end)/2;
            if(isValid(stalls, n, k, mid)){
                ans = mid;
                start = mid+1;                     //finding max(min) dist
            }else{
                end = mid-1;
            }
        }
        return ans;
    }
};
/*
Input:
n=5 
k=3
stalls = [1 2 4 8 9]
Output:
3
Explanation:
The first cow can be placed at stalls[0], 
the second cow can be placed at stalls[2] and 
the third cow can be placed at stalls[3]. 
The minimum distance between cows, in this case, is 3, 
which also is the largest among all possible ways.

Example 2:
Input:
n=5 
k=3
stalls = [10 1 2 7 5]
Output:
4
Explanation:
The first cow can be placed at stalls[0],
the second cow can be placed at stalls[1] and
the third cow can be placed at stalls[4].
The minimum distance between cows, in this case, is 4,
which also is the largest among all possible ways.
*/