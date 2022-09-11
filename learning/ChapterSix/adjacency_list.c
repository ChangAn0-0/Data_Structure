#include <stdlib.h>

#define MaxVertexNum 100
typedef int Vertex;
typedef int WeightType;
typedef struct data DataType;
struct data {
	char c;
};

//边的定义
typedef struct ENode* Edge;
struct ENode {
	Vertex v1, v2;
	WeightType weight;
};

//邻接表节点
typedef struct Node* AdjacencyNode;
struct Node {
	Vertex subscript;
	WeightType weight;
	AdjacencyNode Next;
};

//顶点表头定义
typedef struct Vnode {
	AdjacencyNode head;
	DataType Data;
}AdjacencyList[MaxVertexNum];

//图定义
typedef struct GNode* Graph;
struct GNode {
	int VertexCount;
	int WeightCount;
	AdjacencyList list;
};

//初始化图
Graph CreatGraph(int vertexnum)
{
	if (vertexnum == 0) {
		printf("vertexnum is null");
		return NULL;
	}

	Graph graph = (Graph)malloc(sizeof(struct GNode));
	graph->VertexCount = vertexnum;
	graph->WeightCount = 0;

	for (int i = 0; i < vertexnum; i++) {
		graph->list[i].head = NULL;
	}

	return graph;
}

//插入边
void InsertEdge(Graph graph, Edge edge)
{
	AdjacencyNode new = (AdjacencyNode)malloc(sizeof(struct Node));
	new->weight = edge->weight;
	new->subscript = edge->v2;
	new->Next = graph->list[edge->v1].head;
	graph->list[edge->v1].head = new;

	//无向图
	AdjacencyNode new1 = (AdjacencyNode)malloc(sizeof(struct Node));
	new1->weight = edge->weight;
	new1->subscript = edge->v1;
	new1->Next = graph->list[edge->v2].head;
	graph->list[edge->v2].head = new1;
}

Graph BuildGrape(void)
{
	Graph graph;
	int vertexnum;
	Edge edge;

	scanf("%d", &vertexnum);
	graph = CreatGraph(vertexnum);

	sacnf("%d", &(graph->WeightCount));
	if (graph->WeightCount == 0) {
		printf("edge count is null");
	}
	else {
		edge = (Edge)malloc(sizeof(struct ENode));
		for (int i = 0; i < graph->WeightCount; i++) {
			scanf("%d %d %d", edge->v1, edge->v2, edge->weight);
			InsertEdge(graph,edge);
		}
	}

	for (int i = 0; i < graph->VertexCount; i++) {
		scanf("%c", &(((graph->list[i]).Data).c));
	}

	return graph;
}