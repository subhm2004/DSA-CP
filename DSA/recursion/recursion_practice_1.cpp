/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : recursion_practice_1.cpp
 * PROBLEM  : Recursion Practice 1
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// RECURSION PRACTICE 1 — Mixed recursive problems collection
// ────────────────────────────────────────────────────────────────────────────
// Factorial, sum, fibonacci, search, subsequence, merge/quick sort, permutations
// Har function ek alag recursion pattern demonstrate karta hai
// Practice file — multiple DSA topics ek saath
// ════════════════════════════════════════════════════════════════════════════




// ── factorial: factorial logic ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int factorial(int n){
    if(n==0|| n==1){
        return 1;
    }
    return n*factorial(n-1);
}



// ── sum: sum logic ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int sum(int n){
    // Base case: n == 1
    if(n==1){
        return 1;
    }
    // Base case: n == 0
    if(n==0){
        return 0;
    }
    return n+ sum(n-1);
}



// ── climbstairs: climbstairs logic ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int climbstairs(int n){
    // Base case: n == 1
    if(n==1){
        return 1;
    }
    if(n==2){
        return 2;
    }
    return climbstairs(n-1)+ climbstairs(n-2);
}



// ── printcount: printcount logic ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
void printcount(int n){
    // Base case: n == 1
    if(n==1){
        cout<< 1<< " ";
        return;
    }
    printcount(n-1);
    cout<< n << " ";
}



// ── fibonacci: fibonacci logic ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int fibonacci(int n){
    // Base case: n == 1
    if(n==1){
        return 0;
    }
    if(n==2){
        return 1;
    }
    return fibonacci(n-1)+ fibonacci(n-2);
}



// ── linearsearch: linearsearch logic ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
void linearsearch(int *arr, int &size, int index, int& target){
    if(index>= size){
        return ;
    }
    if(arr[index]== target){
        cout<< index<< " ";
    }
    
    return linearsearch(arr,size,index+1,target);
}




// ── printarray: printarray logic ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
void printarray(int arr[], int n){
    if(n<=0){
        return;
    }
    printarray(arr,n-1);
    cout<< arr[n-1]<< " ";
}




// ── binarysearch: binarysearch logic ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int binarysearch(int arr[], int &n, int s, int e, int &target){
        if(s>e){
            return -1;
        }
        int mid= s+(e-s)/2;
        if(arr[mid]== target){
            return mid;
        }
        else if(arr[mid] > target){
            return binarysearch(arr,n,s,mid-1,target);
        }
        else{
            return binarysearch(arr, n,mid+1, e,target);
        }
}



// ── minimumno: minimumno logic ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int minimumno(int *arr, int& size, int& mini, int index){
    cout<< index<< endl;
    if(index>= size){
        return mini;
    }
    if(arr[index] < mini){
        mini= arr[index];
    }
    cout<< mini<< endl;
    minimumno(arr,size,mini,index+1);

}




// ── evennum: evennum logic ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
void evennum(vector<int>&nums, int* arr, int index, int& size){
    if(index ==size){
        // Iterate over all elements
        for(int i=0; i<nums.size(); i++){
            cout<< nums[i]<< " ";
        }
        return;
    }
    if(arr[index]%2== 0){
        nums.push_back(arr[index]);
    }
    evennum(nums,arr,index+1,size);
}



// ── doubleeach: doubleeach logic ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
void doubleeach(int *arr, int index, int& size){
    if(index==size){
        // Iterate over all elements
        for(int i=0; i<size; i++){
            cout<< arr[i]<< " ";
        }
        return;
    }
    arr[index]= 2*arr[index];
    doubleeach(arr,index+1, size);   
}



// ── printdigits: printdigits logic ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
void printdigits(int n){
    // Base case: n == 0
    if(n==0){
        return;
    }
    int rem= n%10;
    printdigits(n/10);
    cout<< rem<< endl;  
}



// ── sortedarray: sortedarray logic ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
bool sortedarray(int *arr, int index, int& size){
    if(index+1 >= size){
        return true;
    }
    if(arr[index+1] > arr[index]) {
        return sortedarray(arr, index+1 ,size);
    }
    else {
        return false;
    }
}



// ── subsequence: subsequence logic ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
void subsequence(string str, string ans,int index){
    if(index>= str.length()){
        cout<< ans << endl;
        return;
    }
    char ch= str[index];
    subsequence(str,ans,index+1);
    ans.push_back(ch);
    subsequence(str,ans,index+1);
}



// ── subsequence2: subsequence2 logic ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
void subsequence2(string str, string ans, int index){
    if(index>= str.length()){
        cout<< ans<< endl;
        return;
    }
    char ch= str[index];
    ans.push_back(ch);
    subsequence2(str,ans,index+1);
    ans.pop_back();
    subsequence2(str, ans, index+1);
}



// ── maximumsum: maximumsum logic ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int maximumsum(int *arr,int sum, int& size, int index){
    if(index>= size){
        return sum;   
    }
    int a= maximumsum(arr,sum,size,index+1);
    sum= sum+ arr[index];  
    int b= maximumsum(arr,sum,size,index+2);
    sum= max(a,b);   
}



// ── mergearray: mergearray logic ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
void mergearray(int *arr, int& size, int s, int e){
    int mid= s+(e-s)/2;
    int length1= mid-s+1;
    int length2= e-mid;
    int *left= new int[length1];
    int *right= new int[length2];
    int k=s;
    for(int i=0; i< length1; i++){
        left[i]= arr[k];
        k++;
    }
    k= mid+1;
    for(int i=0; i< length2; i++){
        right[i]= arr[k];
        k++;
    }
    int i=0, j=0;
    k=s;
    while(i<length1 && j<length2){
        if(left[i]<= right[j]){
            arr[k++]= left[i++];
        }
        else {
            arr[k++]= right[j++];
        }
    }
    while(i<length1){
        arr[k++]= left[i++];
    }
    while(i<length2){
        arr[k++]= right[j++];
    }

}



// ── mergesort: mergesort logic ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
void mergesort(int* arr, int& size, int s, int e){
    if(s>=e){
        return;
    }
    int mid= s+(e-s)/2;
    mergesort(arr,size,s,mid);
    mergesort(arr,size,mid+1,e);
    mergearray(arr,size,s,e);
}



// ── partitionlogic: partitionlogic logic ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int partitionlogic(int *arr, int& size, int s, int e){
    int pivotindex= s;
    int pivotelement= arr[s];
    int count= 0;
    for(int i=s+1; i<=e; i++){
        if(arr[i] <= pivotelement){
            count++;
        }
    }
    int rightindex= s+count;
    swap(arr[rightindex], arr[pivotindex]);
    pivotindex= rightindex;
    int i=s, j=e;
    while(i<pivotindex && j> pivotindex){
        while(arr[i]<=arr[pivotindex] ){
            i++;
        }
        while(arr[j]> arr[pivotindex]){
        
            j--;
        }
        if(i<pivotindex && j> pivotindex){
            swap(arr[i], arr[j]);
        }
    }
    return pivotindex;
}



// ── quicksort: quicksort logic ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
void quicksort(int *arr, int& size, int s,int e){
    if(s>=e){
        return;
    }
    int p= partitionlogic(arr,size,s,e);
    quicksort(arr,size,s,p-1);
    quicksort(arr,size,p+1,e); 
}



// ── permutations: permutations logic ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
void permutations(string str, int index){
    if(index>= str.length()){
        cout<< str<< endl;
        return;
    }
    for(int j=index; j< str.length(); j++){
        swap(str[index], str[j]);
        permutations(str,index+1);
        swap(str[index], str[j]);
    }
}



// ── main: main logic ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int main(){
    int arr[]= {7,3,2,2,16,25,4,11,9};
    string str= "abc";
    int index=0;
    permutations(str,index);
   
    int sum= 0;
    int size= 9;
    int s=0, e= size-1;
    int target= 5;






    
    return 0;
}
