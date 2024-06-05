//BIT MANIPULATION

#include<bits/stdc++.h>
using namespace std;

/*NOTE
n & (n-1)   => check if a number n is power of 2           {n-1 => (R->L) 0->1 , 1->0 then stop}
            => clear/unset the lowest set bit (0th bit)
while(n){                         //gives number of set(1) bits in a binary number 
    n = n & (n-1);
    cnt++;
}

n & -n  => gives rightmost set bit

*/
//LEARN BIT MANIPULATION -----------------------------------------------------------------------------------
//144. BIT MANIPULATION / INTRODUCTION TO BIT MANIPULATION                 {T.C = O(1), S.C = O(1)}
//Ith Bit = (NUM >> I) & 1 {OR} NUM & BITMASK >> I {BITMASK == (1 << I)}, SET = NUM | BITMASK, RESET = NUM & ~BITMASK
//0th BIT = (NUN & 1) {OR} N & (N + 1) == 0 ? 0 : 1
//NEW BIT AFTER 0TH BIT SET = N | (N+1)
//(1 BASED INDEXING) 
class Solution {
  public:
    void bitManipulation(int num, int index) {
        int i = index-1;                           //1 based indexing
        int bitMask = (1 << i); 
        
        // int ithBit = (num >> i) & 1;            //right shift and mask
        int ithBit = (num & bitMask) >> i;         //bit masking
        int setithBit = num | bitMask;             //for setting bit OR
        int clrithBit = num & ~bitMask;            //for reset bit & ~
        
        cout<<ithBit<<" "<<setithBit<<" "<<clrithBit;
    }
};
/*
Example 1:
Input: 70 3
Output: 1 70 66
Explanation: Bit at the 3rd position from LSB is 1. (1 0 0 0 1 1 0)
The value of the given number after setting the 3rd bit is 70. 
The value of the given number after clearing 3rd bit is 66. (1 0 0 0 0 1 0)

Example 2:
Input: 8 1
Output: 0 9 8
Explanation: Bit at the first position from LSB is 0. (1 0 0 0)
The value of the given number after setting the 1st bit is 9. (1 0 0 1)
The value of the given number after clearing 1st bit is 8. (1 0 0 0)
*/


//145. CHECK WHETHER KTH BIT IS SET OR NOT                                     {T.C = O(1), S.C = O(1)}
//ITH BIT = (NUM >> I) & 1
class Solution
{
    public:
    bool checkKthBit(int n, int k)
    {
        int kthBit = (n >> k) & 1;
        return kthBit == 1 ? true : false;
    }
};
/*
Example 1:
Input: 
N = 4
K = 0
Output: 
No
Explanation: 
Binary representation of 4 is 100, in which 0th index bit from LSB is not set. So, return false.

Example 2:
Input: 
N = 4
K = 2
Output: 
Yes
Explanation: 
Binary representation of 4 is 100, in which 2nd index bit from LSB is set. So, return true.

Example 3:
Input: 
N = 500
K = 3
Output: 
No
Explanation: 
Binary representation of 500 is 111110100, in which 3rd index bit from LSB is not set. So, return false.
*/


//146. ODD OR EVEN                                                     {T.C = O(1), S.C = O(1)}
//ITH BIT = (NUM >> I) & 1
class Solution{   
public:
    string oddEven(int N){
        int i = 0;
        int ithBit = (N >> i) & 1;
        return ithBit == 1 ? "odd" : "even";
    }
};
/*
Example 1:
Input:
N = 1
Output:
odd
Explanation:
The output is self-
explanatory.
 
Example 2:
Input:
N = 2
Output:
even
Explanation:
The output is self-
explanatory.
*/


//147. POWER OF TWO                                          {T.C = O(1), S.C = O(1)}
//N & (N-1) == 0 (ONLY 1 SET BIT => POWER OF 2)
class Solution {
public:
    bool isPowerOfTwo(int n) {
        //base case
        if(n <= 0){
            return false;
        }
        return (n & (n-1)) == 0 ? true : false;         //pow of 2 should only 1 set bit (whole no.)
    }
};
/*
Example 1:
Input: n = 1
Output: true
Explanation: 20 = 1

Example 2:
Input: n = 16
Output: true
Explanation: 24 = 16
Example 3:
Input: n = 3
Output: false
*/


//148a. NUMBER OF SET (1) BITS                                              {T.C = O(1 / (NO. OF BITS(32))), S.C = O(1)}
//USING N & (N-1)
class Solution {
  public:
    int setBits(int N) {
        int count = 0;
        while(N){
            N = N & (N-1);
            count++;
        }
        return count;
    }
};

//USING STL
class Solution {
  public:
    int setBits(int N) {
        return __builtin_popcount(N);
    }
};
/*
Example 1:
Input:
N = 6
Output:
2
Explanation:
Binary representation is '110' 
So the count of the set bit is 2.

Example 2:
Input:
8
Output:
1
Explanation:
Binary representation is '1000' 
So the count of the set bit is 1.
*/


//148b. COUNT TOTAL SET BITS
class Solution {
public:
    int minBitFlips(int start, int goal) {
        int XorAns = start ^ goal;
        // return __builtin_popcount(XorAns);
        int count = 0;
        while(XorAns){
            XorAns = XorAns & (XorAns-1);          //n & (n-1)
            count++;
        }
        return count;
    }
};

//BRUTE FORCE
//USING STL (TLE)                                               {T.C = O(N*LOGN), S.C = O(1)}
class Solution{
    public:
    int countSetBits(int n)
    {
        int count;
        for(int i = 1 ; i <= n ; i++){
            count += __builtin_popcount(i);                      //LOGN
        }
        return count;
    }
};

//USING BIT MANIPULATION                                       {T.C = O(LOGN^2), S.C = O(1)}
//FIRST FIND MAX POW OF 2 TILL NO. HANDLE (2^X-1) + EXRRA BIT + REC(FOR EXTRA BITS RESIDUAL PART)
class Solution{
    public:
    int maxPow2(int n){
        int c = 0;
        while((1 << c) <= n){
            c++;
        }
        return c-1;
    }
    int countSetBits(int n)
    {
        if(n == 0){
            return 0;
        }
        int x = maxPow2(n);
        // ans = x*2^(x-1) + (n - 2^x + 1) + rec(n - 2^x)
        int ans = x*(1 << (x-1)) + (n - (1 << x)) + 1 + countSetBits(n-(1 << x));
        return ans;
    }
};
/*
Example 1:
Input: N = 4
Output: 5
Explanation:
For numbers from 1 to 4.
For 1: 0 0 1 = 1 set bits
For 2: 0 1 0 = 1 set bits
For 3: 0 1 1 = 2 set bits
For 4: 1 0 0 = 1 set bits
Therefore, the total set bits is 5.

Example 2:
Input: N = 17
Output: 35
Explanation: From numbers 1 to 17(both inclusive), 
the total number of set bits is 35.
*/


//149. SET THE RIGTHMOST (OTH) UNSET BIT                                            {T.C = O(LOGN), S.C = O(1)}
//0TH BIT = N & (N+1)
//SET 0TH BIT = N | (N+1)
class Solution
{
public:
    int setBit(int N)
    {
        return (N & (N + 1) == 0) ? N : (N | (N + 1));
    }
};
/*
Example 1:
Input:
N = 6
Output:
7
Explanation:
The binary representation of 6 is 110.
After setting right most bit it becomes
111 which is 7.

Example 2:
Input:
N = 15
Output:
15
Explanation:
The binary representation of 15 is 1111.
As there is no unset bit it remains the
same.
*/


//150. SWAP TWO NUMBERS                                                       {T.C = O(1), S.C = O(1)}
//USING 3RD VARIABLE(TEMP)
class Solution{   
public:
    pair<int, int> get(int a, int b){
        int temp = a;
        a = b;
        b = temp;
        return {a, b};
    }
};

//USING XOR
class Solution{   
public:
    pair<int, int> get(int a, int b){
        a = a^b;
        b = a^b;
        a = a^b;
        
        return {a, b};
    }
};

//USING ADD & SUB
class Solution{   
public:
    pair<int, int> get(int a, int b){
        a = a+b;
        b = a-b;
        a = a-b;
        
        return {a, b};
    }
};
/*
Example 1:
Input: a = 13, b = 9
Output: 9 13
Explanation: after swapping it
becomes 9 and 13.

Example 2:
Input: a = 15, b = 8
Output: 8 15
Explanation: after swapping it
becomes 8 and 15.
*/


//151. DIVIDE TWO INTEGERS (WITHOUT / , %)                                 {T.C = O(LOGN^2), S.C = O(1)}
//USE BIT MANIPULATION
class Solution {
public:
    int divide(int dividend, int divisor) {
        //base case
        if(dividend == divisor){
            return 1;
        }
        bool sign = true;
        if((dividend >= 0 && divisor < 0) || (dividend <= 0 && divisor > 0)){
            sign = false;
        }       

        long n = abs(dividend);
        long d = abs(divisor);
        long q = 0;                       //q = quotient
        while(n >= d){
            int count = 0;
            while(n >= (d << (count + 1))){            //n > d * 2^count+1
                count++;
            }
            q += 1 << count;                           //2^count
            n -= (d << count);                         //d * 2^count
        }
        if(q == (1 << 31) && sign){                    //+2^31
            return INT_MAX; 
        }
        if(q == (1 << 31) && !sign){                   //-2^31
            return INT_MIN;
        }

        return sign ? q : -q;

    }
};
/*
Example 1:
Input: dividend = 10, divisor = 3
Output: 3
Explanation: 10/3 = 3.33333.. which is truncated to 3.

Example 2:
Input: dividend = 7, divisor = -3
Output: -2
Explanation: 7/-3 = -2.33333.. which is truncated to -2.
*/


//INTERVIEW PROBLEMS----------------------------------------------------------------------------------------------
//152. MINIMUM BIT FLIPS TO CONVERT NUMBER                                       {T.C = O(1), S.C = O(1)}
//XOR OF START AND GOAL , THEN COUNT NO. OF SET(1) BITS
class Solution {
public:
    int minBitFlips(int start, int goal) {
        int XorAns = start ^ goal;
        return __builtin_popcount(XorAns);
    }
};
/*
Example 1:
Input: start = 10, goal = 7
Output: 3
Explanation: The binary representation of 10 and 7 are 1010 and 0111 respectively. We can convert 10 to 7 in 3 steps:
- Flip the first bit from the right: 1010 -> 1011.
- Flip the third bit from the right: 1011 -> 1111.
- Flip the fourth bit from the right: 1111 -> 0111.
It can be shown we cannot convert 10 to 7 in less than 3 steps. Hence, we return 3.

Example 2:
Input: start = 3, goal = 4
Output: 3
Explanation: The binary representation of 3 and 4 are 011 and 100 respectively. We can convert 3 to 4 in 3 steps:
- Flip the first bit from the right: 011 -> 010.
- Flip the second bit from the right: 010 -> 000.
- Flip the third bit from the right: 000 -> 100.
It can be shown we cannot convert 3 to 4 in less than 3 steps. Hence, we return 3.
*/


//153. SINGLE NUMBER                                                   {T.C = O(N), S.C = O(1)}
//XOR WILL CANCEL OUT SAME , REMAING IS ANSWER
class Solution {
public:
    int singleNumber(vector<int>& nums) {             //xor = different element != 0 else 0 
        int xorAns = 0;
        for(int i = 0 ; i < nums.size(); i++){
            xorAns = xorAns^nums[i];
        }
        return xorAns;
    }
};
/*
Example 1:
Input: nums = [2,2,1]
Output: 1

Example 2:
Input: nums = [4,1,2,1,2]
Output: 4

Example 3:
Input: nums = [1]
Output: 1
*/


//154. SUBSETS                                                            {T.C = O(N*2^N), S.C = O(N*2^N)}
//USIN BIT
//FIND NO. OF SUBSETS (1 << N), TRAVERSE ON EACH BITMASK THEN CHECK ALL BITS AND PUSH SET BITS ((X >> I) & 1)
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        int bitMask = 1 << n;                  //n == i      //2^i / NO. OF SUBSETS
        vector<vector<int>>ans;
        for(int x = 0 ; x < bitMask ; x++){
            vector<int>temp;
            for(int i = 0 ; i < n ; i++){         //check all bits (3 {2^3})     
                if((x >> i) & 1){                 //check ith bit
                    temp.push_back(nums[i]);
                }
            }
            ans.push_back(temp);
        }
        return ans;
    }
};
/*
Example 1:
Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

Example 2:
Input: nums = [0]
Output: [[],[0]]
*/


//155. FIND XOR OF NUMBERS FROM L TO R                                     {T.C = O(1), S.C = O(1)}
//PATTERN (N % 4 == 1, 2, 3, 4 ==> 1, N+1, 0, N), THEN CALL FOR TRIM RANGE (L, R)
class Solution {
  public:
    int solve(int n){
        if(n % 4 == 1){
            return 1;
        }else if(n % 4 == 2){
            return n+1;
        }else if(n % 4 == 3){
            return 0;
        }else{ //if(n % 4 == 4)
            return n;
        }
    }
    int findXOR(int l, int r) {
        return solve(l-1) ^ solve(r);          //r - (1 - l)  {l, r}
    }
};
/*
Input: 
L = 4, R = 8 
Output:
8 
Explanation:
4 ^ 5 ^ 6 ^ 7 ^ 8 = 8
*/


//156. TWO NUMBER WITH ODD OCCCURENCES / SINGLE NUMBER III          
//BRUTE FORCE (MAP)                                                             {T.C = O(N), S.C = O(N)}
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        vector<int>ans;
        unordered_map<int, int>mp;
        for(auto it : nums){
            mp[it]++;
        }
        for(auto it : mp){
            if(it.second == 1){
                ans.push_back(it.first);
            }
        }
        return ans;
    }
};

//SIMILAR TO ABOVE (ODD OCCURENCES ONLY) {TLE}                                   {T.C = O(N), S.C = O(N)}
class Solution{
    public:
    vector<long long int> twoOddNum(long long int Arr[], long long int N)  
    {
        vector<long long int>ans;
        unordered_map<long long int, long long int>mp;
        for(long long int i = 0 ; i < N ; i++){
            mp[Arr[i]]++;
        }
        for(auto it : mp){
            if(it.second % 2 != 0){               //odd
                ans.push_back(it.first);
            }
        }
        
        sort(ans.rbegin(), ans.rend());
        return ans;
    }
};

//OPTIMIZED APPROACH (BIT MANIPULATION)
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        vector<int> ans(2, 0); // Initialize the answer vector with two elements

        int xorResult = 0;
        
        // Step 1: Get the XOR of all elements
        for (int num : nums) {
            xorResult ^= num;
        }
        
        // Step 2: Find the rightmost set bit
        /*
        int rightmostSetBit = 1;
        while ((rightmostSetBit & xorResult) == 0) {
            rightmostSetBit <<= 1;
        }
        */ // or down
        // int rightmostSetBit = xorResult & -xorResult;                      //overflow
        unsigned int rightmostSetBit = xorResult & -(unsigned int)xorResult;

        
        // Step 3 & 4: Divide into two groups and XOR separately
        for (int num : nums) {
            if ((num & rightmostSetBit) == 0) {
                ans[0] ^= num; // XOR for the group where the bit is not set
            } else {
                ans[1] ^= num; // XOR for the group where the bit is set
            }
        }
        
        return ans;
    }
};
/*
Example 1:
Input: nums = [1,2,1,3,2,5]
Output: [3,5]
Explanation:  [5, 3] is also a valid answer.

Example 2:
Input: nums = [-1,0]
Output: [-1,0]

Example 3:
Input: nums = [0,1]
Output: [1,0]
*/


//ADVANCED MATHS ------------------------------------------------------------------------------------------------
//157. PRIME FACTORS                                                    {T.C = O(SQRT(N)+LOGN), S.C = O(N)}
//TRAVERSE(ROOT) IF(N % I == 0), DIVDIE IT TILL (N % I == 0) : N = N/I , IF BIGGEST PRIME PUSH IN ANS
class Solution{
	public:
	vector<int>AllPrimeFactors(int N) {
	    vector<int>ans;
	    for(int i = 2 ; i <= sqrt(N) ; i++){
	        if(N % i == 0){
	            ans.push_back(i);
	            while(N % i == 0){
	                N = N/i;
	            }
	        }
	    }
	    if(N != 1){                             //for last case of biggest prime number
	        ans.push_back(N);
	    }
	    
	    return ans;
	}
};
/*
Example 1:
Input: N = 100
Output: 2 5
Explanation: 2 and 5 are the unique prime
factors of 100.

Example 2:
Input: N = 35
Output: 5 7
Explanation: 5 and 7 are the unique prime
factors of 35.
*/


//158. ALL DIVISORS OF A NUMBER                            {T.C = O(SQRT(N) OR NLOGN(SORTING)), S.C = O(N)}
//TRAVERSE(ROOT) IF(N % I == 0), DIVDIE IT TILL (N % I == 0) : N = N/I , IF BIGGEST PRIME PUSH IN ANS
class Solution {
  public:
    void print_divisors(int n) {
        vector<int>ans;
        for(int i = 1; i <= sqrt(n) ; i++){
            if(n % i == 0){
                ans.push_back(i);
                if(n / i != i){                      //6x6 = 36 (actually its one 6 only)
                    ans.push_back(n/i);
                }
            }
        }
        sort(ans.begin(), ans.end());
        for(auto it : ans){
            cout<<it<<" ";
        }
    }
};
/*
Example 1:
Input : 20
Output: 1 2 4 5 10 20
Explanation: 20 is completely 
divisible by 1, 2, 4, 5, 10 and 20.

Example 2:
Input: 21191
Output: 1 21191
Explanation: As 21191 is a prime number,
it has only 2 factors(1 and the number itself).
*/


//159. COUNT PRIMES / SIEVE OF ERATOSTHENES	               {T.C = O(N*LOG(LOGN)), S.C = O(N)}
//FIRST MARK ALL PRIME NUMBER AS 1 THEN TRAVERSE FROM 2 TO SQRT(N) AND SET ALL COMPOSITE NUMBER AS 0
class Solution {
public:
    int countPrimes(int n) {
        vector<int>prime(n+1, 1);               //mark all number prime factor 1
        for(int i = 2 ; i <= sqrt(n) ; i++){
            if(prime[i] == 1){
                for(int j = i*i ; j <= n ; j+= i){  //composite number set to 0
                    prime[j] = 0;
                }
            }
        }

        int count = 0;
        for(int i = 2 ; i < n ; i++){             //remaining number setted 1 (required answer)
            if(prime[i] == 1){
                count++;
            }
        }
        return count;
    }
};
/*
Example 1:
Input: n = 10
Output: 4
Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.

Example 2:
Input: n = 0
Output: 0

Example 3:
Input: n = 1
Output: 0
*/


//160. PRIME FACTORIZATION USING SIEVE OF ERATOSTHENES                   {T.C = O(N*LOG(LOGN)), S.C = O(N)}
//SIMILAR TO 157
class Solution {
  public:
    void sieve() {}                           //useless

    vector<int> findPrimeFactors(int N) {
        vector<int>ans;
        for(int i = 2 ; i <= N ; i++){
            if(N % i == 0){
                while(N % i == 0){
                    ans.push_back(i);
                    N = N / i;
                }
            }
        }
        return ans;
    }
};
/*
Example:

Input: 
N = 12246
Output: 
2 3 13 157
Explanation: 
2*3*13*157 = 12246 = N.
*/
//161. POW(X, N)                                            {T.C = O(LOGN), S.C = O(LOGN)}
//SOLVE BY CONDITIONS (N == 0, N < 0, N % 2 == 0)
class Solution {
public:
    double solve(double x, long n){
        //base case
        if(n == 0){                        //2^0 = 1
            return 1;
        }
        if(n < 0){                         //2-1 = 1/2  
            return solve(1/x, -n);
        }
        if(n % 2 == 0){                   //2^8 = 2*2^4
            return solve(x*x , n/2);
        }else{
            return x*solve(x*x, (n-1)/2); //2^9 = 2*(2*2^4)
        }
    }
    double myPow(double x, int n) {
        return solve(x, (long)n);
    }
};
/*
Example 1:
Input: x = 2.00000, n = 10
Output: 1024.00000

Example 2:
Input: x = 2.10000, n = 3
Output: 9.26100

Example 3:
Input: x = 2.00000, n = -2
Output: 0.25000
Explanation: 2-2 = 1/22 = 1/4 = 0.25
*/


/*----------------------------------- THE END -------------------------------------------------------*/