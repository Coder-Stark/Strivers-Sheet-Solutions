//GREEDY ALGORITHM

#include<bits/stdc++.h>
using namespace std;


//EASY PROBLEMS----------------------------------------------------------------------------------------
//221. ASSIGN COOKIES                                             {T.C = O(NLOGN), S.C = O(1)}
//SORT BOTH VECTORS , USE I & J POINTER SEARCH G[I] <= S[J] (BRUTE FORCE)
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int i = 0;                   //g(child)
        int j = 0;                   //s(cookies)

        // int ans = 0;
        while(i < g.size() && j < s.size()){
            if(g[i] <= s[j]){
                // ans++;
                i++;
            }
            j++;
        }

        // return ans;
        return i;
    }
};
/*
Example 1:
Input: g = [1,2,3], s = [1,1]
Output: 1
Explanation: You have 3 children and 2 cookies. The greed factors of 3 children are 1, 2, 3. 
And even though you have 2 cookies, since their size is both 1, you could only make the child whose greed factor is 1 content.
You need to output 1.

Example 2:
Input: g = [1,2], s = [1,2,3]
Output: 2
Explanation: You have 2 children and 3 cookies. The greed factors of 2 children are 1, 2. 
You have 3 cookies and their sizes are big enough to gratify all of the children, 
You need to output 2.
*/


//222. FRACTIONAL KNAPSACK                                   {T.C = O(NLOGN), S.C = O(N)}
//STORE PAIR{PER UNIT VAL , ITEM(VAL, WT)} , SORT ACCORDING TO PUV, THEN PUT FRACTIONAL PART FOR LEFT W
class Solution
{
    public:
    double fractionalKnapsack(int W, Item arr[], int n)
    {
        //create vector {v/w, Item<v , w>}
        vector<pair<double, Item>>v;
        for(int i = 0 ; i < n ; i++){
            double perUnitValue = (1.0* arr[i].value / arr[i].weight);
            pair<double, Item>p = {perUnitValue, arr[i]};
            v.push_back(p);
        }
        
        //sort vector
        auto lambda = [&](auto a, auto b){     //decreasing sort of  per unit value
            return a.first > b.first;
        };
        sort(v.begin(), v.end(), lambda);
        
        double totalValue = 0;
        for(int i = 0 ; i < n ; i++){
            if(v[i].second.weight > W){
                //fractional part
                totalValue = totalValue + W * v[i].first;     // w * v/w
                W = 0;
            }
            else{
                //full part
                totalValue = totalValue + v[i].second.value;
                W = W - v[i].second.weight;
            }
        }
        return totalValue;
    }
};
/*
Input:
n = 3 
w = 50
value[] = {60,100,120}
weight[] = {10,20,30}
Output:
240.000000
Explanation:
Take the item with value 60 and weight 10, value 100 and weight 20 and split the third item with value 120 and weight 30, to fit it into weight 20. so it becomes (120/30)*20=80, so the total value becomes 60+100+80.0=240.0
Thus, total maximum value of item we can have is 240.00 from the given capacity of sack. 
*/


//223. NUMBER OF COINS
//GREEDY APPROACH (WRONG ANSWERR)                                  {T.C = O(NLOGN), S.C = O(1)}
class Solution{
	public:
	int minCoins(vector<int> &coins, int M, int V) 
	{ 
	    sort(coins.begin(), coins.end(), greater<int>());
	    int count = 0;
	    for(int i = 0 ; i < M ; i++){
            while(V >= coins[i]){
                V -= coins[i];
                count++;
                if(V == 0){
                    return count;
                }
            }
	    }
	    return -1;
	} 
};

//USING RECURSION                                         {T.C = O(2^N), S.C = O(1)}
class Solution{
	public:
	int solve(vector<int>&coins, int n, int V, int i){
	    //base case
	    if(V == 0){
	        return 0;
	    }
	    if(i == n || V < 0){
	        return INT_MAX;
	    }
	    
	    int incl = INT_MAX;
	    if(coins[i] <= V){
	        int temp = solve(coins, n, V-coins[i], i);
	        if(temp != INT_MAX){
	            incl = temp+1;
	        }
	    }
	    int excl = 0 + solve(coins, n, V, i+1);

	    return min(incl, excl);
	}
	int minCoins(vector<int> &coins, int M, int V)  //m = size
	{ 
	    return solve(coins, M, V, 0) == INT_MAX ? -1 : solve(coins, M, V, 0);
	} 
};

//USING RECURSION + MEMOIZATION                             {T.C = O(N*M), S.C = O(N*M)}
class Solution{
	public:
	int solve(vector<int>&coins, int i, int V, vector<vector<int>>&dp){
	    //base case
	    if(V == 0) return 0;
	   
	    if(i < 0 || V < 0) return 1e9;
	 
	    
	    if(dp[i][V] != -1){
	        return dp[i][V];
	    }
	    
	    int incl = 1e9;
	    if(coins[i] <= V){
	        incl = 1 + solve(coins, i, V-coins[i], dp);        //not i+1 (one coin can use again)
	    }
	    int excl = 0 + solve(coins, i-1, V, dp);

	    return dp[i][V] = min(incl, excl);
	}
	int minCoins(vector<int> &coins, int M, int V)  //m = size
	{ 
	    vector<vector<int>>dp(M+1, vector<int>(V+1, -1));
	    return solve(coins, M-1, V, dp) == 1e9 ? -1 : solve(coins, M-1, V, dp);  //M == i or n
	} 
};
/*//IN GREEDY OUTPUT IS 3
Input: V = 11, M = 4,coins[] = {9, 6, 5, 1} 
Output: 2 
Explanation: Use one 6 cent coin
and one 5 cent coin
*/


//224. LEMONADE CHANGE                                        {T.C = O(N), S.C = O(1)}
//SINGLE LOOP WITH CONDITION (COUNT 5 & 10 COINS)
class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int n = bills.size();
        int countFive = 0;
        int countTen = 0;
        for(int i = 0 ; i < n ; i++){
            if(bills[i] == 5){
                countFive++;
            }else if(bills[i] == 10){
                if(countFive == 0){
                    return false;
                }
                countFive--;
                countTen++;
            }else if(bills[i] == 20){
                if(countTen > 0 && countFive > 0){
                    countTen--;
                    countFive--;
                }else if(countFive >= 3){
                    countFive -= 3;
                }else{
                    return false;
                }
            }
        }
        return true;
    }
};
/*
Example 1:
Input: bills = [5,5,5,10,20]
Output: true
Explanation: 
From the first 3 customers, we collect three $5 bills in order.
From the fourth customer, we collect a $10 bill and give back a $5.
From the fifth customer, we give a $10 bill and a $5 bill.
Since all customers got correct change, we output true.

Example 2:
Input: bills = [5,5,10,10,20]
Output: false
Explanation: 
From the first two customers in order, we collect two $5 bills.
For the next two customers in order, we collect a $10 bill and give back a $5 bill.
For the last customer, we can not give the change of $15 back because we only have two $10 bills.
Since not every customer received the correct change, the answer is false.
*/


//225. VALID PARENTHESIS
//RECURSION                                                 {T.C = O(3^N), S.C = O(1)}
class Solution {
public:
    bool solve(string &s, int i, int count){
        int n = s.length();
        //base case
        if(count < 0) return false;
        if(i == n) return count == 0;

        if(s[i] == '('){
            return solve(s, i+1, count+1);
        }else if(s[i] == ')'){
            return solve(s, i+1, count-1);
        }else{ //s[i] == '*'
            return (solve(s, i+1, count) || solve(s, i+1, count+1) || solve(s, i+1, count-1));
        }
    }
    bool checkValidString(string s) {
        return solve(s, 0, 0);              //0 = initial index, 0 = count
    }
};

//RECURSION + MEMOIZATION                                     {T.C = O(N^2), S.C = O(N^2)}
class Solution {
public:
    int dp[101][101];
    bool solve(string &s, int i, int count){
        int n = s.length();
        //base case
        if(count < 0) return false;
        if(i == n) return count == 0;

        if(dp[i][count] != -1){
            return dp[i][count];
        }

        bool ans;
        if(s[i] == '('){
            ans = solve(s, i+1, count+1);
        }else if(s[i] == ')'){
            ans =  solve(s, i+1, count-1);
        }else{ //s[i] == '*'
            ans = (solve(s, i+1, count) || solve(s, i+1, count+1) || solve(s, i+1, count-1));
        }

        return dp[i][count] = ans;
    }
    bool checkValidString(string s) {
        memset(dp, -1, sizeof(dp));
        return solve(s, 0, 0);              //0 = initial index, 0 = count
    }
};


//TWO POINTERS                                                {T.C = O(N), S.C = O(1)}
class Solution {
public:
    bool checkValidString(string s) {
        int n = s.length();
        int min = 0, max = 0;                       //ranges [min (0), max(1)]
        for(int i = 0 ; i < n ; i++){
            if(s[i] == '('){
                min++, max++;
            }else if(s[i] == ')'){
                if(min > 0) min--;
                max--;
            }else{ //s[i] == '*'
                if(min > 0) min--;
                max++;
            }
            if(max < 0) return false;
        }
        return min == 0;                          //left range starts with 0(always)
    }
};
/*
Example 1:
Input: s = "()"
Output: true

Example 2:
Input: s = "(*)"
Output: true

Example 3:
Input: s = "(*))"
Output: true
*/


//MEDIUM / HARD----------------------------------------------------------------------------------------
//226. N MEETINGS IN ONE ROOM                                {T.C = O(N*LOGN), S.C = O(N)}
//STORE PAIR(START, END), SORT ACCORDING TO END, COMPARE NEXT START > PREV END : COUNT++
class Solution{
public:
    int maxMeetings(int start[], int end[], int n){
        vector<pair<int,int>>v;
        
        for(int i = 0 ; i < n ; i++){
            v.push_back({start[i], end[i]});
        }
        
        auto lambda = [&](auto a, auto b){     //increasing sort of end time
            return a.second < b.second;
        };
        sort(v.begin(), v.end(), lambda);
        
        int count = 1;                         //first meeting always selected
        int ansEnd = v[0].second;              //end time of first meeting
        for(int i = 1 ; i < n ; i++){
            if(v[i].first > ansEnd){           //next start > prev end
                count++;
                ansEnd = v[i].second;
            }
        }
        return count;
    }
};
/*
Input: n = 6, start[] = {1,3,0,5,8,5}, end[] =  {2,4,6,7,9,9}
Output: 4
Explanation: Maximum four meetings can be held with given start and end timings. The meetings are - (1, 2),(3, 4), (5,7) and (8,9)

Input: n = 3, start[] = {10, 12, 20}, end[] = {20, 25, 30}
Output: 1
Explanation: Only one meetings can be held with given start and end timings.
*/


//227. JUMP GAME                                        {T.C = O(N), S.C = O(1)}
//FAR(I + CURR ELEMENT), CURR (I), CURR < N-1(LAST INDEX) FALSE : TRUE
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int far = 0;                         //max jump from a curr index
        int curr = 0;                        //first index
        // int jumps = 0;

        for(int i = 0 ; i < n-1; i++){       //check till second last index (actually a last index)
            far = max(far, i + nums[i]);
            if(curr == i){
                // jumps++;
                curr = far;
            }
        }
        if(curr < n-1){                     //coudnt reach to last index
            return false;
        }
        return true;                        //return jumps
    }
};
/*
Example 1:
Input: nums = [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.

Example 2:
Input: nums = [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index
*/


//228. JUMP GAME II                                       {T.C = O(N), S.C = O(1)}
//SAME AS ABOVE JUST TAKE VAR(JUMPS), CURR == I (JUMP++)
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        int far = 0;                     //dist cover from curr index
        int curr = 0;
        int jumps = 0;
        

        for(int i = 0 ; i < n-1 ; i++){    //check till second last index
            far = max(far, i + nums[i]);
            if(curr == i){
                jumps++;
                curr = far;
            }
        }
        if(curr < n-1){
            return -1;
        }
        return jumps;
    }
};
/*
Example 1:
Input: nums = [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.

Example 2:
Input: nums = [2,3,0,1,4]
Output: 2
*/


//229. MINIMUM PLATFORMS                                     {T.C = O(NLOGN), S.C = O(1)}
//SORT BOTH (ARRIVAL, DEPARTURE), ARR[ARRIVAL] <= DEP[DEPARTURE] ? PLATFORM++ ? PLATFORM--
class Solution{
public:
    int findPlatform(int arr[], int dep[], int n)
    {
        // Sort the arrival and departure times in ascending order
        sort(arr, arr + n);
        sort(dep, dep + n);
    
        int platforms = 1;  // At least one platform is required
        int maxPlatforms = 1;  // Keep track of the maximum number of platforms needed
    
        int arrivalIndex = 1;
        int departureIndex = 0;
    
        while (arrivalIndex < n && departureIndex < n) {
            if (arr[arrivalIndex] <= dep[departureIndex]) { //next training coming
                platforms++;  // Increment the number of platforms needed
                maxPlatforms = max(maxPlatforms, platforms);
                arrivalIndex++;
            } else {
                platforms--;  // Reduce the number of platforms needed
                departureIndex++;
            }
        }
    
        return maxPlatforms;
    }
};
/*
Input: n = 6, arr[] = {0900, 0940, 0950, 1100, 1500, 1800}, 
            dep[] = {0910, 1200, 1120, 1130, 1900, 2000}
Output: 3
Explanation: There are three trains during the time 0940 to 1200. So we need minimum 3 platforms.

Input: n = 3, arr[] = {0900, 1235, 1100}, 
            dep[] = {1000, 1240, 1200}
Output: 1
Explanation: All train times are mutually exlusive. So we need only one platform

Input: n = 3, arr[] = {1000, 0935, 1100}, 
            dep[] = {1200, 1240, 1130}
Output: 3
Explanation: All 3 trains have to be their from 11:00 to 11:30
*/


struct Job 
{ 
    int id;	 // Job Id 
    int dead; // Deadline of job 
    int profit; // Profit if job is over before or on deadline 
};
//230. JOB SEQUENCING PROBLEM                                   {T.C = O(N^2), S.C = O(N)}
//SORT BY PROFIT, PUT ELEMENT IN REVERSE ORDER IN TEMP VECTOR.
class Solution {
    public:
    vector<int> JobScheduling(Job arr[], int n) { 
        auto lambda = [&](auto a, auto b){   //decreasing sort of profit
            return a.profit > b.profit;
        };
        sort(arr, arr+n, lambda);
        int maxDeadline = INT_MIN;
        for(int i = 0 ; i < n ; i++){
            maxDeadline = max(maxDeadline, arr[i].dead);
        }
        vector<int>schedule(maxDeadline+1, -1);        //1 based indexing
        
        int jobCount = 0, maxProfit = 0;
        for(int i = 0 ; i < n; i++){
            int currId = arr[i].id;
            int currDead = arr[i].dead;
            int currProfit = arr[i].profit;
            
            for(int j = currDead ; j > 0 ; j--){  //put element reverse (betwen space may accumulate another)
                if(schedule[j] == -1){
                    jobCount++;
                    schedule[j] = currId;
                    maxProfit += currProfit;
                    break;
                }
            }
        }
        return {jobCount, maxProfit};
    } 
};
/*
Example 1:
Input:
N = 4
Jobs = {(1,4,20),(2,1,10),(3,1,40),(4,1,30)}
Output:
2 60
Explanation:
Job1 and Job3 can be done with
maximum profit of 60 (20+40).

Example 2:
Input:
N = 5
Jobs = {(1,2,100),(2,1,19),(3,2,27),
        (4,1,25),(5,1,15)}
Output:
2 127
Explanation:
2 jobs can be done with
maximum profit of 127 (100+27).
*/


//231. CANDY                                             {T.C = O(N), S.C = O(N)}
//INITIALIZE VECTOR(N, 1){ATLEAST ONE CANDY }, TRAVERSE RATING(LEFT , RIGTH) CURR > PREV , CURRCAN++.
class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        if(n <= 1){
            return n;
        }
        vector<int>ans(n, 1);          //each child gets atleast 1 candy
        //left traversal
        for(int i = 1 ; i < n ; i++){
            if(ratings[i] > ratings[i-1]){      //curr > prev : currCandy+1
                ans[i] = ans[i-1] + 1;
            }
        }
        //right traversal
        for(int i = n-1 ; i > 0 ; i--){
            if(ratings[i] < ratings[i-1]){
                ans[i-1] = max(ans[i] + 1, ans[i-1]);         //compares both cases 
            }
        }
        int res = 0;
        for(int i = 0 ; i < n ; i++){
            res += ans[i];
        }
        return res;
    }
};
/*
Example 1:
Input: ratings = [1,0,2]
Output: 5
Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.

Example 2:
Input: ratings = [1,2,2]
Output: 4
Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
The third child gets 1 candy because it satisfies the above two conditions.
*/


//232. SHORTEST JOB FIRST                                 {T.C = O(NLOGN), S.C = O(1)}
//FIRST SORT, THEN ADD EACH TIME WITH NEXT , TAKE AVG
class Solution {
  public:
    long long solve(vector<int>& bt) {
        sort(bt.begin(), bt.end());
        long long n = bt.size();
        long long time = 0, waitTime = 0;
        for(int i = 0 ; i < n ; i++){
            waitTime += time;
            time += bt[i];
        }
        return waitTime/n;
    }
};
/*
Example 1:
Input:
n = 5
bt = [4,3,7,1,2]
Output: 4
Explanation: After sorting burst times by shortest job policy, calculated average waiting time is 4.

Example 2:
Input:
n = 4
arr = [1,2,3,4]
Output: 2
Explanation: After sorting burst times by shortest job policy, calculated average waiting time is 2.
*/


//233. PAGE FAULTS IN LRU                                   {T.C = O(NC), S.C = O(C)}
//ITRATE ON ARR , IF X NOT FOUND{COUNT++}, SIZE == C {REMOVE LRU ELE AND PUSH BACK} ELSE PUSH BACK, IF FOUND
//SIMPLE REMOVE CURR POS AND PUSH BACK
class Solution{
public:
    int pageFaults(int N, int C, int pages[]){
        vector<int>v;
        int faultCount = 0;
        for(int i = 0 ; i < N ; i++){
            int x = pages[i];
            if(find(v.begin(), v.end(), x) == v.end()){  //not found
                faultCount++;
                if(v.size() == C){                       //remove lru element and push back
                    v.erase(v.begin());
                    v.push_back(x);
                }else{
                    v.push_back(x);
                }
            }else{                                       //found
                v.erase(remove(v.begin(), v.end(), x));  //remove curr index and move push back
                v.push_back(x);
            }
        }
        return faultCount;
    }
};
/*
Input: N = 9, C = 4
pages = {5, 0, 1, 3, 2, 4, 1, 0, 5}
Output: 8
Explaination: memory allocated with 4 pages 5, 0, 1, 
3: page fault = 4
page number 2 is required, replaces LRU 5: 
page fault = 4+1 = 5
page number 4 is required, replaces LRU 0: 
page fault = 5 + 1 = 6
page number 1 is required which is already present: 
page fault = 6 + 0 = 6
page number 0 is required which replaces LRU 3: 
page fault = 6 + 1 = 7
page number 5 is required which replaces LRU 2: 
page fault = 7 + 1  = 8.
*/


//234. INSERT INTERVAL                                  {T.C = O(N), S.C = O(N)}
//ALREADY SORTED
//FIRST INSERT SMALLER NON OVERLAPPING INTERVAL, THEN OVERLAPPING INTERVAL AND THEN BIGGER NON OVERALPPING.
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>>ans;
        int n = intervals.size();
        int i = 0;

        //insert all intervals which is less then new interval in ans
        while(i < n && intervals[i][1] < newInterval[0]){  //end of interval < start of new interval
            ans.push_back(intervals[i]);
            i++;
        }

        //merge overlapping intervals
        while(i < n && intervals[i][0] <= newInterval[1]){
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }
        ans.push_back(newInterval);

        //insert rest of element
        while(i < n){
            ans.push_back(intervals[i]);
            i++;
        }
        return ans;
    }
};
/*
Example 1:
Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]

Example 2:
Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
*/


//235. MERGE INTERVALS                                         {T.C = O(NLOGN), S.C = O(N)}
//SORT INTERVALS(START INTERVALS), TEMP = INTERVAL[0], ITERATE ON INTERVAL, IF IT[0] < TEMP[1] : TEMP[1]
//MAX(IT[1], TEMP[1]), ELSE PUST TEMP AND TEMP = I(CURRENT), PUSH TEMP
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


//236. NON OVERLAPPING INTERVALS                           {T.C = O(NLOGN), S.C = O(N)}
//END (INITIAL) < CURRBEGIN, END = INTERVAL[I][1], COUNT++,  RETURN N-COUNT (REMOVABLE ELEMENT)
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int n = intervals.size();

        auto lambda = [&](auto &a, auto &b){                 
            return a[1] < b[1];
        };
        sort(intervals.begin(), intervals.end(), lambda);       //sort on the basis of upper bound
        
        int count = 1;                                          //initial count should 1
        int end = intervals[0][1];               //INITIAL
        for(int i = 1 ; i < n; i++){
            if(intervals[i][0] >= end){         //CURRBEGIN > INITIAL END
                end = intervals[i][1];
                count++;
            }
        }
        return n-count;                                        //for count require removable element                   
    }
};
/*
Example 1:
Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
Output: 1
Explanation: [1,3] can be removed and the rest of the intervals are non-overlapping.

Example 2:
Input: intervals = [[1,2],[1,2],[1,2]]
Output: 2
Explanation: You need to remove two [1,2] to make the rest of the intervals non-overlapping.

Example 3:
Input: intervals = [[1,2],[2,3]]
Output: 0
Explanation: You don't need to remove an
*/


/*-----------------------------------------THE END-----------------------------------------------------*/