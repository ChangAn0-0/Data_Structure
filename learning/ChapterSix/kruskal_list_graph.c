#include "kruskal_lst.h"
//--------------------------图操作函数-----------------------------------
ListGraph CreatListGraph(int VertexCount)
{
	ListGraph listgraph = (ListGraph)malloc(sizeof(struct GNode));
	listgraph->VertexCount = VertexCount;
	listgraph->EdgeCount = 0;
	for (int i = 0; i < listgraph->VertexCount; i++) {
		listgraph->list[i].fristedge = NULL;
	}

	return listgraph;
}

void InsertEdge_ListGraph(ListGraph listgraph, Edge edge)
{
	AdjacencyNodePtr new;

	new = (AdjacencyNodePtr)malloc(sizeof(struct AdjacencyNode));
	new->weight = edge->weight;
	new->vertex = edge->v2;
	new->Next = listgraph->list[edge->v1].fristedge;
	listgraph->list[edge->v1].fristedge = new;

	new = (AdjacencyNodePtr)malloc(sizeof(struct AdjacencyNode));
	new->weight = edge->weight;
	new->vertex = edge->v1;
	new->Next = listgraph->list[edge->v2].fristedge;
	listgraph->list[edge->v2].fristedge = new;

	return;
}

ListGraph BuildListGraph(void)
{
	int VertexCount;
	printf("enter vertex count:\n");
	scnaf_s("%d", &VertexCount);

	ListGraph listgraph = CreatListGraph(VertexCount);

	printf("enter edge count:\n");
	scanf_s("%d", &listgraph->EdgeCount);
	if (listgraph->EdgeCount) {
		printf("enter edge data:\n");
		Edge edge = (Edge)malloc(sizeof(struct ENode));
		for (int i = 0; i < listgraph->EdgeCount; i++) {
			scanf_s("%d %d %d", &edge->v1, &edge->v2, &edge->weight);
			edge->v1--; edge->v2--;//输入从编号一开始
			InsertEdge_ListGraph(listgraph, edge);
		}
	}

	return listgraph;
}
//---------------------------------图操作函数结束-----------------------------------
//-------------------------------堆操作函数-----------------------------------------
HeapPtr CrertHeap(int Maxsize)
{
	HeapPtr heap = (HeapPtr)malloc(sizeof(struct Heap));
	heap->MaxSize = Maxsize;
	heap->Count = 0;
	heap->Data = (HeapElementType*)malloc(sizeof(HeapElementType) * (Maxsize + 1));
	heap->Data[0].weight = -1;

	return heap;
}

void InitializeMinHeap(ListGraph graph, HeapPtr heap)
{
	
	for (int i = 0; i < graph->VertexCount; i++) {
		for (AdjacencyNodePtr j = graph->list[i].fristedge; j; j = j->Next) {
			if (i < j->vertex) {
				heap->Data[heap->Count+1].v1 = i;
				heap->Data[heap->Count+1].v2 = j->vertex;
				heap->Data[heap->Count+1].weight = j->weight;
				heap->Count++;
			}
		}
	}

	for (int i = heap->Count / 2; i >= 0; i--) {
		PercDown_MinHeap(heap,i);
	}
	return;
}

void PercDown_MinHeap(HeapPtr heap, int p)
{
	int parent, child;
	
	HeapElementType temp = heap->Data[p];
	for (parent = p; parent * 2 < heap->Count; parent = child) {
		child = parent * 2;
		if (child != heap->Count && heap->Data[child].weight > heap->Data[child + 1].weight)
			child++;
		if (temp.weight <= heap->Data[child].weight)break;
		else
			heap->Data[parent] = heap->Data[child];
	}
	heap->Data[parent] = temp;
}

int GetMinEdge(HeapPtr heap)
{
	HeapElementType temp = heap->Data[1];
	heap->Data[1] = heap->Data[heap->Count];
	heap->Count--;
	PercDown_MinHeap(heap, 1);

	return temp.weight;
}
//-----------------------堆操作结束---------------------------------
//--------------------------并查集操作函数--------------------------
void InitializeVSet(SetType S, int N)
{
	for (int i = 0; i < N; i++) {
		S[i] = -1;
	}
}
void Union(SetType S, SetName Root1, SetName Root2)
{
	if (S[Root2] < S[Root1]) {
		S[Root2] += S[Root1];
		S[Root1] = Root2;
	}
	else {
		S[Root1] += S[Root2];
		S[Root2] = Root1;
	}
}
SetName Find(SetType S, ElementType X)
{
	if (S[X] < 0)
		return X;
	else
		return S[X] = Find(S, S[X]);
}
//----------------------并查集结束----------------------
bool CheckCycle(SetType VSet, Vertex v1, Vertex v2)
{
	Vertex root1, root2;

	root1 = Find(VSet, v1);
	root2 = Find(VSet, v2);

	if (root1 == root2) {
		return false;
	}
	else {
		Union(VSet, root1, root2);
		return true;
	}
}

int Kruskal(ListGraph graph)
{
	WeightType TotalWeight = 0;
	int ECount = 0, NextEdge = 0;
	SetType VSet;
	HeapPtr heap;

	InitializeVSet(VSet, graph->VertexCount);
	heap = CrertHeap(graph->EdgeCount);

	while (ECount < graph->VertexCount - 1) {
		NextEdge = GetMinEdge(heap);
		if (NextEdge < 0)break;

		if (CheckCycle(VSet, heap->Data[NextEdge].v1, heap->Data[NextEdge].v2) == true) {
			TotalWeight += heap->Data[NextEdge].weight;
			ECount++;
		}
	}

	if (ECount < graph->VertexCount - 1)
		TotalWeight = -1;
	
	return TotalWeight;
}



