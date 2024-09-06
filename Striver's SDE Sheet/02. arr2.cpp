#include<bits/stdc++.h>
using namespace std;


//DAY 2: ARRAY II -----------------------------------------------------------------------------------------------------
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