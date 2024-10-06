#include<bits/stdc++.h>
using namespace std;


//DAY 17: BINARY TREE----------------------------------------------------------------------------------
//104. BINARY TREE INORDER TRAVERSAL                                     {T.C = O(N), S.C = O(H)}
class Solution {
public:
    void inOrder(TreeNode* root, vector<int>&ans){
        //base case
        if(!root) return;
        
        inOrder(root->left, ans);
        ans.push_back(root->val);
        inOrder(root->right, ans);
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int>ans;
        inOrder(root, ans);
        return ans;
    }
};
/*
Example 1:
Input: root = [1,null,2,3]
Output: [1,3,2]

Example 2:
Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]
Output: [4,2,6,5,7,1,3,9,8]

Example 3:
Input: root = []
Output: []

Example 4:
Input: root = [1]
Output: [1]
*/


//105. BINARY TREE PREORDER TRAVERSAL                                     {T.C = O(N), S.C = O(H)}
class Solution {
public:
    void preOrder(TreeNode* root, vector<int>&ans){
        //base case
        if(!root) return;

        ans.push_back(root->val);
        preOrder(root->left, ans);
        preOrder(root->right, ans);
    }
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int>ans;
        preOrder(root, ans);
        return ans;
    }
};
/*
Example 1:
Input: root = [1,null,2,3]
Output: [1,2,3]

Example 2:
Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]
Output: [1,2,4,5,6,7,3,8,9]

Example 3:
Input: root = []
Output: []

Example 4:
Input: root = [1]
Output: [1]
*/


//106. BINARY TREE POSTORDER TRAVERSAL                                     {T.C = O(N), S.C = O(H)}
class Solution {
public:
    void postOrder(TreeNode* root, vector<int>&ans){
        //base case
        if(!root) return;

        postOrder(root->left, ans);
        postOrder(root->right, ans);
        ans.push_back(root->val);
    }
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int>ans;
        postOrder(root, ans);
        return ans;
    }
};
/*
Example 1:
Input: root = [1,null,2,3]
Output: [3,2,1]

Example 2:
Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]
Output: [4,6,7,5,2,9,8,3,1]

Example 3:
Input: root = []
Output: []

Example 4:
Input: root = [1]
Output: [1]
*/


//107. BINARY TREE INORDER TRAVERSAL / USING MORRIS TRAVERSAL                {T.C = O(N), S.C = O(1)}
class Solution {
public:
    void inOrderMorris(TreeNode* root, vector<int>&ans){
        //base case
        if(!root) return;

        TreeNode* curr = root;
        while(curr){
            if(curr->left){              //move 1st step left then extreme right
                TreeNode* leftChild = curr->left;
                while(leftChild->right) leftChild = leftChild->right;
                leftChild->right = curr;  //connect right to curr

                //remove previous connections
                TreeNode* prev = curr;
                curr = curr->left;
                prev->left = NULL;
            }else{                       //LNR(not left then print & move right)
                ans.push_back(curr->val);
                curr = curr->right;
            }
        }
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int>ans;
        inOrderMorris(root, ans);
        return ans;
    }
};

//ANOTHER WAY
class Solution {
public:
    //MORRIS TRAVERSAL (T.C = O(N), S.C = O(1) {NO EXTRA SPACE CONSUME})
    void inOrMorrisTraversal(TreeNode* root, vector<int>&ans){
        //base case
        if(!root) return;
        TreeNode* curr = root;           //store original root
        while(curr){
            if(curr->left){
                TreeNode* pred = curr->left;
                while(pred->right && pred->right != curr){
                    pred = pred->right;
                } 
                if(pred->right == NULL){  //move right & add virtual pointer
                    pred->right = curr;
                    curr = curr->left; 
                }else{                   //remove virtual pointer
                    ans.push_back(curr->val);   //LNR
                    pred->right = NULL;
                    curr = curr->right;
                }

            }else{ //!curr->left
                ans.push_back(curr->val);
                curr = curr->right;
            }
        }

    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int>ans;
        inOrMorrisTraversal(root, ans);

        return ans;
    }
};
/*
Example 1:
Input: root = [1,null,2,3]
Output: [1,3,2]

Example 2:
Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]
Output: [4,2,6,5,7,1,3,9,8]

Example 3:
Input: root = []
Output: []

Example 4:
Input: root = [1]
Output: [1]
*/


//108. BINARY TREE PREORDER TRAVERSAL / USING MORRIS TRAVERSAL                {T.C = O(N), S.C = O(1)}
class Solution {
public:
    void preOrMorrisTraversal(TreeNode* root, vector<int>&ans){
        //base case
        if(!root) return;
        TreeNode* curr = root;
        while(curr){
            if(curr->left){
                TreeNode* pred = curr->left;
                while(pred->right && pred->right != curr){
                    pred = pred->right;
                }
                if(pred->right == NULL){           //move right & add virtual pointer
                    ans.push_back(curr->val);      //NLR
                    pred->right = curr;
                    curr = curr->left;
                }else{                             //remove virtual pointer
                    // ans.push_back(curr->val);   //for inorder
                    pred->right = NULL;
                    curr = curr->right;
                }
            }else{
                ans.push_back(curr->val);
                curr = curr->right;
            }
        }
    }
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int>ans;
        preOrMorrisTraversal(root, ans);

        return ans;
    }
};
/*
Example 1:
Input: root = [1,null,2,3]
Output: [1,2,3]

Example 2:
Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]
Output: [1,2,4,5,6,7,3,8,9]

Example 3:
Input: root = []
Output: []

Example 4:
Input: root = [1]
Output: [1]
*/


//109a. LEFT VIEW OF BINARY TREE                           
//RECURSIVE SOLUTION                                                         {T.C = O(N), S.C = O(N)}
void left(Node* root, vector<int>&ans, int lvl){
    //base case
    if(!root) return;
    
    if(lvl == ans.size()) ans.push_back(root->data);
    
    left(root->left, ans, lvl+1);                  //left view (L then R call)
    left(root->right, ans, lvl+1);
}
vector<int> leftView(Node *root){
    vector<int>ans;
    left(root, ans, 0);                    //0 = level number
    
    return ans;
}

//ITERATIVE APPRAOCH / FIND LEVEL ORDER THEN PUSH 1st OF EACH LEVEL            {T.C = O(N), S.C = O(N)}
void lvlOrder(Node* root, vector<vector<int>>&ans){
    //base cse
    if(!root) return;

    queue<Node*>q;
    q.push(root);
    
    while(!q.empty()){
        int lvlsz = q.size();
        vector<int>lvlNodes;
        for(int i = 0 ; i < lvlsz ; i++){
            auto frontNode = q.front();
            q.pop();
            lvlNodes.push_back(frontNode->data);
            if(frontNode->left) q.push(frontNode->left);
            if(frontNode->right)q.push(frontNode->right);
        }
        ans.push_back(lvlNodes);
    }
}
vector<int> leftView(Node *root){
   vector<vector<int>>ans;
   lvlOrder(root, ans);
   
   vector<int>res;
   for(auto it : ans) res.push_back(it[0]);     //first node of each level
   return res;
}
/*
Examples :
Input: root[] = [1, 2, 3, 4, 5, 6, 7, N, 8]
          1
       /     \
     2        3
   /     \    /    \
  4     5   6    7
   \
     8   
Output: [1, 2, 4, 8]
Explanation: When we view the tree from the left side, we can only see the nodes 1, 2, 4, and 8.
Input: root[] = [1, 3, N, N, 4]
Output: [1, 3, 4]
Input: root[] = [N]
Output: []
*/


//109b. RIGHT VIEW OF BINARY TREE
//RECURSIVE APPROACH                                                   {T.C = O(N), S.C = O(N)}
class Solution{
public:
    void right(Node* root, vector<int>&ans, int lvl){
        //base case
        if(!root) return;
        
        if(lvl == ans.size()) ans.push_back(root->data);
        
        right(root->right, ans, lvl+1);          //for right view (firs R then L)
        right(root->left, ans, lvl+1); 
    }
    vector<int> rightView(Node *root){
       vector<int>ans;
       right(root, ans, 0);                   //0 = level number
       
       return ans;
    }
};

//ITERATIVE APPROACH / SAME ABOVE JUST PUSH BACK ELEMENT               {T.C = O(N), S.C = O(N)}                           
class Solution{
    public:
    void lvlOrder(Node* root, vector<vector<int>>&ans){
        //base case
        if(!root) return;
        
        queue<Node*>q;
        q.push(root);
        
        while(!q.empty()){
            int lvlsz = q.size();
            vector<int>lvlNodes;
            for(int i = 0 ; i < lvlsz ; i++){
                auto frontNode = q.front();
                q.pop();
                lvlNodes.push_back(frontNode->data);
                if(frontNode->left) q.push(frontNode->left);
                if(frontNode->right)q.push(frontNode->right);
            }
            ans.push_back(lvlNodes);
        }
    }
    vector<int> rightView(Node *root){
       vector<vector<int>>ans;
       lvlOrder(root, ans);
       
       vector<int>res;
       for(auto it : ans) res.push_back(it.back());        //push last node of each level
       
       return res;
    }
};
/*
Examples :
Input:
       1
    /    \
   3      2
Output: 1 2
Input:
     10
    /   \
  20     30
 /   \
40  60 
Output: 10 30 60
*/


//110. BOTTOM VIEW OF BINARY TREE                                     {T.C = O(N), S.C = O(N)}
class Solution{
    public:
    vector<int> bottomView(Node *root){
        vector<int>ans;
        //base case
        if(!root) return ans;
        map<int,int>mp;                       //axis(-1,0,1), acutal nodeVal
        queue<pair<Node*, int>>q;             //Node, axis(-1, 0, 1)
        
        q.push({root, 0});
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            Node* currNode = frontNode.first;
            int xVal       = frontNode.second;
            
            // if(!mp.count(xVal)) mp[xVal] = currNode->data;      //for top view
            mp[xVal] = currNode->data;      //for bottom view
            if(currNode->left) q.push({currNode->left, xVal-1});       //----2, -1, 0
            if(currNode->right)q.push({currNode->right, xVal+1});      //0, 1, 2-----
        }
        for(auto it : mp) ans.push_back(it.second);          //map stored ans in req(sorted) order
        return ans;
    }
};
/*
Examples :
Input:
       1
     /   \
    3     2
Output: 3 1 2

Input:
         10
       /    \
      20    30
     /  \
    40   60
Output: 40 20 60 30
*/


//111. TOP VIEW OF BINARY TREE                                        {T.C = O(N), S.C = O(N)}
class Solution{
    public:
    vector<int> topView(Node *root){
        vector<int>ans;
        //base case
        if(!root) return ans;
        map<int,int>mp;                       //axis(-1,0,1), acutal nodeVal
        queue<pair<Node*, int>>q;             //Node, axis(-1, 0, 1)
        
        q.push({root, 0});
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            Node* currNode = frontNode.first;
            int xVal       = frontNode.second;
            
            if(!mp.count(xVal)) mp[xVal] = currNode->data;      //for top view
            // mp[xVal] = currNode->data;      //for bottom view
            if(currNode->left) q.push({currNode->left, xVal-1});       //----2, -1, 0
            if(currNode->right)q.push({currNode->right, xVal+1});      //0, 1, 2-----
        }
        for(auto it : mp) ans.push_back(it.second);          //map stored ans in req(sorted) order
        return ans;
    }
};
/*
Example 1:
Input:
      1
   /    \
  2      3
Output: 2 1 3

Example 2:
Input:
       10
    /      \
  20        30
 /   \    /    \
40   60  90    100
Output: 40 20 10 30 100
*/


//112. TREE TRAVERSAL / PREORDER, POSTORDER, INORDER IN SINGLE TRAVERSAL      {T.C = O(N), S.C = O(H)}
void solve(TreeNode* root, vector<int>&In, vector<int>&pre, vector<int>& post){
    if(!root) return;

    //pre
    pre.push_back(root->data);

    //In
    solve(root->left,In,pre,post);
    In.push_back(root->data);

    //Post
    solve(root->right,In,pre,post);
    post.push_back(root->data);
}


vector<vector<int>> getTreeTraversal(TreeNode *root){
    vector<int>pre,In,post;      //PREORDER, INORDER, POSTORDER
    solve(root,In,pre,post);
    
    return {In, pre, post};
}
/*
Sample Input 1 :
1 2 3 -1 -1 -1  6 -1 -1
Sample Output 1 :
2 1 3 6 
1 2 3 6 
2 6 3 1
*/


//113. VERTICAL ORDER TRAVERSAL OF A BINARY TREE                       {T.C = O(N*LOGN), S.C = O(N)}
class Solution {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        map<int,map<int,multiset<int>>>mp;        //x(axis), y(depth), node->val
        queue<pair<TreeNode*, pair<int,int>>>q;    //node, x, y
        q.push({root, {0, 0}});
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            TreeNode* currNode = frontNode.first;
            int xVal           = frontNode.second.first;
            int yVal           = frontNode.second.second;

            mp[xVal][yVal].insert(currNode->val);
            if(currNode->left) q.push({currNode->left, {xVal-1, yVal+1}});
            if(currNode->right)q.push({currNode->right,{xVal+1, yVal+1}});
        } 

        vector<vector<int>>ans;
        for(auto it : mp){
            vector<int>vertLine;
            for(auto x : it.second){           //x(axis) traverse col & node
                vertLine.insert(vertLine.end(), x.second.begin(), x.second.end());  //insert map ele to vector
            }
            ans.push_back(vertLine);
        }
        return ans;
    }
};
/*
Example 1:
Input: root = [3,9,20,null,null,15,7]
Output: [[9],[3,15],[20],[7]]
Explanation:
Column -1: Only node 9 is in this column.
Column 0: Nodes 3 and 15 are in this column in that order from top to bottom.
Column 1: Only node 20 is in this column.
Column 2: Only node 7 is in this column.

Example 2:
Input: root = [1,2,3,4,5,6,7]
Output: [[4],[2],[1,5,6],[3],[7]]
Explanation:
Column -2: Only node 4 is in this column.
Column -1: Only node 2 is in this column.
Column 0: Nodes 1, 5, and 6 are in this column.
          1 is at the top, so it comes first.
          5 and 6 are at the same position (2, 0), so we order them by their value, 5 before 6.
Column 1: Only node 3 is in this column.
Column 2: Only node 7 is in this column.

Example 3:
Input: root = [1,2,3,4,6,5,7]
Output: [[4],[2],[1,5,6],[3],[7]]
Explanation:
This case is the exact same as example 2, but with nodes 5 and 6 swapped.
Note that the solution remains the same since 5 and 6 are in the same location and should be ordered by their values.
*/


//114. ROOT TO LEAF PATHS                                            {T.C = O(N), S.C = O(H)}
class Solution {
  public:
    void solve(Node* root, vector<int>&temp, vector<vector<int>>&ans){
        //base case
        if(!root) return;
        
        temp.push_back(root->data);
        if(!root->left && !root->right) ans.push_back(temp);
        
        if(root->left) solve(root->left, temp, ans);
        if(root->right)solve(root->right, temp, ans);
        temp.pop_back();
    }
    vector<vector<int>> Paths(Node* root) {
        vector<vector<int>>ans;
        vector<int>temp;
        solve(root, temp, ans);
        return ans;
    }
};
/*
Example 1:
Input:
       1
    /     \
   2       3
Output: 
1 2 
1 3 
Explanation: 
All possible paths:
1->2
1->3

Example 2:
Input:
         10
       /    \
      20    30
     /  \
    40   60
Output: 
10 20 40 
10 20 60 
10 30 
*/


//115. MAXIMUM WIDTH OF BINARY TREE                                      {T.C = O(N), S.C = O(N)}
class Solution {
public:
    //using level order traversal
    typedef unsigned long long ll;
    int widthOfBinaryTree(TreeNode* root) {
        queue<pair<TreeNode*, ll>>q;           //node, index 
        q.push({root, 0});
        ll maxWidth = 0;
        while(!q.empty()){
            ll lvlsz = q.size();
            ll left  = q.front().second;       //first index of level
            ll right = q.back().second;        //last index of level
            maxWidth  = max(maxWidth, right-left+1);
            for(int i = 0 ; i < lvlsz ; i++){
                auto frontNode = q.front();
                q.pop();
                TreeNode* currNode = frontNode.first;
                ll currI          = frontNode.second;
                if(currNode->left) q.push({currNode->left, 2*currI+1});  //leftIdx = 2i+1
                if(currNode->right)q.push({currNode->right,2*currI+2});  //rightIdx= 2i+2
            }
        }
        return maxWidth;
    }
};
/*
Example 1:
Input: root = [1,3,2,5,3,null,9]
Output: 4
Explanation: The maximum width exists in the third level with length 4 (5,3,null,9).

Example 2:
Input: root = [1,3,2,5,null,null,9,6,null,7]
Output: 7
Explanation: The maximum width exists in the fourth level with length 7 (6,null,null,null,null,null,7).

Example 3:
Input: root = [1,3,2,5]
Output: 2
Explanation: The maximum width exists in the second level with length 2 (3,2).
*/