//SORTING 
#include<bits/stdc++.h>
using namespace std;


//LEARN IMPORTANT SORTING TECHNIQUE ---------------------------------------------------------------------------------
//01. SELECTION SORT                                                          {T.C = O(N^2), S.C = O(1)}
void selectionSort(vector<int>& arr, int n){   
    for(int i = 0 ; i < n-1 ; i++){
        int minIdx = i;
        for(int j = i+1 ; j < n ; j++){
            if(arr[j] < arr[minIdx]){
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}
/*
Sample Input 1:
1
5
6 2 8 4 10
Sample Output 1:
2 4 6 8 10
*/


//02. BUBBLE SORT                                                             {T.C = O(N^2), S.C = O(1)}
class Solution {
  public:
    void bubbleSort(int arr[], int n) {
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n-1-i ; j++){
                if(arr[j] > arr[j+1]){
                    swap(arr[j], arr[j+1]);
                }
            }
        }
    }
};
/*
Input: n = 5, arr[] = {4, 1, 3, 9, 7}
Output: 1 3 4 7 9

Input: n = 10, arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}
Output: 1 2 3 4 5 6 7 8 9 10
*/


//03. INSERTION SORT                                                          {T.C = O(N^2), S.C = O(1)}
void insertionSort(int n, vector<int> &arr){
    for(int i = 1 ; i < n ; i++){
        int temp = arr[i];
        int j = i-1;
        while(j >= 0 && arr[j] > temp){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = temp;
    }
}
/*
Sample Input 1 :
2
4
3 1 2 2
3
1 4 2
Sample Output 1 :
1 2 2 3
1 2 4
*/


//04. MERGE SORT                                                                   {T.C = O(N*LOGN), S.C = O(N)}
class Solution{
public:
    void merge(int arr[], int l, int m, int r){
        vector<int>temp;
        int left = l;
        int right = m+1;
        while(left <= m && right <= r){
            if(arr[left] <= arr[right]){
                temp.push_back(arr[left]);
                left++;
            }else{
                temp.push_back(arr[right]);
                right++;
            }
        }
        while(left <= m){
            temp.push_back(arr[left]);
            left++;
        }
        while(right <= r){
            temp.push_back(arr[right]);
            right++;
        }
        
        //push temp in ans
        for(int i = l ; i <= r ; i++){
            arr[i] = temp[i-l];              //l-l = 0 (starting index)
        }
    }
    
    void mergeSort(int arr[], int l, int r){
        //base case
        if(l >= r) return;
        
        int m = (l + r)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
};
/*
Example 1:
Input:
N = 5
arr[] = {4 1 3 9 7}
Output:
1 3 4 7 9

Example 2:
Input:
N = 10
arr[] = {10 9 8 7 6 5 4 3 2 1}
Output:
1 2 3 4 5 6 7 8 9 10
*/


//05. QUICK SORT                                                                {T.C = O(N*LOGN / N^2), S.C = O(1)}
class Solution{
public:
    int partition (int arr[], int low, int high){
        int pivot = low;
        int i = low, j = high;
        while(i < j){
           while(arr[i] <= arr[pivot]) i++;
           while(arr[j] > arr[pivot]) j--;
           if(i < j) swap(arr[i], arr[j]);           //swap both side ele till i < j
        }
        swap(arr[j], arr[pivot]);                    //push pivot to its correct pos
        return j;
    }
    void quickSort(int arr[], int low, int high){
        if(low < high){
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi-1);
            quickSort(arr, pi+1, high);
        }
    }
};
/*
Example 1:
Input: 
N = 5 
arr[] = { 4, 1, 3, 9, 7}
Output:
1 3 4 7 9

Example 2:
Input: 
N = 9
arr[] = { 2, 1, 6, 10, 4, 1, 3, 9, 7}
Output:
1 1 2 3 4 6 7 9 10
*/