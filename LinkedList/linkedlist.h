#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef LINKEDLIST
#define LINKEDLIST

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef void* Element;

typedef struct tlistnode {
	Element data;
	struct tlistnode* link;
}Node;

typedef struct {
	int count;
	Node* head;
	int (*compare)(Element item1, Element item2);
}List;

List* CreateList(int (*compare) (Element item1, Element item2)) {
	List* newlist = (List*)malloc(sizeof(List));
	if (newlist == NULL) return NULL;

	newlist->count = 0;
	newlist->head = NULL;
	newlist->compare = compare;
}

void insertList(List* plist, Node* pPre, Element data) {
	int* item;
	Node* newnode = (Node*)malloc(sizeof(Node));
	item = (int*)malloc(sizeof(int*));
	*item = *(int*)data;
	newnode->data = item;
	if (pPre == NULL) {
		newnode->link = plist->head;
		plist->head = newnode;
	}
	else {
		newnode->link = pPre->link;
		pPre->link = newnode;
	}
	plist->count++;
}

int searchList(List* plist, Node** ppPre, Node** ppLoc, Element data) {
	for (*ppPre = NULL, *ppLoc = plist->head;*ppLoc != NULL;*ppPre = *ppLoc, *ppLoc = (*ppLoc)->link) {
		if ((*plist->compare)(data, (*ppLoc)->data) == 0) return 1;
		else if ((*plist->compare)(data, (*ppLoc)->data) < 0) break;
	}
	return 0;
}




void addNode(List* plist, Element data) {
	Node* pPre = NULL, * pLoc = NULL;
	int found = searchList(plist, &pPre, &pLoc, data);

	if (found == 0) {
		insertList(plist, pPre, data);
	}

}

void delList(List* plist, Node* pPre, Node* pLoc) {
	if (pPre == NULL) {
		plist->head = pLoc->link;
	}
	else {
		pPre->link = pLoc->link;
	}
	free(pLoc);
	plist->count--;
}

void removeList(List* plist, Element data) {
	Node* pPre = NULL, * pLoc = NULL;
	int found = searchList(plist, &pPre, &pLoc, data);
	if (found == 1) {
		delList(plist, pPre, pLoc);
	}
}

void destroyList(List* plist) {
	Node* del = NULL, * next = NULL;
	for (del = plist->head; del != NULL;del = next) {
		next = del->link;
		free(del);
	}
	free(plist);
}

#endif