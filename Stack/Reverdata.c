#define _CRT_SECURE_NO_WARNINGS
#include"ArrayStack.h"
#include<stdio.h>
#include<stdlib.h>

//reverse data
int main() {
	int size;
	int* item;
	Stack* pStack = NULL;

	printf("Number of integer: ");
	scanf("%d", &size);
	pStack=CreateStack(size);
	item = (int*)malloc(sizeof(int*)*size);

	for (int i = 0;i < size;i++) {
		printf("Á¤¼ö %d: ", i + 1);
		if (scanf("%d",&item[i] )==0) {
			
			printf("Warning : integer only!! Program Down!!!");
			return 0;
		}
		Push(pStack, &item[i]);
	}
	printf("\nPrint reverse: ");
	for (int i = 0;i < size ;i++) {
		printf("%d ", *(int*)Pop(pStack));
	}
	DestroyStack(pStack);
	return 0;
}