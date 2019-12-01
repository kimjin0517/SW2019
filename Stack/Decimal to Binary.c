#define _CRT_SECURE_NO_WARNINGS
#include"ArrayStack.h"
#include<stdio.h>
#include<stdlib.h>

int main() {
	int size, temp ,num,i=0; 
	int* item;
	Stack* pStack;

	printf("Enter Natural Number: ");
	
	if (scanf("%d", &num) == 0) {
		printf("Natural Number Only!!! Program Down...\n");
		return 0;
	}
	if (num < 0) {
		printf("Natural Number Only!!! Program Down...\n");
		return 0;
	}
	temp = num;
	
	while (temp > 1) {
		temp /= 2;
		i++;
	}
	size = i + 1;
	pStack = CreateStack(size);
	item = (int*)malloc(sizeof(int*) * size);

	i = 0;
	while (num > 0) {
		item[i] = num % 2;
		Push(pStack, &item[i]);
		num /= 2;
		i++;
	}
	
	printf("Decimal to binary: ");

	for (int j = 0;j < size;j++) {
		printf("%d", *(int*)Pop(pStack));
	}
	DestroyStack(pStack);
	return 0;
}