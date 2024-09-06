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


//03. SIEVE'S ALGO TO FINDING PRIME TILL N                                  {T.C = O(N*LOG(LOGN)), S.C = O(N)}
class Solution{
public:
    vector<int> sieveOfEratosthenes(int n){
        vector<bool>isPrime(n+1, true);
        isPrime[0] = isPrime[1] = false;
        for(int i = 2 ; i*i <= n ; i++){
            if(isPrime[i] == true){
                for(int j = i*i ; j <= n ; j += i){
                    isPrime[j] = false;
                }
            }
        }
        vector<int>needed;
        for(int i = 2 ; i <= n ;i++){
            if(isPrime[i] == true) needed.push_back(i);
        }
        return needed;
    }
};
/*
Example 1:
Input:
N = 10
Output:
2 3 5 7
Explanation:
Prime numbers less than equal to N 
are 2 3 5 and 7.

Example 2:
Input:
N = 35
Output:
2 3 5 7 11 13 17 19 23 29 31
Explanation:
Prime numbers less than equal to 35 are
2 3 5 7 11 13 17 19 23 29 and 31.
*/


//04. CONVERSTION DEC TO BINARY , BINARY TO DECIMAL                              {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int findComplement(int num) {
        // Convert num to binary string
        string binary = "";
        while (num > 0) {                                     //DEC TO BINARY
            binary = (num % 2 == 0 ? '0' : '1') + binary;
            num /= 2;
        }

        string compliment(binary.size(), ' ');

        for (int i = 0; i < binary.size(); i++) {              // Find the complement
            compliment[i] = (binary[i] == '0' ? '1' : '0');
        }

        return stoi(compliment, nullptr, 2);         //binary to dec
    }
};


//05. PALINDROMIC SUBSTRINGS                                                  
//BRUTE FORCE                                                                   {T.C = O(N^3), S.C = O(1)}
class Solution {
public:
    //brute force
    bool isPalindrome(conststring &s){
        int n = s.length();
        int i = 0, j = n-1;
        while(i < j){
            if(s[i] != s[j]) return false;
            i++ , j--;
        }
        return true;
    }
    int countSubstrings(string s) {
        int n = s.length();
        int count = 0;
        for(int i = 0 ; i < n ; i++){
            for(int j = i ; j < n ; j++){
                if(isPalindrome(s.substr(i, j-i+1))) count++;
            }
        }
        return count;
    }
};

//USING BOTTOM UP DP 
//(MIK TEMPLATE FOR PALINDROMES(COUNT, LONGEST PALINDROMIC SUBSTRING OR SUBSEQUENCE)) {T.C = O(N^2), S.C = O(N^2)}
class Solution {
public:
    //USING MIK BLUEPRINT
    int countSubstrings(string s) {
        int n = s.length();
        vector<vector<int>>dp(n, vector<int>(n, false));
        int count = 0;

        for(int l = 1 ; l <= n ; l++){
            for(int i = 0 ; i+l-1 < n; i++){                  //i+L-1(curr len of substring)
                int j = i+l-1;
                if(i == j)   dp[i][j] = true;                            //1 len string
                else if(i+1 == j) dp[i][j] = (s[i] == s[j]);             //2 len string
                else{
                    dp[i][j] = (s[i] == s[j] && dp[i+1][j-1] == true);   //>2 len string
                }

                if(dp[i][j] == true) count++;
            }
        }
        return count;
    }
};

//SMART APPROACH (PALINDROME PROPERTIES)                                   {T.C = O(N^2), S.C = O(N^2)}
class Solution {
public:
    //SMART APPROACH
    void checkOddAndEven(int i, int j, string &s, int &count){
        int n = s.length();
        while(i >= 0 && j < n && s[i] == s[j]){
            count++;
            i--, j++;
        }
    }
    int countSubstrings(string s) {
        int n = s.length();
        int count = 0;
        for(int i = 0 ; i < n ; i++){
            checkOddAndEven(i, i,   s, count);
            checkOddAndEven(i, i+1, s, count);
        }
        return count;
    }
};
/*
Example 1:
Input: s = "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".

Example 2:
Input: s = "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".
*/


//DP
//05. MINIMUM FUEL COST TO REPORT TO THE CAPITAL                               {T.C = O(N), S.C = O(N)}
//USING  DFS
class Solution {
public:
    typedef long long ll;
    double dfs(unordered_map<int, vector<int>>&adj, int parent, int &seats, ll &minCost, int node){
        double representatives = 1;
        for(auto it : adj[node]){
            if(it != parent) representatives += dfs(adj, node, seats, minCost, it); //parent=>node
        }
        if(node != 0){
            minCost += ceil(representatives/seats);   //or (representatives + seats - 1)
        }
        return representatives;
    }
    long long minimumFuelCost(vector<vector<int>>& roads, int seats) {
        int n = roads.size();
        unordered_map<int,vector<int>>adj;    
        for(auto it : roads){
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }

        ll minCost = 0;
        // vector<bool>vis(n, false);           //not req(no cycle), instead parent(-1)
        dfs(adj, -1, seats, minCost, 0);        //0 = intital node
        return minCost;
    }
};
/*
Example 1:
Input: roads = [[0,1],[0,2],[0,3]], seats = 5
Output: 3
Explanation: 
- Representative1 goes directly to the capital with 1 liter of fuel.
- Representative2 goes directly to the capital with 1 liter of fuel.
- Representative3 goes directly to the capital with 1 liter of fuel.
It costs 3 liters of fuel at minimum. 
It can be proven that 3 is the minimum number of liters of fuel needed.

Example 2:
Input: roads = [[3,1],[3,2],[1,0],[0,4],[0,5],[4,6]], seats = 2
Output: 7
Explanation: 
- Representative2 goes directly to city 3 with 1 liter of fuel.
- Representative2 and representative3 go together to city 1 with 1 liter of fuel.
- Representative2 and representative3 go together to the capital with 1 liter of fuel.
- Representative1 goes directly to the capital with 1 liter of fuel.
- Representative5 goes directly to the capital with 1 liter of fuel.
- Representative6 goes directly to city 4 with 1 liter of fuel.
- Representative4 and representative6 go together to the capital with 1 liter of fuel.
It costs 7 liters of fuel at minimum. 
It can be proven that 7 is the minimum number of liters of fuel needed.
*/


//06. REDUNDANT CONNNECTION                                            {T.C = O(N), S.C = O(N)}
//UNION SET
class Solution {
public:
    //UNION AND FIND                              {T.C = O(N), S.C = O(N)}
    vector<int>parent, rank;
    int find(int i){
        if(parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    void Union(int x, int y){
        int xParent = find(x);
        int yParent = find(y);

        if(xParent == yParent) return;

        if(rank[xParent] > rank[yParent]) parent[yParent] = xParent;
        else if(rank[xParent] < rank[yParent]) parent[xParent] = yParent;
        else{
            parent[xParent] = yParent;
            rank[yParent]++;
        }
    }
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        rank.resize(n+1, 0);                  //1 based indexing
        parent.resize(n+1); 
        for(int i = 0 ; i < n ; i++) parent[i] = i;

        for(auto &it : edges){
            int uParent = find(it[0]);
            int vParent = find(it[1]);
            
            if(uParent == vParent) return {it[0], it[1]};
            else Union(uParent, vParent);
        }
        return {};
    }
};
/*
Example 1:
Input: edges = [[1,2],[1,3],[2,3]]
Output: [2,3]

Example 2:
Input: edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
Output: [1,4]
*/


//07. FLOWER PLANTING WITH NO ADJACENT                                     {T.C = O(N), S.C = O(N)}
//FILL THE NODES WITH 4(1,2,3,4) COLOR WHICH IS ADJACENT(NOT SAME)
class Solution {
public:
    vector<int> gardenNoAdj(int n, vector<vector<int>>& paths) {
        unordered_map<int,vector<int>>adj;
        for(auto &it : paths){
            adj[it[0]-1].push_back(it[1]-1);      //1 based to 0 based indexing
            adj[it[1]-1].push_back(it[0]-1);
        }

        vector<int>ans(n);
        for(int i = 0 ; i < n ; i++){
            vector<bool>usedFlower(5, false);                 //0 to 4 (but 0 not used(1st flower 1))
            for(auto j : adj[i]){
                usedFlower[ans[j]] = true;                    //ans[j]=> flowertype(1,2,3,4)
            }
            for(int c = 1 ; c <= 4 ; c++){                    //assign smallest not used flower to adjacent
                if(!usedFlower[c]) ans[i] = c;
            }
        }
        return ans;
    }
};
/*
Example 1:
Input: n = 3, paths = [[1,2],[2,3],[3,1]]
Output: [1,2,3]
Explanation:
Gardens 1 and 2 have different types.
Gardens 2 and 3 have different types.
Gardens 3 and 1 have different types.
Hence, [1,2,3] is a valid answer. Other valid answers include [1,2,4], [1,4,2], and [3,2,1].

Example 2:
Input: n = 4, paths = [[1,2],[3,4]]
Output: [1,2,1,2]

Example 3:
Input: n = 4, paths = [[1,2],[2,3],[3,4],[4,1],[1,3],[2,4]]
Output: [1,2,3,4]
*/


//08. DECODE WAYS                                                          {T.C = O(N), S.C = O(N)}
//DECODE A(1) TO 26(Z) IN VALID STRING
class Solution {
public:
    int dp[105];
    int solveMem(string &s, int i){
        int n = s.length();
        //base case
        if(i == n) return 1;                         //only 1 way to decode

        if(dp[i] != -1) return dp[i];

        int oneCharDecode = 0;                       //1 char decode (a to i)
        int twoCharDecode = 0;                       //2 char decode (11(j) to 26(z))
        if(s[i] != '0'){
            oneCharDecode = solveMem(s, i+1);
        }
        if(i+1 < n && (s[i] == '1' || (s[i] == '2' && s[i+1] <= '6'))){
            twoCharDecode = solveMem(s, i+2);        //skip two places
        }

        return dp[i] = oneCharDecode + twoCharDecode;
    }
    int numDecodings(string s) {
        memset(dp, -1, sizeof(dp));
        int n = s.length();
        //base case 
        if(s[0] == '0') return 0;

        return solveMem(s, 0);
    }
};
/*
Example 1:
Input: s = "12"
Output: 2
Explanation:
"12" could be decoded as "AB" (1 2) or "L" (12).

Example 2:
Input: s = "226"
Output: 3
Explanation:
"226" could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).

Example 3:
Input: s = "06"
Output: 0
Explanation:
"06" cannot be mapped to "F" because of the leading zero ("6" is different from "06"). In this case, the string is not a valid encoding, so return 0.
*/


//09. COURSE SCHEDULE                                                   {T.C = O(V+E), S.C = O(V)}
//TOPOLOGICAL SORT BFS(KAHN'S ALGO)
class Solution {
public:
    //USING KAHNS ALGO
    vector<int>topoSort(vector<vector<int>>&edges, int n){
        unordered_map<int,vector<int>>adj;
        for(auto it : edges){
            adj[it[1]].push_back(it[0]);
        }

        vector<int>inDegree(n, 0);
        for(int i = 0 ; i < n ;i++){
            for(auto it : adj[i]) inDegree[it]++;
        }
        /*
        for(auto it : edges){                //indegree using direct edges(without adj)
            inDegree[it[0]]++;
        }
        */

        queue<int>q;
        for(int i = 0 ; i < n ;i++){
            if(inDegree[i] == 0) q.push(i);
        }

        vector<int>ans;
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            ans.push_back(frontNode);
            for(auto it : adj[frontNode]){
                inDegree[it]--;
                if(inDegree[it] == 0) q.push(it);
            }
        }
        return ans;
    }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int>topo = topoSort(prerequisites, numCourses);
        if(topo.size() == numCourses) return true;      //valid toposort(all course completed)
        return false;
    }
};
/*
Example 1:
Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0. So it is possible.

Example 2:
Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.
*/