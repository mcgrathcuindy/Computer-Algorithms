/*
 * C++ Program to Solve N-Queen Problem
 */
#include<bits/stdc++.h> 
#define N 4
using namespace std;
 
/* print solution */
void printSolution(int board[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout<<board[i][j]<<"  ";
        cout<<endl;
    }
}
 
/* check if a queen can be placed on board[row][col]*/
bool isSafe(int board[N][N], int row, int col)
{
    int i, j;
    // return false if two queens share the same column
    for(i = 0; i < row; i++)
    {
        if(board[i][col] == 1)
            return false;
    }
    
    // return false if two queens share the same \ diagonal
    for(i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if(board[i][j]==1)
            return false;
    }

    // return false if two queens share the same / diagonal
    for(i = row, j = col; i >= 0 && j < N; i--, j++)
    {
        if(board[i][j]==1)
            return false;
    }
    return true;
 }
 
/*solve N Queen problem */
bool solveNQUtil(int board[N][N], int row)
{
    // if N queens are placed successfully, return True
    if(row>=N)
        return true;
    // place Queen at every square in current row r 
    //and recur for each valid movement  
    for (int i = 0; i < N; i++)
    {
        // if no two queens threaten each other
        if ( isSafe(board, row, i) )
        {
            // place queen on current square
            board[row][i] = 1;
            // recur for next row
            if(solveNQUtil(board, row+1) == true)
                return true;
            // backtrack and remove queen from current square
            board[row][i] = 0;   
        }
    }
    return false;
}
 
/* solves the N Queen problem using Backtracking.*/
bool solveNQ()
{
    int board[N][N] = {0};
    if (solveNQUtil(board, 0) == false)
    {
        cout<<"Solution does not exist"<<endl;
        return false;
    }
    printSolution(board);
    return true;
}
 
// Main
int main()
{
    solveNQ();
    return 0;
}