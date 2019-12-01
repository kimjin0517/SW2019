#define _CRT_SECURE_NO_WARNINGS
#include"Adjacencymatrix.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int compareChar(void* data1, void* data2) {
	int a = (*(char*)data1) - (*(char*)data2);
	return a;
}

void process(void* data) {
	printf("%c ", *(char*)data);
}

int main() {
	Graph* graph;
	char first;
	char* s[100];
	int i = 0;
	Queue* q = CreateQueue();
	FILE* f1 = fopen("input1.txt","r");
	if (f1 == NULL) return 1;

	printf("input : \n");
	fscanf(f1, "%c\n", &first);
	graph = CreatGraph(&first, compareChar);
	printf("%c\n", first);

	while (fscanf(f1, "%c %c\n", &s[i++], &s[i++]) != EOF) {
		LinkVertex(graph, &s[i - 1], &s[i - 2]);
		printf("%c %c\n", s[i - 1], s[i - 2]);
	}

	printf("\nDepthFirstTraversal : ");
	DepthFirstTraversal(graph, 0, process);
	Process0(graph);
	printf("\nBreadthFirstTraversal : ");
	BreadthFirstTraversal(q, graph, 0, process);

	fclose(f1);
	DestroyQueue(q);

	return 0;
}

