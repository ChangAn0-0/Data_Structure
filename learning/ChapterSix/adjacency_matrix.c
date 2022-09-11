#include <stdio.h>
#include <stdlib.h>

#define MAXNUM 100           //��󶥵���
#define INFINITY 65535       //���з���int�������Ϊ����
typedef int Vertex;          //�����±��ʾ����
typedef int WeightType;      //�ߵ�Ȩ��

//���嶥��洢�������ͽṹ
typedef struct data DataType;
struct data {
	char information;
};

//�����ڽӾ����ͼ����
typedef struct GNode* Graph;
struct GNode {
	int VertexCount;
	int EdgeCount;
	WeightType Weight[MAXNUM][MAXNUM];
	DataType Data[MAXNUM];
};

//�����
typedef struct ENode* Edge;
struct ENode {
	Vertex v1, v2;
	WeightType weight;
};


//��ʼ��ͼ-------------------------------------------------------------------------
//����һ����vertexnum�����㵫�ޱߵ�ͼ
Graph CreateGraph(void)
{
	int vertexnum;
	Graph graph;
	printf("enter vertex count");
	scanf("%d", &vertexnum);

	graph = (Graph)malloc(sizeof(struct GNode));
	if (!graph) {
		printf("error:line 39");
		exit(1);
	}

	graph->VertexCount = vertexnum;
	graph->EdgeCount = 0;
for(int i=0;i<graph->VertexCount;i++)
	for (int j = 0; j < graph->VertexCount; i++) {
		graph->Weight[i][j] = INFINITY;
	}

return graph;
}

//�����
void InsertEdge(Graph graph)
{
	int count;
	printf("enter edge count");
	scanf("%d", &count);
	graph->EdgeCount = count;
	if (count == 0)
		return;
	else {
		Edge edge = (Edge)malloc(sizeof(struct ENode));
		if (edge == NULL) {
			printf("error:line 66");
			exit(1);
		}
		edge->v1 = edge->v2 = 0;
		edge->weight = 0;
	//	Vertex v1, v2; WeightType weight;
		for (int i = 0; i < graph->EdgeCount; i++) {
			scanf("%d %d %d", &edge->v1, &edge->v2, &edge->weight);
			graph->Weight[edge->v1][edge->v2] = edge->weight;
			//����ͼ
			graph->Weight[edge->v2][edge->v1] = edge->weight;
		}
	}
}

Graph BuildGraph(viod)
{
	Graph graph = CreateGraph();
	InsertEdge(graph);

	for (int i = 0; i < graph->VertexCount; i++)
	{
		scanf("%c", &(graph->Data[i]).information);
	}

	return graph;
}
