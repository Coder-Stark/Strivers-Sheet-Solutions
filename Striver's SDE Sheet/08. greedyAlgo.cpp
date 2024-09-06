#include<bits/stdc++.h>
using namespace std;



//DAY 8: GREEDY ALGORITHM-------------------------------------------------------------------------------------------------
//43. N MEETINGS IN ONE ROOM                                                  {T.C = O(N*LOGN), S.C = O(N)}
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
        
        int count = 1;
        int ansEnd = v[0].second;            //end time of last selected meeting
        for(int i = 1 ; i < n ; i++){
            if(v[i].first > ansEnd){
                count++;
                ansEnd = v[i].second;
            }
        }
        return count;
    }
};
/*
Input: n = 6, start[] = [1, 3, 0, 5, 8, 5], end[] =  [2, 4, 6, 7, 9, 9]
Output: 4
Explanation: Maximum four meetings can be held with given start and end timings. The meetings are - (1, 2), (3, 4), (5,7) and (8,9)

Input: n = 3, start[] = [10, 12, 20], end[] = [20, 25, 30]
Output: 1
Explanation: Only one meetings can be held with given start and end timings.
*/


//44. MINIMUM PLATFORMS (TWO POINTERS)                                     {T.C = O(N*LOGN), S.C = O(1)}
class Solution{
public:
    //USING 2 POINTERS
    int findPlatform(int arr[], int dep[], int n)
    {
        // Sort the arrival and departure times in ascending order
        sort(arr, arr + n);
        sort(dep, dep + n);
    
        int platforms = 1;               // At least one platform is required
        int maxPlatforms = 1;            // Keep track of the maximum number of platforms needed
    
        int arrivalIndex = 1;            //arr[0] = req 1 platfrom handled above
        int departureIndex = 0;
    
        while (arrivalIndex < n && departureIndex < n) {
            if (arr[arrivalIndex] <= dep[departureIndex]) {   //new train arrived and req platform
                platforms++;                                 // Increment the number of platforms needed
                maxPlatforms = max(maxPlatforms, platforms);
                arrivalIndex++;
            } else {
                platforms--;                                 // Reduce the number of platforms needed
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


//45. JOB SEQUENCING PROBLEM                                                {T.C = O(N*LOGN), S.C = O(N)}
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
            
            for(int j = currDead ; j > 0 ; j--){  //put element reverse (between space may accumulate another)
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
Input: Jobs = [[1,4,20],[2,1,1],[3,1,40],[4,1,30]]
Output: 2 60
Explanation: Job1 and Job3 can be done with maximum profit of 60 (20+40).

Input: Jobs = [[1,2,100],[2,1,19],[3,2,27],[4,1,25],[5,1,15]]
Output: 2 127
Explanation: 2 jobs can be done with maximum profit of 127 (100+27).
*/


//46. FRACTIONAL KNAPSACK                                                {T.C = O(N*LOGN), S.C = O(N)}
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
Input: n = 3, w = 50, value[] = [60,100,120], weight[] = [10,20,30]
Output: 240.000000
Explanation: Take the item with value 60 and weight 10, value 100 and weight 20 and split the third item with value 120 and weight 30, to fit it into weight 20. so it becomes (120/30)*20=80, so the total value becomes 60+100+80.0=240.0 Thus, total maximum value of item we can have is 240.00 from the given capacity of sack. 

Input: n = 2, w = 50, value[] = [60,100], weight[] = [10,20]
Output: 160.000000
Explanation: Take both the items completely, without breaking. Total maximum value of item we can have is 160.00 from the given capacity of sack.
*/


//47. COIN CHANGE                                                            {T.C = O(N*M), S.C = O(N*M)}
class Solution {
public:
    int dp[13][10001];
    int solveMem(vector<int>&coins, int sum, int i){
        int n = coins.size();
        //base case
        if(sum == 0) return 0;                     //NO TAKE ANY COIN(0)
        if(i >= n || sum < 0) return INT_MAX;
        
        if(dp[i][sum] != -1) return dp[i][sum];

        int incl = INT_MAX;
        if(sum >= coins[i]){
            int inclAns = solveMem(coins, sum-coins[i], i);     //use same coin(i)
            if(inclAns != INT_MAX) incl = inclAns+1;            //increase count of coin
        }
        int excl = 0 + solveMem(coins, sum, i+1);

        return dp[i][sum] = min(incl, excl);

    }
    int coinChange(vector<int>& coins, int amount) {
        memset(dp, -1, sizeof(dp));
        int ans = solveMem(coins, amount, 0);                  //0 = initial index
        return ans == INT_MAX ? -1 : ans;                 
    }
};
/*
Example 1:
Input: amount = 5, coins = [1,2,5]
Output: 4
Explanation: there are four ways to make up the amount:
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1

Example 2:
Input: amount = 3, coins = [2]
Output: 0
Explanation: the amount of 3 cannot be made up just with coins of 2.

Example 3:
Input: amount = 10, coins = [10]
Output: 1
*/


//48. ASSIGN COOKIES                                                         {T.C = O(N*LOGN), S.C = O(1)}
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        int n = g.size(), m = s.size();
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int i = 0, j = 0, count = 0;
        while(i < n && j < m){
            if(g[i] <= s[j]){                    //req <= have
                count++;
                i++;
            }
            j++;
        }
        return count;
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
