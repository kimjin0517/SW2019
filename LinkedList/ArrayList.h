#define _CRT_SECURE_NO_WARNINGS
#ifndef ARRAYLIST
#define ARRAYLIST
#include<stdio.h>
#include<stdlib.h>


typedef void* Element;

typedef struct {
	Element *list;
	int top;
	int size;
	int (*compare)(Element item1, Element item2);
}List;

List* CreateList(int size, int (*compare) (Element item1, Element item2)) {
	List* nlist =NULL;
	nlist = (List*)malloc(sizeof(List));
	if (nlist == NULL) return NULL;
	nlist->list = (Element*)malloc(sizeof(Element)*size);
	if (nlist->list == NULL) return NULL;
	nlist->top = 0;
	nlist->size = size;
	nlist->compare = compare;
	return nlist;
}

int searchList(List* list,Element item) {
	if (list->top == 0) return -1;
	if (list->top == 1) {
		if (list->compare(item, list->list[0]) <= 0) return 0;
	}
	for (int i = 0;i < list->top;i++) {
		if (list->compare(item, list->list[i]) <= 0) return i;
	}
	return -1;
}

void insertList(List* list,Element item) {
	int* a=NULL;
	int found = searchList(list, item);
	a = (int*)malloc(sizeof(int*));
	*a = *(int*)item;
	
	if (found == -1) {
		list->list[list->top] = a;
		list->top++;
		return;
	}
	
	if (*(int*)(list->list[found]) == *(int*)item) {
		return;
	}
	
	
	for (int i = list->top;i > found;i--) {
		list->list[i] = list->list[i - 1];
	}
	list->list[found] = a;
	list->top++;
	return;
}


void removeList(List* list, Element data) {
	int found = searchList(list, data);
	
	if (*(int*)(list->list[found])==*(int*)data) {
		free(list->list[found]);
		for (int i = found;i < list->top;i++) {
			list->list[i] = list->list[i + 1];
		}
		list->top--;
		list->list[list->top] = NULL;
	}
	else return;
}

void delList(List* list){
	free(list->list);
	free(list);
}
#endif
