#include <stdio.h>
#include <stdlib.h>

void main() 
{
	int i,j=1,k=2,flag;
	for(i=0;i<=4;i++) 
	{
		k=i+j*k;
	}
	flag=55;
	if(flag==10)
		printf("Hello World!");
}