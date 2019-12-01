#define _CRT_SECURE_NO_WARNINGS
#include"Adjacencyweightlist.h"
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
	//변수 선언
	Graph* graph = NULL;
	char first;
	char s[100];
	int i = 0;
	int weight=0;
	FILE* f1 = fopen("input2.txt", "r");
	if (f1 == NULL) return 1;
	printf("input : \n");
	fscanf(f1,"%c\n", &first);
	printf("%c\n", first);
	graph = CreatGraph(&first,compareChar);
	while (fscanf(f1, "%c %c %d\n", &s[i++], &s[i++],&weight) != EOF) {
		LinkVertex(graph, &s[i - 1], &s[i - 2], weight);
		printf("%c %c %d\n", s[i-1], s[i-2], weight);
	}
	printf("\nMinimumSpanningTree :\n\n");
	MinimunSpanningTree(graph->first);
	Process0(graph->first);
	printf("\nShortestPath from A :\n\n");
	ShortestPath(graph, &first);

	return 0;
	fclose(f1);
}


