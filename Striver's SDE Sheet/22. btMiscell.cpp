#include<bits/stdc++.h>
using namespace std;


//DAY 22. BINARY TREE (MISCELLANEOUS) ----------------------------------------------------------------------------------------
//146a. FLATEN BINARY TREE TO LINKED LIST {SINGLY LL} (PREORDER FORMAT)                       {T.C = O(N), S.C = O(H)}
class Solution {
public:
    void flatten(TreeNode* root) {
        TreeNode* curr = root;
        while(curr){
            if(curr->left){
                TreeNode* leftChild = curr->left;
                while(leftChild->right) leftChild = leftChild->right;       //extreme right
                leftChild->right = curr->right;                   //in flatten

                /*                                                //in morris(inorder)
                leftChild->right = curr

                TreeNode* prev = curr;                            //remove prev connections
                curr = curr->left;
                prev->left = NULL;
                */

                curr->right = curr->left;
                curr->left  = NULL;
            }
            /*
            ans.push_back(curr->val);                  
            */
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


//146b. BINARY TREE TO DOUBLY LINKED LIST                                        {T.C = O(N), S.C = O(H)}
class Solution {
  public:
    void inOrderDLL(Node* root, Node* &head, Node* &prev){
        //base case
        if(!root) return;
        
        inOrderDLL(root->left, head, prev);
        if(!prev) head = root;
        else{
            root->left = prev;
            prev->right= root;
        }
        prev = root;
        inOrderDLL(root->right, head, prev);
    }
    Node* bToDLL(Node* root) {
        Node* head = NULL;
        Node* prev = NULL;
        
        inOrderDLL(root, head, prev);
        return head;
    }
};
/*
Input:
      1
    /  \
   3    2
Output:
3 1 2 
2 1 3
Explanation: DLL would be 3<=>1<=>2

Input:
       10
      /   \
     20   30
   /   \
  40   60
Output:
40 20 60 10 30 
30 10 60 20 40
Explanation:  DLL would be 40<=>20<=>60<=>10<=>30.
*/


//147. FIND MEDIAN FROM A DATA STREAM                                        {T.C = O(LOGN), S.C = O(1)}
class MedianFinder {
public:
    priority_queue<int>leftMaxHeap;
    priority_queue<int,vector<int>, greater<int>>rightMinHeap;
    MedianFinder() {}
    
    void addNum(int num) {                                                    //{T.C = O(LOGN)}
        if(leftMaxHeap.empty() || leftMaxHeap.top() > num) leftMaxHeap.push(num);
        else rightMinHeap.push(num);

        int n = leftMaxHeap.size(), m = rightMinHeap.size();
        if(n < m){
            leftMaxHeap.push(rightMinHeap.top());
            rightMinHeap.pop();
        }else if(abs(n-m) > 1){
            rightMinHeap.push(leftMaxHeap.top());
            leftMaxHeap.pop();
        }
    }
    
    double findMedian() {
        if(leftMaxHeap.size() == rightMinHeap.size()){
            return (leftMaxHeap.top() + rightMinHeap.top()) / 2.0;
        }
        return leftMaxHeap.top();                             //extra element in maxHeap(odd len)
    }
};
/*
Input
["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
[[], [1], [2], [], [3], []]
Output
[null, null, null, 1.5, null, 2.0]

Explanation
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.addNum(2);    // arr = [1, 2]
medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
medianFinder.addNum(3);    // arr[1, 2, 3]
medianFinder.findMedian(); // return 2.0
*/


//148. FIND KTH LARGEST ELEMENT IN A STREAM                                      {T.C = O(N*LOGK), S.C = O(K)}
class KthLargest {
public:
    int k;
    priority_queue<int, vector<int>, greater<int>>minHeap;
    KthLargest(int k, vector<int>& nums) {
        this->k = k;
        for(auto it : nums){
            minHeap.push(it);
            if(minHeap.size() > k) minHeap.pop();
        }
    }
    
    int add(int val) {
        minHeap.push(val);
        if(minHeap.size() > k) minHeap.pop();
        return minHeap.top();
    }
};
/*
Example 1:
Input:
["KthLargest", "add", "add", "add", "add", "add"]
[[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]

Output: [null, 4, 5, 5, 8, 8]

Explanation:
KthLargest kthLargest = new KthLargest(3, [4, 5, 8, 2]);
kthLargest.add(3); // return 4
kthLargest.add(5); // return 5
kthLargest.add(10); // return 5
kthLargest.add(9); // return 8
kthLargest.add(4); // return 8

Example 2:
Input:
["KthLargest", "add", "add", "add", "add"]
[[4, [7, 7, 7, 7, 8, 3]], [2], [10], [9], [9]]

Output: [null, 7, 7, 7, 8]
Explanation:
KthLargest kthLargest = new KthLargest(4, [7, 7, 7, 7, 8, 3]);
kthLargest.add(2); // return 7
kthLargest.add(10); // return 7
kthLargest.add(9); // return 7
kthLargest.add(9); // return 8
*/


//149. COUNT DISTINCT ELEMENTS IN EVERY WINDOW                                  {T.C = O(N), S.C = O(N)}
class Solution{
  public:
    vector <int> countDistinct (int arr[], int n, int k){
        unordered_map<int,int>mp;
        vector<int>ans;
        int i = 0, j = 0;
        while(j < n ){
            mp[arr[j]]++;
            
            if(j-i+1 == k){
                ans.push_back(mp.size());
                
                mp[arr[i]]--;                           //slide window
                if(mp[arr[i]] == 0) mp.erase(arr[i]);
                i++;
            }
            j++;
        }
        return ans;
    }
};
/*
Example 1:
Input:
N = 7, K = 4
A[] = {1,2,1,3,4,2,3}
Output: 3 4 4 3
Explanation: Window 1 of size k = 4 is
1 2 1 3. Number of distinct elements in
this window are 3. 
Window 2 of size k = 4 is 2 1 3 4. Number
of distinct elements in this window are 4.
Window 3 of size k = 4 is 1 3 4 2. Number
of distinct elements in this window are 4.
Window 4 of size k = 4 is 3 4 2 3. Number
of distinct elements in this window are 3.

Example 2:
Input:
N = 3, K = 2
A[] = {4,1,1}
Output: 2 1
*/


//150. KTH LARGEST ELEMENT IN AN ARRAY                 
//for finding largest build minheap and vice versa                         {T.C = O(N*LOGK), S.C = O(N)}
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int,vector<int>, greater<int>>minHeap;
        for(auto it : nums){
            minHeap.push(it);
            if(minHeap.size() > k) minHeap.pop();
        }
        return minHeap.top();
    }
};
/*
Example 1:
Input: nums = [3,2,1,5,6,4], k = 2
Output: 5

Example 2:
Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
Output: 4
*/


//151. FLOOD FILL                                                               {T.C = O(N*M), S.C = O(N*M)}
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
Input: image = [[1,1,1],[1,1,0],[1,0,1]], sr = 1, sc = 1, color = 2
Output: [[2,2,2],[2,2,0],[2,0,1]]
Explanation:
From the center of the image with position (sr, sc) = (1, 1) (i.e., the red pixel), all pixels connected by a path of the same color as the starting pixel (i.e., the blue pixels) are colored with the new color.
Note the bottom corner is not colored 2, because it is not horizontally or vertically connected to the starting pixel.

Example 2:
Input: image = [[0,0,0],[0,0,0]], sr = 0, sc = 0, color = 0
Output: [[0,0,0],[0,0,0]]
Explanation:
The starting pixel is already colored with 0, which is the same as the target color. Therefore, no changes are made to the image.
*/