#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true }bool;

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

//Djiktra算法
Vertex FindMinDist(Graph graph, WeightType dist[],Vertex collected[])
{
	Vertex nextvertex;
	WeightType MinDist = ENDLESS;

	for (int i = 0; i < graph->VertexCount; i++) {
		if (collected[i] == false && dist[i] < MinDist) {
			MinDist = dist[i];
			nextvertex = i;
		}
	}
	if (MinDist < ENDLESS)
		return nextvertex;
	else
		return false;
}

bool Djiktra(Graph graph, Vertex path[], WeightType dist[], Vertex start)
{
	Vertex collected[MaxNum];
	Vertex nextvertex;

	for (int i = 0; i < graph->VertexCount; i++) {
		dist[i] = graph->weight[start][i];
		if (dist[i] < ENDLESS)
			path[i] = start;
		else
			path[i] = -1;
		collected[i] = false;
	}

	dist[start] = 0;
	collected[start] = true;

	while (1) {
		nextvertex = FindMinDist(graph, dist, collected); 
		if (nextvertex == false)
			break;

		collected[nextvertex] = true;

		for (int i = 0; i < graph->VertexCount; i++) {
			if (collected[i] == false && graph->weight[nextvertex][i] < ENDLESS)
				if (graph->weight[nextvertex][i] < 0)
					return false;
				if (dist[nextvertex] + graph->weight[nextvertex][i] < dist[i]) {
					dist[i] = dist[nextvertex] + graph->weight[nextvertex];
					path[i] = nextvertex;
				}
		}
	}

	return true;
}

//Floyd算法
bool Floyd(Graph graph, WeightType D[][MaxNum], Vertex path[][MaxNum])
{
	for (int i = 0; i < graph->VertexCount; i++) {
		for (int j = 0; j < graph->VertexCount; j++) {
			path[i][j] = -1;
			D[i][j] = graph->weight[i][j];
		}
	}

	for (int k = 0; k < graph->VertexCount; k++) {
		for (int i = 0; i < graph->VertexCount; i++) {
			for (int j = 0; j < graph->VertexCount; j++) {
				if (D[i][k] + D[k][j] < D[i][j]){
					D[i][j] = D[i][k] + D[k][j];
					if (i == j && D[i][j] < 0)
						return false;
					path[i][j] = k;
				 }
			}
		}
	}

	return true;
}
