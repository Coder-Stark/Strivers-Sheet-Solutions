//HEAPS

#include<bits/stdc++.h>
using namespace std;

/*NOTES
HEAP    - COMPLETE BINARY TREE(CBT{ALL LEVEL FILL EXCEPT LAST LEVEL}) WITH HEAP ORDER(MAX, MIN) PROPERTY
        - NODES ALWAYS ADD FROM LEFT
                *        (VALID)                *       (INVALID) {FIRST LEFT FILLED IN EACH LEVEL }
              /  \                            /    \
            *       *                        *      *
           /  \                             /         \
          *    *                           *           *
HEAP CHILDS (1 BASED INDEXING) {FOR ZERO + 1 }
        LEFT = 2*I
        RIGHT = 2*I+1
        PARENT = I/2
*/
//LEARNING-----------------------------------------------------------------------------------------------
//204. IMPLEMENTATION OF PRIORITY QUEUE USING BINARY HEAP
//204a. BUILD MAX HEAP                                                   {T.C = O(N*LOGN), S.C = O(1)}
//heapify = o(logn), build heap = o(n)
//STL = priority_queue<int>maxHeap
void heapify(vector<int>&arr, int n , int i){

	int largest = i;
	int left = 2*i + 1;                                       //0 based indexing
	int right = 2*i + 2;

	if(left < n && arr[largest] < arr[left]){
		largest = left;
	}
	if(right < n && arr[largest] < arr[right]){
		largest = right;
	}

	if(largest != i){
		swap(arr[largest], arr[i]);
		heapify(arr, n, largest);
	}
}
vector<int> buildHeap(vector<int> arr, int n)
{	
	for(int i = n/2-1 ; i >= 0 ; i--){
		heapify(arr, n , i);
	}
	return arr;
}
/*
Input Array (unsorted): [4, 10, 3, 5, 1]
Resulting Max Heap: [10, 5, 3, 4, 1]
*/

//204b. BUILD MIN HEAP                                                 {T.C = O(N*LOGN), S.C = O(1)}
//STL = priority_queue<int, vector<int>, greater<int> >minHeap
void heapify(vector<int>&arr , int n , int i){

    int smallest = i;
    int left = 2 * i + 1 ;
    int right = 2 * i + 2;

    if(left < n && arr[smallest] > arr[left]){
        smallest = left;
    }
    if(right < n && arr[smallest] > arr[right]){
        smallest = right;
    }

    if(smallest != i){
        swap(arr[smallest],arr[i]);
        heapify(arr,n,smallest);
    }
}


vector<int> buildMinHeap(vector<int> &arr)
{
    int n = arr.size();
    for(int i = n/2-1 ; i >= 0 ; i--){
        heapify(arr, n, i);
    }
    return arr;
}
/*
Input Array (unsorted): [4, 10, 3, 5, 1]
Resulting Min Heap: [1, 3, 4, 5, 10]
*/



//The structure of the class is
struct MinHeap
{
    int *harr;
    int capacity, heap_size;
    MinHeap(int cap) {heap_size = 0; capacity = cap; harr = new int[cap];}
    int extractMin();
    void deleteKey(int i);
    void insertKey(int k);
    int parent(int i);
    int left(int i);
    int right(int i);
};
//Function to change value at ith index and store that value at first index.
void MinHeap::decreaseKey(int i, int new_val) 
{
    harr[i] = new_val;
    while (i != 0 && harr[parent(i)] > harr[i]) {
        swap(harr[i], harr[parent(i)]);
        i = parent(i);
    }
}

/* You may call below MinHeapify function in
   above codes. Please do not delete this code
   if you are not writing your own MinHeapify */
void MinHeap::MinHeapify(int i) 
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && harr[l] < harr[i]) smallest = l;
    if (r < heap_size && harr[r] < harr[smallest]) smallest = r;
    if (smallest != i) {
        swap(harr[i], harr[smallest]);
        MinHeapify(smallest);
    }
}
//205. BINARY HEAP OPERATIONS / MIN & MAX HEAP IMPLEMENTATION         {T.C = O(LOGN), S.C = O(LOGN)}
//COMPLETE ALL 3 FUNCTIONS

//Function to extract minimum value in heap and then to store 
//next minimum value at first index.
int MinHeap::extractMin() 
{
    if(heap_size == 0){
        return -1;
    }
    if(heap_size == 1){
        heap_size--;
        return harr[0];
    }
    swap(harr[0], harr[heap_size-1]);
    heap_size--;
    
    MinHeapify(0);
    return harr[heap_size];
}

//Function to delete a key at ith index.
void MinHeap::deleteKey(int i)
{
    if(i > (heap_size-1)){
        return;
    }
    decreaseKey(i, INT_MIN);
    int x = extractMin();
}

//Function to insert a value in Heap.
void MinHeap::insertKey(int k) 
{   
    if(heap_size==capacity) return;
    harr[heap_size] = k;
    heap_size++;
    
    for(int i=heap_size-1; i != 0 && harr[i] < harr[parent(i)]; )
    {
        swap(harr[i], harr[parent(i)]);
        i=parent(i);
    }  
 }


/*
Example 1:
Input:
Q = 7
Queries:
insertKey(4)
insertKey(2)
extractMin()
insertKey(6)
deleteKey(0)
extractMin()
extractMin()
Output: 2 6 - 1
Explanation: In the first test case for
query 
insertKey(4) the heap will have  {4}  
insertKey(2) the heap will be {2 4}
extractMin() removes min element from 
             heap ie 2 and prints it
             now heap is {4} 
insertKey(6) inserts 6 to heap now heap
             is {4 6}
deleteKey(0) delete element at position 0
             of the heap,now heap is {6}
extractMin() remove min element from heap
             ie 6 and prints it  now the
             heap is empty
extractMin() since the heap is empty thus
             no min element exist so -1
             is printed.

Example 2:
Input:
Q = 5
Queries:
insertKey(8)
insertKey(9)
deleteKey(1)
extractMin()
extractMin()
Output: 8 -1
*/


//206. DOES ARRAY REPRESENT HEAP(MAXHEAP)                     {T.C = O(N), S.C = O(1)}
//PARENT > LEFTCHILD && PARENT > RIGHTCHILD
class Solution{
    public:
    bool isMaxHeap(int arr[], int n)
    {
        bool check = true;
        
        auto lambda = [&](auto p, auto l, auto r){         //parent > left & parent > right
            if( !(p >= l && p >= r)){
                check = false;
            }
        };
        for(int i = n/2-1 ; i >= 0 ; i--){
            lambda(arr[i], arr[2*i+1], arr[2*i+2]);         //parent, leftchild, rightchild
        }
        
        return check;
    }
};
/*
Example 1:
Input:
n = 6
arr[] = {90, 15, 10, 7, 12, 2}
Output: 
1
Explanation: 
The given array represents below tree
       90
     /    \
   15      10
  /  \     /
7    12  2
The tree follows max-heap property as every
node is greater than all of its descendants.

Example 2:
Input:  
n = 6
arr[] = {9, 15, 10, 7, 12, 11}
Output:
0
Explanation:
The given array represents below tree
       9
     /    \
   15      10
  /  \     /
7    12  11
The tree doesn't follows max-heap property 9 is
smaller than 15 and 10, and 10 is smaller than 11. 
*/


//207. CONVERT MINHEAP TO MAXHEAP                               {T.C = O(NLOGN), S.C = O(1)}
//USE HEAPIFY FUNC(BUILD HEAP)
class Solution{
public:
    void heapify(vector<int>&arr, int n, int i){                   //LOGN
        int parent = i;                   //i = parent
        int leftChild = 2*i+1;
        int rightChild = 2*i+2;
        
        if(leftChild < n && arr[leftChild] > arr[parent]){
            parent = leftChild;
        }
        if(rightChild < n && arr[rightChild] > arr[parent]){
            parent = rightChild;
        }
        
        if(parent != i){
            swap(arr[parent], arr[i]);
            heapify(arr, n, parent);
        }
    }
    void convertMinToMaxHeap(vector<int> &arr, int N){
        //build heap
        for(int i = N/2-1 ; i >= 0 ; i--){        //n/2-1 => non leaf node
            heapify(arr, N, i);
        }
    }
};
/*
Example 1:

Input:
N = 4
arr = [1, 2, 3, 4]
Output:
[4, 2, 3, 1]
Explanation:

The given min Heap:

          1
        /   \
      2       3
     /
   4

Max Heap after conversion:

         4
       /   \
      2     3
    /
   1
Example 2:

Input:
N = 5
arr = [3, 4, 8, 11, 13]
Output:
[13, 11, 8, 3, 4]
Explanation:

The given min Heap:

          3
        /   \
      4      8
    /   \ 
  11     13

Max Heap after conversion:

          13
        /    \
      11      8
    /   \ 
   3     4
*/


//MEDIUM PROBLEMS--------------------------------------------------------------------------------------
//208. KTH LARGEST ELEMENT IN AN ARRAY                     {T.C = O(NLOGN), S.C = O(1)}
//BRUTE FORCE (SORTING)                                       
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        return nums[n-k];
    }
};
//USING DECREASING SORT
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end(), greater<int>());  //decreasing sort
        return nums[k-1];
    }
};

//USING MINHEAP  (TWO ITERATION)
//PUT FIRST K ELEMENTS IN MINHEAP, FOR REST MATCH TOP ELEMENT OF MINHEAP AND PUSH ACCORDINGLY
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>>minHeap;
        for(int i = 0 ; i < k ; i++){
            minHeap.push(nums[i]);
        }
        for(int i = k ; i < nums.size(); i++){
            if(nums[i] > minHeap.top()){
                minHeap.pop();
                minHeap.push(nums[i]);
            }
        }
        return minHeap.top();
    }
};

//USING MINHEAP (SINGLE ITERATION)
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>>minHeap;
        for(auto it : nums){
            minHeap.push(it);
            if(minHeap.size() > k){
                minHeap.pop();
            }
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


//209. KTH SMALLEST                                        {T.C = O(NLOGN), S.C = O(1)}
//BRUTE FORCE (SORTING)                                     
class Solution{
    public:
    // arr : given array
    // l : starting index of the array i.e 0
    // r : ending index of the array i.e size-1
    // k : find kth smallest element and return using this function
    int kthSmallest(int arr[], int l, int r, int k) {
        int n = r-l+1;
        sort(arr, arr+n);
        return arr[l+k-1];           //-1 for zero index
    }
};

//USING MAXHEAP                                             
//TWO ITERATION
//PUT FIRST K ELEMENTS IN MAXHEAP, FOR REST MATCH TOP ELEMENT OF MINHEAP AND PUSH ACCORDINGLY
class Solution{
    public:
    int kthSmallest(int arr[], int l, int r, int k) {
        int n = r-l+1;
        priority_queue<int>maxHeap;
        for(int i = 0 ; i < k ; i++){
            maxHeap.push(arr[i]);
        }
        for(int i = k ; i < n ; i++){
            if(arr[i] < maxHeap.top()){
                maxHeap.pop();
                maxHeap.push(arr[i]);
            }
        }
        return maxHeap.top();
    }
};

//USING MAXHEAP
//SINGLE ITERATION
class Solution{
    public:
    int kthSmallest(int arr[], int l, int r, int k) {
        int n = r-l+1;
        priority_queue<int>maxHeap;
        // for(auto it : arr){                //error
        for(int i = l ; i <= r ; i++){
            maxHeap.push(arr[i]);
            if(maxHeap.size() > k){
                maxHeap.pop();
            }
        }
        return maxHeap.top();
    }
};
/*
Example 1:
Input:
n = 6
arr[] = 7 10 4 3 20 15
k = 3
l=0 r=5
Output : 
7
Explanation :
3rd smallest element in the given 
array is 7.

Example 2:
Input:
n = 5
arr[] = 7 10 4 20 15
k = 4 
l=0 r=4
Output : 
15
Explanation :
4th smallest element in the given 
array is 15.
*/


//210. MERGE K SORTED ARRAYS
//BRUTE FORCE (NESTED LOOP)                                 {T.C = O(NK*LOGNK), S.C = O(N)}
class Solution
{
    public:
    vector<int> mergeKArrays(vector<vector<int>> arr, int K)
    {
        vector<int>ans;
        for(int i = 0 ; i < arr.size() ; i++){
            for(int j = 0; j < arr.size() ; j++){
                ans.push_back(arr[i][j]);
            }
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};

//USING MINHEAP                                               {T.C = O(NK*LOGK), S.C = O(N*K{PQ})}
//OBJECT APPROACH         (USING (.))
//PUT FIRST ELEMENT OF EACH ARRAY IN MINHEAP, PUSH EXTRACTED ELEMENT'S ARRAY'S NEXT ELEMENT IN HEAP
class data {
public:
    int val, row, col;
    data(int val, int row, int col) {
        this->val = val;
        this->row = row;
        this->col = col;
    }
};

class compare {
public:
    bool operator()(data &d1, data &d2) {        //CREATE MINHEAP
        return d1.val > d2.val;
    }
};

class Solution {
public:
    vector<int> mergeKArrays(vector<vector<int>> arr, int k) {
        priority_queue<data, vector<data>, compare> minHeap;

        // Insert 1st k elements of each arrays
        for (int i = 0; i < k; i++) {
            data d(arr[i][0], i, 0);
            minHeap.push(d);
        }

        vector<int> ans;
        // Extract answer and push to vector
        while (!minHeap.empty()) {
            data curr = minHeap.top();
            minHeap.pop();
            ans.push_back(curr.val);
            int actualRow = curr.row;
            int actualCol = curr.col;

            if (actualCol + 1 < arr[actualRow].size()) {
                data d2(arr[actualRow][actualCol + 1], actualRow, actualCol + 1);
                minHeap.push(d2);
            }
        }
        return ans;
    }
};

//POINTER APPROACH (USING ->)
class data {
public:
    int val, row, col;
    data(int val, int row, int col) {
        this->val = val;
        this->row = row;
        this->col = col;
    }
};

class compare {
public:
    bool operator()(data* d1, data* d2) {
        return d1->val > d2->val;  // CREATE MINHEAP
    }
};

class Solution {
public:
    vector<int> mergeKArrays(vector<vector<int>>& arr, int k) {
        vector<int> ans;
        priority_queue<data*, vector<data*>, compare> minHeap;

        // Insert 1st element of each array
        for (int i = 0; i < k; i++) {
            if (!arr[i].empty()) {
                data* d = new data(arr[i][0], i, 0);
                minHeap.push(d);
            }
        }

        // Extract minimum element and push the next element of that array
        while (!minHeap.empty()) {
            data* curr = minHeap.top();
            minHeap.pop();
            ans.push_back(curr->val);

            int actualRow = curr->row;
            int actualCol = curr->col;

            if (actualCol + 1 < arr[actualRow].size()) {
                data* d2 = new data(arr[actualRow][actualCol + 1], actualRow, actualCol + 1);
                minHeap.push(d2);
            }

            // Delete the current data object to free memory
            delete curr;
        }

        return ans;
    }
};

/*
Example 1:
Input:
K = 3
arr[][] = {{1,2,3},{4,5,6},{7,8,9}}
Output: 1 2 3 4 5 6 7 8 9
Explanation:Above test case has 3 sorted
arrays of size 3, 3, 3
arr[][] = [[1, 2, 3],[4, 5, 6], 
[7, 8, 9]]
The merged list will be 
[1, 2, 3, 4, 5, 6, 7, 8, 9].

Example 2:
Input:
K = 4
arr[][]={{1,2,3,4},{2,2,3,4},
         {5,5,6,6},{7,8,9,9}}
Output:
1 2 2 2 3 3 4 4 5 5 6 6 7 8 9 9 
Explanation: Above test case has 4 sorted
arrays of size 4, 4, 4, 4
arr[][] = [[1, 2, 2, 2], [3, 3, 4, 4],
[5, 5, 6, 6], [7, 8, 9, 9 ]]
The merged list will be 
[1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 
6, 6, 7, 8, 9, 9].
*/


//211a. MERGE 2 SORTED LISTS(LINKED LIST)
//USE RECURSION                                        {T.C = O(N+M), S.C = O(N+M{RECURSIVE STACK})}
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        //base case
        if(!list1) return list2;
        if(!list2) return list1;

        if(list1->val <= list2->val){
            list1->next = mergeTwoLists(list1->next, list2);
            return list1;
        }else{
            list2->next = mergeTwoLists(list1, list2->next);
            return list2;
        }
    }
};
/*
Example 1:
Input: list1 = [1,2,4], list2 = [1,3,4]
Output: [1,1,2,3,4,4]

Example 2:
Input: list1 = [], list2 = []
Output: []

Example 3:
Input: list1 = [], list2 = [0]
Output: [0]
*/


//211. MERGE K SORTED LISTS(LINKED LIST)                         {T.C = O(NKLOGNK), S.C = O(1)}
//USING MERGE 2 LISTS (ABOVE)
//DIVIDE LIST IN 2 PARTS THEN EACH TIME MERGE 2 LIST
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        //base case
        if(!list1) return list2;
        if(!list2) return list1;

        if(list1->val <= list2->val){
            list1->next = mergeTwoLists(list1->next, list2);
            return list1;
        }else{
            list2->next = mergeTwoLists(list1, list2->next);
            return list2;
        }
    }
    ListNode* partitionAndMerge(int start, int end, vector<ListNode*>&lists){
        //base case
        if(start > end) return NULL;
        if(start == end) return lists[start];

        int mid = start + (end-start)/2;

        ListNode* L1 = partitionAndMerge(start, mid, lists);
        ListNode* L2 = partitionAndMerge(mid+1, end, lists);

        return mergeTwoLists(L1, L2);
    }
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int k = lists.size();
        return k == 0 ? NULL : partitionAndMerge(0, k-1, lists);
    }
};

//USING MINHEAP                                              {T.C = O(NK*LOGK), S.C = O(K)}
class compare{
public:
    bool operator()(ListNode* a, ListNode* b){
       return a->val > b->val;
    }
};
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {

        priority_queue<ListNode* , vector<ListNode*>, compare>minHeap;

        //put first element of each lists(k elements)
        for(int i = 0 ; i < lists.size() ; i++){
            if(lists[i]){
                minHeap.push(lists[i]);
            }
        }

        ListNode* dummyNode = new ListNode(NULL);
        ListNode* temp = dummyNode;
        while(!minHeap.empty()){
            auto topNode = minHeap.top();
            minHeap.pop();

            temp->next = topNode;              
            temp = temp->next;
            if(topNode->next){
                minHeap.push(topNode->next);
            }
        }
        return dummyNode->next;
    }
};
/*
Example 1:
Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted list:
1->1->2->3->4->4->5->6

Example 2:
Input: lists = []
Output: []

Example 3:
Input: lists = [[]]
Output: []
*/


//212. REPLACE ELEMENTS BY ITS RANKS IN THE ARRAY                        {T.C = O(NLOGN), S.C = O(N)}
//BRUTE FORCE (UNIQUE ELEMENT ONLY)                             
//STORE (ELEMENT, ORIGINAL INDEX), SORT, ASSIGN RANK BASED ON SORTED ARRAY
class Solution{
public:
    vector<int> replaceWithRank(vector<int> &arr, int N){
        vector<pair<int,int>>temp;
        for(int i = 0 ; i < N ; i++){           //strore {element, original index)
            temp.push_back({arr[i], i});
        }
        
        sort(temp.begin(), temp.end());        //sort based of element
        
        //assign rank based on sorted array
        vector<int>ans(N);
        for(int i = 0 ; i < N ; i++){
            ans[temp[i].second] = i+1;        //for 1 based index
        }
        
        return ans;
    }
};

//BRUTE FORCE (DUPLICATE ELEMENT )                            
//SIMILAR ABOVE, HANDLE DUPLICATE (RANK++)
class Solution{
public:
    vector<int> replaceWithRank(vector<int> &arr, int N){
        vector<pair<int,int>>temp;
        for(int i = 0 ; i < N ; i++){           //strore {element, original index)
            temp.push_back({arr[i], i});
        }
        
        sort(temp.begin(), temp.end());        //sort based of element
        
        //assign rank based on sorted array
        vector<int>ans(N);
        int rank = 1;
        ans[temp[0].second] = rank;
        for(int i = 1 ; i < N ; i++){
            if(i > 0 && temp[i-1].first != temp[i].first){   //DUPLICATE ELEMENT
                rank++;
            }
            ans[temp[i].second] = rank;       
        }
        
        return ans;
    }
};


//USING MINHEAP
//MAKE MINHEAP(PAIR{ELE, IND}) ELE != TOP ? RANK++ : ANS[I] = RANK
class Solution{
public:
    typedef pair<int,int> P;
    vector<int> replaceWithRank(vector<int> &arr, int N){
        priority_queue<P,vector<P>,greater<P>>minHeap;
        for(int i = 0 ; i < N ; i++){
            minHeap.push({arr[i], i});
        }
        
        vector<int>ans(N);
        int rank = 1;
        while(!minHeap.empty()){
            int i = minHeap.top().second;       //index
            int a = minHeap.top().first;        //element
            minHeap.pop();
            
            ans[i] = rank;
            if(a != minHeap.top().first){
                rank++;
            }
        }
        
        return ans;
    }
};
/*
Example 1:
Input:
N = 6
arr = [20, 15, 26, 2, 98, 6]
Output:
4, 3, 5, 1, 6, 2
Explanation:
After sorting, array becomes {2,6,15,20,26,98}
Rank(2) = 1 (at index 0) 
Rank(6) = 2 (at index 1) 
Rank(15) = 3 (at index 2) 
Rank(20) = 4 (at index 3) and so on..

Example 2:
Input:
N = 4
arr = [2, 2, 1, 6]
Output:
2, 2, 1, 3
Explanation:
After sorting, array becomes {1, 2, 2, 6}
Rank(1) = 1 (at index 0) 
Rank(2) = 2 (at index 1) 
Rank(2) = 2 (at index 2) 
Rank(6) = 3 (at index 3)
Rank(6) = 3 because rank after 2 is 3 as rank 
of same element remains same and for next element 
increases by 1.
*/


//213. TASK SCHEDULAR                                             {T.C = O(NLOG(26)), S.C = O(1)}
//BRUTE FORCE (SORTING)
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int>freq(26);                         //A TO Z
        for(auto it : tasks){
            freq[it-'A']++;
        }
        sort(freq.begin(), freq.end(), greater<int>());    //HIGH FREQ FIRST
        int chunk = freq[0]-1;                       //CHUNK => GAP (BTW A__A)
        int idle = chunk*n;                          //SPOTS = GAP*N
        for(int i = 1 ; i < 26 ; i++){
            idle -= min(chunk, freq[i]);
        }
        return idle > 0 ? tasks.size() + idle : tasks.size();
    }
};

//USING MAXHEAP                                          {T.C = O(NLOG(26), S.C = O(1))}
class Solution {
public:
    int leastInterval(vector<char>& tasks, int p) {
        int n = tasks.size();
        unordered_map<char, int> mp;
        
        for(char &ch : tasks) {
            mp[ch]++;
        }

        priority_queue<int> maxHeap; //max heap
        //we want to finish the process which is most occurring (having highest frequency)
        //so that we don't have to finish in the last with p gaps.
        int time = 0;
        
        for(auto &it : mp) {
            maxHeap.push(it.second);
        }
        
        while(!maxHeap.empty()) {
            vector<int> temp;
            for(int i = 1; i<=p+1; i++) {
                //filling first p+1 characters
                if(!maxHeap.empty()) {
                    temp.push_back(maxHeap.top()-1); //finishing one instance of each process
                    maxHeap.pop();
                }
            }
            
            for(int &freq : temp) {
                if(freq > 0)
                    maxHeap.push(freq);
            }
            
            if(maxHeap.empty()) //all processes finished
                time += temp.size();
            else
                time += (p+1); //we finished p+1 tasks above in the loop
            
        }
        
        return time;
    }
};
/*
Example 1:
Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: A possible sequence is: A -> B -> idle -> A -> B -> idle -> A -> B.
After completing task A, you must wait two cycles before doing A again. The same applies to task B. In the 3rd interval, neither A nor B can be done, so you idle. By the 4th cycle, you can do A again as 2 intervals have passed.

Example 2:
Input: tasks = ["A","C","A","B","D","B"], n = 1
Output: 6
Explanation: A possible sequence is: A -> B -> C -> D -> A -> B.
With a cooling interval of 1, you can repeat a task after just one other task.

Example 3:
Input: tasks = ["A","A","A", "B","B","B"], n = 3
Output: 10
Explanation: A possible sequence is: A -> B -> idle -> idle -> A -> B -> idle -> idle -> A -> B.
There are only two types of tasks, A and B, which need to be separated by 3 intervals. This leads to idling twice between repetitions of these tasks.
*/


//214. HAND OF STRAIGHTS                                    {T.C = O(NLOGN), S.C = O(N)}
//USING MINHEAP & MAP
class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        int n = hand.size();
        //base case
        if(n % groupSize != 0){
            return false;
        }

        priority_queue<int,vector<int>, greater<int>>minHeap;
        for(auto it : hand){
            minHeap.push(it);
        }
        
        unordered_map<int,int>mp;
        for(auto it : hand){
            mp[it]++;
        }

        while(!minHeap.empty()){
            int smallest = minHeap.top();
            minHeap.pop();
            if(mp[smallest] == 0){
                continue;
            }
            for(int i = 0 ; i < groupSize ; i++){
                int currCard = smallest + i;
                if(mp[currCard] == 0){             //next consecutive card not found
                    return false;
                }
                mp[currCard]--;
                if(mp[currCard] > 0){
                    minHeap.push(currCard);        //more same card push again for future
                }
            }
        }
        return true;
    }
};
/*
Example 1:
Input: hand = [1,2,3,6,2,3,4,7,8], groupSize = 3
Output: true
Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8]

Example 2:
Input: hand = [1,2,3,4,5], groupSize = 4
Output: false
Explanation: Alice's hand can not be rearranged into groups of 4.
*/


//214b. DIVIDE ARRAY IN SETS OF K CONSECUTIVE NUMBER           {T.C = O(NLOGN), S.C = O(N)}
//SAME AS ABOVE
class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        int n = nums.size();
        //base case
        if(n % k != 0){
            return false;
        }

        priority_queue<int,vector<int>,greater<int>>minHeap;
        for(auto it : nums){
            minHeap.push(it);
        }

        unordered_map<int,int>mp;
        for(auto it : nums){
            mp[it]++;
        }

        while(!minHeap.empty()){
            int smallest = minHeap.top();
            minHeap.pop();
            if(mp[smallest] == 0){                   //necessary step
                continue;
            }
            for(int i = 0 ; i < k ; i++){
                int currNumber = smallest + i;
                if(mp[currNumber] == 0){             //next consecutive no. not found
                    return false;
                }
                mp[currNumber]--;
                if(mp[currNumber] > 0){             //again push to minheap for future
                    minHeap.push(currNumber);
                }
            }
        }
        return true;
    }
};
/*
Example 1:
Input: nums = [1,2,3,3,4,4,5,6], k = 4
Output: true
Explanation: Array can be divided into [1,2,3,4] and [3,4,5,6].

Example 2:
Input: nums = [3,2,1,2,3,4,3,4,5,9,10,11], k = 3
Output: true
Explanation: Array can be divided into [1,2,3] , [2,3,4] , [3,4,5] and [9,10,11].

Example 3:
Input: nums = [1,2,3,4], k = 3
Output: false
Explanation: Each array should be divided in subarrays of size 3.
*/


//215. DESIGN TWITTER                                     {T.C = O(N^2), S.C = O(N)}
//USE MAXHEAP AND MAP
class Twitter {
public:
    long long time;
    unordered_map<int,set<int>>following;               //{userId, {followees}}
    unordered_map<int,vector<pair<int,int>>>tweets;     //{userId, {tweetTime, tweetId}}
    Twitter() {
        time = 0;
    }
    
    void postTweet(int userId, int tweetId) {
        tweets[userId].push_back({time++, tweetId});
    }
    
    vector<int> getNewsFeed(int userId) {
        vector<int>ans;
        priority_queue<pair<int,int>>maxHeap;
        for(auto it : tweets[userId]){          //add user's own tweets to maxheap
            maxHeap.push(it);
        }
        for(auto it: following[userId]){        //Add the tweets from the users the current user is following
            for(auto j : tweets[it]){
                maxHeap.push(j);
            }
        }
        while(!maxHeap.empty() && ans.size() < 10){  // Retrieve up to 10 most recent tweets
            ans.push_back(maxHeap.top().second);
            maxHeap.pop();
        }
        return ans;
    }
    
    void follow(int followerId, int followeeId) {
        following[followerId].insert(followeeId);
    }
    
    void unfollow(int followerId, int followeeId) {
        following[followerId].erase(followeeId);
    }
};
/*
Input
["Twitter","postTweet","getNewsFeed","follow","postTweet","getNewsFeed","unfollow","getNewsFeed"]
[[],[1,5],[1],[1,2],[2,6],[1],[1,2],[1]]
Output
[null,null,[5],null,null,[6,5],null,[5]]
*/


//216. MINIMUM COST OF ROPES / CONNECT N ROPES WITH MINIMUM COST  {T.C = O(NLOGN), S.C = O(N)}
//USING MINHEAP, POP 1 AND 2 (TOP) , SUM THEN PUSH AGAIN (MAKE UNTIL SIZE > 1)
class Solution{
    public:
    long long minCost(long long arr[], long long n) {
        priority_queue<long long,vector<long long>,greater<long>>minHeap;
        for(int i = 0 ; i < n; i++){
            minHeap.push(arr[i]);
        }
        
        long long ans = 0;
        while(minHeap.size() > 1){            //not minHeap.empty()
            long long firstSmallest = minHeap.top();
            minHeap.pop();
            long long secondSmallest = minHeap.top();
            minHeap.pop();
            
            long long sum = firstSmallest + secondSmallest;
            minHeap.push(sum);
            
            ans += sum;
        }
        return ans;
    }
};
/*
Example 1:
Input:
n = 4
arr[] = {4, 3, 2, 6}
Output: 
29
Explanation:
We can connect the ropes in following ways.
1) First connect ropes of lengths 2 and 3.
Which makes the array {4, 5, 6}. Cost of
this operation 2+3 = 5. 
2) Now connect ropes of lengths 4 and 5.
Which makes the array {9, 6}. Cost of
this operation 4+5 = 9.
3) Finally connect the two ropes and all
ropes have connected. Cost of this 
operation 9+6 =15
Total cost for connecting all ropes is 5
+ 9 + 15 = 29. This is the optimized cost
for connecting ropes. 
Other ways of connecting ropes would always 
have same or more cost. For example, if we 
connect 4 and 6 first (we get three rope of 3,
2 and 10), then connect 10 and 3 (we get
two rope of 13 and 2). Finally we
connect 13 and 2. Total cost in this way
is 10 + 13 + 15 = 38.
*/


//217. KTH LARGEST ELEMENT IN A STREAM                            {T.C = O(NLOGN), S.C = O(N)}
//SIMPLY FIND KTH LARGES ELEMENT IN ARRAY, PUSH VAL IN HEAP , IF SIZE > K , POP
class KthLargest {
public:
    int k;
    priority_queue<int, vector<int>,greater<int>>minHeap;
    KthLargest(int k, vector<int>& nums) {
        this->k = k;
        for(auto it : nums){
            minHeap.push(it);
            if(minHeap.size() > k){
                minHeap.pop();
            }
        }
    }
    
    int add(int val) {
        minHeap.push(val);
        if(minHeap.size() > k){
            minHeap.pop();
        }
        return minHeap.top();
    }
};
/*
Example 1:
Input
["KthLargest", "add", "add", "add", "add", "add"]
[[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
Output
[null, 4, 5, 5, 8, 8]
Explanation
KthLargest kthLargest = new KthLargest(3, [4, 5, 8, 2]);
kthLargest.add(3);   // return 4
kthLargest.add(5);   // return 5
kthLargest.add(10);  // return 5
kthLargest.add(9);   // return 8
kthLargest.add(4);   // return 8
*/


//218. MAXIMUM SUM COMBINATION                             {T.C = O(NLOGN), S.C = O(N)}
//USE SORTING + MAXHEAP
class Solution {
  public:
    vector<int> maxCombinations(int N, int K, vector<int> &A, vector<int> &B) {
        vector<int>ans;
        
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());
        
        priority_queue<pair<int, pair<int,int>>>maxHeap;           //{sum,{i, j}} i, j = 1st & 2nd array index
        
        set<pair<int, int>>st;                                //{i,j}
        
        maxHeap.push({A.back() + B.back(), {N-1, N-1}});          //push last element of both vector
        st.insert({N-1, N-1});                                //st.push for stack
        while(K--){
            auto frontNode = maxHeap.top();                      //q.front for queue
            int sum = frontNode.first;
            int i = frontNode.second.first;
            int j = frontNode.second.second;
            ans.push_back(sum);
            maxHeap.pop();
            
            //if  one of last element not present (edge cases)
            if(!st.count({i-1, j})){                 //second last(A) element not present in set
                maxHeap.push({A[i-1]+B[j], {i-1, j}});
                st.insert({i-1, j});
            }
            if(!st.count({i, j-1})){                 //second last(B) element not present in set
                maxHeap.push({A[i]+ B[j-1], {i, j-1}});
                st.insert({i, j-1});
            }
        }
        return ans;
    }
};
/*
Example 1:
Input:
N = 2
K = 2
A [ ] = {3, 2}
B [ ] = {1, 4}
Output: {7, 6}
Explanation: 
7 -> (A : 3) + (B : 4)
6 -> (A : 2) + (B : 4)

Example 2:
Input:
N = 4
K = 3
A [ ] = {1, 4, 2, 3}
B [ ] = {2, 5, 1, 6}
Output: {10, 9, 9}
Explanation: 
10 -> (A : 4) + (B : 6)
9 -> (A : 4) + (B : 5)
9 -> (A : 3) + (B : 6)
*/


//219. FIND MEDIAN FROM DATA STREAM                            {T.C = O(LOGN), S.C = O(N)}
//USING MAXHEAP(LEFT PART(N/2)) AND MINHEAP(RIGHT PART (N/2)), ODD (LEFT SHOULD GREATER)
class MedianFinder {
public:
    priority_queue<int>leftMaxHeap;
    priority_queue<int, vector<int>, greater<int>>rightMinHeap;

    MedianFinder() {}
    
    void addNum(int num) {
        if(leftMaxHeap.empty() || num < leftMaxHeap.top()){       //insert in left side 
            leftMaxHeap.push(num);
        }else{
            rightMinHeap.push(num);
        }

        //maintain left and right heap (left should be greater element if one extra)
        if(abs((int)leftMaxHeap.size() - (int)rightMinHeap.size()) > 1){
            rightMinHeap.push(leftMaxHeap.top());
            leftMaxHeap.pop(); 
        }else if(leftMaxHeap.size() < rightMinHeap.size()){          //left should be greater always
            leftMaxHeap.push(rightMinHeap.top());
            rightMinHeap.pop();
        }   
    }
    
    double findMedian() {
        if(leftMaxHeap.size() == rightMinHeap.size()){               //even
            return (leftMaxHeap.top()+rightMinHeap.top()) / 2.0;
        }                                                      
        return leftMaxHeap.top()/1.0;           //size not equal                          //odd               
    }
};
/*
Example 1:
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


//220. TOP K FREQUENT ELEMENTS                            {T.C = O(NLOGN), S.C = O(N)}
//USING MAXHEAP AND MAP({FREQ, ELEMENT})
class Solution {
public:
    typedef pair<int,int> P;
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int>mp;
        for(auto it : nums){
            mp[it]++;
        }
        priority_queue<P>maxHeap;                      //{freq, element}
        for(auto it : mp){
            maxHeap.push({it.second, it.first});
        }

        vector<int>ans;
        for(int i = 0 ; i < k ; i++){
            int element = maxHeap.top().second;
            maxHeap.pop();
            ans.push_back(element);
        }

        return ans;
    }
};
/*
Example 1:
Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Example 2:
Input: nums = [1], k = 1
Output: [1]
*/


/*---------------------------------------THE END-------------------------------------------------------*/