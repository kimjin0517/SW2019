#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

void selectionSort(int list[], int n){
	int i = 0;
	int j = 0;
	int small = 0;
	int temp = 0;
	for (i = 0; i < n - 1; i++) {
		small = i;
		for (j = i + 1; j < n; j++)
			if (list[j] < list[small])
				small = j;
		temp = list[i];
		list[i] = list[small];
		list[small] = temp;
	}
}

void insertionSort(int list[], int n){
	int i = 0;
	int	j = 0;
	int hd = 0;
	for (i = 1; i < n; i++) {
		hd = list[i];
		for (j = i; j > 0 && hd < list[j - 1]; j--) {
			list[j] = list[j - 1];
		}
		list[j] = hd;
	}
}


void bubbleSort(int list[], int n){
	int i = 0;
	int	j = 0;
	int temp = 0;
	int sorted = 0;
	for (i = 0; i < n && sorted==0; i++) {
		for (j = n - 1, sorted = 1; j > i; j--) {
			if (list[j] < list[j - 1]) {
				sorted = 0;
				temp = list[j];
				list[j] = list[j - 1];
				list[j - 1] = temp;
			}
		}
	}
}

void quicksort(int list[], int left, int right) {
	int pivot = 0;
	int i = 0;
	int j = 0;
	int temp = 0;
	if (left < right) {
		i = left; 
		j = right + 1;
		pivot = list[left];
		do {
			do {
				i++;
			} while (list[i] < pivot );
			do {
				j--;
			} while (list[j] > pivot );
			if (i < j) {
				temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
		} while (i < j);
		temp = list[left];
		list[left] = list[j];
		list[j] = temp;
		quicksort(list, left, j - 1);
		quicksort(list, j + 1, right);
	}
	else return;
}

void Merge(int list[], int sorted[], int left, int mid, int right) {
	int i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;

	while (i <= mid && j <= right) {
		if (list[i] <= list[j])
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}

	if (i > mid) {
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	}
	else {
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];
	}

	for (l = left; l <= right; l++) {
		list[l] = sorted[l];
	}
}

void Merge_Sort(int list[], int sorted[], int left, int right) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		Merge_Sort(list, sorted, left, mid);
		Merge_Sort(list, sorted, mid + 1, right);
		Merge(list, sorted, left, mid, right);
	}
}

int main() {
	int list[100];
	int merge[100];
	int quick[100];
	int bubble[100];
	int insertion[100];
	int selection[100];
	FILE* f1 = fopen("input.txt", "r");
	if (f1 == NULL) return 0;
	
	printf("<Sort function>\ninput은 0 ~ 99 무작위 순서입니다\n\n"); 
	printf("input : \n");

	for (int i = 0; i < 100; i++) {
		fscanf(f1,"%d\n", &list[i]);
		quick[i] = list[i];
		bubble[i] = list[i];
		insertion[i] = list[i];
		selection[i] = list[i];
		printf("%d, ", list[i]);
		if (i % 10 == 9) printf("\n");
	}
	
	printf("\b\b \n");

	selectionSort(selection, 100);
	insertionSort(insertion, 100);
	bubbleSort(bubble, 100);
	quicksort(quick, 0, 99);
	Merge_Sort(list, merge, 0,99);
	printf("Selection :\n");
	for (int i = 0; i < 100; i++) {
		printf("%d, ", selection[i]);
		if (i % 10 == 9) printf("\n");
	}
	printf("\b\b \nInsertion :\n");
	for (int i = 0; i < 100; i++) {
		printf("%d, ", insertion[i]);
		if (i % 10 == 9) printf("\n");
	}
	printf("\b\b \nBubble :\n");
	for (int i = 0; i < 100; i++) {
		printf("%d, ", bubble[i]);
		if (i % 10 == 9) printf("\n");
	}
	printf("\b\b \nQuick :\n");
	for (int i = 0; i < 100; i++) {
		printf("%d, ", quick[i]);
		if (i % 10 == 9) printf("\n");
	}
	printf("\b\b \nMerge :\n");
	for (int i = 0; i < 100; i++) {
		printf("%d, ", merge[i]);
		if (i % 10 == 9) printf("\n");
	}
	fclose(f1);
	return 0;
}

