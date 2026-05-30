/*
 * ============================================================================
 * TOPIC    : Queues
 * FILE     : nonrepeating_char.cpp
 * PROBLEM  : Nonrepeating Char
 * LEETCODE : 387 — First Unique Character in String
 * ABOUT    : Queue, deque, circular queue, sliding window
 * APPROACH : FIFO queue — enqueue rear, dequeue front.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <queue>
#include <string>
using namespace std;


/*
 * main()
 * Purpose : Entry point — demo/test for Nonrepeating Char
 */
int main(){
    string str= "fafcdcad";
    string ans="";
    int freq[26]= {0};
    queue<int>q;
    for(int i=0; i< str.length(); i++){
        char ch= str[i];
        freq[ch-'a']++;
        q.push(ch);
        while(!q.empty()){
            if(freq[q.front()- 'a'] ==1){
                ans.push_back(q.front());
                break;
            }
            else {
                q.pop();
            }
        }
        if(q.empty()){
            ans.push_back('#');
        }
    }
    for(int i=0; i< ans.length(); i++){
        cout<< ans[i]<< "->";
    }

}
