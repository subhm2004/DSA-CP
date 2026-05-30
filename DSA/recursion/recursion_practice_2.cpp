/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : recursion_practice_2.cpp
 * PROBLEM  : Recursion Practice 2
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <limits.h>
using namespace std;


/*
 * climbstairs()
 * Purpose : Use BST property: left < root < right.
 * Params  : int n
 * Returns : int
 */
int climbstairs(int n){
    if(n==0 || n==1){
        return 1;
    }
    return climbstairs(n-1) + climbstairs(n-2);
}


/*
 * printarray()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int arr[], int& size, int index
 * Returns : void
 */
void printarray(int arr[], int& size, int index){
    if(index>= size){
        return;
    }
    cout<< arr[index]<< " ";
    printarray(arr,size,index+1);
}


/*
 * linearsearch()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int arr[], int& size, int index, int& target
 * Returns : int
 */
int linearsearch(int arr[], int& size, int index, int& target){
    if(index>= size){
        return -1;
    }
    if(arr[index]== target){
        return index;
    }
    else {
         return linearsearch(arr,size,index+1,target);
    }
}


/*
 * minnumber()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int arr[], int& size, int index, int minimum
 * Returns : int
 */
int minnumber(int arr[], int& size, int index, int minimum){
    if(index>= size){
        return minimum;
    }
     int mini= min(arr[index], minimum);
     return minnumber(arr,size,index+1,minimum);
}
vector<int>checkeven(int arr[],int index, int size, vector<int>&ans){
    if(index>= size){
        return ans;
    }
    if(arr[index] %2 ==0){
        ans.push_back(arr[index]);
    }
    return checkeven(arr,index+1, size,ans);
}


/*
 * doubleeach()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int arr[], int size, int index
 * Returns : void
 */
void doubleeach(int arr[], int size, int index){
    if(index>= size){
        return;
    }
    arr[index]= 2*arr[index];
    doubleeach(arr,size,index+1);
}


/*
 * maxnumber()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int arr[], int& size, int index, int& maxi
 * Returns : int
 */
int maxnumber(int arr[], int& size, int index, int& maxi){
    if(index>= size){
        return maxi;
    }
    if(arr[index]> maxi){
        maxi= arr[index];
    }
    return maxnumber(arr,size,index+1, maxi);
}


/*
 * indexoccurrence()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int *arr, int& size, int index, int& target, vector<int>&ans
 * Returns : vector<int>
 */
vector<int> indexoccurrence(int *arr, int& size, int index, int& target, vector<int>&ans){
    if(index>= size){
        return ans;
    }
    if(arr[index]== target){
        ans.push_back(index);
    }
     return indexoccurrence(arr,size,index+1, target, ans);

}


/*
 * printdigits()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int n
 * Returns : void
 */
void printdigits(int n){
    // Base case: n == 0
    if(n==0){
        return;
    }
    int rem= n%10;
    n= n/10;
    printdigits(n);
    cout<< rem<< endl;
}


/*
 * printnumber()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int arr[], int track, int& size, int& num, int index
 * Returns : void
 */
void printnumber(int arr[], int track, int& size,int& num, int index){
    if(index>= size){
        return;
    }
     num= arr[index] * pow(10, track-1)  + num;
     
     printnumber(arr,track-1,size, num,index+1);

}


/*
 * checksorted()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int arr[], int size, int index
 * Returns : bool
 */
bool checksorted(int arr[], int size, int index){
    if(index >= size-1){
        return true;
    }
    if(arr[index]< arr[index+1]){
        return checksorted(arr,size,index+1);
    }
    else{
        return false;
    }
}


/*
 * binarysearch()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int arr[], int& size, int s, int e, int& target
 * Returns : int
 */
int binarysearch(int arr[],int& size, int s, int e, int& target){
    if(s>e){
        return -1;
    }
    if(s<=e){
        int mid= s+(e-s)/2;
        if(arr[mid]== target){
            return mid;
        }
        else if(arr[mid] > target){
            return binarysearch(arr,size,s, mid-1, target);
        }
        else {
            return binarysearch(arr,size,mid+1,e,target);
        }
    }
}


/*
 * subseq()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : string& str, string& output, int index
 * Returns : void
 */
void subseq(string& str, string& output, int index){
    if(index>= str.length()){
        return;
    }
    subseq(str,output,index+1);

    output.push_back(str[index]);
    subseq(str,output,index+1);
}


/*
 * segmentlength()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int n, int x, int y, int z
 * Returns : int
 */
int segmentlength(int n, int x, int y, int z){
    if(n<0){
        return INT_MIN;
    }
    // Base case: n == 0
    if(n==0){
        return 0;
    }
    int option1= 1+ segmentlength(n-x,x,y,z);
    int option2= 1+ segmentlength(n-y,x,y,z);
    int option3= 1+ segmentlength(n-z,x,y,z);
    int ans= max(option1, max(option2,option3));
    return ans;
}



/*
 * main()
 * Purpose : Entry point — demo/test for Recursion Practice 2
 */
int main() {
    int n;
    cout<< "enter the amount to be made "<< endl;
    cin>> n;
    int arr[]= {1,2,5};
    int size= 3;
    int s=0, e= size-1;
    int track= size;
    int num=0;
    int index= 0;
   
}
