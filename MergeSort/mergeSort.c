#include <stdio.h>

void merge(int arr[], int left, int middle, int right) {
	int sizeLeft = middle - left + 1;
	int sizeRight = right - middle;

	int arrLeft[sizeLeft], arrRight[sizeRight];
	for (int i=0; i<sizeLeft; i++) 
		arrLeft[i] = arr[left + i];

	for (int i=0; i<sizeRight; i++)
		arrRight[i] = arr[middle + i + 1];

	int i = 0, j = 0, k = left;
	while (i < sizeLeft && j < sizeRight) {
		if (arrLeft[i] <= arrRight[j]) {
			arr[k] = arrLeft[i];
			i++;
		}

		else {
			arr[k] = arrRight[j];
			j++;
		}
		k++;
	}

	while (i < sizeLeft) {
		arr[k] = arrLeft[i];
		i++;
		k++;
	}

	while (j < sizeRight) {
		arr[k] = arrRight[j];
		j++;
		k++;
	}
}

void mergeSort(int arr[], int left, int right) {
	if (left < right) {
		int middle = (left + right) / 2;
		mergeSort(arr,left,middle);
		mergeSort(arr,middle+1,right);

		merge(arr,left,middle,right);
	}
}

void mergeDesc(int arr[], int left, int middle, int right) {
	int sizeLeft = middle - left + 1;
	int sizeRight = right - middle;

	int arrLeft[sizeLeft], arrRight[sizeRight];
	for (int i=0; i<sizeLeft; i++) 
		arrLeft[i] = arr[left + i];

	for (int i=0; i<sizeRight; i++)
		arrRight[i] = arr[middle + i + 1];

	int i = 0, j = 0, k = left;
	while (i < sizeLeft && j < sizeRight) {
		if (arrLeft[i] > arrRight[j]) {
			arr[k] = arrLeft[i];
			i++;
		}

		else {
			arr[k] = arrRight[j];
			j++;
		}
		k++;
	}

	while (i < sizeLeft) {
		arr[k] = arrLeft[i];
		i++;
		k++;
	}

	while (j < sizeRight) {
		arr[k] = arrRight[j];
		j++;
		k++;
	}
}

void mergeSortDesc(int arr[], int left, int right) {
	if (left < right) {
		int middle = (left + right) / 2;
		mergeSortDesc(arr,left,middle);
		mergeSortDesc(arr,middle+1,right);

		mergeDesc(arr,left,middle,right);
	}
}

void display(int arr[20], int size) {
	printf("\n");
	for (int i=0; i<size; i++) 
		printf("%d\t",arr[i]);
	printf("\n");	
}

int main() {
	int size, arr[20];
	printf("\nENTER SIZE OF THE ARRAY:");
	scanf("%d",&size);
	printf("\nENTER THE ELEMENTS IN THE ARRAY:\n");
	for (int i=0; i<size; i++) {
		scanf("%d",&arr[i]);
	}
	
	printf("\n\nTHE ARRAY IS:");
	display(arr,size);

	FILE *fp;
	fp = fopen("mergeSort.txt","w");
	fprintf(fp,"INPUT ARRAY:");
	for (int i=0; i<size; i++) {
		fprintf(fp,"\t%d",arr[i]);
	}
	fclose(fp);

	printf("\n\nNOW SORTING THE ARRAY IN ASCENDING ORDER...");
	printf("\nTHE ARRAY IN ASCENDING ORDER IS:");
	mergeSort(arr,0,size-1);
	display(arr,size);

	fp = fopen("mergeSort.txt","a");
	fprintf(fp,"\n\n\nTHE ARRAY IN ASCENDING ORDER:");
	for (int i=0; i<size; i++) {
		fprintf(fp,"\t%d",arr[i]);
	}
	fclose(fp);

	printf("\n\nNOW SORTING THE ARRAY IN DESCENDING ORDER...");
	printf("\nTHE ARRAY IN DESCENDING ORDER IS:");
	mergeSortDesc(arr,0,size-1);
	display(arr,size);

	fp = fopen("mergeSort.txt","a");
	fprintf(fp,"\n\nTHE ARRAY IN DESCENDING ORDER:");
	for (int i=0; i<size; i++) {
		fprintf(fp,"\t%d",arr[i]);
	}
	fclose(fp);
	printf("\n");
	return 0;
}