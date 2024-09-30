#include<bits/stdc++.h>
using namespace std;


//DAY 16: STRINGS II----------------------------------------------------------------------------------
//98. Z FUNCTION


//99. KMP ALGO / LPS ARRAY
//99a. FIND THE  INDEX OF FIRST OCCURANCE OF THE STRING        
//BRUTE FORCE  (USING STL)                                                 {T.C = O(N*M), S.C = O(1)}
class Solution {
public:
    int strStr(string haystack, string needle) {
        return haystack.find(needle);
    }
};

//USING KMP                                         {T.C = O(N), S.C = O(N)}
class Solution {
public:
    void findLPS(string &pat, vector<int>&lps, int m){
        int len = 0;
        lps[0] = 0;                     //first ele's lps always 0
        int i = 1;
        while(i < m){
            if(pat[i] == pat[len]){
                len++;
                lps[i] = len;
                i++;
            }else{
                if(len == 0) i++;      //no chance move pointer
                else len = lps[len-1];
            }
        }
    }
    int strStr(string haystack, string needle) {
        int n = haystack.size(), m = needle.size();
        vector<int>lps(m, 0); 
        findLPS(needle, lps, m);             //lps of pattern always

        //find idx
        int i = 0, j = 0;
        while(i < n){
            if(haystack[i] == needle[j]){   //match
                i++, j++;
                if(j == m) return i-m;     //pat found, starting index(currIdx-len)
            }else{                         //mismatch
                if(j == 0) i++;
                else j = lps[j-1];
            }
        }
        return -1;                        //not found
    }
};
/*
Example 1:
Input: haystack = "sadbutsad", needle = "sad"
Output: 0
Explanation: "sad" occurs at index 0 and 6.
The first occurrence is at index 0, so we return 0.

Example 2:
Input: haystack = "leetcode", needle = "leeto"
Output: -1
Explanation: "leeto" did not occur in "leetcode", so we return -1.
*/


//100. MIN CHARS TO ADD FRO PALINDROME                                {T.C = O(N), S.C = O(N)}
class Solution {
public:
    void findLPS(string &pat, vector<int>&lps, int m){
        int len = 0;
        lps[0] = 0;                            //first ele's lps is always 0
        int i = 1; 
        while(i < m){
            if(pat[i] == pat[len]){
                len++;
                lps[i] = len;
                i++;
            }else{
                if(len == 0) i++;
                else len = lps[len-1];
            }
        }
    }
    int minChar(string str){
        string rev = str;
        reverse(rev.begin(), rev.end());
        
        string c = str + "$" + rev;
        int m = c.size();
        vector<int>lps(m, 0);
        findLPS(c, lps, m);
        
        int ans = str.length()-lps.back();        //length of string - last element of lps array(longest match)
        return ans;
    }
};
/*
Example 1:
Input:
S = "abc"
Output: 2
Explanation: 
Add 'b' and 'c' at front of above string to make it
palindrome : "cbabc"

Example 2:
Input:
S = "aacecaaa"
Output: 1
Explanation: Add 'a' at front of above string
to make it palindrome : "aaacecaaa"
*/


//101. VALID ANAGRAM                          
//BRUTE FORCE (SORTING)                                        {T.C = O(N*LOGN), S.C = O(N)}
class Solution {
public:
    bool isAnagram(string s, string t) {
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t;
    }
};

//USING MAP                                                    {T.C = O(N), S.C = O(N)}
class Solution {
public:
    bool isAnagram(string s, string t) {
        //base case
        if(s.length() != t.length()) return false;
        unordered_map<char,int>mp;
        for(auto it : s){
            mp[it]++;
        }
        for(auto it : t){
            if(mp.count(it)){
                mp[it]--;
                if(mp[it] == 0) mp.erase(it);
            }
        }
        if(mp.empty()) return true;
        return false;
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


//102. COUNT AND SAY                                               {T.C = O(2^N), S.C = O(N)}
class Solution {
public:
    string countAndSay(int n) {
        //base case
        if(n == 1) return "1";

        string say = countAndSay(n-1);
        int sz = say.length();
        string ans = "";
        for(int i = 0 ; i < sz ; i++){
            char ch = say[i];
            int count = 1;
            while(i < sz && say[i] == say[i+1]){
                count++, i++;
            }
            ans += to_string(count) + string(1, ch);      //count + char(char to string)
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


//103. COMPARE VERSIONS                                                {T.C = O(MAX(N, M)), S.C = O(N+M)}
class Solution {
public:
    vector<string>getTokens(string &str){
        stringstream ss(str);                      //convert string to streamstring(token's string)
        vector<string>ans;
        string token = "";
        while(getline(ss, token, '.')){             //stringstream, temp string , delimeter(divider)
            ans.push_back(token);
        }
        return ans;
    }
    int compareVersion(string version1, string version2) {
        vector<string>v1 = getTokens(version1);
        vector<string>v2 = getTokens(version2);

        int n = v1.size(), m = v2.size();
        int i = 0;
        while(i < n || i < m){
            int a = i < n ? stoi(v1[i]) : 0;
            int b = i < m ? stoi(v2[i]) : 0;

            if(a < b) return -1;
            else if(a > b) return 1;
            i++;
        }
        return 0;
    }
};
/*
Example 1:
Input: version1 = "1.2", version2 = "1.10"
Output: -1
Explanation:
version1's second revision is "2" and version2's second revision is "10": 2 < 10, so version1 < version2.

Example 2:
Input: version1 = "1.01", version2 = "1.001"
Output: 0
Explanation:
Ignoring leading zeroes, both "01" and "001" represent the same integer "1".

Example 3:
Input: version1 = "1.0", version2 = "1.0.0.0"
Output: 0
Explanation:
version1 has less revisions, which means every missing revision are treated as "0".
*/