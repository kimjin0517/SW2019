#define _CRT_SECURE_NO_WARNINGS
#include"intQueue.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//구조체 설정
typedef struct {
	int cnt;
	struct vertex* first;
	int (*compare)(void* data1, void* data2);
}Graph;

typedef struct vertex {
	struct vertex* pNextVertex;
	void* data;
	int inDegree;
	int outDegree;
	int processed;
	struct arc* pArc;
}Vertex;

typedef struct arc {
	struct vertex* destination;
	struct arc* pNextArc;
	int weight;
}Arc;

//벌텍스 만들기
Vertex* CreateVertex(void* data) {
	Vertex* newVertex = NULL;
	newVertex = (Vertex*)malloc(sizeof(Vertex));
	if (!newVertex) return NULL;

	newVertex->data = data;
	newVertex->inDegree = 0;
	newVertex->outDegree = 0;
	newVertex->pArc = NULL;
	newVertex->pNextVertex = NULL;
	newVertex->processed = 0;
	return newVertex;
}

//그래프 만들기
Graph* CreatGraph(void* data, int (*compare)(void* data1, void* data2)) {
	Graph* newGraph;
	newGraph = (Graph*)malloc(sizeof(Graph));
	if (!newGraph) return NULL;

	newGraph->cnt = 1;
	newGraph->compare = compare;
	newGraph->first = CreateVertex(data);
	return newGraph;
}

//아크만들기
Arc* CreateArc(Vertex* vertex, Arc* arc, int weight) {
	Arc* newArc = (Arc*)malloc(sizeof(Arc));
	if (!newArc) return NULL;
	newArc->destination = vertex;
	newArc->pNextArc = arc;
	newArc->weight = weight;

	return newArc;
}

//인터페이스
int LinkVertex(Graph* graph, void* start, void* destination, int weight) {
	Vertex* Loc1 = NULL;
	Vertex* Loc2 = NULL;
	Vertex* tmp = NULL;
	Vertex* tmp2 = NULL;
	Arc* Loc3 = NULL;
	Arc* Loc4 = NULL;
	Arc* newArc;

	//출발지 목적지 존재여부 확인 후 벌텍스 생성
	for (tmp = graph->first;tmp != NULL;tmp = tmp->pNextVertex) {
		if (graph->compare(tmp->data, start) == 0) Loc1 = tmp;
		tmp2 = tmp;
	}
	if (Loc1 == NULL) {
		Loc1 = CreateVertex(start);
		tmp2->pNextVertex = Loc1;
		graph->cnt++;
	}
	for (tmp = graph->first;tmp != NULL;tmp = tmp->pNextVertex) {
		if (graph->compare(tmp->data, destination) == 0) Loc2 = tmp;
		tmp2 = tmp;
	}
	if (Loc2 == NULL) {
		Loc2 = CreateVertex(destination);
		tmp2->pNextVertex = Loc2;
		graph->cnt++;
	}

	//아크 생성
	if (Loc1->outDegree == 0) {//벌텍스 아웃디그리가 없는 경우
		Loc1->pArc = CreateArc(Loc2, NULL, weight);
	}
	else {//벌텍스의 아웃디그리가 존재하는 경우
		for (Loc3 = Loc1->pArc;Loc3 != NULL;Loc3 = Loc3->pNextArc) {
			if (graph->compare(Loc3->destination->data, destination) < 0) break;
			Loc4 = Loc3;
		}

		if (Loc4 == NULL) {//가장 작은 경우
			newArc = CreateArc(Loc2, Loc1->pArc, weight);
			Loc1->pArc = newArc;
		}
		else if (Loc3 == NULL) {//가장 큰 경우
			Loc4->pNextArc = CreateArc(Loc2, NULL, weight);
		}
		else {//아닌경우
			newArc = CreateArc(Loc2, Loc4->pNextArc, weight);
			Loc4->pNextArc = newArc;
		}
	}
	Loc1->outDegree++;
	Loc2->inDegree++;
}

void DepthFirstTraversal(Vertex* root, void (*process)(void* data)) {
	Arc* arc = NULL;
	if (root->processed) return;
	(*process)(root->data);
	root->processed = 1;
	for (arc = root->pArc; arc != NULL; arc = arc->pNextArc) {
		if (!arc->destination->processed) DepthFirstTraversal(arc->destination, process);
	}
}

void BreadthFirstTraversal(Queue* q, Vertex* root, void (*process)(void* data)) {
	Arc* arc = NULL;
	process(root->data);
	if (root->pArc == NULL) return;
	for (arc = root->pArc; arc != NULL; arc = arc->pNextArc) {
		if (arc->destination->processed == 0) {
			arc->destination->processed = 1;
			Enqueue(q, arc->destination);
		}
	}
	BreadthFirstTraversal(q, (Vertex*)Dequeue(q), process);
}

//process 0으로 복귀
void Process0(Vertex* root) {
	Arc* arc = NULL;
	if (root->processed == 0) return;
	root->processed = 0;
	for (arc = root->pArc; arc != NULL; arc = arc->pNextArc) {
		if (arc->destination->processed == 1) Process0(arc->destination);
	}
}

int processedcheck(Vertex* vertex) {
	Vertex* tmp;
	for (tmp = vertex;tmp != NULL;tmp = tmp->pNextVertex) if (tmp->processed == 0) return 0;
	return 1;
}

void MinimunSpanningTree(Vertex* vertex) {
	Vertex* Vtmp1 = NULL;
	Arc* Atmp1 = NULL;
	Vertex* Loc1 = NULL;
	Vertex* Loc2 = NULL;
	int wt = 10000;

	vertex->processed = 1;

	if (processedcheck(vertex) == 1) return;

	for (Vtmp1 = vertex;Vtmp1 != NULL;Vtmp1 = Vtmp1->pNextVertex) {
		if (Vtmp1->processed == 1) {
			for (Atmp1 = Vtmp1->pArc; Atmp1 != NULL; Atmp1 = Atmp1->pNextArc) {
				if (Atmp1->weight < wt && Atmp1->destination->processed == 0) {
					wt = Atmp1->weight;
					Loc1 = Vtmp1;
					Loc2 = Atmp1->destination;
				}
			}
		}
	}
	Loc2->processed = 1;
	printf("%c %c\n", *(char*)(Loc1->data), *(char*)(Loc2->data));
	MinimunSpanningTree(vertex);
}

int choose(int* distance, int start, int n, int* found) {
	int i = 0;
	int tmp = start;
	int dis = 10000;
	for (i = 0;i < n;i++) {
		if (*(distance + i) < dis && *(found + i) == 0) {
			dis = *(distance + i);
			tmp = i;
		}
	}
	return tmp;
}

int cost(int a, int b, Graph* graph) {
	Vertex* tmp = graph->first;
	Arc* arc = NULL;
	Vertex* Loc1;
	Vertex* Loc2;

	for (int i = 0;i < a;i++) {
		tmp = tmp->pNextVertex;
	}
	Loc1 = tmp;
	tmp = graph->first;

	for (int i = 0;i < b;i++) {
		tmp = tmp->pNextVertex;
	}
	Loc2 = tmp;

	for (arc = Loc1->pArc;arc != NULL;arc = arc->pNextArc) {
		if ((graph->compare)(arc->destination->data, Loc2->data) == 0) return arc->weight;
	}
	return 10000;
}

void ShortestPath(Graph* graph, void* data) {
	int i, u, w, v = 0;
	int a = 0;
	int* found = NULL;
	int* distance = NULL;
	Vertex* tmp = graph->first;
	int n = graph->cnt;
	found = (int*)malloc(sizeof(int) * n);
	distance = (int*)malloc(sizeof(int) * n);

	for (i = 0;i < n;i++) {
		if (graph->compare(data, tmp->data) == 0) v = i;
		*(found + i) = 0;
		*(distance + i) = 10000;
		tmp = tmp->pNextVertex;
	}

	*(found + v) = 1;
	*(distance + v) = 0;

	for (i = 0;i < n - 1;i++) {
		u = choose(distance, v, n, found);
		*(found + u) = 1;
		for (w = 0;w < n;w++) {
			a = cost(u, w, graph);
			if (*(found + w) == 0 && ((*(distance + u)) + a) < *(distance + w))* (distance + w) = *(distance + u) + a;

		}
	}
	tmp = graph->first;
	for (i = 0;i < n;i++) {
		if (i == v) {
			tmp = tmp->pNextVertex;
			continue;
		}
		printf("%c %c %d\n", *(char*)data, *(char*)tmp->data, *(distance + i));
		tmp = tmp->pNextVertex;
	}
	return;
}