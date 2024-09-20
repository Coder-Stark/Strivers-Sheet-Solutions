#include<bits/stdc++.h>
using namespace std;


//DAY 13: STACK AND QUEUES-----------------------------------------------------------------------------------------------
/*
class MyStack{
private:
    int arr[1000];
    int top;
public:
    MyStack() top=-1;
    
    int pop();
    void push(int);
};
*/
//75. IMPLETEMENT STACK USING ARRAY                                          {T.C = O(1), S.C = O(1)}
void MyStack :: push(int x){
    top++;                                //new element push on top                //first increase then update 
    arr[top] = x;
}

int MyStack :: pop(){
    return top == -1 ? -1 : arr[top--];  //top element remove
}
/*
Input: 1 2 1 3 2 1 4 2 
Output: 3, 4
Explanation: 
push(2)    the stack will be {2}
push(3)    the stack will be {2 3}
pop()      poped element will be 3,
           the stack will be {2}
push(4)    the stack will be {2 4}
pop()      poped element will be 4

Input: 2 1 4 1 5 2
Output: -1, 5
*/



/* 
class MyQueue {
private:
    int arr[100005];
    int front;
    int rear;
public :
    MyQueue() front=0; rear=0;
    void push(int);
    int pop();
};
 */
//76. IMPLEMENT QUEUE USING ARRAY                                             {T.C = O(1), S.C = O(1)}
void MyQueue :: push(int x){
    arr[rear] = x;                     //update the  increase rear
    rear++;
}

int MyQueue :: pop(){
    return front == rear ? -1 : arr[front++];
}
/*
Input: Q = 5, Queries = 1 2 1 3 2 1 4 2
Output: 2 3
Explanation:
In the first test case for query 
1 2 the queue will be {2}
1 3 the queue will be {2 3}
2   poped element will be 2 the 
    queue will be {3}
1 4 the queue will be {3 4}
2   poped element will be 3 

Input: Q = 4, Queries = 1 3 2 2 1 4   
Output: 3 -1
Explanation:
In the second testcase for query 
1 3 the queue will be {3}
2   poped element will be 3 the
    queue will be empty
2   there is no element in the
    queue and hence -1
1 4 the queue will be {4}. 
*/


//77. IMPLEMENT STACK USING QUEUES
class MyStack {
public:
    queue<int>q;
    MyStack() {}
    
    void push(int x) {                                         //{T.C = O(N)}
        int n = q.size();
        q.push(x);
        while(n--){
            q.push(q.front());
            q.pop();
        }
    }
    
    int pop() {                                                //{T.C = O(1)}
        int ele = q.front();
        q.pop();
        return ele;
    }
    
    int top() {                                                //{T.C = O(1)}
        return q.front();
    }
    
    bool empty() {                                             //{T.C = O(1)}
        return q.empty();
    }
};
/*
Example 1:

Input
["MyStack", "push", "push", "top", "pop", "empty"]
[[], [1], [2], [], [], []]
Output
[null, null, null, 2, 2, false]

Explanation
MyStack myStack = new MyStack();
myStack.push(1);
myStack.push(2);
myStack.top(); // return 2
myStack.pop(); // return 2
myStack.empty(); // return False
*/


//78. IMPLEMENT QUEUE USING STACK 
class MyQueue {
public:
    stack<int>stk;
    MyQueue() {}
    
    void push(int x) {                                                    //{T.C = O(N)}
        //base case
        if(stk.empty()){
            stk.push(x);
            return;
        }
        int ele = stk.top();
        stk.pop();
        push(x);                               //recursion
        stk.push(ele);
    }
    
    int pop() {                                                          //{T.C = O(1)}
        int ele = stk.top();
        stk.pop();
        return ele;
    }
    
    int peek() {                                                         //{T.C = O(1)}
        return stk.top();
    }
    
    bool empty() {                                                      //{T.C = O(1)}
        return stk.empty();
    }
};
/*
Input
["MyQueue", "push", "push", "peek", "pop", "empty"]
[[], [1], [2], [], [], []]
Output
[null, null, null, 1, 1, false]
Explanation
MyQueue myQueue = new MyQueue();
myQueue.push(1); // queue is: [1]
myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
myQueue.peek(); // return 1
myQueue.pop(); // return 1, queue is [2]
myQueue.empty(); // return false
*/


//79. VALID PARENTHESIS                                                {T.C = O(N), S.C = O(N)}
class Solution {
public:
    bool isValid(string s) {
        stack<char>stk;
        for(auto ch : s){
            if(ch == '(' || ch == '[' || ch == '{') stk.push(ch);
            else if(!stk.empty() && ( (stk.top() == '(' && ch == ')') || (stk.top() == '[' && ch == ']') || (stk.top() == '{' && ch == '}') ) ){
                stk.pop();
            }else return false;
        }
        return stk.empty();                   //empty => valid 
    }
};
/*
Example 1:
Input: s = "()"
Output: true

Example 2:
Input: s = "()[]{}"
Output: true

Example 3:
Input: s = "(]"
Output: false

Example 4:
Input: s = "([])"
Output: true
*/


//80a. NEXT GREATER ELEMENT (SAME ARRAYS NEXT ELEMENT)
//BRUTE FORCE                                                                     {T.C = O(N*M), S.C = O(N)}
class Solution{
    public:
    vector<long long> nextLargerElement(vector<long long> arr, int n){
        vector<long long>ans(n, -1);
        for(int i = 0 ; i < n ; i++){
            for(int j = i+1 ; j < n ; j++){
                if(arr[j] > arr[i]){
                    ans[i] = arr[j];
                    break;
                }
            }
        }
        return ans;
    }
};

//USING STACK                                                                      {T.C = O(N), S.C = O(N)}
class Solution{
    public:       
    vector<long long> nextLargerElement(vector<long long> arr, int n){
        vector<long long>ans(n, -1);
        stack<long long>stk;
        for(int i = n-1 ; i >= 0 ; i--){
            while(!stk.empty() && stk.top() <= arr[i]) stk.pop();
            if(!stk.empty()) ans[i] = stk.top();                     //not empty nge(ans found)
            stk.push(arr[i]);
        }
        return ans;
    }
};
/*
Input: arr[] = [1 3 2 4], n = 4
Output: 3 4 4 -1
Explanation: The next larger element to 1 is 3, 3 is 4, 2 is 4 and for 4, since it doesn't exist, it is -1.

Input: arr[] [6 8 0 1 3], n = 5
Output: 8 -1 1 3 -1
Explanation: The next larger element to 6 is 8, for 8 there is no larger elements hence it is -1, for 0 it is 1 , for 1 it is 3 and then for 3 there is no larger element on right and hence -1.
*/


//80. NEXT GREATER ELEMENT I  (2 ARRAYS FIRST SEARCH IN 1ST THEN NGE IN NEXT)                   
//BRUTE FORCE                                                                      {T.C = O(N*M), S.C = O(N)}
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        vector<int>ans(n, -1);
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < m; j++){
                if(nums1[i] == nums2[j]){
                    for(int k = j+1 ; k < m ; k++){
                        if(nums2[k] > nums2[j]){
                            ans[i] = nums2[k];
                            break;
                        }
                    }
                }
            }
        }
        return ans;
    }
};
/*
Example 1:
Input: nums1 = [4,1,2], nums2 = [1,3,4,2]
Output: [-1,3,-1]
Explanation: The next greater element for each value of nums1 is as follows:
- 4 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the answer is -1.
- 1 is underlined in nums2 = [1,3,4,2]. The next greater element is 3.
- 2 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the answer is -1.

Example 2:
Input: nums1 = [2,4], nums2 = [1,2,3,4]
Output: [3,-1]
Explanation: The next greater element for each value of nums1 is as follows:
- 2 is underlined in nums2 = [1,2,3,4]. The next greater element is 3.
- 4 is underlined in nums2 = [1,2,3,4]. There is no next greater element, so the answer is -1.
*/


//81. SORT A STACK                                                 {T.C = O(N*N), S.C = O(N)}
void insertAtBottom(stack<int>&s, int x){
    if(s.empty() || x > s.top()){
        s.push(x);
        return;
    }
    
    int num = s.top();
    s.pop();
    insertAtBottom(s, x);
    s.push(num);
}
void SortedStack :: sort(){
    if(s.empty()) return;

    int num = s.top();
    s.pop();
    sort();                                     
    insertAtBottom(s, num);
}
/*
Example 1:
Input:
Stack: 3 2 1
Output: 3 2 1

Example 2:
Input:
Stack: 11 2 32 3 41
Output: 41 32 11 3 2
*/


//82. HELP CLASSMATES / NEXT SMALLER ELEMENT        
//BRUTE FORCE                                                   {T.C = O(N^2), S.C = O(N)}
class Solution{
    public:
    vector<int> help_classmate(vector<int> arr, int n){ 
        vector<int>ans(n, -1);
        for(int i = 0 ; i < n ; i++){
            for(int j = i+1 ; j < n ;j++){
                if(arr[j] < arr[i]){
                    ans[i] = arr[j];
                    break;
                }
            }
        }
        return ans;
    } 
};

//USING STACK                                                      {T.C = O(N), S.C = O(N)}
class Solution{
    public:
    vector<int> help_classmate(vector<int> arr, int n){ 
        vector<int>ans(n, -1);
        stack<int>stk;
        for(int i = n-1 ;  i >= 0 ; i--){
            while(!stk.empty() && stk.top() >= arr[i]) stk.pop();  //top >= arr ? pop : push ans
            if(!stk.empty()) ans[i] = stk.top();
            stk.push(arr[i]);
        }
        return ans;
    } 
};
/*
Input: N = 5, arr[] = {3, 8, 5, 2, 25}
Output: 2 5 2 -1 -1
Explanation: 
1. Roll number 1 has 3 marks. The first person 
who has less marks than him is roll number 4, 
who has 2 marks.
2. Roll number 2 has 8 marks, he helps student 
with 5 marks.
3. Roll number 3 has 5 marks, he helps student 
with 2 marks.
4. Roll number 4 and 5 can not pick anyone as 
no student with higher roll number has lesser 
marks than them. This is denoted by -1.
Output shows the marks of the weaker student that 
each roll number helps in order. ie- 2,5,2,-1,-1
*/