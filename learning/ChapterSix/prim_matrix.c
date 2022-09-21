#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef enum{false,true}bool;

#define ENDLESS 65535
#define MaxNum 100
typedef int Vertex;
typedef int WeightType;
typedef int Data;

typedef struct ENode* Edge;
struct ENode {
	Vertex v1, v2;
	WeightType weight;
};

typedef struct GNode* Graph;
struct GNode {
	int VertexCount;
	int EdgeCount;
	WeightType weight[MaxNum][MaxNum];
	Data data[MaxNum];
};

//初始化图
Graph CreatGraph(int VertexCount)
{
	Graph graph = (Graph)malloc(sizeof(struct GNode));
	graph->VertexCount = VertexCount;
	graph->EdgeCount = 0;
	for (int i = 0; i < graph->VertexCount; i++) {
		for (int j = 0; j < graph->VertexCount; j++) {
			graph->weight[i][j] = ENDLESS;
		}
	}

	return graph;
}

//插入边
void InsertEdge(Graph graph, Edge edge)
{
	graph->EdgeCount++;

	graph->weight[edge->v1][edge->v2] = edge->weight;
	graph->weight[edge->v2][edge->v1] = edge->weight;
	
	return;
}

Graph BuildGraph(void)
{
	int VertexCount, EdgeCount;
	printf("enter vertex count\n");
	scanf("%d", &VertexCount);

	Graph graph = CreatGraph(VertexCount);
	printf("enter edge count\n");
	scanf("%d", &EdgeCount);

	Edge edge = (Edge)malloc(sizeof(struct ENode));
	printf("enter edge data:\n");
	for (int i = 0; i < EdgeCount; i++) {
		scanf("%d %d %d", &edge->v1, &edge->v2, &edge->weight);
		InsertEdge(graph, edge);
	}

	return graph;
}


//prim算法
Vertex FindMinDist(Graph graph,WeightType dist[])
{
	Vertex min;
	WeightType MinDist = ENDLESS;
	for (int i = 0; i < graph->VertexCount; i++) {
		if (dist[i] != 0 && dist[i] < MinDist) {
			MinDist = dist[i];
			min = i;
		}
	}
	if (MinDist == ENDLESS)
		return false;
	else
		return min;
}

WeightType Prim(Graph graph)
{
	WeightType sum = 0;
	int Count = 0;
	WeightType dist[MaxNum];
	Vertex parent[MaxNum];

	for (int i = 0; i < graph->VertexCount; i++) {
		dist[i] = graph->weight[0][i];
		parent[i] = 0;
	}

	dist[0] = 0;
	parent[0] = -1;
	Count++;

	while (1) {
		Vertex MinDistVertex = FindMinDist;
		if (MinDistVertex == false) {
			break;
		}

		sum += dist[MinDistVertex];
		dist[MinDistVertex] = 0;
		Count++;

		for (int i = 0; i < graph->VertexCount; i++) {
			if (dist[i] != 0 && graph->weight[MinDistVertex][i] < dist[i]) {
				dist[i] = graph->weight[MinDistVertex][i];
				parent[i] = MinDistVertex;
			}
		}

	}
	if (Count < graph->VertexCount) {
		sum = false;
	}

	return sum;
}

int main(void)
{
	return 0;
}


