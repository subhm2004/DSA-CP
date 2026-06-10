/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : rat_in_maze.cpp
 * PROBLEM  : Rat In Maze
 * LEETCODE : 490 — The Maze (grid path backtracking)
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Backtrack: try 4 directions; undo on failure.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// RAT IN MAZE — (0,0) se (n-1,n-1) tak path dhundho
// ────────────────────────────────────────────────────────────────────────────
// 4 directions: D, L, R, U — sirf maze[x][y]==1 aur visited==false
// Backtrack: visited mark, recurse, visited unmark (undo)
// Saare valid paths output string me store
// ════════════════════════════════════════════════════════════════════════════

// ── issafe: cell (x,y) pe ja sakte hain? ────────────────────────────────────
//   1) bounds check — row/col ke andar
//   2) maze[x][y]==1 — blocked nahi
//   3) visited[x][y]==false — pehle nahi aaye
bool issafe(int x, int y, int row, int col, int maze[3][3], vector<vector<bool>>& visited){
    if(((x>=0 && x< row) && (y>=0 && y< col)) && (maze[x][y]== 1) && (visited[x][y]== false)){
        return true;
    }
    else {
        return false;
    }
}

// ── solvemaze: DFS backtracking se saare paths ──────────────────────────────
//   1) (x,y)==destination -> path store, return
//   2) 4 directions try — D, L, R, U
//   3) har direction: visited=true, recurse, visited=false (backtrack)
//   4) output string me direction char append
void solvemaze(int maze[3][3], int &row, int &col, int x, int y,vector<string>&path,
               string output= "", vector<vector<bool> > visited= {}){
                if(x== row-1 && y== col-1){ // destination pe pahunch gaye
                    path.push_back(output);
                    return;
                }
                if(issafe(x+1,y,row,col,maze,visited)){
                    visited[x+1][y] = true;
                    solvemaze(maze,row,col,x+1,y,path,output+'D',visited);
                    visited[x+1][y]= false;  // backtrack
                }
                if(issafe(x,y-1, row,col,maze, visited)){
                    visited[x][y-1]= true;
                    solvemaze(maze,row,col,x,y-1,path,output+'L',visited);
                    visited[x][y-1]= false;
                }
                if(issafe(x,y+1,row,col,maze,visited)){
                    visited[x][y+1]= true;
                    solvemaze(maze,row,col,x,y+1,path,output+ 'R',visited);
                    visited[x][y+1]= false;

                }
                if(issafe(x-1,y, row,col,maze,visited)){
                    visited[x-1][y]= true;
                    solvemaze(maze,row,col,x-1,y,path,output+'U',visited);
                    visited[x-1][y]= false;

                }
 }

// ── main: maze input, saare paths print ─────────────────────────────────────
int main(){
    int maze[3][3]= {{1,0,0},
                     {0,0,0},
                     {1,1,0},

                    };
    if(maze[0][0]== 0){
        cout<< "no path exists"<< endl;
        return 0;
    }
    int row=3, col= 3;
    int x=0, y=0;
    vector<string>path;
    string output= "";
    vector<vector<bool> > visited(row,vector<bool>(col,false));
    visited[0][0]= true;
    solvemaze(maze,row,col,x,y,path,output,visited);
    for(int i=0; i< path.size(); i++){
        cout<< path[i]<< " ";
    }
    if(path.size()== 0){
        cout<< "no path exists"<< endl;
    }


}
