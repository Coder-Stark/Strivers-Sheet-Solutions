#include<bits/stdc++.h>
using namespace std;


//DAY 20. BINARY SEARCH TREE--------------------------------------------------------------------------------------------
//131. POPULATING NEXT RIGHT POINTERS IN EACH NODE                              {T.C = O(N), S.C = O(N)}
class Solution {
public:
    void lvlOrder(Node* root){
        //base case
        if(!root) return;
        
        queue<Node*>q;
        q.push(root);
        while(!q.empty()){
            int sz = q.size();
            Node* prev = NULL;
            for(int i = 0 ; i < sz ; i++){
                auto frontNode = q.front();
                q.pop();
                if(prev) prev->next = frontNode;
                prev = frontNode;

                if(frontNode->left) q.push(frontNode->left);
                if(frontNode->right)q.push(frontNode->right);
            }
            prev->next = NULL;                       //mark end of lvl NULL
        }
    }
    Node* connect(Node* root) {
        lvlOrder(root);
        return root;
    }
};
/*
Example 1:
Input: root = [1,2,3,4,5,6,7]
Output: [1,#,2,3,#,4,5,6,7,#]
Explanation: Given the above perfect binary tree (Figure A), your function should populate each next pointer to point to its next right node, just like in Figure B. The serialized output is in level order as connected by the next pointers, with '#' signifying the end of each level.

Example 2:
Input: root = []
Output: []
*/


//132. SEARCH IN A BINARY SEARCH TREE                                          {T.C = O(N), S.C = O(H)}
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        //base case
        if(!root) return NULL;

        if(root->val == val) return root;
        else if(root->val > val) return searchBST(root->left, val);
        else return searchBST(root->right, val);                        //if(root->val < val)
    }
};
/*
Example 1:
Input: root = [4,2,7,1,3], val = 2
Output: [2,1,3]

Example 2:
Input: root = [4,2,7,1,3], val = 5
Output: []
*/


//133. CONVERT SORTED ARRAY TO BINARY SEARCH TREE                                {T.C = O(N), S.C = O(N)}
//BST INORDER IS SORTED
class Solution {
public:
    TreeNode* inOrder(vector<int>&nums){
        int n = nums.size();
        //base case
        if(n == 0) return NULL;

        int mid = n/2;
        TreeNode* root = new TreeNode(nums[mid]);
        vector<int>leftSubTree(nums.begin(), nums.begin()+mid);    //left to mid
        vector<int>rightSubTree(nums.begin()+mid+1, nums.end());   //after mid to right

        root->left = inOrder(leftSubTree);
        root->right = inOrder(rightSubTree);

        return root;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return inOrder(nums);
    }
};
/*
Example 1:
Input: nums = [-10,-3,0,5,9]
Output: [0,-3,9,-10,null,5]
Explanation: [0,-10,5,null,-3,null,9] is also accepted:

Example 2:
Input: nums = [1,3]
Output: [3,1]
Explanation: [1,null,3] and [3,1] are both height-balanced BSTs.
*/


//134. CONSTRUCT BINARY SEARCH TREE USING PREORDER TRAVERSAL                       {T.C = O(N), S.C = O(H)}
class Solution {
public:
    TreeNode* solve(vector<int>&preOrder, int &i, int upperBound){
        int n = preOrder.size();
        //base case
        if(i >= n || preOrder[i] > upperBound) return NULL;

        TreeNode* root = new TreeNode(preOrder[i]);
        i++;

        root->left = solve(preOrder, i, root->val);       //ub = rootVal (bst)
        root->right= solve(preOrder, i, upperBound);     

        return root;
    }
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int i = 0;
        return solve(preorder, i, INT_MAX);            //INT_MAX = upper bound
    }
};
/*
Example 1:
Input: preorder = [8,5,1,7,10,12]
Output: [8,5,10,1,7,null,12]

Example 2:
Input: preorder = [1,3]
Output: [1,null,3]
*/


//135. VALIDATE BINARY SEARCH TREE                                           {T.C = O(N), S.C = O(H)}
class Solution {
public:
    bool isValid(TreeNode* root, long long lowerBound, long long upperBound){
        //base case
        if(!root) return true;

        if(lowerBound >= root->val || root->val >= upperBound) return false;

        return isValid(root->left, lowerBound, root->val) && isValid(root->right, root->val, upperBound);
    }
    bool isValidBST(TreeNode* root) {
        return isValid(root, LLONG_MIN, LLONG_MAX);              //lower and upper bound (int wont work)
    }
};
/*
Example 1:
Input: root = [2,1,3]
Output: true

Example 2:
Input: root = [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.
*/


//136. LOWEST COMMON ANCESTOR OF A BINARY SEARCH TREE       
//USING SIMPLE LCA IN BT                                                            {T.C = O(N), S.C = O(H)}
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        //base case
        if(!root) return NULL;

        if(root->val == p->val || root->val == q->val) return root;

        TreeNode* leftSubTree = lowestCommonAncestor(root->left, p, q);
        TreeNode* rightSubTree= lowestCommonAncestor(root->right,p, q);

        if(leftSubTree && rightSubTree) return root;
        else if(!leftSubTree && rightSubTree) return rightSubTree;
        else if(leftSubTree && !rightSubTree) return leftSubTree;
        else return NULL;                             //!left && !right
    }
};

//USING PROPERTY OF BST                                                              {T.C = O(N), S.C = O(H)}
class Solution {
public:
    //using bst property 
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        //base case
        if(!root) return NULL;

        if(root->val > p->val && root->val > q->val){
            return lowestCommonAncestor(root->left, p, q);         //DIRECT RETURN
        } 
        else if(root->val < p->val && root->val < q->val){
            return lowestCommonAncestor(root->right,p, q);
        }
        return root;
    }
};
/*
Example 1:
Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
Output: 6
Explanation: The LCA of nodes 2 and 8 is 6.

Example 2:
Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
Output: 2
Explanation: The LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.

Example 3:
Input: root = [2,1], p = 2, q = 1
Output: 2
*/


//137. PREDECESSOR AND SUCCESSOR (IN BST)                                    {T.C = O(H), S.C = O(1)}
class Solution
{
    public:
    void findPreSuc(Node* root, Node*& pre, Node*& suc, int target){
        //base case
        if(!root) return;
        
        //for successor
        Node* temp = root;
        while(temp){
            if(temp->key <= target) temp = temp->right;
            else{
                suc = temp;
                temp = temp->left;                      //minimize range(closest succ)
            }
        }
        //for pred
        temp = root;              //reset
        while(temp){
            if(temp->key >= target) temp = temp->left;
            else{
                pre = temp;
                temp = temp->right;                     //maximize range(closes pred)
            }
        }
    }
};
/*
Example 1:
Input:
      8
    /   \
   1     9
    \     \
     4    10
    /
   3
key = 8 
Output: 4 9
Explanation: 
In the given BST the inorder predecessor of 8 is 4 and inorder successor of 8 is 9.

Example 2:
Input:
        10
      /   \
     2    11
   /  \ 
  1    5
      /  \
     3    6
      \
       4
key = 11
Output: 10 -1
Explanation:In given BST, the inorder predecessor of 11 is 10 whereas it does not have any inorder successor.
*/