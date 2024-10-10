#include<bits/stdc++.h>
using namespace std;


//DAY 21. BINARY SEARCH TREE II --------------------------------------------------------------------------------------------
//138. FLOOR IN BST                                                           {T.C = O(N), S.C = O(H)}
int floorInBST(TreeNode<int> * root, int target){
    TreeNode<int>* temp = root;       //not required
    int pred = -1;
    //just like find predecessor
    while(temp){
        if(temp->val > target) temp = temp->left;           //in predeccsor >= 
        else{
            pred = temp->val;
            temp = temp->right;
        }
    }
    return pred;
}
/*
Sample Input 1:
2
10 5 15 2 6 -1 -1 -1 -1 -1 -1
7
2 1 3 -1 -1 -1 -1
2
Sample Output 1:
6
2
*/


//139. CEIL IN BST                                                           {T.C = O(N), S.C = O(H)}
int findCeil(BinaryTreeNode<int> *temp, int target){
    int succ = -1;
    //just like find successor
    while(temp){
        if(temp->data < target) temp = temp->right;  //in successor <=
        else{
            succ = temp->data;
            temp = temp->left; 
        }
    }
    return succ;
}
/*
Sample Input 1:
2
8 5 10 2 6 -1 -1 -1 -1 -1 7 -1 -1
4
8 5 10 2 6 -1 -1 -1 -1 -1 7 -1 -1
7
Sample Output 1:
5
7
*/


//140. KTH SMALLEST ELEMENT IN A BST                                
//BRUTE FORCE TREE TO VEC (BST INORDER GIVES SORTED ARR)                       {T.C = O(N), S.C = O(N)}
class Solution {
public:
    void treeToArr(TreeNode* root, vector<int>&vec){
        //base case
        if(!root) return;

        //inorder
        treeToArr(root->left, vec);
        vec.push_back(root->val);
        treeToArr(root->right, vec);
    }
    int kthSmallest(TreeNode* root, int k) {
        vector<int>vec;
        treeToArr(root, vec);

        return vec[k-1];
    }
};
/*
Example 1:
Input: root = [3,1,4,null,2], k = 1
Output: 1

Example 2:
Input: root = [5,3,6,2,4,null,null,1], k = 3
Output: 3
*/

//141. KTH LARGEST ELEMENT IN A BST                                             {T.C = O(N), S.C = O(N)}
class Solution
{
    public:
    void inOrder(Node* root, vector<int>&vec){
        //base case
        if(!root) return;
        
        inOrder(root->left, vec);
        vec.push_back(root->data);
        inOrder(root->right, vec);
    }
    int kthLargest(Node *root, int K){
        vector<int>vec;
        inOrder(root, vec);
        
        reverse(vec.begin(), vec.end());            //for finding largest
        return vec[K-1];
    }
};
/*
Example 1:
Input:
      4
    /   \
   2     9
k = 2 
Output: 4

Example 2:
Input:
       9
        \ 
          10
K = 1
Output: 10
*/


//142. TWO SUM IV                                                                 {T.C = O(N), S.C = O(N)}
class Solution {
public:
    void inOrder(TreeNode* root, vector<int>&vec){
        //base case
        if(!root) return;

        inOrder(root->left, vec);
        vec.push_back(root->val);
        inOrder(root->right, vec);
    }
    bool findTarget(TreeNode* root, int k) {
        vector<int>vec;
        inOrder(root, vec);

        int n = vec.size();
        int i = 0, j = n-1;
        while(i < j){                          //not <=
            long long sum = vec[i]+vec[j];
            if(sum == k) return true;
            else if(sum < k) i++;
            else j--;
        }
        return false;
    }
};
/*
Example 1:
Input: root = [5,3,6,2,4,null,7], k = 9
Output: true

Example 2:
Input: root = [5,3,6,2,4,null,7], k = 28
Output: false
*/


//143. BINARY SEARCH TREE ITERATOR                                           {T.C = O(1), S.C = O(H)}
class BSTIterator {
public:
    stack<TreeNode*>stk;
    BSTIterator(TreeNode* root) {
        while(root){                          //push all left 
            stk.push(root); 
            root = root->left;
        }
    }
    
    int next() {
        TreeNode* curr = stk.top();
        stk.pop();
        if(curr->right){                     //if right exist push all its left(extrem left)
            TreeNode* temp = curr->right;
            while(temp){
                stk.push(temp);
                temp = temp->left;
            }
        }
        return curr->val;
    }
    
    bool hasNext() {
        return !stk.empty();                       //not empty then true else false
    }
};
/*
Example 1:
Input
["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
[[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
Output
[null, 3, 7, true, 9, true, 15, true, 20, false]
Explanation
BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
bSTIterator.next();    // return 3
bSTIterator.next();    // return 7
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 9
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 15
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 20
bSTIterator.hasNext(); // return False
*/


//144a. LARGEST BST                                                             {T.C = O(N). S.C = O(H)}
class NodeVal{
public:
    int minNode, maxNode, maxSize;
    
    NodeVal(int minNode, int maxNode, int maxSize){
        this->minNode = minNode;
        this->maxNode = maxNode;
        this->maxSize = maxSize;
    }
};
class Solution{
    public:
    NodeVal solve(Node* root){
        //base case
        if(!root) return NodeVal(INT_MAX, INT_MIN, 0);
        
        auto leftTree = solve(root->left);
        auto rightTree= solve(root->right);
        
        //valid bst(left part max < node < right part min)
        if(leftTree.maxNode < root->data && root->data < rightTree.minNode){
            return NodeVal(
                min(root->data, leftTree.minNode), 
                max(root->data, rightTree.maxNode), 
                leftTree.maxSize+rightTree.maxSize + 1
            );
        }
        
        //not valid
        return NodeVal(INT_MIN, INT_MAX, max(leftTree.maxSize, rightTree.maxSize));
    }
    int largestBst(Node *root){
    	return solve(root).maxSize;
    }
};
/*
Input:   1
        /  \
        4   4              
       / \ 
      6   8
Output: 1 
Explanation: There's no sub-tree with size greater than 1 which forms a BST. All the leaf Nodes are the BSTs with size equal to 1.

Input:    6
        /   \
      6      2              
       \    / \
        2  1   3
Output: 3
Explanation: The following sub-tree is a BST of size 3:  2
                                                       /   \
                                                      1     3
*/


//144b. MAXIMUM SUM BST IN A BINARY TREE                                       
//BRUTE FORCE(FIND VALID BST THEN FIND MAX SUM OF EACH BST)                     {T.C = O(N^2), S.C = O(H)}
class Solution {
public:
    bool isValidBST(TreeNode* root, long long lowerBound, long long upperBound){
        //base case
        if(!root) return true;
        if(lowerBound >= root->val || root->val >= upperBound) return false;
        return isValidBST(root->left, lowerBound, root->val) && isValidBST(root->right, root->val, upperBound);
    }
    int bstSum(TreeNode* root){
        //base case
        if(!root) return 0;
        return root->val + bstSum(root->left) + bstSum(root->right);
    }
    int maxSumBST(TreeNode* root) {
        //base case
        if(!root) return 0;

        int sum = 0;
        if(isValidBST(root, LLONG_MIN, LLONG_MAX)){
            sum = bstSum(root);
        }
        int leftBSTSum = maxSumBST(root->left);
        int rightBSTSum= maxSumBST(root->right);

        return max({sum , leftBSTSum, rightBSTSum});
    }
};

//OPTIMIZED APPROACH                                                            {T.C = O(N), S.C = O(H)}
class NodeVal {
public:
    int minNode, maxNode, maxSize, maxSum;
    NodeVal(int minNode, int maxNode, int maxSize, int maxSum) {
        this->minNode = minNode;
        this->maxNode = maxNode;
        this->maxSize = maxSize;
        this->maxSum  = maxSum;
    }
};

class Solution {
public:
    int globalMaxSum = 0;  // To track the maximum sum of any valid BST in the tree

    NodeVal solve(TreeNode* root) {
        //base case
        if (!root) return NodeVal(INT_MAX, INT_MIN, 0, 0);

        auto leftTree = solve(root->left);
        auto rightTree = solve(root->right);

        // Check if the current subtree is a valid BST
        if (leftTree.maxNode < root->val && root->val < rightTree.minNode) {
            // It's a valid BST, so calculate its size and sum
            int currentSum = leftTree.maxSum + rightTree.maxSum + root->val;
            globalMaxSum = max(globalMaxSum, currentSum);  // Update the global maximum sum
            return NodeVal(
                min(root->val, leftTree.minNode),
                max(root->val, rightTree.maxNode),
                leftTree.maxSize + rightTree.maxSize + 1,
                currentSum
            );
        }

        // If not a valid BST, return invalid bounds and a max sum of 0
        return NodeVal(INT_MIN, INT_MAX, 0, 0);
    }

    int maxSumBST(TreeNode* root) {
        solve(root);
        return globalMaxSum;                          // Return the global maximum sum found
    }
};

/*
Example 1:
Input: root = [1,4,3,2,4,2,5,null,null,null,null,null,null,4,6]
Output: 20
Explanation: Maximum sum in a valid Binary search tree is obtained in root node with key equal to 3.

Example 2:
Input: root = [4,3,null,1,2]
Output: 2
Explanation: Maximum sum in a valid Binary search tree is obtained in a single root node with key equal to 2.

Example 3:
Input: root = [-4,-2,-5]
Output: 0
Explanation: All values are negatives. Return an empty BST.
*/


//145. SERIALIZE AND DESERIALIZE BINARY TREE                                 {T.C = O(N), S.C = O(N)}
class Codec {
public:
    void btToStr(TreeNode* root, string &serAns){
        // base case
        if(!root){
            serAns += "N ";  // for NULL
            return;
        }
        // using preorder
        serAns += to_string(root->val) + ' ';
        btToStr(root->left, serAns);
        btToStr(root->right, serAns);
    }

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string serAns = "";
        btToStr(root, serAns);
        return serAns;
    }

    TreeNode* strToBt(string &data, int &i){
        if(data[i] == 'N'){
            i += 2;  // skip 'N' and space
            return NULL;
        }

        string temp = "";
        while(data[i] != ' '){
            temp += data[i];
            i++;
        }
        //preorder
        TreeNode* root = new TreeNode(stoi(temp));
        i++;  // skip space
        root->left = strToBt(data, i);
        root->right = strToBt(data, i);

        return root;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int i = 0;
        return strToBt(data, i);
    }
};
/*
Example 1:
Input: root = [1,2,3,null,null,4,5]
Output: [1,2,3,null,null,4,5]

Example 2:
Input: root = []
Output: []
*/