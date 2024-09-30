#include<bits/stdc++.h>
using namespace std;


//DAY 15: STRINGS ----------------------------------------------------------------------------------
//92. REVERSE WORDS IN A STRING                                          {T.C = O(N), S.C = O(N)}
class Solution {
public:
    string reverseWords(string s) {
        int n = s.length();
        string ans = "";
        int i = 0;
        while(i < n){
            while(i < n && s[i] == ' ') i++;          //skip spaces
            if(i >= n) break;                      //all travesed

            int j = i+1;                           //idx just after space
            while(j < n && s[j] != ' ') j++;       //find substr len
            string temp = s.substr(i, j-i);        //extract single word
            if(ans.empty()) ans = temp;            //first word
            else ans = temp + " " + ans;           //push in front(reverse push)
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


//93. LONGEST PALINDROMIC SUBSTRING                                 {T.C = O(N^2), S.C = O(N^2)}
//USING MIKE TEMPLETE
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.length();
        //base case
        if (n == 0) return "";
        
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        int maxLength = 1;                           // Length of the longest palindrome
        int startIdx = 0;                            // Starting index of the longest palindrome
        
        for (int L = 1; L <= n; L++) {
            for (int i = 0; i+L-1 < n; i++) {
                int j = i+L-1;                    //len of substring
                if (i == j) dp[i][j] = true;      // Single character palindrome
                else if (i + 1 == j){             // Two character palindrome
                    dp[i][j] = (s[i] == s[j]);
                }  
                else{                             // General case
                    dp[i][j] = (s[i] == s[j] && dp[i + 1][j - 1]);
                }  
                
                //find palindromic starting char
                if (dp[i][j] == true && L > maxLength) {
                    maxLength = L;
                    startIdx = i;
                }
            }
        }
        
        return s.substr(startIdx, maxLength);  // Return the longest palindromic substring
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


//94. ROMAN TO INTEGER                                              {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int romanToInt(string s) {
        int n = s.length();
        unordered_map<char,int>mp;
        mp['I'] = 1;
        mp['V'] = 5;
        mp['X'] = 10;
        mp['L'] = 50;
        mp['C'] = 100;
        mp['D'] = 500;
        mp['M'] = 1000;

        int ans = 0;
        for(int i = 0 ; i < n; i++){
            if(mp[s[i]] >= mp[s[i+1]]) ans += mp[s[i]];
            else ans -= mp[s[i]];
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


//95. STRING TO INTEGER                                              {T.C = O(N), S.C = O(N)}
class Solution {
public:
    long atoi(string s, int sign, int i, long ans){
        if(sign*ans <= INT_MIN) return INT_MIN;
        
        if(sign*ans >= INT_MAX) return INT_MAX;
        
        if(i >= s.size() || s[i] < '0' || s[i] > '9') return sign*ans;
        
        ans = atoi(s, sign, i+1, (ans*10 + (s[i]-'0')));

        return ans;
    }
    int myAtoi(string s) {
        int n = s.length();
        int i = 0;
        int sign = 1;
        while(i < n && s[i] == ' ') i++;          //ignore beginnig spaces
            
        if(s[i] == '+') i++;
        else if(s[i] == '-'){
            sign = -1;
            i++;
        }

        return atoi(s, sign, i, 0);           //0 = ans
    }
};
/*
Example 1:
Input: s = "42"
Output: 42
Explanation:
The underlined characters are what is read in and the caret is the current reader position.
Step 1: "42" (no characters read because there is no leading whitespace)
         ^
Step 2: "42" (no characters read because there is neither a '-' nor '+')
         ^
Step 3: "42" ("42" is read in)
           ^

Example 2:
Input: s = " -042"
Output: -42
Explanation:
Step 1: "   -042" (leading whitespace is read and ignored)
            ^
Step 2: "   -042" ('-' is read, so the result should be negative)
             ^
Step 3: "   -042" ("042" is read in, leading zeros ignored in the result)
*/


//96. LONGEST COMMON PREFIX                                    {T.C = O(N*LOGN), S.C = O(N)}
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int n = strs.size();
        sort(strs.begin(), strs.end());
        string first = strs[0];
        string last  = strs[n-1];
        string ans = "";
        for(int i = 0 ; i < first.size() ; i++){
            if(first[i] == last[i]) ans += first[i];
            else break;
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


//97. ROBIN KARP ALGO //ROLLING HASH FUNCTION                              {T.C = O(N), S.C = O(N)}
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