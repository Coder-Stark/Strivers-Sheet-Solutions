#include<bits/stdc++.h>
using namespace std;

//DAY 23: GRAPH -----------------------------------------------------------------------------------------------------
//84. CLONE A GRAPH (DEEP COPY)                                            {T.C = O(V+E), S.C = O(V)}
class Solution {
public:
    void dfs(Node* root, vector<Node*>&vis, Node*node){
        vis[node->val] = node;
        for(auto it : root->neighbors){
            if(!vis[it->val]){
                Node* newNode = new Node(it->val);
                node->neighbors.push_back(newNode);
                dfs(it, vis, newNode);
            }else{
                node->neighbors.push_back(vis[it->val]);
            }
        }
    }
    Node* cloneGraph(Node* root) {
        //base case
        if(!root) return NULL;
        Node* node = new Node(root->val);
        vector<Node*>vis(100, NULL);                         //n  = 100(max nodes constraints)
        dfs(root, vis, node);

        return node;
    }
};
/*
Example 1:
Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
Output: [[2,4],[1,3],[2,4],[1,3]]
Explanation: There are 4 nodes in the graph.
1st node (val = 1)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
2nd node (val = 2)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
3rd node (val = 3)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
4th node (val = 4)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).

Example 2:
Input: adjList = [[]]
Output: [[]]
Explanation: Note that the input contains one empty list. The graph consists of only one node with val = 1 and it does not have any neighbors.

Example 3:
Input: adjList = []
Output: []
Explanation: This an empty graph, it does not have any nodes.
*/


//85. DFS OF GRAPH                                              {T.C = O(V+E), S.C = O(V+E)}
//We required 2 DS (ans, vis(bool)) and also initialize nodeindex = 0,  mark vis[node] = 1 and push node in ans,  now traverse adj[node],
//if (!vis[it]) then push it and mark vis[it]=1 and make recursive call to DFS.
class Solution {
  public:
    void DFS(vector<int>adj[], vector<int>&ans, vector<bool>&vis, int node){
        vis[node] = 1;
        ans.push_back(node);
        for(auto it : adj[node]){
            if(!vis[it]){
                DFS(adj, ans, vis, it);
            }
        }
    }
    vector<int> dfsOfGraph(int V, vector<int> adj[]) {
        vector<int>ans;
        vector<bool>vis(V, 0);
        DFS(adj, ans, vis, 0);                       //0 = nodeindex
        return ans;

        /*
        //handle disconnected components
        for(int i = 0 ; i < V ; i++){
            dfs(i, adj, ans, vis);                                  //0 = starting index or node
        }
        */
    }
};
/*
Example 1:
Input: V = 5 , adj = [[2,3,1] , [0], [0,4], [0], [2]]
Output: 0 2 4 3 1
Explanation: 
0 is connected to 2, 3, 1.
1 is connected to 0.
2 is connected to 0 and 4.
3 is connected to 0.
4 is connected to 2.
so starting from 0, it will go to 2 then 4,
and then 3 and 1.
Thus dfs will be 0 2 4 3 1.

Example 2:
Input: V = 4, adj = [[1,3], [2,0], [1], [0]]
Output: 0 1 2 3
Explanation:
0 is connected to 1 , 3.
1 is connected to 0, 2. 
2 is connected to 1.
3 is connected to 0. 
so starting from 0, it will go to 1 then 2
then back to 0 then 0 to 3
thus dfs will be 0 1 2 3. 
*/


//86. BFS OF GRAPH                                 {T.C = O(V+E), S.C = O(V+E)}   //N = nodes, E = edges
//We required 3 DS (ans, vis(bool), queue) and also initialize nodeindex = 0, push node in queue and mark vis[node] = 1 and push node in ans
//now traverse queue, take out frontNode and push in ans, after that traverse adj[frontNode] , if (!vis[it]) then push it and mark vis[it]=1.
class Solution {
  public:
    void BFS(vector<int>adj[], vector<int>&ans, vector<bool>&vis, int node){
        vis[node] = 1;
        queue<int>q;
        q.push(node);
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            ans.push_back(frontNode);
            for(auto it : adj[frontNode]){
                if(!vis[it]){
                    q.push(it);
                    vis[it] = 1;
                }
            }
        }
    }
    vector<int> bfsOfGraph(int V, vector<int> adj[]) {
        vector<int>ans;
        vector<bool>vis(V, 0);
        BFS(adj, ans, vis, 0);                        //node index = 0
        return ans;
    }
};
/*
Example 1:
Input:
V = 5, E = 4
adj = {{1,2,3},{},{4},{},{}}
Output: 
0 1 2 3 4
Explanation: 
0 is connected to 1 , 2 , 3.
2 is connected to 4.
so starting from 0, it will go to 1 then 2
then 3. After this 2 to 4, thus bfs will be
0 1 2 3 4.

Example 2:
Input:
V = 3, E = 2
adj = {{1,2},{},{}}
Output: 
0 1 2
Explanation:
0 is connected to 1 , 2.
so starting from 0, it will go to 1 then 2,
thus bfs will be 0 1 2. 
*/


//87. UNDIRECTED GRAPH CYCLE / CHECK CYCLE PRESENT IN UNDIRECTED GRAPH          {T.C = O(V+E), S.C = O(V)}
//USING BFS
class Solution {
  public:
    bool isCyclicBFS(vector<int>adj[], vector<bool>&vis, int node){
        vis[node] = 1;
        queue<pair<int, int>>q;                   //{node, parent}
        q.push({node, -1});
        while(!q.empty()){
            auto frontNode = q.front();
            int currNode = frontNode.first;
            int parent = frontNode.second;
            q.pop();
            for(auto it : adj[frontNode.first]){   //node
                if(!vis[it]){
                    q.push({it, currNode});  //node, current node becomes parent
                    vis[it] = 1;
                }else if(it != parent){
                    return true;
                }
            }
        }
        return false;
    }
    bool isCycle(int V, vector<int> adj[]) {
        vector<bool>vis(V, 0);
        for(int i = 0 ; i < V ; i++){             //for disconnected components
            if(!vis[i] && isCyclicBFS(adj, vis, i)){            //i = nodeIndex, //parent not defined it will define via queue
                return true;
            }
        }
        return false;
    }
};

//88. USING DFS
class Solution {
  public:
    bool dfsUnCycle(vector<int>adj[], vector<bool>&vis, int node, int prev){
        vis[node] = true;
        for(auto it : adj[node]){
            if(!vis[it]){
                if(dfsUnCycle(adj, vis, it, node)) return true;  //it = curr, prev = node
            }else if(it != prev) return true;                   //visited but not parent(prev) then cycle
        }
        return false;
    }
    bool isCycle(int V, vector<int> adj[]) {
        vector<bool>vis(V, false);
        for(int i = 0 ; i < V ; i++){
            if(!vis[i] && dfsUnCycle(adj, vis, i, -1)) return true;
        }
        return false;
    }
};
/*
Input: V = 5, E = 5
adj = [[1], [0, 2, 4], [1, 3], [2, 4], [1, 3]] 
Output: 1
Explanation: 
1->2->3->4->1 is a cycle.
Input: V = 4, E = 2
adj = [[], [2], [1, 3], [2]]
Output: 0
Explanation: 
No cycle in the graph.
*/


//DIRECTED GRAPH CYCLE / CHECK CYCLE PRESENT IN DIRECTED GRAPH          {T.C = O(V+E), S.C = O(V)}
//89. USING DFS
class Solution {
  public:
    bool dfsDiCycle(vector<int>adj[], vector<bool>&vis, vector<bool>&dfsVis, int node){
        vis[node] = true;
        dfsVis[node] = true;
        for(auto it : adj[node]){
            if(!vis[it] && dfsDiCycle(adj, vis, dfsVis, it)) return true;
            else if(dfsVis[it] == true) return true;
        }
        dfsVis[node] = false;
        
        return false;
    }
    bool isCyclic(int V, vector<int> adj[]) {
        vector<bool>vis(V, false), dfsVis(V, false);
        for(int i = 0 ; i < V ; i++){
            if(!vis[i] && dfsDiCycle(adj, vis, dfsVis, i)) return true;
        }
        return false;
    }
};


//90. USING BFS
//KAHN'S ALGO
class Solution {
  public:
    vector<int>topoSort(vector<int>adj[], int n){
        vector<int>inDegree(n, 0);
        for(int i = 0 ; i < n ; i++){
            for(auto it : adj[i]) inDegree[it]++;
        }
        queue<int>q;
        for(int i = 0 ;i < n ;i++){
            if(inDegree[i] == 0) q.push(i);       //push index not ele
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
    bool isCyclic(int V, vector<int> adj[]) {
        vector<int>topo = topoSort(adj, V);
        if(topo.size() == V) return false;                //valid topo(no cycle)
        return true;
    }
};
/*
Example 1:
Input:
Output: 1
Explanation: 3 -> 3 is a cycle

Example 2:
Input:
Output: 0
Explanation: no cycle in the graph
*/


//91. TOPOLOGICAL SORT                                                        {T.C = O(V+E), S.C = O(V)}
//USING BFS (KAHN'S ALGO)
class Solution
{
	public:
	vector<int> topoSort(int V, vector<int> adj[]){
	    vector<int>ans;
	    vector<int>inDegree(V, 0);
	    
	    for(int i = 0 ; i < V ; i++){
	        for(auto it : adj[i]) inDegree[it]++;             //nbr indegree++
	    }
	    
	    queue<int>q;
	    for(int i = 0 ; i < V ; i++){
	        if(inDegree[i] == 0) q.push(i);
	    }
	    
	    //bfs
	    while(!q.empty()){
	        auto frontNode = q.front();
	        q.pop();
	        ans.push_back(frontNode);
	        for(auto it : adj[frontNode]){
	            inDegree[it]--;                            //reduce indegree of nbr
	            if(inDegree[it] == 0) q.push(it);
	        }
	    }
	    return ans;
	}
};


//92. USING DFS
class Solution{
	public:
	void dfsTopo(vector<int>adj[], vector<bool>&vis, stack<int>&stk, int node){
	    vis[node] = true;
	    for(auto it : adj[node]){
	        if(!vis[it]) dfsTopo(adj, vis, stk, it);
	    }
	    stk.push(node);                                //topo logic
	}
	vector<int> topoSort(int V, vector<int> adj[]){
        stack<int>stk;
        vector<bool>vis(V, false);
        for(int i = 0 ; i < V ; i++){
            if(!vis[i]) dfsTopo(adj, vis, stk, i);
        }
        
        vector<int>ans;
        while(!stk.empty()){
            ans.push_back(stk.top());
            stk.pop();
        } 
        return ans;
	}
};
/*
Example 1:
Input:
Output:
1
Explanation:
The output 1 denotes that the order is
valid. So, if you have, implemented
your function correctly, then output
would be 1 for all test cases.
One possible Topological order for the
graph is 3, 2, 1, 0.

Example 2:
Input:
Output:
1
Explanation:
The output 1 denotes that the order is
valid. So, if you have, implemented
your function correctly, then output
would be 1 for all test cases.
One possible Topological order for the
graph is 5, 4, 2, 1, 3, 0.
*/


//93. NUMBER OF ISLANDS                                                   {T.C = O(N*M), S.C = O(N*M)}
class Solution {
public:
    vector<vector<int>>directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool isValid(int i, int j , int n, int m){
        return (i >= 0 && i < n && j >= 0 && j < m);
    }
    void dfs(vector<vector<char>>&grid, int i, int j, int n, int m){
        if(isValid(i, j, n, m) && grid[i][j] == '1'){
            grid[i][j] = '0';              //mark visited
            
            for(auto it : directions){
                int newR = i + it[0];
                int newC = j + it[1];
                dfs(grid, newR, newC, n, m);
            }
            /*
            dfs(grid, i+1, j, n, m);       //down
            dfs(grid, i-1, j, n, m);       //up
            dfs(grid, i, j+1, n, m);       //right
            dfs(grid, i, j-1, n, m);       //left
            */
        }
    }
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int components = 0;
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < m ; j++){
                if(grid[i][j] == '1'){
                    components++;
                    dfs(grid, i, j, n, m);
                }
            }
        }
        return components;
    }
};
/*
Example 1:
Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1

Example 2:
Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3
*/


//93.b NUMBER OF DISTINCT ISLANDS                                       {T.C = O(N*M), S.C = O(N*M)}
class Solution {
  public:
    vector<vector<int>>directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool isValid(int newRow, int newCol, int n, int m){
        return (newRow >= 0 && newRow < n && newCol >= 0 && newCol < m);
    }
    void dfs(vector<vector<int>>&grid, vector<vector<int>>&vis, int i, int j, vector<vector<int>>&shapes, int baseRow, int baseCol){
        int n = grid.size(), m = grid[0].size();
        vis[i][j] = 1;
        shapes.push_back({i-baseRow, j-baseCol});      //{{0,0},{0.1},{1,0},{1,1} == (0.0)[{3,3}-{3,3}] , (0,1)[{3,4}-{3,3}], (1, 0)[{4,3}-{3,3}] , (1, 1)[{4,4}-{3,3}]
        for(auto it : directions){
            int newRow = i + it[0];
            int newCol = j + it[1];
            if(isValid(newRow, newCol, n, m) && !vis[newRow][newCol] && grid[newRow][newCol] == 1){
                dfs(grid, vis, newRow, newCol, shapes, baseRow, baseCol);
            }
        }
    }
    int countDistinctIslands(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>>vis(n, vector<int>(m, 0));
        set<vector<vector<int>>>st;
        int countDistinct = 0;
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ;  j < m ; j++){
                if(!vis[i][j] && grid[i][j] == 1){
                    vector<vector<int>>shapes;        //smilar shape islands
                    dfs(grid, vis, i, j, shapes, i, j);
                    st.insert(shapes);
                }
            }
        }
        return st.size();
    }
};
/*
Example 1:
Input:
grid[][] = {{1, 1, 0, 0, 0},
            {1, 1, 0, 0, 0},
            {0, 0, 0, 1, 1},
            {0, 0, 0, 1, 1}}
Output:
1
Explanation:
grid[][] = {{1, 1, 0, 0, 0}, 
            {1, 1, 0, 0, 0}, 
            {0, 0, 0, 1, 1}, 
            {0, 0, 0, 1, 1}}
Same colored islands are equal.
We have 2 equal islands, so we 
have only 1 distinct island.

Example 2:
Input:
grid[][] = {{1, 1, 0, 1, 1},
            {1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1},
            {1, 1, 0, 1, 1}}
Output:
3
Explanation:
grid[][] = {{1, 1, 0, 1, 1}, 
            {1, 0, 0, 0, 0}, 
            {0, 0, 0, 0, 1}, 
            {1, 1, 0, 1, 1}}
Same colored islands are equal.
We have 4 islands, but 2 of them
are equal, So we have 3 distinct islands.
*/


//94. IS GRAPH BIPARTITE                                                   {T.C = O(V+E), S.C = O(V)}
//USING BFS
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


//95. USING DFS               
class Solution {
public:
    bool dfsBi(vector<vector<int>>&adj, vector<int>&vis, int node, int currClr){
        vis[node] = currClr;
        for(auto it : adj[node]){
            if(vis[it] == -1){                         //not vis
                currClr = 1-currClr;                   //1 to 0 or 0 to 1
                if(!dfsBi(adj, vis, it, currClr)) return false;
            }else if(vis[it] == vis[node]) return false;            //adjacent same color(not allowed)
        }
        return true;
    }
    bool isBipartite(vector<vector<int>>& graph) {        //graph => adj
        int n = graph.size();
        vector<int>vis(n, -1);                 //1 for red , 0 = blue (2 color)
        for(int i = 0 ; i < n ; i++){
            if(vis[i] == -1){
                if(!dfsBi(graph, vis, i, 1)){            //1 = currClr (like prevIdx -1)
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