//STACKS AND QUEUES
#include<bits/stdc++.h>
using namespace std;

//MONOTONIC STACK
/*      SMALLER                         GREATER       
PREV    0->N    (POP {X < TOP})         0->N     (POP {X > TOP})    
NEXT    N-1 -> 0(POP {X < TOP})         N-1 -> 0 (POP {X > TOP})        
*/


//LEARNING
class MyStack
{
private:
    int arr[1000];
    int top;
public:
    MyStack(){top=-1;}
    int pop();
    void push(int);
};
//162. IMPLEMENT STACK USING ARRAY                                         {T.C = O(1), S.C = O(1)}
//FIRST INCREASE TOP THEN PUSH ELEMENT
//PUSH(TOP++, ARR[TOP] = X), POP (TOP != -1 ? ARR[TOP], TOP--)
void MyStack :: push(int x)
{
    top++;
    arr[top] = x;
}
//Function to remove an item from top of the stack.
int MyStack :: pop()
{
    // return top == -1 ? -1 : arr[top--];
    if(top == -1){
        return -1;
    }else{
        int val = arr[top];
        top--;
        return val;
    }
}
/*
Example 1:
Input: 
push(2)
push(3)
pop()
push(4) 
pop()
Output: 3, 4
Explanation: 
push(2)    the stack will be {2}
push(3)    the stack will be {2 3}
pop()      poped element will be 3,
           the stack will be {2}
push(4)    the stack will be {2 4}
pop()      poped element will be 4

Example 2:
Input: 
pop()
push(4)
push(5)
pop()
Output: -1, 5
*/


class MyQueue {
private:
    int arr[100005];
    int front;
    int rear;

public :
    MyQueue(){front=0;rear=0;}
    void push(int);
    int pop();
};
//163. IMPLEMENT QUEUE USING ARRAY                               {T.C = O(1), S.C = O(1)}
//FIRST UPDATE REAR(PUSH ELEMENT) THEN REAR++
void MyQueue :: push(int x)
{
    arr[rear] = x;
    rear++;
}

//Function to pop an element from queue and return that element.
int MyQueue :: pop()
{
    if(front == rear){
        return -1;
    }else{
        int val = arr[front];
        front++;
        return val;
    }
}
/*
Example 1:
Input:
Q = 5
Queries = 1 2 1 3 2 1 4 2
Output: 2 3
Explanation:
In the first test case for query 
1 2 the queue will be {2}
1 3 the queue will be {2 3}
2   poped element will be 2 the 
    queue will be {3}
1 4 the queue will be {3 4}
2   poped element will be 3 

Example 2:
Input:
Q = 4
Queries = 1 3 2 2 1 4   
Output: 3 -1
Explanation:
In the second testcase for query 
1 3 the queue will be {3}
2   poped element will be 3 the
    queue will be empty
2   there is no element in the
    queue and hence -1
1 4 the queue will be {4}
*/


//164. IMPLEMENT STACK USING QUEUES                          {T.C = O(N), S.C = O(N)}
//USING 2 QUEUES (PUSH -> Q2.PUSH(X), Q1->Q2(TRANSFER), SWAP(Q1, Q2))
class MyStack {
public:
    queue<int>q1;
    queue<int>q2;
    MyStack() {}                          //useless
    
    void push(int x) {
        q2.push(x);                        //push ele (q1)
        while(!q1.empty()){                //pop all ele (q1->q2) sequence wise
            q2.push(q1.front());
            q1.pop();
        }
        swap(q1, q2);                      //swap both q
    }
    
    int pop() {
        int ele = q1.front();
        q1.pop();
        return ele;
    }
    
    int top() {
        return q1.front();
    }
    
    bool empty() {
        return q1.empty();
    }
};

//USING 1 QUEUE
//PUSH->POP(EXCEPT 1 ELEMENT) AGAIN PUSH TO Q
class MyStack {
public:
    queue<int>q;
    MyStack() {}                          //useless
    
    void push(int x) {
        q.push(x);
        for(int i = 0 ; i < q.size()-1; i++){       //keep only 1 ele other pop and push again
            q.push(q.front());
            q.pop();
        }
    }
    
    int pop() {
        int ele = q.front();
        q.pop();
        return ele;
    }
    
    int top() {
        return q.front();
    }
    
    bool empty() {
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


//165. IMPLEMENT QUEUE USING STACK                            {T.C = O(N), S.C = O(N)}
//USING 1 STACK (RECURSION)
class MyQueue {
public:
    stack<int>stk;
    MyQueue() {}                              //useless
    
    void push(int x) {
        //base case
        if(stk.empty()){
            stk.push(x);
            return;
        }
        int ele = stk.top();
        stk.pop();
        push(x);                         //recursion
        stk.push(ele);
    }
    
    int pop() {
        int ele = stk.top();
        stk.pop();
        return ele;
    }
    
    int peek() {
        return stk.top();
    }
    
    bool empty() {
        return stk.empty();
    }
};
/*
Example 1:
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


struct StackNode {
    int data;
    StackNode *next;
    StackNode(int a) {
        data = a;
        next = NULL;
    }
};
class MyStack {
  private:
    StackNode *top;
  public:
    void push(int);
    int pop();
    MyStack() { top = NULL; }
};
//166. IMPLIMENT STACK USING LINKED LIST                       {T.C = O(1), S.C = O(1)}
//IF NO NODE MAKE NEW NODE ELSE NEWNODE->TOP, TOP = NEWNODE
void MyStack::push(int x) 
{
    StackNode* newNode = new StackNode(x);
    if (!top) {
        top = newNode;
    } else {
        newNode->next = top;                                  //NEWNODE->TOP (REVERSE PUSH)
        top = newNode;
    }
}

//Function to remove an item from top of the stack.
int MyStack ::pop() 
{
    //base case
    if(!top){
        return -1;
    }
    int val = top->data;
    top = top->next;
    return val;
}
/*
Example 1:
Input: 
push(2)
push(3)
pop()
push(4) 
pop()
Output: 3 4
Explanation: 
push(2)    the stack will be {2}
push(3)    the stack will be {2 3}
pop()      poped element will be 3,
           the stack will be {2}
push(4)    the stack will be {2 4}
pop()      poped element will be 4

Example 2:
Input: 
pop()
push(4)
push(5)
pop()
Output: -1 5
*/


//Structure of a node in Queue
struct QueueNode
{
    int data;
    QueueNode *next;
    QueueNode(int a)
    {
        data = a;
        next = NULL;
    }
};
// And structure of MyQueue
struct MyQueue {
    QueueNode *front;
    QueueNode *rear;
    void push(int);
    int pop();
    MyQueue() {front = rear = NULL;}
};
//167. IMPLEMENT QUEUE USING LINKED LIST                    {T.C = O(1), S.C = O(1)}
//REAR->NEWNODE, REAR = NEWNODE
void MyQueue:: push(int x)
{
    QueueNode* newNode = new QueueNode(x);
    if(!front){
        front = newNode;
        rear = newNode;
    }else{
        rear->next = newNode;                            //REAR->NEWNODE (PUSH)
        rear = newNode;
    }
}

//Function to pop front element from the queue.
int MyQueue :: pop()
{
    //base case
    if(!front){
        return -1;
    }
    int val = front->data;
    front = front->next;
    return val;
}
/*
Example 1:
Input:
Q = 5
Queries = 1 2 1 3 2 1 4 2
Output: 2 3
Explanation: n the first testcase
1 2 the queue will be {2}
1 3 the queue will be {2 3}
2   poped element will be 2 the
    queue will be {3}
1 4 the queue will be {3 4}
2   poped element will be 3.

Example 2:
Input:
Q = 4
Queries = 1 2 2 2 1 3 
Output: 2 -1
Explanation: In the second testcase 
1 2 the queue will be {2}
2   poped element will be {2} then
    the queue will be empty. 
2   the queue is empty and hence -1
1 3 the queue will be {3}.
*/


//168. VALID PARENTHESIS                                 {T.C = O(N), S.C = O(N)}
//CHECK TOP AND CURR BRACKET
class Solution {
public:
    bool isValid(string s) {
        stack<int>st;
        for(auto ch : s){
            if(ch == '(' || ch == '{' || ch == '['){
                st.push(ch);
            }
            //check also is st is not empty otherwise run time error
            else if( !st.empty() && ( (ch == ')' && st.top() == '(' ) || (ch == '}' && st.top() == '{') || (ch == ']' && st.top() == '[') ) ){
                st.pop();
            }else{
                return false;
            }
        }
        return st.empty();
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
*/


//169. MIN STACK                                          {T.C = O(1), S.C = O(N)}
//USE 2 STACK(ORIGINAL, MINIMUM VAL STACK)
class MinStack {
public:
    stack<int>s, b;                      //s = stores original elements, b = stores minimum elements
    MinStack() {}                         //USELESS
    
    void push(int val) {
        s.push(val);
        if(!b.empty()){
            val = min(val, b.top());
        }
        b.push(val);
    }
    
    void pop() {                                     //for maintaining consistancy pop from both
        s.pop();
        b.pop();
    }
    
    int top() {
        return s.top();
    }
    
    int getMin() {
        return b.top();
    }
};
/*
Example 1:
Input
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]
Output
[null,null,null,null,-3,null,0,-2]
Explanation
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin(); // return -3
minStack.pop();
minStack.top();    // return 0
minStack.getMin(); // return -2
*/


//170. INFIX TO POSTFIX                                  {T.C = O(N), S.C = O(N)}
//CHAR->PUSH, ()-> TEMP PUSH IN STK, OPERATOR->PUSH ACCORDINGLY
class Solution {
  public:
    string infixToPostfix(string s) {
        stack<char>stk;
        
        auto precedence = [&](auto it){
            if(it == '+' || it == '-') return 1;
            else if(it == '*' || it == '/') return 2;
            else if(it == '^') return 3;
            else return 0;
        };
        
        string ans;
        for(auto it : s){
            /*
            if((it >= 'a' && it <= 'z') || (it >= 'A' && it <= 'Z') || (it >= '0' && it <= '9') ){
                ans.push_back(it);
            }
            */ 
            // if(isalpha(it) || isdigit(it)){
            if(isalnum(it)){
                ans.push_back(it);
            }else if(it == '('){
                stk.push(it);                           //temporary push
            }else if(it == ')'){
                while(!stk.empty() && stk.top() != '('){
                    ans.push_back(stk.top());
                    stk.pop();
                }
                stk.pop();                                 //remove () from final ans
            }else{      //operator ^*/+-
                while(!stk.empty() && precedence(stk.top()) >= precedence(it)){
                    ans.push_back(stk.top());
                    stk.pop();
                }
                stk.push(it);
            }
        }
        while(!stk.empty()){
            ans.push_back(stk.top());
            stk.pop();
        }
        
        return ans;
    }
};
/*
Example 1:
Input: str = "a+b*(c^d-e)^(f+g*h)-i"
Output: abcd^e-fgh*+^*+i-
Explanation:
After converting the infix expression 
into postfix expression, the resultant 
expression will be abcd^e-fgh*+^*+i-

Example 2:
Input: str = "A*(B+C)/D"
Output: ABC+*D/
Explanation:
After converting the infix expression 
into postfix expression, the resultant 
expression will be ABC+*D/
*/


//171. PREFIX TO INFIX                                 {T.C = O(N), S.C = O(N)}
//REVERSE TRAVERSE , STK(STRING)
class Solution {
  public:
    string preToInfix(string pre_exp) {
        stack<string>stk;
        string s = pre_exp;
        string ans = "";
        for(int i = s.length()-1 ; i >= 0 ; i--){
            if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/'){
                string op1 = stk.top();
                stk.pop();
                string op2 = stk.top();
                stk.pop();
                ans = '(' + op1 + s[i] + op2 + ')';
                stk.push(ans);
            }else{
                stk.push(string(1,s[i]));                   //push ch in string
            }
        }
        return stk.top();
    }
};

//USING STL(ISALNUM)
//ANS = '(' + OP1 + S[I] + OP2 + ')'
class Solution {
  public:
    string preToInfix(string pre_exp) {
        stack<string>stk;
        string s = pre_exp;
        string ans = "";
        for(int i = s.length()-1 ; i >= 0 ; i--){
            if(isalnum(s[i])){
                stk.push(string(1, s[i]));
            }else{                  //operator */+-
                string op1 = stk.top();
                stk.pop();
                string op2 = stk.top();
                stk.pop();
                ans = '(' + op1 + s[i] + op2 + ')';
                stk.push(ans);
            }
        }
        return stk.top();
    }
};
/*
Example 1:
Input: 
*-A/BC-/AKL
Output: 
((A-(B/C))*((A/K)-L))
Explanation: 
The above output is its valid infix form.
*/


//172. PREFIX TO POSTFIX                                {T.C = O(N), S.C = O(N)}
//ANS = OP1 + OP2 + S[I]
class Solution {
  public:
    string preToPost(string pre_exp) {
        stack<string>stk;
        string s = pre_exp;
        string ans = "";
        for(int i = s.length()-1 ; i >=  0 ; i--){
            if(isalnum(s[i])){
                stk.push(string(1, s[i]));
            }else{         //operators */+-
                string op1 = stk.top();
                stk.pop();
                string op2 = stk.top();
                stk.pop();
                ans = op1 + op2 + s[i];
                stk.push(ans);
            }
        }
        return stk.top();
    }
};
/*
Example:
Input: 
*-A/BC-/AKL
Output: 
ABC/-AK/L-*
Explanation: 
The above output is its valid postfix form.
*/


//173. POSTFIX TO PREFIX                                 {T.C = O(N), S.C = O(N)}
//REVERSE OF PRE-POST
//ANS = S[I] + OP2 + OP1
class Solution {
  public:
    string postToPre(string post_exp) {
        stack<string>stk;
        string s = post_exp;
        string ans = "";
        
        for(int i = 0 ; i < s.length() ; i++){
            if(isalnum(s[i])){
                stk.push(string(1, s[i]));
            }else{       //operator */+-
                string op1 = stk.top();
                stk.pop();
                string op2 = stk.top();
                stk.pop();
                ans = s[i] + op2 + op1;                 //reverse of prefix
                stk.push(ans);
            }
        }
        return stk.top();
    }
};
/*
Example 1:
Input: 
ABC/-AK/L-*
Output: 
*-A/BC-/AKL
Explanation: 
The above output is its valid prefix form.
*/


//174. POSTFIX TO INFIX CONVERSION                         {T.C = O(N), S.C = O(N)}
//ANS = '(' + OP2 + S[I] + OP1 + ')'
class Solution {
  public:
    string postToInfix(string exp) {
        stack<string>stk;
        string s = exp;
        // string ans = "";                          //gives TLE
        
        for(int i = 0 ; i < s.length() ; i++){
            if(isalnum(s[i])){
                stk.push(string(1, s[i]));
            }else{               //operators */+-
                string op1 = stk.top();
                stk.pop();
                string op2 = stk.top();
                stk.pop();
                /*
                ans = '(' + op2 + s[i] + op1 + ')';          //reveres of preToInf
                stk.push(ans);
                */
                stk.push('(' + op2 + s[i] + op1 + ')');
            }
        }
        
        return stk.top();
    }
};
/*
Example:
Input:
ab*c+ 
Output: 
((a*b)+c)
Explanation: 
The above output is its valid infix form.
*/


//175. INFIX TO PREFIX                                      {T.C = O(N), S.C = O(N)}
//REVERSE S, REPLACE ('(' <=> ')'), APPLY POST FIX , REVERSE (INFIX TO PREFIX)
class Solution {
  public:
    string infToPos(string &s){
        stack<char>stk;
        
        auto precedence = [&](auto it){
            if(it == '+' || it == '-') return 1;
            else if(it == '*' || it == '/') return 2;
            else if(it == '^') return 3;
            else return 0;
        };
        
        string ans;
        for(auto it : s){
            if(isalnum(it)){
                ans.push_back(it);
            }else if(it == '('){
                stk.push(it);                           //temporary push
            }else if(it == ')'){
                while(!stk.empty() && stk.top() != '('){
                    ans.push_back(stk.top());
                    stk.pop();
                }
                stk.pop();                                 //remove () from final ans
            }else{      //operator ^*/+-
                while(!stk.empty() && precedence(stk.top()) >= precedence(it)){
                    ans.push_back(stk.top());
                    stk.pop();
                }
                stk.push(it);
            }
        }
        while(!stk.empty()){
            ans.push_back(stk.top());
            stk.pop();
        }
        
        return ans;
    }

    string infixToPrefix(string s){
        reverse(s.begin(), s.end());
        for(int i = 0 ; i < s.length() ; i++){
            if(s[i] == '('){
                s[i] = ')';
            }else if(s[i] == ')'){
                s[i] = '(';
            }
        }
        
        string temp = infToPos(s);             
        reverse(temp.begin(), temp.end());          //infixToPrefix
        
        return temp;
    }
};
/*
Input: A * B + C / D
Output: + * A B/ C D 

Input: (A – B/C) * (A/K-L)
Output: *-A/BC-/AKL
*/


//MONOTONIC STACK/QUEUE PROBLEMS--------------------------------------------------------------------
//176. NEXT GREATER ELEMENT    (2 VECTORS BUT NOT CIRCULAR)          {T.C = O(N), S.C = O(N)}
//NGR (NEXT GREATER RIGHT)
//TRAVERSE LEFT <- RIGTH (VEC2) , TOP <= X ? POP : TEMP(TOP OR -1) , MP(X, TEMP) , TRAVERSE VEC1 SEARCH IN MP
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        unordered_map<int,int>mp;
        stack<int>stk;
        for(int i = m-1 ; i >= 0 ; i--){                         //traverse vec2 from last
            while(!stk.empty() && nums2[i] >= stk.top()){
                stk.pop();
            }
            int temp = stk.empty() ? -1 : stk.top();
            mp.insert({nums2[i], temp});                        //{curr, greater}
            stk.push(nums2[i]);                                 //x < stk.top()
        }

        vector<int>ans;                                        //extract greater for each ele in nums1
        for(auto it : nums1){
            ans.push_back(mp[it]);
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


//177. NEXT GREATER ELEMENT II        (CIRCULAR)                  {T.C = O(N), S.C = O(N)}
//NGR(NEXT GREATER RIGHT)
//SIMILAR TO ABOVE , I => I % N (CIRCULAR)
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int>ans(n);                     //initialize (other wise tle)
        stack<int>stk;
        for(int i = 2*n-1 ; i >= 0 ; i--){
            while(!stk.empty() && nums[i % n] >= stk.top()){
                stk.pop();
            }
            if(i < n){
                ans[i] = stk.empty() ? -1 : stk.top();
            }
            stk.push(nums[i % n]);
        }
        
        return ans;
    }
};
/*
Example 1:
Input: nums = [1,2,1]
Output: [2,-1,2]
Explanation: The first 1's next greater number is 2; 
The number 2 can't find next greater number. 
The second 1's next greater number needs to search circularly, which is also 2.

Example 2:
Input: nums = [1,2,3,4,3]
Output: [2,3,4,-1,4]
*/


//178. NEXT SMALLER ELEMENT                                {T.C = O(N), S.C = O(N)}
//NSL(NEXT SMALLER LEFT)
//NOT REVERSE TRAVERSAL, X <= STK.TOP() : STK.POP()
vector<int>prevSmaller(vector<int> &A) {
    int n = A.size();
    vector<int>ans(n);
    stack<int>stk;
    for(int i = 0 ;i < n ; i++){                       //not reverse traversal
        while(!stk.empty() && A[i] <= stk.top()){
            stk.pop();
        }
        ans[i] = stk.empty() ? -1 : stk.top();
        stk.push(A[i]);
    }
    return ans;
}
/*
Input 1:
    A = [4, 5, 2, 10, 8]
Output 1:
    G = [-1, 4, -1, 2, 2]
Explaination 1:
    index 1: No element less than 4 in left of 4, G[1] = -1
    index 2: A[1] is only element less than A[2], G[2] = A[1]
    index 3: No element less than 2 in left of 2, G[3] = -1
    index 4: A[3] is nearest element which is less than A[4], G[4] = A[3]
    index 4: A[3] is nearest element which is less than A[5], G[5] = A[3]
*/


//179. NUMBER OF NGES(NEXT GREATER ELEMENTS) ON THE RIGHT           {T.C = O(N*QUERIES), S.C = O(QUERIES)}
//TRAVERSE IN QUERIES, TRAVERSE OF ARR (J = INDICES[I]+1), CURR < ARR : COUNT++
class Solution{
public:
    vector<int> count_NGE(int n, vector<int> &arr, int queries, vector<int> &indices){
        vector<int>ans(queries);
        for(int i = 0 ; i < queries; i++){
            int count = 0;
            for(int j = indices[i] + 1 ; j < n ; j++){
                if(arr[indices[i]] < arr[j]){
                    count++;
                }
            }
            ans[i] = count;
        }
        
        return ans;
    }
};
/*
Input:  arr     = [3, 4, 2, 7, 5, 8, 10, 6]
        queries = 2
        indices = [0, 5]
Output:  6, 1
Explanation:  
The next greater elements to the right of 3(index 0)
are 4,7,5,8,10,6.  
The next greater elements to the right of 8(index 5)
is only 10.
*/


//180. TRAPPING RAIN WATER
//USING PREFIX AND SUFFIX SUM , ARRAY                            {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        vector<int>prefixSum(n), suffixSum(n);
        for(int i = 1 ; i < n ; i++){
            prefixSum[i] = max(prefixSum[i-1] , height[i-1]);
        }
        for(int i = n-2 ; i >= 0 ; i--){
            suffixSum[i] = max(suffixSum[i+1], height[i+1]);
        }
        int ans = 0;
        for(int i = 0 ; i < n ;i++){
            int waterLevel = min(prefixSum[i], suffixSum[i]);
            if(waterLevel >= height[i]){
                ans += waterLevel-height[i];
            }
        }
        return ans;
    }
};

//USING 2 POINTERS                                               {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int left = 0, right = n-1, leftMax = 0, rightMax = 0;
        int res = 0;
        while(left <= right){
            if(height[left] <= height[right]){
                if(height[left] > leftMax){
                    leftMax = height[left];
                }else{
                    res += leftMax - height[left];
                }
                left++;
            }else{
                if(height[right] > rightMax){
                    rightMax = height[right];
                }else{
                    res += rightMax - height[right];
                }
                right--;
            }
        }
        return res;
    }
};
/*
Example 1:
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.

Example 2:
Input: height = [4,2,0,3,2,5]
Output: 9
*/


//181. SUM OF SUBARRAY MINIMUM                            
//BRUTE FORCE , FIND ALL SUBARRAY , SUM MIN OF EACH              {T.C = O(N^2), S.C = O(1)}
class Solution {
public:
    int mod = 1e9+7;
    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
        long miniSum = 0;
        for(int i = 0 ; i <n ; i++){
            int val = arr[i];
            for(int j = i ; j < n ; j++){
                val = min(val, arr[j]);
                miniSum = (miniSum + val) % mod;
            }
        }
        return miniSum;
    }
};

//USING STACK (NSL{NEXT SMALLER LEFT}, NGR{NEXT GREATER RIGHT})   {T.C= O(N), S.C = O(N)}
class Solution {
public:
    int mod = 1e9+7;
    vector<int> nextSmallerLeft(vector<int>&arr){
        int n = arr.size();
        stack<int>stk;
        vector<int>ans(n);
        for(int i = 0 ; i < n ; i++){
            while(!stk.empty() && arr[i] <= arr[stk.top()]){    //= is only in one case nsl or ngr , arr[stk.top()] -> index
                stk.pop();
            }
            ans[i] = stk.empty() ? -1 : stk.top();
            stk.push(i);                               //pushing index not ele
        }
        return ans;
    }
    vector<int> nextGreaterRight(vector<int>&arr){
        int n = arr.size();
        stack<int>stk;
        vector<int>ans(n);
        for(int i = n-1 ; i >= 0 ; i--){
            while(!stk.empty() && arr[i] < arr[stk.top()]){
                stk.pop();
            }
            ans[i] = stk.empty() ? n : stk.top();           //empty(): push(n)
            stk.push(i);
        }
        return ans;
    }
    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
        long long sum = 0;
        vector<int>NSL = nextSmallerLeft(arr);
        vector<int>NGR = nextGreaterRight(arr);

        for(int i = 0 ; i < n ; i++){
            long long beforeCurr = i-NSL[i];
            long long afterCurr = NGR[i]-i;

            long long totalWays = beforeCurr*afterCurr;       //all smaller = arr[i]
            long long totalSum = arr[i]*totalWays;

            sum = (sum + totalSum) % mod;
        }

        return sum;
    }
};

//SAME AS ABOVE JUST VARIABLE NAME CHANGE 
class Solution {
public:
    int mod = 1e9+7;
    vector<int> prevSmaller(vector<int>&arr){
        int n = arr.size();
        stack<int>stk;
        vector<int>ans(n);
        for(int i = 0 ; i < n ; i++){
            while(!stk.empty() && arr[i] <= arr[stk.top()]){    //= is only in one case prevSm or nextSm , arr[stk.top()] -> index
                stk.pop();
            }
            ans[i] = stk.empty() ? -1 : stk.top();
            stk.push(i);                               //pushing index not ele
        }
        return ans;
    }
    vector<int> nextSmaller(vector<int>&arr){
        int n = arr.size();
        stack<int>stk;
        vector<int>ans(n);
        for(int i = n-1 ; i >= 0 ; i--){
            while(!stk.empty() && arr[i] < arr[stk.top()]){
                stk.pop();
            }
            ans[i] = stk.empty() ? n : stk.top();           //empty(): push(n)
            stk.push(i);
        }
        return ans;
    }
    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
        long long sum = 0;
        vector<int>prevSm = prevSmaller(arr);
        vector<int>nextSm = nextSmaller(arr);

        for(int i = 0 ; i < n ; i++){
            long long beforeCurr = i-prevSm[i];
            long long afterCurr = nextSm[i]-i;

            long long totalWays = beforeCurr*afterCurr;       //all smaller = arr[i]
            long long totalSum = arr[i]*totalWays;

            sum = (sum + totalSum) % mod;
        }

        return sum;
    }
};
/*
Example 1:
Input: arr = [3,1,2,4]
Output: 17
Explanation: 
Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4]. 
Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.
Sum is 17.

Example 2:
Input: arr = [11,81,94,43,3]
Output: 444
*/


//182. ASTEROIDS COLLISIONS                               {T.C = O(N), S.C = O(N)}
//CURR > STK.TOP ? STK.POP(DESTROYED) : IT = 0 (CURR {DESTROYED})
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int>ans;
        stack<int>stk;

        for(auto it : asteroids){
            while(!stk.empty() && it < 0 && stk.top() > 0){
                int sum = it + stk.top();
                if(sum < 0){               //incoming asteroid is big
                    stk.pop();             //stk's asteroid destroyed
                }else if(sum > 0){         //stack's asteroid is big
                    it = 0;                //incoming asteroid is destroid
                }else{ //sum == 0          //both asteroids destroyed
                    stk.pop();
                    it = 0;
                }
            }
            if(it != 0){
                stk.push(it);
            }
        }

        while(!stk.empty()){
            ans.push_back(stk.top());
            stk.pop();
        }
        reverse (ans.begin(), ans.end());

        return ans;
    }
};
/*
Example 1:
Input: asteroids = [5,10,-5]
Output: [5,10]
Explanation: The 10 and -5 collide resulting in 10. The 5 and 10 never collide.

Example 2:
Input: asteroids = [8,-8]
Output: []
Explanation: The 8 and -8 collide exploding each other.

Example 3:
Input: asteroids = [10,2,-5]
Output: [10]
Explanation: The 2 and -5 collide resulting in -5. The 10 and -5 collide resulting in 10.
*/


//183. SUM OF SUBARRAY RANGES
//BRUTE FORCE USING 2 LOOPS(FIND ALL SUBARRAYS , MAX-MIN)               {T.C = O(N^2), S.C = O(1)}
//SIMILAR TO 181
#include<algorithm>
class Solution {
public:
    long long subArrayRanges(vector<int>& nums) {
        int  n = nums.size();
        long long sum = 0;
        for(int i = 0 ;i < n ; i++){
            int maxi = nums[i];
            int mini = nums[i];
            for(int j = i ; j < n ; j++){
                maxi = max(maxi, nums[j]);
                mini = min(mini, nums[j]);

                sum += maxi - mini;
            }
        }
        return sum;
    }
};

//USING STACK                                              {T.C = O(N), S.C = O(N)}
//(sumSubarrayMax{prevGreater, nextGreater} - sumSubarrayMin {prevSmaller, nextSmaller})
class Solution {
public:
        vector<int> prevSmaller(vector<int>&arr){
        int n = arr.size();
        stack<int>stk;
        vector<int>ans(n);
        for(int i = 0 ; i < n ; i++){
            while(!stk.empty() && arr[i] <= arr[stk.top()]){    //= is only in one case prevSm or nextSm , arr[stk.top()] -> index
                stk.pop();
            }
            ans[i] = stk.empty() ? -1 : stk.top();
            stk.push(i);                               //pushing index not ele
        }
        return ans;
    }
    vector<int> nextSmaller(vector<int>&arr){
        int n = arr.size();
        stack<int>stk;
        vector<int>ans(n);
        for(int i = n-1 ; i >= 0 ; i--){
            while(!stk.empty() && arr[i] < arr[stk.top()]){
                stk.pop();
            }
            ans[i] = stk.empty() ? n : stk.top();           //empty(): push(n)
            stk.push(i);
        }
        return ans;
    }
    long long sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
        long long sum = 0;
        vector<int>prevSm = prevSmaller(arr);
        vector<int>nextSm = nextSmaller(arr);

        for(int i = 0 ; i < n ; i++){
            long long beforeCurr = i-prevSm[i];
            long long afterCurr = nextSm[i]-i;

            long long totalWays = beforeCurr*afterCurr;       //all smaller = arr[i]
            long long totalSum = arr[i]*totalWays;

            // sum = (sum + totalSum) % mod;
            sum = sum + totalSum;

        }
        return sum;
    }

    //------------------------------------------------------------------
    vector<int> prevGreater(vector<int>&arr){
        int n = arr.size();
        stack<int>stk;
        vector<int>ans(n);
        for(int i = 0 ; i < n ; i++){
            while(!stk.empty() && arr[i] >= arr[stk.top()]){    //= is only in one case prevSm or nextSm(duplicate) , arr[stk.top()] -> index
                stk.pop();
            }
            ans[i] = stk.empty() ? -1 : stk.top();
            stk.push(i);                               //pushing index not ele
        }
        return ans;
    }
    vector<int> nextGreater(vector<int>&arr){
        int n = arr.size();
        stack<int>stk;
        vector<int>ans(n);
        for(int i = n-1 ; i >= 0 ; i--){
            while(!stk.empty() && arr[i] > arr[stk.top()]){
                stk.pop();
            }
            ans[i] = stk.empty() ? n : stk.top();           //empty(): push(n)
            stk.push(i);
        }
        return ans;
    }
    long long sumSubarrayMaxs(vector<int>& arr) {
        int n = arr.size();
        long long sum = 0;
        vector<int>prevGr = prevGreater(arr);
        vector<int>nextGr = nextGreater(arr);

        for(int i = 0 ; i < n ; i++){
            long long beforeCurr = i-prevGr[i];
            long long afterCurr = nextGr[i]-i;

            long long totalWays = beforeCurr*afterCurr;       //all smaller = arr[i]
            long long totalSum = arr[i]*totalWays;

            // sum = (sum + totalSum) % mod;
            sum = sum + totalSum;
        }

        return sum;
    }
    long long subArrayRanges(vector<int>& nums) {
        return sumSubarrayMaxs(nums) - sumSubarrayMins(nums);
    }
};
/*
Example 1:
Input: nums = [1,2,3]
Output: 4
Explanation: The 6 subarrays of nums are the following:
[1], range = largest - smallest = 1 - 1 = 0 
[2], range = 2 - 2 = 0
[3], range = 3 - 3 = 0
[1,2], range = 2 - 1 = 1
[2,3], range = 3 - 2 = 1
[1,2,3], range = 3 - 1 = 2
So the sum of all ranges is 0 + 0 + 0 + 1 + 1 + 2 = 4.

Example 2:
Input: nums = [1,3,3]
Output: 4
Explanation: The 6 subarrays of nums are the following:
[1], range = largest - smallest = 1 - 1 = 0
[3], range = 3 - 3 = 0
[3], range = 3 - 3 = 0
[1,3], range = 3 - 1 = 2
[3,3], range = 3 - 3 = 0
[1,3,3], range = 3 - 1 = 2
So the sum of all ranges is 0 + 0 + 0 + 2 + 0 + 2 = 4.
*/


//184. REMOVE K DIGITS                                           {T.C = O(N), S.C = O(N)}
//MONOTONIC (INCREASING STACK), TOP > X : POP & K-- : PUSH , REMOVE PREV 0, ALREADY INCREASEIN REMOVE TOP(K--)
class Solution {
public:
    string removeKdigits(string num, int k) {
        int n = num.length();
        if(k == n){
            return "0";
        }
        stack<char>stk;
        string ans = "";
        for(int i = 0 ; i < n ; i++){
            while(!stk.empty() && stk.top() > num[i] && k > 0){
                stk.pop();
                k--;
            }
            stk.push(num[i]);
            if(stk.size() == 1 && stk.top() == '0'){        //prev 0 remove
                stk.pop();
            }
        }
        while(k > 0 && !stk.empty()){                //1234 or 1111 (increasing order already)
            stk.pop();
            k--;
        }
        while(!stk.empty()){
            ans.push_back(stk.top());
            stk.pop();
        }
        if(ans == ""){
            return "0";
        }else{
            reverse(ans.begin(), ans.end());
        }
        return ans;
    }
};
/*
Example 1:
Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.

Example 2:
Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.

Example 3:
Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing which is 0.
*/


//185. LARGEST RECTANGLE IN A HISTOGRAM                              {T.C = O(N), S.C = O(N)}
//AREA = LENGHT(HEIGHT) * WIDHT(PREVSMALLER, NEXTSMALLER)
class Solution {
private:
    vector<int> prevSmaller(vector<int> arr, int n) {
        stack<int> stk;
        vector<int> ans(n);
        for(int i = 0; i < n; i++) {
            while(!stk.empty() && arr[i] <= arr[stk.top()]) {
                stk.pop();
            }
            ans[i] = stk.empty() ? -1 : stk.top();
            stk.push(i);
        }
        return ans;
    }

    
    vector<int> nextSmaller(vector<int> arr, int n) {
        stack<int> stk;
        vector<int> ans(n);
        for(int i = n-1; i >= 0; i--) {
            while(!stk.empty() && arr[i] <= arr[stk.top()]) {
                stk.pop();
            }
            ans[i] = stk.empty() ? n : stk.top();
            stk.push(i);
        }
        return ans;
    }
    
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int> next = nextSmaller(heights, n);
        vector<int> prev = prevSmaller(heights, n);
        
        int maxArea = 0;                        // Initial area should be 0
        for(int i = 0; i < n; i++) {
            //l = heights[i] ; w = next[i]-prev[i]-1, (exclude boundary)
            maxArea = max(maxArea, (heights[i]*(next[i] - prev[i] - 1)));   
        }
        return maxArea;
    }
};
/*
Example 1:
Input: heights = [2,1,5,6,2,3]
Output: 10
Explanation: The above is a histogram where width of each bar is 1.
The largest rectangle is shown in the red area, which has an area = 10 units.

Example 2:
Input: heights = [2,4]
Output: 4
*/


//186. MAXIMAL RECTANGLE                                {T.C = O(N*M), S.C = O(M)}
//FIRST FIND AREA ROW WISE(HISTOGRAM{LIKE ABOVE}), THEN TRAVERSE MATRIX (1 H++, 0 H=0)
class Solution {
public:
    vector<int>prevSmaller(vector<int>arr , int n){
        stack<int>stk;
        vector<int>ans(n);
        for(int i = 0 ; i < n ; i++){
            while(!stk.empty() && arr[i] <= arr[stk.top()]){
                stk.pop();
            }
            ans[i] = stk.empty() ? -1 : stk.top();
            stk.push(i);
        }
        return ans;
    }
    vector<int>nextSmaller(vector<int>arr , int n){
        stack<int>stk;
        vector<int>ans(n);

        for(int i = n-1 ; i >= 0 ; i--){
            while(!stk.empty() && arr[i] <= arr[stk.top()]){
                stk.pop();
            }
            ans[i] = stk.empty() ? n : stk.top();
            stk.push(i);
        }
        return ans;
    }

    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int>next = nextSmaller(heights, n);
        vector<int>prev = prevSmaller(heights, n);
        int maxArea = 0;
        for(int i = 0 ; i < n ; i++){
            //l = heights[i], b = (next[i]-prev[i]-1)
            maxArea = max(maxArea, heights[i]*(next[i]-prev[i]-1));
        }
        return maxArea;
    }
    int maximalRectangle(vector<vector<char>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        int maxi = 0;
        vector<int>histogram(m, 0);                   //height (initially all h=0)

        for(int i =  0 ; i < n ; i++){
            //to create histogram array
            for(int j = 0 ; j < m ; j++){
                if(matrix[i][j] == '1'){
                    histogram[j]++;                  //increasing height
                }
                else{
                    histogram[j] = 0;                //reset heigth to 0
                }
            }
            maxi = max(maxi, largestRectangleArea(histogram));
        }
        return maxi;
    }
};
/*
Example 1:


Input: matrix = [["1","0","1","0","0"],
                 ["1","0","1","1","1"],
                 ["1","1","1","1","1"],
                 ["1","0","0","1","0"]]
Output: 6
Explanation: The maximal rectangle is shown in the above picture.

Example 2:
Input: matrix = [["0"]]
Output: 0

Example 3:
Input: matrix = [["1"]]
Output: 1
*/


//IMPLEMENTATION PROBLEMS -----------------------------------------------------------------------------------
//187. SLIDING WINDOW MAXIMUM
//BRUTE FOREC (TRAVERSE ALL ONCE (TILL VALID SUBARR{N-K}),            {T.C = O(N^2), S.C = O(N)}
//THEN CHECK EACH SUBARRAY(I+K) FIND MAX)
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int>ans;
        for(int i = 0 ; i <= n-k ; i++){       //final subarray (n-k)
            int maxi = nums[i];
            for(int j = i ; j < i+k ; j++){    //each subarray (i+k)
                maxi = max(maxi, nums[j]);
            }
            ans.push_back(maxi);
        }
        return ans;
    }
};

//USING MONOTONIC QUEUE(DECREASING)                        {T.C = O(N), S.C = O(N)}
//add & remove both ends of window
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int>ans;
        deque<int>dq;                        //store ans in decreasing order
        //for first window
        for(int i = 0 ; i < k ; i++){
            while(!dq.empty() && nums[i] > dq.back()){  //remove prev smaller
                dq.pop_back();
            }
            dq.push_back(nums[i]);
        }
        ans.push_back(dq.front());
        //for all next windows
        for(int i = k ; i < n ; i++){
            //remove previous element
            if(dq.front() == nums[i-k]){
                dq.pop_front();
            }

            //same as above
            while(!dq.empty() && dq.back() < nums[i]){
                dq.pop_back();
            }
            dq.push_back(nums[i]);
            ans.push_back(dq.front());                  //push all top elements
        }
        return ans;
    }
};
/*
Example 1:
Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation: 
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

Example 2:
Input: nums = [1], k = 1
Output: [1]
*/


//188. ONLINE STOCK SPAN                                {T.C = O(N), S.C = O(N)}
//SPAN(CURRCOUNT + PREV SMALLERCOUNT), TOP < X : SPAN++
class StockSpanner {
public:
    stack<pair<int, int>>stk;
    StockSpanner() {}                 //useless
    
    int next(int price) {
        int span = 1;                   //current span(minimum value before curr+itself) is 1 
        while(!stk.empty() && stk.top().first <= price){
            span += stk.top().second;
            stk.pop();
        }
        stk.push({price, span});
        return span;
    }
};
/*
Example 1:

Input
["StockSpanner", "next", "next", "next", "next", "next", "next", "next"]
[[], [100], [80], [60], [70], [60], [75], [85]]
Output
[null, 1, 1, 1, 2, 1, 4, 6]
Explanation
StockSpanner stockSpanner = new StockSpanner();
stockSpanner.next(100); // return 1
stockSpanner.next(80);  // return 1
stockSpanner.next(60);  // return 1
stockSpanner.next(70);  // return 2
stockSpanner.next(60);  // return 1
stockSpanner.next(75);  // return 4, because the last 4 prices (including today's price of 75) were less than or equal to today's price.
*/


//189. FIND CELEBRITY PROBLEM
//BRUTE FORCE                                                {T.C = O(N^2), S.C = O(1)}
class Solution {
    public:
    //Function to find if there is a celebrity in the party or not.
    int celebrity(vector<vector<int> >& M, int n) 
    {
        for(int i = 0 ; i < n ; i++){
            bool isCelebrity = true;
            for(int j = 0 ; j < n ; j++){
                if(i != j){
                    if(M[i][j] == 1 || M[j][i] == 0){ //i knows j or j not know i
                        isCelebrity = false;
                        break;
                    }
                }
            }
            if(isCelebrity == true){
                return i;
            }
        }
        return -1;
    }
};

//USING STACK                                                 {T.C = O(N), S.C = O(N)}
//PUSH ALL IN STACK, POP 2 AND COMPARE THEM, CHECK ROW(ALL 0), CHECK COL(ALL 1{EXCEPT DIAGONAL})
class Solution 
{
    private:
    bool knows(vector<vector<int> >& M,int a , int b, int n){
        return M[a][b] == 1 ? true : false;
    }
    
    public:
    int celebrity(vector<vector<int> >& M, int n) 
    {
        stack<int>s;
        
        //put all elements in stack
        for(int i = 0 ; i < n ; i++){
            s.push(i);
        }
        
        //get 2 person and compare them
        while(s.size() > 1){
            int a = s.top();
            s.pop();
            
            int b = s.top();
            s.pop();
            
            if(knows(M,a,b,n)){           //a knows b , so a is not celebrity
                s.push(b);
            }
            else{                        //b knows a , so b is not celebrity
                s.push(a);
            }
        }
        
        //(potential candidate left) single element left verify it , as a celebraty 
        int validCandidate = s.top();
        
        //all rows element = 0
        int zeroCount = 0;
        for(int i = 0 ; i < n ; i++){
            if(M[validCandidate][i] == 0){            //checking row
                zeroCount++;
            }
        }
        //all zero
        if(zeroCount != n){
            return -1;
        }

        //all cols element = 1 except diagonal
        int oneCount = 0;
        for(int i = 0 ; i < n ; i++){
            if(M[i][validCandidate] == 1){             //checking col
                oneCount++;
            }
        }
        //all one except diagonal
        if(oneCount != n-1 ){           //except digonal all 1
            return -1;
        }
        
        return validCandidate;
    }
};
/*
Example 1:
Input:
N = 3
M[][] = {{0 1 0},
         {0 0 0}, 
         {0 1 0}}
Output: 1
Explanation: 0th and 2nd person both
know 1. Therefore, 1 is the celebrity. 

Example 2:

Input:
N = 2
M[][] = {{0 1},
         {1 0}}
Output: -1
Explanation: The two people at the party both
know each other. None of them is a celebrity.
*/


//190. LRU CACHE
//BRUTE FORCE                                               {T.C = O(N^2), S.C = O(N)}
class LRUCache {
public:
    vector<pair<int,int>>cache;             //{key, value}
    int n;
    LRUCache(int capacity) {
        n = capacity;
    }
    
    int get(int key) {
        for(int i = 0 ;i < cache.size() ; i++){
            if(cache[i].first == key){              //found in vec
                int val = cache[i].second;
                pair<int,int>temp = cache[i];       //temp store data (for remove)
                cache.erase(cache.begin() + i);  //remove (front)
                cache.push_back(temp);              //push (back)
                
                return val;
            }
        }
        return -1;
    }
    
    void put(int key, int value) {
        for(int i = 0 ; i < cache.size() ; i++){     //search ,already present
            if(cache[i].first == key){
                cache.erase(cache.begin() + i);
                cache.push_back({key, value});
                return;
            }
        }

        if(cache.size() == n){
            cache.erase(cache.begin());            //erase least recent used
            cache.push_back({key, value});
        }else{
            cache.push_back({key, value});
        }
    }
};


//OPTIMIZED APPROACH {DOUBLLY LINKED LIST}                        {T.C = O(1), S.C = O(1)}
class LRUCache {
public:
    class Node{
        public:
        int key;
        int val;
        Node* prev;
        Node* next;
        
        Node(int key, int val){
            this->key = key;
            this->val = val;
        }
    };

    Node* head = new Node(-1, -1);
    Node* tail = new Node(-1, -1);

    int cap;
    unordered_map<int, Node*>mp;

    LRUCache(int capacity) {
        cap = capacity;
        head->next = tail;
        tail->prev = head;
    }
    
    void deleteNode(Node* delNode){
        Node* delPrev = delNode->prev;
        Node* delNext = delNode->next;

        delPrev->next = delNext;
        delNext->prev = delPrev;
    }

    void addNode(Node* newNode){
        Node* temp = head->next;
        newNode->next = temp;
        newNode->prev = head;

        head->next = newNode;
        temp->prev = newNode;
    }
    int get(int key) {
        if(mp.find(key) != mp.end()){
            Node* ansNode = mp[key];
            int ans = ansNode->val;

            mp.erase(key);
            deleteNode(ansNode);
            addNode(ansNode);

            mp[key] = head->next;
            return ans;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if(mp.find(key) != mp.end()){
            Node* curr = mp[key];
            mp.erase(key);
            deleteNode(curr);
        }
        if(mp.size() == cap){
            mp.erase(tail->prev->key);
            deleteNode(tail->prev);
        }
        addNode(new Node(key, value));
        mp[key] = head->next;
    }
};
/*
Example 1:

Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]
Explanation
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4
*/


//191. LFU CACHE                                           {T.C = O(1), S.C = O(N)}
//COPIED (CODEWITHMIK)
class LFUCache {
private:
    int cap;
    int size;
    unordered_map<int, list<vector<int>>::iterator> mp; //key -> address of list of vector{key, value, freq}
    map<int, list<vector<int>>> freq; //freq -> list of vector{key, value, freq}
    
public:
    LFUCache(int capacity) {
        cap = capacity;
        size = 0;
    }
    
    void makeMostFrequentlyUsed(int key) {
        auto &vec = *(mp[key]);
        
        int value = vec[1];
        
        int f     = vec[2];
        
        freq[f].erase(mp[key]);
        
        if(freq[f].empty())
            freq.erase(f);
        
        f++;
        
        freq[f].push_front(vector<int>({key, value, f}));
        
        mp[key] = freq[f].begin();
    }
    
    int get(int key) {
        if(mp.find(key) == mp.end())
            return -1;
        
        auto &vec = (*(mp[key]));
        
        int value = vec[1];
        
        makeMostFrequentlyUsed(key);
        
        return value;
    }
    
    void put(int key, int value) {
        if(cap == 0)
            return;
        
        if(mp.find(key) != mp.end()) {
            auto &vec = (*(mp[key]));
            vec[1] = value;
            makeMostFrequentlyUsed(key);
        }
        else if(size < cap) {
            size++;
            freq[1].push_front(vector<int>({key, value, 1}));
            mp[key] = freq[1].begin();
        }
        else { //Time to remove LFU or LRU if tie
            
            auto &kaun_sa_list = freq.begin()->second;
            
            int key_delete = (kaun_sa_list.back())[0]; //ordered_map ensures that the begin() will be th eleast frequency
            
            kaun_sa_list.pop_back();
            
            if(kaun_sa_list.empty())
                freq.erase(freq.begin()->first);
            
            freq[1].push_front(vector<int>({key, value, 1}));
            
            mp.erase(key_delete);
            mp[key] = freq[1].begin();
        }
    }
};
/*
Example 1:

Input
["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, 3, null, -1, 3, 4]

Explanation
// cnt(x) = the use counter for key x
// cache=[] will show the last used order for tiebreakers (leftmost element is  most recent)
LFUCache lfu = new LFUCache(2);
lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
lfu.get(1);      // return 1
                 // cache=[1,2], cnt(2)=1, cnt(1)=2
lfu.put(3, 3);   // 2 is the LFU key because cnt(2)=1 is the smallest, invalidate 2.
                 // cache=[3,1], cnt(3)=1, cnt(1)=2
lfu.get(2);      // return -1 (not found)
lfu.get(3);      // return 3
                 // cache=[3,1], cnt(3)=2, cnt(1)=2
lfu.put(4, 4);   // Both 1 and 3 have the same cnt, but 1 is LRU, invalidate 1.
                 // cache=[4,3], cnt(4)=1, cnt(3)=2
lfu.get(1);      // return -1 (not found)
lfu.get(3);      // return 3
                 // cache=[3,4], cnt(4)=1, cnt(3)=3
lfu.get(4);      // return 4
                 // cache=[4,3], cnt(4)=2, cnt(3)=3
*/


/*-------------------------------------THE END ----------------------------------------------------*/