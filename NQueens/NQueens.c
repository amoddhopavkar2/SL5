#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 20
int count = 0;

void display(int board[], int n) {
	printf("\n\n\nSOLUTION NO. '%d':\n\n\n",++count);
	for (int i=1; i<=n; i++)
		printf("\t%d",i);

	for (int i=1; i<=n; i++) {
		printf("\n\n%d",i);
		for (int j=1; j<=n; j++) {
			if (board[i] == j) 
				printf("\tQ");
			else
				printf("\t-");
		}
	}
	printf("\n");
}

int place(int board[], int row, int col) {
	for (int i=0; i<=row-1; i++) {
		if ((board[i] == col) || (abs(board[i]-col) == (abs(i-row))))
			return 0;
	}
	return 1;
}

void NQueens(int board[], int row, int n) {
	for (int i=1; i<=n; i++) {
		if (place(board,row,i)) {
			board[row] = i;	
			if (row == n) 
				display(board,n);
			else
				NQueens(board,row+1,n);
		}
	}
}

int main() {
	int n, board[SIZE];
	printf("\n---N QUEENS PROBLEM---\n");
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