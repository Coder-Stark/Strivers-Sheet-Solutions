//LEARN THE BASICS

#include<bits/stdc++.h>
using namespace std;


//THINGS TO KNOW IN C++
//01. USER INPUT / OUTPUT                                   {T.C = O(1), S.C = O(1)}
//INPUT(CIN) & OUTPUT(COUT)
int main() {
    int x;
    int y;
    cout<<"Enter the value of x : ";
    cin >> x;
    cout<<"Enter the value of y : ";
    cin >> y;
    cout << "Value of x: " << x << " and Value of y : "<< y;
    return 0;
}

//02. DATA TYPES                                            {T.C = O(1), S.C = O(1)}
//SIMPLE MATCH VALUE
class Solution {
  public:
    int dataTypeSize(string str) {
        if(str == "Character"){
            return 1;
        }else if(str == "Integer"){
            return 4;
        }else if(str == "Float"){
            return 4;
        }else if(str == "Long"){
            return 8;
        }else if(str == "Double"){
            return 8;
        }
    }
};
/*
Example 1:
Input: Character
Output: 1

Example 2:
Input: Integer
Output: 4
*/


//03. IF-ELSE (DECISION MAKING)                                                  {T.C = O(1), S.C = O(1)}
//SIMPLE RETURN ACCORDING TO CONDITION
class Solution {
  public:
    string compareNM(int n, int m){
        if(n < m){
            return "lesser";
        }else if(n == m){
            return "equal";
        }else{
            return "greater";
        }
    }
};
/*
Example 1:
Input:
n = 4
m = 8
Output: lesser
Explanation:
4 < 8 so print 'lesser'.

Example 2:
Input:
n = 8
m = 8
Output: equal
Explanation:
8 = 8 so print 'equal'.
*/


//04. SWITCH CASE STATEMENT                                  {T.C = O(1), S.C = O(1)}
//M_PI(pi stl) use switch case
class Solution {
  public:
    double switchCase(int choice, vector<double> &arr) {
        switch(choice){
            case 1:
                return M_PI*arr[0]*arr[0];
            case 2:
                return arr[0]*arr[1];
        }
    }
};
/*
Example 1:
Input: 
choice = 1, 
R = 5
Output: 78.53981633974483
Explaination: The choice is 1. 
So we have to calculate the area of the circle.

Example 2:
Input: 
choice = 2, 
L = 5, B = 10
Output: 50
Explaination: Here we have to calculate the 
area of the rectangle.
*/


//05. ARRAY / STRINGS
//THEORY + VIDEO


//06. FOR LOOP PRIME CHECK                                            {T.C = O(N), S.C = O(1)}
//IF SQRT OF N % I RETURN NO : YES
class Solution {
  public:
    string isPrime(int n) {
        for (int i = 2; i <= sqrt(n); i++) {
            if(n % i == 0){
                return "No";
            }
        }
        if(n == 0 || n == 1){
            return "No";
        }
        return "Yes";
    }
};
/*
Example 1:
Input:
n = 1
Output:No
Explanation: it is already said that 1 is not a prime number.

Example 2:
Input:
n = 2
Output:Yes
Explanation: 2 is a prime number because it is only divisible by itself and 1.
*/


//07. WHILE LOOP-PRINTABLE                                            {T.C = O(N), S.C = O(1)}
//M*N , M--
class Solution{
    public:
    void printTable(int n)
    {
        int multiplier=10;
        while(multiplier)
        {
           cout<<multiplier*n<<" ";
           multiplier--;
        }
        
        cout<<endl;
    }  
};
/*
Example 1:
Input: n = 1
Output: 10 9 8 7 6 5 4 3 2 1

Example 2:
Input: n = 2
Output: 20 18 16 14 12 10 8 6 4 2
*/


//08. PASS BY REFERENCE AND VALUE                         {T.C = O(1), S.C = O(1)}
//SIMPLE RETURN 
class Solution {
  public:
    vector<int> passedBy(int a, int &b) {
        return {a+1, b+2};
    }
};
/*
Example 1:
Input:
a = 1
b = 2
Output:
2 4
Explanation: 1 was passed by value whereas 2 passed by reference.

Example 2:
Input:
a = 10
b = 20
Output: 11 22
Explanation: 10 was passed by value whereas 20 passed by reference.
*/


//09. TIME AND SPACE COMPLEXITY
//THEORY + VIDEO


//BUILD UP LOGICAL THINKING--------------------------------------------------------------------------
//10. PATTERNS
//************************************************************************************************** */
//01. N-FOREST                                                    {T.C = O(N^2), S.C = O(1)}
void nForest(int n) {
  	for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout<<"*"<<" ";
        }
		cout<<endl;
    }
}
/*
Example:
Input: ‘N’ = 3
Output: 
* * *
* * *
* * *
*/


//02. N/2-FOREST                                                 {T.C = O(N^2), S.C = O(1)}
void nForest(int n) {
	for(int i = 0 ; i < n ; i++){
		for(int j = 0 ; j <= i ; j++){
			cout<<"*"<<" ";
		}
		cout<<endl;
	}
}
/*
Example:
Input:  ‘N’ = 3

Output: 
* 
* *
* * *
*/


//03. N-TRIANGLES                                              {T.C = O(N^2), S.C = O(1)}
void nTriangle(int n) {
	for(int i = 1 ; i <= n ; i++){
		for(int j = 1 ; j <= i ; j++){
			cout<<j<<" ";
		}
		cout<<endl;
	}
}
/*
Example:
Input: ‘N’ = 3
Output: 
1
1 2 
1 2 3
*/


//04. TRIANGLE                                                 {T.C = O(N^2), S.C = O(1)}
void triangle(int n) {
	for(int i = 1 ; i <= n ;i++){
		for(int j = 1 ; j <= i ; j++){
			cout<<i<<" ";
		}
		cout<<endl;
	}
}
/*
Example:
Input: ‘N’ = 3
Output: 
1
2 2 
3 3 3
*/


//05. SEEDING                                                  {T.C = O(N^2), S.C = O(1)}
void seeding(int n) {
	for(int i = 0 ; i < n ; i++){
		for(int j = i ;j < n ; j++){
			cout<<"*"<<" ";
		}
		cout<<endl;
	}
}
/*
Example:
Input: ‘N’ = 3
Output: 
* * *
* *
*
*/


//06. REVERSE NUMBER TRIANGLE                                       {T.C = O(N^2), S.C = O(1)}
void nNumberTriangle(int n) {
    for(int i = 1 ; i <= n ;i++){
        for(int j = 1 ; j <= n-i+1 ; j++){
            cout<<j<<" ";
        }
        cout<<endl;
    }
}
/*
Example:
Input: ‘N’ = 3
Output: 
1 2 3
1 2
1
*/


//07. STAR TRIANGLE                                                 {T.C = O(N^2), S.C = O(1)}
void nStarTriangle(int n) {
    for(int i = 0 ; i < n ; i++){
        //print spaces(before stars)
        for(int j = 0 ; j < n-i-1 ; j++){
            cout<<" ";
        }
        //print star
        for(int j = 0 ; j < 2*i+1 ; j++){
            cout<<"*";
        }
        //print space(after stars)
        for(int j = 0 ; j < n-i-1 ; j++){
            cout<<" ";
        }
        cout<<endl;
    }
}
/*
Input: ‘N’ = 3

Output: 

  *
 ***
*****
*/


//08. REVERSE STAR TRIANGLE                                   {T.C = O(N^2), S.C = O(1)}
void nStarTriangle(int n) {
    for(int i = 0 ; i < n ; i++){
        //print spaces(before star) 
        for(int j = 0 ; j < i ; j++){
            cout<<" ";
        }
        //print star
        for(int j = 0 ; j < 2*n-(2*i + 1) ; j++){
            cout<<"*";
        }
        //print spaces (after star){
        for(int j = 0 ; j < i ; j++){
            cout<<" ";
        }
        cout<<endl;
    }
}
/*
Example:
Input: ‘N’ = 3
Output: 
*****
 ***
  *
*/

/****************************************************************************************************** */


//LEAR STL--------------------------------------------------------------------------------------------
//11. C++ STL
//THEORY + VIDEO


//12. JAVA COLLECTIONS
//NOT REQUIRED


//KNOW BASIC MATHS-----------------------------------------------------------------------------------
//13. COUNT DIGITS                                       {T.C = O(LOGN), S.C = O(1)}
//STORE N, EXTRACT DIGIT(N % 10), CHECK IT DIVIDES N : COUNT++ , N = N/10(REMOVE NEXT DIGIT)
class Solution{
public:
    int evenlyDivides(int N){
        int count = 0;
        int currNum = N;
        while(N){
            int digit = N % 10;               //extract single digit (last)
            if(digit != 0 && currNum % digit == 0){
                count++;
            }
            N /= 10;                          //move next digit (backward)
        }
        return count;
    }
};
/*
Example 1:
Input:
N = 12
Output:
2
Explanation:
1, 2 both divide 12 evenly

Example 2:
Input:
N = 23
Output
0
Explanation:
2 and 3, none of them
divide 23 evenly
*/


//14. REVERSE INTEGER                                    {T.C = O(LOGN), S.C = O(1)}
//ANS = (ANS*10) + DIGIT(X % 10)
class Solution {
public:
    int reverse(int x) {
        int ans = 0;
        while(x){
            int digit = x % 10;
            if(ans > INT_MAX/10 || ans < INT_MIN/10){       //32 bit integer
                return 0;
            }
            ans = (ans * 10) + digit;
            x = x/10;
        }
        return ans;
    }
};
/*
Example 1:
Input: x = 123
Output: 321

Example 2:
Input: x = -123
Output: -321

Example 3:
Input: x = 120
Output: 21
*/


//15. PALINDROME NUMBER                                  {T.C = O(LOGN), S.C = O(1) }
//STORE REVERSED NUMBER AND COMPARE ( -VE ALWAYS FALSE)
class Solution {
public:
    int reverse(int x){
        long ans = 0;
        while(x){
            int digit = x % 10;
            ans = (ans*10)+digit;
            x /= 10;
        }
        if(ans > INT_MAX || ans < INT_MIN){
            return 0;
        }
        return (int)ans;
    }
    bool isPalindrome(int x) {
        int rev = reverse(x);
        if(x < 0){
            return false;
        }
        if(rev == x){
            return true;
        }
        return false;
    }
};
/*
Example 1:
Input: x = 121
Output: true
Explanation: 121 reads as 121 from left to right and from right to left.

Example 2:
Input: x = -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.

Example 3:
Input: x = 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
*/


//16. LCM AND GCD  / GCD OR HCF                         {T.C = O(LOG(MIN(A, B))), S.C = O(1)}
//EUCLEDIAN ALGO (DIVIDEND % DIVISOR = REMINDER-> DIVISOR , DIVISOR->DIVIDEND {UNTILL 0 REMINDER})
//LCM*GCD = A*B
class Solution {
  public:
    long long gcd(long long a, long long b){
        while(a % b != 0){                 //a = divident, b = divisor
            long long rem = a % b;
            a = b;
            b = rem;
        }
        return b;                               //final divisor
    }
    vector<long long> lcmAndGcd(long long A , long long B) {
        long long GCD = gcd(A, B);
        long long LCM = (A*B)/GCD;           //LCM * GCD  = A*B
        
        return {LCM, GCD};
    }
};
/*
Example 1:
Input: a = 5 , b = 10
Output: 10 5
Explanation: LCM of 5 and 10 is 10, while thier GCD is 5.
Input: a = 14 , b = 8
Output: 56 2
Explanation: LCM of 14 and 8 is 56, while thier GCD is 2.
*/


//17. ARMSTRONGS NUMBER                                     {T.C = O(LOGN OR 1), S.C = O(1)}
//STORE ACTUAL NUMBER, TAKE SUM , EXTRACT EACH DIGIT AND CHECK (SUM += DIGIT^3) == ACTUAL NUMBER 
class Solution {
  public:
    string armstrongNumber(int n) {
        int sum = 0;
        int actualNumber = n;
        while(n){
            int digit = n % 10;
            sum += digit * digit * digit;
            n /= 10;
        }
        return sum == actualNumber ? "true": "false";
    }
};
/*
Input: n = 153
Output: true
Explanation: 153 is an Armstrong number since 13 + 53 + 33 = 153. Hence answer is "true".
Input: n = 372
Output: false
Explanation: 372 is not an Armstrong number since 33 + 73 + 23 = 378. Hence answer is "false".
*/


//18. SUM OF ALL DIVISORS FROM 1 TO N                       {T.C = O(N), S.C = O(1)}
//ADD (N/I)*I (CONTRIBUTION OF EACH)
class Solution{
public:
    long long sumOfDivisors(int N){
        long long sum = 0;
        for(int i = 1 ; i <= N ; i++){
            sum += (N/i)*i;
        }
        return sum;
    }
};
/*
Example 1:
Input:
N = 4
Output:
15
Explanation:
F(1) = 1
F(2) = 1 + 2 = 3
F(3) = 1 + 3 = 4
F(4) = 1 + 2 + 4 = 7
ans = F(1) + F(2) + F(3) + F(4)
    = 1 + 3 + 4 + 7
    = 15
*/


//19. PRIME NUMBER / CHECK FOR PRIME                      {T.C = O(SQRT(N)), S.C = O(1)}
//ITERATE 2 TO SQRT(N)
class Solution{
public:
    int isPrime(int N){
        //base case
        if(N == 0 || N == 1){
            return 0;
        }
        for(int i = 2 ; i <= sqrt(N) ; i++){
            if(N % i == 0){
                return 0;
            }
        }
        return 1;
    }
};
/*
Example 1:
Input:
N = 5
Output:
1
Explanation:
5 has 2 factors 1 and 5 only.

Example 2:
Input:
N = 25
Output:
0
Explanation:
25 has 3 factors 1, 5, 25
*/


//LEARN BASIC RECURSION----------------------------------------------------------------------------------
//20. PRINT 1 TO N WITHOUT LOOP (RECURSION)                  {T.C = O(N), S.C = O(N){REC}}
//ADD BASE CASE THEN RECURSIVE CALL(N-1)
class Solution{
    public:
    void printNos(int N)
    {
        //base case
        if(N == 0) return;
        printNos(N-1);
        cout<<N<<" ";
    }
};
/*
Input: n = 10
Output: 1 2 3 4 5 6 7 8 9 10

Input: n = 5
Output: 1 2 3 4 5
*/


//21. PRINT GFG N TIMES                               {T.C = O(N), S.C = O(N){REC}}
//SAME AS ABOVE
class Solution {
  public:
    void printGfg(int N) {
        //base case
        if(N == 0) return;
        printGfg(N-1);
        cout<<"GFG"<<" ";
    }
};
/*
Input:
5
Output:
GFG GFG GFG GFG GFG
*/


//22. PRINT 1 TO N WITHOUD LOOP (RECURSION) 
//SAME 20


//23. PRINT N TO 1 WITHOUT LOOP (RECURSION)               {T.C = O(N), S.C = O(N){REC}}
//JUST COUT FIRST THEN MAKE RECURSIVE CALL
class Solution {
  public:
    void printNos(int N) {
        //base case
        if(N == 0) return;
        cout<<N<<" ";
        printNos(N-1);
    }
};
/*
Input:
N = 10
Output: 10 9 8 7 6 5 4 3 2 1
*/


//24. SUM OF FIRST N TERMS                                    {T.C = O(N), S.C = O(N)}
//SUM = N^3 + CALL(N-1)
class Solution {
  public:
    long long sumOfSeries(long long n) {
        //base case
        if(n == 1) return 1;
        
        long long cubeSum = n*n*n + sumOfSeries(n-1);
        return cubeSum;
    }
};
/*
Example 1:
Input:
n=5
Output:
225
Explanation:
13+23+33+43+53=225

Example 2:
Input:
n=7
Output:
784
Explanation:
13+23+33+43+53+63+73=784
*/


//25. FIND ALL FACTORIALS NUMBERS LESS THAN OR EQUAL TO N         {T.C = O(N), S.C = O(N)}
//MAKE SOLVE FUNCTION
class Solution {
  public:
    void solve(long long n, vector<long long>&ans, long long fact, long long i){
        fact = i*fact;
        //base case 
        if(fact > n){
            return;
        }
        ans.push_back(fact);
        solve(n, ans, fact, i+1);
    }
    vector<long long> factorialNumbers(long long n) {
        vector<long long>ans;
        long long fact = 1;
        long long i = 1;
        solve(n, ans, fact, i);
        return ans;
    }
};
/*
Input: n = 3
Output: 1 2
Explanation: The first factorial number is 1 which is less than equal to n. The second number is 2 which is less than equal to n,but the third factorial number is 6 which is greater than n. So we print only 1 and 2.

Input: n = 6
Output: 1 2 6
Explanation: The first three factorial numbers are less than equal to n but the fourth factorial number 24 is greater than n. So we print only first three factorial numbers.
*/


//26. REVERSE AN ARRAY                                      {T.C = O(N), S.C = O(N)}
//TAKE TEMP(VARIABLE) , REVERSE IT (START, END)
void reverseArray(int arr[], int start, int end){
    //base case
    if (start >= end) return;

    int temp = arr[start];
    arr[start] = arr[end];
    arr[end] = temp;

    // Recursive Function calling
    reverseArray(arr, start + 1, end - 1);
}
/*
INPUT
1 2 3 4 5 6 
OUTPUT
6 5 4 3 2 1
*/


//27. VALID PALINDROME
//RECURSION (STORE ALPHANUMERIC CHAR IN TEMP THEN MAKE RECURSIVE CALL) {T.C = O(N), S.C = O(N)}
class Solution {
public:
    bool solve(string &s, int i){
        int n = s.length();
        //base case
        if(i >= n/2) return true;
        if(s[i] != s[n-i-1]) return false;

        return solve(s, i+1);
    }
    bool isPalindrome(string s) {
        int n = s.length();
        string temp = "";
        for(auto it : s){
            if(isalnum(it)){
                temp.push_back(tolower(it));
            }
        }

        return solve(temp, 0);                     //0 = initial index
    }
};

//OPTIMIZED APPROACH  (USING 2 POINTERS)                               {T.C = O(N), S.C = O(1)}
class Solution {
public:
    bool isPalindrome(string s) {
        int n = s.size();
        int i = 0;
        int j = n-1;
        while(i <= j){
            if(!isalnum(s[i])){
                i++;
            }
            else if(!isalnum(s[j])){
                j--;
            }else{
                if(tolower(s[i]) != tolower(s[j])){
                    return false;
                }else{
                    i++;
                    j--;
                }
            }
        }
        return true;
    }
};
/*
Example 1:
Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.

Example 2:
Input: s = "race a car"
Output: false
Explanation: "raceacar" is not a palindrome.

Example 3:
Input: s = " "
Output: true
Explanation: s is an empty string "" after removing non-alphanumeric characters.
Since an empty string reads the same forward and backward, it is a palindrome.
*/


//28. FIBONACCI NUMBER                                 {T.C = O(2^N), S.C = O(N){RECURSIVE STACK}}
//F(N) = F(N-1) + F(N-2)
class Solution {
public:
    int fib(int n) {
        //base case
        if(n == 0 || n == 1){
            return n;
        }
        return fib(n-1)+fib(n-2);
    }
};
/*
Example 1:
Input: n = 2
Output: 1
Explanation: F(2) = F(1) + F(0) = 1 + 0 = 1.

Example 2:
Input: n = 3
Output: 2
Explanation: F(3) = F(2) + F(1) = 1 + 1 = 2.

Example 3:
Input: n = 4
Output: 3
Explanation: F(4) = F(3) + F(2) = 2 + 1 = 3.
*/


//LEARN BASIC HASHING----------------------------------------------------------------------------------
//29. FREQUENCIES OF LIMITED RANGE ARRAY ELEMENTS                    {T.C = O(N), S.C = O(N)}
//STORE ELEMENT IN MAP WITH FREQ , REPLACE ARR[I] WITH MP(I+1){1 BASED INDEXING}
class Solution{
    public:
    void frequencyCount(vector<int>& arr,int N, int P)
    { 
        unordered_map<int,int>mp;
        for(int i = 0 ; i < N ; i++){
            mp[arr[i]]++;
        }
        for(int i = 0 ; i < N ; i++){
            arr[i] = mp[i+1];              //i+1 for 1 based indexing
        }
    }
};
/*
Input: n = 5 arr[] = {2, 3, 2, 3, 5} p = 5
Output: 0 2 2 0 1
Explanation: Counting frequencies of each array element We have: 1 occurring 0 times. 2 occurring 2 times. 3 occurring 2 times. 4 occurring 0 times. 5 occurring 1 time.

Input: n = 4  arr[] = {3,3,3,3} p = 3
Output: 0 0 4 0
Explanation: Counting frequencies of each array element We have: 1 occurring 0 times. 2 occurring 0 times. 3 occurring 4 times. 4 occurring 0 times.
*/


//30. FIND HIGHEST/LOWEST FREQUENCY ELEMENT                     {T.C = O(N), S.C = O(N)}
//USE MAP STORE FREQ AND FIND HIGHEST FREQ ELEMENT
int maximumFrequency(vector<int> &arr, int n)
{
    unordered_map<int,int>mp;
    int maxFreq = 0;
    int maxAns = 0;

    for(int i = 0 ; i < arr.size() ; i++){
        mp[arr[i]]++;
        maxFreq = max(maxFreq,mp[arr[i]]);
    }
    for(int i= 0 ; i < arr.size() ; i++){
        if(maxFreq == mp[arr[i]]){
            maxAns = arr[i];
            break;
        }
    }
    return maxAns;
}
/*
Sample Input 1:
1 
13
2 12 2 11 -12 2 -1 2 2 11 12 2 -6 

Sample Output 1:
2
Explanation of Sample Input 1:
Test case 1:
For the first test case of sample output 1, as we start traveling the array, ‘2’ has the highest frequency, hence our answer is ‘2’.
*/


/*------------------------------------------THE END----------------------------------------------------*/