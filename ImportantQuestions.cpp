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


//10. COURSE SCHEDULE IV                                               {T.C = O(N^3), S.C = O(N^2)}
class Solution {
public:
    vector<int>topoSort(vector<vector<int>>&edges, int n, vector<vector<bool>>&reachMatrix){
        unordered_map<int,vector<int>>adj;
        vector<int>inDegree(n, 0);
        for(auto it : edges){
            adj[it[0]].push_back(it[1]);
            inDegree[it[1]]++;                        //0->1
        }
        queue<int>q;
        for(int i = 0 ; i < n; i++){
            if(inDegree[i] == 0) q.push(i);
        }
        vector<int>ans;
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            ans.push_back(frontNode);
            for(auto it : adj[frontNode]){

                reachMatrix[frontNode][it] = true;                   //directly connected
                for(int i = 0 ; i < n ; i++){                        //indirect connection from currNode
                    if(reachMatrix[i][frontNode] == true) reachMatrix[i][it] = true;
                }

                inDegree[it]--;
                if(inDegree[it] == 0) q.push(it);
            }
        }
        return ans;
    }
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        int n = numCourses;
        vector<vector<bool>>reachMatrix(n, vector<bool>(n, false));
        vector<int>topo = topoSort(prerequisites, n, reachMatrix);

        vector<bool>ans;
        for(auto it : queries){
            ans.push_back(reachMatrix[it[0]][it[1]]);
        }

        return ans;
    }
};
/*
Example 1:
Input: numCourses = 2, prerequisites = [[1,0]], queries = [[0,1],[1,0]]
Output: [false,true]
Explanation: The pair [1, 0] indicates that you have to take course 1 before you can take course 0.
Course 0 is not a prerequisite of course 1, but the opposite is true.

Example 2:
Input: numCourses = 2, prerequisites = [], queries = [[1,0],[0,1]]
Output: [false,false]
Explanation: There are no prerequisites, and each course is independent.

Example 3:
Input: numCourses = 3, prerequisites = [[1,2],[1,0],[2,0]], queries = [[1,0],[1,2]]
Output: [true,true]
*/


//11. NODE WITH HIGHEST EDGE SCORE                                         {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int edgeScore(vector<int>& edges) {
        int n = edges.size();
        vector<long long>inDegree(n, 0);
        for(int i = 0; i < n ; i++){
            inDegree[edges[i]] += i;                       //not +1 (+ value of node)
        }

        int maxScoreNode = 0;
        long long maxScore = 0;

        for(int i = n-1 ; i >= 0 ; i--){                  //ensure smallest index is choosen at last
            if(inDegree[i] >= maxScore){
                maxScore = inDegree[i];
                maxScoreNode = i;
            }
        }
        return maxScoreNode;
    }
};
/*
Example 1:
Input: edges = [1,0,0,0,0,7,7,5]
Output: 7
Explanation:
- The nodes 1, 2, 3 and 4 have an edge pointing to node 0. The edge score of node 0 is 1 + 2 + 3 + 4 = 10.
- The node 0 has an edge pointing to node 1. The edge score of node 1 is 0.
- The node 7 has an edge pointing to node 5. The edge score of node 5 is 7.
- The nodes 5 and 6 have an edge pointing to node 7. The edge score of node 7 is 5 + 6 = 11.
Node 7 has the highest edge score so return 7.

Example 2:
Input: edges = [2,0,0,2]
Output: 0
Explanation:
- The nodes 1 and 2 have an edge pointing to node 0. The edge score of node 0 is 1 + 2 = 3.
- The nodes 0 and 3 have an edge pointing to node 2. The edge score of node 2 is 0 + 3 = 3.
Nodes 0 and 2 both have an edge score of 3. Since node 0 has a smaller index, we return 0.
*/


//12. GET WATCHED VIDEOS BY YOUR FRIENDS                                 {T.C = O(V+E), S.C = O(V+E)}
//BFS (LEVEL WISE)
class Solution {
public:
    vector<string> watchedVideosByFriends(vector<vector<string>>& watchedVideos, vector<vector<int>>& friends, int id, int level) {
        int n = watchedVideos.size();
        unordered_map<int, vector<int>>adj;
        for(int i = 0 ; i < n ; i++){
            for(auto it : friends[i]){                //1st level (me - friend(nbr))
                adj[i].push_back(it);
            }
        }
        queue<pair<int,int>>q;                      //id, level
        q.push({id, 0});
        vector<bool>vis(n, 0);
        vis[id] = true;
        unordered_map<string,int>mp;                          //string, freq
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            int id = frontNode.first;
            int lvl = frontNode.second;
            if(lvl == level){
                for(auto it : watchedVideos[id]){   //insert id's strings
                    mp[it]++;
                }
            }else if(lvl < level){
                for(auto it : adj[id]){
                    if(!vis[it]){
                        q.push({it, lvl+1});
                        vis[it] = true;
                    }
                }
            }
        }
        vector<string>ans;
        for(auto it : mp) ans.push_back(it.first);

        auto lambda = [&](auto &a, auto &b){
            if(mp[a] != mp[b]) return mp[a] < mp[b];
            return a < b;
        };
        sort(ans.begin(), ans.end(), lambda);

        return ans;
    }
};
/*
Example 1:
Input: watchedVideos = [["A","B"],["C"],["B","C"],["D"]], friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 1
Output: ["B","C"] 
Explanation: 
You have id = 0 (green color in the figure) and your friends are (yellow color in the figure):
Person with id = 1 -> watchedVideos = ["C"] 
Person with id = 2 -> watchedVideos = ["B","C"] 
The frequencies of watchedVideos by your friends are: 
B -> 1 
C -> 2

Example 2:
Input: watchedVideos = [["A","B"],["C"],["B","C"],["D"]], friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 2
Output: ["D"]
Explanation: 
You have id = 0 (green color in the figure) and the only friend of your friends is the person with id = 3 (yellow color in the figure).
*/


//13. COUNT THE NUMBER OF CONSISTENT STRINGS                                {T.C = O(N*M), S.C = O(N)}
class Solution {
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        set<char>st(allowed.begin(), allowed.end());
        int n = words.size();
        int count = 0;
        for(auto it : words){                     //traverse all strings of words
            bool isConsistent = true;
            for(char ch : it){                    //traverse each strings via character match
                if(!st.count(ch)){
                    isConsistent = false;
                    break;
                }
            }
            if(isConsistent == true) count++;
        }
        return count;
    }
};
/*
Example 1:
Input: allowed = "ab", words = ["ad","bd","aaab","baa","badab"]
Output: 2
Explanation: Strings "aaab" and "baa" are consistent since they only contain characters 'a' and 'b'.

Example 2:
Input: allowed = "abc", words = ["a","b","c","ab","ac","bc","abc"]
Output: 7
Explanation: All strings are consistent.

Example 3:
Input: allowed = "cad", words = ["cc","acd","b","ba","bac","bad","ac","d"]
Output: 4
Explanation: Strings "cc", "acd", "ac", and "d" are consistent.
*/


//14. SHORTEST PATH WITH ALTERNATING COLORS                                   {T.C = O(V+E), S.C = (V)}
//BFS (SIMILAR TO DIJKSTRA)
class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
        unordered_map<int, vector<pair<int,int>>>adj;
        for(auto it : redEdges) adj[it[0]].push_back({it[1], 0});  //0 = red  //u->{v, clr(0[red], 1[blue])}
        for(auto it : blueEdges) adj[it[0]].push_back({it[1], 1}); //0 = blue

        vector<vector<int>>minDis(n+1, {INT_MAX, INT_MAX});
        queue<pair<int,int>>q;           //node, clr
        q.push({0, 0});                  //src distance always 0
        q.push({0, 1});                  //same above(no matters clr)
        minDis[0] = {0, 0};              //node, clr
        int count = 1;                   //curr dist from src node
        //bfs
        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                auto frontNode = q.front();
                q.pop();
                int node = frontNode.first;
                int clr  = frontNode.second;
                int newClr = clr ^ 1;  //change clr 1 to 0 or 0 to 1
                for(auto it : adj[node]){
                    if(it.second == newClr){         //alternate sequence
                        if(count < minDis[it.first][newClr]){
                            minDis[it.first][newClr] = count;
                            q.push({it.first, newClr});
                        }
                    }
                }

            }
            count++;
        }

        vector<int>ans(n);
        for(int i = 0 ; i < n; i++){
            int mini = min(minDis[i][0], minDis[i][1]);
            ans[i] = (mini == INT_MAX ? -1 : mini); 
        }
        return ans;
    }
};
/*
Example 1:
Input: n = 3, redEdges = [[0,1],[1,2]], blueEdges = []
Output: [0,1,-1]

Example 2:
Input: n = 3, redEdges = [[0,1]], blueEdges = [[2,1]]
Output: [0,1,-1]
*/


//15. UNCOMMON WORDS FROM TWO SENTENCES                              
//USING TWO POINTERS                                               //{T.C = O(N+M), S.C = O(N)}
class Solution {
public:
    vector<string> uncommonFromSentences(string s1, string s2) {
        int n = s1.length(), m = s2.length();
        unordered_map<string, int>mp;
        int i = 0;
        while(i < n){
            int j = i;
            while(j < n && s1[j] != ' ') j++;
            string word = s1.substr(i, j-i);
            mp[word]++;
            i = j+1;                  //move to next word
        }

        i = 0;                        //reset for next string
        while(i < m){
            int j = i;
            while(j < m && s2[j] != ' ') j++;
            string word = s2.substr(i, j-i);
            mp[word]++;
            i = j+1;
        }
        vector<string>ans;
        for(auto it : mp){
            if(it.second == 1) ans.push_back(it.first);
        }
        return ans;
    }
};

//USING STL (STRINGSTREAM)                                         {T.C = O(N+M), S.C = O(N)}
class Solution {
public:
    vector<string> uncommonFromSentences(string s1, string s2) {
        unordered_map<string, int>mp;
        stringstream ss1(s1), ss2(s2);
        string word = "";
        while(ss1 >> word) mp[word]++;
        while(ss2 >> word) mp[word]++;

        vector<string>ans;
        for(auto it : mp){
            if(it.second == 1) ans.push_back(it.first);
        }
        return ans;
    }
};
/*
Example 1:
Input: s1 = "this apple is sweet", s2 = "this apple is sour"
Output: ["sweet","sour"]
Explanation:
The word "sweet" appears only in s1, while the word "sour" appears only in s2.

Example 2:
Input: s1 = "apple apple", s2 = "banana"
Output: ["banana"]
*/


//16. LARGEST NUMBER FORMED FROM AN ARRAY                       {T.C = O(N*LOGN), S.C = O(N)}
class Solution{
public:
	string printLargest(int n, vector<string> &arr) {
	    
	    auto lambda = [&](auto &a, auto &b){
	        if(a+b > b+a) return true;           //3+30 = 330 > 30+3 = 303
	        return false;
	    };
	    sort(arr.begin(), arr.end(), lambda);
	    
	    string ans = "";
	    for(auto it : arr) ans += it;
	    return ans;
	}
};

//LARGEST NUMBER                                                {T.C = O(N*LOGN), S.C = O(N)}
//SAME AS ABOVE JUST FIRST CONVERT INTEGER VECTOR INTO STRING VECTOR (HANDLE EXTRA CASE)
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<string>arr;             //convert int vector into string vector
        for(auto it : nums) arr.push_back(to_string(it));

        auto lambda = [&](auto &a, auto &b){
            if(a + b > b + a) return true;          //3+30 = 330 > 30+3 = 303
            return false;
        };
        sort(arr.begin(), arr.end(), lambda);

        string ans = "";
        for(auto it : arr)  ans += it;

        bool all0 = true;             //handle "00" output "0" only
        for(auto &it : ans){
            if(it != '0'){
                all0 = false;
                break;
            }
        }

        return all0 == true ? "0" : ans;
    }
};
/*
Input: n = 5, arr[] =  {"3", "30", "34", "5", "9"}
Output: "9534330"
Explanation: Given numbers are  {"3", "30", "34", "5", "9"}, the arrangement "9534330" gives the largest value.

Input: n = 4, arr[] =  {"54", "546", "548", "60"}
Output: "6054854654"
Explanation: Given numbers are {"54", "546", "548", "60"}, the arrangement "6054854654" gives the largest value.
*/


//17. NEXT PERMUTATION         
//using STL                                                                             {T.C = O(N), S.C = O(1)}
class Solution{
public:
    vector<int> nextPermutation(int N, vector<int> arr){
        next_permutation(arr.begin(), arr.end());
        return arr;
    }
};


//18. CONVERT 1D ARRAY INTO 2D MATRIX                                  {T.C = O(N), S.C = O(N)}
class Solution {
public:
    vector<vector<int>> construct2DArray(vector<int>& original, int m, int n) {
        //base case
        if(original.size() != m*n) return {};

        vector<vector<int>>matrix(m, vector<int>(n));
        for(int i = 0 ; i < original.size() ; i++){
            int row = i / n;                              //row = i / col(total)
            int col = i % n;                              //col = i % col(total)  

            matrix[row][col] = original[i]; 
        }
        return matrix;
    }
};
/*
Example 1:
Input: original = [1,2,3,4], m = 2, n = 2
Output: [[1,2],[3,4]]
Explanation: The constructed 2D array should contain 2 rows and 2 columns.
The first group of n=2 elements in original, [1,2], becomes the first row in the constructed 2D array.
The second group of n=2 elements in original, [3,4], becomes the second row in the constructed 2D array.

Example 2:
Input: original = [1,2,3], m = 1, n = 3
Output: [[1,2,3]]
Explanation: The constructed 2D array should contain 1 row and 3 columns.
Put all three elements in original into the first row of the constructed 2D array.

Example 3:
Input: original = [1,2], m = 1, n = 1
Output: []
Explanation: There are 2 elements in original.
It is impossible to fit 2 elements in a 1x1 2D array, so return an empty 2D array.
*/


//19. ROTATE IMAGE 90 DEGREE                                              {T.C = O(N^2), S.C = O(1)}
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();             //n = m
        for(int i = 0 ; i < n; i++){                  //transpose of matrix
            for(int j = i ; j < n ; j++){             //START WITH I NOT 0
                swap(matrix[i][j], matrix[j][i]);
            }
        }

        //reverse each row
        for(int i = 0 ; i < n; i++){
            int l = 0, r = n-1;
            while(l <= r){
                swap(matrix[i][l], matrix[i][r]);
                l++, r--;
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


//20. MY CALENDER I                                                  {T.C = O(K), S.C = O(K)}
//INTERVALS
class MyCalendar {
public:
    vector<pair<int,int>>interval;
    MyCalendar() {}
    
    //overlap = a < e && s < b
    bool book(int start, int end) {       //{T.C = O(K), S.C = O(K) K = INTERVALS}
        for(auto it : interval){
            int intvlStart = it.first;
            int intvlEnd   = it.second;
            if(intvlStart < end && start < intvlEnd) return false;    //overlap
        }
        interval.push_back({start, end});
        return true;
    }
};
/*
Example 1:

Input
["MyCalendar", "book", "book", "book"]
[[], [10, 20], [15, 25], [20, 30]]
Output
[null, true, false, true]
Explanation
MyCalendar myCalendar = new MyCalendar();
myCalendar.book(10, 20); // return True
myCalendar.book(15, 25); // return False, It can not be booked because time 15 is already booked by another event.
myCalendar.book(20, 30); // return True, The event can be booked, as the first event takes every time less than 20, but not including 20.
*/



//21. COMPARE VERSIONS                                                {T.C = O(MAX(N, M)), S.C = O(N+M)}
class Solution {
public:
    vector<string>getTokens(string &str){
        stringstream ss(str);                      //convert string to streamstring(token's string)
        vector<string>ans;
        string token = "";
        while(getline(ss, token, '.')){             //stringstream, temp string , delimeter(divider)
            ans.push_back(token);
        }
        return ans;
    }
    int compareVersion(string version1, string version2) {
        vector<string>v1 = getTokens(version1);
        vector<string>v2 = getTokens(version2);

        int n = v1.size(), m = v2.size();
        int i = 0;
        while(i < n || i < m){
            int a = i < n ? stoi(v1[i]) : 0;
            int b = i < m ? stoi(v2[i]) : 0;

            if(a < b) return -1;
            else if(a > b) return 1;
            i++;
        }
        return 0;
    }
};
/*
Example 1:
Input: version1 = "1.2", version2 = "1.10"
Output: -1
Explanation:
version1's second revision is "2" and version2's second revision is "10": 2 < 10, so version1 < version2.

Example 2:
Input: version1 = "1.01", version2 = "1.001"
Output: 0
Explanation:
Ignoring leading zeroes, both "01" and "001" represent the same integer "1".

Example 3:
Input: version1 = "1.0", version2 = "1.0.0.0"
Output: 0
Explanation:
version1 has less revisions, which means every missing revision are treated as "0".
*/


//22. CHECK IF ARRAY PAIRS ARE DIVISIBLE BY K                         {T.C = O(N), S.C = O(N)}
class Solution {
public:
    /*
    1 % 5 = 1
    9 % 5 = 4
    total = 5 (k)
    (1+9) % 5 (k)
    */
    bool canArrange(vector<int>& arr, int k) {
        unordered_map<int, int> mp; // remainderCount: {remainder, count}

        // Calculate remainders and count frequencies
        for (int num : arr) {
            int remainder = ((num % k) + k) % k;  // Ensure positive remainder
            mp[remainder]++;
        }

        // Check for valid pairs (simple 2 sum problem)
        for (auto &it : mp) {
            int rem = it.first;
            int count = it.second;

            if (rem == 0) {
                // Remainder 0 must have an even count to be paired
                if (count % 2 != 0) return false;
            } else {
                int complement = k - rem;
                if (mp[rem] != mp[complement]) return false;
            }
        }

        return true;
    }
};
/*
Example 1:
Input: arr = [1,2,3,4,5,10,6,7,8,9], k = 5
Output: true
Explanation: Pairs are (1,9),(2,8),(3,7),(4,6) and (5,10).

Example 2:
Input: arr = [1,2,3,4,5,6], k = 7
Output: true
Explanation: Pairs are (1,6),(2,5) and(3,4).

Example 3:
Input: arr = [1,2,3,4,5,6], k = 10
Output: false
Explanation: You can try all possible pairs to see that there is no way to divide arr into 3 pairs each with sum divisible by 10.
*/


//23. PERMUTATION IN A STRING                                              
//BRUTE FORCE                                                               {T.C = O(N! * N), S.C = O(N)}
class Solution {
public:
    void totalPermutation(string &s, unordered_set<string>&st){
        st.insert(s);
        while(next_permutation(s.begin(), s.end())){
            st.insert(s);
        }
    }
    bool checkInclusion(string s1, string s2) {
        sort(s1.begin(), s1.end());
        unordered_set<string>st;
        totalPermutation(s1, st);

        for(auto it : st){
            if(s2.find(it) != string :: npos) return true;
        }
        return false;
    }
};

//BETTER                                                                     {T.C = O(M*NLOGN), S.C = O(N)}
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n = s1.length(), m = s2.length();
        sort(s1.begin(), s1.end());

        for(int i = 0 ; i <= m-n ; i++){
            string subStr = s2.substr(i, n);        //substring of len s1 check all substr
            sort(subStr.begin(), subStr.end());
            if(subStr == s1) return true;
        }
        return false;
    }
};

//BEST (USING SLIDING WINDOW)                                               {T.C = O(N), S.C = O(n)}
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n = s1.length(), m = s2.length();

        if (n > m) return false;        // If s1 is larger than s2, no permutation can exist

        vector<int> s1_freq(26, 0);
        vector<int> s2_freq(26, 0);

        // Fill frequency of characters in s1
        for (int i = 0; i < n; i++) {
            s1_freq[s1[i] - 'a']++;
        }

        int i = 0, j = 0;
        while (j < m) {
            s2_freq[s2[j] - 'a']++;

            if (j-i+1 > n) {                     //n == k
                s2_freq[s2[i] - 'a']--;
                i++;
            }

            if (s1_freq == s2_freq) return true;
            j++;
        }

        // No matching window found
        return false;
    }
};
/*
Example 1:
Input: s1 = "ab", s2 = "eidbaooo"
Output: true
Explanation: s2 contains one permutation of s1 ("ba").

Example 2:
Input: s1 = "ab", s2 = "eidboaoo"
Output: false
*/