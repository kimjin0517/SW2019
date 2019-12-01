#define _CRT_SECURE_NO_WARNINGS
#include"ArrayQ.h"
#include<stdio.h>
#include<stdlib.h>

typedef struct {
	char str[20];
}Name;

int main() {
	//variable

	char* s = NULL;
	Queue* c = NULL;
	Name* name = NULL;
	int swit, temp1=0,temp2=0;
	void* e = NULL;

	c = CreateQueue(100);
	name = (Name*)malloc(sizeof(Name) * 100);

	//main
	while (1) {
		printf("\nIn(0), out(1), exit(2) : ");
		scanf("%d", &swit);
		switch (swit) {
		case 0:
			printf("\nCustomer: ");
			scanf("%s", (name + (c->rear))->str);
			Enqueue(c, (name + (c->rear))->str);
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
		temp1 = c->front;
		temp2 = c->rear;
		printf("\nThe current status of queue : (");
		for (int i = temp1 ;i < temp2;i++) {
			if (i!=temp1) printf(", ");
			s = (char*)Dequeue(c);
			printf("%s", s);
			Enqueue(c, s);
		}
		printf(")\n\n");
	}

	return 0;

}










