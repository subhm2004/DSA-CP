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

// ════════════════════════════════════════════════════════════════════════════
// FIRST NON-REPEATING CHARACTER STREAM — queue + frequency array
// ────────────────────────────────────────────────────────────────────────────
// har char aaye → freq++ aur queue rear push
// queue front jab tak repeat ho → pop (FIFO cleanup)
// front unique hai → ans mein add; empty → '#'
// ════════════════════════════════════════════════════════════════════════════

// ── main: stream se first non-repeating char track ─────────────────────────
//   1) har char: freq[ch]++, queue push
//   2) front repeat? pop karo jab tak unique na mile
//   3) unique → ans; empty → '#'
//   4) final ans print
int main() {
    string str = "fafcdcad";
    string ans = "";
    int freq[26] = {0};
    queue<int> q;
    for (int i = 0; i < str.length(); i++) {
        char ch = str[i];
        freq[ch - 'a']++;
        q.push(ch);                        // enqueue — stream order maintain
        while (!q.empty()) {
            if (freq[q.front() - 'a'] == 1) {
                ans.push_back(q.front());  // unique mila — answer mein
                break;
            } else {
                q.pop();                   // repeat — front hatao (dequeue)
            }
        }
        if (q.empty()) {
            ans.push_back('#');            // koi unique nahi
        }
    }
    for (int i = 0; i < ans.length(); i++) {
        cout << ans[i] << "->";
    }
}
