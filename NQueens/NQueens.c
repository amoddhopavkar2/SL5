#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 20
int count = 0, backTrack = 0;

void display(int board[], int n) {
	int i,j;
	printf("\n\n\nSOLUTION NUMBER '%d':\n\n\n",++count);
	for (i=1; i<=n; i++)
		printf("\t%d",i);

	for (i=1; i<=n; i++) {
		printf("\n\n%d",i);
		for (j=1; j<=n; j++) {
			if (board[i] == j) 
				printf("\tQ");
			else
				printf("\t-");
		}
	}
	printf("\n");
}

void displayBackTrack(int board[], int n) {
	int i,j;
	printf("\n\n\nBACKTRACK NUMBER '%d':\n\n\n",++backTrack);
	for (i=1; i<=n; i++)
		printf("\t%d",i);

	for (i=1; i<=n; i++) {
		printf("\n\n%d",i);
		for (j=1; j<=n; j++) {
			if (board[i] == j) 
				printf("\tQ");
			else
				printf("\t-");
		}
	}
	printf("\n");
}

int place(int board[], int row, int col) {
	int i;
	for (i=1; i<=row-1; i++) {
		if ((board[i] == col) || (abs(board[i]-col) == (abs(i-row))))
			return 0;
	}
	return 1;
}

void NQueens(int board[], int row, int n) {
	int i; //flag = 0;
	for (i=1; i<=n; i++) {
		if (place(board,row,i)) {
			board[row] = i;	
			if (row == n) 
				display(board,n);
			else {
				NQueens(board,row+1,n);
				//flag = 1;
			}
		}
	}
	displayBackTrack(board,n);
}

int main() {
	int n, board[SIZE];
	printf("\nN QUEENS PROBLEM WITH BACKTRACKING -->\n");
	printf("\nNO. OF QUEENS: ");
	scanf("%d",&n);
	while (n < 4) {
		printf("\n\nNO. OF QUEENS CANNOT BE LESS THAN 4...\n");
		printf("\nRE-ENTER VALID NO. OF QUEENS: ");
		scanf("%d",&n);
	}
	NQueens(board,1,n);
	return 0;
}
