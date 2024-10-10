#include<bits/stdc++.h>
using namespace std;


//DAY 19: BINARY TREE 3----------------------------------------------------------------------------------
//124.BINARY TREE MAXIMUM PATH SUM                                                 {T.C = O(N), S.C = O(H)}
class Solution {
public:
    int solve(TreeNode* root, int &maxi){
        //base case
        if(!root) return 0;

        int left = solve(root->left, maxi);
        int right = solve(root->right, maxi);
        
        int anyOnePath = max(left, right) + root->val;       //root->val == 1
        int onlyNode = root->val;
        int onlyPath = left + right + root->val;

        maxi = max({maxi, anyOnePath, onlyNode, onlyPath});
        
        return max(anyOnePath, onlyNode);                //onlyPath cant call for parent(its already ans)
        // return maxi;                           //NOT WORK
    }
    int maxPathSum(TreeNode* root) {
        int maxi = INT_MIN;
        solve(root, maxi);
        return maxi;
    }
};
/*
Example 1:
Input: root = [1,2,3]
Output: 6
Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.

Example 2:
Input: root = [-10,9,20,null,null,15,7]
Output: 42
Explanation: The optimal path is 15 -> 20 -> 7 with a path sum of 15 + 20 + 7 = 42.
*/


//125. CONSTRUCT BINARY TREE FROM PREORDER AND INORDER TRAVERSAL                 {T.C = O(N), S.C = O(N)}
class Solution {
public:
    TreeNode* inOrAndPreOr(vector<int>&preOrder, vector<int>&inOrder, int inOrStart, int inOrEnd, int &preOrIdx, map<int,int>&mp){
        //base case
        if(inOrStart > inOrEnd) return NULL;

        int rootVal = preOrder[preOrIdx];
        preOrIdx++;
        TreeNode* root = new TreeNode(rootVal);

        int i = mp[rootVal];
        
        //s__i-1 (i) i+1__e
        root->left  = inOrAndPreOr(preOrder, inOrder, inOrStart, i-1, preOrIdx, mp);   
        root->right = inOrAndPreOr(preOrder, inOrder, i+1, inOrEnd, preOrIdx, mp);

        return root;
        
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = inorder.size();
        // for(auto it : inOrder) mp[it]++;             //not work (it stores count of freq)
        map<int,int>mp;
        for(int i = 0 ; i < n ; i++){                //store val and its index
            mp[inorder[i]] = i;
        }

        int preOrIdx = 0;                         //pass by reference only
        return inOrAndPreOr(preorder, inorder, 0, n-1, preOrIdx, mp);     //0 = inOrStart, n-1 = inOrEnd
    }
};
/*
Example 1:
Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]

Example 2:
Input: preorder = [-1], inorder = [-1]
Output: [-1]
*/


//126. CONSTRUCT BINARY TREE FROM POSTORDER AND INORDER TRAVERSAL                 {T.C = O(N), S.C = O(N)}
class Solution {
public:
    TreeNode* inOrAndPoOr(vector<int>&inOrder, vector<int>&poOrder, int inOrStart, int inOrEnd, int &poOrIdx, map<int,int>&mp){
        //base case
        if(inOrStart > inOrEnd) return NULL;

        int rootVal = poOrder[poOrIdx];
        poOrIdx--;
        TreeNode* root = new TreeNode(rootVal);

        int i = mp[rootVal];

        //s___i-1 (i) i+1__e                    //R then L (reverse in post (alike pre))
        root->right = inOrAndPoOr(inOrder, poOrder, i+1, inOrEnd, poOrIdx, mp);
        root->left  = inOrAndPoOr(inOrder, poOrder, inOrStart, i-1, poOrIdx, mp);

        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = inorder.size();
        map<int,int>mp;
        for(int i = 0 ; i < n; i++){               //store val and its index
            mp[inorder[i]] = i;
        }
        int m = postorder.size();
        int poOrIdx = m-1;                         //should pass by reference
        return inOrAndPoOr(inorder, postorder, 0, n-1, poOrIdx, mp);
    }
};
/*
Example 1:
Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
Output: [3,9,20,null,null,15,7]

Example 2:
Input: inorder = [-1], postorder = [-1]
Output: [-1]
*/


//127. SYMMETRIC TREE                                                         {T.C = O(N), S.C = O(H)}
class Solution {
public:
    bool isMirror(TreeNode* p, TreeNode* q){
        //base case
        if(!p && !q) return true;
        if(!p || !q) return false;
        if(p->val != q->val) return false;

        return isMirror(p->left, q->right) && isMirror(p->right, q->left);          //for symmetric tree
        // return isEqual(p->left, q->left) && isEqual(p->right, q->right);         //for equal tree
    }
    bool isSymmetric(TreeNode* root) {
        //base case
        if(!root) return true;

        return isMirror(root->left, root->right);
    }
};
/*
Example 1:
Input: root = [1,2,2,3,4,4,3]
Output: true

Example 2:
Input: root = [1,2,2,null,3,null,3]
Output: false
*/


//128. FLATTEN BINARY TREE TO LINKED LIST                                         {T.C = O(N), S.C = O(H)}
class Solution {
public:
    void flatten(TreeNode* root) {
        TreeNode* curr = root;
        while(curr){
            if(curr->left){
                TreeNode* pred = curr->left;                 //first left
                while(pred->right) pred = pred->right;        //extreme right
                pred->right = curr->right;                //virtual pointer to curr->right(not curr{like morris})
                curr->right = curr->left;                 //update curr->right
                curr->left = NULL;                        //mark left null
            }
            curr = curr->right;
        }
    }
};
/*
Example 1:
Input: root = [1,2,5,3,4,null,6]
Output: [1,null,2,null,3,null,4,null,5,null,6]

Example 2:
Input: root = []
Output: []

Example 3:
Input: root = [0]
Output: [0]
*/


//129. MIRROR TREE                                                                   {T.C = O(N), S.C = O(H)}
class Solution {
  public:
    void mirror(Node* node) {
        //base case
        if(!node) return;
        
        mirror(node->left);
        mirror(node->right);
        
        swap(node->left, node->right);
    }
};
/*
Input:
      1
    /  \
   2    3
Output: 3 1 2
Explanation: The tree is
  1    (mirror)     1
 /  \    =>        /  \
2    3           3   2
The inorder of mirror is 3 1 2

Input:
      10
     /  \
    20   30
   /  \
  40  60
Output: 30 10 60 20 40
Explanation: The tree is
      10               10
    /    \  (mirror)    /    \
   20    30    =>   30    20
  /  \                     /   \
 40  60                 60   40
The inroder traversal of mirror is: 30 10 60 20 40.
*/


//130. CHILDREN SUM IN A BINARY TREE                                            {T.C = O(N), S.C = O(H)}
class Solution{
public:
    int isSumProperty(Node *root){
       //base case
       if(!root || (!root->left && !root->right)) return 1;            //1 = true
       
       int leftVal = 0, rightVal = 0;
       
       if(root->left) leftVal = root->left->data;
       if(root->right)rightVal= root->right->data;
       
       if(root->data != (leftVal + rightVal)) return 0;
       
       return isSumProperty(root->left) && isSumProperty(root->right);
    }
};
/*
Example 1:
Input:
Binary tree
       35
      /   \
     20  15
    /  \  /  \
   15 5 10 5
Output: 
1
Explanation: 
Here, every node is sum of its left and right child.

Example 2:
Input:
Binary tree
       1
     /   \
    4    3
   /  
  5    
Output: 
0
Explanation: 
Here, 1 is the root node and 4, 3 are its child nodes. 4 + 3 = 7 which is not equal to the value of root node. Hence, 
this tree does not satisfy the given condition.
*/