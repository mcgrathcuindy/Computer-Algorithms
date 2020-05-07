/*
NAME: Christopher McGrath
DATE: 2/3/2020
DESC: C program for Knight Tour problem 
*/
#include<stdio.h> 
#define N 8 

int solveKTUtil(int x, int y, int movei, int sol[N][N], 
				int xMove[], int yMove[]); 

/* A utility function to check if i,j are valid indexes 
for N*N chessboard */
int isSafe(int x, int y, int sol[N][N]) 
{ 
	if (x >= 0 && x < N && y >= 0 && y < N && sol[x][y] == -1)
		return 1;

	return 0;
}

/* A utility function to print solution matrix sol[N][N] */
void printSolution(int sol[N][N]) 
{ 
	int i,j;
	for(i = 0; i < N; i++)
	{ 
		printf("\n");
		for(j = 0; j < N; j++)
		{
			if(sol[i][j] >= 10)					//used to print each element in a neat fashion
				printf("%d  ",sol[i][j]);		//each element will be printed starting in one's column
			else 
				printf(" %d  ", sol[i][j]);
		}
	}
	printf("\n");
} 

/* This function solves the Knight Tour problem using 
Backtracking. This function mainly uses solveKTUtil() 
to solve the problem. It prints "Solutions doesn't exist" if
no complete tour is possible, otherwise prints the 
tour. */
int solveKT() 
{ 
	int i,j;
	int sol[N][N];
	int xMove[N] = {  2, 1, -1, -2, -2, -1,  1,  2 };
	int yMove[N] = {  1, 2,  2,  1, -1, -2, -2, -1 };
	for(i = 0; i < N; i++)
		for(j = 0; j < N; j++)
			sol[i][j] = -1;
	sol[0][0] = 0;
	
	if (solveKTUtil(0, 0, 1, sol, xMove, yMove) == 0) 
    { 
        printf("Solution does not exist"); 
        return 0;
    } 
    else
        printSolution(sol); 
	return 1;
} 

/* A recursive utility function to solve Knight Tour problem */
int solveKTUtil(int x, int y, int movei, int sol[N][N], int xMove[N], int yMove[N]) 
{ 
	int i, newx, newy; 
	if (movei == N*N) 
		return 1; 
    for(i = 0; i< 8; i++) 
    {
        newx = x + xMove[i];
        newy = y + yMove[i];
        if(isSafe(newx, newy, sol))
        {
       	    sol[newx][newy] = movei;
            if(solveKTUtil(newx, newy, movei+1, sol, xMove, yMove) == 1) return 1; 
            else sol[newx][newy] = -1; 
        }
    }
	return 0;
} 

/* Driver program to test above functions */
int main() 
{ 
	solveKT(); 
	return 0; 
} 