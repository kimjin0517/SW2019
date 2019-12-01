#define _CRT_SECURE_NO_WARNINGS
#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H


#include<stdio.h>
#include<stdlib.h>

typedef void* Element;

typedef struct aStackNode {
	Element data;
	struct aStackNode* link;
} StackNode;

typedef struct {
	int count;
	StackNode* top;
	int size;
} Stack;

Stack* CreateStack(int size) {
	Stack* pStack = (Stack*)malloc(sizeof(Stack));
	if (pStack == NULL) {
		return NULL;
	}
	pStack->count = 0;
	pStack->top = NULL;
	pStack->size = size;
	return pStack;
}

void Push(Stack *pStack,Element item){
	StackNode* node = NULL;
	if(IsFullStack(pStack)) return;
	node= (StackNode*)malloc(sizeof(StackNode));
	node->data = item;
	node->link = pStack->top;
	pStack->count++;
	pStack->top = node;
	return;
}

Element Pop(Stack *pStack) {
	StackNode* node = NULL;
	Element a;
	if (IsEmptyStack(pStack)) {
		return NULL;
	}
	node = pStack->top;
	pStack->top = node->link;
	a = node->data;
	free(node);
	pStack->count--;
	return a;
}

void DestroyStack(Stack* pStack) {
	StackNode* node;
	if (pStack->count == 0) {
		free(pStack);
		return;
	}
	while (pStack->top == NULL) {
		node = pStack->top;
		pStack->top = (node->link);
		free(node);
	}
	free(pStack);
}
int IsEmptyStack(Stack* pStack) {
	if (pStack->count == 0) return 1;
	else return 0;
}
int IsFullStack(Stack* pStack) {
	if (pStack->size == pStack->count) return 1;
	else return 0;
}
void EmptyStack(Stack *pStack) {
	StackNode* node;
	if (pStack->count == 0) {
		free(pStack);
		return;
	}
	while (pStack->top == NULL) {
		node = pStack->top;
		pStack->top = (node->link);
		free(node);
		pStack->count -=1;
	}
	return;
}

#endif