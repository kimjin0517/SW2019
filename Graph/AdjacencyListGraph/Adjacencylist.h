#define _CRT_SECURE_NO_WARNINGS
#include"voidQueue.h"
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

	newGraph->cnt = 0;
	newGraph->compare = compare;
	newGraph->first = CreateVertex(data);
	return newGraph;
}

//아크만들기
Arc* CreateArc(Vertex* vertex, Arc* arc) {
	Arc* newArc = (Arc*)malloc(sizeof(Arc));
	if (!newArc) return NULL;
	newArc->destination = vertex;
	newArc->pNextArc = arc;

	return newArc;
}

//인터페이스
int LinkVertex(Graph* graph, void* start, void* destination) {
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

	}
	for (tmp = graph->first;tmp != NULL;tmp = tmp->pNextVertex) {
		if (graph->compare(tmp->data, destination) == 0) Loc2 = tmp;
		tmp2 = tmp;
	}
	if (Loc2 == NULL) {
		Loc2 = CreateVertex(destination);
		tmp2->pNextVertex = Loc2;
	}

	//아크 생성
	if (Loc1->outDegree == 0) {//벌텍스 아웃디그리가 없는 경우
		Loc1->pArc = CreateArc(Loc2, NULL);
	}
	else {//벌텍스의 아웃디그리가 존재하는 경우
		for (Loc3 = Loc1->pArc;Loc3 != NULL;Loc3 = Loc3->pNextArc) {
			if (graph->compare(Loc3->destination->data, destination) < 0) break;
			Loc4 = Loc3;
		}

		if (Loc4 == NULL) {//가장 작은 경우
			newArc = CreateArc(Loc2, Loc1->pArc);
			Loc1->pArc = newArc;
		}
		else if (Loc3 == NULL) {//가장 큰 경우
			Loc4->pNextArc = CreateArc(Loc2, NULL);
		}
		else {//아닌경우
			newArc = CreateArc(Loc2, Loc4->pNextArc);
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

int compareChar(void* data1, void* data2) {
	int a = (*(char*)data1) - (*(char*)data2);
	return a;
}

void process(void* data) {
	printf("%c ", *(char*)data);
}