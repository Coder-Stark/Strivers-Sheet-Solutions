//IMPORTANT QUESTIONS

//PREFIX SUM
//01. LONGEST SUBARRY WITH SUM K  (-VE NUMBER ALLOWED)                                {T.C = O(N), S.C = O(N)}
class Solution{
    public:
    //USING PREFIX SUM (sum-k), then ans = i-(mp[sum-k]th index)
    int lenOfLongSubarr(int A[],  int N, int K){ 
        unordered_map<int,int>mp;
        int sum = 0, maxLen = 0;
        for(int i = 0 ; i < N ; i++){
            sum += A[i];
            if(sum == K) maxLen = max(maxLen, i+1);               //I+1 FOR LEN (0 BASED INDEXING)
            if(!mp.count(sum)) mp[sum] = i;                       //map filling
            if(mp.count(sum-K)) maxLen = max(maxLen, i-mp[sum-K]);
        }
        return maxLen;
    } 
};

//or
class Solution {
  public:
    int maxLen(vector<int>& arr, int n) {
        unordered_map<int,int>mp;
        int maxiLen = 0;
        int sum = 0;
        for(int i = 0 ;  i < n; i++){
            sum += arr[i];
            if(sum == 0) maxiLen = max(maxiLen, i+1);
            else if(mp.count(sum-0)) maxiLen = max(maxiLen, i-mp[sum-0]);
            else mp[sum] = i;
        }
        return maxiLen;
    }
};
/*
Input :
arr[] = {10, 5, 2, 7, 1, 9}, k = 15
Output : 4
Explanation:
The sub-array is {5, 2, 7, 1}.

Input : 
arr[] = {-1, 2, 3}, k = 6
Output : 0
Explanation: 
There is no such sub-array with sum 6.
*/


//02. NEXT PERMUTATION                                                        {T.C = O(N), S.C = O(1)}
//USING STL
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        next_permutation(nums.begin(), nums.end());
    }
};

//WITHOUT STL
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
            if(nums[i-1] < nums[i]){                                   //I-1 (NORMAL NOT REVERSED IDX)  3 < 4
                golaIdx = i-1;
                break;
            }
        }

        if(golaIdx != -1){                                            //CHECK for outer bound case
            int swapIdx = golaIdx;
            for(int i = n-1 ; i >= golaIdx + 1 ; i--){                //traverse right to just after golaIdx
                if(nums[i] > nums[golaIdx]){
                    swapIdx = i;
                    break;
                }
            }
            swap(nums[golaIdx], nums[swapIdx]);
        }

        reverse(nums.begin()+golaIdx+1 , nums.end());                //reverse from golaIdx+1 to end
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
