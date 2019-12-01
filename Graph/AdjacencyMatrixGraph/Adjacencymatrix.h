#define _CRT_SECURE_NO_WARNINGS
#include"voidQueue.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//구조체 설정
typedef struct {
	int cnt;
	struct vertex* first;
	int Arc[20][20];
	int processed[20];
	int (*compare)(void* data1, void* data2);
}Graph;

typedef struct vertex {
	struct vertex* pNextVertex;
	void* data;
	int inDegree;
	int outDegree;
}Vertex;


//벌텍스 만들기
Vertex* CreateVertex(void* data) {
	Vertex* newVertex = NULL;
	newVertex = (Vertex*)malloc(sizeof(Vertex));
	if (!newVertex) return NULL;

	newVertex->data = data;
	newVertex->inDegree = 0;
	newVertex->outDegree = 0;
	newVertex->pNextVertex = NULL;
	return newVertex;
}

//그래프 만들기
Graph* CreatGraph(void* data, int (*compare)(void* data1, void* data2)) {
	Graph* newGraph;
	int i = 0;
	int j = 0;

	newGraph = (Graph*)malloc(sizeof(Graph));
	if (!newGraph) return NULL;
	newGraph->cnt = 1;
	newGraph->compare = compare;
	newGraph->first = CreateVertex(data);
	for (i = 0;i < 20;i++) {
		for (j = 0;j < 20;j++) {
			newGraph->Arc[i][j] = 0;
		}
		newGraph->processed[i] = 0;
	}

	return newGraph;
}


//인터페이스
int LinkVertex(Graph* graph, void* start, void* destination) {
	Vertex* Loc1 = NULL;
	Vertex* Loc2 = NULL;
	Vertex* tmp = NULL;
	Vertex* tmp2 = NULL;
	int i = 0;
	int j = 0;


	//출발지 목적지 존재여부 확인 후 벌텍스 생성
	for (tmp = graph->first;tmp != NULL;tmp = tmp->pNextVertex) {
		if (graph->compare(tmp->data, start) == 0) {
			Loc1 = tmp;
			break;
		}
		tmp2 = tmp;
		i++;
	}
	if (Loc1 == NULL) {
		Loc1 = CreateVertex(start);
		tmp2->pNextVertex = Loc1;
		graph->cnt++;
	}
	for (tmp = graph->first;tmp != NULL;tmp = tmp->pNextVertex) {
		if (graph->compare(tmp->data, destination) == 0) {
			Loc2 = tmp;
			break;
		}
		tmp2 = tmp;
		j++;
	}
	if (Loc2 == NULL) {
		Loc2 = CreateVertex(destination);
		tmp2->pNextVertex = Loc2;
		graph->cnt++;
	}

	graph->Arc[i][j] = 1;

	Loc1->outDegree++;
	Loc2->inDegree++;
}

void DepthFirstTraversal(Graph* graph, int n, void (*process)(void* data)) {
	Vertex* tmp1 = NULL;
	int i = n;
	int j = 0;

	tmp1 = graph->first;
	if (n != 0) {
		for (int k = 0;k < n;k++) {
			tmp1 = tmp1->pNextVertex;
		}
	}

	if (graph->processed[i] == 1) return;
	(*process)(tmp1->data);
	graph->processed[i] = 1;

	for (j = 0;j < graph->cnt;j++) {
		if (graph->processed[j] == 0 && graph->Arc[i][j] == 1) DepthFirstTraversal(graph, j, process);
	}
}

void BreadthFirstTraversal(Queue* q, Graph* graph, int n, void (*process)(void* data)) {
	Vertex* tmp1 = NULL;
	int i = n;
	int j = 0;
	int ck = 0;

	tmp1 = graph->first;
	if (n != 0) {
		for (int k = 0;k < n;k++) {
			tmp1 = tmp1->pNextVertex;
		}
	}
	process(tmp1->data);
	for (int k = 0;k < graph->cnt;k++) {
		if (graph->Arc[i][k] == 1) {
			ck = 1;
			break;
		}
	}
	if (ck == 0) return;
	for (j = 0; j < graph->cnt; j++) {
		if (graph->Arc[i][j] == 1 && graph->processed[j] == 0) {
			graph->processed[j] = 1;
			Enqueue(q, j);
		}
	}
	BreadthFirstTraversal(q, graph, Dequeue(q), process);

}

//process 0으로 복귀
void Process0(Graph* graph) {
	for (int i = 0;i < graph->cnt;i++) graph->processed[i] = 0;
}

