#include <stdio.h>
#include <stdlib.h>
#define MAX 20

typedef struct program {
	int progNum;
	int progLen;
}program;

typedef struct tape {
	program P[MAX];
}tape;

void merge(program P[MAX], int left, int right, int mid) {
	program temp[MAX];
	int i = left;
	int k = left;
	int j = mid + 1;
	while ((i <= mid) && (j <= right)) {
		if (P[i].progLen < P[j].progLen) {
			temp[k] = P[i];
			i++;
			k++;
		}
		else {
			temp[k] = P[j];
			j++;
			k++;
		}
	}
	while (i <= mid) {
		temp[k] = P[i];
		i++;
		k++;
	}
	while (j <= right) {
		temp[k] = P[j];
		j++;
		k++;
	}
	for (int c=left; c<=right; c++) {
		P[c] = temp[c];
	}
}

void mergeSort(program A[MAX], int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		mergeSort(A,left,mid);
		mergeSort(A,mid+1,right);
		merge(A,left,right,mid);
	}
}

void store(tape T[MAX], program P[MAX], int m, int n) {
	for (int i=0; i<n; i++) {
		int j = (i % m);
		T[j].P[(i-j)/m] = P[i];
	}
}

void printTape(tape T, int i, int m, int n) {
	int k, sum = 0;
	int j = n % m;
	if (i <= j)
		k = (n / m) + 1;
	else
		k = (n / m);
	for (int l=0; l<k; l++) {
		printf("%d\t%d\n",T.P[l].progNum,T.P[l].progLen);
		sum += T.P[l].progLen;
	}
	printf("TOTAL RETRIEVAL TIME --> %d",sum);
}

void delimeter() {
	printf("\n");
}

int main() {
	program P[MAX];
	int n,m;
	printf("\n---OPTIMAL STORAGE ON TAPES---\n");
	printf("\nEnter no of programs: ");
	scanf("%d",&n);
	printf("\nEnter no of tapes: ");
	scanf("%d",&m);
	tape T[m];
	printf("\nENTER LENGTH OF EACH PROGRAM :-");
	for (int i=0; i<n; i++) {
		printf("\nProgram %d: ",i+1);
		P[i].progNum = i+1;
		scanf("%d",&P[i].progLen);
 	}
 	mergeSort(P,0,n-1);
 	store(T,P,m,n);
 	printf("\nPrograms are sorted according to length...");
 	for (int i=0; i<n; i++) {
 		printf("\nProgram No: %d \tProgram Length: %d",P[i].progNum,P[i].progLen);
 	}
 	delimeter();
 	for (int i=0; i<m; i++) {
 		printf("\n----TAPE %d ----\n",i+1);
 		printf("NUM\tLEN\n");
 		printTape(T[i],i+1,m,n);
 		delimeter();
 	}
 	return 0;
}