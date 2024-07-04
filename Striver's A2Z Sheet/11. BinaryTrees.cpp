//BINARY TREES

#include<bits/stdc++.h>
using namespace std;


/*
DFS = PREORDER, INORDER, POSTORDER
BFS = LEVELORDER
*/
//TRAVERSALS--------------------------------------------------------------------------------------------
//237. INTRODUCTION TO TREES                                 {T.C = O(1), S.C = O(1)}
//TOTAL NODE WITH LEVEL(I) = 2^I , ITH LEVEL = 2^(I-1)
class Solution {
  public:
    int countNodes(int i) {
        return pow(2, i-1);          //nodes on level i = 2^(i-1)
    }
};
/*
Example 1:
Input: 5
Output: 16

Example 2:
Input: 1
Output: 1
*/


struct node {
  int data;
  struct node *left;
  struct node *right;
};

struct node *newNode(int data) {
  struct node *node = (struct node *)malloc(sizeof(struct node));

  node->data = data;

  node->left = NULL;
  node->right = NULL;
  return (node);
}
//238. BINARY TREE REPRESENTATIONS                           {T.C = O(1), S.C = O(1)}
//SIMPLE PUT VECTORS VALUE ACCORDINT TO TREE
class Solution{
public:

    void create_tree(node* root0, vector<int> &vec){
        root0->left = newNode(vec[1]);
        root0->right = newNode(vec[2]);
        root0->left->left = newNode(vec[3]);
        root0->left->right = newNode(vec[4]);
        root0->right->left = newNode(vec[5]);
        root0->right->right = newNode(vec[6]);
    }
};
/*
Input: 
nodes = [1 2 3 4 5 6 7]
Output: 
         1
       /   \
     2       3
   /  \     /  \
   4  5    6   7
Explanation: 
The 7 node binary tree is represented above.
*/


//239. TREE TRAVERSALS                                      {T.C = O(N), S.C = O(N)}
//INORDER(LNR), PREORDER(NLR), POSTORDER(LRN)
void inOrder(TreeNode* root, vector<int>&v){
    //base case
    if(!root) return;
    //LNR
    inOrder(root->left, v);
    v.push_back(root->data);
    inOrder(root->right, v);
}
void prOrder(TreeNode* root, vector<int>&v){
    //base case
    if(!root) return;
    //NLR
    v.push_back(root->data);
    prOrder(root->left, v);
    prOrder(root->right, v);
}
void poOrder(TreeNode* root, vector<int>&v){
    //base case
    if(!root) return;
    //LRN
    poOrder(root->left, v);
    poOrder(root->right, v);
    v.push_back(root->data);
}
vector<vector<int>> getTreeTraversal(TreeNode *root){
    vector<int>v1;
    inOrder(root, v1);

    vector<int>v2;
    prOrder(root, v2);

    vector<int>v3;
    poOrder(root, v3);

    return {v1, v2, v3};

}
/*
For the given binary tree:
The Inorder traversal will be [5, 3, 2, 1, 7, 4, 6].
The Preorder traversal will be [1, 3, 5, 2, 4, 7, 6].
The Postorder traversal will be [5, 2, 3, 7, 6, 4, 1].
*/


//240. BINARY TREE PREORDER TRAVERSAL                           {T.C = O(N), S.C = O(N)}
//RECURSION (NLR)
class Solution {
public:
    void preOrder(TreeNode* root, vector<int>&v){
        //base case
        if(!root) return;
        //NLR
        v.push_back(root->val);
        preOrder(root->left, v);
        preOrder(root->right, v);
    }
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int>v;
        preOrder(root, v);

        return v;
    }
};
/*
Example 1:
Input: root = [1,null,2,3]
Output: [1,2,3]

Example 2:
Input: root = []
Output: []

Example 3:
Input: root = [1]
Output: [1]
*/


//241. BINARY TREE INORDER TRAVERSAL                     {T.C = O(N), S.C = O(N)}
//RECURSION (LNR)
class Solution {
public:
    void inOrder(TreeNode* root, vector<int>&v){
        //base case
        if(!root) return;
        //LNR
        inOrder(root->left, v);
        v.push_back(root->val);
        inOrder(root->right, v);
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int>v;
        inOrder(root, v);

        return v;
    }
};
/*
Example 1:
Input: root = [1,null,2,3]
Output: [1,3,2]

Example 2:
Input: root = []
Output: []

Example 3:
Input: root = [1]
Output: [1]
*/


//242. BINARY TREE POST ORDER TRAVERSAL                   {T.C = O(N), S.C = O(N)}
//RECURSION (LRN)
class Solution {
public:
    void poOrder(TreeNode* root, vector<int>&v){
        //base case
        if(!root) return;
        //LRN
        poOrder(root->left, v);
        poOrder(root->right, v);
        v.push_back(root->val);
    }
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int>v;
        poOrder(root, v);

        return v;
    }
};
/*
Example 1:
Input: root = [1,null,2,3]
Output: [3,2,1]

Example 2:
Input: root = []
Output: []

Example 3:
Input: root = [1]
Output: [1]
*/


//243a. BINARY TREE LEVEL ORDER TRAVERSAL(EACH LEVEL IS NOT DISTINCT)     {T.C = O(N), S.C = O(N)}
//USE QUEUE
class Solution
{
    public:
    vector<int> levelOrder(Node* node)
    {
        vector<int>ans;
        queue<Node*>q;
        q.push(node);
        
        if(!node) return ans;

        while(!q.empty()){
            Node* temp = q.front();
            q.pop();
            ans.push_back(temp->data);
            
            if(temp->left){
                q.push(temp->left);
            }
            if(temp->right){
                q.push(temp->right);
            }
        }
        return ans;
    }
};
/*
Input:
        10
     /      \
    20       30
  /   \
 40   60
Output:10 20 30 40 60
*/


//243b. BINARY TREE LEVEL ORDER TRAVERSAL (EACH LEVEL DISTINCT)   {T.C = O(N), S.C = O(N)}
//USE EXTRA FOR LOOP FOR EACH LEVEL ELSE SAME AS ABOVE
class Solution {
public:
    void leOrder(TreeNode* root, vector<vector<int>>&v){
        //base case
        if(!root) return;
        
        queue<TreeNode*>q;
        q.push(root);
        while(!q.empty()){
            int lvlSize = q.size();
            vector<int>lvlNodes;                           //for store each levels ans
            for(int i = 0 ; i < lvlSize ; i++){
                TreeNode* frontNode = q.front();
                q.pop();
                lvlNodes.push_back(frontNode->val);
                if(frontNode->left) q.push(frontNode->left);
                if(frontNode->right) q.push(frontNode->right);
            }
            v.push_back(lvlNodes);
        }
    }
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>>ans;
        leOrder(root, ans);

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


//244. BINARY TREE PREORDER TRAVERSAL (ITERATIVE)               {T.C = O(N), S.C = O(N)}
//USE STACK, PUSH (NRL {REVERSE PUSH})
class Solution {
public:
    void prOrderIt(TreeNode* root, vector<int>&v, stack<TreeNode*>&stk){
        //base case
        if(!root) return;

        stk.push(root);
        while(!stk.empty()){
            root = stk.top();
            stk.pop();
            //NLR -> NRL (STACK IS USED)
            v.push_back(root->val);
            if(root->right) stk.push(root->right);
            if(root->left) stk.push(root->left);
        }
    }
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int>ans;
        stack<TreeNode*>stk;
        prOrderIt(root, ans, stk);

        return ans;
    }
};
/*

Example 1:
Input: root = [1,null,2,3]
Output: [1,2,3]

Example 2:
Input: root = []
Output: []

Example 3:
Input: root = [1]
Output: [1]
*/


//245. BINARY TREE INORDER TRAVERSAL (ITERATIVE)                     {T.C = O(N), S.C = O(N)}
//IF NODE != NULL PUSH ELE IN STACK AND MOVE LEFT ELSE, PUSH ELE IN ANS AND MOVE RIGHT
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*>stk;
        TreeNode* node = root;
        vector<int>ans;
        while(true){
            if(node){
                stk.push(node);
                node = node->left;                    //L
            }else{
                if(stk.empty()) break;
                node = stk.top();
                stk.pop();
                ans.push_back(node->val);             //N
                node = node->right;                   //R
            }
        }
        return ans;
    }
};
/*
Example 1:
Input: root = [1,null,2,3]
Output: [1,3,2]

Example 2:
Input: root = []
Output: []

Example 3:
Input: root = [1]
Output: [1]
*/


//245. POST ORDER TRAVERSAL OF BINARY TREE (USING 2 STACKS)          {T.C = O(N), S.C = O(N)}
//USE 2 STACK WITH 1 STACK APPLY PREORDER LIKE ABOVE AND STORE ANS IN STACK 2 THEN POP FROM IT TO VECTOR.
class Solution {
public:
    void poOrderIt(Node* root, vector<int>& v, stack<Node*>& stk1, stack<Node*>& stk2) {
        // base case
        if (!root) return;

        // Initialize the first stack with the root node
        stk1.push(root);

        // Process nodes in preorder but store in second stack
        while (!stk1.empty()) {
            Node* node = stk1.top();
            stk1.pop();
            
            stk2.push(node);
            if (node->left) stk1.push(node->left);
            if (node->right) stk1.push(node->right);
        }

        // Pop all items from the second stack and add to result vector
        while (!stk2.empty()) {
            Node* node = stk2.top();
            stk2.pop();
            v.push_back(node->data);
        }
    }

    vector<int> postOrder(Node* root) {
        vector<int> ans;
        stack<Node*> stk1, stk2;
        poOrderIt(root, ans, stk1, stk2);

        return ans;
    }
};
/*
Example 1
Input:
           1
         /   \
        2     3
      /  \
     4    5

Output: 4 5 2 3 1
Explanation:
Postorder traversal (Left->Right->Root) of 
the tree is 4 5 2 3 1.

Example 2
Input:
             8
          /      \
        1          5
         \       /   \
          7     10    6
           \   /
            10 6

Output: 10 7 1 6 10 6 5 8 
Explanation:
Postorder traversal (Left->Right->Root) 
of the tree is 10 7 1 6 10 6 5 8 .
*/


//246. POST ORDER TRAVERSAL OF BINARY TREE (USING 1 STACKS)          {T.C = O(N), S.C = O(N)}
//LRN->NLR, THEN REVERSE ANS
class Solution {
public:
     vector<int> postorderTraversal(TreeNode* root) {
        stack<TreeNode*>s;
        if(!root)return {};
        s.push(root);
        vector<int>v;
        while(s.size()>0){
            TreeNode*node=s.top();
            s.pop();
            //LRN->NLR
            v.push_back(node->val);
            if(node->left)  s.push(node->left);
            if(node->right) s.push(node->right);
        }
        reverse(v.begin(),v.end());
        return v;
    }
};
/*
Example 1:
Input: root = [1,null,2,3]
Output: [3,2,1]

Example 2:
Input: root = []
Output: []

Example 3:
Input: root = [1]
Output: [1]
*/


//247. PREORDER, INORDER AND POSTORDER TRAVERSAL IN ONE TRAVERSAL   {T.C = O(N), S.C = O(N)}
//TAKE 3 VECTORS(IN, PRE, POST) , PUSH DATA (PRE), SOLVE LEFT THEN PUSH(IN), SOLVE RIGHT THEN PUSH(POST)
void solve(TreeNode* root, vector<int>&In, vector<int>&pre, vector<int>& post){
    if(root == NULL) return;

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

//MEDIUM PROBLEMS---------------------------------------------------------------------------------------
//248. MAXIMUM DEPTH OF BINARY TREE / HEIGTH OF BINAR TREE       {T.C = O(N), S.C = O(H)}
//FIND MAX OF LEFT AND RIGHT NODES COUNT + 1(CURR LEVEL)
class Solution {
public:
    int maxDepth(TreeNode* root) {
        //base case
        if(!root) return 0;
        int left = maxDepth(root->left);
        int right = maxDepth(root->right);
        int ans = max(left, right) + 1;                //+1 (current level)

        return ans;
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


//249. BALANCED BINARY TREE                                       {T.C = O(N^2), S.C = O(N)}
//ABS(LEFT HEIGT - RIGHT HEIGHT > 1) FALSE , MAKE RECURSIVE CALL LEFT AND RIGTH
class Solution {
public:
    int findHeight(TreeNode* root){
        //base case
        if(!root) return 0;

        int left = findHeight(root->left);
        int right = findHeight(root->right);

        return max(left, right) + 1;                //1 for curr level
    }
    bool isBalanced(TreeNode* root) {
        //base case
        if(!root) return true;
        if(abs(findHeight(root->left) - findHeight(root->right)) > 1) return false;
        return isBalanced(root->left) && isBalanced(root->right);
    }
};

//OPTIMIZED APPROACH                                           {T.C = O(N), S.C = O(N)}
//WIHT FINDING HEIGHT CHECK LEFT AND RIGTH (-1 OR ABS( > 1))
class Solution {
public:
    int checkHeight(TreeNode* root){
        //base case
        if(!root) return 0;

        int left = checkHeight(root->left);
        if(left == -1) return -1;

        int right = checkHeight(root->right);
        if(right == -1) return -1;

        if(abs(left-right) > 1) return -1;

        return max(left, right) + 1;                //1 for curr level
    }
    bool isBalanced(TreeNode* root) {
        //base case
        if(!root) return true;

        return checkHeight(root) == -1 ? false : true;
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


//250. DIAMETER OF BINARY TREE                                 {T.C = O(N), S.C = O(H{REC})}
//SAME FIND HEIGTH FUNCTION + MAXI(VARIABLE) {MAXI = MAX(MAXI, LEFT+HEIGHT)}
class Solution {
public:
    int dfsDiameter(TreeNode* root, int &maxi){
        //base case
        if(!root) return 0;
        
        int left = dfsDiameter(root->left, maxi);
        int right = dfsDiameter(root->right, maxi);

        maxi = max(maxi, left+right);     //include longest path

        return max(left, right)+1;        //1 = currNode
    }
    int diameterOfBinaryTree(TreeNode* root) {
        //base case
        if(!root) return 0;
        int maxi = INT_MIN;
        dfsDiameter(root, maxi);

        return maxi;
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


//251. BINARY TREE MAXIMUM PATH SUM                        {T.C = O(N), S.C = O(H)}
//CHOOSE FROM 3 (ANYONE PATH (LEFT, RIGTH VALID), ONLYNODE(L, R INVALID), ONLYPATH (DOWN THE NODE VALID))
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


//252. SAME TREE                                        {T.C = O(N), S.C = O(H)}
//CHECK (BOTH NULL, ONE NULL, VAL NOT SAME) ELSE RECURSIVE CALL FOR LEFT AND RIGHT
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(!p && !q){               //both null
            return true;
        }else if(!p || !q){         //one null but not 2
            return false;
        }else if(p->val != q->val){  //val is not same
            return false;
        }
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


//253. BINARY TREE ZIG ZAG LEVEL ORDER TRAVERSAL              {T.C = O(N), S.C = O(N)}
//SIMILAR 243B. JUST USE EXTRA FLAG (LEFT TO RIGTH) AND AFTER LVL TRAVERSAL REVERSE PUSH IN ANS.
class Solution {
public:
    void zigZagLeOrder(TreeNode* root, vector<vector<int>>&ans){
        //base case
        if(!root) return;

        bool leftToRight = true;

        queue<TreeNode*>q;
        q.push(root);
        while(!q.empty()){
            int lvlSize = q.size();
            vector<int>lvlNodes;
            for(int i = 0 ; i < lvlSize ; i++){
                TreeNode* frontNode = q.front();
                q.pop();

                lvlNodes.push_back(frontNode->val);
                if(frontNode->left) q.push(frontNode->left);
                if(frontNode->right) q.push(frontNode->right);
            }
            if(!leftToRight) reverse(lvlNodes.begin(), lvlNodes.end());
            ans.push_back(lvlNodes);
            leftToRight = !leftToRight;
        }
    }
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>>ans;
        zigZagLeOrder(root, ans);

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


//254. TREE BOUNDARY TRAVERSAL                                {T.C = O(N), S.C = O(H)}
//TRAVERSAL 3 WAYS(LEFT, LEAF, REVERSE RIGHT)
class Solution {
public:
    void traversalLeft(Node* root, vector<int>&ans){
        //base case
        if(root == NULL || root->left == NULL && root->right == NULL) return;
        
        ans.push_back(root->data);
        if(root->left) traversalLeft(root->left, ans);
        else traversalLeft(root->right,ans);
    }
    
    void traversalLeaf(Node* root, vector<int>&ans){
        //base case
        if(root == NULL) return;
        
        if(root->left == NULL && root->right == NULL){
            ans.push_back(root->data);
        }
        
        traversalLeaf(root->left, ans);
        traversalLeaf(root->right, ans);
    }
    
    void traversalReverseRight(Node* root, vector<int>&ans){
        //base case
        if(root == NULL || root->left == NULL && root->right == NULL) return;

        
        if(root->right) traversalReverseRight(root->right, ans);
        else traversalReverseRight(root->left, ans);
        
        //wapas ate samay print karo
        ans.push_back(root->data);
        
    }
    vector <int> boundary(Node *root)
    {
        vector<int>ans;
        
        //base case
        if(root == NULL) return ans;
        
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
*/


//255. VERTICAL ORDER TRAVERSAL OF A BINARY TREE                {T.C = O(NLOGN), S.C = O(N)}
//USE MAP(MAP, MULTISET), QUEUE(NODE, {X, Y}) FIRST STORE ANS IN MP THEN MOVE TO VECTOR.
class Solution {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        map<int,map<int, multiset<int>>>mp;                //x, y, node->val
        queue<pair<TreeNode* , pair<int, int>>>q;          //node, x, y
        q.push({root, {0, 0}});

        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();

            TreeNode* node = frontNode.first;
            int x = frontNode.second.first;               //x = vertical distance
            int y = frontNode.second.second;              //y = level (at which)

            mp[x][y].insert(node->val);
            if(node->left) q.push({node->left, {x-1, y+1}});    //left  (-x, +y)
            if(node->right) q.push({node->right, {x+1, y+1}});  //right (+x, +y)
        }
        vector<vector<int>>ans;
        for(auto p : mp) {
            vector<int> col;
            for(auto q : p.second) {
                col.insert(col.end(), q.second.begin(), q.second.end());  //insert all element from map to col
            }
            ans.push_back(col);
        }
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
*/


//256. TOP VIEW OF BINARY TREE                            {T.C = O(NLOGN), S.C = O(N)}
//MAP(X, NODE), QUEUE(NODE, X) STORE ANS IN MAP THEN STORE TO VECTOR
class Solution{
public:
    vector<int> topView(Node *root)
    {
        vector<int>ans;
        //base case
        if(!root) return ans;
        
        map<int,int>mp;                    //x(Vertical distance) , node->data
        queue<pair<Node*, int>>q;          //node, x
        
        q.push({root, 0});                 //initiallise
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            
            Node* node = frontNode.first;
            int x = frontNode.second;
            
            if(!mp.count(x)){               //not found (unique entry)
                mp[x] = node->data;               
            }
            // mp[x] = node->data;          //not work (capturing first node only)
            //recursive call
            if(node->left)  q.push({node->left, x-1});   //line = <-- -2 -1 0 
            if(node->right) q.push({node->right, x+1}); //line = 0 1 2 --- > 
            
        }
        
        for(auto it : mp){
            ans.push_back(it.second);                   //push node->data
        }
        
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


//257. BOTTOM VIEW OF BINARY TREE                           {T.C = O(NLOGN), S.C = O(N)}
//JUST DONT CHECK FOR MAP EXISTING ELEMENT (UPDATE EXISTING ELEMENT) , REST SAME AS ABOVE
class Solution {
  public:
    vector <int> bottomView(Node *root)
    {
        vector<int>ans;
        //base case
        if(!root) return ans;
        
        map<int,int>mp;                    //x(Vertical distance) , node->data
        queue<pair<Node*, int>>q;          //node, x
        
        q.push({root, 0});                 //initiallise
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            
            Node* node = frontNode.first;
            int x = frontNode.second;
            
            // if(!mp.count(x)){               //top view
            //     mp[x] = node->data;               
            // }
            mp[x] = node->data;                //bottom view
            //recursive call
            if(node->left)  q.push({node->left, x-1});   //line = <-- -2 -1 0 
            if(node->right) q.push({node->right, x+1}); //line = 0 1 2 --- > 
            
        }
        
        for(auto it : mp){
            ans.push_back(it.second);                   //push node->data
        }
        
        return ans;
    }
};
/*
Example 1:
Input:
       1
     /   \
    3     2
Output: 3 1 2
Explanation:
First case represents a tree with 3 nodes
and 2 edges where root is 1, left child of
1 is 3 and right child of 1 is 2.

Thus nodes of the binary tree will be
printed as such 3 1 2.

Example 2:
Input:
         10
       /    \
      20    30
     /  \
    40   60
Output: 40 20 60 30
*/


//258a. BINARY TREE RIGHT SIDE VIEW                        {T.C = O(N), S.C = O(H)}
//NRL (PUSH NODE, RIGHT RECURSIVE + LEVEL++ , LEFT RECURSIVE + LEVEL++)
class Solution {
public:
    void solve(TreeNode* root, vector<int>&ans, int level){
        //base case
        if(!root) return;

        //NRL        (for right view)  //for left view (NLR)
        if(level == ans.size()){                   //if level reach ends then change the level and push root->data in vector
            ans.push_back(root->val);           
        }
        solve(root->right, ans, level+1);
        solve(root->left, ans, level+1);
    }
    vector<int> rightSideView(TreeNode* root) {
        vector<int>ans;
        solve(root, ans, 0);                      //0 == initial level
        return ans;
    }
};
/*
Example 1:
Input: root = [1,2,3,null,5,null,4]
Output: [1,3,4]

Example 2:
Input: root = [1,null,3]
Output: [1,3]

Example 3:
Input: root = []
Output: []
*/


//258b. BINARY TREE LEFT SIDE VIEW                         {T.C = O(N), S.C = O(N)}
//NLR (NODE, LEFT RECURSIVE + LEVEL++, RIGHT RECURSIVE + LEVEL++)
void solve(Node* root, vector<int>&ans, int lvl){
    //base case
    if(!root) return;
    
    //NLR (LEFT VIEW), NRL(RIGHT VIEW)
    if(lvl == ans.size()){
        ans.push_back(root->data);
    }
    solve(root->left, ans, lvl+1);
    solve(root->right, ans, lvl+1);
}
vector<int> leftView(Node *root)
{
   vector<int>ans;
   solve(root, ans, 0);                 //intial level
   
   return ans;
}
/*
Example 1:
Input:
   1
 /  \
3    2
Output: 1 3

Example 2:
Input:
Output: 10 20 40
*/


//259. SYMMETRIC TREE                                    {T.C = O(N), S.C = O(N)}
//FIRST CHECK P && 1 SAME , THEN CHECK P->LEFT, Q->RIGHT == P->RIGHT, Q->LEFT
class Solution {
public:
    bool isMirror(TreeNode* p, TreeNode* q){
        if(!p && !q) return true;
        if(!p || !q) return false;
        
        return p->val == q->val && isMirror(p->left, q->right) && isMirror(p->right, q->left);   
    }
    bool isSymmetric(TreeNode* root) {
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


//HARD PROBLEMS----------------------------------------------------------------------------------------
//260. ROOT TO LEAF PATHS                                         {T.C = O(N), S.C = O(N)}
//FIRST PUSH CURR DATA , THEN CHECK IF LEAF PUT TEMP IN ANS ELSE RIGHT AND LEFT RECURSIVE CALL
class Solution {
  public:
    void solve(Node* root,vector<int>&temp, vector<vector<int>>&ans){
        //base case
        if(!root) return;
        
        temp.push_back(root->data);                        //before recursive call
        
        if(!root->left && !root->right){
            ans.push_back(temp);
        }
        
        if(root->left) solve(root->left, temp, ans);

        if(root->right) solve(root->right, temp, ans);
        
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


//261. LOWEST COMMON ANCESTOR (LCA) OF A BINARY TREE            {T.C = O(N), S.C = O(N)}
//ROOT = P || Q (ROOT), L & R (ROOT), R(R), L (L) , {} (NULL)
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        //base case
        if(!root) return NULL;
        
        if((root->val == p->val) || (root->val == q->val)){      //ownself is an ancestor
            return root;
        }

        //LRN
        TreeNode* leftAns = lowestCommonAncestor(root->left, p, q);
        TreeNode* rightAns = lowestCommonAncestor(root->right, p, q);

        if(leftAns && rightAns){                                //both left and right call not null (thats the lca answer)
            return root;
        }
        else if(!leftAns && rightAns){
            return rightAns;
        }
        else if(leftAns && !rightAns){
            return leftAns;
        }
        else{  //!leftAns && !rightAns
            return NULL;
        }
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


//262. MAXIMUM WIDTH OF BINARY TREE                          {T.C = O(N), S.C = O(N)}
//USE MODIFIED LEVEL ORDER TRAVERSAL QUEUE(ROOT, INDEX), MODIFIY INDEX = CURRIDEX(AVOID OVERFLOW)
//ANS = LAST-FIRST+1 (INDEX)
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        int ans = 0;
        //base case
        if(!root) return 0;
        queue<pair<TreeNode*,int>>q;              //root, i
        q.push({root, 0});
        while(!q.empty()){
            int sz = q.size();
            int minI = q.front().second;
            int first, last;
            for(int i = 0 ; i < sz ; i++){
                TreeNode* node = q.front().first;
                int currI = q.front().second-minI;   //for ignore overflow
                q.pop();

                if(i == 0) first = currI;
                if(i == sz-1) last = currI;

                if(node->left) q.push({node->left, (long long)2*currI + 1});      //2*i+1 (left child)
                if(node->right) q.push({node->right, (long long)2*currI + 2});    //2*i+2 (right child)
            }
            ans = max(ans, last-first+1);
        }
        return ans;
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


//263. CHECK FOR CHILDREN SUM PROPERTY OF BINARY TREE           {T.C =  O(N), S.C = O(H)}
//IF NOT ROOT OR LEAF NODE : TRUE ELSE CHECK SUM OF LEFT + RIGHT == ROOT , THEN RECURSIVE CALL L, R.
class Solution{
    public:
    int isSumProperty(Node *root)
    {
        //base case
        if(!root || (!root->left && !root->right)) return 1;
        
        int leftVal = 0, rightVal = 0;
        if(root->left) leftVal = root->left->data;
        if(root->right) rightVal = root->right->data;
        
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
Here, 1 is the root node and 4, 3 are its child nodes. 4 + 3 = 7 which is not equal to the value of 
root node. Hence, this tree does not satisfy the given condition.
*/


//264. ALL NODES DISTANCE K IN BINARY TREES                       {T.C = O(N), S.C = O(H)}
//CONVERT TREE TO GRAPH
//FIRST CREATE PARENT POINTERS, THEN APPLY BFS FOR EACH LEVEL, FINAL LEVEL IS REQUIRED ANS.
class Solution {
public:
    unordered_map<TreeNode* , TreeNode*>parent;       //node, node's parent
    //make parent pointer of each node
    void inOrder(TreeNode* root){
        //base case
        if(!root) return;

        if(root->left){
            parent[root->left] = root;
            inOrder(root->left);
        } 
        if(root->right){
            parent[root->right] = root;
            inOrder(root->right);
        }
    }
    void bfs(TreeNode* target, int k, unordered_map<TreeNode*, bool>&vis, vector<int>&ans){
        vis[target] = true;
        queue<TreeNode*>q;
        q.push(target);
        
        while(!q.empty()){
            int n = q.size();
            if(k == 0) break;
            while(n--){
                auto it = q.front();
                q.pop();
                
                //left
                if(it->left && !vis[it->left]){
                    q.push(it->left);
                    vis[it->left] = true;
                }
                //right
                if(it->right && !vis[it->right]){
                    q.push(it->right);
                    vis[it->right] = true;
                }
                //parent
                if(parent.count(it) && !vis[parent[it]]){
                    q.push(parent[it]);
                    vis[parent[it]] = true;
                }
            }
            k--;
        }
        
        while(!q.empty()){                      //remaining level elements are answers with distance k
            TreeNode* temp = q.front();
            q.pop();
            ans.push_back(temp->val);
        }
    }
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        vector<int>ans;
        unordered_map<TreeNode*, bool>vis;
        inOrder(root);
        bfs(target, k, vis, ans);

        return ans;
    }
};
/*
Example 1:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
Output: [7,4,1]
Explanation: The nodes that are a distance 2 from the target node (with value 5) have values 7, 4, and 1.

Example 2:
Input: root = [1], target = 1, k = 3
Output: []
*/


//265. BURNING TREE                                            {T.C = O(N), S.C = O(H)}
//BY USING ABOVE APPROACH
class Solution {
public:
    unordered_map<Node*, Node*> parent; // node, node's parent

    // Making bidirectional edges or child to parent edges
    void inOrder(Node* root) {
        // Base case
        if (!root) return;

        if (root->left) {
            parent[root->left] = root;
            inOrder(root->left);
        }
        if (root->right) {
            parent[root->right] = root;
            inOrder(root->right);
        }
    }

    void bfs(Node* target, unordered_map<Node*, bool>& vis, int& ans) {
        vis[target] = true;
        queue<Node*> q;
        q.push(target);

        ans = 0;
        while (!q.empty()) {
            int n = q.size();
            bool newInfected = false;

            while (n--) {
                Node* it = q.front();
                q.pop();

                // Left
                if (it->left && !vis[it->left]) {
                    q.push(it->left);
                    vis[it->left] = true;
                    newInfected = true;
                }
                // Right
                if (it->right && !vis[it->right]) {
                    q.push(it->right);
                    vis[it->right] = true;
                    newInfected = true;
                }
                // Parent
                if (parent[it] && !vis[parent[it]]) {
                    q.push(parent[it]);
                    vis[parent[it]] = true;
                    newInfected = true;
                }
            }

            if (newInfected) {
                ans++;
            }
        }
    }

    int minTime(Node* root, int target) {
        inOrder(root);
        
        // Find the target node
        Node* targetNode = nullptr;
        queue<Node*> q;
        q.push(root);
        while (!q.empty() && !targetNode) {
            Node* node = q.front();
            q.pop();
            if (node->data == target) {
                targetNode = node;
            }
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }

        if (!targetNode) return -1; // Target not found

        unordered_map<Node*, bool> vis;
        int ans = 0;
        bfs(targetNode, vis, ans);

        return ans;
    }
};
/*
Examples : 
Input:      
          1
        /   \
      2      3
    /  \      \
   4    5      6
       / \      \
      7   8      9
                   \
                   10
Target Node = 8
Output: 7
Explanation: If leaf with the value 
8 is set on fire. 
After 1 sec: 5 is set on fire.
After 2 sec: 2, 7 are set to fire.
After 3 sec: 4, 1 are set to fire.
After 4 sec: 3 is set to fire.
After 5 sec: 6 is set to fire.
After 6 sec: 9 is set to fire.
After 7 sec: 10 is set to fire.
It takes 7s to burn the complete tree.

Input:      
          1
        /   \
      2      3
    /  \      \
   4    5      7
  /    / 
 8    10
Target Node = 10
Output: 5
*/


//265b. AMOUNT OF TIME FOR BINARTY TREE TO BE INFECTED         {T.C = O(N), S.C = O(N)}
//USING DFS (ROOT == START : ANS = MAX(LH, RH)), LH >= 0 && RH >= 0 RETURN MAX(LH, RH)+1, ONE IS -VE(ADD ABS DIFF(LH, RH))
class Solution {
public:
    int solve(TreeNode* root, int start, int &ans){
        //base case
        if(!root) return 0;
        
        int lh = solve(root->left, start, ans);
        int rh = solve(root->right, start, ans);

        if(root->val == start){
            ans = max(lh, rh);
            return -1;
        }else if(lh >= 0 && rh >= 0){                  //start is in another branch
            return max(lh, rh)+1;
        }else{                                       //one is negative
            int dist = abs(lh)+abs(rh);
            ans = max(ans, dist);
            return min(lh, rh)-1;
        }
        return 0;
    }
    int amountOfTime(TreeNode* root, int start) {
        int ans = INT_MIN;
        solve(root, start, ans);

        return ans;
    }
};
/*
Example 1:
Input: root = [1,5,3,null,4,10,6,9,2], start = 3
Output: 4
Explanation: The following nodes are infected during:
- Minute 0: Node 3
- Minute 1: Nodes 1, 10 and 6
- Minute 2: Node 5
- Minute 3: Node 4
- Minute 4: Nodes 9 and 2
It takes 4 minutes for the whole tree to be infected so we return 4.

Example 2:
Input: root = [1], start = 1
Output: 0
Explanation: At minute 0, the only node in the tree is infected so we return 0.
*/


//266. COUNT COMPLETE TREE NODES                            {T.C = O(N), S.C = O(H)}
//TOTAL NODES = LEFT + RIGHT + 1(CURR NODE)
class Solution {
public:
    int countNodes(TreeNode* root) {
        //base case
        if(!root) return 0;
        
        //recursive call
        int left = countNodes(root->left);
        int right = countNodes(root->right);

        return left + right + 1;                    //1 = node element
    }
};
/*
Example 1:
Input: root = [1,2,3,4,5,6]
Output: 6

Example 2:
Input: root = []
Output: 0

Example 3:
Input: root = [1]
Output: 1
*/


//267. UNIQUE BINARY TREE REQUIREMENTS                        {T.C = O(1), S.C = O(1)}
//1 = PREORDER, 2 = INORDER, 3 = POSTORDER
//1 BINARY TREE IS NECESSARY, SAME ORDER CANT MAKE UNIQUE BT
class Solution
{
public:
    bool isPossible(int a,int b)
    {
        if(a == b) return false;                //same cant be make unique
        if(a == 2 || b == 2) return true;       //1 inorder is necessary
        return false;
    }
};
/*
Example 1:
Input:
a = 1, b=2
Output: 1
Explanation: We can construct binary tree using inorder traversal and preorder traversal. 

Example 2:
Input: a = 1, b=3
Output: 0 
Explanation: We cannot construct binary tree using preorder traversal and postorder traversal. 
*/


//268. CONSTRUCT BINARY TREE FROM PREORDER AND INORDER TRAVERSAL     {T.C = O(N), S.C = O(H)}
//PASS IDX BY REFERENCE , FIND ROOT IN PREORDER(START), SEARCH IN INORDER (LEFT, RIGTH SUBTREE), MAKE NEW ROOT
class Solution {
public:
    TreeNode* solve(vector<int>&preorder, vector<int>&inorder, int inOrStart, int inOrEnd , int &preOrIdx){
        //base case
        if(inOrStart > inOrEnd) return NULL;

        int rootVal = preorder[preOrIdx];
        preOrIdx++;
        int i = inOrStart;
        for(i = inOrStart ; i <= inOrEnd ; i++){           //search in inorder
            if(inorder[i] == rootVal) break;
        }

        TreeNode* root = new TreeNode(rootVal);
        //s__i-1 (i) i+1__e
        root->left = solve(preorder, inorder, inOrStart, i-1, preOrIdx);   
        root->right = solve(preorder, inorder, i+1, inOrEnd, preOrIdx);

        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();                  //n = m = inorder(same tree)
        int preOrIdx = 0;                              //pass by reference only
        return solve(preorder, inorder, 0, n-1, preOrIdx);    //0 = inOrStart, n-1 = inOrEnd
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


//269. CONSTRUCT BINARY TREE FROM POSTORDER AND INORDER TRAVERSAL     {T.C = O(N), S.C = O(H)}
//PASS IDX BY REFERENCE , FIND ROOT IN POSTORDER(START), SEARCH IN INORDER (LEFT, RIGTH SUBTREE), MAKE NEW ROOT
class Solution {
public:
    TreeNode* solve(vector<int>&inorder, vector<int>&postorder, int inOrStart, int inOrEnd, int &poOrIdx){
        //base case
        if(inOrStart > inOrEnd) return NULL;
        int rootVal = postorder[poOrIdx];
        poOrIdx--;
        int i = inOrStart;
        for(i = inOrStart ; i <= inOrEnd ; i++){
            if(inorder[i] == rootVal) break;
        }

        //NRL(REVERSE POST ORDER)
        TreeNode* root = new TreeNode(rootVal);
        root->right = solve(inorder, postorder, i+1, inOrEnd, poOrIdx);
        root->left = solve(inorder, postorder, inOrStart, i-1 , poOrIdx);

        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = inorder.size();
        int poOrIdx = n-1;
        return solve(inorder, postorder, 0, n-1 , poOrIdx);     //0 = inOrStart, n-1 = inOrEnd
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


//270. SERIALIZE AND DESERIALIZE BINARY TREE                 {T.C = O(N), S.C = O(N)}
//SERIALIZE (BT TO STR), DESERIALIZE (STR TO BT) {USING PREORDER}
lass Codec {
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


//271. BINARY TREE PREORDER (MORRIS TRAVERSAL)              {T.C = O(N), S.C = O(1)}
//STORE ROOT IN CURR, IF CURR-LEFT , POINTER(PREDECESSOR = CURR->LEFT), MOVE PRED TO LEFT THEN EXTREME RIGHT
//AND THEN LINK TO CURR AFTER FINAL ANS REMOVE LINK
//PREORDER (ANS PUSH IF PRED->RIGHT == NULL)
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
                if(pred->right == NULL){           //add virtual pointer
                    ans.push_back(curr->val);
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
Input: root = []
Output: []

Example 3:
Input: root = [1]
Output: [1]
*/


//272. BINARY TREE INORDER (MORRIS TRAVERSAL)              {T.C = O(N), S.C = O(1)}
//STORE ROOT IN CURR, IF CURR-LEFT , POINTER(PREDECESSOR = CURR->LEFT), MOVE PRED TO LEFT THEN EXTREME RIGHT
//AND THEN LINK TO CURR AFTER FINAL ANS REMOVE LINK
//PREORDER (ANS PUSH IF PRED->RIGHT != NULL)
//
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
                if(pred->right == NULL){  //extreme right to curr pointer
                    //ans.push_back(curr->val);              //for preorder
                    pred->right = curr;
                    curr = curr->left;
                }else{                   //remove virtual pointer
                    ans.push_back(curr->val);
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
Input: root = []
Output: []

Example 3:
Input: root = [1]
Output: [1]
*/


//273. FLATTEN BINARTY TREE TO LINKED LIST                   {T.C = O(N), S.C = O(1)}
//USE MORRIS TRAVERSAL (ORDER -> PRED->RIGHT = CURR->RIGHT, CURR->RIGHT = CURR->LEFT, CURR->LEFT = NULL)
class Solution {
public:
    void flatten(TreeNode* root) {
        TreeNode* curr = root;                   //store original root
        while(curr){
            if(curr->left){
                TreeNode* predecessor = curr->left;        //first left then extream right 
                while(predecessor->right){
                    predecessor = predecessor->right;
                }
                //Exact order should maintain otherwise node lost
                predecessor->right = curr->right;       //set virtual pointer 
                curr->right = curr->left;
                curr->left = NULL;
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


/*---------------------------------------THE END------------------------------------------------------*/