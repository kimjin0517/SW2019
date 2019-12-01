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

//stack 생성함수
Stack* CreateStack(int size) {
	//stack 할당?
	Stack* pStack = (Stack*)malloc(sizeof(Stack));
	if (pStack == NULL) {
		return NULL;
	}
	//stack mem 비할당시 
	pStack->stack = malloc(sizeof(Element) * size);
	if (pStack->stack == NULL) {
		return NULL;
	}
	//top,max 설정
	pStack->max = size;
	pStack->top = -1;

	return pStack;
}

//
void Push(Stack* pStack, Element item) {
	//푸쉬 전 stack의 잔여공간 확인
	if (IsFullStack(pStack)) {
		printf("There's no left stack space.");
		return;
	}
	//item push
	pStack->stack[++pStack->top] = item;
	return;
}

//stack mem 할당해제
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

//stack full 확인
int IsFullStack(Stack* pStack) {
	if (pStack->top == pStack->max - 1) {
		return 1;
	}
	else return 0;
}

//stack empty 확인
int IsEmptyStack(Stack* pStack) {
	if (pStack->top == -1) {
		return 1;
	}
	else return 0;
}

//stack갯수 확인
int CountStackItem(Stack* pStack) {
	return pStack->top + 1;
}

//stack 비우기
void ClearStack(Stack* pStack) {
	pStack->top = -1;
	return;
}


#endif




