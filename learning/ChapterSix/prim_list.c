#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef enum{false,true}bool;

#define MaxNum 100
#define ENDLESS 65535
typedef int Vertex;
typedef int WeightType;
typedef int DataType;

//定义边
typedef struct ENode* Edge;
struct ENode {
	Vertex vertex1, vertex2;
	WeightType weight;
};

//邻接表节点定义
typedef struct AdjacencyNode* AdjacencyNodePtr;
 struct AdjacencyNode {
	Vertex vertex;
	WeightType weight;
	AdjacencyNodePtr Next;
};

 //邻接表表头定义
// typedef struct AdjacencyHead* AdjacencyHeadPtr;
 struct AdjacencyHead {
	 AdjacencyNodePtr fristedge;
	 DataType data;
 };

 //图的定义
 typedef struct GNode* Graph;
 struct GNode {
	int VertexCount;
	int EdgeCount;
	struct AdjacencyHead list[MaxNum];
};

//创建图并初始化
Graph CreatGraph(void)
{
	int vertexnum;
	printf("enter vertex count:\n");
	if (scanf("%d", &vertexnum) && vertexnum>0) {
		Graph graph = (Graph)malloc(sizeof(struct GNode));
		if (!graph) {
			printf("error:%d", __LINE__);
			exit(EXIT_FAILURE);
		}

		graph->VertexCount = vertexnum;
		graph->EdgeCount = 0;
		printf("enter data:\n");
		for (int i = 0; i < graph->VertexCount; i++) {
			graph->list[i].fristedge = NULL;
			scanf("%d", &graph->list[i].data);
		}
		return graph;
	}
	else {
		printf("error:%d", __LINE__);
		exit(EXIT_FAILURE);
	}
}

//插入边
void InsertEdge(Graph graph, Edge edge)
{
	AdjacencyNodePtr new = (AdjacencyNodePtr)malloc(sizeof(struct AdjacencyNode));
	if (!new) {
		printf("error:%d", __LINE__);
		exit(EXIT_FAILURE);
	}
	new->weight = edge->weight;
	new->vertex = edge->vertex2;
	new->Next = graph->list[edge->vertex1].fristedge;
	graph->list[edge->vertex1].fristedge = new;

	//无向图
	new = (AdjacencyNodePtr)malloc(sizeof(struct AdjacencyNode));
	if (!new) {
		printf("error:%d", __LINE__);
		exit(EXIT_FAILURE);
	}
	new->weight = edge->weight;
	new->vertex = edge->vertex1;
	new->Next = graph->list[edge->vertex2].fristedge;
	graph->list[edge->vertex2].fristedge = new;

	return;
}

//图建立函数
Graph BuildGraph(void)
{
	Graph graph = CreatGraph();

	printf("enter edge count:\n");
	if (scanf("%d", &graph->EdgeCount) && graph->EdgeCount > 0) {
		printf("enter edge:\n");
		Edge edge = (Edge)malloc(sizeof(struct ENode));
		if (!edge) {
			printf("error:%d", __LINE__);
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i < graph->EdgeCount; i++) {
			scanf("%d %d %d", &edge->vertex1, &edge->vertex2, &edge->weight);
			InsertEdge(graph, edge);
		}
	}

	return graph;
}

//图输出---------------------------------------------------------------------
void GraphNodePrint(AdjacencyNodePtr fristedge)
{
	if (fristedge) {
		printf("-->顶点%d:权重%d", fristedge->vertex, fristedge->weight);
		GraphNodePrint(fristedge->Next);
	}
	return;
}

void ShowGraph(Graph graph)
{
	for (int i = 0; i < graph->VertexCount; i++) {
		printf("顶点%d", i);
		GraphNodePrint((graph->list[i]).fristedge);
		putchar('\n');
	}
}

//prim算法----------------------------------------------------------------------------------------------
Vertex FindMinDist(Graph graph, WeightType dist[])
{
	Vertex min;
	WeightType MinDist = ENDLESS;

	for (Vertex i = 0; i < graph->VertexCount; i++) {
		if (dist[i] != 0 && dist[i] < MinDist) {
			MinDist = dist[i];
			min = i;
		}
	}
	if (MinDist < ENDLESS) {
		return min;
	}
	else return false;
}

int Prim(Graph graph)
{
	WeightType dist[MaxNum];
	Vertex parent[MaxNum];

	for (int i = 0; i < graph->VertexCount; i++) {
		dist[i] = ENDLESS;
	}
	for (AdjacencyNodePtr i = graph->list[0].fristedge; i; i=i->Next) {
		dist[i->vertex] = i->weight;
	}

	WeightType sum = 0;
	int MinVertexCount = 0; 

	Graph Mst = CreatGraph();
	Edge E = (Edge)malloc(sizeof(struct ENode));

	dist[0] = 0;
	MinVertexCount++;
	parent[0] = -1;

	while (1) {
		Vertex min = FindMinDist(graph, dist);
		if (min == false)
			break;

		E->vertex1 = parent[min];
		E->vertex2 = min;
		E->weight = dist[min];
		InsertEdge(Mst, E);
		sum += dist[min];
		dist[min] = 0;
		MinVertexCount++;

		for (AdjacencyNodePtr i = graph->list[min].fristedge; i; i = i->Next) {
			if (dist[i->vertex] != 0 && i->weight < ENDLESS) {
				if (i->weight < dist[i->vertex]) {
					dist[i->vertex] = i->weight;
					parent[i->vertex] = min;
				}
			}
		}
	}
	if (MinVertexCount < graph->VertexCount)
		sum = false;
	else return sum;
}

int main(void)
{
	Graph graph = BuildGraph();
	ShowGraph(graph);

	return 0;
}
