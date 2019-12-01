#define _CRT_SECURE_NO_WARNINGS
#include"Adjacencylist.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
	Graph* graph;
	char first;
	char* s[100];
	int i = 0;
	Queue* q = CreateQueue();
	FILE* f1 = fopen("input1.txt","r");
	if (f1 == NULL) return 0;
	printf("input : \n");
	fscanf(f1,"%c\n", &first);
	graph = CreatGraph(&first,compareChar);
	printf("%c\n",first);

	while (fscanf(f1, "%c %c\n", &s[i++], &s[i++])!=EOF) {
		LinkVertex(graph, &s[i - 1], &s[i - 2]);
		printf("%c %c\n", s[i - 1], s[i - 2]);
	}

	printf("\nDepthFirstTraversal : ");
	DepthFirstTraversal(graph->first, process);
	Process0(graph->first);
	printf("\nBreadthFirstTraversal : ");
	BreadthFirstTraversal(q, graph->first, process);

	fclose(f1);
	DestroyQueue(q);

	return 0;
}

