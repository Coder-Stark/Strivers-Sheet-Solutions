//BINARY SEARCH
#include<bits/stdc++.h>
using namespace std;

//BINARY SEARCH ON 1D ARRAYS                                        {T.C = O(LOGN), S.C = O(1)}
//41. BINARY SEARCH / BINARY SEARCH TO FIND X IN SORTED ARRAY
//SIMPLE BS
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int start = 0;
        int end = n-1;
        while(start <= end){
            int mid = start + (end-start)/2;
            if(nums[mid] == target){
                return mid;
            }else if(nums[mid] < target){
                start = mid+1;
            }else{
                end = mid-1;
            }
        }
        return -1;
    }
};
/*
Example 1:
Input: nums = [-1,0,3,5,9,12], target = 9
Output: 4
Explanation: 9 exists in nums and its index is 4

Example 2:
Input: nums = [-1,0,3,5,9,12], target = 2
Output: -1
Explanation: 2 does not exist in nums so return -1
*/


//42. FLOOR IN A SORTED ARRAY                                    {T.C = O(LOGN), S.C = O(1)}
//FOR LOWER BOUND UPDATE ANS = MID IN START
class Solution{
  public:
    int findFloor(vector<long long> v, long long n, long long x){
        long long start = 0;
        long long end = n-1;
        long long ans = -1;
        while(start <= end){
            long  long mid = start + (end-start)/2;
            if(v[mid] == x){
                return mid;
            }else if(v[mid] < x){
                ans = mid;
                start = mid+1;
            }else{
                end = mid-1;
            }
        }
        return ans;                            //lower bound(starting element)
    }
};
/*
Example 1:
Input:
N = 7, x = 0 
arr[] = {1,2,8,10,11,12,19}
Output: -1
Explanation: No element less 
than 0 is found. So output 
is "-1".

Example 2:
Input:
N = 7, x = 5 
arr[] = {1,2,8,10,11,12,19}
Output: 1
Explanation: Largest Number less than 5 is
2 (i.e K = 2), whose index is 1(0-based 
indexing).
*/


//43. CEIL THE FLOOR / FINDING FLOOR AND CEIL                            {T.C = O(N*LOGN), S.C = O(1)}
//(NOT SORTED) FOR LOWER BOUND UPDATE ANS1 = MID IN START AND ANS2 IN END
//(NOT SORTED) FOR LOWER BOUND UPDATE ANS1 = MID IN START AND ANS2 IN END
pair<int, int> getFloorAndCeil(int arr[], int n, int x) {
    sort(arr, arr+n);
    int start = 0;
    int end  = n-1;
    int ans1 = -1, ans2 = -1;                  //ans1 = floor, ans2 = ceil
    while(start <= end){
        int mid = start + (end-start)/2;
        if(arr[mid] == x){
            return {arr[mid], arr[mid]};
        }else if(arr[mid] < x){
            ans1 = arr[mid];                   //finding element not index
            start = mid+1;
        }else{
            ans2 = arr[mid];
            end = mid-1;
        }
    }
    return {ans1, ans2};
}
/*
Example 1:
Input:
N = 8, X = 7
Arr[] = {5, 6, 8, 9, 6, 5, 5, 6}
Output: 6 8
Explanation:
Floor of 7 is 6 and ceil of 7 
is 8.

Example 2:
Input:
N = 8, X = 10
Arr[] = {5, 6, 8, 9, 6, 5, 5, 6}
Output: 9 -1
Explanation:
Floor of 10 is 9 but ceil of 10 is not 
possible.
*/


//44. SEARCH INSERT POSITION                                          {T.C = O(LOGN), S.C = O(1)}             
//FINALLY RETURN START(CORRECT POSITION)
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
        int start = 0;
        int end = n-1;
        
        if(target > nums[end]){
            return end+1;                             //last + 1 index or new element
        }
        while(start <= end){  
            int mid = (start + end)/2;
            if(nums[mid] == target){
                return mid;
            }
            else if(nums[mid] < target){
                start = mid+1;
            }
            else{ //(nums[mid] > target)
                end = mid-1;
            }
        }
        return start;                                //return low or start because after breaking loop it will show correct position to insert
    }
};
/*
Example 1:
Input: nums = [1,3,5,6], target = 5
Output: 2

Example 2:
Input: nums = [1,3,5,6], target = 2
Output: 1

Example 3:
Input: nums = [1,3,5,6], target = 7
Output: 4
*/


//45. CEIL THE FLOOR / FINDING FLOOR AND CEIL                            {T.C = O(LOGN), S.C = O(1)}
//(SORTED) FOR LOWER BOUND UPDATE ANS1 = MID IN START AND ANS2 IN END
pair<int, int> getFloorAndCeil(int arr[], int n, int x) {
    sort(arr, arr+n);
    int start = 0;
    int end  = n-1;
    int ans1 = -1, ans2 = -1;                  //ans1 = floor, ans2 = ceil
    while(start <= end){
        int mid = start + (end-start)/2;
        if(arr[mid] == x){
            return {arr[mid], arr[mid]};
        }else if(arr[mid] < x){
            ans1 = arr[mid];                   //finding element not index
            start = mid+1;
        }else{
            ans2 = arr[mid];
            end = mid-1;
        }
    }
    return {ans1, ans2};
}
/*
Input: 
n=6, x=5, a=[3, 4, 7, 8, 8, 10]   
Output:
4
Explanation:
The floor and ceiling of 'x' = 5 are 4 and 7, respectively.
*/


//46. FIND FIRST AND LAST POSITION OF ELEMENT IN SORTED ARRAY                  {T.C = O(LOGN), S.C = O(1)}
//WE HAVE TO APPLY 2 CALL FUNC (FIRST , LAST) UPDATE ELEMENT == TARGET {FIRST, LAST}
class Solution {
public:
    int firstPos(vector<int>&nums, int target){
        int n = nums.size();
        int start = 0, end = n-1;
        int first = -1;
        while(start <= end){
            int mid = start + (end-start)/2;
            if(nums[mid] == target){
                first = mid;
                end = mid-1;                          //search only in first half
            }else if(nums[mid] < target){
                start = mid+1;
            }else{
                end = mid-1;
            }
        }
        return first;
    }
    int lastPos(vector<int>&nums, int target){
        int n = nums.size();
        int start = 0, end = n-1;
        int last = -1;
        while(start <= end){
            int mid = start + (end-start)/2;
            if(nums[mid] == target){
                last = mid;
                start = mid+1;                              //search in second half
            }else if(nums[mid] < target){
                start = mid+1;
            }else{
                end = mid-1;
            }
        }
        return last;
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        int first = firstPos(nums, target);
        int last = lastPos(nums, target);
        
        return {first, last};
    }
};
/*
Example 1:
Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]

Example 2:
Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]

Example 3:
Input: nums = [], target = 0
Output: [-1,-1]
*/


//47. NUMBER OF OCCURRENCE / COUNT OCC OF A NUMBER IN SORTED ARRAYS WITH DUPLICATES {T.C = O(LOGN), S.C = O(1)}
//ANS = LB-UB
class Solution{
public:	
	int count(int arr[], int n, int x) {
	    int ans = 0;
	    int lb = lower_bound(arr, arr+n, x) - arr;
	    int ub = upper_bound(arr, arr+n, x) - arr;
	    ans = abs(lb-ub);
	    return ans == 0 ? 0 : ans;
	}
};
/*
Example 1:
Input:
N = 7, X = 2
Arr[] = {1, 1, 2, 2, 2, 2, 3}
Output: 4
Explanation: 2 occurs 4 times in the
given array.

Example 2:
Input:
N = 7, X = 4
Arr[] = {1, 1, 2, 2, 2, 2, 3}
Output: 0
Explanation: 4 is not present in the
given array.
*/


//48. SEARCH IN ROTATED SORTED ARRAY (DISTINC/UNIQUE VALUES)                        {T.C = O(LOGN), S.C = O(1)}   
//LEFT SORTED(LOW-TARGET-MID) , RIGHT SORTED (MID-TARGET-HIGH)
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int start = 0; 
        int end = n-1;

        while(start <= end){                  //is equal to for last element case
            int mid = start + (end-start)/2;
            if(nums[mid] == target){
                return mid;
            }
            
            if(nums[start] <= nums[mid]){              //left part is sorted
                if(nums[start] <= target && target <= nums[mid]){   //check between left range (nums[start] to nums[mid])
                    end = mid-1;
                }else{
                    start = mid+1;
                }
            }else{ //(nums[start] > nums[mid])        //right part is sorted
                if(nums[end] >= target && target >= nums[mid]){    //check between right range (nums[mid] to nums[end])
                    start = mid+1;
                }else{
                    end = mid-1;
                }
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


//49. SEARCH IN ROTATED SORTED ARRAY II      (NOT DISTINCT / NOT UNIQUE VALUE)  {T.C = O(LOGN), S.C = O(1)}
//JUST HANDLE DUPLICATE (SHRINK SEARCH SPACE) , OTHER WISE SAME
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int n = nums.size();
        int start = 0, end = n-1;
        while(start <= end){
            int mid = start + (end-start)/2;
            if(nums[mid] == target){
                return true;
            }
            
            //for duplicate add this code only
            if(nums[start] == nums[mid] && nums[mid] == nums[end]){  //shrink search space
                start++;
                end--;
                continue;
            }
            
            if(nums[start] <= nums[mid]){
                if(nums[start] <= target && target <= nums[mid]){
                    end = mid-1;
                }else{
                    start = mid + 1;
                }
            }else {   //nums[end] > nums[mid]
                if(nums[end] >= target && target >= nums[mid]){
                    start = mid+1;
                }else{
                    end = mid-1;
                }
            }
        }
        return false;
    }
};
/*
Example 1:
Input: nums = [2,5,6,0,0,1,2], target = 0
Output: true

Example 2:
Input: nums = [2,5,6,0,0,1,2], target = 3
Output: false
*/


//50. FIND MINIMUM IN ROTATED SORTED ARRAY                    {T.C = O(LOGN), S.C = O(1)}
//NUMS[START] > NUMS[MID] ? END = MID : START = MID+1
class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size();
        int start = 0;
        int end = n - 1;

        while (start < end) {
            int mid = start + (end - start) / 2;
            // If the array is not rotated (sorted in ascending order), return the first element
            if (nums[start] < nums[end]) {
                return nums[start];
            }
            if (nums[start] > nums[mid]) {   // Minimum element lies in the left half
                end = mid;
            } else {                         // Minimum element lies in the right half
                start = mid + 1;
            }
        }

        return nums[start];                  // the minimum element is at nums[start]
    }
};

//ANOTHER APPROACH (GENERIC)
class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size();
        int start = 0;
        int end = n - 1;
        int ans =  INT_MAX; 

        while (start <= end) {
            int mid = start + (end - start) / 2;
            // If the array is not rotated (sorted in ascending order), return the first element
            if (nums[start] <= nums[end]) {
                ans = min(ans, nums[start]);
                break;
            }
            if (nums[start] <= nums[mid]) {      // Minimum element lies in the left half
                ans = min(ans, nums[start]);
                start = mid+1;
            } else { //nums[start] > nums[mid]   // Minimum element lies in the right half
                ans = min(ans, nums[mid]);
                end = mid-1;
            }
        }

        return ans;     
    }
};
/*
Example 1:
Input: nums = [3,4,5,1,2]
Output: 1
Explanation: The original array was [1,2,3,4,5] rotated 3 times.

Example 2:
Input: nums = [4,5,6,7,0,1,2]
Output: 0
Explanation: The original array was [0,1,2,4,5,6,7] and it was rotated 4 times.

Example 3:
Input: nums = [11,13,15,17]
Output: 11
Explanation: The original array was [11,13,15,17] and it was rotated 4 times. 
*/


//51. ROTATION / FIND HOW MANY TIMES ARRAY IS ROTATED           {T.C = O(LOGN), S.C = O(1)}
//SAME AS ABOVE + INDEX
class Solution{
public:	
	int findKRotation(int arr[], int n) {
	    int start = 0, end = n-1;
	    int ans = INT_MAX, idx = -1;
	    while(start <= end){
	        int mid = start + (end-start)/2;
	        if(arr[start] <= arr[end]){
	            if(arr[start] < ans){
	                ans = arr[start];
	                idx = start;
	            }
	            break;
	        }
	        if(arr[start] <= arr[mid]){
	            if(arr[start] < ans){
	                ans = arr[start];
	                idx = start;
	            }
	            start = mid+1;
	        }else{ //arr[start] > arr[mid]
	            if(arr[mid] < ans){
	                ans = arr[mid];
	                idx = mid;
	            }
	            end = mid-1;
	        }
	    }
	    return idx;                           //gives no. of rotations
	}
};
/*
Example 1:
Input:
n = 5
arr[] = {5, 1, 2, 3, 4}
Output: 1
Explanation: The given array is 5 1 2 3 4. 
The original sorted array is 1 2 3 4 5. 
We can see that the array was rotated 
1 times to the right.

Example 2:
Input:
n = 5
arr[] = {1, 2, 3, 4, 5}
Output: 0
Explanation: The given array is not rotated.
*/


//52. SINGLE ELEMENT IN A SORTED ARRAY                           {T.C = O(LOGN), S.C = O(1)}
//1 1 2 2 4 5 5 6 6     {ev od ev od 4 od ev od ev}
//(evenIdx, oddIdx) same then eliminate left part (element is on right)
//(oddIdx, evenIdx) same then eliminate right part (element is on left)
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int n = nums.size();
        //base cases
        if(n == 1){
            return nums[0];
        }
        if(nums[0] != nums[1]){                  //1st element is single element
            return nums[0];
        }
        if(nums[n-1] != nums[n-2]){              //last element is single element
            return nums[n-1];
        }

        int start = 1, end = n-2;               //shirnk space(handled above)
        while(start <= end){
            int mid = start + (end-start)/2;
            if(nums[mid-1] != nums[mid] && nums[mid] != nums[mid+1]){  //left and right both not match(single element)
                return nums[mid];
            }else if((mid % 2 == 1 && nums[mid-1] == nums[mid] ) ||
                     (mid % 2 == 0 && nums[mid] == nums[mid+1])  ){      //left sorted (eleminate left)
                start = mid+1;
            }else{
                end = mid-1;
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


//53. FIND PEAK ELEMENT I   (1D ARRAY)                                        {T.C = O(LOGN), S.C = O(1)}
//END = MID (NOT MID-1)
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        int start = 0;
        int end = n - 1;

        while(start <= end){
            int mid = start + (end-start)/2;
            if(nums[mid] < nums[mid+1]){              //peak may be in left side
                start = mid+1;
            }else{ //(nums[mid] > nums[mid+1])        //peak may be in right side
                end = mid;
            }
        }
        return start;
    }
};
/*
Example 1:
Input: nums = [1,2,3,1]
Output: 2
Explanation: 3 is a peak element and your function should return the index number 2.

Example 2:
Input: nums = [1,2,1,3,5,6,4]
Output: 5
Explanation: Your function can return either index number 1 where the peak element is 2, or index number 5 where the peak element is 6.
*/


//BS ON ANSWERS/ELEMENT NOT ON INDEX----------------------------------------------------------------------
//54. SQUARE ROOT OF A NUMBER                                 {T.C = O(LOGN), S.C = O(1)}
//RANGE[1, X]
class Solution{
  public:
    long long int floorSqrt(long long int x) 
    {
        long long start = 1;                   //range [0, x]
        long long end = x;
        long long ans = 1;                      //ateast 1 (constraints)
        while(start <= end){
            long long mid = start + (end-start)/2;
            if(mid*mid <= x){
                ans = mid;
                start = mid+1;
            }else{
                end = mid-1;
            }
        }
        return ans;
    }
};
/*
Example 1:
Input:
x = 5
Output: 2
Explanation: Since, 5 is not a perfect 
square, floor of square_root of 5 is 2.

Example 2:
Input:
x = 4
Output: 2
Explanation: Since, 4 is a perfect 
square, so its square root is 2.
*/


//55. FIND NTH ROOT OF M                                          {T.C = O(N*LOGM), S.C = O(1)}
//RANGE [1, M(BASE)]
class Solution{
	public:
	int findPow(int base, int exp){
	    long ans = 1;
	    for(int i = 1; i <= exp ; i++){
	        ans *= base;
	        if(ans > INT_MAX){
	            return INT_MAX;
	        }
	    }
	    return ans;
	}
	int NthRoot(int n, int m)               //n = exp, m = base
	{
	    int start = 1, end = m;
	    while(start <= end){
	        int mid = start + (end-start)/2;
	        int midN = findPow(mid, n);
	        if(midN == m){
	            return mid;
	        }else if(midN < m){
	            start = mid+1;
	        }else{
	            end = mid-1;
	        }
	    }
	    return -1;
	}  
};
/*
Example 1:
Input: n = 2, m = 9
Output: 3
Explanation: 32 = 9

Example 2:
Input: n = 3, m = 9
Output: -1
Explanation: 3rd root of 9 is not
integer.
*/


//56. KOKO EATING BANANAS                        //min()                           {T.C = O(N*LOGN), S.C = O(1)}
//INITIALLY ANS = 1(ATLEAST BANANA EAT) THEN CHECK OF AT MIN(MAX)
class Solution {
public:
    long long getHours(vector<int>&piles, int mid){       //mid == hr
        long long count = 0;
        for(auto it : piles){
            count += ceil((double)it/(double)mid);
        }
        return count;
    }
    int minEatingSpeed(vector<int>& piles, int h) {
        int start = 1;
        int end = *max_element(piles.begin(), piles.end());
        int ans = 1;
        while(start <= end){
            int mid = start + (end-start)/2;
            if(getHours(piles, mid) <= h){
                ans = mid;
                end = mid-1;
            }else{
                start = mid+1;
            }
        }
        return ans;
    }
};
/*
Example 1:
Input: piles = [3,6,7,11], h = 8
Output: 4

Example 2:
Input: piles = [30,11,23,4,20], h = 5
Output: 30

Example 3:
Input: piles = [30,11,23,4,20], h = 6
Output: 23
*/


//57. MINIMUM NUMBER OF DAYS TO MAKE M BOUQUETS              min()        {T.C = O(N*LOGN), S.C = O(1)}
//RANGE [MINELEMENT, MAXELEMENT]
class Solution {
public:
    bool isPossible(vector<int>&bloomDay, int mid, int m, int k){
        int count = 0;
        int noOfB = 0;
        for(int i = 0 ; i < bloomDay.size(); i++){
            if(bloomDay[i] <= mid){
                count++;
            }else{
                noOfB += (count/k);
                count = 0;
            }
        }
        noOfB += (count/k);
        
        return noOfB >= m;
    }
    int minDays(vector<int>& bloomDay, int m, int k) {
        int n = bloomDay.size();
        //base case
        long long val = m*1LL * k*1LL;
        if(val > n){
            return -1;
        }
        int maxi = INT_MIN, mini = INT_MAX;
        for(auto it : bloomDay){
            maxi = max(maxi, it);
            mini = min(mini, it);
        }

        int start = mini, end = maxi;           //BS on element not on index
        while(start <= end){
            int mid = start + (end-start)/2;
            if(isPossible(bloomDay, mid, m, k)){
                end = mid-1;
            }else{
                start = mid+1;
            }
        }
        return start;                                     //finding mini possible ans
    }
};
/*
Example 1:
Input: bloomDay = [1,10,3,10,2], m = 3, k = 1
Output: 3
Explanation: Let us see what happened in the first three days. x means flower bloomed and _ means flower did not bloom in the garden.
We need 3 bouquets each should contain 1 flower.
After day 1: [x, _, _, _, _]   // we can only make one bouquet.
After day 2: [x, _, _, _, x]   // we can only make two bouquets.
After day 3: [x, _, x, _, x]   // we can make 3 bouquets. The answer is 3.

Example 2:
Input: bloomDay = [1,10,3,10,2], m = 3, k = 2
Output: -1
Explanation: We need 3 bouquets each has 2 flowers, that means we need 6 flowers. We only have 5 flowers so it is impossible to get the needed bouquets and we return -1.

Example 3:
Input: bloomDay = [7,7,7,7,12,7,7], m = 2, k = 3
Output: 12
Explanation: We need 2 bouquets each should have 3 flowers.
Here is the garden after the 7 and 12 days:
After day 7: [x, x, x, x, _, x, x]
We can make one bouquet of the first three flowers that bloomed. We cannot make another bouquet from the last three flowers that bloomed because they are not adjacent.
After day 12: [x, x, x, x, x, x, x]
It is obvious that we can make two bouquets in different ways.
*/


//58. FIND THE SMALLEST DIVISOR GIVEN A THRESHOLD                     {T.C = O(N*LOGN), S.C = O(1)}
//RANGE = [1, MAXELEMENT]
class Solution {
public:
    int sumOfDiv(vector<int>&nums, int mid){
        int sum = 0;
        for(int i = 0 ; i < nums.size(); i++){
            sum += ceil((double)nums[i] / (double)mid);    //i/m + j/m ....(int gives 0)
        }
        return sum;
    }
    int smallestDivisor(vector<int>& nums, int threshold) {
        int n = nums.size();
        int maxi = INT_MIN;
        // int mini = INT_MAX;                   //not work or take 1 (constraint)
        for(int i = 0 ; i < n ; i++){
            maxi = max(maxi, nums[i]);
        }

        int start = 1;
        int end = maxi;
        while(start <= end){
            int mid = start + (end-start)/2;
            if(sumOfDiv(nums, mid) <= threshold){
                end = mid-1;
            }else{
                start = mid+1;
            }
        }
        return start;                                //finding minimum
    }
};
/*
Example 1:
Input: nums = [1,2,5,9], threshold = 6
Output: 5
Explanation: We can get a sum to 17 (1+2+5+9) if the divisor is 1. 
If the divisor is 4 we can get a sum of 7 (1+1+2+3) and if the divisor is 5 the sum will be 5 (1+1+1+2). 

Example 2:
Input: nums = [44,22,33,11,1], threshold = 5
Output: 44
*/


//59. CAPACITY TO SHIP PACKAGES WITHIN D DAYS                         {T.C = O(N*LOGN), S.C = O(1)}
//RANGE [MAX ELEMENT, TOTAL SUM]
class Solution {
public:
    int findMinDays(vector<int>&wt, int cap){        //mid == capacity
        int n = wt.size();
        int days = 1, load = 0;                      //min days = 1
        for(int i = 0 ; i < n ; i++){
            if(load + wt[i] <= cap){
                load += wt[i];
            }else{
                days++;
                load = wt[i];
            }
        }
        return days;
    }
    int shipWithinDays(vector<int>& weights, int days) {
        int n = weights.size();
        // int maxi = *max_element(weights.begin(), weights.end());
        int maxi = INT_MIN;
        int sum = 0;
        for(int i = 0 ; i < n ; i++){
            sum += weights[i];
            maxi = max(maxi, weights[i]);
        }
        int start = maxi;
        int end = sum;
        while(start <= end){                          //range [maxElement, totalSum]
            int mid = start + (end-start)/2;
            int ans = findMinDays(weights, mid);
            if(ans <= days){
                end = mid-1;
            }else{
                start = mid+1;
            }
        }
        return start;                                  //min ans
    }
};
/*
Example 1:
Input: weights = [1,2,3,4,5,6,7,8,9,10], days = 5
Output: 15
Explanation: A ship capacity of 15 is the minimum to ship all the packages in 5 days like this:
1st day: 1, 2, 3, 4, 5
2nd day: 6, 7
3rd day: 8
4th day: 9
5th day: 10
Note that the cargo must be shipped in the order given, so using a ship of capacity 14 and splitting the packages into parts like (2, 3, 4, 5), (1, 6, 7), (8), (9), (10) is not allowed.

Example 2:
Input: weights = [3,2,2,4,1,4], days = 3
Output: 6
Explanation: A ship capacity of 6 is the minimum to ship all the packages in 3 days like this:
1st day: 3, 2
2nd day: 2, 4
3rd day: 1, 4

Example 3:
Input: weights = [1,2,3,1,1], days = 4
Output: 3
Explanation:
1st day: 1
2nd day: 2
3rd day: 3
4th day: 1, 1
*/


//60. KTH MISSING POSITIVE NUMBER
//BRUTE FORCE (LINEAR SEARCH)                                              {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        for(int i = 0 ; i < arr.size() ; i++){
            if(arr[i] <= k){
                k++;
            }else{
                break;
            }
        }
        return k;
    }
};

//USING BS                                                  {T.C = O(LOGN), S.C = O(1)}
//FORMULA => arr[end] + more {k-missing(arr[end]-end-1)} == end + 1 + k or start + k
class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int n = arr.size();
        int start = 0, end = n-1;
        while(start <= end){
            int mid = start + (end-start)/2;
            int missing = arr[mid]-(mid+1);                //starting element 1 to ---
            if(missing < k){
                start = mid+1;
            }else{
                end = mid-1;
            }
        }
        return end+1 + k;                 //or start + k     //arr[end] + more {k-missing}
    }
};
/*
Example 1:
Input: arr = [2,3,4,7,11], k = 5
Output: 9
Explanation: The missing positive integers are [1,5,6,8,9,10,12,13,...]. The 5th missing positive integer is 9.

Example 2:
Input: arr = [1,2,3,4], k = 2
Output: 6
Explanation: The missing positive integers are [5,6,7,...]. The 2nd missing positive integer is 6.
*/


//61. AGGRESIVE COW                     {max(min) pattern}             {T.C = O(N*LOG(MAX_DIST)), S.C = O(1)}
bool canWePlace(vector<int>& stalls, int dist, int cow){
    int cowCnt = 1;
    int last = stalls[0];                         // Variable to store the position of the last placed cow.

    for(int i = 1 ; i < stalls.size(); i++){
        if(stalls[i] - last >= dist){
            cowCnt++;
            last = stalls[i];
        }
        if(cowCnt >= cow){                         // If 'cow' cows have been placed, return true.
            return true;
        }
    }

    // If it's not possible to place 'cow' cows with distance 'dist', return false.
    return false;
}

int aggressiveCows(vector<int> &stalls, int k)
{
    int n = stalls.size();
    sort(stalls.begin(), stalls.end()); 

    int low = 1 , high = stalls[n-1] - stalls[0];                    //max dist b/w cow is (high - low)
    
    // Binary search to find the maximum distance among all minimum distances.
    while(low <= high){
        int mid = low + (high-low)/2;
        if(canWePlace(stalls, mid, k) == true){
            low = mid + 1; // If 'k' cows can be placed with distance 'mid', search for higher distances.
        } else {
            high = mid - 1; // If 'k' cows cannot be placed with distance 'mid', search for lower distances.
        }
    }

    // Return the maximum distance among all minimum distances for placing 'k' cows in 'stalls'.
    return high;
}
/*
Sample Input 1 :
6 4
0 3 4 7 10 9
Sample Output 1 :
3
*/


//62. ALLOCATE MINIMUM NUMBER OF PAGES / ALLOCATE BOOKS     {min(max) pattern}          {T.C = O(N*LOGN), S.C = O(1)}
/*Allocate the book to m students such that Maximum no. of pages assigned to a student is minimum value*/
bool isPossible(vector<int> a, int n, int m, int mid) {
    int studentCount = 1;
    int pageSum = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] > mid) {
            return false; // The current book's pages exceed the 'mid' value, which is not allowed.
        }
        if (pageSum + a[i] <= mid) {
            pageSum += a[i];
        } else {
            studentCount++;
            if (studentCount > m) {
                return false; // The required number of students is greater than 'm'.
            }
            pageSum = a[i];
        }
    }
    return true;
}

int findPages(vector<int>&a ,int n ,int m){
    //base case
    if(m > n){
        return -1;
    }

    int low = *max_element(a.begin(), a.end());           //low should contain max element
    int sum = 0;
    for(int i = 0 ; i < n; i++){
        sum += a[i];
    }
    int high = sum;
    while(low <= high){
        int mid = low + (high-low)/2;
        if(isPossible(a , n , m , mid) == true){
            high  = mid - 1;
        }
        else{
            low = mid + 1;
        }
    }
    return low;                             //min(max)
}
/*
Input:
N = 4
A[] = {12,34,67,90}
M = 2
Output:113
Explanation:Allocation can be done in 
following ways:
{12} and {34, 67, 90} Maximum Pages = 191
{12, 34} and {67, 90} Maximum Pages = 157
{12, 34, 67} and {90} Maximum Pages =113.
Therefore, the minimum of these cases is 113,
which is selected as the output.
*/


//63. SPLIT ARRAY LARGEST SUM       min(max)                    {T.C = O(N*LOGN), S.C = O(1)}
//BS ON VAL  (SAME AS ABOVE)
class Solution {
public:
    bool isPossible(vector<int>&nums, int mid, int k){
        int n = nums.size();
        int splitCount = 1;
        int splitSum = 0;
        for(int i = 0 ; i < n ;i++){
            if(splitSum + nums[i] <= mid){
                splitSum += nums[i];
            }else{
                splitCount++;
                if(splitCount > k){
                    return false;
                }
                splitSum = nums[i];
            }
        }
        return true;
    }
    int splitArray(vector<int>& nums, int k) {
        int n = nums.size();
        // sort(nums.begin(), nums.end());                   //not required (BS on val not element)
        int low = *max_element(nums.begin(), nums.end());    //subarray contains largest val ateleast
        int sum = 0;
        for(int i = 0 ; i < n ; i++){
            sum += nums[i];
        }
        int high = sum;
        while(low <= high){
            int mid = low + (high - low)/2;
            if(isPossible(nums, mid, k) == true){
                high = mid-1;
            }else{
                low = mid+1;
            }
        }
        return low;                                   //min(max)
    }
};
/*
Example 1:
Input: nums = [7,2,5,10,8], k = 2
Output: 18
Explanation: There are four ways to split nums into two subarrays.
The best way is to split it into [7,2,5] and [10,8], where the largest sum among the two subarrays is only 18.

Example 2:
Input: nums = [1,2,3,4,5], k = 2
Output: 9
Explanation: There are four ways to split nums into two subarrays.
The best way is to split it into [1,2,3] and [4,5], where the largest sum among the two subarrays is only 9.
*/


//64. PAINTER'S PARTITION PROBLEM           min(max)                    {T.C = O(N*LOGN), S.C = O(1)}
//SAME AS ABOVE
bool isPossible(vector<int>&boards, int mid, int k){
    int n = boards.size();
    int partCount = 1;                                     //intitially 1 partition
    int paintSum = 0;
    for(int i = 0 ; i < n ; i++){
        if(paintSum + boards[i] <= mid){
            paintSum += boards[i];
        }else{
            partCount++;
            if(partCount > k){
                return false;
            }
            paintSum = boards[i];
        }
    }
    return true;
}
int findLargestMinDistance(vector<int> &boards, int k)
{
    int n = boards.size();
    int sum = 0;
    for(int i = 0 ; i < n ; i++){
        sum += boards[i];
    }
    int low = *max_element(boards.begin(), boards.end());        //subarray contains largest val atleast
    int high = sum;
    while(low <= high){
        int mid = low + (high-low)/2;
        if(isPossible(boards, mid, k)){
            high = mid-1;
        }else{
            low = mid+1;
        }
    }
    return low;                                                       //min(max)
}
/*
Sample Input 1 :
4 2
10 20 30 40
Sample Output 1 :
60
Explanation For Sample Input 1 :
In this test case, we can divide the first 3 boards for one painter and the last board for the second painter.
*/


//65. MINIMIZE MAX DISTANCE TO GAS STATION                                          {T.C = O(N*LOGN), S.C = O(1)}
//min(max)
class Solution {
  public:
    bool isPossible(const vector<int>&s, double mid, int k) {
        int n = s.size();
        int cnt = 0;
        for (int i = 1; i < n; ++i) {
            cnt += max(0, (int)((s[i]-s[i-1])/mid));
        }
        return cnt <= k;
    }
    double findSmallestMaxDist(vector<int>&s, int k) {
        double st = 0.0;
        double en = 0.0;
        int n = s.size();
        
        // Find the maximum initial gap
        for (int i = 1; i < n; ++i) {
            en = max(en, (double)(s[i] - s[i - 1]));
        }
        // Binary search for the smallest maximum distance
        while (en - st > 1e-6) {
            double mid = st + (en - st) / 2.0;
            if (isPossible(s, mid, k)) {
                en = mid;
            } else {
                st = mid;
            }
        }
        return en;                                //min(max) {not work st}
    }
};
/*
Example 1:
Input:
n = 10
stations = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
k = 9
Output: 0.50
Explanation: Each of the 9 stations can be added mid way between all the existing adjacent stations.

Example 2:
Input:
n = 10
stations = [3,6,12,19,33,44,67,72,89,95] 
k = 2 
Output: 14.00 
Explanation: Construction of gas stations at 8th(between 72 and 89) and 6th(between 44 and 67) locations.
*/


//66. MEDIAN OF TWO SORTED ARRAYS                                                   {T.C = O(LOGN), S.C = O(1)}
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size();
        int n2 = nums2.size();
        
        if(n2 < n1){
            return findMedianSortedArrays(nums2, nums1);                //smallest should be first parameter
        }
        
        int low = 0 , high = n1;
        
        while(low <= high){
            int cut1 = (low+high)/2;
            int cut2 = ((n1+n2+1)/2) - cut1;
            int left1 = cut1 == 0 ? INT_MIN : nums1[cut1-1];
            int left2 = cut2 == 0 ? INT_MIN : nums2[cut2-1];
            int right1 = cut1 == n1 ? INT_MAX : nums1[cut1];
            int right2 = cut2 == n2 ? INT_MAX : nums2[cut2];
            
            if(left1 <= right2 && left2 <= right1){
                if((n1+n2) % 2 == 0){            //even
                    return (max(left1, left2) + min(right1, right2))/2.0;
                }
                else{                            //odd
                    return max(left1, left2);
                }
            }
            else if(left1 > left2){
                high = cut1-1;                   //move left
            }
            else{
                low = cut1+1;                    //move right
            }
        }
        return 0.0;        
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


//67. KTH ELEMENT OF TWO ARRAYS                                                       {T.C = O(LOGN), S.C = O(1)}
class Solution{
    public:
    int kthElement(int arr1[], int arr2[], int n, int m, int k)
    {
        if(n > m){
            return kthElement(arr2, arr1, m , n , k);
        }
        
        int low = max(0, k-m), high = min(k, n);
        
        while(low <= high){
            int cut1 = (low+high)/2;
            int cut2 = k-cut1;
            int l1 = cut1 == 0 ? INT_MIN : arr1[cut1 - 1];
            int l2 = cut2 == 0 ? INT_MIN : arr2[cut2 - 1];
            int r1 = cut1 == n ? INT_MAX : arr1[cut1];
            int r2 = cut2 == m ? INT_MAX : arr2[cut2];
            
            if(l1 <= r2 && l2 <= r1){
                return max(l1, l2);
            }
            else if(l1 > r2){
                high = cut1 - 1;
            }
            else{
                low = cut1 + 1;
            }
        }
        return 1;
    }
};
/*
Example 1:
Input:
arr1[] = {2, 3, 6, 7, 9}
arr2[] = {1, 4, 8, 10}
k = 5
Output:
6
Explanation:
The final sorted array would be -
1, 2, 3, 4, 6, 7, 8, 9, 10
The 5th element of this array is 6.

Example 2:
Input:
arr1[] = {100, 112, 256, 349, 770}
arr2[] = {72, 86, 113, 119, 265, 445, 892}
k = 7
Output:
256
Explanation:
Final sorted array is - 72, 86, 100, 112,
113, 119, 256, 265, 349, 445, 770, 892
7th element of this array is 256.
*/


//BS ON 2D ARRAYS ----------------------------------------------------------
//68. ROW WITH MAX 1'S                                             {T.C = O(N*LOGN), S.C = O(1)}         
//N-FIRST OCC OR 1
class Solution{
public:
    int lowerBoundIdx(vector<int>&nums, int n, int target){
        int start = 0, end = n-1;
        int first = n;                        //not -1 (handle)
        while(start <= end){
            int mid = start + (end-start)/2;
            if(nums[mid] == target){
                first = mid;
                end = mid-1;                          //search only in first half
            }else if(nums[mid] < target){
                start = mid+1;
            }else{
                end = mid-1;
            }
        }
        return first;
    }
	int rowWithMax1s(vector<vector<int> > arr, int n, int m) {
	    int countMax = 0;
	    int idx = -1;
	    for(int i = 0 ; i < arr.size() ; i++){
	       // int countOnes = n - ( lower_bound(arr[i].begin(), arr[i].end(), 1) - arr[i].begin() ); //n-first occ or 1(lower bound of 1)
	        int countOnes = m - lowerBoundIdx(arr[i], m, 1);       //lowerBoundIdx == first pos
	        if(countOnes > countMax){
	            countMax = countOnes;
	            idx = i;
	        }
	    }
	    return idx;
	}
};
/*
Input: 
N = 4 , M = 4
Arr[][] = {{0, 1, 1, 1},
           {0, 0, 1, 1},
           {1, 1, 1, 1},
           {0, 0, 0, 0}}
Output: 2
Explanation: Row 2 contains 4 1's (0-based
indexing).

Example 2:
Input: 
N = 2, M = 2
Arr[][] = {{0, 0}, {1, 1}}
Output: 1
Explanation: Row 1 contains 2 1's (0-based
indexing).
*/


//69. SEARCH A 2D MATRIX  (ROW SORTED AND ROW[N-1] < ROW[N+1]COL[N+1])    {T.C = O(LOG(N*M)), S.C = O(1)}
//FULL SORTED MATRIX
//element = matrix[mid/col {row}][mid%col {col}]
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
            }else if(element < target){
                start = mid+1;
            }else{
                end = mid-1;
            }
        }
        return false;
    }
};
/*
Example 1:
Input: matrix = [[1,3,5,7],
                 [10,11,16,20],
                 [23,30,34,60]],
                target = 3
Output: true

Example 2:
Input: matrix = [[1,3,5,7],
                 [10,11,16,20],
                 [23,30,34,60]], 
                target = 13
Output: false
*/


//70. SEARCH A 2D MATRIX II (ONLY INDIVIDUAL ROW AND COL SORTED )          {T.C = O(LOGN*M), S.C = O(1)}
//ROWIDX = 0, COLIDX = COL-1;
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int row = matrix.size();
        int col = matrix[0].size();

        int rowIndex = 0;
        int colIndex = col-1;

        while(rowIndex < row && colIndex >= 0){
            int element = matrix[rowIndex][colIndex];
            if(element == target){
                return true;
            }
            else if(element < target){
                rowIndex++;
            }
            else{
                colIndex--;
            }
        }
        return false;
    }
};
/*
Example 1:
Input: matrix = [[1,4,7,11,15],
                 [2,5,8,12,19],
                 [3,6,9,16,22],
                 [10,13,14,17,24],
                 [18,21,23,26,30]], 
                target = 5
Output: true

Example 2:
Input: matrix = [[1,4,7,11,15],
                 [2,5,8,12,19],
                 [3,6,9,16,22],
                 [10,13,14,17,24],
                 [18,21,23,26,30]], 
                target = 20
Output: false
*/


//71a. FIND PEAK ELEMENT I   (1D ARRAY)                                        {T.C = O(LOGN), S.C = O(1)}
//END = MID (NOT MID-1)
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        int start = 0;
        int end = n - 1;

        while(start < end){
            int mid = start + (end-start)/2;
            if(nums[mid] < nums[mid+1]){              //peak may be in left side
                start = mid+1;
            }else{ //(nums[mid] > nums[mid+1])        //peak may be in right side
                end = mid;
            }
        }
        return start;
    }
};
/*
Example 1:
Input: nums = [1,2,3,1]
Output: 2
Explanation: 3 is a peak element and your function should return the index number 2.

Example 2:
Input: nums = [1,2,1,3,5,6,4]
Output: 5
Explanation: Your function can return either index number 1 where the peak element is 2, or index number 5 where the peak element is 6.
*/


//71b. FIND PEAK ELEMETNT II (2D ARRAY/MATRIX)                                   {T.C = O(N*LOGM), S.C = O(1)}
//FIND PEAK IN ROW THEN CHECK VERTICALLY MAX ELEMENT (ROWIDX) THEN CHECK FOR ALL SIDE
class Solution {
public:
    int findIdx(vector<vector<int>>&mat, int n, int m, int col){
        int maxVal = -1;
        int idx = -1;
        for(int i = 0 ; i < n ; i++){
            if(mat[i][col] > maxVal){
                maxVal = mat[i][col];
                idx = i;
            }
        }
        return idx;
    }
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();
        int start = 0, end = m-1;                       //row wise traversal
        while(start <= end){
            int mid = start + (end-start)/2;
            int rowIdxInCol = findIdx(mat, n, m, mid);
            
            int left = mid-1 >= 0 ? mat[rowIdxInCol][mid-1] : -1;
            int right = mid+1 < m ? mat[rowIdxInCol][mid+1] : -1;

            int curr = mat[rowIdxInCol][mid];
            if(curr > left && curr > right){
                return {rowIdxInCol, mid};
            }else if(curr < left){     //peak is on left side
                end = mid-1;
            }else{
                start = mid+1;
            }
        }
        return {-1, -1};
    }
};
/*
Example 1:
Input: mat = [[1,4],[3,2]]
Output: [0,1]
Explanation: Both 3 and 4 are peak elements so [1,0] and [0,1] are both acceptable answers.

Example 2:
Input: mat = [[10,20,15],[21,30,14],[7,16,32]]
Output: [1,1]
Explanation: Both 30 and 32 are peak elements so [1,1] and [2,2] are both acceptable answers.
*/


//72. MEDIAN IN A ROW-WISE SORTED MATRIX                             {T.C = O(N*LOGM), S.C = O(1)}
class Solution{   
public:
    int median(vector<vector<int>> &m, int r, int c){
        int mini = INT_MAX;
        int maxi = INT_MIN;
        
        for(int i = 0 ; i < r ; i++){
            //finding the minimum element
            if(m[i][0] < mini){
                mini = m[i][0];
            }
            //finding the maximum element
            if(m[i][c-1] > maxi){
                maxi = m[i][c-1];
            }
        }
        int desired = (r*c + 1)/2;                            //odd
        while(mini < maxi){
            int mid = mini + (maxi-mini)/2;
            int place = 0;
            
            //find count of elements smaller then mid
            for(int i = 0 ; i < r ; i++){
                place += upper_bound(m[i].begin(), m[i].end(), mid) - m[i].begin();
            }
            if(place < desired){
                mini = mid+1;
            }
            else{
                maxi = mid;
            }
        }
        return mini;
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


/*---------------------------------------------- THE END ---------------------------------------------------------*/