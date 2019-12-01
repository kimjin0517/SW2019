#define _CRT_SECURE_NO_WARNINGS
#include"Arraylist.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int compareInt(void* argu1, void* argu2)
{
	return *(int*)argu1 - *(int*)argu2;
}

int compareStr(void* argu1, void* argu2)
{
	return strcmp((char*)argu1, (char*)argu2);
}


int main() {
	List* list;
	int swit = 0;
	int* item = (int*)malloc(sizeof(int*));
	list = CreateList(1000,compareInt);
	
	while (1) {
		printf("\nIn(0), Search(1), Out(2), Exit(3)  : ");
		scanf("%d", &swit);

		if (swit == 0) {
			printf("Input : ");
			scanf("%d", item);
			insertList(list, item);
			
		}
		else if (swit == 1) {
			printf("Search : ");
			scanf("%d", item);
			if (searchList(list,item)==-1) printf("My List does not have %d.\n", *(int*)item);
			else if (*(int*)(list->list[searchList(list, item)])==*(int*)item)printf("My List has %d.\n", *(int*)item);
			else printf("My List does not have %d.\n", *(int*)item);
		}
		else if (swit == 2) {
			printf("Out: ");
			scanf("%d", item);
			if (searchList(list, item) == -1) printf("My List does not have %d.\n", *(int*)item);
			else if(*(int*)list->list[searchList(list, item)] != *(int*)item) printf("My List does not have %d.\n", *(int*)item);
			else {
				removeList(list, item);
				printf("%d was removed.\n", *(int*)item);
			}
		}
		else if (swit == 3) {
			delList(list);
			return 0;
		}
		printf("The current status of List : ");
		for (int i = 0;i < list->top;i++) {
			printf("%d, ", *(int*)(list->list[i]));
		}
		printf("\b\b \n");
	}


	return 0;
}