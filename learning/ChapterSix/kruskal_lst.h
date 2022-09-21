#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef enum{false,true} bool;

//----------------ͼ����----------------------
#define MaxNum 100
#define ENDLESS 65535
typedef int Vertex;
typedef int WeightType;

typedef struct ENode* Edge;
struct ENode {
	Vertex v1, v2;
	WeightType weight;
};

typedef struct AdjacencyNode* AdjacencyNodePtr;
struct AdjacencyNode {
	Vertex vertex;
	WeightType weight;
	AdjacencyNodePtr Next;
};

struct AdjacencyHeadList {
	AdjacencyNodePtr fristedge;
};

typedef struct GNode* ListGraph;
struct GNode {
	int VertexCount;
	int EdgeCount;
	struct AdjacencyHeadList list[MaxNum];
};

ListGraph CreatListGraph(int VertexCount);
void InsertEdge_ListGraph(ListGraph graph, Edge edge);
ListGraph BuildListGraph(void);
//-----------------------ͼ�������-----------------------------
//----------------------�Ѷ���--------------------------------
typedef struct Heap* HeapPtr;
typedef struct ENode HeapElementType;
struct Heap {
	HeapElementType* Data;
	int MaxSize;
	int Count;
};

HeapPtr CrertHeap(int Maxsize);
void InitializeMinHeap(ListGraph graph, HeapPtr heap);
void PercDown_MinHeap(HeapPtr heap, int p);
int GetMinEdge(HeapPtr heap);
//------------------�Ѷ������---------------------
//-------------------���鼯------------------------
typedef Vertex ElementType;
typedef Vertex SetName;
typedef ElementType SetType[MaxNum];

void InitializeVSet(SetType S, int N);
void Union(SetType S, SetName Root1, SetName Root2);
SetName Find(SetType S, ElementType X);
//--------------------���鼯����--------------------


