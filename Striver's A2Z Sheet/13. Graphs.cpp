//GRAPHS

#include<bits/stdc++.h>
using namespace std;

//2D TO 1D INDEX
//int index = row*m + col;            //col = total number of columns

/*------------------------------------------------------- GRAPHS GENERAL ------------------------------------------------*/
//GRAPH
/*
//MINIMUM DISTANCE FINDING ALGORITHM
1. DIJKSTRA'S ALGO                  {not work for -ve Undirected weighted graph} //DAG
2. BELLMANFORD ALGO                 {work for -ve weighted graph}
3. FLOYD WARSHALL ALGO              {brute force algo}

//MINIMUM SPANNING TREE ALGORITHM
1. KRUSKAL'S ALGO          {intermediate result may be or may be not connected}
2. PRIM'S ALGO             {intermediate result always connected} 

DIJKSTRA ALGORITM                                           {T.C = O((V+E)LOGV), S.C = O(V+E)}
//NOT APPLICABLE FOR NEGATIVE WEIGHT CYCLE (similar to BFS)
1. Create minHeap.
2. find shortest distance of each node from current node.

BELLMAN FORD                                                {T.C = O(V*E), S.C = O(V)}
APPLICABLE FOR NEGATIVE WEIGHT CYCLE
WORK ONLY FOR DIRECTED GRAPH (DAG) SO FOR UNDIRECTED GRAPH FIRST WE HAVE TO CONVERT IT INTO DIRECTED(make edges both side)
1.2 LOOP 1ST(0 TO V), 2ND(EDGES REST {SIMILAR TO DIJKSTRA}), 
2.AGAIN 2ND LOOP OUTER FOR CHECK CYCLE.

FLOYD WARSHALL                                              {T.C = O(N^3), S.C = O(N^2)}
1. Brute force algo
2. Three loops (k , i , j) take mindis = min(mindis[i][j], minDis[i][k]+minDis[k][j])

PRIM'S ALGORITHM                                                     {T.C = O(ELOGV), S.C = O(E+V)}
//required 
1.Adjacency list
2.Priority queue ({w, node, parent})                  //{0, 0, -1}
3. visited vector

//vertex based
//Data Structures = key(n, INT_MAX), mst(n, false), parent(n, -1)
ALGORITHM
1. Choose any vertex
2. Take minimum weight path.
3. Take care of previous paths as well.
4. Cycle should not be created.
5. Intermediate result is always connected

//KRUSKAL ALGORITHM (REQUIRED DISJOINT SET (FIND, UNION))
//require vector<vector<int>>vec               //{u, v, w}
ALGORITHM
1. Take a vector or map and store {u, v, w}
2. sort the vector on the basis of its weight.
3. then take sum, and iterate on vec
4. if the parent of u and v not same then take Union and sum+= w
5. finally return sum(minsum spanning tree)

DISJOINT SET = Intersection of all sets(components is null)              {T.C = O(CONSTANT), S.C = O(1)}  
//USED IN DYNAMIC CHANGE GRAPH.
//2 Functions = find and Union
1. COMBINE TWO GIVEN SETS.          {union find}
2. TELLS IF TWO MEMBERS BELONG TO SAME SETS OR NOT                     //in constant time (bfs o(n))
//SMALLER LENGTH GRAPH CONNECT TO LARGER LEN GRAPH (FOR AVOID INCREASING HEIGHT OF TREE OR GRAPH)
//REQUIREMENT OF EDGES (NOT ADJACENCY LIST)


//STRONGLY CONNECTED COMPONENTS (SCC)
ALGORITHM
1. sort the adjacency list using topological sort
2. create a transpose graph
3. dfs call on basis of above ordering (stack ordering)

//EULERIAN PATH
1. A Path of edges that visits all the edges in a graph exactly once.
2. Not all graphs have eulerian path.
3. All node have even degree except (2 nodes {starting & ending})
4. If any node degree > 2 then it is not having Eulerian Path.
//EULERIAN CIRCUIT
1. An eulerian path which starts and ends on the same node.
2. If the path is eulerian circuit then we can start any node(it will always ends on same node).
3. All vertices with non zero degree node need to belong to a single connected component. 
    (non zero degree nodes must be connected via a single component {one dfs only})
4. If all vertices have even degrees then it always a Eulerian Circuit.
//SEMI EULERIAN GRAPH
1. Eulerian Path Only (starting and ending node degree is always odd and other nodes have even degree)
2. Not Eulerian circuit.


TIPS
1. given a string change to required string with minium (value) is always a bfs Question.
2. for finding cycle is present or not in DAG we required vis && dfsVis both.
/*---------------------------------------------------------------------------------------------------------------------*/


//LEARNING-------------------------------------------------------------------------------------------
//290. GRAPH AND VERTICES                                       {T.C = O(1), S.C = O(1)}
//TOTAL EDGES (NC2 = N*(N-1)/2), SO TOTAL GRAPHS = 2^TOTAL EDGES
class Solution {
  public:
    long long count(int n) {
        long long noOfEdges = n*(n-1)/2;      //nC2
        return pow(2, noOfEdges);
    }
};
/*
Example 1:
Input: 2
Output: 2

Example 2:
Input: 5
Output: 1024
*/


//291 /292. PRINT ADJACENCY LIST                                     {T.C = O(V+E), S.C = O(V+E)}
//CREATE 2 VECTOR(ADJ), ITERATE OVER EDGES AND CONNECT (U <-> V), PUSH IN ADJ
class Solution {
  public:
    vector<vector<int>> printGraph(int V, vector<pair<int,int>>edges) {
        vector<vector<int>>adj(V);
        for(auto it : edges){
            int u = it.first;
            int v = it.second;
            
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        return adj;
    }
};
/*
Example 1:

Input:
V = 5, E = 7
edges = {(0,1),(0,4),(4,1),(4,3),(1,3),(1,2),(3,2)}
Output: 
{{1,4}, 
 {0,2,3,4}, 
 {1,3},
 {1,2,4},
 {0,1,3}}
Explanation:
Node 0 is connected to 1 and 4.
Node 1 is connected to 0,2,3 and 4.
Node 2 is connected to 1 and 3.
Node 3 is connected to 1,2 and 4.
Node 4 is connected to 0,1 and 3.
*/


//293. NUMBER OF CONNECTED COMPONENT IN UNDIRECTED GRAPH             {T.C = O(V+E), S.C = O(V)}
//SIMPLE USE DFS AND ITERATE ON ALL VERTICES AND INCREASE COUNT (FOR DISCONNECTED COMPONENT)
class Solution {
public:
    void dfs(unordered_map<int, vector<int>>& adj, vector<bool>& vis, int node) {
        vis[node] = true;
        for (auto it : adj[node]) {
            if (!vis[it]) {
                dfs(adj, vis, it);
            }
        }
    }

    int countComponents(int n, vector<vector<int>>& edges) {
        unordered_map<int, vector<int>> adj;
        for (auto it : edges) {
            int u = it[0];
            int v = it[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        vector<bool> vis(n, false);
        int countComponents = 0;
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs(adj, vis, i);
                countComponents++;
            }
        }
        return countComponents;
    }
};

int main() {
    Solution solution;
    int n, e;

    cout << "Enter the number of nodes: ";
    cin >> n;

    cout << "Enter the number of edges: ";
    cin >> e;

    vector<vector<int>> edges(e, vector<int>(2));
    cout << "Enter the edges (u v): " << endl;
    for (int i = 0; i < e; i++) {
        cin >> edges[i][0] >> edges[i][1];
    }

    int result = solution.countComponents(n, edges);
    cout << "Number of connected components: " << result << endl;

    return 0;
}
/*
Enter the number of nodes: 6
Enter the number of edges: 4
Enter the edges (u v): 
0 1
1 2
2 3
4 5
Number of connected components: 2*/


//294. BFS OF GRAPH                                 {T.C = O(N+M/ V+E), S.C = O(N+M / V+E)}   //N = nodes, E = edges
/*
We required 3 DS (ans, vis(bool), queue) and also initialize nodeindex = 0, push node in queue and mark vis[node] = 1 and push node in ans
now traverse queue, take out frontNode and push in ans, after that traverse adj[frontNode] , if (!vis[it]) then push it and mark vis[it]=1.
*/
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


//295. DFS OF GRAPH                                              {T.C = O(N+M / V+E), S.C = O(N+M / V+E)}
/*
We required 2 DS (ans, vis(bool)) and also initialize nodeindex = 0,  mark vis[node] = 1 and push node in ans,  now traverse adj[node],
if (!vis[it]) then push it and mark vis[it]=1 and make recursive call to DFS.
*/
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
            dfs(0, adj, ans, vis);                                  //0 = starting index or node
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


//PROBLEMS ON BFS/DFS----------------------------------------------------------------------------------
//296. NUMBER OF PROVINCES                                    {T.C = O(N^2), S.C = O(N^2)}
//CREATE ADJ LSIT (ONLY THOSE WHO CONNECTED) , THEN TRAVERSE ON GRAPH AND FIND COUNT OF COMPONENTS.
class Solution {
public:
    void dfs(unordered_map<int,vector<int>>&adj, vector<bool>&vis, int node){
        vis[node] = 1;
        for(auto it : adj[node]){
            if(!vis[it]){
                dfs(adj, vis, it);
            }
        }
    }
    int findCircleNum(vector<vector<int>>& isConnected) {
        unordered_map<int , vector<int>>adj;
        int n = isConnected.size();
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                if(isConnected[i][j] == 1){
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }
        int countComponents = 0;
        vector<bool>vis(n, 0);
        for(int i = 0 ; i < n ; i++){
            if(!vis[i]){
                dfs(adj, vis, i);                          //i = initial node
                countComponents++;
            }
        }
        return countComponents;
    }
};
/*
Example 1:
Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
Output: 2

Example 2:
Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]]
Output: 3
*/


//297. NUMBER OF PROVINCES                                    {T.C = O(N^2), S.C = O(N^2)}
//CREATE ADJ LSIT (ONLY THOSE WHO CONNECTED) , THEN TRAVERSE ON GRAPH AND FIND COUNT OF COMPONENTS.
//USING BFS
class Solution {
  public:
    void bfs(unordered_map<int,vector<int>>&adj, vector<bool>&vis, int node){
        vis[node] = 1;
        queue<int>q;
        q.push(node);
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            for(auto it : adj[frontNode]){
                if(!vis[it]){
                    q.push(it);
                    vis[it] = 1;
                }
            }
        }
    }
    int numProvinces(vector<vector<int>> adj, int V) {
        unordered_map<int, vector<int>>adjList;
        for(int i = 0 ; i < V ;i++){
            for(int j = 0 ; j < V ; j++){
                if(adj[i][j] == 1){
                    adjList[i].push_back(j);
                    adjList[j].push_back(i);
                }
            }
        }
        vector<bool>vis(V, 0);
        int components = 0;
        for(int i =  0 ; i < V ; i++){
            if(!vis[i]){
                bfs(adjList, vis, i);
                components++;
            }
        }
        return components;
    }
};
/*
Example 1:
Input:
[
 [1, 0, 1],
 [0, 1, 0],
 [1, 0, 1]
]
Output:
2
Explanation:
The graph clearly has 2 Provinces [1,3] and [2]. As city 1 and city 3 has a path between them they belong to a single province. City 2 has no path to city 1 or city 3 hence it belongs to another province.

Example 2:
Input:
[
 [1, 1],
 [1, 1]
]
Output :
1
*/


//298. ROTTING ORANGES                                         {T.C = O(N*M), S.C = O(N*M)}
//USING BFS (MINIMUM TIME REQUIRED TO ROT ORANGE)
//FIRST FIND COUNT OF FRESH && MODIFIED VIS(2D{0,1}), THEN MAKE BFS FIND COUNT FOR ROTTEN AND TIME.
class Solution {
  public:
    vector<vector<int>>directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    bool isValid(int newRow, int newCol, int n, int m){
        return newRow >= 0 && newRow < n && newCol >= 0 && newCol < m;
    }
    int orangesRotting(vector<vector<int>>&grid) {
      int n = grid.size();
      int m = grid[0].size();

      queue<pair<pair<int, int>,int>>q;                // store {{row, column}, time}
      vector<vector<int>>vis(n, vector<int>(m, 0));
      int cntFresh = 0;
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          if (grid[i][j] == 2) {                      // if cell contains rotten orange push in queue with time 0 and mark vis(rotten {2})
            q.push({{i, j}, 0}); 
            vis[i][j] = 2;                            
          }
          else {                                      // if not rotten
            vis[i][j] = 0;
          }

          if (grid[i][j] == 1){                       // count fresh oranges
            cntFresh++;
          } 
        }
      }

      int tm = 0;
      int cnt = 0;

      // bfs traversal (until the queue becomes empty)
      while (!q.empty()) {
        auto frontNode = q.front();
        q.pop();
        int r = frontNode.first.first;
        int c = frontNode.first.second;
        int t = frontNode.second;
        tm = max(tm, t);

        for (auto it : directions) {
          int newRow = r + it[0];
          int newCol = c + it[1];

          if(isValid(newRow, newCol, n, m) && vis[newRow][newCol] == 0 && grid[newRow][newCol] == 1){
            q.push({{newRow, newCol}, t+1});             //increase time 
            vis[newRow][newCol] = 2;
            cnt++;
          }
        }
      }
      
      if (cnt != cntFresh){                              // if all oranges are not rotten
        return -1;                     
      } 
      return tm;
    }
};
/*
Example 1:
Input: grid = [[2,1,1],
               [1,1,0],
               [0,1,1]]
Output: 4

Example 2:
Input: grid = [[2,1,1],
               [0,1,1],
               [1,0,1]]
Output: -1
Explanation: The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.

Example 3:
Input: grid = [[0,2]]
Output: 0
Explanation: Since there are already no fresh oranges at minute 0, the answer is just 0.
*/


//299. FLOOD FILL                                            {T.C = O(N*M), S.C = O(N*M)}
//USING BFS
class Solution {
public:
    vector<vector<int>>directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    bool isValid(int newRow, int newCol, int n, int m){
        return (newRow >= 0 && newRow < n && newCol >= 0 && newCol < m);
    }
    void bfs(vector<vector<int>>&image, int sr, int sc, int newColor, int currColor, vector<vector<int>>&vis){
        int n = image.size(), m = image[0].size();
        vis[sr][sc] = 1;
        queue<pair<int,int>>q;
        q.push({sr, sc});
        image[sr][sc] = newColor;
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            int r = frontNode.first;
            int c = frontNode.second;
            for(auto it : directions){
                int newRow = r + it[0];
                int newCol = c + it[1]; 
                if(isValid(newRow, newCol, n, m) && !vis[newRow][newCol] && image[newRow][newCol] == currColor){
                    q.push({newRow, newCol});
                    vis[newRow][newCol] = 1;
                    image[newRow][newCol] = newColor;
                }
            }
        }
    }
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int n = image.size(), m = image[0].size();

        vector<vector<int>>vis(n, vector<int>(m, 0));
        int currColor = image[sr][sc];
        bfs(image, sr, sc, color, currColor, vis);

        return image;        
    }
};

//USING DFS
class Solution {
public:
    vector<vector<int>>directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    bool isValid(int newRow, int newCol, int n, int m){
        return (newRow >= 0 && newRow < n && newCol >= 0 && newCol < m);
    }
    void dfs(vector<vector<int>>&image, int sr, int sc, int newColor, int currColor, vector<vector<int>>&vis){
        int n = image.size(), m = image[0].size();
        vis[sr][sc] = 1;
        image[sr][sc] = newColor;
        for(auto it : directions){
            int newRow = sr + it[0];
            int newCol = sc + it[1];

            if(isValid(newRow, newCol, n, m) && !vis[newRow][newCol] && image[newRow][newCol] == currColor){
                dfs(image, newRow, newCol, newColor, currColor, vis);
            }
        }
    }
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int n = image.size(), m = image[0].size();

        vector<vector<int>>vis(n, vector<int>(m, 0));
        int currColor = image[sr][sc];
        dfs(image, sr, sc, color, currColor, vis);

        return image;        
    }
};
/*
Example 1:
Input: image = [[1,1,1],
                [1,1,0],
                [1,0,1]], 
                sr = 1, sc = 1, color = 2
Output: [[2,2,2],[2,2,0],[2,0,1]]
Explanation: From the center of the image with position (sr, sc) = (1, 1) (i.e., the red pixel), all pixels connected by a path of the same color as the starting pixel (i.e., the blue pixels) are colored with the new color.
Note the bottom corner is not colored 2, because it is not 4-directionally connected to the starting pixel.

Example 2:
Input: image = [[0,0,0],
                [0,0,0]], 
                sr = 0, sc = 0, color = 0
Output: [[0,0,0],[0,0,0]]
Explanation: The starting pixel is already colored 0, so no changes are made to the image.
*/


//300. DETECT CYCLE IN UNDIRECTED GRAPH
//USING BFS                                                                      {T.C = O(V+E), S.C = O(V)}
/*
Firstly the graph can be disconnected so we have to use a loop for disconnected graph, the call bfs function , in which 
use simple bfs(queue<int, int>q {node, parent}) and check for if !vis[it{frontnode.first}] push {it, currNode} and mark vis[it] = 1
else check if vis but not parent then also true else return false(cycle is not present).
*/
class Solution {
  public:
    //using bfs
    bool isCyclicBFS(vector<int>adj[], vector<bool>&vis, int node){
        vis[node] = 1;
        queue<pair<int, int>>q;                   //{node, parent}
        q.push({node, -1});
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            int currNode = frontNode.first;
            int parent = frontNode.second;
            for(auto it : adj[currNode]){   //node
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
/*
Example 1:
Input:  
V = 5, E = 5
adj = {{1}, {0, 2, 4}, {1, 3}, {2, 4}, {1, 3}} 
Output: 1
Explanation: 
1->2->3->4->1 is a cycle.

Example 2:
Input: 
V = 4, E = 2
adj = {{}, {2}, {1, 3}, {2}}
Output: 0
Explanation: 
No cycle in the graph.
*/


//301. DETECT CYCLE IN UNDIRECTED GRAPH
// USING DFS                                                                 {T.C = O(V+E), S.C = O(V)}
/*
Firstly the graph can be disconnected so we have to use a loop for disconnected graph, the call dfs function , in which 
use simple dfs and check for if !vis[it] and isCyclic return true, else outer check if vis but not parent then also true
else return false(cycle is not present).
*/
class Solution {
  public:
    // using dfs
    bool isCyclicDFS(vector<int>adj[], vector<bool>&vis, int node , int parent){
        vis[node] = 1;
        for (auto it : adj[node]) {
            if (!vis[it]) {
                if (isCyclicDFS(adj, vis, it, node)) {
                    return true;
                }
            }else if (it != parent) {           //vis is true but not parent then cycle present
                return true;
            }
        }
        return false;
    }
    bool isCycle(int V, vector<int> adj[]) {
        vector<bool>vis(V, 0);
        for(int i = 0 ; i < V ; i++){                        //for disconnected components
            if(!vis[i] && isCyclicDFS(adj, vis, i, -1)){       //i = nodeIndex, -1 = parent
                return true;
            }
        }
        return false;
    }
};
/*
Example 1:
Input:  
V = 5, E = 5
adj = {{1}, {0, 2, 4}, {1, 3}, {2, 4}, {1, 3}} 
Output: 1
Explanation: 
1->2->3->4->1 is a cycle.

Example 2:
Input: 
V = 4, E = 2
adj = {{}, {2}, {1, 3}, {2}}
Output: 0
Explanation: 
No cycle in the graph.
*/


//302. 01 MATRIX                                            {T.C = O(N*M), S.C = O(N*M)}
//USING BFS
//STORE ALL Os AND FIND DISTANCE OF 0 TO 0 (INSTEAD OF ALL 1 TO 0)
class Solution {
public:
    //bfs from 0 instead of 1 
    vector<vector<int>>directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool isValid(int newRow, int newCol, int n , int m){
        return (newRow >= 0 && newRow < n && newCol >= 0 && newCol < m);
    }
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        vector<vector<int>>ansMat(n, vector<int>(m, -1));
        queue<pair<int,int>>q;
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < m ; j++){
                if(mat[i][j] == 0){
                    ansMat[i][j] = 0;
                    q.push({i, j});
                }
            }
        }
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            int r = frontNode.first;
            int c = frontNode.second;
            for(auto it : directions){
                int newRow = r + it[0];
                int newCol = c + it[1];
                if(isValid(newRow, newCol, n, m) && ansMat[newRow][newCol] == -1){
                    ansMat[newRow][newCol] = ansMat[r][c] + 1;
                    q.push({newRow, newCol});
                }

            }
        }
        return ansMat;
    }
};
/*
Example 1:
Input: mat = [[0,0,0],
              [0,1,0],
              [0,0,0]]
Output: [[0,0,0],
         [0,1,0],
         [0,0,0]]

Example 2:
Input: mat = [[0,0,0],
              [0,1,0],
              [1,1,1]]
Output: [[0,0,0],
         [0,1,0],
         [1,2,1]]
*/


//303. SORROUNDED REGIONS                                     {T.C = O(N*M), S.C = O(N*M)}
//USING DFS
//FIRST CHECK 'O' ON BOUNDARY IF PRESENT DFS(AND IGNORE IT) ELSE CONVERT 'O' TO 'X'
class Solution {
public:
    vector<vector<int>>directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool isValid(int newRow, int newCol, int n, int m){
        return (newRow >= 0  && newRow < n && newCol >= 0 && newCol < m);
    }

    void dfs(vector<vector<char>>& board, vector<vector<int>>&vis, int i, int j) {
        int n = board.size(), m = board[0].size();
        vis[i][j] = 1;
        for(auto it : directions){
            int newRow = i + it[0];
            int newCol = j + it[1];
            if(isValid(newRow, newCol, n, m) && !vis[newRow][newCol] && board[newRow][newCol] == 'O'){
                dfs(board, vis, newRow, newCol);
            }
        }
    }

    void solve(vector<vector<char>>& board) {
        int n = board.size();
        int m = board[0].size();
        vector<vector<int>>vis(n, vector<int>(m, 0));

        // Handle edge case of empty board
        if (n == 0) return;  

        //check boundry connected or not
        // Moving over first and last columns
        for (int i = 0; i < n; i++) {
            if (!vis[i][0] && board[i][0] == 'O') {                 //first col
                dfs(board, vis, i, 0);
            }
            if (!vis[i][m-1] && board[i][m - 1] == 'O') {            //last col
                dfs(board, vis, i, m - 1);
            }
        }

        // Moving over first and last rows
        for (int j = 0; j < m; j++) {
            if (!vis[0][j] && board[0][j] == 'O') {              //first row
                dfs(board, vis, 0, j);
            }
            if (!vis[n-1][j] && board[n - 1][j] == 'O') {        //last row
                dfs(board, vis, n - 1, j);
            }
        }

        // Convert remaining 'O's to 'X'
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!vis[i][j] && board[i][j] == 'O') {
                    board[i][j] = 'X';
                }
            }
        }
        //return board;
    }
};
/*
Example 1:
Input: board = [["X","X","X","X"],
                ["X","O","O","X"],
                ["X","X","O","X"],
                ["X","O","X","X"]]
Output: [["X","X","X","X"],
         ["X","X","X","X"],
         ["X","X","X","X"],
         ["X","O","X","X"]]
Explanation:
In the above diagram, the bottom region is not captured because it is on the edge of the board and cannot be surrounded.

Example 2:
Input: board = [["X"]]
Output: [["X"]]
*/


//304. NUMBER OF ENCLAVES                                     {T.C = O(N*M), S.C = O(N*M)}
//USING DFS
//SAME AS ABOVE JUST IN PLACE OF REPLACEMENT OF O=>X WE HAVE TO INCREASE COUNT(ENCLAVES)
class Solution {
public:
    vector<vector<int>>directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool isValid(int newRow, int newCol, int n, int m){
        return (newRow >= 0 && newRow < n && newCol >= 0 && newCol < m);
    }
    void dfs(vector<vector<int>>&grid, vector<vector<int>>&vis, int i, int j){
        int n = grid.size(), m = grid[0].size();
        vis[i][j] = 1;
        for(auto it : directions){
            int newRow = i + it[0];
            int newCol = j + it[1];
            if(isValid(newRow, newCol, n, m) && !vis[newRow][newCol] && grid[newRow][newCol] == 1){
                dfs(grid, vis, newRow, newCol);
            }
        }
    }
    int numEnclaves(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>>vis(n, vector<int>(m, 0));
        //check boundary cases
        //boundary row 
        for(int i = 0 ; i < n ; i++){
            if(!vis[i][0] && grid[i][0] == 1){      //first col
                dfs(grid, vis, i, 0);
            }
            if(!vis[i][m-1] && grid[i][m-1] == 1){  //last col
                dfs(grid, vis, i, m-1);
            }
        }

        //boundary col 
        for(int j = 0 ; j < m ; j++){
            if(!vis[0][j] && grid[0][j] == 1){
                dfs(grid, vis, 0, j);
            }
            if(!vis[n-1][j] && grid[n-1][j] == 1){
                dfs(grid, vis, n-1, j);
            }
        }

        int count = 0;                   //count of 1 (sorrounding with 0)
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < m; j++){
                if(!vis[i][j] && grid[i][j] == 1){
                    count++;
                }
            }
        }
        return count;
    }
};
/*
Example 1:
Input: grid = [[0,0,0,0],
               [1,0,1,0],
               [0,1,1,0],
               [0,0,0,0]]
Output: 3
Explanation: There are three 1s that are enclosed by 0s, and one 1 that is not enclosed because its on the boundary.
Example 2:
Input: grid = [[0,1,1,0],
               [0,0,1,0],
               [0,0,1,0],
               [0,0,0,0]]
Output: 0
Explanation: All 1s are either on the boundary or can reach the boundary.
*/


//305. WORD LADDER I                                          {T.C = O(N*WORDLENGTH*26), S.C = O(N)}
//USING BFS
//STORE DICTIONARY IN SET (EASY FETCHING), QUEUE(WORD, STEPS), THEN CHECK OF WORDLENGTH 26(a-z) times
//and pop char for backtrack and search for all possible answer
class Solution {
public:
    int wordLadderLength(string startWord, string targetWord, vector<string>& wordList) {
        queue<pair<string, int>>q;                    //{word, steps}
        q.push({startWord, 1});                       //initial word count as step1 
        unordered_set<string>st(wordList.begin(), wordList.end());      //dictionary
        st.erase(startWord);                        //pushed in queue
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            string currWord = frontNode.first;
            int currStep    = frontNode.second;
            if(currWord == targetWord) return currStep;
            
            for(int i = 0 ; i < currWord.size() ; i++){
                char original = currWord[i];                   //store curr word for 
                for(char ch = 'a' ; ch <= 'z' ; ch++){
                    currWord[i] = ch;
                    if(st.count(currWord)){
                        q.push({currWord, currStep+1});
                        st.erase(currWord);
                    }
                }
                currWord[i] = original;                      //backtrack for searching each char replacement
            }
        }
        
        return 0;                                            //word cant form
    }
};
/*
Example 1:
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5
Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> cog", which is 5 words long.

Example 2:
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: 0
Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.
*/


//306. WORD LADDER II                            {T.C =(CANT TELL MULTIPLE SEQUENCE), S.C = O(N*M)}                
//USING BFS
//HARDEST PROBLEM
class Solution {
public:
    vector<vector<string>> findSequences(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>>ans;
        queue<vector<string>>q;
        q.push({beginWord});                                   //intial vector contains beginWord only
        unordered_set<string>st(wordList.begin(), wordList.end());
        vector<string>usedOneLevel;
        usedOneLevel.push_back(beginWord);
        int level = 0;
        while(!q.empty()){
            auto vec = q.front();             //vec = frontNode (vector of strings)
            q.pop();
            if(vec.size() > level){           //erase all words i.e used in prev levels to transform
                level++;
                for(auto it : usedOneLevel) st.erase(it);
            }
            
            string currWord = vec.back();
            if(currWord == endWord){          //store answer
                if(ans.size() == 0) ans.push_back(vec);
                else if(ans[0].size() == vec.size()) ans.push_back(vec);
            }
            for(int i = 0 ; i < currWord.size() ; i++){
                char original = currWord[i];
                for(char ch = 'a' ; ch <= 'z' ; ch++){
                    currWord[i] = ch;
                    if(st.count(currWord)){
                        vec.push_back(currWord);
                        q.push(vec);
                        usedOneLevel.push_back(currWord); //mark vis on the level
                        vec.pop_back();
                    }
                }
                currWord[i] = original;
            }
        }
        return ans;
    }
};
/*
Example 1:
Input:
startWord = "der", targetWord = "dfs",
wordList = {"des","der","dfr","dgt","dfs"}
Output:
der dfr dfs
der des dfs
Explanation:
The length of the smallest transformation is 3.
And the following are the only two ways to get
to targetWord:-
"der" -> "des" -> "dfs".
"der" -> "dfr" -> "dfs".

Example 2:
Input:
startWord = "gedk", targetWord = "geek", 
wordList = {"geek", "gefk"}
Output:
"gedk" -> "geek"
*/


//307. FIND NUMBER OF ISLANDS                               {T.C = O(N*M), S.C = O(N*M)}
//USING DFS
//SAME AS FINDING CONNECTED COMPONENTS
class Solution {
  public:
    vector<vector<int>>directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, 1}, {-1, -1}, {1, -1}};
    bool isValid(int newRow, int newCol, int n, int m){
        return (newRow >= 0 && newRow < n && newCol >= 0 && newCol < m);
    }
    void dfs(vector<vector<char>>&grid, vector<vector<int>>&vis, int i, int j){
        int n = grid.size(), m = grid[0].size();
        vis[i][j] = 1;
        for(auto it : directions){
            int newRow = i + it[0];
            int newCol = j + it[1];
            if(isValid(newRow, newCol, n, m) && !vis[newRow][newCol] && grid[newRow][newCol] == '1'){
                dfs(grid, vis, newRow, newCol);
            }
        }
    }
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>>vis(n, vector<int>(m, 0));
        
        int count = 0;
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < m ; j++){
                if(!vis[i][j] && grid[i][j] == '1'){
                    count++;
                    dfs(grid, vis, i, j);
                }
            }
        }
        return count;
    }
};
/*
Example 1:
Input:
grid = {{0,1},
        {1,0},
        {1,1},
        {1,0}}
Output:
1
Explanation:
The grid is-
0 1
1 0
1 1
1 0
All lands are connected.
Example 2:
Input:
grid = {{0,1,1,1,0,0,0},
        {0,0,1,1,0,1,0}}
Output:
2
Expanation:
The grid is-
0 1 1 1 0 0 0
0 0 1 1 0 1 0 
There are two islands :- one is colored in blue 
and other in orange.
*/


//308. NUMBER OF DISTINCT ISLANDS                             {T.C = O(N*M), S.C = O(N*M)}
//USING DFS
//SIMILAR AS ABOVE, STORE ALL SHAPES IN VECTOR AND THEN IN SET(UNIQUE), RETURN SIZE OF SET(COUNT DISTINCT)
class Solution {
  public:
    vector<vector<int>>directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool isValid(int newRow, int newCol, int n, int m){
        return (newRow >= 0 && newRow < n && newCol >= 0 && newCol < m);
    }
    void dfs(vector<vector<int>>&grid, vector<vector<int>>&vis, int i, int j, vector<vector<int>>&shapes, int baseRow, int baseCol){
        int n = grid.size(), m = grid[0].size();
        vis[i][j] = 1;
        shapes.push_back({i-baseRow, j-baseCol});      //{{0,0},{0.1},{1,0},{1,1} == (0.0){3,3}-{3,3} , {3,4}-{3,3} (0, 1), {4,3}-{3,3}(1,0) , {4,4}-{3,3}(1,1) }
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


//309. IS GRAPH BIPARTITE                                   {T.C = O(V+E), S.C = O(V)}
/*
ODD LENGTH CYCLE  = NOT BIPARTITE
EVEN LENGTH CYCLE = BIPARTITE
LINEAR GRAPH      = BIPARTITE
*/
//USING DFS
//MARK VIS(-1 (1/0 USED FOR COLOR)), FILL  ADJACENT NODE WITH DIFF COLOR
class Solution {
public:
    bool dfsBipartite(vector<vector<int>>&adj, vector<int>&clr, int node, int currClr){
        clr[node] = currClr;                     //vis[node] = 1;
        for(auto it : adj[node]){
            if(clr[it] == -1){                    //not visited
                int newClr = 1-currClr;           //1 to 0 or 0 to 1 (changing color)
                if(!dfsBipartite(adj, clr, it, newClr)){
                    return false;
                }
            }else if(clr[it] == clr[node]){         //adjacent color cant same
                return false;
            }
        }
        return true;
    }
    bool isBipartite(vector<vector<int>>& graph) {       //graph = adjacencylist
        int n = graph.size();
        vector<int>clr(n, -1);                        //eg = red = 1, green = 0
        for(int i = 0 ;i < n ; i++){
            if(clr[i] == -1){                          //not visited
                if(!dfsBipartite(graph, clr, i, 1)){     //i = initial index, 1 = curr color(red)
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


//310. DIRECTED GRAPH CYCLE / DETECT CYCLE IN DIRECTED GRAPH      {T.C = O(V+E), S.C = O(V)}
//USING DFS
//USE VIS & DFSVIS (FOR BACKTRACK) , ELSE DETECT CYCLE CODE
class Solution {
  public:
    //using DFS
    bool isCyclicDFS(vector<int>adj[], vector<bool>&vis, vector<bool>&dfsVis, int node){
        vis[node] = true;
        dfsVis[node] = true;
        
        for(auto it : adj[node]){
            if(!vis[it]){
                if(isCyclicDFS(adj, vis, dfsVis, it)){
                    return true;
                }
            }else if(dfsVis[it]){                     //for undirected(it != parent(-1))
                return true;
            }
        }
        dfsVis[node] = false;                                //for next traversal reset it
        return false;
    }
    bool isCyclic(int V, vector<int> adj[]) {
        vector<bool>vis(V, 0);
        vector<bool>dfsVis(V, 0);
        
        //for disconnected components
        for(int i = 0 ; i < V ; i++){
            if(!vis[i] && isCyclicDFS(adj, vis, dfsVis, i)){      //i = nodeIndex
                return true;
            }
        }
        return false;
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


//TOPO SORT AND PROBLEMS-------------------------------------------------------------------------------
//311. TOPO SORT                                             {T.C = O(V+E), S.C = O(V)}
//LINEAR ORDERING OF VERTEX (U - V) THEN ALWAYS U COMES BEFORE V IN SORTING
//USING DFS (STACK)
//SIMPLE DFS JUST ADD ELEMENT IN STACK AFTER EVERTY TRAVERSAL OF ADJACENT NODE
class Solution
{
	public:
	void dfsTopoSort(vector<int>adj[], vector<int>&vis, stack<int>&stk, int node){
	    vis[node] = 1;
	    for(auto it : adj[node]){
	        if(!vis[it]){
	            dfsTopoSort(adj, vis, stk, it);
	        }
	    }
	    stk.push(node);                       //push backtrack node
	}
	vector<int> topoSort(int V, vector<int> adj[]) 
	{
	    //4 datastructures required = adjlist, vis, stack, ans
	    vector<int>ans;
	    vector<int>vis(V, 0);
	    stack<int>stk;
	    
	    for(int i = 0 ; i < V ; i++){      //for disconnected components
	        if(!vis[i]){
	            dfsTopoSort(adj, vis, stk, i);                //i = initial node
	        }
	    }
	    
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


//312. TOPO SORT / KAHN'S ALGO                                            {T.C = O(V+E), S.C = O(V)}
//LINEAR ORDERING OF VERTEX (U - V) THEN ALWAYS U COMES BEFORE V IN SORTING
//USING BFS (QUEUE)
//STORE INDEGREE OF ALL NODES, PUSH IN QUEUE (INDEGREE == 0), CALL BFS AND REDUCE INDEGREE WITH REMOVING ADJ NODE
class Solution
{
	public:
	vector<int> topoSort(int V, vector<int> adj[]) 
	{
	    //4 data structures required = adj, indegree, queue, ans
	    vector<int>ans;
	    vector<int>inDegree(V, 0);
	    
	    //calculate all indegrees for each node
	    for(int i = 0 ; i < V ; i++){
	        for(auto it : adj[i]){
	            inDegree[it]++;
	        }
	    }
	    
	    queue<int>q;
	    //push 0 indegree's nodes
	    for(int i = 0 ; i < V ; i++){
	        if(inDegree[i] == 0){
	            q.push(i);
	        }
	    }
	    
	    //do bfs
	    while(!q.empty()){
	        int frontNode = q.front();
	        q.pop();
	        ans.push_back(frontNode);
	        
	        //reduce indegree of ajacent nodes after disconnection of node
	        for(auto it : adj[frontNode]){
	            inDegree[it]--;
	            if(inDegree[it] == 0){
	                q.push(it);
	            }
	        }
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


//313. DIRECTED GRAPH CYCLE / DETECT CYCLE IN DIRECTED GRAPH      {T.C = O(V+E), S.C = O(V)}
//USING BFS
//USE TOPOLOGICAL SORT , INITIALIZE COUNT OF NODES IF COUNT == V (VALID TOPO {CYCLE NOT PRESENT}) 
//ELSE CYCLE PRESENT
class Solution {
  public:
    // Function to detect cycle in a directed graph.
    bool isCyclic(int V, vector<int> adj[]) {
        // 3 data structures required = adj, indegree, queue
        vector<int>inDegree(V, 0);
        
        //calculate all indegree's of each node
        for(int i = 0 ; i < V ; i++){
            for(auto it : adj[i]){
                inDegree[it]++;
            }
        }
        
        queue<int>q;
        //push 0 indegree's nodes in queue
        for(int i = 0 ; i < V ; i++){
            if(inDegree[i] == 0){
                q.push(i);
            }
        }
        
        int count = 0;
        //do bfs
        while(!q.empty()){
            int frontNode = q.front();
            q.pop();
            
            count++;
            
            //reduce indegree of adjacent nodes after disconnection of node
            for(auto it : adj[frontNode]){
                inDegree[it]--;
                if(inDegree[it] == 0){
                    q.push(it);
                }
            }
        }
        
        if(count == V){               //valid topological = not cycle
            return false;
        }
        return true;                  //invalid topological = cyclic
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


//314. COURSE SCHEDULE
//USING DFS                                                    {T.C = O(V+E), S.C = O(V)}
//DETECT CYCLE IF PRESENT (INVALID SCHEDULE), CYCLE NOT PRESENT (VALID SCHEDULE)
class Solution {
public:
    //simple find cycle is present of not (dfs) or use toposort(bfs) or (dfs)
    bool dfs(unordered_map<int,vector<int>>&adj, vector<int>&vis, vector<int>&dfsVis, int node){
        vis[node] = 1;
        dfsVis[node] = 1;
        for(auto it : adj[node]){
            if(!vis[it]){
                if(dfs(adj, vis, dfsVis, it) == true) return true;
            }else if(dfsVis[it] == true) return true;           //node visited and dfsVis so again same path or back edge found
        }
        dfsVis[node] = 0;                     //backtrack for other branches
        return false;
    }
    bool isCyclicDfs(int V, vector<vector<int>>&edges){
        unordered_map<int,vector<int>>adj;
        for(auto it : edges){
            int u = it[0];
            int v = it[1];

            adj[u].push_back(v);
        }
        vector<int>vis(V, 0);
        vector<int>dfsVis(V, 0);
        for(int i = 0 ;  i < V ; i++){         //for all components
            if(!vis[i] && dfs(adj, vis, dfsVis, i)) return true;;
        }
        return false;
    }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        return !isCyclicDfs(numCourses, prerequisites);  //cycle present(false{cant finish}, not present(true){can finish})
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


//315. COURSE SCHEDULE II                              
//USING DFS                                                    {T.C = O(V+E), S.C = O(V)}
//IN DFS FUNCTION PUSH NODE IN ANS AFTER TRAVERSAL
//DETECT CYCLE IF PRESENT (INVALID SCHEDULE), CYCLE NOT PRESENT (VALID SCHEDULE) 
//IF CYCLE RETURN {} ELSE RETURN ANS.
class Solution {
public:
    bool dfs(unordered_map<int, vector<int>>&adj, vector<int>&vis, vector<int>&dfsVis, int node, vector<int>&ans){
        vis[node] = 1;
        dfsVis[node] = 1;
        for(auto it : adj[node]){
            if(!vis[it]){
                if(dfs(adj, vis, dfsVis, it, ans)) return true;
            }else if(dfsVis[it] == true) return true;
        }
        dfsVis[node] = 0;
        ans.push_back(node);                   //just add this line for find valid path
        return false;
    }
    bool isCyclicDfs(int V, vector<vector<int>>&edges, vector<int>&ans){
        unordered_map<int,vector<int>>adj;
        for(auto it : edges){
            int u = it[0];
            int v = it[1];

            adj[u].push_back(v);
        }
        vector<int>vis(V, 0);
        vector<int>dfsVis(V, 0); 
        for(int i = 0 ; i < V ; i++){           //disconnected components
            if(!vis[i] && dfs(adj, vis, dfsVis, i, ans)) return true;
        }
        return false;
    }
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int>ans;
        if (isCyclicDfs(numCourses, prerequisites, ans)) return {};
        return ans;
    }
};
/*
Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: [0,1]
Explanation: There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1].
Example 2:

Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
Output: [0,2,1,3]
Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0.
So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3].
Example 3:

Input: numCourses = 1, prerequisites = []
Output: [0]
*/


//316. FIND EVENTUAL SAFE STATES                             {T.C = O(V+E), S.C = O(V)}
//USING DFS
//FIND CYCLE IN GRAPH, AND PUSH NON CYCLIC ELEMENT IN ANS.
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
        dfsVis[node] = 0;                          //backtrack
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


//317. ALIEN DICTIONARY                                           {T.C = O(V*L+E), S.C = O(V)}
//USING BFS (TOPO SORT)
//FIRST CREATE ADJ LIST , THEN SIMPLE TOPOSORT AND STORE ANS 
class Solution{
    public:
    vector<int>topoSort(int V , unordered_map<int, vector<int>>&adj){
        vector<int>ans;
        vector<int>inDegree(V, 0);
        
        //calculate indegrees for each nodes
        for(int i = 0 ; i < V ; i++){
            for(auto it : adj[i]){
                inDegree[it]++;
            }
        }
        
        queue<int>q;
        //push 0 indegree's in queue
        for(int i = 0 ; i < V ; i++){
            if(inDegree[i] == 0){
                q.push(i);
            }
        }
        
        //do dfs
        while(!q.empty()){
            int frontNode = q.front();
            q.pop();
            ans.push_back(frontNode);
            
            //reduce indegree of adjacent nodes after disconnection of node
            for(auto it : adj[frontNode]){
                inDegree[it]--;
                if(inDegree[it] == 0){
                    q.push(it);
                }
            }
        }
        return ans;
    }
    string findOrder(string dict[], int n, int k) {
        
        //create adjacency list
        unordered_map<int,vector<int>>adj;
        for(int i = 0 ; i < n-1 ; i++){             //compare till second last elemenent is possible
            string s1 = dict[i];
            string s2 = dict[i+1];
            int len = min(s1.size(), s2.size());    //compare till small string length
            for(int j = 0 ; j < len ; j++){
                if(s1[j] != s2[j]){                 //if char match skip
                    int u = s1[j]-'a';
                    int v = s2[j]-'a';
                    
                    adj[u].push_back(v);             //u before v (u -> v)
                    break;
                }
            }
        }
        
        vector<int>topo = topoSort(k, adj);          //no. of v is k not n
        string ans = "";
        for(auto it : topo){
            ans = ans + char(it + 'a');
        }
        return ans;
    }
};
/*
Example 1:
Input: 
N = 5, K = 4
dict = {"baa","abcd","abca","cab","cad"}
Output:
1
Explanation:
Here order of characters is 
'b', 'd', 'a', 'c' Note that words are sorted 
and in the given language "baa" comes before 
"abcd", therefore 'b' is before 'a' in output.
Similarly we can find other orders.

Example 2:
Input: 
N = 3, K = 3
dict = {"caa","aaa","aab"}
Output:
1
Explanation:
Here order of characters is
'c', 'a', 'b' Note that words are sorted
and in the given language "caa" comes before
"aaa", therefore 'c' is before 'a' in output.
Similarly we can find other orders.
*/


//SHORTEST PATH ALGORITHM AND PROBLEMS-----------------------------------------------------------------------
//DIJKSTRA COMPLEXITY
/*
Time Complexity: 𝑂((𝑉+𝐸)log⁡𝑉)
Building the adjacency list: 𝑂(𝐸)
Dijkstra's algorithm: 𝑂((𝑉+𝐸)log⁡𝑉)
Finding the maximum distance: 𝑂(𝑉)
The dominant term is 𝑂((𝑉+𝐸)log⁡𝑉)
O((V+E)logV), 
so the overall time complexity is 𝑂((𝑉+𝐸)log⁡𝑉)

Space Complexity: 𝑂(𝑉+𝐸)
Adjacency list: 𝑂(𝑉+𝐸)
Priority queue: 𝑂(𝑉)
Distance array: 𝑂(𝑉)
Combining these, the overall space complexity is 
𝑂(𝑉+𝐸).
*/
//318. SHORTEST PATH IN UNDIRECTED GRAPH                        {T.C = O(V+E), S.C = O(V+E)}
//WEIGHT OF ALL EDGES IS 1
//USING BFS FOR UNIFORM EDGE WEIGHT (SIMILAR TO DIJKSTRA BUT NOT)
class Solution {
  public:
    vector<int>dijkstraQueue(unordered_map<int,vector<int>>&adj, int V, int src){
        queue<int>q;                                      
        vector<int>minDis(V, 1e9);  //or INT_MAX        //ans(minDis from src to all nodes)
        q.push(src);
        minDis[src] = 0;                                  //distance is 0 for ownself
        
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            for(auto it : adj[frontNode]){
                if(minDis[frontNode] + 1 < minDis[it]){
                    minDis[it] = minDis[frontNode]+1;
                    q.push(it);
                }
            }
        }
        
        vector<int>ans(V, -1);                //in place of INT_MAX insert -1
        for(int i = 0 ; i < V ; i++){
            if(minDis[i] != 1e9) ans[i] = minDis[i];
        }
        return ans;
    }
    vector<int> shortestPath(vector<vector<int>>& edges, int N,int M, int src){
        unordered_map<int,vector<int>>adj;
        for(auto it : edges){
            int u = it[0];
            int v = it[1];
            
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        return dijkstraQueue(adj, N, src);
    }
};
/*
Example1:
Input:
n = 9, m= 10
edges=[[0,1],[0,3],[3,4],[4,5],[5,6],[1,2],[2,6],[6,7],[7,8],[6,8]] 
src=0
Output:
0 1 2 1 2 3 3 4 4

Example2:
Input:
n = 4, m= 4
edges=[[0,0],[1,1],[1,3],[3,0]] 
src=3
Output:
1 1 -1 0
*/


//319. SHORTEST PATH IN DIRECTED ACYCLIC GRAPH                    
//USING BFS(SIMILAR TO DIJKSTRA)   {NOT OPTIMALL FOR VARIABLE WEIGHTED GRAPHS}  {T.C = O(V+E), S.C = O(V+E)}
//SIMILAR TO ABOVE , JUST CHANGE THE FORMATE OF ADJACENCY {U, {V, W}} OR {U -> V,W}
class Solution {
  public:
    typedef pair<int,int>P;
    vector<int>dijkstraQueue(unordered_map<int,vector<P>>&adj, int V, int src){
        vector<int>minDis(V, 1e9);
        queue<int>q;
        q.push(src);
        minDis[src] = 0;                              //own distance is 0 always
        
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            for(auto it : adj[frontNode]){
                int d = it.second;
                int u = it.first;
                if(minDis[frontNode] + d < minDis[u]){
                    minDis[u] = minDis[frontNode] + d;
                    q.push(u);
                }
            }
        }
        vector<int>ans(V, -1);
        for(int i = 0 ; i < V ; i++){
            if(minDis[i] != 1e9) ans[i] = minDis[i];
        }
        return ans;
    }
    vector<int> shortestPath(int N,int M, vector<vector<int>>& edges){
        unordered_map<int,vector<P>>adj;
        for(auto it : edges){
            int u = it[0];
            int v = it[1];
            int d = it[2];
            
            adj[u].push_back({v, d});
            // adj[v].push_back({u, d});       //for undirected
        }
        return dijkstraQueue(adj, N, 0);           //0 = source
    }
};

//USING DIJKSTRA (OPTIMAL APPROACH FOR VARIABLE WEIGHTED GRAPH)    {T.C = O((V+E)LOGV), S.C = O(V+E)}
class Solution {
public:
    typedef pair<int, int> P;

    vector<int> dijkstra(unordered_map<int, vector<P>>& adj, int V, int src) {
        // Priority queue to select the node with the minimum distance
        priority_queue<P, vector<P>, greater<P>> pq; // Min-heap
        vector<int> minDis(V, INT_MAX);              // Distance from source to each vertex
        pq.push({0, src});                           // {distance, node}
        minDis[src] = 0;                             // Distance to the source is 0

        while (!pq.empty()) {
            auto topNode = pq.top();
            pq.pop();
            int dist = topNode.first;
            int node = topNode.second;
            
            for (auto it : adj[node]) {              // For each adjacent node
                int d = it.second;                   //keep in mind d is second not first
                int u = it.first;
                if (dist + d < minDis[u]) {  // If a shorter path to adjNode is found
                    minDis[u] = dist + d;
                    pq.push({minDis[u], u});
                }
            }
        }

        // Replace INT_MAX with -1 for unreachable nodes
        for (int i = 0; i < V; i++) {
            if (minDis[i] == INT_MAX) minDis[i] = -1;
        }

        return minDis;
    }

    vector<int> shortestPath(int N, int M, vector<vector<int>>& edges) {
        unordered_map<int, vector<P>> adj;
        for (auto it : edges) {
            int u = it[0];
            int v = it[1];
            int d = it[2];

            adj[u].push_back({v, d});
            // adj[v].push_back({u, d}); // Uncomment for undirected graph
        }
        return dijkstra(adj, N, 0); // 0 = source
    }
};
/*
Example1:
Input:
N = 4, M = 2
edge = [[0,1,2],[0,2,1]]
Output:
0 2 1 -1
Explanation:
Shortest path from 0 to 1 is 0->1 with edge weight 2. 
Shortest path from 0 to 2 is 0->2 with edge weight 1.
There is no way we can reach 3, so it's -1 for 3.

Example2:
Input:
N = 6, M = 7
edge = [[0,1,2],[0,4,1],[4,5,4],[4,2,2],[1,2,3],[2,3,6],[5,3,1]]
Output:
0 2 3 6 1 5
Explanation:
Shortest path from 0 to 1 is 0->1 with edge weight 2. 
Shortest path from 0 to 2 is 0->4->2 with edge weight 1+2=3.
Shortest path from 0 to 3 is 0->4->5->3 with edge weight 1+4+1=6.
Shortest path from 0 to 4 is 0->4 with edge weight 1.
Shortest path from 0 to 5 is 0->4->5 with edge weight 1+4=5.
*/


//320. DIJKSTRA  ALGORITHM                                    {T.C = O((V+E)LOGV), S.C = O(V+E)}
//SIMPLE USING ALGO (PRIORITY QUEUE AND MINDIS VECTOR)
class Solution
{
	public:
	typedef pair<int,int>P;
    vector <int> dijkstra(int V, vector<vector<int>> adj[], int src)
    {
        priority_queue<P, vector<P>, greater<P>>pq;       //minHeap
        vector<int>minDis(V, INT_MAX);
        pq.push({0, src});                               //src itself dis 0
        minDis[src] = 0;
        while(!pq.empty()){
            auto topNode = pq.top();
            pq.pop();
            int dist = topNode.first;
            int node = topNode.second;
            for(auto it : adj[node]){
                int u = it[0];                         //currNode is first in adj not second
                int d = it[1];
                if(dist+d < minDis[u]){
                    minDis[u] = dist+d;
                    pq.push({minDis[u], u});           //currdis, currNode
                }
            }
        }
        return minDis;
    }
};
/*
Example 1:
Input:
V = 2
adj [] = {{{1, 9}}, {{0, 9}}}
S = 0
Output:
0 9
Explanation:
The source vertex is 0. Hence, the shortest 
distance of node 0 is 0 and the shortest 
distance from node 1 is 9. 

Example 2:
Input:
V = 3, E = 3
adj = {{{1, 1}, {2, 6}}, {{2, 3}, {0, 1}}, {{1, 3}, {0, 6}}}
S = 2
Output:
4 3 0

Explanation:
For nodes 2 to 0, we can follow the path-
2-1-0. This has a distance of 1+3 = 4,
whereas the path 2-0 has a distance of 6. So,
the Shortest path from 2 to 0 is 4.
The shortest distance from 0 to 1 is 1 .
*/


//321. SHORTEST PATH IN WEIGHTED UNDIRECTED GRAPH                      {T.C = O((V+E)*LOGV), S.C = O(V)}
/*
Take an minheap, minDisWt vector initialize source with 0, push element in pq(heap) {s, 0} , while pq not empty
pop element, for(auto it : adj[node]{pq.top().first}) check if curr Weight/dist is smaller then push that in pq.
Take an path vector base check if distination not reached return -1, else check untill parent[node] != node, push the node
in path and update node to parent[node] and finally reverse and return path vector.
*/
class Solution {
  public:
    vector<int> shortestPath(int n, int m, vector<vector<int>>& edges) {
        unordered_map<int, vector<pair<int, int>>> adj;
        for(auto &it : edges) {
            int u = it[0];
            int v = it[1];
            int w = it[2];
            
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> minDisWt(n+1, INT_MAX);
        vector<int> parent(n+1);
        
        for(int i = 1; i<=n; i++) {                          //initialize parent vector of each node with itself
            parent[i] = i;
        }
        
        minDisWt[1] = 0;
		pq.push({1, 0});

		while(!pq.empty()) {

		    int node = pq.top().first;
		    int dW  = pq.top().second;
		    pq.pop();
		    for(auto it : adj[node]) {

    			int u = it.first;
    			int w = it.second;
    
    			if(dW+ w < minDisWt[u]) {
    			    minDisWt[u] = dW + w;
    			    pq.push({u, minDisWt[u]});
    			    parent[u] = node;
    			}
		    }
		}

        vector<int> path;
        int node = n;
        
        //base check {not reach to destination}
        if(minDisWt[node] == INT_MAX){   
            return {-1};
        }
        while(parent[node] != node) {
            path.push_back(node);
            node = parent[node];
        }
        path.push_back(1);
        reverse(begin(path), end(path));
		return path;
    }
};
/*
Input:
n=5, m = 6
edges = [[1, 2,,2], [2, 5, 5], [2, 3, 4], [1, 4, 1], [4, 3, 3], [3, 5, 1]]
Output:
1 4 3 5
Explaination
Shortest path from 1 to n is by the path 1 4 3 5
*/


//322. SHORTEST PATH IN BINARY MATRIX (2D)                     {T.C = O(N*M), S.C = O(N*M)}
//USING BFS
//LELVEL WISE TRAVERSAL , VIS (MARK 0 TO 1 (COORDINATES)), RETURN STEPS(+1) {COUNT INITIAL ZERO}
class Solution {
public:
    vector<vector<int>>directions = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}}; //8 directions
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int steps = 1;                   //count initial zero
        int n = grid.size();             //m == n

        //base case
        if(n == 0 || grid[0][0] != 0){                  //only on 0 traversal
            return -1;
        }

        auto isSafe = [&](int x, int y){                 //check for boundary condition
            return (x >= 0 && x < n && y >= 0 && y < n);
        };
        //BFS
        queue<pair<int, int>>q;
        grid[0][0] = 1;                          //vis[node] = 1 {same as}
        q.push({0, 0});                       //q.push(node) == q.push{coordinates}
        while(!q.empty()){
            int sz = q.size();
            while(sz--){                        //level wise traversal
                auto frontNode = q.front();
                q.pop();
                int x = frontNode.first;
                int y = frontNode.second;

                if(x == n-1 && y == n-1){       //reached at end
                    return steps;            //+1 for count of zeroes
                }

                for(auto dir : directions){
                    int newX = x + dir[0];
                    int newY = y + dir[1];

                    if(isSafe(newX, newY) && grid[newX][newY] == 0){
                        q.push({newX, newY});                         //q.push(it)
                        grid[newX][newY] = 1;                            //vis[it] = 1
                    }
                }
            }
            steps++;
        }
        return -1;                                     //cant reach end
    }
};

//USING DIJKSTRA                                             {T.C = O(N^2LOGN), S.C = O(N^2)}
class Solution {
public:
    typedef pair<int,pair<int,int>>P;
    vector<vector<int>>directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, 1}, {-1, -1}, {1, -1}};
    bool isValid(int newX, int newY, int n){
        return (newX >= 0 && newX < n && newY >= 0 && newY < n);
    }
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();           //n == m
        //base case
        if(n == 0 || grid[0][0] != 0) return -1;
        
        priority_queue<P, vector<P>, greater<P>>pq;
        vector<vector<int>>minDis(n, vector<int>(n, INT_MAX));
        pq.push({0, {0, 0}});                   //distance , {coordinates(x, y)}
        minDis[0][0] = 0;
        while(!pq.empty()){
            auto topNode = pq.top();
            pq.pop();
            int dist = topNode.first;
            int x    = topNode.second.first;
            int y    = topNode.second.second;
            for(auto it : directions){
                int newX = x + it[0];
                int newY = y + it[1];
                int d    = 1;

                if(isValid(newX, newY, n) && dist + d < minDis[newX][newY] && grid[newX][newY] == 0){
                    pq.push({dist+d, {newX, newY}});
                    minDis[newX][newY] = dist + d;
                }
            }
        }

        return minDis[n-1][n-1] == INT_MAX ? -1 : minDis[n-1][n-1] + 1;    //total 0 = count of steps + 1
    }
};
/*
Example 1:
Input: grid = [[0,1],[1,0]]
Output: 2

Example 2:
Input: grid = [[0,0,0],[1,1,0],[1,1,0]]
Output: 4

Example 3:
Input: grid = [[1,0,0],[1,1,0],[1,1,0]]
Output: -1
*/


//323. PATH WITH MINIMUM EFFORTS                            {T.C = O(N^2), S.C = O(N^2)}
//USING DIJAKSTRA (2D) {DIST => DIFF(H(X,Y)-H(x,y))}
class Solution {
public:
    typedef pair<int,pair<int,int>>P;
    vector<vector<int>>directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool isValid(int newRow, int newCol, int n, int m){
        return (newRow >= 0 && newRow < n && newCol >= 0 && newCol < m);
    }
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size(), m = heights[0].size();
        priority_queue<P, vector<P>, greater<P>>pq;          //minHeap
        vector<vector<int>>minDis(n, vector<int>(m, INT_MAX));
        pq.push({0, {0, 0}});                      //dis, {x, y}  //dis = height difference
        minDis[0][0] = 0;
        
        while(!pq.empty()){
            auto topNode = pq.top();
            pq.pop();
            int diff = topNode.first;
            int x    = topNode.second.first;
            int y    = topNode.second.second;

            if(x == n-1 && y == m-1) return diff;

            for(auto it : directions){
                int newX = x + it[0];
                int newY = y + it[1];
                if(isValid(newX, newY, n, m)){
                    int absDiff = abs(heights[newX][newY]-heights[x][y]);
                    int newDiff = max(diff, absDiff);
                    if(newDiff < minDis[newX][newY]){
                        minDis[newX][newY] = newDiff;
                        pq.push({minDis[newX][newY], {newX, newY}});
                    }
                } 
            }
        }

        return minDis[n-1][m-1];
    }
};
/*
Example 1:
Input: heights = [[1,2,2],
                  [3,8,2],
                  [5,3,5]]
Output: 2
Explanation: The route of [1,3,5,3,5] has a maximum absolute difference of 2 in consecutive cells.
This is better than the route of [1,2,2,2,5], where the maximum absolute difference is 3.

Example 2:
Input: heights = [[1,2,3],
                  [3,8,4],
                  [5,3,5]]
Output: 1
Explanation: The route of [1,2,3,4,5] has a maximum absolute difference of 1 in consecutive cells, which is better than route [1,3,5,3,5].

Example 3:
Input: heights = [[1,2,1,1,1],
                  [1,2,1,2,1],
                  [1,2,1,2,1],
                  [1,2,1,2,1],
                  [1,1,1,2,1]]
Output: 0
Explanation: This route does not require any effort.
*/


//324. CHEAPEST FLIGHT WITHIN K STOPS                            {T.C = O(V+E), S.C = O(V+E)}
//USING BFS
//DIJKSTRA IS FAIL (IT FINDS SHORTEST PATH WITHOUT CARE OF STOPS), IN BFS IF STOPS > K (IGNORE THAT PATH)
class Solution {
public:
    typedef pair<int,int>P;
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        unordered_map<int,vector<P>>adj;

        for(auto it : flights){
            adj[it[0]].push_back({it[1] ,it[2]});             //u = 0, v = 1, d = 2
        }

        //BFS on basis of stops                           //dijakstra will fail
        queue<pair<int,P>>q;                 //stops,{node, dist}
        q.push({0, {src, 0}});
        vector<int>minPrice(n, INT_MAX);
        minPrice[src] = 0;

        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            int stops = frontNode.first;
            int node = frontNode.second.first;
            int dist = frontNode.second.second;

            if(stops > k){                                //ignore path which exceed stops (not in dijkstra)
                continue;
            }
            for(auto it : adj[node]){         //node not frontNode
                int v = it.first;
                int d = it.second;

                if(dist + d < minPrice[v] && stops <= k){
                    minPrice[v] = dist + d;
                    q.push({stops + 1, {v, dist+d}});
                }
            }
        }
        if(minPrice[dst] == INT_MAX) return -1;

        return minPrice[dst];
    }
};
/*
Example 1:
Input: n = 4, flights = [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]], src = 0, dst = 3, k = 1
Output: 700
Explanation:
The graph is shown above.
The optimal path with at most 1 stop from city 0 to 3 is marked in red and has cost 100 + 600 = 700.
Note that the path through cities [0,1,2,3] is cheaper but is invalid because it uses 2 stops.

Example 2:
Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 1
Output: 200
Explanation:
The graph is shown above.
The optimal path with at most 1 stop from city 0 to 2 is marked in red and has cost 100 + 100 = 200.

Example 3:
Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 0
Output: 500
Explanation:
The graph is shown above.
The optimal path with no stops from city 0 to 2 is marked in red and has cost 500.
*/


//325. NETWORK DELAY TIME                                             {T.C = ((V+E)LOGV), S.V = O(V+E)}
//USING DIJKASTRA 
//SIMPLE DIJKASTRA (SOURCE == K), THEN FIND MAX VALUE OF MINDIS VECTOR (GIVES SMALLEST TIME TO REACH ALL NODES)
class Solution {
public:
    typedef pair<int,int>P;
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {  //k = source node
        unordered_map<int , vector<P>>adj;
        for(auto it : times){
            int u = it[0];
            int v = it[1];
            int d = it[2];
            
            adj[u].push_back({v, d});
        }

        priority_queue<P, vector<P>, greater<P>>pq; //{node, dist or time}
        vector<int>minDis(n+1, INT_MAX);           //n+1 nodes from 1 not 0
        minDis[k] = 0;                             //initialize source node
        pq.push({0 , k});
        while(!pq.empty()){
            auto topNode = pq.top();
            int dist = topNode.first;
            int node = topNode.second;
            pq.pop();
            for(auto it : adj[node]){
                int u = it.first;
                int d = it.second;
                if(dist+d < minDis[u]){
                    minDis[u] = dist+d;
                    pq.push({u, minDis[u]});
                }
            }
        }

        int maxi = INT_MIN;                              //Shortest time to reach all nodes is max dis
        for(int i = 1 ; i <= n ; i++){                   //node start from 1 not 0
            maxi = max(maxi, minDis[i]);
        }

        return maxi == INT_MAX ? -1 : maxi;             //INT_MAX (the node is not updated)
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


//326. NUMBER OF WAYS TO ARRIVE AT DESTINATION                  {T.C = O((V+E)LOGV), S.C = O(V+E)}
//USING DIJKSTRA
//JUST USE WAYS VECTOR TO STORE WAYS (AGAIN ARRIVING) ,AND RETURN WAYS OF DEST.
class Solution {
  public:
    int mod = 1e9+7;
    typedef long long ll;
    typedef pair<ll, int>P;
    int countPaths(int n, vector<vector<int>>& roads) {
        unordered_map<int, vector<P>>adj;
        for(auto it : roads){
            adj[it[0]].push_back({it[1], it[2]});         //0 = u, 1 = v , 2 = d
            adj[it[1]].push_back({it[0], it[2]});         
        }
        priority_queue<P, vector<P>, greater<P>>pq;
        vector<ll>minDis(n, LLONG_MAX);                      //INT_MAX not work (big constraints)
        vector<ll>ways(n, 0);                            //count ways src to dst
        pq.push({0, 0});                                  //dist, src
        minDis[0] = 0; 
        ways[0] = 1;                                      //initial ways = 1
        
        while(!pq.empty()){
            auto topNode = pq.top();
            pq.pop();
            ll dist = topNode.first;
            int node = topNode.second;
            for(auto it : adj[node]){                    
                int u = it.first;
                ll d = it.second;
                if(dist+d < minDis[u]){                    //first time arriving
                    minDis[u] = dist+d;
                    pq.push({dist+d, u});
                    ways[u] = ways[node];
                }else if(dist+d == minDis[u]){             //again arriving via path
                    // ways[u] += ways[node];                 //add paths ways
                    ways[u] = (ways[u]+ways[node]) % mod;
                }
            }
        }
        
        return ways[n-1] % mod;                                  //destination total ways
    }
};
/*
Example 1:
Input:
n=7, m=10
edges= [[0,6,7],[0,1,2],[1,2,3],[1,3,3],[6,3,3],[3,5,1],[6,5,1],[2,5,1],[0,4,5],[4,6,2]]
Output:
4
Explaination:
The four ways to get there in 7 minutes are:
- 0  6
- 0  4  6
- 0  1  2  5  6
- 0  1  3  5  6
 

Example 2:
Input:
n=6, m=8
edges= [[0,5,8],[0,2,2],[0,1,1],[1,3,3],[1,2,3],[2,5,6],[3,4,2],[4,5,2]]
Output:
3

Explaination:
The three ways to get there in 8 minutes are:
- 0  5
- 0  2  5
- 0  1  3  4  5
*/


//327. MINIMUM MULTIPLICATION TO REACH END                        
//USING BFS (DIJKSTRA WILL ALSO WORKS)                           {T.C = O(N*M(1000000), S.C = O(N))}
//SIMILAR TO DIJKASTRA BUT WITHOUT PQ, USE QUEUE, NEWNODE = (IT*NODE)
class Solution {
  public:
    typedef pair<int,int>P;
    int minimumMultiplications(vector<int>& arr, int start, int end) {
        int mod = 100000;
        queue<P>q;                                    //dijakstra will also work(no need in this)
        vector<int>minDist(100000, INT_MAX);          //n = 0 to 9999 (100000)
        
        q.push({0, start});                          
        minDist[start] = 0;
        //base case
        if(start == end) return 0;
        
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            int dist = frontNode.first;
            int node = frontNode.second;
            for(auto it : arr){
                int u = (it * node) % mod;              //u == num
                if(dist + 1 < minDist[u]){
                    minDist[u] = dist+1;
                    q.push({dist+1, u});
                    if(u == end) return dist+1;    //1 for curr node
                }
            }
        }
        return -1;                                    //cant form end number
    }
};
/*
Example 1:
Input:
arr[] = {2, 5, 7}
start = 3, end = 30
Output:
2
Explanation:
Step 1: 3*2 = 6 % 100000 = 6 
Step 2: 6*5 = 30 % 100000 = 30

Example 2:
Input:
arr[] = {3, 4, 65}
start = 7, end = 66175
Output:
4
Explanation:
Step 1: 7*3 = 21 % 100000 = 21 
Step 2: 21*3 = 63 % 100000 = 63 
Step 3: 63*65 = 4095 % 100000 = 4095 
Step 4: 4095*65 = 266175 % 100000 = 66175
*/


//328. DISTANCE FROM THE SOURCE (BELLMAN-FORD ALGORITHM)     {T.C = O(V*E), S.C = O(V)}
//USING BELLMANFORD ALGO
//2 LOOP 1ST(0 TO V), 2ND(EDGES REST {SIMILAR TO DIJKSTRA}), AGAIN 2ND LOOP OUTER FOR CHECK CYCLE.
class Solution {
  public:
    vector<int> bellman_ford(int V, vector<vector<int>>& edges, int S) {
        vector<int>minDis(V, 1e8);
        minDis[S] = 0;                             //initial distance = 0
        for(int i = 0 ; i < V ; i++){                //rest (V-1) times
            for(auto it : edges){
                int u = it[0];
                int v = it[1];
                int w = it[2];
                
                if(minDis[u] != 1e8 && minDis[u]+w < minDis[v]){
                    minDis[v] = minDis[u] + w;
                }
            }
        }
        
        //checking extra time for negative cycle
        for(auto it : edges){
            int u = it[0];
            int v = it[1];
            int w = it[2];
            
            if(minDis[u] != 1e8 && minDis[u]+w < minDis[v]){
                return {-1};
            }
        }
        
        return minDis;
    }
};
/*
Example 1:
Input:
E = [[0,1,9]]
S = 0
Output:
0 9
Explanation:
Shortest distance of all nodes from
source is printed.

Example 2:
Input:
E = [[0,1,5],[1,0,3],[1,2,-1],[2,0,1]]
S = 2
Output:
1 6 0
Explanation:
For nodes 2 to 0, we can follow the path-
2-0. This has a distance of 1.
For nodes 2 to 1, we cam follow the path-
2-0-1, which has a distance of 1+5 = 6,
*/


//329. FLOYD WARSHALL                                                 {T.C = O(N^3), S.C = O(1)}
//Brute force algo (MINDIS OF EACH NODE TO EACH NODE)
//Three loops (k , i , j) take mindis = min(mindis[i][j], minDis[i][k]+minDis[k][j])
class Solution {
  public:
	void shortest_distance(vector<vector<int>>&matrix){
	    int n = matrix.size();
	    
	    //creating a matrix with update -1 to 1e9
	    for(int i = 0 ; i < n ; i++){
	        for(int j = 0 ; j < n ; j++){
	            if(matrix[i][j] == -1){
	                matrix[i][j] = 1e9;
	            }
	            if(i == j){                          //self distance
	                matrix[i][j] = 0;
	            }
	        }
	    }
	    
	    //traverse all graph via a node     (bellman logic (k, i, j))
	    for(int k = 0 ; k < n ; k++){
	        for(int i = 0 ; i < n ; i++){
	            for(int j = 0 ; j < n ; j++){
	                matrix[i][j] = min(matrix[i][j], matrix[i][k]+matrix[k][j]);
	            }
	        }
	    }
	    
	    //reset the matrix 1e9 TO -1
	    for(int i = 0 ; i < n ; i++){
	        for(int j = 0 ; j < n ; j++){
	            if(matrix[i][j] == 1e9){
	                matrix[i][j] = -1;
	            }
	        }
	    }
	}
};
/*
Input: matrix = [[0, 25],[-1, 0]]
Output: [[0, 25],[-1, 0]]
Explanation: The shortest distance between every pair is already given(if it exists).

Input: matrix = [[0, 1, 43],[1, 0, 6],[-1, -1, 0]]
Output: [[0, 1, 7],[1, 0, 6],[-1, -1, 0]]
Explanation: We can reach 2 from 0 as 0->1->2 and the cost will be 1+6=7 which is less than 43.
*/


//330. FIND THE CITY WITH THE SMALLEST NUMBER OF NEIGHBORS AT A THRESHOLD DISTANCE   {T.C = O(N^2*LOGN), S.C = O(N^2)}                     
//USING DIJAKSTRA FOR EACH NODE (FIND MINDIST) OR USE FLOYD WARSHALL
class Solution {
public:
    typedef pair<int,int>P;
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        unordered_map<int,vector<P>>adj;
        for(auto it:edges){
            adj[it[0]].push_back({it[1],it[2]});
            adj[it[1]].push_back({it[0],it[2]});                   //bidirectional edges
        }
        
        int cityNum = INT_MAX;
        int minCityCount = INT_MAX;
        
        priority_queue<P,vector<P>,greater<P>>pq;

        for(int i=0;i<n;i++)                                     //FOR CALLING DIJKASTRA FOR EACH NODE
        {
            vector<int> minDist(n,INT_MAX);
            pq.push({0,i});                                      //0 = dist, i = src
            minDist[i]=0;
            while(!pq.empty()){
                auto topNode = pq.top();
                pq.pop();
                int dist = topNode.first;
                int node = topNode.second;

                for(auto it: adj[node]){
                    int u =it.first;
                    int d =it.second;
                    if(dist + d < minDist[u]){
                        minDist[u] = dist + d;
                        pq.push({minDist[u],u});
                    }
                }
            }

            int count=0;
            for(int j=0;j<n;j++)
            {
                if(minDist[j]<=distanceThreshold)
                    count++;
            }
            if(count<=minCityCount)
            {
                minCityCount=count;
                cityNum = i;
            }
        }

        return cityNum;
    }
};
/*
Example 1:
Input: n = 4, edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]], distanceThreshold = 4
Output: 3
Explanation: The figure above describes the graph. 
The neighboring cities at a distanceThreshold = 4 for each city are:
City 0 -> [City 1, City 2] 
City 1 -> [City 0, City 2, City 3] 
City 2 -> [City 0, City 1, City 3] 
City 3 -> [City 1, City 2] 
Cities 0 and 3 have 2 neighboring cities at a distanceThreshold = 4, but we have to return city 3 since it has the greatest number.

Example 2:
Input: n = 5, edges = [[0,1,2],[0,4,8],[1,2,3],[1,4,2],[2,3,1],[3,4,1]], distanceThreshold = 2
Output: 0
Explanation: The figure above describes the graph. 
The neighboring cities at a distanceThreshold = 2 for each city are:
City 0 -> [City 1] 
City 1 -> [City 0, City 4] 
City 2 -> [City 3, City 4] 
City 3 -> [City 2, City 4]
City 4 -> [City 1, City 2, City 3] 
The city 0 has 1 neighboring city at a distanceThreshold = 2.
*/


//MINIMUM SPANNING TREES / DISJOINT SETS AND UNION-----------------------------------------------------
//331. MINIMUM SPANNING TREE 
//THEORY
//TREE IN WHICH (N) NODES & (N-1) EDGES & ALL NODES REACHABLE EACH OTHER


//332. MINIMUM SPANNING TREE (PRIM'S ALGORITHM)                    {T.C = O(ELOGV), S.C = O(E+V)(for adj list)}
//INTERMEDIATE NODE IS CONNECTED ALWAYS 
//TAKE MINHEAP, VIS(BOOL), SUM(TOTAL MINIMUM WT OF MST), WHILE PQ IF VIS[NODE] CONTINUE(SKIP) ELSE ITERATE
//NOT MARK VIS INSIDE THE FOR EACH LOOP (LIKE DIJKSTRA, BFS AND ALL)
class Solution
{
	public:
	//PRIM'S ALGORITHM
	typedef pair<int,int>P;
    int spanningTree(int V, vector<vector<int>> adj[])
    {
        priority_queue<P, vector<P>, greater<P>>pq;
        vector<bool>vis(V, false);
        pq.push({0, 0});                          //{dist, node}  //parent when find mst (not tatal dist)
        
        int sum = 0;
        
        while(!pq.empty()){
            auto topNode = pq.top();
            pq.pop();
            int dist = topNode.first;
            int node = topNode.second;
            
            if(vis[node] == true) continue;      //skip already vis node
            vis[node] = true;                     //vis only when insert in mst not in every iteration
            sum += dist;
            
            for(auto it : adj[node]){
                int v = it[0];
                int d = it[1];
                if(!vis[v]){
                    pq.push({d, v});
                }
            }
        }
        return sum;
    }
};
/*
Example 1:
Input:
3 3
0 1 5
1 2 3
0 2 1
Output:
4
Explanation:
The Spanning Tree resulting in a weight
of 4 is shown above.

Example 2:
Input:
2 1
0 1 5
Output:
5
Explanation:
Only one Spanning Tree is possible
which has a weight of 5.
*/


//333. DISJOINT SET (GENERAL)                                {T.C = O(CONSTANT), S.C = O(1)}
int find(int parent[],int i){                       //i = node
    if(i == parent[i]) return i;
    
    return parent[i] = find(parent, parent[i]);     //rank & path compression (store ans in parent[i])
}
void unionSet(int parent[],int x,int y){            //union by rank
    int xParent = find(parent, x);
    int yParent = find(parent, y);
    
    if(xParent == yParent) return;             //belong to same set
    
    parent[xParent] = y;
}
/*
/*
Input:
N = 5, K = 4
queries[] = {{find 4},
             {find 1},
             {unionSet 3 1},
             {find 3}}
Output:
4 1 1
Explanation:
1. The parent of 4 is 4. Hence the output is 4.
2. The parent of 1 is 1. Hence the output is 1.
3. After performing unionSet 3 1, parent of 3 becomes 1,
   since, parent of 1 is currently 1 itself.
4. The parent of 3 is now 1. Hence, the output is 1.
*/


//333. DISJOINT SET (UNION BY RANK)                          {T.C = O(ALPHA OR CONSTANT), S.C = O(1)}
//TAKE RANK & PARENT(GLOBAL) , INITIALIZE RANK(N, 0), PARENT(FOR LOOP FOR PARENT OF SELF).
//SMALLER LENGTH GRAPH CONNECT TO LARGER LEN GRAPH (FOR AVOID INCREASING HEIGHT OF TREE OR GRAPH)
class DisjointSet {
    vector<int> rank, parent, size;
public:
    DisjointSet(int n) {                                //constructor
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int find(int parent[],int i){                       //i = node
        if(i == parent[i]) return i;

        return parent[i] = find(parent, parent[i]);     //rank & path compression (store ans in parent[i])
    }
    void unionSet(int parent[],int x,int y){            //union by rank
        int xParent = find(parent, x);
        int yParent = find(parent, y);

        if(xParent == yParent) return;                  //belong to same set (same graph)

        parent[xParent] = yParent;
        if     (rank[xParent] > rank[yParent]) parent[yParent] = xParent;   //y->x (x is parent)
        else if(rank[xParent] < rank[yParent]) parent[xParent] = yParent;   //x->y (y is parent)
        else    parent[xParent] = yParent;   rank[yParent]++;               //rank[xParent] == rank[yParent], increase rank of parent 
    }
};
int main() {
    int n = 10; // Number of nodes
    int parent[n];
    rank.resize(n, 0); // Initialize the rank vector with size n and all values set to 0
    
    for (int i = 0; i < n; i++) {
        parent[i] = i; // Initially, each node is its own parent
    }

    // Perform union operations
    unionSet(parent, 0, 1);
    unionSet(parent, 1, 2);
    unionSet(parent, 3, 4);
    unionSet(parent, 4, 5);
    unionSet(parent, 6, 7);
    unionSet(parent, 7, 8);
    unionSet(parent, 8, 9);
    unionSet(parent, 0, 9);

    return 0;
} 
/*
Input:
N = 5, K = 4
queries[] = {{find 4},
             {find 1},
             {unionSet 3 1},
             {find 3}}
Output:
4 1 1
Explanation:
1. The parent of 4 is 4. Hence the output is 4.
2. The parent of 1 is 1. Hence the output is 1.
3. After performing unionSet 3 1, parent of 3 becomes 1,
   since, parent of 1 is currently 1 itself.
4. The parent of 3 is now 1. Hence, the output is 1.
*/


//334. DISJOINT SET (UNION BY SIZE)                         {T.C = O(ALPHA OR CONSTANT), S.C = O(1)}
class DisjointSet {
    vector<int> rank, parent, size;
public:
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        }
        else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};
int main() {
    DisjointSet ds(7);
    ds.unionBySize(1, 2);
    ds.unionBySize(2, 3);
    ds.unionBySize(4, 5);
    ds.unionBySize(6, 7);
    ds.unionBySize(5, 6);
    // if 3 and 7 same or not
    if (ds.findUPar(3) == ds.findUPar(7)) {
        cout << "Same\n";
    }
    else cout << "Not same\n";

    ds.unionBySize(3, 7);

    if (ds.findUPar(3) == ds.findUPar(7)) {
        cout << "Same\n";
    }
    else cout << "Not same\n";
    return 0;
}
/*
Input:
N = 5, K = 4
queries[] = {{find 4},
             {find 1},
             {unionSet 3 1},
             {find 3}}
Output:
4 1 1
Explanation
1. The parent of 4 is 4. Hence the output is 4.
2. The parent of 1 is 1. Hence the output is 1.
3. After performing unionSet 3 1, parent of 3 becomes 1,
   since, parent of 1 is currently 1 itself.
4. The parent of 3 is now 1. Hence, the output is 1.
*/


//335. MINIMUM SPANNING TREES (KRUSKAL'S ALGORITHM)               {T.C = O(ELOGE), S.C = O(V+E)}
//MORE EFFICIENT THEN PRIM'S ALGO
//REQURIED EDGES VECTOR(NOT ADJACENCY LIST), SORTED(ACCORDING TO W), THEN APPLY ALGO AND SUM (IF NOT CONNECTED)
class Solution{
	public:
	//KRUSKAL'S ALGORITHM
	vector<int>parent;
	vector<int>rank;
	
	int find(int i){
	    if(i == parent[i]) return i;
	    
	    return parent[i] = find(parent[i]);
	}
	void Union(int x, int y){
	    int xParent = find(x);
	    int yParent = find(y);
	    
	    if(xParent == yParent) return;
	    
	    if     (rank[xParent] > rank[yParent]) parent[yParent] = xParent;   //x is parent
	    else if(rank[xParent] < rank[yParent]) parent[xParent] = yParent;
	    else{ //rank[xParent] == rank[yParent]                             //any one can be parent
	        parent[xParent] = yParent; 
	        rank[yParent]++;
	    }
	}
	int kruskal(vector<vector<int>>&vec){
	    int sum = 0;
	    
	    for(auto it : vec){
	        int u = it[0];
	        int v = it[1];
	        int w = it[2];
	        
	        int uParent = find(u);
	        int vParent = find(v);
	        
	        if(uParent != vParent){
	            Union(u, v);
	            sum += w;
	        }
	    }
	    
	    return sum;
	}
    int spanningTree(int V, vector<vector<int>> adj[]){
        //reinitialize parent and rank
        parent.resize(V);
        rank.resize(V, 0);
        for(int i = 0 ; i < V ; i++){
            parent[i] = i;
        }
        
        //convert adjacency list to edge list  (in kruskal we require edge list( sorted order of weight))
        vector<vector<int>>edges;
        for(int u = 0 ; u < V ; u++){
            for(auto it : adj[u]){
                int v = it[0];
                int w = it[1];
                
                edges.push_back({u, v, w});
            }
        }
        
        auto lambda = [&](auto &a, auto &b){
            return a[2] < b[2];                            //compare on basis of weight 
        };
        sort(edges.begin(), edges.end(), lambda);
        
        return kruskal(edges);
    }
};
/*
Example 1:
Input:
3 3
0 1 5
1 2 3
0 2 1
Output:
4
Explanation:
The Spanning Tree resulting in a weight
of 4 is shown above.

Example 2:
Input:
2 1
0 1 5
Output:
5
Explanation:
Only one Spanning Tree is possible
which has a weight of 5.
*/


//336. NUMBER OF OPERATIONS TO MAKE NETWORK CONNECTED
//USING DFS                                                       {T.C = O(V+E), S.C = O(V+E)}
//SIMPLY COUNT COMPONENTS, REQUIRED EDGES SHOULD BE COMPONENTS-1.
class Solution {
public:
    //USING DFS
    void dfs(unordered_map<int,vector<int>>&adj, vector<bool>&vis, int node){
        vis[node] = 1;
        for(auto it : adj[node]){
            if(!vis[it]) dfs(adj, vis, it);
        }
    }
    int makeConnected(int n, vector<vector<int>>& connections) {
        int edges = connections.size();   
        //base case
        if(edges < n-1) return -1;          //edges == v-1                                    
        unordered_map<int,vector<int>>adj;
        for(auto it : connections){
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }
        int components = 0;
        vector<bool>vis(n, 0);
        for(int i = 0 ; i < n ; i++){                      //handle all components
            if(!vis[i]){
                dfs(adj, vis, i);
                components++;
            }
        }
        return components-1;                               //minimum edges required
    }
};

//USING DISJOINT SET                                          {T.C = O(E*ALPHA), S.C = O(V)}
class Solution {
public:
    //USING DISJOIN SET
    vector<int>parent, rank;
    int find(int i){
        if(i == parent[i]) return i;

        return parent[i] = find(parent[i]);
    }
    void Union(int x, int y){
        int xParent = find(x);
        int yParent = find(y);

        if(xParent == yParent) return;

        if     (rank[xParent] > rank[yParent]) parent[yParent] = xParent;
        else if(rank[xParent] < rank[yParent]) parent[xParent] = yParent;
        else{ //rank[xParent] == rank[yParent]                 //choose any as parent
            parent[xParent] = yParent;
            rank[yParent]++;
        }
    }
    int makeConnected(int n, vector<vector<int>>& connections) {
        int edges = connections.size();   
        //base case
        if(edges < n-1) return -1;          //edges == v-1  

        //reinitialize parent , rank
        rank.resize(n, 0);
        parent.resize(n);
        for(int i = 0 ; i < n ;i++) parent[i] = i;            //self parent

        int components = n;
        for(auto it : connections){
            if(find(it[0]) != find(it[1])){
                Union(it[0], it[1]);
                components--;
            }
        }
        return components-1;                               //minimum edges             
    }
};
/*
Example 1:
Input: n = 4, connections = [[0,1],[0,2],[1,2]]
Output: 1
Explanation: Remove cable between computer 1 and 2 and place between computers 1 and 3.

Example 2:
Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2],[1,3]]
Output: 2

Example 3:
Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2]]
Output: -1
Explanation: There are not enough cables.
*/


//337. MOST STONES REMOVED WITH SAME ROW OR COLUMN               
//USING DFS                                               {T.C = O(N^2), S.C = O(N)}
//MAKE GROUP OF SAME ROW OR SAME COL(DFS), RETURN N-GROUP(IN GROUP ONLY 1 WILL LEFT)
class Solution {
public:
    void dfs(vector<vector<int>>&stones, vector<bool>&vis, int node){
        vis[node] = 1;
        for(int i = 0 ; i  < stones.size() ; i++){                 //TAKES O(N)
            int sameRow = stones[node][0];                      //{x, y}
            int sameCol = stones[node][1];
            if(!vis[i] && (sameRow == stones[i][0] || sameCol == stones[i][1])){
                dfs(stones, vis, i);
            }
        }
    }
    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        vector<bool>vis(n, false);
        int group = 0;
        for(int i = 0 ; i  < n ; i++){       //disconnected components
            if(!vis[i]){
                dfs(stones, vis, i);
                group++;
            }
        }
        return n-group;                //most stones removed {stones - group{at last 1 left from each grp}}
    }
};

//USING DISJOINT SET                                       {T.C = O(N^2), S.C = O(N)}
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

        return n - groups;
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

Example 3:
Input: stones = [[0,0]]
Output: 0
Explanation: [0,0] is the only stone on the plane, so you cannot remove it.
*/


//338. ACCOUNTS MERGE                                     {T.C = O(M*LOGM), S.C = O(M){M = EMAILS}}
//USING DISJOINT SETS
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

        if (xParent == yParent) return;

        if (rank[xParent] > rank[yParent]) parent[yParent] = xParent;
        else if (rank[xParent] < rank[yParent]) parent[xParent] = yParent;
        else {
            parent[xParent] = yParent;
            rank[yParent]++;
        }
    }

    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        rank.resize(n, 0);
        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i;

        unordered_map<string, int> mp;                      // mail, index
        for (int i = 0; i < n; i++) {                       //iterate on account
            for (int j = 1; j < accounts[i].size(); j++) {  //iterate on emails, 0 is name, 1+ is emails
                string mail = accounts[i][j];
                if (!mp.count(mail)) mp[mail] = i;          //not present then map to index
                else Union(i, mp[mail]);                    //present then take union
            }
        }

        unordered_map<int, vector<string>> mergedMail;
        for (auto& it : mp) {
            string mail = it.first;
            int node = find(it.second);
            mergedMail[node].push_back(mail);
        }

        vector<vector<string>> ans;
        for (int i = 0; i < n; i++) {
            if (mergedMail[i].empty()) continue;
            sort(mergedMail[i].begin(), mergedMail[i].end());
            vector<string> temp;
            temp.push_back(accounts[i][0]);
            for (auto& mail : mergedMail[i]) temp.push_back(mail);
            ans.push_back(temp);
        }
        sort(ans.begin(), ans.end());

        return ans;
    }
};
/*
Example 1:

Input: accounts = [["John","johnsmith@mail.com","john_newyork@mail.com"],
                   ["John","johnsmith@mail.com","john00@mail.com"],
                   ["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
Output: [["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],
         ["Mary","mary@mail.com"],
         ["John","johnnybravo@mail.com"]]
Explanation:
The first and second John's are the same person as they have the common email "johnsmith@mail.com".
The third John and Mary are different people as none of their email addresses are used by other accounts.
We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'], 
['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.
*/


//339. NUMBER OF ISLANDS II                                   {T.C = O(K*LOGN*M), S.C = O(N*M)} //K = OPERATIONS
//USING DISJOINT SETS
class Solution {
public:
    vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    bool isValid(int newRow, int newCol, int n, int m) {
        return (newRow >= 0 && newRow < n && newCol >= 0 && newCol < m);
    }

    vector<int> parent, rank;

    int find(int i) {
        if (i == parent[i]) return i;
        return parent[i] = find(parent[i]);
    }

    void Union(int x, int y) {
        int xParent = find(x);
        int yParent = find(y);

        if (xParent == yParent) return;

        if (rank[xParent] > rank[yParent]) parent[yParent] = xParent;
        else if (rank[xParent] < rank[yParent]) parent[xParent] = yParent;
        else {
            parent[xParent] = yParent;
            rank[yParent]++;
        }
    }

    vector<int> numOfIslands(int n, int m, vector<vector<int>>& operators) {
        int totalCells = n * m;
        rank.resize(totalCells, 0);
        parent.resize(totalCells);
        for (int i = 0; i < totalCells; i++) parent[i] = i;  // initialize self parent

        vector<vector<bool>> vis(n, vector<bool>(m, false));
        vector<int> componentsArr;
        int components = 0;

        //connecting components
        for (auto& it : operators) {
            int row = it[0];
            int col = it[1];
            int index = row * m + col;  // 2D to 1D conversion
            if (vis[row][col]) {
                componentsArr.push_back(components);
                continue;  // skip if the cell is already added
            }
            vis[row][col] = true;
            components++;

            for (auto& dir : directions) {
                int newRow = row + dir[0];
                int newCol = col + dir[1];
                if (isValid(newRow, newCol, n, m) && vis[newRow][newCol]) {
                    int newIndex = newRow * m + newCol;
                    if (find(index) != find(newIndex)) {
                        Union(index, newIndex);
                        components--;
                    }
                }
            }
            componentsArr.push_back(components);
        }
        return componentsArr;
    }
};
/*
Example 1:
Input: n = 4
m = 5
k = 4
A = {{1,1},{0,1},{3,3},{3,4}}
Output: 1 1 2 2
Explanation:
0.  00000
    00000
    00000
    00000
1.  00000
    01000
    00000
    00000
2.  01000
    01000
    00000
    00000
3.  01000
    01000
    00000
    00010
4.  01000
    01000
    00000
    00011
*/


//340. MAKING A LARGE ISLANDS
//USING DISJOINT SETS                                       {T.C = O(N*M*ALPHA), S.C = O(N*M)}
//COUNT TOTALCELLS(N*N), CONNECT COMPONENTS(WITH 1 VAL), STORE SIZE OF EACH COMPONENT, CONVERT ADJ(0 TO 1)
//THEN FIND MAXCOMPONENT SIZE.
class Solution {
public:
    vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    
    bool isValid(int newRow, int newCol, int n, int m) {
        return (newRow >= 0 && newRow < n && newCol >= 0 && newCol < m);
    }

    vector<int> parent, rank;

    int find(int i) {
        if (i == parent[i]) return i;
        return parent[i] = find(parent[i]);
    }

    void Union(int x, int y) {
        int xParent = find(x);
        int yParent = find(y);

        if (xParent == yParent) return;

        if (rank[xParent] > rank[yParent]) parent[yParent] = xParent;
        else if (rank[xParent] < rank[yParent]) parent[xParent] = yParent;
        else {
            parent[xParent] = yParent;
            rank[yParent]++;
        }
    }

    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        if (n == 0) return 0;
        int m = grid[0].size();
        int totalCells = n * m;
        
        rank.resize(totalCells, 0);
        parent.resize(totalCells);
        for (int i = 0; i < totalCells; i++) parent[i] = i;

        // Connecting components
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < m; col++) {
                if (grid[row][col] == 0) continue;
                for (auto it : directions) {
                    int newRow = row + it[0];
                    int newCol = col + it[1];
                    if (isValid(newRow, newCol, n, m) && grid[newRow][newCol] == 1) {
                        int idx = row * m + col;
                        int newIdx = newRow * m + newCol;
                        Union(idx, newIdx);
                    }
                }
            }
        }

        // Size of each component
        vector<int> componentSize(totalCells, 0);
        for (int i = 0; i < totalCells; i++) {
            int root = find(i);
            componentSize[root]++;
        }

        // Find the maximum size of an island
        int maxSizeComponent = *max_element(componentSize.begin(), componentSize.end());

        // Convert 0 to 1 and find the maximum size of the largest island
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < m; col++) {
                if (grid[row][col] == 1) continue;  // skip already 1

                set<int> components;                               //each component count 1's only
                for (auto it : directions) {
                    int newRow = row + it[0];
                    int newCol = col + it[1];
                    if (isValid(newRow, newCol, n, m) && grid[newRow][newCol] == 1) { //if adj(1) insert in parent compoent
                        components.insert(find(newRow * m + newCol));
                    }
                }

                int totalSize = 1;  // Converting 0 to 1
                for (auto it : components) {
                    totalSize += componentSize[it];
                }
                maxSizeComponent = max(maxSizeComponent, totalSize);
            }
        }

        return maxSizeComponent;
    }
};
/*
Example 1:
Input: grid = [[1,0],[0,1]]
Output: 3
Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.

Example 2:
Input: grid = [[1,1],[1,0]]
Output: 4
Explanation: Change the 0 to 1 and make the island bigger, only one island with area = 4.

Example 3:
Input: grid = [[1,1],[1,1]]
Output: 4
Explanation: Can't change any 0 to 1, only one island with area = 4.
*/


//341. SWIM IN RISING WATER
//USING DISJOINT SETS                                        {T.C = O(N^2*LOGN), S.C = O(N^2)}
//STORE POSITIONS OF COORDINATES , IF ADJ(NEW COORDINATES) <= T THEN UNION (IDX && NEWIDX), WHEN REACH
//START TO END(N-1, N-1) RETURN T.
class Solution {
public:
    vector<vector<int>>directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool isValid(int newRow, int newCol, int n){
        return (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n);
    }
    
    vector<int>parent, rank;
    int find(int i){
        if(i == parent[i]) return i;
        
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
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        int totalCells = n*n;
        rank.resize(totalCells, 0);
        parent.resize(totalCells);
        for(int i = 0 ; i < totalCells; i++) parent[i] = i;
        //or
        // iota(parent.begin(), parent.end(), 0);

        //store positions of each cell value
        vector<vector<int>>positions(totalCells);
        for(int i = 0; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                positions[grid[i][j]] = {i, j}; 
            }
        }

        //iterate over all cells
        for(int i = 0 ;  i < totalCells ; i++){
            int x = positions[i][0];
            int y = positions[i][1];

            for(auto &it : directions){
                int newX = x + it[0];
                int newY = y + it[1];
                if(isValid(newX, newY, n) && grid[newX][newY] <= i){     //i == t
                    int idx     = x*n + y;
                    int newIdx  = newX*n + newY;
                    Union(idx, newIdx);
                }
            }

            if(find(0) == find(totalCells-1)){              //(0, 0) -> (n-1, n-1)
                return i; 
            }
        }

        return -1;
    }
};
/*
Example 1:
Input: grid = [[0,2],
               [1,3]]
Output: 3
Explanation:
At time 0, you are in grid location (0, 0).
You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.
You cannot reach point (1, 1) until time 3.
When the depth of water is 3, we can swim anywhere inside the grid.

Example 2:
Input: grid = [[0, 1, 2, 3, 4],
               [24,23,22,21,5],
               [12,13,14,15,16],
               [11,17,18,19,20],
               [10,9, 8, 7, 6]]
Output: 16
Explanation: The final route is shown.
We need to wait until time 16 so that (0, 0) and (4, 4) are connected.
*/


//342. CRITICAL CONNECTIONS IN A NETWORK / BRIDGES IN A GRAPH            {T.C = O(V+E), S.C = O(V+E)}
//USING TARZAN'S ALGO
//ANY EDGE(REMOVAL) CAUSE INCREASE IN COMPONENT, THEN THIS EDGE CALLED BRIDGE.
class Solution {
public:
    void dfs(unordered_map<int,vector<int>>&adj, int timer, int parent, vector<int>&discTime, vector<int>&lowestTime, vector<bool>&vis, vector<vector<int>>&ans, int node){
        vis[node] = true;
        discTime[node] = lowestTime[node] = timer++;

        for (auto it : adj[node]) {
            if (it == parent) continue;                        //skip
            
            if (!vis[it]) {
                dfs(adj, timer, node, discTime, lowestTime, vis, ans, it); // Pass 'node' as the parent
                lowestTime[node] = min(lowestTime[node], lowestTime[it]);

                // Check if the edge is a bridge or not
                if (lowestTime[it] > discTime[node]) { // This is a bridge edge
                    vector<int> temp;
                    temp.push_back(node);
                    temp.push_back(it);
                    ans.push_back(temp);
                }
            }
            else { // Back edge (node already visited)
                lowestTime[node] = min(lowestTime[node], discTime[it]);
            }
        }

    }
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        unordered_map<int,vector<int>>adj;
        for(auto &it : connections){
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }

        int timer = 0, parent = -1;
        vector<int>discTime(n, -1);
        vector<int>lowestTime(n, -1);
        vector<bool>vis(n, false);

        vector<vector<int>>ans;
        //dfs
        for(int i = 0 ; i < n ; i++){
            if(!vis[i]){
                dfs(adj, timer, parent, discTime, lowestTime, vis, ans, i);
            }
        }
        return ans;
    }
};
/*
Example 1:
Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
Output: [[1,3]]
Explanation: [[3,1]] is also accepted.

Example 2:
Input: n = 2, connections = [[0,1]]
Output: [[0,1]]
*/


//343. ARTICULATION POINT I (USING TARZAN'S ALGO)             {T.C = O(VLOGN + V+E), S.C = O(V)}
//ANY VERTEX(REMOVAL) CAUSE INCREASE IN COMPONENT, THEN THIS VERTEX CALLED ARTICULATION POINT.
class Solution {
public:
    void dfs(vector<int> adj[], int& timer, int parent, vector<int>& discTime, vector<int>& lowestTime, vector<bool>& vis, vector<int>& ans, int node) {
        vis[node] = true;
        discTime[node] = lowestTime[node] = timer++;
        
        int child = 0;
        for (auto it : adj[node]) {
            if (it == parent) continue;

            if (!vis[it]) {
                child++;
                dfs(adj, timer, node, discTime, lowestTime, vis, ans, it);
                lowestTime[node] = min(lowestTime[node], lowestTime[it]);

                // Check if the vertex is an articulation point
                if (lowestTime[it] >= discTime[node] && parent != -1) {
                    ans.push_back(node);
                }
            } else {  // Back edge
                lowestTime[node] = min(lowestTime[node], discTime[it]);
            }
        }

        // Root node is an articulation point if it has more than one child in DFS tree
        if (parent == -1 && child > 1) {
            ans.push_back(node);
        }
    }

    vector<int> articulationPoints(int V, vector<int> adj[]) {
        int timer = 0;
        vector<int> discTime(V, -1);
        vector<int> lowestTime(V, -1);
        vector<bool> vis(V, false);
        
        vector<int> ans;
        for (int i = 0; i < V; i++) {
            if (!vis[i])
                dfs(adj, timer, -1, discTime, lowestTime, vis, ans, i);
        }

        // Remove duplicates and sort the articulation points
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());

        // If no articulation point is found, return -1
        if (ans.empty()) {
            ans.push_back(-1);
        }
        
        return ans;
    }
};


/*
Example 1:
Input:
Output:{1,4}

Explanation: Removing the vertex 1 will
discconect the graph as-
Removing the vertex 4 will disconnect the
graph as-
*/


//344. STRONGLY CONNECTED COMPONENTS (KOSARAJU'S ALGO)            {T.C = O(V+E), S.C = O(V+E)}
class Solution
{
	public:
	void dfs(vector<vector<int>>&adj, vector<int>&vis, stack<int>&s, int node){
	    vis[node]  = 1;
	    
	    for(auto it : adj[node]){
	        if(!vis[it]){
	            dfs(adj, vis, s, it);
	        }
	    }
	    //topo sort logic
	    s.push(node);
	}
	void dfs(vector<vector<int>>&transpose, vector<int>&vis, int node){
	    vis[node] = 1;
	    
	    for(auto it : transpose[node]){
	        if(!vis[it]){
	            dfs(transpose, vis, it);
	        }
	    }
	}
    int kosaraju(int V, vector<vector<int>>& adj)
    {
        //step1 sort the adjacency list using topological sort
        vector<int>vis(V, 0);
        stack<int>s;
        for(int i = 0 ; i < V ; i++){
            if(!vis[i]){
                dfs(adj, vis, s, i);
            }
        }
        
        //step2 create a transpose graph
        vector<vector<int>>transpose(V);
        for(int i = 0 ; i < V ; i++){
            vis[i] = 0;                                    //reinitialize visited array
            for(auto it : adj[i]){
                transpose[it].push_back(i);
            }
        }
        
        //step3 dfs call on basis of above ordering (stack ordering)
        int countSCC = 0;                          //SCC = Strongly Conneted Component
        while(!s.empty()){
            int top = s.top();
            s.pop();
            if(!vis[top]){
                countSCC++;
                dfs(transpose, vis, top);
            }
        }
        return countSCC;
    }
};
/*
Example 1:
Input:
Output:
3
Explanation:
We can clearly see that there are 3 Strongly
Connected Components in the Graph

Example 2:
Input:
Output:
1
Explanation:
All of the nodes are connected to each other.
So, there's only one SCC.
*/


/*--------------------------------------THE END--------------------------------------------------------*/