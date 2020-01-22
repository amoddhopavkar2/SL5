#include <stdio.h>
#include <stdlib.h>
#define SIZE 20
int count = 0;

void MaxMin(int arr[], int left, int right, int *max, int *min) {
  int max1,min1,mid;
  if (left == right) {
    *max = arr[left];
    *min = arr[left];
  }

  else if (left == right - 1) {
    if (arr[left] < arr[right])
    {
      *max=arr[right];
      *min=arr[left];
    }
    else
    {
      *max=arr[left];
      *min=arr[right];
    }
  }

  else {
    mid = (left + right) / 2;
    MaxMin(arr,left,mid,max,min);
    max1 = *max;
    min1 = *min;
    MaxMin(arr,mid+1,right,max,min);
    if (*max < max1) {
      *max = max1;
    }
    if (min1 < *min){
      *min = min1;
    }
  }
  printf("\n\nFOR PASS '%d':-",count++);
  printf("\nMAX:%d",*max);
  printf("\nMIN:%d",*min);
}

int main() {
  int n, arr[SIZE];
  int *max, *min;
  max = (int*)malloc(sizeof(int));
  min = (int*)malloc(sizeof(int));
  printf("\n---MAX MIN USING DIVIDE AND CONQUER---\n\n");
  printf("\nENTER THE SIZE OF ARRAY: ");
  scanf("%d",&n);
  for (int i=0; i<n; i++) {
    printf("\nENTER THE ELEMENT A[%d]: ",i+1);
    scanf("%d",&arr[i]);
  }
  MaxMin(arr,0,n-1,max,min);
  printf("\n\nMAX IN THE ARRAY IS:%d",*max);
  printf("\nMIN IN THE ARRAY IS:%d\n",*min);
  return 0;
}
