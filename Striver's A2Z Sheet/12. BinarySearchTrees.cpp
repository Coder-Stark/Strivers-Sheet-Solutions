//BINARY SEARCH TREES (BST)

#include<bits/stdc++.h>
using namespace std;


//CONCEPTS-------------------------------------------------------------------------------------------
//274. INTRODUCTION TO BINARY SEARCH TREES                              {T.C = O(N), S.C = O(1)}
//BST'S INORER IS IN SORTED ORDER , IF NOT THEN IT IS NOT AN BST
class Solution {
  public:
    bool isBSTTraversal(vector<int>& arr) {
        for(int i = 1 ;  i < arr.size() ; i++){
            if(arr[i-1] >= arr[i]) return false;
        }
        return true;
    }
};
/*
Input: arr[] = [8, 14, 45, 64, 100]
Output: True
Input: arr[] = [5, 6, 1, 8, 7]
Output: False
*/


//275. SEARCH IN BINARY SEARCH TREE                                    {T.C = O(N), S.C = O(H)}
//ROOT > VAL ? SEARCH IN LEFT : SEARCH IN RIGHT
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        //base case
        if(!root) return NULL;

        if(root->val == val) return root;
        if(root->val > val) return searchBST(root->left, val);
        else return searchBST(root->right, val);
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


//276. MINIMUM ELEMENT IN BST                                       {T.C = O(N OR H), S.C = O(1)}
//LEFT LEAF NODE IS SMALLEST IN BST
class Solution {
  public:
    int minValue(Node* root) {
        //base case
        if(!root) return -1;
        int ans = -1;
        while(root->left){
            root = root->left;
        }
        ans = root->data;
        return ans;
    }
};
/*
Example 1:
Input:
           5
         /    \
        4      6
       /        \
      3          7
     /
    1
Output: 1

Example 2:
Input:
             9
              \
               10
                \
                 11
Output: 9
*/


//PRACTISE PROBLEMS-------------------------------------------------------------------------------------
//277. CEIL IN BST                                           {T.C = O(H), S.C = O(1)}
//ROOT >= INPUT ? ROOT->DATA , ROOT = ROOT->LEFT : ROOT = ROOT->RIGHT 
int findCeil(Node* root, int input) {
    //base case
    if (!root) return -1;
    
    int ceilVal = -1;
    while(root){
        if(root->data == input){
            ceilVal = root->data;
            return ceilVal;
        }else if(root->data > input){
            ceilVal = root->data;
            root = root->left;
        }else{ //root->data < input
            root = root->right;
        }
    }
    return ceilVal;
}
/*
Example 1:
Input:
      5
    /   \
   1     7
    \
     2 
      \
       3
X = 3
Output: 3
Explanation: We find 3 in BST, so ceil
of 3 is 3.

Example 2:
Input:
     10
    /  \
   5    11
  / \ 
 4   7
      \
       8
X = 6
Output: 7
Explanation: We find 7 in BST, so ceil
of 6 is 7.
*/


//278. FLOOR IN BST                                           {T.C = O(H), S.C = O(1)}
//ROOT <= X ? ROOT->DATA , ROOT = ROOT->RIGHT : ROOT = ROOT->LEFT 
class Solution{
public:
    int floor(Node* root, int x) {
        //base case
        if(!root) return -1;
        
        int floorVal = -1;
        while(root){
            if(root->data == x){
                floorVal = root->data;
                return floorVal;
            }
            else if(root->data < x){             //just reverse of ceil
              floorVal = root->data;
              root = root->right;
            }else{ //root->data > x
                root = root->left;
            }
        }
        
        return floorVal;
    }
};
/*
Example:
Input:
n = 7               2
                     \
                      81
                    /     \
                 42       87
                   \       \
                    66      90
                   /
                 45
x = 87
Output:
87
Explanation:
87 is present in tree so floor will be 87.

Example 2:
Input:
n = 4                     6
                           \
                            8
                          /   \
                        7       9
x = 11
Output:
9
*/


//279. INSERT INTO A BINARY SEARCH TREE                         {T.C = O(H), S.C = O(1)}
//MAKE NEW NODE, IF NO ROOT RETURN NEWNODE, CHECK VAL INSERT IN LEFT LEAF OR RIGHT LEAF ACCORDINGLY
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        TreeNode* newNode = new TreeNode(val);
        //base case
        if(!root) return newNode;
        TreeNode* curr = root;
        while(curr){
            if(curr->val > val){                          //move left
                if(curr->left) curr = curr->left;         //reach to leaf node
                else{         
                    curr->left = newNode;                 //insert newnode on leaf
                    break;
                }
            }else{                                        //move right
                if(curr->right) curr = curr->right;
                else{
                    curr->right = newNode;
                    break;
                }
            }
        }
        return root;
    }
};
/*
Example 1:
Input: root = [4,2,7,1,3], val = 5
Output: [4,2,7,1,3,5]
Explanation: Another accepted tree is:

Example 2:
Input: root = [40,20,60,10,30,50,70], val = 25
Output: [40,20,60,10,30,50,70,null,null,25]

Example 3:
Input: root = [4,2,7,1,3,null,null,null,null,null,null], val = 5
Output: [4,2,7,1,3,5]
*/


//280. DELETE NODE IN A BST                                      {T.C = O(H), S.C = O(H)}
//DELETE 3 WAYS OF CHILD(0 ,1 , 2(REPLACE MINVAL(RIGHT) OR MAXVAL(LEFT)){FOR MAINTAIN BST})
class Solution {
public:
    TreeNode* minValue(TreeNode* root){
        TreeNode* temp = root;
        while(temp->left){
            temp = temp->left;
        }
        return temp;
    }
    TreeNode* deleteNode(TreeNode* root, int key) {
        //base case
        if(!root) return NULL;

        if(root->val == key){
            //0 child / leaf node delete
            if(!root->left && !root->right){
                delete root;
                return NULL;
            }

            //1 child either left or right node delete
            if(root->left && !root->right){
                TreeNode* temp = root->left;
                delete root;
                return temp;
            }
            if(!root->left && root->right){
                TreeNode* temp = root->right;
                delete root;
                return temp;
            }

            //2 child node delete 
            //2 options minVal from right or maxVal from left
            TreeNode* temp = minValue(root->right);
            root->val = temp->val;                                 //replace root to minval
            root->right = deleteNode(root->right, temp->val);      //remove right(minval)
            return root;
        }
        else if(root->val > key){           //val present in left subtree
            root->left = deleteNode(root->left, key);
            return root;
        }else{ //root->val < key            //val present in right subtree
            root->right = deleteNode(root->right,  key);
            return root;
        }
        return root;
    }
};
/*
Example 1:
Input: root = [5,3,6,2,4,null,7], key = 3
Output: [5,4,6,2,null,null,7]
Explanation: Given key to delete is 3. So we find the node with value 3 and delete it.
One valid answer is [5,4,6,2,null,null,7], shown in the above BST.
Please notice that another valid answer is [5,2,6,null,4,null,7] and it's also accepted.

Example 2:
Input: root = [5,3,6,2,4,null,7], key = 0
Output: [5,3,6,2,4,null,7]
Explanation: The tree does not contain a node with value = 0.

Example 3:
Input: root = [], key = 0
Output: []
*/


//281. KTH SMALLEST ELEMENT IN A BST                                  {T.C = O(N), S.C = O(N)}
//STORE INORDER(SORTED ORDER) NODES IN VECTOR RETURN K-1(1 BASED INDEX)
class Solution {
public:
    void solve(TreeNode* root, vector<int>&v){
        //base case
        if(!root) return;
        //LNR (inorder is already sorted order)
        solve(root->left, v);
        v.push_back(root->val);
        solve(root->right, v);
    }
    int kthSmallest(TreeNode* root, int k) {
        vector<int>v;
        solve(root, v);
        return v[k - 1] ;                        //-1 for 1 based indexing
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


//282. VALIDATE BINARY SEARCH TREE                            {T.C = O(N), S.C = O(N)}
//MINI < ROOT < MAX
class Solution {
public:
    bool bst(TreeNode* root, long long mini, long long maxi){ // Using long long to cover the edge case of INT_MIN and INT_MAX
        //base case
        if(!root) return true;
        
        if(root->val <= mini || root->val >= maxi) return false;
    
        return bst(root->left, mini, root->val) && bst(root->right, root->val, maxi);
    }
    bool isValidBST(TreeNode* root) {
        return bst(root, LLONG_MIN, LLONG_MAX); // Using LLONG_MIN and LLONG_MAX for initial minimum and maximum values, INT_MIN & INT_MAX NOT WORKS
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


//283. LOWEST COMMON ANCESTOR (LCA) OF A BINARY SEARCH TREE            
//BRUTE FORCE (CODE OF BINARY TREE (NOT BST))                         {T.C = O(N), S.C = O(N)}
//ROOT = P || Q (ROOT), L & R (ROOT), R(R), L (L) , {} (NULL)
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
        else return NULL;                            //!left && !right
    }
};

//USING BST PROPERTY                                       {T.C = O(H), S.C = O(1)}
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        //base case
        if(!root) return NULL;
        
        if(root->val > p->val && root->val > q->val){
            return lowestCommonAncestor(root->left, p, q);
        }
        else if(root->val < p->val && root->val < q->val){
            return lowestCommonAncestor(root->right, p, q);
        }

        return root;                                    //branching point (LCA)
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


//284. CONSTRUCT BINARY SEARCH TREE FROM PREORDER TRAVERSAL                       {T.C- O(N), S.C = O(H)}
//TAKE INDEX AND BOUND(LEFT SUBTREE MAX < ROOT), RIGHT SUBTREE MAX <= BOUND
class Solution {
public:
    TreeNode* solve(vector<int>&preorder, int &i , int bound){
        //base case
        if(i == preorder.size() || preorder[i] > bound) return NULL;

        TreeNode* root = new TreeNode(preorder[i++]);
        root->left = solve(preorder, i, root->val);            //left subtree max < root
        root->right = solve(preorder, i, bound);
        return root;
    }
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int i = 0;
        return solve(preorder, i, INT_MAX);                   //INT_MAX == BOUND
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


//285a. INORDER SUCCESSOR IN BST                                        
//BRUTE FORCE                                                         {T.C = O(N), S.C = O(N)}
//STORE INORDER(SORTED) NODE IN VECTOR AND RETURN X+1TH NODE
class Solution{
  public:
    void inOrder(Node* root, vector<Node*>&ans){
        //base case
        if(!root) return;
        //LNR
        inOrder(root->left, ans);
        ans.push_back(root);
        inOrder(root->right, ans);
    }
    Node * inOrderSuccessor(Node *root, Node *x)
    {
        vector<Node*>ans;
        inOrder(root, ans);
 
        for(int i = 0 ; i < ans.size() ; i++){
            if(ans[i] == x && i+1 < ans.size()){
                return ans[i+1];
            }
        }
        return NULL;
    }
};

//OPTIMIZED APPROACH                                             {T.C = O(H), S.C = O(1)}
//IF ROOT <= X MOVE RIGHT ELSE STORE ROOT IN SUCC(ROOT IS SUCC) AND MOVE LEFT 
class Solution{
  public:
    Node * inOrderSuccessor(Node *root, Node *x)
    {
        Node* succ = NULL;
        
        while(root){
            if(root->data <= x->data){
                root = root->right;
            }else{
                succ = root;                   //first store then move left(root is succ)
                root = root->left;
            }
        }
        return succ;
    }
};

//285b. INORDER PREDESORSOR IN BST                                   {T.C = O(H), S.C = O(1)}
//USING ABOVE LOGIC SLIGHT MODIFICATION
class Solution{
  public:
    Node * preOrderSuccessor(Node *root, Node *x)
    {
        Node* pred = NULL;
        
        while(root){
            if(root->data >= x->data){
                root = root->left;
            }else{
                pred = root;                   //first store then move left(root is succ)
                root = root->left;
            }
        }
        return pred;
    }
};
/*
Example 1:
Input:
      2
    /   \
   1     3
K(data of x) = 2
Output: 3 
Explanation: 
Inorder traversal : 1 2 3 
Hence, inorder successor of 2 is 3.

Example 2:
Input:
             20
            /   \
           8     22
          / \
         4   12
            /  \
           10   14
K(data of x) = 8
Output: 10
Explanation:
Inorder traversal: 4 8 10 12 14 20 22
Hence, successor of 8 is 10.
*/


//286. MERGE 2 BST'S                                              {T.C = O(N), S.C = O(N)}
//STORE INORDER(SORTED ANS IN 2 VECTORS), THEN MEREGE THE VECTOR USING 3 POINTERS(I(A), J(B), K(MERGE VECTOR))
class Solution
{
    public:
    void inOr(Node* root, vector<int>&v){
        //base case
        if(root == NULL) return;
        
        //LNR
        inOr(root->left, v);
        v.push_back(root->data);
        inOr(root->right, v);
    }
    vector<int>mergeBST(vector<int>&a, vector<int>&b){
        vector<int>ans(a.size() + b.size());
        
        int i = 0, j = 0, k = 0;         //i(a), j(b), k(merged vector)
        while(i < a.size() && j < b.size()){
            if(a[i] < b[j]){
                ans[k] = a[i];
                k++, i++;
            }
            else{ //(a[i] > b[j])
                ans[k] = b[j];
                k++, j++;
            }
        }
        while(i < a.size()){
            ans[k] = a[i];
            k++, i++;
        }
        while(j < b.size()){
            ans[k] = b[j];
            k++, j++;
        }
        
        return ans;
    }
    vector<int> merge(Node *root1, Node *root2)
    {
        vector<int>v1, v2;
        inOr(root1,v1);
        inOr(root2, v2);
        
        return mergeBST(v1, v2);
    }
};
/*
Example 1:
Input:
BST1:
       5
     /   \
    3     6
   / \
  2   4  
BST2:
        2
      /   \
     1     3
            \
             7
            /
           6
Output: 1 2 2 3 3 4 5 6 6 7
Explanation: 
After merging and sorting the
two BST we get 1 2 2 3 3 4 5 6 6 7.

Example 2:
Input:
BST1:
       12
     /   
    9
   / \    
  6   11
BST2:
      8
    /  \
   5    10
  /
 2
Output: 2 5 6 8 9 10 11 12
Explanation: 
After merging and sorting the
two BST we get 2 5 6 8 9 10 11 12.
*/


//287. 2 SUM IV INPUT BST                                         {T.C = O(N), S.C = O(N)}
//STORE INORDER(SORTED IN VECTOR), USE 2 POINTERS(START & END) AND SEARCH FOR TARGET
class Solution {
public:
    void inOrder(TreeNode* root, vector<int>&ans){
        //base case
        if(!root) return;
        //LNR
        inOrder(root->left, ans);
        ans.push_back(root->val);
        inOrder(root->right, ans);
    }
    bool findTarget(TreeNode* root, int k) {
        vector<int>ans;
        inOrder(root, ans);
        int n = ans.size();
        int i = 0, j = n-1;
        while(i < j){
            long long sum = (long long)ans[i]+ans[j];
            if(sum == k){
                return true;
                break;
            } 
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


//288. RECOVER BINARY SEARCH TREE
//BRUTE FORCE                                                   {T.C = O(N), S.C = O(N)}
//STORE INORDER IN VECTOR, THEN CHECK FOR VALID POSITION IF NOT SWAP CURR WITH ROOT
class Solution {
public:
    void inOrder(TreeNode* root, vector<int>&ans){
        //base case
        if(!root) return;
        //LNR
        inOrder(root->left, ans);
        ans.push_back(root->val);
        inOrder(root->right, ans);
    }
    void check(TreeNode* root, vector<int>&ans, int &i){
        //base case
        if(!root) return;
        //LNR
        check(root->left, ans, i);
        if(ans[i] != root->val){
            swap(ans[i], root->val);
        } 
        i++;
        check(root->right, ans, i);
    }
    void recoverTree(TreeNode* root) {
        vector<int>ans;
        inOrder(root, ans);
        sort(ans.begin(), ans.end());
        int i = 0;
        check(root, ans, i);                        //0 = initial index
    }
};

//OPTIMIZED APPROACH                                          {T.C = O(N), S.C = O(1)}
//USE 3 POINTERS (PREV, FIRST, LAST) AND SWAP FIRST AND LAST
class Solution {
public:
    void markTree(TreeNode* root, TreeNode*&prev, TreeNode* &first, TreeNode* &last){
        //base case
        if(!root) return;
        //LNR
        markTree(root->left, prev, first, last);
        if(prev){
            if(root->val < prev->val){
                if(!first) first = prev;
                last = root;
            }
        }
        prev = root;
        markTree(root->right, prev, first, last);
    }
    void recoverTree(TreeNode* root) {
        TreeNode *prev = NULL, *first = NULL, *last = NULL;
        markTree(root, prev, first, last);
        swap(first->val, last->val);
    }
};
/*
Example 1:
Input: root = [1,3,null,null,2]
Output: [3,1,null,null,2]
Explanation: 3 cannot be a left child of 1 because 3 > 1. Swapping 1 and 3 makes the BST valid.

Example 2:
Input: root = [3,1,4,null,null,2]
Output: [2,1,4,null,null,3]
Explanation: 2 cannot be in the right subtree of 3 because 2 < 3. Swapping 2 and 3 makes the BST valid.
*/


//289. LARGEST BST                                                {T.C = O(N), S.C = O(1)}
//FOLLOW COMMENTS
struct NodeVal {
    int minNode, maxNode, maxSize;
    NodeVal(int minN, int maxN, int maxS) : minNode(minN), maxNode(maxN), maxSize(maxS) {}
};

class Solution {
public:
    // Function to solve the problem
    NodeVal solve(Node* root) {
        // Base case
        if (!root) return NodeVal(INT_MAX, INT_MIN, 0);

        // Values from left and right subtrees
        NodeVal left = solve(root->left);
        NodeVal right = solve(root->right);

        // If current node is a valid BST
        if (root->data > left.maxNode && root->data < right.minNode) {
            return NodeVal(min(root->data, left.minNode), max(root->data, right.maxNode), left.maxSize + right.maxSize + 1);
        }

        // If not a valid BST, return the size of the largest BST so far
        return NodeVal(INT_MIN, INT_MAX, max(left.maxSize, right.maxSize));
    }

    // Function to find the largest BST in a binary tree
    int largestBst(Node *root) {
        return solve(root).maxSize;
    }
};


/*-------------------------------------------THE END---------------------------------------------------*/