//STRINGS HARD PROBLEM

#include<bits/stdc++.h>
using namespace std;


//404. MINIMUM ADD TO MAKE PARENTHESIS VALID                                 {T.C = O(N), S.C = O(N)}
//USING STACKS, push openbr, else not empty then pop , add stk.size(unpaired), return count.
class Solution {
public:
    int minAddToMakeValid(string s) {
        stack<char>stk;
        int count = 0;
        for(int i = 0 ;  i < s.length() ; i++){
            if(s[i] == ')'){
                if(stk.empty()) count++;
                else stk.pop();                     //stk.top == '('
            }else{
                stk.push(s[i]);                     //stk.push('(')
            }
        }
        count += stk.size();                        //unpaired

        return count;
    }
};
/*
Example 1:
Input: s = "())"
Output: 1

Example 2:
Input: s = "((("
Output: 3
*/


//405. COUNT AND SAY                                                 {T.C = O(EXP), S.C = O(N)}
//RECURSION, IF N != 1 , MAKE RECURSIVE CALL, THEN PRECESSING, ITERATE ON SAY LENGTH, IF NEXT CHAR SAME COUNT++
//ADD STRING(COUNT) + STRING(CH) TO ANS.
class Solution {
public:
    string countAndSay(int n) {
        //base case
        if(n == 1) return "1";

        string say = countAndSay(n-1);               //recursion
        //processing
        int m = say.length();
        string ans = "";
        for(int i = 0 ; i < m ; i++){
            char ch = say[i];
            int count = 1;
            while(i < m && say[i] == say[i+1]){
                count++;
                i++;
            }

            ans += to_string(count) + string(1, ch);  //add count then char
        }

        return ans;
    }
};
/*
Example 1:
Input: n = 4
Output: "1211"
Explanation:
countAndSay(1) = "1"
countAndSay(2) = RLE of "1" = "11"
countAndSay(3) = RLE of "11" = "21"
countAndSay(4) = RLE of "21" = "1211"

Example 2:
Input: n = 1
Output: "1"
Explanation:
This is the base case.
*/


//406. INDEX TO THE FIRST OCCURANCE OF PATTERN IN A TEXT                  {T.C = O(N*M), S.C = O(1)}             
//USING STL
class Solution {
  public:
    int findMatching(string text, string pat) {
        return text.find(pat);
    }
};

//USING 2 POINTERS
class Solution {
  public:
    int findMatching(string text, string pat) {
        int n = text.length(), m = pat.length();
        
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < m ; j++){
                if(text[i+j] != pat[j]) break;
                if(j == m-1) return i;              //all char match
            }
        }
        return -1;
    }
};
/*
Example 1:
Input:
text = gffgfg
pattern = gfg
Output: 3
Explanation:  Considering 0-based indexing, substring of text from 3rd to last index is gfg.

Example 2:
Input:
text = gffggg
pattern = gfg
Output: -1
Explanation: pattern "gfg" does not exist in the text.
*/


//407. SEARCH PATTERN
//USING STL                                                                 {T.C = O(N^2*M), S.C = O(N)}
class Solution{
public:
    vector <int> search(string pattern, string text){
        vector<int>ans;
        int pos = text.find(pattern);
        
        while(pos != string :: npos){
            ans.push_back(pos+1);                         //1 based indexing
            pos = text.find(pattern, pos+1);
        }
        return ans;
    }
};

//WITHOUT STL                                                               {T.C = O(N*M), S.C = O(N)}
class Solution{
public:
    vector <int> search(string pattern, string text){
        int n = text.size(), m = pattern.size();
        vector<int>ans;
        for(int i = 0 ; i < n ; i++){
            if(pattern == text.substr(i, m)) ans.push_back(i+1);       //1 based indexing
        }
        return ans;
    }
};

//USING ROBIN KARP ALGO //ROLLING HASH FUNCTION                              {T.C = O(N), S.C = O(N)}
class Solution{
public:
    int mod = 1e5;
    vector <int> search(string pat, string txt){
        vector<int>ans;
        int txtHash=0,patHash=0;
        int n=txt.size();
        int m=pat.size();
        
        for(int i=0;i<m;i++){                                   //hash till pattern len
            txtHash = ((txt[i]-'a')+txtHash)%mod;
            patHash = ((pat[i]-'a')+patHash)%mod;
        }
        
        if(txtHash==patHash){                                  //1 text window match with pattern
            if(txt.substr(0,m)==pat) ans.push_back(1);         //1 based indexing
        }
        
        for(int i=m,j=0;i<txt.size();i++,j++){                //slide window
           txtHash = (txtHash-txt[j])%mod;                    //remove prev char
           txtHash = (txtHash+txt[i])%mod;                    //add next char
           
            if(txtHash==patHash){
              if(txt.substr(j+1,m)==pat) ans.push_back(j+2);  //match curr(j+1{starting}) push j+2 index(1 based indexing)
            }
        }
        return ans;
    }
};
/*
Example 1:
Input: 
text = "birthdayboy"
pattern = "birth"
Output: 
[1]
Explanation: 
The string "birth" occurs at index 1 in text.

Example 2:
Input:
text = "geeksforgeeks"
pattern = "geek"
Output: 
[1, 9]
Explanation: 
The string "geek" occurs twice in text, one starts are index 1 and the other at index 9.
*/


//408. FIND NUMBER OF OCCURANCE OF P IN S
//BRUTE FORCE (FINDING SUBSTR)                                              {T.C = O(N*M), S.C = O(1)}
int zAlgorithm(string s, string p, int n, int m){
	int count = 0;
	for(int i = 0 ; i < n ;i++){
		if(p == s.substr(i, m)) count++;
	}
	return count;
}

//USING Z ALGORITHM                                                         {T.C = O(N+M), S.C = O(N+M)}
//
/*
ababa
ab

codercodes
code
Sample Output 1:
2

2
Explanation of Sample Input 1:
In the 1st testcase,
"ab" occurs two times in "ababa". The first occurrence is from position 1 to position 2 and the second occurrence is from position 4 to position 5.
*/


//409. SEARCH PATTERN (USING KMP(KNUTH MORRIS PATT) ALGORITHM)                      {T.C = O(N), S.C = O(N)}
//USING LPS(LONGEST PREFIX SUFFIX)
class Solution{
public:
    void findLPS(string &pat, vector<int>&lps, int m){
        int len = 0;
        lps[0] = 0;                          //first ele have 0 lps
        int i = 1;
        while(i < m){
            if(pat[i] == pat[len]){
                len++;                      //maintain order
                lps[i] = len;
                i++;
            }else{
                if(len != 0) len = lps[len-1];
                else{
                    lps[i] = 0;
                    i++;
                }
            }
        }
    }
    vector <int> search(string pat, string txt){
        int n = txt.length(), m = pat.length();
        vector<int>ans;
        
        vector<int>lps(m, 0);                    //lps = longest prefix suffix
        findLPS(pat, lps, m);
        
        //KMP CODE
        int i = 0, j = 0;
        while(i < n){
            if(txt[i] == pat[j]) i++, j++;
            if(j == m){                        
                ans.push_back(i-m+1);          //+1 for 1 based indexing (i-m = starting index)
                j = lps[j-1];                  //update j index
            }
            
            if(txt[i] != pat[j]){
                if(j != 0)  j = lps[j-1];
                else i++;                      //no chance , increase i
            }
        }
        
        return ans;
    }
};
/*
Example 1:
Input:
txt = "geeksforgeeks"
pat = "geek"
Output: 
1 9
Explanation: 
The string "geek" occurs twice in txt, one starts are index 1 and the other at index 9. 

Example 2:
Input: 
txt = "abesdu"
pat = "edu"
Output: 
-1
Explanation: 
There's not substring "edu" present in txt.
*/


//410. SHORTEST PALINDROME                                            {T.C = O(N), S.C = O(N)}
//USING KMP(LPS)
//FIRST MAKE STRING (S + 3 + A(REVERSE OF S)), THEN FIND LPS , STORE LONGEST LPS(N-1), STORE REMAINING STRING I TO N
//REVERSE IT AND ADD TO PALINDROMIC LPS STRING.
class Solution {
public:
    void findLPS(vector<int>&lps, string &str){
        int n = str.length();
        int len = 0;
        lps[0] = 0;                             //starting ele lps is 0
        int i = 1;
        while(i < n){
            if(str[i] == str[len]){
                len++;
                lps[i] = len;
                i++;
            }else{
                if(len == 0) i++;
                else len = lps[len-1];
            }
        }
    }
    string shortestPalindrome(string s) {
        string a = s;
        reverse(a.begin(), a.end());
        string str = s + '#' + a;             //original + # + reverse
        vector<int>lps(str.length(), 0);
        findLPS(lps, str);

        //add remaining not palindromic in begin(temp)
        int i = lps[str.length()-1];          //store len of longest lps(palindromic substring)
        string temp = s.substr(i);            //remaining string(i to n)
        reverse(temp.begin(), temp.end());

        return temp + s;
    }
};
/*
Example 1:
Input: s = "aacecaaa"
Output: "aaacecaaa"

Example 2:
Input: s = "abcd"
Output: "dcbabcd"
*/


//411. LONGEST HAPPY PREFIX                                              {T.C = O(N), S.C = O(N)}
//USING KMP(LPS)
//SIMPLE FIND LPS, THEN CREATE STRING FROM 0 TO I(LPS[N-1]{LONGEST LPS})
class Solution {
public:
    void findLPS(string &s, vector<int>&lps){
        int n = s.length();
        int len = 0;
        lps[0] = 0;
        int i = 1;
        while(i < n){
            if(s[i] == s[len]){
                len++;
                lps[i] = len;
                i++;
            }else{
                if(len == 0) i++;
                else len = lps[len-1];
            }
        }
    }
    string longestPrefix(string s) {
        int n = s.length();
        vector<int>lps(n, 0);
        findLPS(s, lps);

        int i = lps[n-1];                       //store len of longest lps
        string ans = s.substr(0, i);
        return ans;
    }
};
/*
Example 1:
Input: s = "level"
Output: "l"
Explanation: s contains 4 prefix excluding itself ("l", "le", "lev", "leve"), and suffix ("l", "el", "vel", "evel"). The largest prefix which is also suffix is given by "l".

Example 2:
Input: s = "ababab"
Output: "abab"
Explanation: "abab" is the largest prefix which is also suffix. They can overlap in the original string.
*/


//412. COUNT PALINDROMIC SUBSEQUENCES                                   {T.C = O(N^2), S.C = O(N^2)}
//TOP DOWN(MEMOIZATION)
//IF 1ST AND LAST CHAR SAME , THEN 1 + SOLVE((I+1, J) + (I, J-1)) ELSE SOLVE(0 + SOLVE((I+1, J) + (I, J-1) - (I+1, J-1)))
class Solution{
    public:
    int mod = 1e9 + 7; 
    int dp[1005][1005];
    long long int solveMem(string &s, int i , int j){
        //base case
        if(i == j) return 1;                       //only 1 char string
        if(i > j) return 0;                        //not possible
        
        if(dp[i][j] != -1) return dp[i][j];
        
        long long int count;
        if(s[i] == s[j]){
            count = (1 + solveMem(s, i+1, j) + solveMem(s, i, j-1)) %  mod;
        }else{
            count = ((solveMem(s, i+1, j) + solveMem(s, i, j-1) - solveMem(s, i+1, j-1)) % mod + mod) % mod;
        }
        
        return dp[i][j] = count;
    }
    long long int  countPS(string str){
        memset(dp, -1, sizeof(dp));
        int n = str.length();
        return solveMem(str, 0 , n-1);              //0 = initial index, n-1 = last index
    }
};
/*
Example 1:
Input: 
Str = "abcd"
Output: 
4
Explanation:
palindromic subsequence are : "a" ,"b", "c" ,"d"
 
Example 2:
Input: 
Str = "aab"
Output: 
4
Explanation:
palindromic subsequence are :"a", "a", "b", "aa"
*/


/*---------------------------------------------- THE END ---------------------------------------------------------------*/