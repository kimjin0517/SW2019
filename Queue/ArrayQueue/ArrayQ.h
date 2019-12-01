#define _CRT_SECURE_NO_WARNINGS
#ifndef ARRAYQ_H
#define	ARRAYQ_H

#include<stdio.h>
#include<stdlib.h>
typedef void* Element;

typedef struct {
	Element* queue;
	int size;
	int front, rear;
}Queue;

Queue* CreateQueue(int size) {
	Queue* q = NULL;
	q = (Queue*)malloc(sizeof(Queue));
	if (q == NULL) return NULL;

	q->queue = (Element*)malloc(sizeof(Element) * size);
	if (q->queue == NULL) {
		free(q);
		return NULL;
	}
	q->size = size;
	q->front = q->rear = 0;

	return q;
}

void Enqueue(Queue* q, Element item) {
	if (IsFullQueue(q)) {
		return;
	}
	else {
		q->rear = (q->rear + 1) % q->size;
		q->queue[q->rear] = item;
	}
}

Element Dequeue(Queue* q) {
	Element item;
	if (IsEmptyQueue(q)) {
		return NULL;
	}
	else {
		return q->queue[++q->front];
	}

}

int IsFullQueue(Queue* q) {
	if ((q->rear) % q->size == q->front && q->front != q->rear) return 1;
	else return 0;
}
int IsEmptyQueue(Queue* q) {
	if (q->front == q->rear) return 1;
	else return 0;
}

void DestroyQueue(Queue* q) {
	free(q->queue);
	free(q);
}

#endif