#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true }bool;

#define ENDLESS 65535
#define MaxNum 100
typedef int Vertex;
typedef int WeightType;
typedef int Cost;
//typedef int Data;

typedef struct ENode* Edge;
struct ENode {
	Vertex v1, v2;
	WeightType weight;
	Cost cost;

};

typedef struct GNode* Graph;
struct GNode {
	int VertexCount;
	int EdgeCount;
	WeightType weight[MaxNum][MaxNum];
	Cost cost[MaxNum][MaxNum];
	Vertex start, end;
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
			graph->cost[i][j] = ENDLESS;
		}
	}

	return graph;
}

//插入边
void InsertEdge(Graph graph, Edge edge)
{
	graph->EdgeCount++;

	graph->weight[edge->v1][edge->v2] = edge->weight;
	graph->cost[edge->v1][edge->v2] = edge->cost;

	graph->weight[edge->v2][edge->v1] = edge->weight;
	graph->cost[edge->v2][edge->v1] = edge->cost;

	return;
}

Graph BuildGraph(void)
{
	int VertexCount, EdgeCount;
	printf("enter vertex count\n");
	scanf("%d", &VertexCount);
	Graph graph = CreatGraph(VertexCount);

	printf("enter start and end:\n");
	scanf("%d %d", &graph->start, &graph->end);

	printf("enter edge count\n");
	scanf("%d", &EdgeCount);

	Edge edge = (Edge)malloc(sizeof(struct ENode));
	printf("enter edge data:\n");
	for (int i = 0; i < EdgeCount; i++) {
		scanf("%d %d %d %d", &edge->v1, &edge->v2, &edge->weight,&edge->cost);
		InsertEdge(graph, edge);
	}

	return graph;
}

//-------------------------算法--------------------------------------------
Vertex FindMinDist(Graph graph, WeightType dist[], Vertex collected[])
{
	Vertex Next;
	WeightType MinDist = ENDLESS;

	for (int i = 0; i < graph->VertexCount; i++) {
		if (collected[i] == false && dist[i] < MinDist) {
			MinDist = dist[i];
			Next = i;
		}
	}

	if (MinDist < ENDLESS)
		return Next;
	else
		return false;
}

bool Dijikstra(Graph graph, WeightType dist[], Cost cost[], Vertex path[],Vertex start)
{
	Vertex collected[MaxNum];
	for (int i = 0; i < graph->VertexCount; i++) {
		collected[i] = false;
		dist[i] = graph->weight[start][i];
		cost[i] = graph->cost[start][i];
		if (dist[i] < ENDLESS)
			path[i] = start;
		else
			path[i] = -1;
	}

	dist[start] = cost[start] = 0;
	collected[start] = true;

	Vertex Next;
	while (1) {
		Next = FindMinDist(graph, dist, collected);
		if (Next == false)
			break;

		collected[Next] = true;
		for (int i = 0; i < graph->VertexCount; i++) {
			if (collected[i] == false && graph->weight[Next][i] < ENDLESS) {
				if (graph->weight[Next][i] < 0)
					return false;
				if (dist[Next] + graph->weight[Next][i] < dist[i]) {
					dist[i] = dist[Next] + graph->weight[Next][i];
					cost[i] = cost[Next] + graph->cost[Next][i];
					path[i] = Next;
				}

				else if (dist[Next] + graph->weight[Next][i] == dist[i]) {
					if (cost[Next] + graph->cost[Next][i] < cost[i]) {
						dist[i] = dist[Next] + graph->weight[Next][i];
						cost[i] = cost[Next] + graph->cost[Next][i];
						path[i] = Next;
					}
				}
			}
			
		}
	}

	return true;
}

void ShowPath(Vertex path[], Vertex end)
{
	if (path[end] < 0)
	{
		printf("path:%d", end);
		return;
	}
	else
	{
		ShowPath(path, path[end]);
		printf("-->%d", end);
	}
}
//-------------------------------------------------------------------------
int main(void)
{
	Graph graph = BuildGraph();

	WeightType* dist; Vertex* path; Cost* cost;
	dist = (WeightType*)malloc(sizeof(WeightType) * graph->VertexCount);
	cost = (Cost*)malloc(sizeof(Cost) * graph->VertexCount);
	path = (Vertex*)malloc(sizeof(Vertex) * graph->VertexCount);

	Dijikstra(graph, dist, cost, path, graph->start);

	putchar('\n');
	printf("dist:%d cost:%d\n", dist[graph->end], cost[graph->end]);
//	printf("path:");
	ShowPath(path, graph->end);

	return 0;
}

