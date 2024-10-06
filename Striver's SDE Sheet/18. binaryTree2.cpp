#include<bits/stdc++.h>
using namespace std;


//DAY 18: BINARY TREE 2----------------------------------------------------------------------------------
//116. BINARY TREE LEVEL ORDER TRAVERSAL                                  {T.C = O(N), S.C = O(N)}
class Solution {
public:
    void lvlOrder(TreeNode* root, vector<vector<int>>&ans){
        //base case
        if(!root) return;

        queue<TreeNode*>q;
        q.push(root);
        while(!q.empty()){
            int sz = q.size();
            vector<int>lvlNodes;
            for(int i = 0 ; i < sz ; i++){
                auto frontNode = q.front();
                q.pop();
                lvlNodes.push_back(frontNode->val);
                if(frontNode->left) q.push(frontNode->left);
                if(frontNode->right)q.push(frontNode->right);
            }
            ans.push_back(lvlNodes);
        }
    }
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>>ans;
        lvlOrder(root, ans);
        return ans;
    }
};
/*
Example 1:
Input: root = [3,9,20,null,null,15,7]
Output: [[3],[9,20],[15,7]]

Example 2:
Input: root = [1]
Output: [[1]]

Example 3:
Input: root = []
Output: []
*/


//117. MAXIMUM DEPTH OF A BINARY TREE / HEIGHT OF BINARY TREE                      {T.C = O(N), S.C = O(H)}
class Solution {
public:
    int maxDepth(TreeNode* root) {
        //base case
        if(!root) return 0;
        
        int left = maxDepth(root->left);
        int right = maxDepth(root->right);

        return max(left, right)+1;               //1 = for current level
    }
};
/*
Example 1:
Input: root = [3,9,20,null,null,15,7]
Output: 3

Example 2:
Input: root = [1,null,2]
Output: 2
*/


//118. DIAMETER OF BINARY TREE                                             {T.C = O(N), S.C = O(H)}
class Solution {
public:
    int findDiameter(TreeNode* root, int &maxi){
        //base csae
        if(!root) return 0;

        int left = findDiameter(root->left, maxi);
        int right = findDiameter(root->right, maxi);

        maxi = max(maxi, left+right);                   //diameter is leftH + rightH

        return max(left, right) + 1;                     //include curr node

    }
    int diameterOfBinaryTree(TreeNode* root) {
        int maxi = INT_MIN;
        int ans = findDiameter(root, maxi);            //we have to pass by refernce(not call in main func)

        return  maxi;
    }
};
/*
Example 1:
Input: root = [1,2,3,4,5]
Output: 3
Explanation: 3 is the length of the path [4,2,1,3] or [5,2,1,3].

Example 2:
Input: root = [1,2]
Output: 1
*/


//119. BALANCED BINARY TREE                                                 {T.C = O(N), S.C = O(H)}
class Solution {
public:
    int findHeight(TreeNode* root){
        //base case
        if(!root) return 0;

        int left = findHeight(root->left);
        if(left == -1) return -1;

        int right = findHeight(root->right);
        if(right == -1) return -1;

        if(abs(left-right) > 1) return -1;

        return max(left, right)+1;
    }
    bool isBalanced(TreeNode* root) {
        int maxHeight = findHeight(root);

        if(maxHeight == -1) return false;
        return true;
    }
};
/*
Example 1:
Input: root = [3,9,20,null,null,15,7]
Output: true

Example 2:
Input: root = [1,2,2,3,3,null,null,4,4]
Output: false

Example 3:
Input: root = []
Output: true
*/


//120. LOWEST COMMON ANCESTOR                                                 {T.C = O(N), S.C = O(H)}
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        //base case
        if(!root) return NULL;

        if(root->val == p->val || root->val == q->val) return root;

        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        if(left && right) return root; 
        else if(left && !right) return left;
        else if(!left && right) return right;
        else return NULL;                          //!left && !right
    }
};
/*
Example 1:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.

Example 2:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.

Example 3:
Input: root = [1,2], p = 1, q = 2
Output: 1
*/


//121. SAME TREE                                                           {T.C = O(N), S.C = O(H)}
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(!p && !q) return true;
        if(!p || !q) return false;

        if(p->val != q->val) return false;

        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};
/*
Example 1:
Input: p = [1,2,3], q = [1,2,3]
Output: true

Example 2:
Input: p = [1,2], q = [1,null,2]
Output: false

Example 3:
Input: p = [1,2,1], q = [1,1,2]
Output: false
*/


//122. BINARY TREES ZIG ZAG LEVEL ORDER TRAVERSAL                             {T.C = O(N), S.C = O(N)}
class Solution {
public:
    void lvlOrder(TreeNode* root, vector<vector<int>>&ans){
        //base case
        if(!root) return;

        bool leftToRight = true;
        queue<TreeNode*>q;
        q.push(root);

        while(!q.empty()){
            int sz = q.size();
            vector<int>temp;
            for(int i = 0 ; i < sz ; i++){
                auto frontNode = q.front();
                q.pop();
                temp.push_back(frontNode->val);
                if(frontNode->left) q.push(frontNode->left);
                if(frontNode->right)q.push(frontNode->right);
            }
            if(!leftToRight) reverse(temp.begin(), temp.end());     //logic for zigzag
            ans.push_back(temp);
            leftToRight = !leftToRight;
        }
    }
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>>ans;
        lvlOrder(root, ans);

        return ans;
    }
};
/*
Example 1:
Input: root = [3,9,20,null,null,15,7]
Output: [[3],[20,9],[15,7]]

Example 2:
Input: root = [1]
Output: [[1]]

Example 3:
Input: root = []
Output: []
*/


//123. TREE BOUNDARY TRAVERSAL                                                  {T.C = O(N), S.C = O(H)}
class Solution {
public:
    void traversalLeft(Node* root, vector<int>&ans){
        //base case
        if(!root || !root->left && !root->right) return;
        
        ans.push_back(root->data);
        if(root->left) traversalLeft(root->left, ans);
        else traversalLeft(root->right,ans);
    }
    
    void traversalLeaf(Node* root, vector<int>&ans){
        //base case
        if(!root) return;
        
        if(!root->left && !root->right){           //LEAF NODES
            ans.push_back(root->data);
        }
        
        traversalLeaf(root->left, ans);
        traversalLeaf(root->right, ans);
    }
    
    void traversalReverseRight(Node* root, vector<int>&ans){
        //base case
        if(!root || !root->left && !root->right) return;
        
        if(root->right) traversalReverseRight(root->right, ans);
        else traversalReverseRight(root->left, ans);
        
        //wapas ate samay print karo
        ans.push_back(root->data);
        
    }
    vector <int> boundary(Node *root){
        vector<int>ans;
        
        //base case
        if(!root) return ans;
        
        ans.push_back(root->data);             //push root data
        
        //left call
        traversalLeft(root->left, ans);
        
        //leaf call (left, right)
        //left subtree
        traversalLeaf(root->left, ans);
        //right subtree
        traversalLeaf(root->right, ans);
        
        //reverse right call
        traversalReverseRight(root->right, ans);
        
        return ans;
    }
};
/*
Example 1:
Input:
        1 
      /   \
     2     3  
    / \   / \ 
   4   5 6   7
      / \
     8   9
   
Output: 1 2 4 8 9 6 7 3

Example 2:
Input:
            1
           /
          2
        /  \
       4    9
     /  \    \
    6    5    3
             /  \
            7     8

Output: 1 2 4 6 5 7 8
Explanation:
*/