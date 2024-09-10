#include<bits/stdc++.h>
using namespace std;

//DAY 24: GRAPH 2-----------------------------------------------------------------------------------------------------
//96. STRONGLY CONNECTED COMPONENTS (KOSARAJU'S ALGO)                     {T.C = O(V+E), S.C = O(V+E)}
class Solution
{
	public:
	void dfsTopo(vector<vector<int>>&adj, vector<bool>&vis, stack<int>&stk, int node){
	    vis[node] = true;
	    for(auto it : adj[node]){
	        if(!vis[it]) dfsTopo(adj, vis, stk, it);
	    }
	    stk.push(node);                                        //topological sort logic
	}
	void dfs(vector<vector<int>>&adj, vector<bool>&vis , int node){
	    vis[node] = true;
	    for(auto it : adj[node]){
	        if(!vis[it]) dfs(adj, vis, it);
	    }
	}
    int kosaraju(int V, vector<vector<int>>& adj){
        vector<bool>vis(V, false);
        stack<int>stk;
        for(int i = 0 ; i < V ; i++){
            if(!vis[i]) dfsTopo(adj, vis, stk, i);
        }
        
        //transpose of graph (reverse edge graph)
        vector<vector<int>>transpose(V);
        for(int i= 0 ; i < V ; i++){
            vis[i] = false;                        //reinitialize vis with false
            for(auto it : adj[i]){
                transpose[it].push_back(i);
            }   
        }
        
        //apply dfs and count components(actually SCC) on transposed graph
        int componentsSCC = 0;
        while(!stk.empty()){
            int top = stk.top();
            stk.pop();
            if(!vis[top]){
                componentsSCC++;
                dfs(transpose, vis, top);
            }
        }
        
        return componentsSCC;
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


//97. DIJKSTRA ALGO                                                       {T.C = O(E*LOGV), S.C = O(V+E)}
class Solution{
	public:
	typedef pair<int,int>P;
    vector <int> dijkstra(int V, vector<vector<int>> adj[], int S){
        vector<int>minDis(V, INT_MAX);
        minDis[S] = 0;                                //self dis is always 0
        priority_queue<P,vector<P>, greater<P>>pq;
        pq.push({0, S});                             //dist, src
        while(!pq.empty()){
            auto topNode = pq.top();
            pq.pop();
            int dis = topNode.first;
            int u = topNode.second;
            for(auto it : adj[u]){
                int d = it[1];
                int v = it[0];
                if(dis+d < minDis[v]){
                    minDis[v] = dis+d;
                    pq.push({dis+d, v});
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


//98. DISTANCE FROM THE SOURCE (BELLMAN-FORD ALGORITHM)                   {T.C = O(V*E), S.C = O(V)}
class Solution {
  public:
    vector<int> bellman_ford(int V, vector<vector<int>>& edges, int S) {
        vector<int>minDis(V, 1e8);                      //according to constraints
        minDis[S] = 0;
        for(int i = 0 ; i < V ; i++){                  //check v-1 times
            for(auto it : edges){
                int u = it[0], v = it[1], d = it[2];
                if(minDis[u]+d < minDis[v] && minDis[u] != 1e8){
                    minDis[v] = minDis[u]+d;
                }
            }
        }
        for(auto it : edges){                          //check 1 more time for cycle check
            int u = it[0], v = it[1], d = it[2];
            if(minDis[u]+d < minDis[v] && minDis[u] != 1e8){
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


//99.FLOYD WARSHALL                                                        {T.C = O(N^3), S.C = O(1)}
class Solution {
  public:
	void shortest_distance(vector<vector<int>>&matrix){
	    int n = matrix.size();               //n == m
	    //update matrix -1 to 1e9
	    for(int i = 0 ; i < n ; i++){
	        for(int j = 0 ; j < n ; j++){
	            if(matrix[i][j] == -1) matrix[i][j] = 1e9;
	            if(i == j) matrix[i][j] = 0;               //self dis 0
	        }
	    }
	    
	    //floyd logic 3 loop
	    for(int k = 0 ; k < n ; k++){
	        for(int i = 0 ; i < n ; i++){
	            for(int j = 0 ; j < n ;j++){
                    matrix[i][j] = min(matrix[i][j], matrix[i][k]+matrix[k][j]);
	            }
	        }
	    }
	    
	    //reset the 1e8 to -1 matrix
	    for(int i = 0 ; i < n; i++){
	        for(int j = 0 ; j < n ;j++){
	            if(matrix[i][j] == 1e9) matrix[i][j] = -1;
	        }
	    }
	}
};
/*
Examples :
Input: matrix = [[0, 25],[-1, 0]]
Output: [[0, 25],[-1, 0]]
Explanation: The shortest distance between every pair is already given(if it exists).

Input: matrix = [[0, 1, 43],[1, 0, 6],[-1, -1, 0]]
Output: [[0, 1, 7],[1, 0, 6],[-1, -1, 0]]
Explanation: We can reach 2 from 0 as 0->1->2 and the cost will be 1+6=7 which is less than 43.
*/


//100. MINIMUM SPANNING TREE (PRIM'S ALGO)  {FFICIENT FOR DENSE GRAPH}                  {T.C = O(E*LOGV), S.C = O(V)}
class Solution{
	public:
	typedef pair<int,int>P;
    int spanningTree(int V, vector<vector<int>> adj[]){
        priority_queue<P, vector<P>, greater<P>>pq;
        pq.push({0, 0});                      //dist src , -1 if finding mst
        
        vector<bool>vis(V, false);
        int sum = 0;
        while(!pq.empty()){
            auto topNode = pq.top();
            pq.pop();
            int dis = topNode.first;
            int u = topNode.second;
            
            if(vis[u] == true) continue;         //skip
            vis[u] = true;
            sum += dis;
            
            for(auto it : adj[u]){
                int d = it[1];
                int v = it[0];
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


//101. MINIMUM SPANNING TREE (KRUSKAL'S ALGO) (EFFICIENT FOR SPARSE GRAPH)              {T.C = O(E*LOGE), S.C = O(V)}
class Solution{
	public:
	vector<int>parent, rank;
	int find(int i){
	    if(i == parent[i]) return i;
	    else parent[i] = find(parent[i]);
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
	int kruskal(vector<vector<int>>&edges){
	    int sum = 0;
	    
	    for(auto it : edges){
	        int u = it[0], v = it[1], w = it[2];
	        
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
        rank.resize(V, 0);
        parent.resize(V);
        for(int i = 0 ; i < V ; i++) parent[i] = i;
        
        //convert adj into edges
        vector<vector<int>>edges;
        for(int i = 0 ; i < V ; i++){
            for(auto it : adj[i]){
                int v = it[0], w = it[1];
                edges.push_back({i, v, w});                   //u, v, w
            }
        }
        
        
        auto lambda = [&](auto &a, auto &b){
            return (a[2] < b[2]); 
        };
        sort(edges.begin(), edges.end(), lambda);            //sort according to weight
        
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