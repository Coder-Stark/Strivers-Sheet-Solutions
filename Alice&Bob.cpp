//ALICE AND BOB PROBLEMS (DP)

#include<bits/stdc++.h>
using namespace std;

//01. DIVISOR GAME
//BRUTE FORCE (RECURSION)                                                     {T.C = O(EXP), S.C = O(1)}
class Solution {
public:
    bool solve(int n , bool alice){
        for(int i = 1 ; i < n ; i++){                 //1 for valid divisor
            if(n % i == 0){
                if(alice == true){    //alice turn
                    bool b = solve(n-i, false);       //for bob
                    if(!b) return true;
                }else{                //bob turn
                    bool a = solve(n-i, true);        //for alice
                    if(!a) return true;
                }
            }
        }
        return false;
    }
    bool divisorGame(int n) {
        return solve(n, true);               //alice = true, bob = false
    }
};

//MEMOIZATION (2D DP)                                                     {T.C = O(N^2), S.C = O(N)}
class Solution {
public:
    int dp[1005][2];
    bool solve(int n , bool alice){
        if(dp[n][alice] != -1) return dp[n][alice];

        for(int i = 1 ; i < n ; i++){
            if(n % i == 0){
                if(alice == true){    //alice turn
                    bool b = solve(n-i, false);       //for bob
                    if(!b) return dp[n][alice] = true;
                }else{                //bob turn
                    bool a = solve(n-i, true);        //for alice
                    if(!a) return dp[n][alice] = true;
                }
            }
        }
        return dp[n][alice] = false;
    }
    bool divisorGame(int n) {
        memset(dp, -1, sizeof(dp));
        return solve(n, true);               //alice = true, bob = false
    }
};
/*
Example 1:
Input: n = 2
Output: true
Explanation: Alice chooses 1, and Bob has no more moves.

Example 2:
Input: n = 3
Output: false
Explanation: Alice chooses 1, Bob chooses 1, and Alice has no more moves.
*/


//02. STONE GAME I                                                           {T.C = O(1), S.C = O(1)}
class Solution {
public:
    //even len arr, choose index(even or odd) , if(even > odd) or (odd > even) alice wins always
    bool stoneGame(vector<int>& piles) {        
        return true;
    }
};
/*
Example 1:
Input: piles = [5,3,4,5]
Output: true
Explanation: 
Alice starts first, and can only take the first 5 or the last 5.
Say she takes the first 5, so that the row becomes [3, 4, 5].
If Bob takes 3, then the board is [4, 5], and Alice takes 5 to win with 10 points.
If Bob takes the last 5, then the board is [3, 4], and Alice takes 4 to win with 9 points.
This demonstrated that taking the first 5 was a winning move for Alice, so we return true.

Example 2:
Input: piles = [3,7,2,3]
Output: true
*/