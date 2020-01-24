#include<stdio.h>
#define MAX 20 

typedef struct program
{
    int programNum;
    int programLength;
}program;

typedef struct tape
{
    program P[MAX];
}tape;

void mergeSort(program A[MAX], int lb, int hb);
void merge(program A[MAX], int lb, int hb, int mid);
void store(tape T[MAX], program A[MAX], int m, int n);
void printTape(tape T, int i, int m, int n);

void mergeSort(program A[MAX], int lb, int hb)
{
	if(lb < hb)
	{
		int mid = (lb + hb) / 2;
		mergeSort(A, lb, mid);
		mergeSort(A, mid+1, hb);
		merge(A,lb,hb,mid);
	}	
}

void merge(program P[MAX], int lb, int hb, int mid)
{
	int i, j, k, c;
    program temp[MAX];
	i = lb;
	j = mid + 1;
	k = lb;
	while((i <= mid) && (j <= hb))
	{
		if(P[i].programLength < P[j].programLength)
		{
			temp[k] = P[i];
			k++;
			i++; 
		}
		else
		{
			temp[k] = P[j];
			k++;
			j++;
		}
	}
	while(i <= mid)
	{
		temp[k] = P[i];
		k++;
		i++;
	}
	while(j <= hb)
	{
		temp[k] = P[j];
		k++;
		j++;
	}
	for(c = lb; c <= hb; c++)
	{
		P[c] = temp[c];
	}
}

void store(tape T[MAX], program P[MAX], int m, int n)
{
    int i, j;
    for(i = 0; i < n; i++)
    {
        j = (i % m);
        T[j].P[(i-j)/m] = P[i];
    }
}

void printTape(tape T, int i, int m, int n)
{
    int j = n % m;
    int k, l, sum = 0;
    if(i <= j)
        k = (n / m) + 1;
    else
        k = (n / m);
    for(l = 0; l < k; l++)
    {
        printf("%d\t%d\n",T.P[l].programNum, T.P[l].programLength);
        sum = sum + T.P[l].programLength;
    }
    printf("Total retrieval time :: %d\n",sum);
}

int main()
{
	program P[MAX];
    int n, i, m;
	printf("Enter number of programs (1-20) :: ");
	scanf("%d",&n);
    printf("Enter number of tapes :: ");
	scanf("%d",&m);
    tape T[m];
	printf("Enter length of programs :: \n");
	for(i = 0; i < n; i++)
	{
        printf("Program %d :: ", i+1);
        P[i].programNum = i+1;
		scanf("%d",&P[i].programLength);
	}
	mergeSort(P, 0 ,n-1);
    store(T,P,m,n);
	printf("Sorted programs acc to length are :: \n");
	for(i = 0; i < n; i++)
	{
		printf("Program number :: %d Program length :: %d \n",P[i].programNum,P[i].programLength);
	}
    for(i = 0; i < m; i++)
    {
        printf("===============TAPE %d================\n", i+1);
        printf("Num\tLen\n");
        printTape(T[i],i+1,m,n);
        printf("\n");
    }
}