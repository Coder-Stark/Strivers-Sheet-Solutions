//STRINGS (BASIC AND MEDIUM)
#include<bits/stdc++.h>
using namespace std;


//BASIC AND EASY STRING PROBLEMS ---------------------------------------------------------------------
//73. REMOVE OUTERMOST PARENTHESES                                      {T.C = O(N), S.C = O(N)}
//COUNT == 0 {REMOVE BRACKET (OUTERMOST BRACKET)}
class Solution {
public:
    string removeOuterParentheses(string s) {
        string ans = "";
        int count = 0;
        for(auto ch : s){
            if(ch == '('){
                count++;
                if(count > 1){
                    ans.push_back(ch);
                }
            }else{ //ch == ')'
                count--;                   //count == 0 {outermost bracket we have to remove}
                if(count > 0){
                    ans.push_back(ch);
                }
            }
        }
        return ans;
    }
};
/*
Example 1:
Input: s = "(()())(())"
Output: "()()()"
Explanation: 
The input string is "(()())(())", with primitive decomposition "(()())" + "(())".
After removing outer parentheses of each part, this is "()()" + "()" = "()()()".

Example 2:
Input: s = "(()())(())(()(()))"
Output: "()()()()(())"
Explanation: 
The input string is "(()())(())(()(()))", with primitive decomposition "(()())" + "(())" + "(()(()))".
After removing outer parentheses of each part, this is "()()" + "()" + "()(())" = "()()()()(())".

Example 3:
Input: s = "()()"
Output: ""
Explanation: 
The input string is "()()", with primitive decomposition "()" + "()".
After removing outer parentheses of each part, this is "" + "" = "".
*/


//74. REVERSE WORDS IN A STRING                                   {T.C = O(N), S.C = O(N)}
//2 POINTER (1 INITIAL WORD , 2 NEXT WORD)
class Solution {
public:
    string reverseWords(string s) {
        int n = s.length();
        string ans;
        int i = 0;
        while(i < n){
            while(i < n && s[i] == ' '){               //continue beginning spaces
                i++;
            }
            if(i >= n){                               //no space(only 1 word)  written as it is
                break;
            }
            int j = i+1;                              //just next space's word
            while(j < n && s[j] != ' '){              //word encounter
                j++;
            }
            string sub = s.substr(i, j-i);            //find substring = substr(initial, lenght (substring))
            if(ans.empty()){
                ans = sub;
            }else{
                ans = sub + " " + ans;                //reverse push 
            }
            i = j+1;
        }
        return ans;
    }
};
/*
Example 1:
Input: s = "the sky is blue"
Output: "blue is sky the"

Example 2:
Input: s = "  hello world  "
Output: "world hello"
Explanation: Your reversed string should not contain leading or trailing spaces.

Example 3:
Input: s = "a good   example"
Output: "example good a"
Explanation: You need to reduce multiple spaces between two words to a single space in the reversed string.
*/


//75. LARGEST ODD NUMBER IN STRING                                     {T.C = O(N), S.C = O(1)}
//TRAVERSING (LEFT <- RIGHT) {GREATEST ODD NUMBER} , SUBSTR(0, I+1)
class Solution {
public:
    string largestOddNumber(string num) {
        for(int i = num.size() ; i >= 0 ; i--){      //right most odd digit (greatest odd number)
            if((num[i]-'0') % 2 != 0){
                return num.substr(0, i+1);           //0 index to length of odd number "12456780" (0, 5+1)=>124567
            }
        }
        return "";
    }
};
/*
Example 1:
Input: num = "52"
Output: "5"
Explanation: The only non-empty substrings are "5", "2", and "52". "5" is the only odd number.

Example 2:
Input: num = "4206"
Output: ""
Explanation: There are no odd numbers in "4206".

Example 3:
Input: num = "35427"
Output: "35427"
Explanation: "35427" is already an odd number.
*/


//76. LONGEST COMMON PREFIX                                       {T.C = O(N*LOGN), S.C = O(N)}
//SORT, CHECK FIRST AND LAST AND MATCH PREFIX(CH OF EACH)
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int n = strs.size();
        sort(strs.begin(), strs.end());
        string a = strs[0];
        string b = strs[n-1];
        string ans = "";
        for(int i = 0 ; i < a.size() ; i++){            //check till first string of grp exist
            if(a[i] == b[i]){                           //after sorting if 1st and last match automatically matched intermidiate strings
                ans += a[i];
            }else{
                break;
            }
        }
        return ans;
    }
};
/*
Example 1:
Input: strs = ["flower","flow","flight"]
Output: "fl"

Example 2:
Input: strs = ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.
*/


//77. ISOMORPHIC STRINGS                                          {T.C = O(N), S.C = O(N)}
//2 MAP AND MAP S AND T .
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        int n = s.length();
        int m = t.length();
        if(n != m){
            return false;
        }

        unordered_map<char, char>mp1;
        unordered_map<char, char>mp2;

        for(int i = 0 ; i < n ; i++){
            char ch1 = s[i];
            char ch2 = t[i];

            if( ( mp1.find(ch1) != mp1.end() && mp1[ch1] != ch2 ) || (mp2.find(ch2) != mp2.end() && mp2[ch2] != ch1) ){
                return false;
            }
            mp1[ch1] = ch2;
            mp2[ch2] = ch1;
        }
        return true;
    }
};
/*
Example 1:
Input: s = "egg", t = "add"
Output: true

Example 2:
Input: s = "foo", t = "bar"
Output: false

Example 3:
Input: s = "paper", t = "title"
Output: true
*/


//78. ROTATE STRING                                                {T.C = O(N), S.C = O(1)}
//STL (S.FIND(GOAL) != STRING :: NPOS)
class Solution {
public:
    bool rotateString(string s, string goal) {
        if(s.size() != goal.size()){
            return false;
        }
        s = s + s;
        return s.find(goal) != string :: npos; 
    }
};
/*
Example 1:
Input: s = "abcde", goal = "cdeab"
Output: true

Example 2:
Input: s = "abcde", goal = "abced"
Output: false
*/


//79. VALID ANAGRAMS                                           {T.C = O(N), S.C = O(N)}
//STORE S IN MAP AND REMOVE T FROM MAP
class Solution {
public:
    bool isAnagram(string s, string t) {
        //base case
        if(s.size() != t.size()){
            return false;
        }
        unordered_map<char,int>mp;
        for(auto ch : s){
            mp[ch]++;
        }
        
        for(auto ch : t){
            mp[ch]--;
        }
        
        for(auto it : mp){                                   //traversal map for count each char
            if(it.second != 0){
                return false;
            }
        }
        return true;
    }
};
/*
Example 1:
Input: s = "anagram", t = "nagaram"
Output: true

Example 2:
Input: s = "rat", t = "car"
Output: false
*/


//80. SORT CHARACTERS BY FREQUENCY                                    {T.C = O(N*LOGN), S.C = O(N)}
//USE LAMBDA FUCNTION
class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int>mp;
        for(auto it : s){
            mp[it]++;
        }
        auto lambda = [&](auto x, auto y){
            if(mp[x] != mp[y]){
                return mp[x] > mp[y];              //decreasing sort by freq
            }
            return x < y;                      //optional (to maintain order)
        };
        sort(s.begin(), s.end(), lambda);

        return s;
    }
};
/*
Example 1:
Input: s = "tree"
Output: "eert"
Explanation: 'e' appears twice while 'r' and 't' both appear once.
So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.

Example 2:
Input: s = "cccaaa"
Output: "aaaccc"
Explanation: Both 'c' and 'a' appear three times, so both "cccaaa" and "aaaccc" are valid answers.
Note that "cacaca" is incorrect, as the same characters must be together.

Example 3:
Input: s = "Aabb"
Output: "bbAa"
Explanation: "bbaA" is also a valid answer, but "Aabb" is incorrect.
Note that 'A' and 'a' are treated as two different characters.
*/


//81. MAXIMUM NESTING DEPTH OF THE PARENTHESES                             
//USING STACK (FIND FINAL STK SIZE AFTER PUSH'(' & POP')')               {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int maxDepth(string s) {
        stack<char>stk;
        int ans = 0;
        for(int i = 0 ; i < s.length() ; i++){
            if(s[i] == '('){
                stk.push(s[i]);
            }else if(s[i] == ')'){
                stk.pop();
            }
            ans = max(ans, (int)stk.size());               //stk.size() == size_t
        }
        return ans;
    }
};

//USING STRING (currDepth += (ch == '(') - (ch == ')'))                 {T.C = O(N), S.C = O(1)}
class Solution {
public:
    int maxDepth(string s) {
        int ans = 0, currDepth = 0;
        for(auto ch : s){
            currDepth += (ch == '(') - (ch == ')');         //ch == ( {depth++} , ch == ) {depth--}
            ans = max(ans, currDepth);
        }
        return ans;
    }
};
/*
Example 1:
Input: s = "(1+(2*3)+((8)/4))+1"
Output: 3
Explanation:
Digit 8 is inside of 3 nested parentheses in the string.

Example 2:
Input: s = "(1)+((2))+(((3)))"
Output: 3
Explanation:
Digit 3 is inside of 3 nested parentheses in the string.

Example 3:
Input: s = "()(())((()()))"
Output: 3
*/


//82. ROMAN TO INTEGER                                             {T.C = O(N), S.C = O(1){CONSTANT MAP}}
//STORE KEY(I,V ..) AND VALUE(1, 5..) TRAVERSE STRING IF NEXT > CURR (ANS+) : (ANS-)
class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int>mp;
        mp['I'] = 1;
        mp['V'] = 5;
        mp['X'] = 10;
        mp['L'] = 50;
        mp['C'] = 100;
        mp['D'] = 500;
        mp['M'] = 1000;

        int ans = 0;
        for(int i = 0 ; i < s.length(); i++){
            if(mp[s[i]] >= mp[s[i+1]]){
                ans += mp[s[i]];
            }else{
                ans -= mp[s[i]];
            }
        }
        return ans;
    }
};
/*
Example 1:
Input: s = "III"
Output: 3
Explanation: III = 3.

Example 2:
Input: s = "LVIII"
Output: 58
Explanation: L = 50, V= 5, III = 3.

Example 3:
Input: s = "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
*/
 

//83. STRING TO INTEGER (ATOI)                                        {T.C = O(N), S.C = O(1)}
//ANS = ANS*10 + S[I]-'0' (SIMPLE) + HANDLE CASES
class Solution {
public:
    int myAtoi(string s) {
        int n = s.size();
        if(n == 0){
            return 0;
        }
        int i = 0;
        while(i < n  && s[i] == ' '){
            i++;
        }
        s = s.substr(i);                 //str = i to last of string (remove white spaces)
        int sign = +1;
        long ans = 0;
        if(s[0] == '-'){
            sign = -1;
        }
        int maxi = INT_MAX, mini = INT_MIN;
        if(s[0] == '+' || s[0] == '-'){   //starting with - or + iterator starts from next i
            i = 1;
        }else{
            i = 0;
        }

        while(i < n){
            if(s[0] == ' ' || !isdigit(s[i])){
                break;
            }
            ans = ans * 10 + s[i]-'0';
            if(sign == -1 && -1*ans < mini){
                return mini;
            }
            if(sign == 1 && ans > maxi){
                return maxi;
            }
            i++;
        }
        return (int)(sign*ans);
    }
};
/*
Example 1:
Input: s = "42"
Output: 42
Explanation:
The underlined characters are what is read in and the caret is the current reader position.
Step 1: "42" (no characters read because there is no leading whitespace)
Step 2: "42" (no characters read because there is neither a '-' nor '+')
Step 3: "42" ("42" is read in)

Example 2:
Input: s = " -042"
Output: -42
Explanation:
Step 1: "   -042" (leading whitespace is read and ignored)
Step 2: "   -042" ('-' is read, so the result should be negative)
Step 3: "   -042" ("042" is read in, leading zeros ignored in the result)

Example 3:
Input: s = "1337c0d3"
Output: 1337
Explanation:
Step 1: "1337c0d3" (no characters read because there is no leading whitespace)
Step 2: "1337c0d3" (no characters read because there is neither a '-' nor '+')
Step 3: "1337c0d3" ("1337" is read in; reading stops because the next character is a non-digit)

Example 4:
Input: s = "0-1"
Output: 0
Explanation:
Step 1: "0-1" (no characters read because there is no leading whitespace)
Step 2: "0-1" (no characters read because there is neither a '-' nor '+')
Step 3: "0-1" ("0" is read in; reading stops because the next character is a non-digit)          ^

Example 5:
Input: s = "words and 987"
Output: 0
Explanation:
Reading stops at the first non-digit character 'w'.
*/


//84a. FINDING ALL SUBSTRINGS OF A STRINGS                                  {T.C = O(N^2), S.C = O(N)}
//BY ME NO PLATFORM
vector<string> subStr (string s) {
    vector<string>ans;
	int n = s.size();
	for(int i = 0 ; i < n ; i++){
	    for(int j = i ; j < n ; j++){
	        ans.push_back(s.substr(i, j-i+1));
	    }
	}
	return ans;
}
int main(){
    string s;
    cin>>s;
    vector<string>ans = subStr(s);
    for(auto it : ans){
        cout<<it<<endl;
    }
}
/*
INPUT
aba
OUTPUT
a ab aba b ba a 
*/


//84b. COUNT NUMBER OF SUBSTRINGS
//BRUTE FORCE APPRAOCH (STRING + MAP)                              {T.C = O(N^2), S.C = O(N)}
class Solution
{
  public:
    long long int substrCount (string s, int k) {
        int n = s.length();
    	long long int count = 0;
    	for(int i = 0 ; i < n ; i++){
    	    unordered_map<char, int>mp;
    	    int distinctCount = 0;
    	    for(int j = i ; j < n ; j++){
    	        if(mp[s[j]] == 0){                    //new char
    	            distinctCount++;
    	        }
    	        mp[s[j]]++;
    	        
    	        if(distinctCount == k){
    	            count++;
    	        }
    	        if(distinctCount > k){
    	            break;
    	        }
    	    }
    	}
    	return count;
    }
};

//BETTER SOLUTION (SLIDING WINDOW + MAP)                                  {T.C = O(N), S.C = O(N)}
class Solution
{
  public:
     long long int f(string s,int k){
        unordered_map<char,int>m;
        int i=0;
        int j=0;
        long long int ans=0;
        while(j<s.size()){
             m[s[j]]++;
            while(m.size()>k){
                m[s[i]]--;
                if(m[s[i]]==0){
                    m.erase(s[i]);
                }
                i++;
                
            }
            ans+=(j-i+1);
            j++;
            
        }
        return ans;
    }
    long long int substrCount (string s, int k){ 
        return f(s,k)-f(s,k-1);
    }
};

//OPTIMIZED APPROACH  (SLIDING WINDWO + CONSTANT SIZE VECTOR)              {T.C = O(N), S.C = O(1)}
class Solution
{
  public:
    long long int solve(string s,int k){
        long long int ans=0;
        vector<int>v(26,0);
        int i=0, j = 0, count = 0;
        
        while(j<s.size()){
            v[s[j]-'a']++;
            
            if(v[s[j]-'a']==1){
                count++;
            }
            while(count>k)
            {
                v[s[i]-'a']--;
                if(v[s[i]-'a']==0){
                    count--;
                }
                i++;
            }
            
            ans+=(j-i+1);
            j++;
        }
        return ans;
    }
    long long int substrCount (string s, int k) {
        return (solve(s,k)-solve(s,k-1));
    }
};
/*
Example 1:
Input:
S = "aba", K = 2
Output:
3
Explanation:
The substrings are: "ab", "ba" and "aba".

Example 2:
Input: 
S = "abaaca", K = 1
Output:
7
Explanation:
The substrings are: "a", "b", "a", "aa", "a", "c", "a". 
*/


//85. LONGEST PALINDROMIC SUBSTRING                                 {T.C = O(N^2), S.C = O(N)}
//EXPAND FROM CENTER (2 CALLS {ODD, EVEN LENGTH OF STRING})
class Solution {
public:
    string expandFromCenter(string &s, int left, int right){
        while(left >= 0 && right < s.length() && s[left] == s[right]){
            left--;
            right++;
        }
        return s.substr(left+1, right-1-left);          //(starting index, length) {i+1, j-1+i}
    }
    string longestPalindrome(string s) {
        int n = s.length();

        //base case
        if(s.length() <= 1){
            return s;
        };

        string maxStr = s.substr(0, 1);                 //(starting index, length)
        for(int i = 0 ; i < n-1 ; i++){
            string odd = expandFromCenter(s, i, i);     //partition on char
            string eve = expandFromCenter(s, i, i+1);   //partition in between char

            if(odd.length() > maxStr.length()){
                maxStr = odd;
            }
            if(eve.length() > maxStr.length()){
                maxStr = eve;
            }
        }
        return maxStr;
    }
};
/*
Example 1:
Input: s = "babad"
Output: "bab"
Explanation: "aba" is also a valid answer.

Example 2:
Input: s = "cbbd"
Output: "bb"
*/


//86. SUM OF BEAUTY OF ALL SUBSTRINGS
//USING MAP                                                   {T.C = O(N^3), S.C = O(N)}
class Solution {
public:
    int findBeautySum(unordered_map<char,int>&mp){
        int maxi = 0;
        int mini = INT_MAX;

        for(auto it: mp){
            maxi = max(maxi, it.second);
            mini = min(mini, it.second);
        }
        return maxi-mini;
    }
    int beautySum(string s) {
        int ans = 0;
        int n = s.length();
        for(int i = 0 ; i < n ; i++){
            unordered_map<char,int>mp;
            mp[s[i]]++;
            for(int j = i+1 ; j < n ; j++){
                mp[s[j]]++;

                ans += findBeautySum(mp);
            }
        }
        return ans;
    }
};

//USING CONSTANT SIZE VECTOR(26, 0)                                 {T.C = O(N^2), S.C = O(1)}
class Solution {
public:
    int beauty(vector<int>&freq){
        int mstFreq = INT_MIN;
        int lstFreq = INT_MAX;
        for(int i = 0 ; i < 26 ; i++){
            mstFreq = max(mstFreq, freq[i]);
            if(freq[i] >= 1){                           //"abcd" , xy.. = 0
                lstFreq = min(lstFreq, freq[i]);
            }
        }
        return mstFreq - lstFreq;
    }
    int beautySum(string s) {
        int n = s.length();
        int ans = 0;
        for(int i = 0 ; i < n ; i++){
            vector<int>freq(26, 0);                    //small alphabet with freq = 0
            for(int j = i ; j < n ; j++){
                freq[s[j]-'a']++;
                ans += beauty(freq);
            }
        }
        return ans;
    }
};
/*
Example 1:
Input: s = "aabcb"
Output: 5
Explanation: The substrings with non-zero beauty are ["aab","aabc","aabcb","abcb","bcb"], each with beauty equal to 1.

Example 2:
Input: s = "aabcbaa"
Output: 17
*/


//87. REVERSE WORDS IN A STRING                                   {T.C = O(N), S.C = O(N)}
//SAME 74.
//2 POINTER (1 INITIAL WORD , 2 NEXT WORD)
class Solution {
public:
    string reverseWords(string s) {
        int n = s.length();
        string ans;
        int i = 0;
        while(i < n){
            while(i < n && s[i] == ' '){               //continue beginning spaces
                i++;
            }
            if(i >= n){                               //no space(only 1 word)  written as it is
                break;
            }
            int j = i+1;                              //just next space's word
            while(j < n && s[j] != ' '){              //word encounter
                j++;
            }
            string sub = s.substr(i, j-i);            //find substring = substr(initial, lenght (substring))
            if(ans.empty()){
                ans = sub;
            }else{
                ans = sub + " " + ans;                //reverse push 
            }
            i = j+1;
        }
        return ans;
    }
};
/*
Example 1:
Input: s = "the sky is blue"
Output: "blue is sky the"

Example 2:
Input: s = "  hello world  "
Output: "world hello"
Explanation: Your reversed string should not contain leading or trailing spaces.

Example 3:
Input: s = "a good   example"
Output: "example good a"
Explanation: You need to reduce multiple spaces between two words to a single space in the reversed string.
*/


/*--------------------------------------------- THE END ---------------------------------------------------------------*/