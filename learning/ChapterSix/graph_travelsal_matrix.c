#define _CRT_SECURE_NO_WARNINGS

#include  <stdio.h>
#include <stdlib.h>

typedef enum{false,true}bool;

#define MaxVertexCount 100
#define ENDLESS 65535
typedef int Vertex;
typedef int WeightType;
typedef int Data;

static bool Visited[MaxVertexCount];


//����ͼ
typedef struct GNode* Graph;
struct GNode {
	int VertexCount;
	int EdgeCount;
	WeightType weight[MaxVertexCount][MaxVertexCount];
	Data data[MaxVertexCount];
}; 

//�����
typedef struct ENode* Edge;
struct ENode {
	Vertex v1, v2;
	WeightType weight;
};

//��ʼ��ͼ
Graph CreatGraph(void)
{
	int vertexnum;
	printf("enter vertex count\n");
	scanf("%d", &vertexnum);

	Graph graph = (Graph)malloc(sizeof(struct GNode));
	if (!graph) {
		printf("error:line 33\n");
		exit(1);
	}

	graph->VertexCount = vertexnum;
	graph->EdgeCount = 0;
	for(int i=0;i<graph->VertexCount;i++)
		for (int j = 0; j < graph->VertexCount; j++) {
			graph->weight[i][j] = ENDLESS;
		}

	return graph;
}

//�����
void InsertEdge(Graph graph)
{
	int edgenum;
	printf("enter edge count\n");
	scanf("%d", &edgenum);
	graph->EdgeCount = edgenum;

	if (edgenum == 0) {
		return;
	}
	else {
		Edge edge = (Edge)malloc(sizeof(struct ENode));
		if (!edge) {
			printf("error:line 59\n");
			exit(1);
		}

		printf("enter edge:\n");
		for (int i = 0; i < graph->EdgeCount; i++) {
			scanf("%d %d %d", &edge->v1, &edge->v2, &edge->weight);
			graph->weight[edge->v1][edge->v2] = edge->weight;
			//����ͼ
			graph->weight[edge->v2][edge->v1] = edge->weight;
		}
	}

	return;
}

//����ͼ
Graph BuildGraph(void)
{
	Graph graph = CreatGraph();
	InsertEdge(graph);

	printf("enter vertex data:\n");
	for (int i = 0; i < graph->VertexCount; i++) {
		scanf("%d", &graph->data[i]);
	}

	for (int i = 0; i < graph->VertexCount; i++) {
		Visited[i] = false;
	}

	return graph;
}

//���ʽڵ�
void Visit(Vertex vertex) 
{
	printf("���ڷ��ʶ���%d\n", vertex);
}

//ͼ������-�������-------------------------------------------------------
void DFSMatrix(Graph graph, Vertex vertex, void(*Visit)(Vertex vertex))
{
	Visit(vertex);
	Visited[vertex] = true;
	for (Vertex i = 0; i < graph->VertexCount; i++)
	{
		if (!Visited[i] && graph->weight[vertex][i] < ENDLESS) {
			DFSMatrix(graph, i, Visit);
		}
	}
}
//-----------------------------------------------------------------------
//ͼ������-�������-------------------------------------------------------------------------------------------
typedef struct Node* Queue;
struct Node {
	Vertex* element;
	int front, rear;
	int maxsize;
};


//��������
Queue CreatQueue(int maxsize)
{
	Queue queue = (Queue)malloc(sizeof(struct Node));
	if (!queue) {
		printf("errror:line 131\n");
		exit(1);
	}

	queue->element = (Vertex*)malloc(sizeof(Vertex) * maxsize);
	queue->front = queue->rear = 0;
	queue->maxsize = maxsize;

	return queue;
}

//�ж϶�����
bool IsFull(Queue queue) 
{
	if ((queue->rear + 1) % queue->maxsize == queue->front)
	{
		return true;
	}
	else
		return false;
}

//�ж϶��п�
bool IsEmpty(Queue queue)
{
	if (queue->front == queue->rear)
		return true;
	else
		return false;
}

//����Ԫ��
bool InsertQueue(Queue queue, Vertex vertex)
{
	if (IsFull(queue)) {
		printf("queue is full");
		return false;
	}
	else {
		queue->rear = (queue->rear + 1) % queue->maxsize;
		queue->element[queue->rear] = vertex;
		return true;
	}
}

//ɾ��Ԫ��
Vertex DeleteQueue(Queue queue)
{
	if (IsEmpty(queue)) {
		printf("queue is empty\n");
		return false;
	}
	else {
		queue->front = (queue->front + 1) % queue->maxsize;
		return queue->element[queue->front];
	}
}

//�����������
void BFSMatrix(Graph graph, Vertex vertex, void(*Visit)(Vertex vertex))
{
	Queue queue = CreatQueue(graph->VertexCount);

	Visit(vertex);
	Visited[vertex] = true;

	InsertQueue(queue, vertex);

	Vertex v;
	while (!IsEmpty(queue)) {
		v = DeleteQueue(queue);
		for (Vertex i = 0; i < graph->VertexCount; i++) {
			if (!Visited[i] && graph->weight[v][i] < ENDLESS) {
				Visit(i);
				Visited[i] = true;
				InsertQueue(queue, i);
			}
		}
	}

	return;
}
//-----------------------------------------------------------------------------------------------------------

int main(void)
{
	Graph graph = BuildGraph();

	for (int i = 0; i < graph->VertexCount; i++) {
		for (int j = 0; j < graph->VertexCount; j++) {
			printf("%7d", graph->weight[i][j]);
		}
		putchar('\n');
	}
	putchar('\n');

	Vertex vertex = 5;
//	DFSMatrix(graph, vertex, Visit);
//	putchar('\n');
	BFSMatrix(graph, vertex, Visit);
	return 0;
}


