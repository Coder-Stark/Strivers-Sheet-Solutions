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


//24. SENTENCE SIMILARITY III                                                 {T.C = O(N+M), S.C = O(N+M)}
class Solution {
public:
    bool areSentencesSimilar(string sentence1, string sentence2) {
        if(sentence1.length() < sentence2.length()) swap(sentence1, sentence2);  //s1 always > s2

        vector<string>vec1;
        stringstream ss1(sentence1);
        string token;
        while(ss1 >> token) vec1.push_back(token);

        vector<string>vec2;
        stringstream ss2(sentence2);
        while(ss2 >> token) vec2.push_back(token);

        int n = vec1.size(), m = vec2.size();
        int i = 0, j = n-1;
        int k = 0, l = m-1;

        while(i < n && k < m && vec1[i] == vec2[k]){
            i++, k++;
        }        
        while(l >= k && vec1[j] == vec2[l]){
            j--, l--;
        }

        return l < k;                                    //cross the pointers (s2 fully traversed)
    }
};
/*
Example 1:
Input: sentence1 = "My name is Haley", sentence2 = "My Haley"
Output: true
Explanation:
sentence2 can be turned to sentence1 by inserting "name is" between "My" and "Haley".

Example 2:
Input: sentence1 = "of", sentence2 = "A lot of words"
Output: false
Explanation:
No single sentence can be inserted inside one of the sentences to make it equal to the other.

Example 3:
Input: sentence1 = "Eating right now", sentence2 = "Eating"
Output: true
Explanation:
sentence2 can be turned to sentence1 by inserting "right now" at the end of the sentence.
*/


//25. MAXIMAL SCORE AFTER APPLYING K OPERATIONS                                    {T.C = O(N*LOGN), S.C = O(N)}
class Solution {
public:
    long long maxKelements(vector<int>& nums, int k) {
        priority_queue<int>maxHeap;
        for(auto it : nums){
            maxHeap.push(it);
        }

        long long sum = 0;
        while(k--){
            int ele = maxHeap.top();
            maxHeap.pop();
            sum += ele;
            maxHeap.push(ceil(ele / 3.0));
        }
        return sum;
    }
};
/*
Example 1:
Input: nums = [10,10,10,10,10], k = 5
Output: 50
Explanation: Apply the operation to each array element exactly once. The final score is 10 + 10 + 10 + 10 + 10 = 50.

Example 2:
Input: nums = [1,10,3,3,3], k = 3
Output: 17
Explanation: You can do the following operations:
Operation 1: Select i = 1, so nums becomes [1,4,3,3,3]. Your score increases by 10.
Operation 2: Select i = 1, so nums becomes [1,2,3,3,3]. Your score increases by 4.
Operation 3: Select i = 2, so nums becomes [1,1,1,3,3]. Your score increases by 3.
The final score is 10 + 4 + 3 = 17.
*/


//26. PRODUCT OF ARRAY EXCEPT SELF                                             {T.C = O(N), S.C = O(N)}
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int>prefixMul(n, 1);
        for(int i = 1; i < n; i++){
            prefixMul[i] = prefixMul[i-1]*nums[i-1];        //exclude nums[i]
        }

        vector<int>suffixMul(n, 1);
        for(int i = n-2 ; i >= 0 ; i--){
            suffixMul[i] = suffixMul[i+1]*nums[i+1];       //exclude nums[i]
        }

        vector<int>ans(n);
        for(int i = 0 ; i < n; i++){
            ans[i] = prefixMul[i]*suffixMul[i];
        }
        return ans;
    }
};
/*
Example 1:
Input: nums = [1,2,3,4]
Output: [24,12,8,6]

Example 2:
Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]
*/


//27. MAXIMUM SUM SUBARRAY (KADANE'S ALGO)                                          {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        int sum = 0, maxSum = INT_MIN;
        for(int i = 0 ; i < n ;i++){
            sum += nums[i];
            maxSum = max(maxSum, sum);
            if(sum < 0) sum = 0;                 //reset sum
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


//28. MAXIMUM PRODUCT SUBARRAY (KADANE'S ALGO)                                          {T.C = O(N), S.C = O(1)}
//USING KADANE'S ALGO(LEFT TO RIGTH, RIGTH TO LEFT BOTH)
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int prod = 1;
        int maxProd = INT_MIN;
        for(int i = 0 ; i < n ; i++){             //left to right
            prod *= nums[i];
            maxProd = max(maxProd, prod);
            if(prod == 0) prod = 1;
        }
        prod = 1;                                 //reset
        for(int i = n-1 ; i >= 0 ; i--){
            prod *= nums[i];
            maxProd = max(maxProd, prod);
            if(prod == 0) prod = 1;
        }

        return maxProd;
    }
};
/*
Example 1:
Input: nums = [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.

Example 2:
Input: nums = [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
*/


//29. LONGEST HAPPY STRING                                                    {T.C = O(1), S.C = O(1)}
class Solution {
public:
    //T.C = O(1), S.C = O(1)
    typedef pair<int,char>P;                              //freq, char
    string longestDiverseString(int a, int b, int c) {
        priority_queue<P>maxHeap;
        if(a > 0) maxHeap.push({a, 'a'});
        if(b > 0) maxHeap.push({b, 'b'});
        if(c > 0) maxHeap.push({c, 'c'});

        string ans = "";
        while(!maxHeap.empty()){
            auto topNode = maxHeap.top();
            maxHeap.pop();
            int currFreq = topNode.first;
            char currChar = topNode.second;

            int n = ans.size();
            if(n >= 2 && ans[n-1] == currChar && ans[n-2] == currChar){  //consecutive(3)
                if(maxHeap.empty()) break;

                auto nextTopNode = maxHeap.top();
                maxHeap.pop();
                int nextFreq = nextTopNode.first;
                char nextChar = nextTopNode.second;

                ans.push_back(nextChar);
                nextFreq--;
                if(nextFreq > 0) maxHeap.push({nextFreq, nextChar});
            }else{                                             //not consecutive(3)
                ans.push_back(currChar);
                currFreq--;
            }
            if(currFreq > 0) maxHeap.push({currFreq, currChar});
        }
        return ans;
    }
};
/*
Example 1:
Input: a = 1, b = 1, c = 7
Output: "ccaccbcc"
Explanation: "ccbccacc" would also be a correct answer.

Example 2:
Input: a = 7, b = 1, c = 0
Output: "aabaa"
Explanation: It is the only correct answer in this case.
*/


//30. CONTAINER WITH MOST WATER                                               {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int maxA = 0;
        int i = 0, j = n-1;
        while(i <= j){
            int h = min(height[i], height[j]);         //min height(hold water else flow)
            int w = j-i;
            int a = h*w;
            maxA  = max(maxA, a);
            if(height[i] <= height[j]) i++;
            else j--;
        }
        return maxA;
    }
};
/*
Example 1:
Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.

Example 2:
Input: height = [1,1]
Output: 1
*/


//39. SPLIT A STRING INTO THE MAX NUMBER OF UNIQUE SUBSTRINS      {T.C = O(N*2^N), S.C = O(N)}
//BACKTRACKING (KHANDANI TEMPLET - DO, EXPLORE, UNDO)
class Solution {
public:
    void solve(string &s, unordered_set<string>&st, int currCount, int &maxCount, int i){
        int n = s.length();
        //base case
        if(i >= n){
            maxCount = max(maxCount, currCount);
            return;
        }

        for(int j = i ; j < n ; j++){
            string subStr = s.substr(i, j-i+1);
            if(!st.count(subStr)){
                st.insert(subStr);                            //DO
                solve(s, st, currCount+1, maxCount, j+1);     //EXPLORE
                st.erase(subStr);                             //UNDO
            }
        }
    }
    int maxUniqueSplit(string s) {
        int n = s.length();
        unordered_set<string>st;                            //find unique strings
        int maxCount = 0;
        int currCount = 0;
        solve(s, st, currCount, maxCount, 0);                //0 = initial index

        return maxCount;
    }
};
/*
Example 1:
Input: s = "ababccc"
Output: 5
Explanation: One way to split maximally is ['a', 'b', 'ab', 'c', 'cc']. Splitting like ['a', 'b', 'a', 'b', 'c', 'cc'] is not valid as you have 'a' and 'b' multiple times.

Example 2:
Input: s = "aba"
Output: 2
Explanation: One way to split maximally is ['a', 'ba'].

Example 3:
Input: s = "aa"
Output: 1
Explanation: It is impossible to split the string any further.
*/


//40. COUSINS IN A BINARY TREE II                                  {T.C = O(N), S.C = O(N)}
class Solution {
public:
    void lvlOrder(TreeNode* root, vector<int>&lvlSum){
        queue<TreeNode*>q;
        q.push(root);
        while(!q.empty()){
            int sz = q.size();
            int sum = 0;
            for(int i = 0; i < sz; i++){
                auto frontNode = q.front();
                q.pop();
                sum += frontNode->val;
                if(frontNode->left) q.push(frontNode->left);
                if(frontNode->right)q.push(frontNode->right);
            }
            lvlSum.push_back(sum);
        }
    }
    TreeNode* newlvlOrder(TreeNode* root, vector<int>& lvlSum) {
        // base case
        root->val = 0;  // root has no siblings or cousins
        queue<TreeNode*> q;
        q.push(root);

        int level = 1;  // level 0 (root level) is already covered
        while (!q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                auto frontNode = q.front();
                q.pop();

                // Initialize sibling sum for left and right children
                int siblingLeftSum = (frontNode->left ? frontNode->left->val : 0);
                int siblingRightSum = (frontNode->right ? frontNode->right->val : 0);
                int siblingBothSum = siblingLeftSum + siblingRightSum;

                // Update the values of children
                if (frontNode->left) {
                    frontNode->left->val = lvlSum[level] - siblingBothSum;
                    q.push(frontNode->left);
                }
                if (frontNode->right) {
                    frontNode->right->val = lvlSum[level] - siblingBothSum;
                    q.push(frontNode->right);
                }
            }
            level++;  // move to the next level
        }
        return root;
    }
    TreeNode* replaceValueInTree(TreeNode* root) {
        //base case
        if(!root) return root;
        vector<int>lvlSum;
        lvlOrder(root, lvlSum);

        TreeNode* ans = newlvlOrder(root, lvlSum);
        return ans;
    }
};
/*
Example 1:
Input: root = [5,4,9,1,10,null,7]
Output: [0,0,0,7,7,null,11]
Explanation: The diagram above shows the initial binary tree and the binary tree after changing the value of each node.
- Node with value 5 does not have any cousins so its sum is 0.
- Node with value 4 does not have any cousins so its sum is 0.
- Node with value 9 does not have any cousins so its sum is 0.
- Node with value 1 has a cousin with value 7 so its sum is 7.
- Node with value 10 has a cousin with value 7 so its sum is 7.
- Node with value 7 has cousins with values 1 and 10 so its sum is 11.

Example 2:
Input: root = [3,1,2]
Output: [0,0,0]
Explanation: The diagram above shows the initial binary tree and the binary tree after changing the value of each node.
- Node with value 3 does not have any cousins so its sum is 0.
- Node with value 1 does not have any cousins so its sum is 0.
- Node with value 2 does not have any cousins so its sum is 0.
*/


//41. MAXIMUM NUMBER OF MOVES IN A GRID                           {T.C = O(N*M), S.C = O(N*M)}
class Solution {
public:
    int dp[1005][1005];
    vector<vector<int>> directions = {{-1, 1}, {0, 1}, {1, 1}}; // Right-up, right, right-down
    bool isValid(int i, int j, int n, int m) {
        return i >= 0 && i < n && j >= 0 && j < m;
    }

    int dfs(vector<vector<int>>& grid, int i, int j) {
        int n = grid.size(), m = grid[0].size();
        int maxMove = 0;

        if (dp[i][j] != -1) return dp[i][j];
        
        for (auto it : directions) {
            int newRow = i + it[0];
            int newCol = j + it[1];
            if (isValid(newRow, newCol, n, m) && grid[newRow][newCol] > grid[i][j]) {
                maxMove = max(maxMove, 1 + dfs(grid, newRow, newCol));
            }
        }

        return dp[i][j] = maxMove;
    }

    int maxMoves(vector<vector<int>>& grid) {
        memset(dp, -1, sizeof(dp));
        int n = grid.size(), m = grid[0].size();
        int maxMove = 0;
        
        for (int i = 0; i < n; i++) {         // Start DFS from each cell in the first column
            maxMove = max(maxMove, dfs(grid, i, 0));        //row(1st only), col (all)
        }
        return maxMove;
    }
};
/*
Example 1:
Input: grid = [[2,4,3,5],[5,4,9,3],[3,4,2,11],[10,9,13,15]]
Output: 3
Explanation: We can start at the cell (0, 0) and make the following moves:
- (0, 0) -> (0, 1).
- (0, 1) -> (1, 2).
- (1, 2) -> (2, 3).
It can be shown that it is the maximum number of moves that can be made.

Example 2:
Input: grid = [[3,2,4],[2,1,9],[1,1,7]]
Output: 0
Explanation: Starting from any cell in the first column we cannot perform any moves.
*/


//42. LENGHT OF LONGEST INCREASING SUBSEQUENCE (LIS)           {T.C = O(N^2), S.C = O(N)}
//USING TOP DOWN DP
class Solution {
public:
    int dp[2501][2501];
    int solveMem(vector<int>&nums , int i, int prev){
        int n = nums.size();
        //base case
        if(i >= n) return 0;

        if(dp[i][prev+1] != -1) return dp[i][prev+1];       //+1 for handle out of bound

        int incl = INT_MIN;                                 //max len
        if(prev == -1 || nums[i] > nums[prev]){             //1st ele or next greater then prev
            incl  = 1 + solveMem(nums, i+1, i);             //prev becomes currIdx(i)
        }
        int excl = 0 + solveMem(nums, i+1, prev);

        return dp[i][prev+1] = max(incl, excl);
    }
    int lengthOfLIS(vector<int>& nums) {
        memset(dp, -1, sizeof(dp));
        return solveMem(nums, 0, -1);           //0 = initial index, -1 = prevIdx
    }
};

//USING BOTTOM UP DP
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int>dp(n, 1);                         //initially all dp element 1(min LIS len)
        
        int maxLen = 1;                             //atleast 1 element is there
        for(int i = 0 ; i < n ;i++){                //i = currIdx
            for(int p = 0 ; p < i ; p++){           //p = prevIdx
                if(nums[p] < nums[i]){
                    dp[i] = max(dp[i], 1 + dp[p]);
                }
            }
            maxLen = max(maxLen, dp[i]);
        }
        return maxLen;
    }
};
/*
Example 1:
Input: nums = [10,9,2,5,3,7,101,18]
Output: 4
Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.

Example 2:
Input: nums = [0,1,0,3,2,3]
Output: 4

Example 3:
Input: nums = [7,7,7,7,7,7,7]
Output: 1
*/


//43. MINIMUM NUMBER OF REMOVALS TO MAKE MOUNTAIN ARRAY             {T.C = O(N^2), S.C = O(N)}
class Solution {
public:
    vector<int>LIS(vector<int>&nums, int n){
        vector<int>dp(n, 1);                              //dp == lis
        for(int i = 0 ; i < n; i++){                      //currIdx
            for(int p = 0; p < i ; p++){                  //prevIdx
                if(nums[p] < nums[i]){
                    dp[i] = max(dp[i], 1 + dp[p]);        //1 + prevValue
                }
            }
        }
        return dp;
    }
    vector<int>LDS(vector<int>&nums, int n){             //just opposite of lis
        vector<int>dp(n, 1);
        for(int i = n-1 ; i >= 0 ; i--){
            for(int p = n-1 ; p > i ; p--){              //lis(0 to i) , lds (n-1 to i)
                if(nums[p] < nums[i]){
                    dp[i] = max(dp[i], 1 + dp[p]);
                }
            }
        }
        return dp;
    }
    int minimumMountainRemovals(vector<int>& nums) {
        int n = nums.size();
        vector<int>lis = LIS(nums, n);                    //longest increasing subsequence
        vector<int>lds = LDS(nums, n);                    //longest decreasing subsequence
        
        int minRemove = INT_MAX;
        for(int i = 0 ; i < n ; i++){
            if(lis[i] > 1 && lds[i] > 1){                //for finding correct mountains formation
                minRemove = min(minRemove, n- (lis[i] + lds[i]) + 1);
            }
        }
        return minRemove;
    }
};
/*
Example 1:
Input: nums = [1,3,1]
Output: 0
Explanation: The array itself is a mountain array so we do not need to remove any elements.

Example 2:
Input: nums = [2,1,1,5,6,2,3,1]
Output: 3
Explanation: One solution is to remove the elements at indices 0, 1, and 5, making the array nums = [1,5,6,3,1].
*/


//44. DELETE CHARACTERS TO MAKE FANCY STRINGS                  {T.C = O(N), S.C = O(N)}
class Solution {
public:
    string makeFancyString(string s) {
        string ans = "";
        int n = s.length();
        ans.push_back(s[0]);
        int count = 1;
        for(int i = 1; i < n ; i++){
            if(s[i] == ans.back()){
                count++;
                if(count < 3) ans.push_back(s[i]);
            }else{
                count = 1;                            //reset count
                ans.push_back(s[i]);
            }
        }
        return ans;
    }
};
/*
Example 1:
Input: s = "leeetcode"
Output: "leetcode"
Explanation:
Remove an 'e' from the first group of 'e's to create "leetcode".
No three consecutive characters are equal, so return "leetcode".

Example 2:
Input: s = "aaabaaaa"
Output: "aabaa"
Explanation:
Remove an 'a' from the first group of 'a's to create "aabaaaa".
Remove two 'a's from the second group of 'a's to create "aabaa".
No three consecutive characters are equal, so return "aabaa".

Example 3:
Input: s = "aab"
Output: "aab"
Explanation: No three consecutive characters are equal, so return "aab".
*/


//45. CIRCULAR SENTENCE                                         {T.C = O(N), S.C = O(M)}
class Solution {
public:
    bool isCircularSentence(string sentence) {
        int n = sentence.size();
        stringstream ss(sentence);
        string firstWord, prevWord;

        ss >> firstWord;                           //extract first word
        prevWord = firstWord;

        string word;
        while(ss >> word){
            if(prevWord.back() != word.front()) return false;    //match consecutive words
            prevWord = word;
        }

        return prevWord.back() == firstWord.front();     //match first and last stream 
    }
};
/*
Example 1:
Input: sentence = "leetcode exercises sound delightful"
Output: true
Explanation: The words in sentence are ["leetcode", "exercises", "sound", "delightful"].
- leetcode's last character is equal to exercises's first character.
- exercises's last character is equal to sound's first character.
- sound's last character is equal to delightful's first character.
- delightful's last character is equal to leetcode's first character.
The sentence is circular.

Example 2:
Input: sentence = "eetcode"
Output: true
Explanation: The words in sentence are ["eetcode"].
- eetcode's last character is equal to eetcode's first character.
The sentence is circular.

Example 3:
Input: sentence = "Leetcode is cool"
Output: false
Explanation: The words in sentence are ["Leetcode", "is", "cool"].
- Leetcode's last character is not equal to is's first character.
The sentence is not circular.
*/


//46. SORTED MATRIX                                                                       {T.C = O(N^2 LOGN), S.C = O(N^2)}
class Solution {
  public:
    vector<vector<int>> sortedMatrix(int n, vector<vector<int>> mat) {
        vector<int>ans;
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ;j++){
                ans.push_back(mat[i][j]);
            }
        }
        sort(ans.begin(), ans.end());
        //till now we got a single sorted array
        
        //creating a 2d matrix and push again in mat
        int index = 0;
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                mat[i][j] = ans[index];
                index++;
            }
        }
        return mat;
    }
};
/*
Input:
N=4
Mat=[[10,20,30,40],
[15,25,35,45] 
[27,29,37,48] 
[32,33,39,50]]
Output:
10 15 20 25 
27 29 30 32
33 35 37 39
40 45 48 50
Explanation:
Sorting the matrix gives this result.
*/

//VERY VERY IMPORTANT (SIEVE)**************************************************************************
//47. PRIME SUBTRACTION OPERATIONS                     {T.C = O(N^2), S.C = O(N)}
class Solution {
public:
    vector<bool> isPrime;  // Changed to vector<bool>
    
    void sieve() {
        isPrime.resize(1000, true);  // Initialize with true
        isPrime[0] = false;
        isPrime[1] = false;

        for (int i = 2; i * i < 1000; i++) {
            if (isPrime[i]) {
                for (int j = i * i; j < 1000; j += i) {
                    isPrime[j] = false;
                }
            }
        }
    }

    bool primeSubOperation(vector<int>& nums) {
        int n = nums.size();
        sieve();

        for (int i = n - 2; i >= 0; i--) {  // Start from the second last element
            if (nums[i] < nums[i + 1]) continue;

            for (int p = 2; p < nums[i]; p++) {
                if (isPrime[p] && (nums[i] - p < nums[i + 1])) {  // Check if p is prime and satisfies the condition
                    nums[i] -= p;
                    break;
                }
            }

            if (nums[i] >= nums[i + 1]) return false;  // After decrement, still not sorted
        }

        return true;
    }
};
/*
Example 1:
Input: nums = [4,9,6,10]
Output: true
Explanation: In the first operation: Pick i = 0 and p = 3, and then subtract 3 from nums[0], so that nums becomes [1,9,6,10].
In the second operation: i = 1, p = 7, subtract 7 from nums[1], so nums becomes equal to [1,2,6,10].
After the second operation, nums is sorted in strictly increasing order, so the answer is true.

Example 2:
Input: nums = [6,8,11,12]
Output: true
Explanation: Initially nums is sorted in strictly increasing order, so we don't need to make any operations.

Example 3:
Input: nums = [5,8,3]
Output: false
Explanation: It can be proven that there is no way to perform operations to make nums sorted in strictly increasing order, so the answer is false.
*/


//48. MINIMIZED MAXIMUM OF PRODUCTS DISTRIBUTED TO ANY STORE                         {T.C = O(N*LOGN), S.C = O(1)}
//BINARY SEARCH , MIN(MAX), SIMILAR TO KOKO BANANA
class Solution {
public:
    bool isPossibleToDistribute(vector<int>&quantities, int n, int x){
        for(auto it : quantities){
            // n -= ceil((double)it / x);                   //ceil(it/x)
            n -= (it + x - 1) / x;
            if(n < 0) return false;
        }
        return true;
    }
    int minimizedMaximum(int n, vector<int>& quantities) {
        int start = 1;
        int end = *max_element(quantities.begin(), quantities.end());
        int ans = 0;
        while(start <= end){
            int mid = start + (end-start)/2;
            if(isPossibleToDistribute(quantities, n, mid)){   //n = shops (available spaces)
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

Input: n = 6, quantities = [11,6]
Output: 3
Explanation: One optimal way is:
- The 11 products of type 0 are distributed to the first four stores in these amounts: 2, 3, 3, 3
- The 6 products of type 1 are distributed to the other two stores in these amounts: 3, 3
The maximum number of products given to any store is max(2, 3, 3, 3, 3, 3) = 3.
Example 2:

Input: n = 7, quantities = [15,10,10]
Output: 5
Explanation: One optimal way is:
- The 15 products of type 0 are distributed to the first three stores in these amounts: 5, 5, 5
- The 10 products of type 1 are distributed to the next two stores in these amounts: 5, 5
- The 10 products of type 2 are distributed to the last two stores in these amounts: 5, 5
The maximum number of products given to any store is max(5, 5, 5, 5, 5, 5, 5) = 5.
Example 3:

Input: n = 1, quantities = [100000]
Output: 100000
Explanation: The only optimal way is:
- The 100000 products of type 0 are distributed to the only store.
The maximum number of products given to any store is max(100000) = 100000.
*/


//49. SHORTEST SUBARRAY TO BE REMOVED TO MAKE ARRAY SORTED     {T.C = O(N), S.C= O(1)}
//TWO POINTERS
class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr) {
        int n = arr.size();
        int i = 0;                           //starting pointer
        int j = n-1;
        while(j > 0 && arr[j] >= arr[j-1]) j--;  //from last to breaking point of sorted

        int ans = j;              //j for handle corner cases , remove one side subarra all

        while(i < j && (i == 0 || arr[i] >= arr[i-1])){  //find j-i-1(invalid window)
            while(j < n && arr[i] > arr[j]) j++;
            ans = min(ans, j-i-1);
            i++;                            //arr[i] < arr[j] i++
        }
        return ans;

    }
};
/*
Example 1:
Input: arr = [1,2,3,10,4,2,3,5]
Output: 3
Explanation: The shortest subarray we can remove is [10,4,2] of length 3. The remaining elements after that will be [1,2,3,3,5] which are sorted.
Another correct solution is to remove the subarray [3,10,4].

Example 2:
Input: arr = [5,4,3,2,1]
Output: 4
Explanation: Since the array is strictly decreasing, we can only keep a single element. Therefore we need to remove a subarray of length 4, either [5,4,3,2] or [4,3,2,1].

Example 3:
Input: arr = [1,2,3]
Output: 0
Explanation: The array is already non-decreasing. We do not need to remove any elements.
*/


//50. NUMBER OF GOOD WAYS TO SPLIT A STRING                    {T.C = (N*LOGN), S.C = O(N)}
//DIVIDE IN 2 PARTS, WITH BOTH SIDE SAME NUMBER OF DISTINCT ELE
class Solution {
public:
    int numSplits(string s) {
        unordered_map<int, int>leftMp;
        unordered_map<int, int>rightMp;
        int count = 0;
        for(auto it : s) leftMp[it]++;
        for(auto it : s){
            rightMp[it]++;
            leftMp[it]--;
            if(leftMp[it] == 0) leftMp.erase(it);
            if(rightMp.size() == leftMp.size()) count++; //same no. of distinct ele
        }
        return count;
    }
};
/*
Example 1:
Input: s = "aacaba"
Output: 2
Explanation: There are 5 ways to split "aacaba" and 2 of them are good. 
("a", "acaba") Left string and right string contains 1 and 3 different letters respectively.
("aa", "caba") Left string and right string contains 1 and 3 different letters respectively.
("aac", "aba") Left string and right string contains 2 and 2 different letters respectively (good split).
("aaca", "ba") Left string and right string contains 2 and 2 different letters respectively (good split).
("aacab", "a") Left string and right string contains 3 and 1 different letters respectively.

Example 2:
Input: s = "abcd"
Output: 1
Explanation: Split the string as follows ("ab", "cd").
*/


//51. SHORTEST DISTANCE AFTER ROAD ADDITION QUERIES I                       {T.C = O(Q(V+E)), S.C = O(V+E)}
//BFS VS DIJKSTRA
class Solution {
public:
    /*
    typedef pair<int, int>P;
    int dijkstra(unordered_map<int, vector<int>>& adj, int src, int dst, int n) {
        priority_queue<P, vector<P>, greater<P>> pq;
        pq.push({0, src});
        vector<int> minDis(n, INT_MAX);
        minDis[src] = 0;
        
        while (!pq.empty()) {
            auto topNode = pq.top();
            pq.pop();
            int dis = topNode.first;
            int u   = topNode.second;
            
            if (dis > minDis[u]) continue;         //skip large dis
            
            for (auto &it : adj[u]) {
                if (minDis[u] + 1 < minDis[it]) {
                    minDis[it] = minDis[u] + 1;
                    pq.push({minDis[it], it});
                }
            }
        }
        
        return minDis[dst];
    }
    */
    int bfs(unordered_map<int,vector<int>>&adj, int src, int dst, int n){
        queue<int>q;
        q.push(src);
        vector<int>minDis(n, INT_MAX);
        minDis[src] = 0;

        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();

            for(auto &it : adj[frontNode]){
                if(minDis[frontNode] + 1 < minDis[it]){
                    minDis[it] = minDis[frontNode] + 1;
                    q.push(it);
                }
            }
        }
        return minDis[dst];
    }
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        // Initialize the adjacency list with initial unidirectional roads
        unordered_map<int, vector<int>> adj; 
        for (int i = 0; i < n - 1; ++i) {            //0->1->2--->n-1
            adj[i].push_back(i + 1);
        }

        vector<int> ans;
        for (auto &it : queries) {             //add connections according to queries
            adj[it[0]].push_back(it[1]);

            //find shortest path for each queries
            // int shortestPath = dijkstra(adj, 0, n - 1, n);    //0 = src, n-1 = dst, n = size
            int shortestPath = bfs(adj, 0, n-1, n);
            ans.push_back(shortestPath);
        }

        return ans;
    }
};
/*
Example 1:
Input: n = 5, queries = [[2,4],[0,2],[0,4]]
Output: [3,2,1]
Explanation:
After the addition of the road from 2 to 4, the length of the shortest path from 0 to 4 is 3.
After the addition of the road from 0 to 2, the length of the shortest path from 0 to 4 is 2.
After the addition of the road from 0 to 4, the length of the shortest path from 0 to 4 is 1.

Example 2:
Input: n = 4, queries = [[0,3],[0,2]]
Output: [1,1]
Explanation:
After the addition of the road from 0 to 3, the length of the shortest path from 0 to 3 is 1.
After the addition of the road from 0 to 2, the length of the shortest path remains 1.
*/


//52. SHORTEST PATH IN A GRID WITH OBSTACLES ELIMINATION                 {T.C = O(N*M*K), S.C = O(N*M*K)}
//BFS
class Solution {
public:
    vector<vector<int>> directions{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    int shortestPath(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        int m = grid[0].size();
        
        queue<vector<int>> que;
        
        int i = 0, j = 0;
        que.push({i, j, k});
        
        bool visited[41][41][1601];
        //vector<vector<vector<bool>>> visited(m, vector<vector<bool>>(n, vector<bool>(k)));
        memset(visited, false, sizeof(visited));
        
        int steps = 0;
        while(!que.empty()) {
            int size = que.size();
            while(size--) {
                vector<int> temp = que.front();
                que.pop();
                int r   = temp[0];
                int c   = temp[1];
                int obs = temp[2];
                
                if(r == n-1 && c == m-1)
                    return steps;
                
                for(auto &it : directions) {
                    
                    int newR = r + it[0];
                    int newC = c + it[1];
                    
                    if(newR < 0 || newR >= n || newC < 0 || newC >= m)         //not isValid
                        continue;
                    
                    if(grid[newR][newC] == 0 && !visited[newR][newC][obs]) {
                        que.push({newR, newC, obs});
                        visited[newR][newC][obs] = true;
                    } else if(grid[newR][newC] == 1 && obs > 0 && !visited[newR][newC][obs-1]) {
                        que.push({newR, newC, obs-1});
                        visited[newR][newC][obs-1] = true;
                    }
                }
                
            }
            steps++;
        }
        
        return -1;
    }
};
/*
Example 1:
Input: grid = [[0,0,0],[1,1,0],[0,0,0],[0,1,1],[0,0,0]], k = 1
Output: 6
Explanation: 
The shortest path without eliminating any obstacle is 10.
The shortest path with one obstacle elimination at position (3,2) is 6. Such path is (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2) -> (3,2) -> (4,2).

Example 2:
Input: grid = [[0,1,1],[1,1,1],[1,0,0]], k = 1
Output: -1
Explanation: We need to eliminate at least two obstacles to find such a walk.
*/


//53. MINIMUM OBSTACLE REMOVAL TO REACH CORNER                           {T.C = O(N*M(LOGN*M)), S.C = O(N*M)}
//DIJKSTRA
class Solution {
public:
    typedef pair<int, pair<int, int>> P; // {distance, {row, col}}
    vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    
    int minimumObstacles(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();

        priority_queue<P, vector<P>, greater<P>> pq; // Min-heap based on distance
        pq.push({0, {0, 0}}); // Start with distance 0 at (0, 0)

        vector<vector<int>> minDis(n, vector<int>(m, INT_MAX)); // To track minimum obstacles
        minDis[0][0] = 0;

        while (!pq.empty()) {
            auto topNode = pq.top();
            pq.pop();

            int dis = topNode.first;
            int r = topNode.second.first;
            int c = topNode.second.second;

            // If we reach the bottom-right cell, return the distance
            if (r == n - 1 && c == m - 1) return dis;

            for (auto& dir : directions) {
                int newR = r + dir[0];
                int newC = c + dir[1];

                // Boundary check
                if (newR < 0 || newR >= n || newC < 0 || newC >= m) continue;

                int newDis = dis + grid[newR][newC]; // Add obstacle weight (1 if obstacle, 0 otherwise)

                // Relaxation step: Update the distance if the new distance is smaller
                if (minDis[newR][newC] > newDis) {
                    minDis[newR][newC] = newDis;
                    pq.push({newDis, {newR, newC}});
                }
            }
        }

        return -1; // Shouldn't reach here for valid inputs
    }
};
/*
Example 1:
Input: grid = [[0,1,1],[1,1,0],[1,1,0]]
Output: 2
Explanation: We can remove the obstacles at (0, 1) and (0, 2) to create a path from (0, 0) to (2, 2).
It can be shown that we need to remove at least 2 obstacles, so we return 2.
Note that there may be other ways to remove 2 obstacles to create a path.

Example 2:
Input: grid = [[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]]
Output: 0
Explanation: We can move from (0, 0) to (2, 4) without removing any obstacles, so we return 0.
*/


//54. MINIMUM TIME TO VISIT A CELL IN A GRID                      {T.C = O(N*M*LOGN*M), S.C = O(N*M)}
//DIJKSTRA
class Solution {
public:
    typedef pair<int, pair<int,int>>P;
    vector<vector<int>>directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    int minimumTime(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        //base case
        if(grid[0][1] > 1 && grid[1][0] > 1) return -1;        //cant move futher (for to and fro)

        priority_queue<P, vector<P>, greater<P>>pq;
        pq.push({0, {0, 0}});                        //time, {row, col}

        vector<vector<int>>minDis(n, vector<int>(m, INT_MAX));
        minDis[0][0] = 0;
        vector<vector<bool>>vis(n, vector<bool>(m, false));

        while(!pq.empty()){
            auto topNode = pq.top();
            pq.pop();

            int time = topNode.first;
            int r   = topNode.second.first;
            int c   = topNode.second.second;

            if(r == n-1 && c == m-1) return time;
            if(vis[r][c] == true) continue;         //already visited

            vis[r][c] = true;

            for(auto &it : directions){
                int newR = r + it[0];
                int newC = c + it[1];

                if(newR < 0 || newR >= n || newC < 0 || newC >= m) continue;

                if(grid[newR][newC] <= time+1){
                    minDis[newR][newC] = time+1;
                    pq.push({time + 1, {newR, newC}});
                }else if((grid[newR][newC] - time) % 2 == 0){ //even diff
                    minDis[newR][newC] = grid[newR][newC] + 1;
                    pq.push({grid[newR][newC] + 1, {newR, newC}});
                }else{                                         //odd diff
                    minDis[newR][newC] = grid[newR][newC];
                    pq.push({grid[newR][newC], {newR, newC}});
                }
            }
        }
        return -1;
    }
};
/*
Example 1:
Input: grid = [[0,1,3,2],[5,1,2,5],[4,3,8,6]]
Output: 7
Explanation: One of the paths that we can take is the following:
- at t = 0, we are on the cell (0,0).
- at t = 1, we move to the cell (0,1). It is possible because grid[0][1] <= 1.
- at t = 2, we move to the cell (1,1). It is possible because grid[1][1] <= 2.
- at t = 3, we move to the cell (1,2). It is possible because grid[1][2] <= 3.
- at t = 4, we move to the cell (1,1). It is possible because grid[1][1] <= 4.
- at t = 5, we move to the cell (1,2). It is possible because grid[1][2] <= 5.
- at t = 6, we move to the cell (1,3). It is possible because grid[1][3] <= 6.
- at t = 7, we move to the cell (2,3). It is possible because grid[2][3] <= 7.
The final time is 7. It can be shown that it is the minimum time possible.

Example 2:
Input: grid = [[0,2,4],[3,2,1],[1,0,4]]
Output: -1
Explanation: There is no path from the top left to the bottom-right cell.
*/


//55. MAX AREA OF ISLAND
//DFS                                                             {T.C = O(N*M), S.C = O(N*M)}
class Solution {
public:
    vector<vector<int>>directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool isValid(int i, int j, int n , int m){
        return (i >= 0 && i < n && j >= 0 && j < m);
    }
    int dfs(vector<vector<int>>&grid, vector<vector<bool>>&vis, int i, int j, int n, int m){
        vis[i][j] = true;
        int area = 1;                   //curr cell contribution
        for(auto &it : directions){
            int newR = i + it[0];
            int newC = j + it[1];

            if(isValid(newR, newC, n, m) && !vis[newR][newC] && grid[newR][newC] == 1){
                area += dfs(grid, vis, newR, newC, n, m);
            }
        }
        return area;
    }
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>>vis(n, vector<bool>(m, false));

        // int components = 0;
        int maxArea = 0;
        for(int i = 0 ; i < n; i++){
            for(int j = 0 ;j < m; j++){
                if(grid[i][j] == 1 && !vis[i][j]){
                    maxArea = max(maxArea, dfs(grid, vis, i, j, n, m));
                    // components++;
                }
            }
        }
        return maxArea;
        // return components;
    }
};
/*
Example 1:
Input: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],
               [0,0,0,0,0,0,0,1,1,1,0,0,0],
               [0,1,1,0,1,0,0,0,0,0,0,0,0],
               [0,1,0,0,1,1,0,0,1,0,1,0,0],
               [0,1,0,0,1,1,0,0,1,1,1,0,0],
               [0,0,0,0,0,0,0,0,0,0,1,0,0],
               [0,0,0,0,0,0,0,1,1,1,0,0,0],
               [0,0,0,0,0,0,0,1,1,0,0,0,0]]
Output: 6
Explanation: The answer is not 11, because the island must be connected 4-directionally.

Example 2:
Input: grid = [[0,0,0,0,0,0,0,0]]
Output: 0
*/


//56. LONGEST SUBSTRING WITHOUT REPEATING CHARACTERS                   {T.C = O(N), S.C = O(N)}
//SLIDIING WINDOW
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char,int>mp;
        int n = s.length();
        int i = 0, j = 0, maxLen = 0;
        while(j < n){
            mp[s[j]]++;

            while(mp[s[j]] > 1){
                mp[s[i]]--;                   //shrink window
                if(mp[s[i]] == 0) mp.erase(s[i]);
                i++;
            }
            maxLen = max(maxLen, j-i+1);
            j++;
        }
        return maxLen;
    }
};
/*
Example 1:
Input: s = "zxyzxyz"
Output: 3
Explanation: The string "xyz" is the longest without duplicate characters.

Example 2:
Input: s = "xxxx"
Output: 1
*/


//57. CHECK IF A WORD OCCURS AS A PREFIX OF ANY WORD IN A SENTENCE   
//STRINGSTREAM                                                    {T.C = O(N*M), S.C = O(M)}
class Solution {
public:
    int isPrefixOfWord(string sentence, string searchWord) {
        stringstream ss(sentence);
        string word;               //hold each word
        int wordIdx = 1;           //1 based indexing
        while(ss >> word){
            if(word.find(searchWord) == 0) return wordIdx;  //0 = prefix word (idx, otherwise act as bool val)
            wordIdx++;
        }
        return -1;
    }
};
/*
Example 1:
Input: sentence = "i love eating burger", searchWord = "burg"
Output: 4
Explanation: "burg" is prefix of "burger" which is the 4th word in the sentence.

Example 2:
Input: sentence = "this problem is an easy problem", searchWord = "pro"
Output: 2
Explanation: "pro" is prefix of "problem" which is the 2nd and the 6th word in the sentence, but we return 2 as it's the minimal index.

Example 3:
Input: sentence = "i am tired", searchWord = "you"
Output: -1
Explanation: "you" is not a prefix of any word in the sentence.
*/


//58. ADDING SPACES TO A STRING                           {T.C = O(N), S.C = O(N)}
class Solution {
public:
    string addSpaces(string s, vector<int>& spaces) {
        int n = s.length(), m = spaces.size();
        string ans = "";
        int i = 0, j = 0;               //i = s[0], j = spaces[0]
        while(i < n){
            while(j < m && i == spaces[j]){
                ans += ' ';
                j++;
            }
            ans += s[i];
            i++;
        }
        return ans;
    }
};
/*
Example 1:
Input: s = "LeetcodeHelpsMeLearn", spaces = [8,13,15]
Output: "Leetcode Helps Me Learn"
Explanation: 
The indices 8, 13, and 15 correspond to the underlined characters in "LeetcodeHelpsMeLearn".
We then place spaces before those characters.

Example 2:
Input: s = "icodeinpython", spaces = [1,5,7,9]
Output: "i code in py thon"
Explanation:
The indices 1, 5, 7, and 9 correspond to the underlined characters in "icodeinpython".
We then place spaces before those characters.

Example 3:
Input: s = "spacing", spaces = [0,1,2,3,4,5,6]
Output: " s p a c i n g"
Explanation:
We are also able to place spaces before the first character of the string.
*/


//59. FIND X-SUM OF ALL K-LONG SUBARRAYS I & II                     {T.C = O(N*K*LOGK), S.C = O(K)} 
//MINHEAP
class Solution {
public:
    typedef pair<int, int> P;
    vector<int> findXSum(vector<int>& nums, int k, int x) {
        int n = nums.size();
        vector<int> ans;

        for (int i = 0; i <= n-k; i++) { // Loop through all windows of size k
            unordered_map<int, int> mp;  // Map to store frequency of each element
            for (int j = i; j < i + k; j++) {
                mp[nums[j]]++;
            }

            // Define a lambda comparator for the priority queue
            auto cmp = [&](auto &a, auto &b) {
                if (a.first == b.first) return a.second < b.second; // Sort by value if freq is same
                return a.first < b.first;                          // Sort by frequency
            };

            priority_queue<P, vector<P>, decltype(cmp)> pq(cmp); // Priority queue with custom comparator

            // Push elements into the priority queue
            for (auto& it : mp) {
                pq.push({it.second, it.first}); // Push (frequency, value)
            }

            // Extract the top x elements from the priority queue
            int sum = 0, taken = 0;
            while (!pq.empty() && taken < x) {
                auto [freq, val] = pq.top();
                pq.pop();
                sum += freq * val;
                taken++;
            }
            ans.push_back(sum);
        }
        return ans;
    }
};
/*
Example 1:
Input: nums = [1,1,2,2,3,4,2,3], k = 6, x = 2
Output: [6,10,12]
Explanation:
For subarray [1, 1, 2, 2, 3, 4], only elements 1 and 2 will be kept in the resulting array. Hence, answer[0] = 1 + 1 + 2 + 2.
For subarray [1, 2, 2, 3, 4, 2], only elements 2 and 4 will be kept in the resulting array. Hence, answer[1] = 2 + 2 + 2 + 4. Note that 4 is kept in the array since it is bigger than 3 and 1 which occur the same number of times.
For subarray [2, 2, 3, 4, 2, 3], only elements 2 and 3 are kept in the resulting array. Hence, answer[2] = 2 + 2 + 2 + 3 + 3.

Example 2:
Input: nums = [3,8,7,8,7,5], k = 2, x = 2
Output: [11,15,15,15,12]
Explanation:
Since k == x, answer[i] is equal to the sum of the subarray nums[i..i + k - 1].
*/


//60. ARITHMETIC SLICES                                     {T.C = O(N), S.C = O(1)}
//WITHOUT SLIDING WINDOW
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n = nums.size();
        //base case
        if(n < 3) return 0;

        int countSameDiff = 0;
        int allSlices = 0;
        for(int i = 0 ; i < n-2; i++){
            if(nums[i]-nums[i+1] == nums[i+1] - nums[i+2]){
                countSameDiff++;
                allSlices += countSameDiff;
            }else countSameDiff = 0;
        }
        return allSlices;
    }
};
/*
Example 1:
Input: nums = [1,2,3,4]
Output: 3
Explanation: We have 3 arithmetic slices in nums: [1, 2, 3], [2, 3, 4] and [1,2,3,4] itself.

Example 2:
Input: nums = [1]
Output: 0
*/


//61. MOVE PIECES TO OBTAIN A STRING                                  {T.C = O(N), S.C = O(1)}
//TWO POINTERS
class Solution {
public:
    bool canChange(string start, string target) {
        int n = start.size(); 
        int i = 0, j = 0;                    //pointers for start and target strings
        
        while (i < n || j < n) {             // traverse both strings
            // Skip '_' in both strings
            while (i < n && start[i] == '_') i++;
            while (j < n && target[j] == '_') j++;
            
            // Check if one pointer reaches the end while the other doesn't
            if ((i < n) != (j < n)) return false;

            // If both pointers are valid, compare characters
            if (i < n && j < n) {
                if (start[i] != target[j]) return false;

                // Check movement rules
                if (start[i] == 'L' && i < j) return false; // 'L' can only move left
                if (start[i] == 'R' && i > j) return false; // 'R' can only move right
            }

            i++, j++;
        }

        return true;
    }
};
/*
Example 1:
Input: start = "_L__R__R_", target = "L______RR"
Output: true
Explanation: We can obtain the string target from start by doing the following moves:
- Move the first piece one step to the left, start becomes equal to "L___R__R_".
- Move the last piece one step to the right, start becomes equal to "L___R___R".
- Move the second piece three steps to the right, start becomes equal to "L______RR".
Since it is possible to get the string target from start, we return true.

Example 2:
Input: start = "R_L_", target = "__LR"
Output: false
Explanation: The 'R' piece in the string start can move one step to the right to obtain "_RL_".
After that, no pieces can move anymore, so it is impossible to obtain the string target from start.

Example 3:
Input: start = "_R", target = "R_"
Output: false
Explanation: The piece in the string start can move only to the right, so it is impossible to obtain the string target from start.
*/


//62. TAKE GIFT FROM RICHES PILE                                       {T.C = O(K*N), S.C = O(1)}
class Solution {
public:
    long long pickGifts(vector<int>& gifts, int k) {
        while(k--){
            auto maxVal = max_element(gifts.begin(), gifts.end());     //auto == iterator, * = val
            *maxVal = floor(sqrt(*maxVal));
        }
        long long sum = 0;
        for(auto it : gifts) sum += it;

        return sum;
    }
};
/*
Example 1:
Input: gifts = [25,64,9,4,100], k = 4
Output: 29
Explanation: 
The gifts are taken in the following way:
- In the first second, the last pile is chosen and 10 gifts are left behind.
- Then the second pile is chosen and 8 gifts are left behind.
- After that the first pile is chosen and 5 gifts are left behind.
- Finally, the last pile is chosen again and 3 gifts are left behind.
The final remaining gifts are [5,8,9,4,3], so the total number of gifts remaining is 29.

Example 2:
Input: gifts = [1,1,1,1], k = 4
Output: 4
Explanation: 
In this case, regardless which pile you choose, you have to leave behind 1 gift in each pile. 
That is, you can't take any pile with you. 
So, the total gifts remaining are 4.
*/


//63. FIND SCORE OF AN ARRAY AFTER MARKING ALL ELEMENTS            {T.C = O(NLOGN), S.C = O(N)}
class Solution {
public:
    typedef pair<int,int>P;                                 //val, index
    long long findScore(vector<int>& nums) {
        int n = nums.size();
        vector<bool>vis(n, false);
        priority_queue<P, vector<P>, greater<P>>minHeap;

        for(int i = 0; i < n; i++){
            minHeap.push({nums[i], i});
        }

        long long score = 0;
        while(!minHeap.empty()){
            auto topNode = minHeap.top();
            minHeap.pop();
            int ele = topNode.first;
            int idx = topNode.second;

            if(!vis[idx]){
                vis[idx] = true;                   //left, curr, right(mark vis)
                score += ele;
                
                if(idx-1 >= 0 && !vis[idx-1]) vis[idx-1] = true;
                if(idx+1 < n && !vis[idx+1]) vis[idx+1] = true;
            }
        }
        return score;
    }
};
/*
Example 1:
Input: nums = [2,1,3,4,5,2]
Output: 7
Explanation: We mark the elements as follows:
- 1 is the smallest unmarked element, so we mark it and its two adjacent elements: [2,1,3,4,5,2].
- 2 is the smallest unmarked element, so we mark it and its left adjacent element: [2,1,3,4,5,2].
- 4 is the only remaining unmarked element, so we mark it: [2,1,3,4,5,2].
Our score is 1 + 2 + 4 = 7.

Example 2:
Input: nums = [2,3,5,1,3,2]
Output: 5
Explanation: We mark the elements as follows:
- 1 is the smallest unmarked element, so we mark it and its two adjacent elements: [2,3,5,1,3,2].
- 2 is the smallest unmarked element, since there are two of them, we choose the left-most one, so we mark the one at index 0 and its right adjacent element: [2,3,5,1,3,2].
- 2 is the only remaining unmarked element, so we mark it: [2,3,5,1,3,2].
Our score is 1 + 2 + 2 = 5.
*/


//64. CONTINUOUS ARRAY                                 
//BRUTE FORCE                                              {T.C = O(N^2), S.C = O(1)}
class Solution {
public:
    long long continuousSubarrays(vector<int>& nums) {
        long long count = 0;
        int i = 0, j = 0;
        int n = nums.size();
        
        int minVal = nums[0], maxVal = nums[0];
        while(j < n){
            minVal = min(minVal, nums[j]);
            maxVal = max(maxVal, nums[j]);

            while(maxVal - minVal > 2){          //shrink window (invalid window)
                i++;
                minVal = nums[i], maxVal = nums[i];  //recalculate min, max for each subarray
                for(int k = i; k <= j ; k++){
                    minVal = min(minVal, nums[k]);
                    maxVal = max(maxVal, nums[k]);
                }
            }
            count += j-i+1;
            j++;
        }
        return count;
    }
};

//USING DEQUE                                              {T.C = O(N), S.C = O(N)}
class Solution {
public:
    long long continuousSubarrays(vector<int>& nums) {
        int n = nums.size();
        long long count = 0;
        int i = 0, j = 0;
        deque<int>minDq, maxDq;           //store ele idx in incr order & decr order respectively
        while(j < n){
            while(!minDq.empty() && nums[minDq.back()] >= nums[j]) minDq.pop_back(); //store in incr order
            while(!maxDq.empty() && nums[maxDq.back()] <= nums[j]) maxDq.pop_back(); //store in decr order
            
            minDq.push_back(j);
            maxDq.push_back(j);

            while(nums[maxDq.front()] - nums[minDq.front()] > 2){  //invalid, shrink window
                i++;
                if(minDq.front() < i) minDq.pop_front();
                if(maxDq.front() < i) maxDq.pop_front();
            }
            count += j-i+1;
            j++;
        }
        return count;
    }
};
/*
Example 1:
Input: nums = [5,4,2,4]
Output: 8
Explanation: 
Continuous subarray of size 1: [5], [4], [2], [4].
Continuous subarray of size 2: [5,4], [4,2], [2,4].
Continuous subarray of size 3: [4,2,4].
Thereare no subarrys of size 4.
Total continuous subarrays = 4 + 3 + 1 = 8.
It can be shown that there are no more continuous subarrays.
 
Example 2:
Input: nums = [1,2,3]
Output: 6
Explanation: 
Continuous subarray of size 1: [1], [2], [3].
Continuous subarray of size 2: [1,2], [2,3].
Continuous subarray of size 3: [1,2,3].
Total continuous subarrays = 3 + 2 + 1 = 6.
*/


//65. EXCEL SHEET COLUMN TITLE                                  {T.C = O(LOG26(N)), S.C = O(N)}
class Solution {
public:
    string convertToTitle(int columnNumber) {
        string ans = "";
        while(columnNumber > 0){
            columnNumber--;                               //make 1 to 0 index
            int remainder = columnNumber % 26;
            ans += remainder + 'A';
            // ans += remainder + 'A' - 1;                   //0 != A, 1 == A (-1)
            columnNumber /= 26;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
/*
Example 1:
Input: columnNumber = 1
Output: "A"

Example 2:
Input: columnNumber = 28
Output: "AB"

Example 3:
Input: columnNumber = 701
Output: "ZY"
*/


//66. EXCEL SHEET COLUMN NUMBER                         {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int titleToNumber(string columnTitle) {
        int ans = 0;
        for(auto ch : columnTitle){
            int digit = ch - 'A' + 1;
            ans = ans*26 + digit;
        }
        return ans;
    }
};
/*
Example 1:
Input: columnTitle = "A"
Output: 1

Example 2:
Input: columnTitle = "AB"
Output: 28

Example 3:
Input: columnTitle = "ZY"
Output: 701
*/


//67. FIND ARRAY STATE AFTER K MULTIPLICATION OPERATION I    {T.C = O(N*K), S.C = O(1)}
class Solution {
public:
    vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
        while(k--){
            auto minItr = min_element(nums.begin(), nums.end());     //find minIdx
            *minItr *= multiplier;
        }
        return nums;
    }
};
/*
Example 1:
Input: nums = [2,1,3,5,6], k = 5, multiplier = 2
Output: [8,4,6,5,6]
Explanation:
Operation	Result
After operation 1	[2, 2, 3, 5, 6]
After operation 2	[4, 2, 3, 5, 6]
After operation 3	[4, 4, 3, 5, 6]
After operation 4	[4, 4, 6, 5, 6]
After operation 5	[8, 4, 6, 5, 6]

Example 2:
Input: nums = [1,2], k = 3, multiplier = 4
Output: [16,8]
Explanation:
Operation	Result
After operation 1	[4, 2]
After operation 2	[4, 8]
After operation 3	[16, 8]
*/


//68. MINIMUM NUMBER OF OPERATIONS TO SORT A BINARY TREE BY LEVEL   
//BFS + SORTING + MAP                                         {T.C = O(N*LOGN), S.C = O(N)}
class Solution {
public:
    void lvlOrder(TreeNode* root, vector<vector<int>>&ans){
        //base case
        if(!root) return;

        queue<TreeNode*>q;
        q.push(root);
        while(!q.empty()){
            int sz = q.size();
            vector<int>temp;
            while(sz--){
                auto frontNode = q.front();
                q.pop();
                temp.push_back(frontNode->val);
                if(frontNode->left) q.push(frontNode->left);
                if(frontNode->right)q.push(frontNode->right);
            }
            ans.push_back(temp);
        }
    }
    int countSwaps(vector<int>&arr){
        vector<int>copy = arr;
        sort(copy.begin(), copy.end());

        map<int,int>mp;
        for(int i = 0; i < copy.size(); i++){               //map of copy to index
            mp[copy[i]] = i;
        }
        int swaps = 0;
        for(int i = 0 ; i < arr.size();){
            int idx = mp[arr[i]];
            if(idx == i) i++;                             //already correct position , no swap
            else{
                swap(arr[i], arr[idx]);
                swaps++;
            }
        }
        return swaps;
    }
    int minimumOperations(TreeNode* root) {
        vector<vector<int>>ans;
        lvlOrder(root, ans);

        int swaps = 0;
        for(auto &it : ans){                       //traverse each vector
            swaps += countSwaps(it);
        }
        return swaps;
    }
};
/*
Example 1:
Input: root = [1,4,3,7,6,8,5,null,null,null,null,9,null,10]
Output: 3
Explanation:
- Swap 4 and 3. The 2nd level becomes [3,4].
- Swap 7 and 5. The 3rd level becomes [5,6,8,7].
- Swap 8 and 7. The 3rd level becomes [5,6,7,8].
We used 3 operations so return 3.
It can be proven that 3 is the minimum number of operations needed.

Example 2:
Input: root = [1,3,2,7,6,5,4]
Output: 3
Explanation:
- Swap 3 and 2. The 2nd level becomes [2,3].
- Swap 7 and 4. The 3rd level becomes [4,6,5,7].
- Swap 6 and 5. The 3rd level becomes [4,5,6,7].
We used 3 operations so return 3.
It can be proven that 3 is the minimum number of operations needed.

Example 3:
Input: root = [1,2,3,4,5,6]
Output: 0
Explanation: Each level is already sorted in increasing order so return 0.
*/


/*-------------------------------------------------------------------------------------------------------------------*/
//MOST ASKED QUESTIONS

//69. RATE IN A MAZE I                                              {T.C = O(4^N^2 OR EXP), S.C = O(N^2)}
//BACKTRACKING
class Solution {
  public:
    void dfs(vector<vector<int>>&mat, vector<vector<bool>>&vis, vector<string>&ans, string s, int i, int j){ //s pass by val not refrence
        int n = mat.size();
        //base cases
        if(i < 0 || i >= n || j < 0 || j >= n) return;      //invalid case
        if(mat[i][j] == 0 || vis[i][j] == true) return;
        if(i == n-1 && j == n-1){
            ans.push_back(s);
            return;
        } 
            
        vis[i][j] = true;
        dfs(mat, vis, ans, s+'U', i-1, j);
        dfs(mat, vis, ans, s+'D', i+1, j);
        dfs(mat, vis, ans, s+'L', i, j-1);
        dfs(mat, vis, ans, s+'R', i, j+1);
        
        vis[i][j] = false;                              //backtrack
    }
    vector<string> findPath(vector<vector<int>> &mat) {
        int n = mat.size();               //n=m
        vector<string>ans;
        string s = "";
        vector<vector<bool>>vis(n, vector<bool>(n, false));
        dfs(mat, vis, ans, s, 0, 0);                    //0 = i, 0 = j
        
        sort(ans.begin(), ans.end());
        return ans;
    }
};
/*
Input: mat[][] = [[1, 0, 0, 0], 
                  [1, 1, 0, 1], 
                  [1, 1, 0, 0], 
                  [0, 1, 1, 1]]
Output: ["DDRDRR", "DRDDRR"]
Explanation: The rat can reach the destination at (3, 3) from (0, 0) by two paths - DRDDRR and DDRDRR, when printed in sorted order we get DDRDRR DRDDRR.

Input: mat[][] = [[1, 0], 
                  [1, 0]]
Output: []
Explanation: No path exists and the destination cell is blocked.

Input: mat = [[1, 1, 1], 
              [1, 0, 1], 
              [1, 1, 1]]
Output: ["DDRR", "RRDD"]
Explanation: The rat has two possible paths to reach the destination: 1. "DDRR" 2. "RRDD", These are returned in lexicographically sorted order.
*/


//70. NUMBER OF PROVINCES                                       {T.C = O(N^2), S.C = O(N^2)}
//DFS ON MATRIX
class Solution {
public:
    void dfs(unordered_map<int,vector<int>>&adj, vector<bool>&vis, int node){
        vis[node] = true;
        for(auto it : adj[node]){
            if(!vis[it]) dfs(adj, vis, it);
        }
    }
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        unordered_map<int,vector<int>>adj;
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                if(isConnected[i][j] == 1){
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }

        int components = 0;
        vector<bool>vis(n, false);
        for(int i = 0 ;  i < n ; i++){
            if(!vis[i]){
                dfs(adj, vis, i);
                components++;
            }
        }
        return components;
    }
};
/*
Example 1:
Input: isConnected = [[1,1,0],
                      [1,1,0],
                      [0,0,1]]
Output: 2

Example 2:
Input: isConnected = [[1,0,0],
                      [0,1,0],
                      [0,0,1]]
Output: 3
*/


//71. NETWORK DELAY TIME  
//DIJKSTRA                                                   {T.C = O((V+E)*LOGV), S.C = O(V+E)}
class Solution {
public:
    typedef pair<int,int>P;
    int dijkstra(unordered_map<int,vector<P>>&adj, int n, int src){
        priority_queue<P, vector<P>, greater<P>>pq;
        vector<int>minDis(n+1, INT_MAX);                     //1 based indexing

        pq.push({0, src});
        minDis[src] = 0;
        while(!pq.empty()){
            auto topNode = pq.top();
            pq.pop();
            int dis = topNode.first;
            int u   = topNode.second;
            for(auto it : adj[u]){
                int v = it.first;
                int d = it.second;
                if(dis + d < minDis[v]){
                    minDis[v] = dis + d;
                    pq.push({minDis[v], v});
                }
            }
        }

        int ans = 0;
        for(int i = 1; i <= n ; i++){
            if(minDis[i] == INT_MAX) return -1;
            ans = max(minDis[i], ans);                  //min time to all reach is max of all
        }
        return ans;
    }
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        unordered_map<int, vector<P>>adj;
        for(auto it : times){
            adj[it[0]].push_back({it[1], it[2]});
        }
        return dijkstra(adj, n, k);                     //k = source node
    }
};
/*
Example 1:
Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
Output: 2

Example 2:
Input: times = [[1,2,1]], n = 2, k = 1
Output: 1

Example 3:
Input: times = [[1,2,1]], n = 2, k = 2
Output: -1
*/


//72. IS GRAPH BIPARTITE 
//BFS                                                           {T.C = O(V+E), S.C = O(V+E)}
class Solution {
public:
    bool bfsBi(vector<vector<int>>&adj, vector<int>&vis, int node, int currClr){
        vis[node] = currClr;
        queue<int>q;
        q.push(node);
        
        while(!q.empty()){
            int frontNode = q.front();
            q.pop();
            for(auto it : adj[frontNode]){
                if(vis[it] == -1){
                    vis[it] = 1-vis[frontNode];
                    q.push(it);
                }else if(vis[it] == vis[frontNode]) return false; //adj clr same
            }
        }
        return true;
    }
    bool isBipartite(vector<vector<int>>& graph) {        //graph => adj
        int n = graph.size();
        vector<int>vis(n, -1);                 //1 for red , 0 = blue (2 color)
        for(int i = 0 ; i < n ; i++){
            if(vis[i] == -1){
                if(!bfsBi(graph, vis, i, 1)){            //1 = currClr (like prevIdx -1)
                    return false;
                }
            }
        }
        return true;
    }
};
/*
Example 1:
Input: graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
Output: false
Explanation: There is no way to partition the nodes into two independent sets such that every edge connects a node in one and a node in the other.

Example 2:
Input: graph = [[1,3],[0,2],[1,3],[0,2]]
Output: true
Explanation: We can partition the nodes into two sets: {0, 2} and {1, 3}.
*/


//73. FIND EVANTUALL SAFE NODES  
//DFS (CYCLE)                                               {T.C = O(V+E), S.C = O(V+E)}
class Solution {
public:
    bool isCyclicDfs(vector<vector<int>>&adj, vector<int>&vis, vector<int>&dfsVis, int node){
        vis[node] = 1;
        dfsVis[node] = 1;
        for(auto it : adj[node]){
            if(!vis[it]){
                if(isCyclicDfs(adj, vis, dfsVis, it)){
                    return true;
                }
            }else if(dfsVis[it]){                 //vis but  not parent (cycle)
                return true;
            }
        }
        dfsVis[node] = false;
        return false;
    }
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {  //graph => adj
        int n = graph.size();
        vector<int>ans;
        vector<int>vis(n, 0);
        vector<int>dfsVis(n, 0);
        for(int i = 0 ; i < n ; i++){
            if(!vis[i]){
                isCyclicDfs(graph, vis, dfsVis, i);           
            }
        }
        
        for(int i = 0 ; i < n ; i++){        //safe node pushed in ans
            if(dfsVis[i] == 0){
                ans.push_back(i);
            }
        }
        return ans;
    }
};
/*
Example 1:
Illustration of graph
Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
Output: [2,4,5,6]
Explanation: The given graph is shown above.
Nodes 5 and 6 are terminal nodes as there are no outgoing edges from either of them.
Every path starting at nodes 2, 4, 5, and 6 all lead to either node 5 or 6.

Example 2:
Input: graph = [[1,2,3,4],[1,2],[3,4],[0,4],[]]
Output: [4]
Explanation:
Only node 4 is a terminal node, and every path starting at node 4 leads to node 4.
*/


//74. MOST STONES REMOVED WITH SAME ROW OR COLUMN
//UNION - SET                                                 {T.C = O(N^2), S.C = O(N)}
class Solution {
public:
    vector<int> parent, rank;

    int find(int i) {
        if (i == parent[i]) return i;
        return parent[i] = find(parent[i]);
    }

    void Union(int x, int y) {
        int xParent = find(x);
        int yParent = find(y);

        if (xParent == yParent) return; // belong to same component

        if (rank[xParent] > rank[yParent]) parent[yParent] = xParent;
        else if (rank[xParent] < rank[yParent]) parent[xParent] = yParent;
        else {
            parent[xParent] = yParent;
            rank[yParent]++;
        }
    }

    bool isValid(vector<int>& pos1, vector<int>& pos2) {
        return pos1[0] == pos2[0] || pos1[1] == pos2[1];         //same row or col (consider same components)
    }

    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        rank.resize(n, 0);
        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i; // self parent

        int groups = n;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) { // start j from i + 1 to avoid self comparison
                if (isValid(stones[i], stones[j])) {
                    int xParent = find(i);
                    int yParent = find(j);
                    if (xParent != yParent) {
                        Union(i, j);
                        groups--; // decrement group count on successful union
                    }
                }
            }
        }

        return n - groups;                       //STONES removed (total - groups(1 left after all kill))
    }
};
/*
Example 1:
Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
Output: 5
Explanation: One way to remove 5 stones is as follows:
1. Remove stone [2,2] because it shares the same row as [2,1].
2. Remove stone [2,1] because it shares the same column as [0,1].
3. Remove stone [1,2] because it shares the same row as [1,0].
4. Remove stone [1,0] because it shares the same column as [0,0].
5. Remove stone [0,1] because it shares the same row as [0,0].
Stone [0,0] cannot be removed since it does not share a row/column with another stone still on the plane.

Example 2:
Input: stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
Output: 3
Explanation: One way to make 3 moves is as follows:
1. Remove stone [2,2] because it shares the same row as [2,0].
2. Remove stone [2,0] because it shares the same column as [0,0].
3. Remove stone [0,2] because it shares the same row as [0,0].
Stones [0,0] and [1,1] cannot be removed since they do not share a row/column with another stone still on the plane.
*/


//75. PATH WITH MAXIMUM PROBABILITY            
//DIJKSTRA                                                       {T.C = O(E*LOGV), S.C = O(V+E)}
class Solution {
public:
    typedef pair<double, int>P;
    double dijkstra(int n, unordered_map<int, vector<pair<int, double>>>&adj, int src, int dst){
        vector<double>maxProb(n, 0.0);
        priority_queue<P>pq;

        pq.push({1.0, src});
        while(!pq.empty()){
            auto topNode = pq.top();
            pq.pop();
            double pr = topNode.first;
            int u = topNode.second;
            for(auto [v, p] : adj[u]){
                if(pr*p > maxProb[v]){
                    maxProb[v] = pr*p;
                    pq.push({maxProb[v], v});
                }
            }
        }
        return maxProb[dst];
    }
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
        unordered_map<int,vector<pair<int, double>>>adj;           //u->{v, p}  , p = probability
        for(int i = 0 ; i < edges.size(); i++){
            int u = edges[i][0];
            int v = edges[i][1];
            double p = succProb[i];

            adj[u].push_back({v, p});
            adj[v].push_back({u, p});
        }
        return dijkstra(n, adj, start_node, end_node);
    }
};
/*
Example 1:
Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.2], start = 0, end = 2
Output: 0.25000
Explanation: There are two paths from start to end, one having a probability of success = 0.2 and the other has 0.5 * 0.5 = 0.25.

Example 2:
Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.3], start = 0, end = 2
Output: 0.30000

Example 3:
Input: n = 3, edges = [[0,1]], succProb = [0.5], start = 0, end = 2
Output: 0.00000
Explanation: There is no path between 0 and 2.
*/


//76. FIND A SAFE WALK THROUGH A GRID                           
//BFS ON MATRIX                                                 {T.C = O(N^2), S.C = O(N^2)}
class Solution {
public:
    typedef pair<int, pair<int,int>>P;
    vector<vector<int>>directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool isValid(int i, int j, int n, int m){
        return (i >= 0 && i < n && j >= 0 && j < m);
    }
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int n = grid.size(), m = grid[0].size();

        queue<P>q;
        q.push({health - grid[0][0], {0, 0}});                            //remaining health, row , col

        vector<vector<int>>maxHel(n, vector<int>(m, 0));
        maxHel[0][0] = health - grid[0][0];

        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            int h = frontNode.first;
            int r = frontNode.second.first;
            int c = frontNode.second.second;

            if(r == n-1 && c == m-1 && h > 0) return true;

            for(auto it : directions){
                int newR = r + it[0];
                int newC = c + it[1];

                if(isValid(newR, newC, n, m)){
                    int newHealth = h - grid[newR][newC];

                    if(newHealth > 0 && newHealth > maxHel[newR][newC]){
                        maxHel[newR][newC] = newHealth;
                        q.push({newHealth, {newR, newC}});
                    }
                }
            }
        }
        return false;  
    }
};
/*
Example 1:

Input: grid = [[0,1,0,0,0],
               [0,1,0,1,0],
               [0,0,0,1,0]], health = 1
Output: true
Explanation:
The final cell can be reached safely by walking along the gray cells below.


Example 2:
Input: grid = [[0,1,1,0,0,0],
               [1,0,1,0,0,0],
               [0,1,1,1,0,1],
               [0,0,1,0,1,0]], health = 3
Output: false
Explanation:
A minimum of 4 health points is needed to reach the final cell safely.

Example 3:
Input: grid = [[1,1,1],
               [1,0,1],
               [1,1,1]], health = 5
Output: true
Explanation:
The final cell can be reached safely by walking along the gray cells below.
Any path that does not go through the cell (1, 1) is unsafe since your health will drop to 0 when reaching the final cell.
*/


//77. FIND MINIMUM TIME TO REACH LAST ROOM I                         
//DIJKSTRA ON MATRIX                                             {T.C = O(N^2), S.C = O(N^2)}
class Solution {
public:
    typedef pair<int, pair<int, int>> P;                  // time, {row, col}
    vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    
    bool isValid(int i, int j, int n, int m) {
        return (i >= 0 && i < n && j >= 0 && j < m);
    }
    
    int minTimeToReach(vector<vector<int>>& moveTime) {
        int n = moveTime.size(), m = moveTime[0].size();
        priority_queue<P, vector<P>, greater<P>> pq;
        pq.push({0, {0, 0}});                          // initial time = 0, start from (0, 0)

        vector<vector<int>> minDis(n, vector<int>(m, INT_MAX));
        minDis[0][0] = 0;                              // time to reach start is 0

        while (!pq.empty()) {
            auto topNode = pq.top();
            pq.pop();
            int t = topNode.first;
            int r = topNode.second.first;
            int c = topNode.second.second;

            // if (r == n - 1 && c == m - 1){              // reached destination
            //     return t;
            // }

            for (auto it : directions) {
                int newR = r + it[0];
                int newC = c + it[1];

                if (isValid(newR, newC, n, m)) {
                    int newTime = 1 + max(t, moveTime[newR][newC]);      //1(path) + max(curr, next)
                    
                    if (newTime < minDis[newR][newC]) {
                        minDis[newR][newC] = newTime;
                        pq.push({newTime, {newR, newC}});
                    }
                }
            }
        }
        
        if(minDis[n-1][n-1] == INT_MAX) return -1;
        return minDis[n-1][m-1];
        // return -1; // If destination is unreachable
    }
};

/*
Example 1:
Input: moveTime = [[0,4],
                   [4,4]]
Output: 6
Explanation:
The minimum time required is 6 seconds.
At time t == 4, move from room (0, 0) to room (1, 0) in one second.
At time t == 5, move from room (1, 0) to room (1, 1) in one second.

Example 2:
Input: moveTime = [[0,0,0],
                   [0,0,0]]
Output: 3
Explanation:
The minimum time required is 3 seconds.
At time t == 0, move from room (0, 0) to room (1, 0) in one second.
At time t == 1, move from room (1, 0) to room (1, 1) in one second.
At time t == 2, move from room (1, 1) to room (1, 2) in one second.

Example 3:
Input: moveTime = [[0,1],
                   [1,2]]
Output: 3
*/


//78. MINIMUM OBSTACLE REMOVAL TO REACH CORNER            
//DIJKSTRA ON MATRIX                                          {T.C = O(N*M), S.C = O(N*M)}
class Solution {
public:
    typedef pair<int, pair<int, int>> P; // {distance, {row, col}}
    vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    
    int minimumObstacles(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();

        priority_queue<P, vector<P>, greater<P>> pq; // Min-heap based on distance
        pq.push({0, {0, 0}}); // Start with distance 0 at (0, 0)

        vector<vector<int>> minDis(n, vector<int>(m, INT_MAX)); // To track minimum obstacles
        minDis[0][0] = 0;

        while (!pq.empty()) {
            auto topNode = pq.top();
            pq.pop();
            int dis = topNode.first;
            int r = topNode.second.first;
            int c = topNode.second.second;
            for (auto& dir : directions) {
                int newR = r + dir[0];
                int newC = c + dir[1];

                // Boundary check
                if (newR < 0 || newR >= n || newC < 0 || newC >= m) continue;

                int newDis = dis + grid[newR][newC]; // Add obstacle weight (1 if obstacle, 0 otherwise)

                // Relaxation step: Update the distance if the new distance is smaller
                if (newDis < minDis[newR][newC]) {
                    minDis[newR][newC] = newDis;
                    pq.push({newDis, {newR, newC}});
                }
            }
        }

        if(minDis[n-1][m-1] == INT_MAX) return -1;
        return minDis[n-1][m-1];
    }
};
/*
Example 1:
Input: grid = [[0,1,1],
               [1,1,0],
               [1,1,0]]
Output: 2
Explanation: We can remove the obstacles at (0, 1) and (0, 2) to create a path from (0, 0) to (2, 2).
It can be shown that we need to remove at least 2 obstacles, so we return 2.
Note that there may be other ways to remove 2 obstacles to create a path.

Example 2:
Input: grid = [[0,1,0,0,0],
               [0,1,0,1,0],
               [0,0,0,1,0]]
Output: 0
Explanation: We can move from (0, 0) to (2, 4) without removing any obstacles, so we return 0.
*/


//79. VALID PARENTHESIS WITH HASH CHARACTERS      
//STACK                                                     {T.C = O(N), S.C = O(N)}
#include<bits/stdc++.h>
using namespace std;

bool isValidParenthesisWithHash(string& s) {
    stack<char> stk;
    for(int i = 0; i < s.length(); i++){
        if(s[i] == '('){
            stk.push(s[i]);
        }else if(s[i] == ')'){
            if(!stk.empty() && stk.top() == '(') stk.pop();
        }else if(s[i] == '#') continue;
    }
    return stk.empty();
}

int main(){
    string s;
    cin>>s;
    bool ans = isValidParenthesisWithHash(s);
    cout<<ans;
    
    return 0;
}
/*
input  : (##)
output : 1

input  : )(
output : 0
*/


//80. IS SUBSEQUENCE      
//TWO POINTERS                                                {T.C = O(N), S.C = O(1)}
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int i = 0 , j = 0;
        int n = s.size(), m = t.size();
        while(j < m){
            if(s[i] == t[j]) i++, j++;
            else j++;
        }
        return i == n;                            //string 1 completed
    }
};
/*
Example 1:
Input: s = "abc", t = "ahbgdc"
Output: true

Example 2:
Input: s = "axc", t = "ahbgdc"
Output: false
*/



//81. NUMBER OF 1 BITS  
//APPROACH 1                                                            {T.C = O(N), S.C = O(1)}
/* 
check while(n != 0) if(n & 1) == 1 count++ and right shift(n = n >> 1), finally return count,
*/
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count= 0;
        while(n != 0){
            if(n & 1){                       //1.1 = 1 and 1.0 = 0
                count++;
            }
            n = n>>1;                        //right shift or moving to next position
        }
        return count;
    }
};

//APRROACH 2                                                      {T.C = O(LOGN), S.C = O(1)}
/*
Simply (decimal to binary logic) count += n % 2 and n = n/2, finally return count.
*/
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count= 0;
        while(n != 0){
            count += n % 2;
            n /= 2;
        }
        return count;
    }
};
/*
Example 1:
Input: n = 00000000000000000000000000001011
Output: 3
Explanation: The input binary string 00000000000000000000000000001011 has a total of three '1' bits.

Example 2:
Input: n = 00000000000000000000000010000000
Output: 1
Explanation: The input binary string 00000000000000000000000010000000 has a total of one '1' bit.

Example 3:
Input: n = 11111111111111111111111111111101
Output: 31
Explanation: The input binary string 11111111111111111111111111111101 has a total of thirty one '1' bits.
*/


//82. MINIMUM COST FOR TICKETS
//USING MEMOIZATION                                              {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int dp[370];
    int solve(vector<int>&days, vector<int>&costs, int i){
        int n = days.size();
        //base case
        if(i >= n) return 0;             //out of bound

        if(dp[i] != -1) return dp[i];

        int dayPass1 = costs[0] + solve(days, costs, i+1);  //1 day pass
        
        int j = i;
        int lastDay = days[i] + 7;
        while(j < n && days[j] < lastDay) j++;
        int dayPass7 = costs[1] + solve(days, costs, j);    //7 days pass

        j = i;
        lastDay = days[i] + 30;
        while(j < n && days[j] < lastDay) j++;
        int dayPass30 = costs[2] + solve(days, costs, j);

        return dp[i] = min({dayPass1, dayPass7, dayPass30});
    }
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        memset(dp, -1, sizeof(dp));
        return solve(days, costs, 0);          //0 = initial idx
    }
};
/*
Example 1:
Input: days = [1,4,6,7,8,20], costs = [2,7,15]
Output: 11
Explanation: For example, here is one way to buy passes that lets you travel your travel plan:
On day 1, you bought a 1-day pass for costs[0] = $2, which covered day 1.
On day 3, you bought a 7-day pass for costs[1] = $7, which covered days 3, 4, ..., 9.
On day 20, you bought a 1-day pass for costs[0] = $2, which covered day 20.
In total, you spent $11 and covered all the days of your travel.

Example 2:
Input: days = [1,2,3,4,5,6,7,8,9,10,30,31], costs = [2,7,15]
Output: 17
Explanation: For example, here is one way to buy passes that lets you travel your travel plan:
On day 1, you bought a 30-day pass for costs[2] = $15 which covered days 1, 2, ..., 30.
On day 31, you bought a 1-day pass for costs[0] = $2 which covered day 31.
In total, you spent $17 and covered all the days of your travel.
*/


//83. MAXIMUM SCORE AFTER SPLITTING A STRING
//BRUTE FORCE                                                             {T.C = O(N^2), S.C = O(N^2)}
class Solution {
public:
    int maxScore(string s) {
        int n = s.length();
        int maxi = INT_MIN;

        for(int i = 0 ; i < n-1; i++){        //i = splits (last split before last ele)
            int leftZeroCount = 0;
            for(int j = 0; j <= i ; j++){
                if(s[j] == '0') leftZeroCount++;
            }

            int rightOneCount = 0;
            for(int j = i+1; j < n; j++){
                if(s[j] == '1') rightOneCount++;
            }

            maxi = max(maxi, leftZeroCount + rightOneCount);
        }
        return maxi;
    }
};
/*
Example 1:
Input: s = "011101"
Output: 5 
Explanation: 
All possible ways of splitting s into two non-empty substrings are:
left = "0" and right = "11101", score = 1 + 4 = 5 
left = "01" and right = "1101", score = 1 + 3 = 4 
left = "011" and right = "101", score = 1 + 2 = 3 
left = "0111" and right = "01", score = 1 + 1 = 2 
left = "01110" and right = "1", score = 2 + 1 = 3

Example 2:
Input: s = "00111"
Output: 5
Explanation: When left = "00" and right = "111", we get the maximum score = 2 + 3 = 5

Example 3:
Input: s = "1111"
Output: 3
*/


//RANGE QUERIES QUESTIONS
//84. COUNT VOWEL STRINGS IN A RANGES                              {T.C = O(N), S.C = O(N)}
class Solution {
public:
    vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries) {
        unordered_set<char>st = {'a', 'e', 'i', 'o', 'u'};
        int n = words.size();
        vector<int>prefixArr(n+1, 0);                  //n+1 for handle last val
        for(int i = 0; i < n; i++){
            if(st.count(words[i].front()) && st.count(words[i].back())){
                prefixArr[i+1] = prefixArr[i] + 1;
            }
            else prefixArr[i+1] = prefixArr[i];
        }
        vector<int>ans;
        for(auto &it : queries){
            int l = it[0], r = it[1];
            ans.push_back(prefixArr[r+1] - prefixArr[l]);  //r+1 -> 1 extra index added
        }
        return ans;
    }
};
/*
Example 1:
Input: words = ["aba","bcb","ece","aa","e"], queries = [[0,2],[1,4],[1,1]]
Output: [2,3,0]
Explanation: The strings starting and ending with a vowel are "aba", "ece", "aa" and "e".
The answer to the query [0,2] is 2 (strings "aba" and "ece").
to query [1,4] is 3 (strings "ece", "aa", "e").
to query [1,1] is 0.
We return [2,3,0].

Example 2:
Input: words = ["a","e","i"], queries = [[0,2],[0,1],[2,2]]
Output: [3,2,1]
Explanation: Every string satisfies the conditions, so we return [3,2,1].
*/


//85. STRING MATCHING IN AN ARRAY OF STRING
//USING BRUTE FORCE                                         {T.C = O(N^2*k), S.C = O(N)}, K = AVG LEN OF STRINGS
class Solution {
public:
    vector<string> stringMatching(vector<string>& words) {
        int n = words.size();
        vector<string>ans;

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(i != j && words[j].find(words[i]) != string :: npos){  //word[i] is substring of word[j] else write INT_MAX val
                    ans.push_back(words[i]);
                    break;
                }
            }
        }
        return ans;
    }
};
/*
Example 1:
Input: words = ["mass","as","hero","superhero"]
Output: ["as","hero"]
Explanation: "as" is substring of "mass" and "hero" is substring of "superhero".
["hero","as"] is also a valid answer.

Example 2:
Input: words = ["leetcode","et","code"]
Output: ["et","code"]
Explanation: "et", "code" are substring of "leetcode".

Example 3:
Input: words = ["blue","green","bu"]
Output: []
Explanation: No string of words is substring of another string.
*/