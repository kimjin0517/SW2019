#define _CRT_SECURE_NO_WARNINGS
#ifndef STACK_H
#define STACK_H

#include<stdio.h>
#include<stdlib.h>

typedef void* Element;


typedef struct {
	Element *stack;
	int max;
	int top;
}Stack;

//stack �����Լ�
Stack* CreateStack(int size) {
	//stack �Ҵ�?
	Stack* pStack = (Stack*)malloc(sizeof(Stack));
	if (pStack == NULL) {
		return NULL;
	}
	//stack mem ���Ҵ�� 
	pStack->stack = malloc(sizeof(Element) * size);
	if (pStack->stack == NULL) {
		return NULL;
	}
	//top,max ����
	pStack->max = size;
	pStack->top = -1;

	return pStack;
}

//
void Push(Stack* pStack, Element item) {
	//Ǫ�� �� stack�� �ܿ����� Ȯ��
	if (IsFullStack(pStack)) {
		printf("There's no left stack space.");
		return;
	}
	//item push
	pStack->stack[++pStack->top] = item;
	return;
}

//stack mem �Ҵ�����
void DestroyStack(Stack* pStack) {
	free(pStack->stack);
	free(pStack);
	pStack = NULL;
}

//pop
Element Pop(Stack* pStack) {
	if (IsEmptyStack(pStack)) {
		return NULL;
	}
	return pStack->stack[(pStack->top)--];
}

//stack full Ȯ��
int IsFullStack(Stack* pStack) {
	if (pStack->top == pStack->max - 1) {
		return 1;
	}
	else return 0;
}

//stack empty Ȯ��
int IsEmptyStack(Stack* pStack) {
	if (pStack->top == -1) {
		return 1;
	}
	else return 0;
}

//stack���� Ȯ��
int CountStackItem(Stack* pStack) {
	return pStack->top + 1;
}

//stack ����
void ClearStack(Stack* pStack) {
	pStack->top = -1;
	return;
}


#endif




