#define _CRT_SECURE_NO_WARNINGS
#ifndef LINKEDQ_H
#define	LINKEDQ_H
#include<stdio.h>
#include<stdlib.h>

typedef void* Element;

typedef struct tQueueNode {
	Element data;
	struct tQueueNode* next;
} QueueNode;

typedef struct {
	int count;
	QueueNode* front, * rear;
} Queue;

Queue* CreateQueue() {
	Queue* q = NULL;
	q = (Queue*)malloc(sizeof(Queue));
	if (q == NULL) return NULL;
	q->count = 0;
	q->front = NULL;
	q->rear = NULL;
}

int IsEmptyQueue(Queue* q) {
	if (q->front == q->rear && q->front == NULL) return 1;
	else return 0;
}

void Enqueue(Queue* q, Element item) {
	QueueNode* node = NULL;
	node = (QueueNode*)malloc(sizeof(QueueNode));
	if (node == NULL) return;
	node->data = item;
	node->next = NULL;
	if (q->count == 0) {
		q->front = q->rear = node;
	}
	else {
		(q->rear)->next = node;
		q->rear = node;
	}
	q->count++;
}
Element Dequeue(Queue* q) {
	QueueNode* node = NULL;
	Element item = 0;
	if (q->count == 0) return NULL;

	node = q->front;
	item = node->data;

	if (q->count == 1) q->front = q->rear = NULL;
	else q->front = node->next;

	free(node);
	q->count--;

	return item;
}

void DestroyQueue(Queue* q)
{
	QueueNode* node1 = NULL, * node2 = NULL;
	for (node1 = q->front; node1 != NULL; node1 = node2) {
		node2 = node1->next;
		free(node1);
	}
	q->count = 0;
	q->front = q->rear = NULL;
	free(q);
}

#endif