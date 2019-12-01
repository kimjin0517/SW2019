#define _CRT_SECURE_NO_WARNINGS
#include"LinkedStack.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main() {
	//variables
	int opt,size,i=0;
	int* item=NULL;
	Stack* pStack = NULL;



	//main
	while (1) {
		printf("\n-------------Integer Stack---------------\n");
		printf("\n1)CreateStack\n2)Push\n3)Pop\n4)Top\n5)DestroyStack\n6)IsFullStack\n7)IsEmptyStack\n8)CountStackItem\n9)ClearStack\n0)Exit\n\nchoose the work: ");
		if (scanf("%d", &opt) == 0) {
			printf("You can put 0~9!! Program Down");
			return 0;
		}
		if (opt > 9 || opt < 0) {
			printf("You can put 0~9!! Program Down");
			return 0;
		}
		switch (opt) {
		case 1:
			if (pStack != NULL) {
				printf("Stack is already created!\n");
				continue;
			}
			printf("maximum size of stack: ");
			scanf("%d", &size);
			pStack=CreateStack(size);
			if (pStack == NULL) {
				printf("memory is not allocated\nSystem Down...");
				return 0;
			}

			else printf("Stack created!\n");
			item = (int*)malloc(sizeof(int) * size);
			continue;
		case 2:
			if (pStack == NULL) {
				printf("Stack is not created.\n");
				continue;
			}
			if (IsFullStack(pStack)) {
				printf("Stack is Full!!\n");
				continue;
			}
			printf("Item (Integer Only): ");

			if (scanf("%d", &item[i]) == 0) {
				printf("Integer Only!!\nProgram Down...\n");
				DestroyStack(pStack);
				return 0;
			}
			Push(pStack, (item+i));
			i++;
			continue;
		case 3:
			if (pStack == NULL) {
				printf("Stack is not created.\n");
				size = 0;
				continue;
			}
			if (IsEmptyStack(pStack)) {
				printf("Stack is empty!!\n");
				continue;
			}

			printf("Item: %d \n",*(int*)Pop(pStack));
			i--;
			continue;
		case 4:
			if (pStack == NULL) {
				printf("Stack is not created\n");
				continue;
			}
			if (IsEmptyStack(pStack)) {
				printf("Stack is Empty!!\n");
				continue;
			}
			printf("Top: %d\n", *(int*)pStack->top);
			continue;
		case 5:
			if (pStack == NULL) {
				printf("Stack is not created\n");
				continue;
			}
			DestroyStack(pStack);
			printf("Stack is destroyed\n");
			printf("Program Down...\n");
			return 0;
		case 6:
			if (pStack == NULL) {
				printf("Stack is not created.\n");
				continue;
			}
			if (IsFullStack(pStack)) {
				printf("Stack is Full!!\n");
				continue;
			}
			else printf("Stack is not full.\n");
			continue;
		case 7:
			if (pStack == NULL) {
				printf("Stack is not created.\n");
				continue;
			}
			if (IsEmptyStack(pStack)) {
				printf("Stack is Empty!!\n");
				continue;
			}
			else {
				printf("Stack is not empty.\n");
				continue;
			}
		case 8:
			if (pStack == NULL) {
				printf("Stack is not created.\n");
				continue;
			}
			printf("Stack count: %d", pStack->count);
			continue;
		case 9:
			if (pStack == NULL) {
				printf("Stack is not created.\n");
				continue;
			}
			pStack->top = -1;
			continue;
		case 0:
			if (pStack != NULL) {
				DestroyStack(pStack);
			}

			return 0;
		}
	}

}
