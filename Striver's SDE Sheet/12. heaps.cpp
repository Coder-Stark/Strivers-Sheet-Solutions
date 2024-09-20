#include<bits/stdc++.h>
using namespace std;


//DAY 12: HEAPS ----------------------------------------------------------------------------------------------
/*
1 based indexing
left child  = 2*i
parent      = i/2
right child = 2*i + 1

0 based indexing
left child  = 2*i + 1;
parent      = i/2 + 1;
right child = 2*i + 2

LEAF NODES LIES INDEX
n/2+1 to n                      (include both)
*/


//69. MIN HEAP / MAXHEAP  IMPLEMENTATION
class heap{
public:
    int arr[100];
    int size;

    heap(){
        arr[0] = -1;
        size = 0;
    }

    void insert(int val){                                     //{T.C = O(LOGN)}
        size = size + 1;
        int i = size;
        arr[i] = val;

        while(i > 1){
            int parent = i/2;

            if(arr[parent] < arr[i]){
                swap(arr[parent],arr[i]);
                i = parent;
            }
            else{
                return;
            }
        }
    }
    
    void deleteFromHeap(){                                            //{T.C = O(LOGN)}
        if(size == 0){
            cout<<"Nothing to delete"<<endl;
        }

        //move last element to 1 OR root element
        arr[1] = arr[size];

        //remove last element
        size--;

        //move root to its correct position
        int i = 1;
        while(i < size){
            int leftIndex = 2 * i;
            int rightIndex = 2 * i + 1;
            if(leftIndex < size && arr[i] < arr[leftIndex]){
                swap(arr[i] , arr[leftIndex]);
                i = leftIndex;
            }
            else if(rightIndex < size && arr[i] < arr[rightIndex]){
                swap(arr[i] , arr[rightIndex]);
                i = rightIndex;
            }
            else{
                return;
            }
        }

    }
    void print(){
        for(int i = 1 ; i <= size ; i++){
            cout<<arr[i]<<" ";
        }
    }
};

//heapify work = take node to its correct position in a heap
void heapify(int arr[] , int n , int i){                               //{T.C = O(LOGN)}
    int largest = i;
    int left = 2 * i ;
    int right = 2 * i + 1;

    if(left <= n && arr[largest] < arr[left]){
        largest = left;
    }
    if(right <= n && arr[largest] < arr[right]){
        largest = right;
    }

    if(largest != i){                            //is updated 
        swap(arr[largest],arr[i]);
        heapify(arr,n,largest);
    }
}

void heapSort(int arr[], int n){                                          //{T.C = O(N*LOGN)}
    int size = n;
    while(size>1){
        //swap
        swap(arr[size], arr[1]);
        
        //remove element
        size--;

        //heapify
        heapify(arr, size, 1);
    }

}
int main(){
    heap h;
    h.insert(50);
    h.insert(55);
    h.insert(53);
    h.insert(52);
    h.insert(54);
    
    cout<<"After Insertion in a Heap"<<endl;
    h.print();
    cout<<endl;

    h.deleteFromHeap();
    cout<<"After Deletion in a Heap"<<endl;
    h.print();

    int arr[6] = {-1, 54, 53, 55, 52, 50};
    int n = 5;
    //heap creation              
    for(int i = n/2 ; i > 0 ; i--){                //n/2 to n is leaf nodes no need to process
        heapify(arr, n, i);
    }

    cout<<endl;

    cout<<"Printing the array after heapify"<<endl;
    for(int i = 1 ; i <= n ; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;

    heapSort(arr,n);
    cout<<"Printing sorted Array"<<endl;
    for(int i = 1 ; i <= n ; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;


    //Build heap using Priority queue
    //Priority is already in Max heap format

    priority_queue<int>pq;

    pq.push(4);
    pq.push(2);
    pq.push(5);
    pq.push(3);

    cout<<"Element at Top in maxHeap "<<pq.top()<<endl;
    pq.pop();
    cout<<"Element at Top in maxHeap "<<pq.top()<<endl;

    cout<<"Size is "<<pq.size()<<endl;

    if(pq.empty()){
        cout<<"pq is empty"<<endl;
    }
    else{
        cout<<"pq is not empty"<<endl;
    }


    //Min heap using Priority queue
    priority_queue<int, vector<int>,greater<int>>pqmin;
    pqmin.push(4);
    pqmin.push(2);
    pqmin.push(5);
    pqmin.push(3);

    cout<<"Element at Top in minHeap "<<pqmin.top()<<endl;
    pqmin.pop();
    cout<<"Element at Top in minHeap "<<pqmin.top()<<endl;
    cout<<"Size is "<<pq.size()<<endl;

    if(pq.empty()){
        cout<<"pqmin is empty"<<endl;
    }
    else{
        cout<<"pqmin is not empty"<<endl;
    }
    return 0;
}


/*output
After Insertion in a Heap
55 54 53 50 52
After Deletion in a Heap
54 52 53 50

Printing the array after heapify
55 53 54 52 50

Printing sorted Array
50 52 53 54 55

//maxHeap using pq
Element at Top in maxHeap 5
Element at Top in maxHeap 4
Size is 3
pq is not empty

//minHeap using pq
Element at Top in minHeap 2
Element at Top in minHeap 3
Size is 3
pqmin is not empty
*/


//BUILD MIN HEAP (0 INDEXING)                                  {T.C = O(n)}
void heapify(vector<int>&arr , int n , int i){

    int smallest = i;                            //maxHeap largest = i and in comparision sign change else same
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
OUTPUT
Sample Input 1 :
2
5
9 3 2 6 7 
4
1 3 2 4
Sample Output 1 :
1
1
*/


//69b. HEAP SORT                                                     {T.C = O(N*LOGN), S.C = O(N)}
class Solution
{
    public:
    //0 BASED INDEXING & MAX HEAP
    //Heapify function to maintain heap property.
    void heapify(int arr[], int n, int i){
        int largest = i;
        int leftIdx  = 2*i+1;
        int rightIdx = 2*i+2;
        
        if(leftIdx < n && arr[largest] < arr[leftIdx])   largest = leftIdx;  //in 1 based lIdx <= n
        if(rightIdx < n && arr[largest] < arr[rightIdx])  largest = rightIdx;
        
        if(largest != i){
            swap(arr[largest], arr[i]);
            heapify(arr, n, largest);
        }
    }

    public:
    //Function to build a Heap from array.
    void buildHeap(int arr[], int n)  
    { 
        for(int i = n/2-1 ; i >= 0 ; i--){
            heapify(arr, n, i);
        }
    }

    
    public:
    //Function to sort an array using Heap Sort.
    void heapSort(int arr[], int n){
        buildHeap(arr, n);
        int sz = n;
        while(sz > 1){
            swap(arr[sz-1], arr[0]);
            sz--;
            heapify(arr, sz, 0);                    //sz not n
        }
    }
};
/*
Example 1:
Input:
N = 5
arr[] = {4,1,3,9,7}
Output:
1 3 4 7 9
Explanation:
After sorting elements
using heap sort, elements will be
in order as 1,3,4,7,9.

Example 2:
Input:
N = 10
arr[] = {10,9,8,7,6,5,4,3,2,1}
Output:
1 2 3 4 5 6 7 8 9 10
Explanation:
After sorting elements
using heap sort, elements will be
in order as 1, 2,3,4,5,6,7,8,9,10.
*/


//70. KTH LARGEST ELEMENT IN AN ARRAY                      
//for finding largest build minheap and vice versa                    {T.C = O(N*LOGK), S.C = O(N)}
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


//71. MAXIMUM SUM COMBINATION                                          {T.C = O(N*LOGN), S.C = O(N)}
class Solution {                                       //{T.C = O(N*LOGN), S.C = O(N)
  public:
    vector<int> maxCombinations(int N, int K, vector<int> &A, vector<int> &B) {
        sort(A.rbegin(), A.rend());
        sort(B.rbegin(), B.rend());
        
        priority_queue<pair<int,pair<int,int>>>pq;      //maxHeap    //{sum, i, j}
        pq.push({A[0]+B[0], {0, 0}});
        
        set<pair<int,int>>st;                          //vis index (for uniqueness)
        st.insert({0, 0});
        
        vector<int>ans;
        while(K-- && !pq.empty()){
            auto topNode = pq.top();
            pq.pop();
            int sum = topNode.first;
            int i   = topNode.second.first;
            int j   = topNode.second.second;
            
            ans.push_back(sum);
            
            //push next combinations
            if(i+1 < N && !st.count({i+1, j})){
                pq.push({A[i+1] + B[j], {i+1, j}});
                st.insert({i+1, j});
            }
            if(j+1 < N && !st.count({i, j+1})){
                pq.push({A[i]+B[j+1], {i, j+1}});
                st.insert({i, j+1});
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


//72. FIND MEDIAN FROM DATA STREAM                                       {T.C = O(N), S.C = O(N)}
//2 HEAP (MAX AND MIN)
class MedianFinder {
public:
    priority_queue<int>leftMaxHeap;
    priority_queue<int,vector<int>, greater<int>>rightMinHeap;
    MedianFinder() {}
    
    void addNum(int num) {
        if(leftMaxHeap.empty() || num < leftMaxHeap.top()) leftMaxHeap.push(num);
        else rightMinHeap.push(num);

        int n = leftMaxHeap.size(), m = rightMinHeap.size();
        if(n < m){                                             //left should be extra element not right
            leftMaxHeap.push(rightMinHeap.top());
            rightMinHeap.pop();
        }else if(abs(n-m) > 1){                                //diff should not be > 1 b/w both size of heaps         
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

Constraints:
-105 <= num <= 105
There will be at least one element in the data structure before calling findMedian.
At most 5 * 104 calls will be made to addNum and findMedian.
*/


//73. MERGE K SORTED ARRAY           
//BRUTE FORCE                                                               {T.C = O(N*LOGN), S.C = O(N)}            
class Solution
{
    public:
    vector<int> mergeKArrays(vector<vector<int>> arr, int K)
    {
        vector<int>ans;
        for(int i = 0 ; i < arr.size(); i++){
            for(auto it : arr[i]){
                ans.push_back(it);
            }
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};

//USING MINHEAP                                                             {T.C = O(N*LOGK), S.C = O(K)}
class Solution {
public:
    typedef pair<int,pair<int,int>>P;            //data, row, col
    vector<int> mergeKArrays(vector<vector<int>> arr, int k) {
        
        vector<P>temp; 
        for(int i = 0 ; i < k ;i++){               //push 1st col element of matrix
            temp.push_back({arr[i][0], {i, 0}});     
        }
        priority_queue<P, vector<P>, greater<P>>minHeap(temp.begin(), temp.end());

        // Extract answer and push to vector
        vector<int>ans;
        while (!minHeap.empty()) {
            auto topNode = minHeap.top();
            minHeap.pop();
            
            ans.push_back(topNode.first);
            int i = topNode.second.first;                  //actual row, col
            int j = topNode.second.second;

            if (j + 1 < arr[i].size()) {           //or j+1 < k   //(for next push)
                minHeap.push({arr[i][j+1], {i, j+1}});
            }
        }
        return ans;
    }
};
/*
Input: k = 3, arr[][] = {{1,2,3},{4,5,6},{7,8,9}}
Output: 1 2 3 4 5 6 7 8 9
Explanation: Above test case has 3 sorted arrays of size 3, 3, 3 arr[][] = [[1, 2, 3],[4, 5, 6],[7, 8, 9]]. The merged list will be [1, 2, 3, 4, 5, 6, 7, 8, 9].

Input: k = 4, arr[][]={{1,2,3,4},{2,2,3,4},{5,5,6,6},{7,8,9,9}}
Output: 1 2 2 2 3 3 4 4 5 5 6 6 7 8 9 9 
Explanation: Above test case has 4 sorted arrays of size 4, 4, 4, 4 arr[][] = [[1, 2, 2, 2], [3, 3, 4, 4], [5, 5, 6, 6], [7, 8, 9, 9 ]]. The merged list will be [1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8, 9, 9].
*/


//73b. MERGE K SORTED LINKED LIST                                             {T.C = O(N*LOGK), S.C = O(K)}
class compare{
public: 
    bool operator()(Node* a, Node* b){
        return a->data > b->data;          //in heap reverse symbol (acutal <)
    }
};
class Solution {
  public:
    Node* mergeKLists(vector<Node*>& arr) {
        
        /* same as belwo initialization
        int k = arr.size();
        for(int i = 0 ; i < k ; i++){            //inserting 1st node of each list
            if(arr[i]) minHeap.push(arr[i]);
        }
        */
        
        // priority_queue<int,vector<int>,greater<int>>minHeap;
        priority_queue<Node*, vector<Node*>, compare>minHeap(arr.begin(), arr.end());   //insert 1st node of each list
        Node* head = NULL;
        Node* tail = NULL;
        //Extract answer and push to list
        while(!minHeap.empty()){
            Node* topNode = minHeap.top();
            minHeap.pop();
            
            if(topNode->next) minHeap.push(topNode->next);
            
            //answer ll is emepty or insert first element 
            if(!head){
                head = topNode;
                tail = topNode;
            }else{
                tail->next = topNode;
                tail = topNode;
            }
        }
        return head;
    }
};
/*
Input: arr = [1->2->3, 4->5, 5->6, 7->8]
Output: 1->2->3->4->5->5->6->7->8
Explanation:
The test case has 4 sorted linked 
list of size 3, 2, 2, 2
1st    list     1 -> 2-> 3
2nd   list      4->5
3rd    list      5->6
4th    list      7->8
The merged list will be

Input: arr = [1->3, 4->5->6, 8]
Output: 1->3->4->5->6->8
Explanation:
The test case has 3 sorted linked
list of size 2, 3, 1.
1st list 1 -> 3
2nd list 4 -> 5 -> 6
3rd list 8
The merged list will be
*/


//74. TOP K FREQUENT ELEMENTS                                              
//USING MAP                                                                  {T.C = O(N*LOGN), S.C = O(N)}
class Solution {
public:                 
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int>mp;
        for(auto it : nums) mp[it]++;
        
        vector<pair<int,int>>v;
        for(auto it : mp) v.push_back({it.second, it.first});
        
        sort(v.rbegin(), v.rend());
        vector<int>ans;
        /*
        for(int i = 0 ; i < v.size() && k != 0 ; i++){
            ans.push_back(v[i].second);                      //second is ele
            k--;
        }
        */
        int i = 0, n = v.size();
        while(i < n && k != 0){
            ans.push_back(v[i].second);
            i++, k--;
        }
        return ans;
    }
};

//USING MAXHEAP                                                           {T.C = O(N*LOGN), S.C = O(N)}
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int>mp;
        for(auto it : nums) mp[it]++;

        priority_queue<pair<int,int>>maxHeap;
        for(auto it : mp) maxHeap.push({it.second, it.first});

        vector<int>ans;
        while(k--){
            ans.push_back(maxHeap.top().second);              //second is element
            maxHeap.pop();
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