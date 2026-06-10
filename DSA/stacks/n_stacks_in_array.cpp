/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : n_stacks_in_array.cpp
 * PROBLEM  : N Stacks In Array
 * LEETCODE : 716 — Max Stack (multi-stack design)
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : LIFO stack — push on open, pop on match.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// N STACKS IN ONE ARRAY — linked list se free spots manage
// ────────────────────────────────────────────────────────────────────────────
// next[] = free list chain; top[m] = m-th stack ka head index
// freespot = next available index; push/pop se free list update
// ════════════════════════════════════════════════════════════════════════════

class NStack {
public:
    int *arr, *top, *next;
    int number;
    int freespot;
    int size;

    // ── NStack ctor: arrays init + free list banao ───────────────────────────
    //   1) arr, top[], next[] allocate
    //   2) top[i]=-1 — har stack empty
    //   3) next chain: 0→1→2→...→-1, freespot=0
    NStack(int n, int s) {
        this->size = s;
        number = n;
        arr = new int[size];
        top = new int[number];
        next = new int[size];
        freespot = 0;
        for (int i = 0; i < number; i++) {
            top[i] = -1;                   // har stack ka head — abhi koi nahi
        }
        for (int i = 0; i < size; i++) {
            next[i] = i + 1;               // free spot chain — next index link
        }
        next[size - 1] = -1;
    }

    // ── push: m-th stack mein data daalo ─────────────────────────────────────
    //   1) freespot==-1 → overflow
    //   2) free index lo, freespot=next[index]
    //   3) arr[index]=data, next[index]=top[m-1], top[m-1]=index
    void push(int data, int m) {
        if (freespot == -1) {
            cout << "Can't be pushed" << endl;
        } else {
            int index = freespot;
            freespot = next[index];        // free list se index nikaalo
            arr[index] = data;
            next[index] = top[m - 1];      // purana head is index ka next
            top[m - 1] = index;            // naya head set
        }
    }

    // ── pop: m-th stack se element nikaalo ─────────────────────────────────────
    //   1) top[m-1]==-1 → empty
    //   2) index=top, top=next[index]
    //   3) index ko free list mein wapas daalo
    int pop(int m) {
        if (top[m - 1] == -1) {
            return -1;
        } else {
            int index = top[m - 1];
            top[m - 1] = next[index];      // head aage badhao
            next[index] = freespot;        // index free list mein return
            freespot = index;
            return arr[index];
        }
    }
    ~NStack() {
        delete[] arr;
        delete[] top;
        delete[] next;
    }
};

int main() {
    NStack *st = new NStack(2, 6);
}
