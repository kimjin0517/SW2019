#define _CRT_SECURE_NO_WARNINGS
#include"LinkedQ.h"
#include<stdio.h>
#include<stdlib.h>

typedef struct {
	char str[20];
}Name;

int main(){
	//variable

	char* s = NULL;
	Queue* c= NULL;
	QueueNode* fnode=NULL, * rnode=NULL;
	Name* name = NULL;
	int swit,i=0;


	c = CreateQueue();
	name = (Name*)malloc(sizeof(Name) * 100);
	
	//main
	while (1) {
		printf("\nIn(0), out(1), exit(2) : ");

		scanf("%d", &swit);
		switch (swit) {
		case 0:
			printf("\nCustomer: ");
			scanf("%s", (name+(i%100))->str);
			Enqueue(c, (name + ((i++)%100))->str);
			break;
		case 1:
			if (Dequeue(c) == NULL) {
				printf("Error: no customer to dequeue! Program down...");
				return 0;
			}
			else break;
		case 2:
			free(name);
			DestroyQueue(c);
			return 0;
		default:
			printf("Error!! You must put 0 or 1 or 2... Program down...");
			free(name);
			DestroyQueue(c);
			return 0;
		}
		
		fnode = c->front;
		rnode = c->rear;
		printf("\nThe current status of queue : (");
		for (QueueNode *node1=fnode, *node2; node1 != rnode;) {
			if (c->count == 0) break;
			node2 = node1->next;
			if (node1!=rnode && node1!=fnode) printf(", ");
			s = (char*)Dequeue(c);
			printf("%s", s);
			Enqueue(c, s);
			node1 = node2;
		}
		if (c->count!=1) {
			printf(", ");
			s = (char*)Dequeue(c);
			printf("%s", s);
			Enqueue(c, s);
		}
		else {
			s = (char*)Dequeue(c);
			printf("%s", s);
			Enqueue(c, s);
		}
		printf(")\n\n");
	}

	return 0;

}