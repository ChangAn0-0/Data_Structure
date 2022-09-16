#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef enum{false,true}bool;

#define ENDLESS 65535
#define MaxVertexNum 100
typedef int Vertex;
typedef int WeightType;
typedef int DataType;

static bool visited[MaxVertexNum];

//定义图-----------------------------------------------------
//邻接表节点
typedef struct AdjacencyNode* PtrAdjacencyNode;
struct AdjacencyNode {
	Vertex node;
	WeightType weight;
	PtrAdjacencyNode next;
};

//邻接表表头
struct AjacencyList {
	DataType data;
	PtrAdjacencyNode frist;
};

//定义边
typedef struct ENode* Edge;
struct ENode {
	Vertex v1, v2;
	WeightType weight;
};

//图
typedef struct GNode* Graph;
struct GNode {
	int VertexCount;
	int EdgeCount;
	struct AjacencyList list[MaxVertexNum];
};
//图定义结束-----------------------------------------------------------
//图建立---------------------------------------------------------------
//初始化图
Graph CreatGraph(void)
{
	int vertexcount;
	printf("enter vertex count:\n");
	scanf("%d", &vertexcount);

	Graph graph = (Graph)malloc(sizeof(struct GNode));
	if (!graph) {
		printf("error:line 45");
		exit(1);
	}
	graph->EdgeCount = 0;
	graph->VertexCount = vertexcount;

//	DataType data;
	printf("enter data:\n");
	for (int i = 0; i < graph->VertexCount; i++) {
		scanf("%d", &(graph->list[i]).data);
		(graph->list[i]).frist = NULL;
	}

	return graph;
}

//插入边
void InsertEdge(Graph graph)
{
	int edgecount;
	printf("enter edge count:\n");
	scanf("%d", &edgecount);
	graph->EdgeCount = edgecount;

	if (graph->EdgeCount == 0) {
		printf("edge count is 0\n");
		return;
	}
	else {
		printf("enter edge:\n");
		Edge edge = (Edge)malloc(sizeof(struct ENode));
		if (!edge) {
			printf("error:line 84");
			exit(1);
		}
		for (int i = 0; i < graph->EdgeCount; i++) {
			scanf("%d %d %d", &edge->v1, &edge->v2, &edge->weight);

			PtrAdjacencyNode new = (PtrAdjacencyNode)malloc(sizeof(struct AdjacencyNode));
			if (new == NULL) {
				printf("erroe:line 86\n");
				exit(1);
			}
			new->node = edge->v2;
			new->weight = edge->weight;
			new->next = (graph->list[edge->v1]).frist;
			(graph->list[edge->v1]).frist = new;
			

			//无向图
		    new = (PtrAdjacencyNode)malloc(sizeof(struct AdjacencyNode));
			if (new == NULL) {
				printf("erroe:line 98\n");
				exit(1);
			}
			new->node = edge->v1;
			new->weight = edge->weight;
			new->next = (graph->list[edge->v2]).frist;
			(graph->list[edge->v2]).frist = new;

		}
	}

	return;
}

//建立图
Graph BuildGraph(void)
{
	Graph graph = CreatGraph();

	InsertEdge(graph);

	return graph;
}
//图建立结束-----------------------------------------------------------------
//图输出---------------------------------------------------------------------
void GraphNodePrint(PtrAdjacencyNode frist)
{
	if (frist) {
		printf("-->顶点%d:权重%d", frist->node, frist->weight);
		GraphNodePrint(frist->next);
	}
	return;
}

void ShowGraph(Graph graph)
{
	for (int i = 0; i < graph->VertexCount; i++) {
		printf("顶点%d", i);
		GraphNodePrint((graph->list[i]).frist);
		putchar('\n');
	}
}
//------------------------------------------------------------------------------
//图的历遍-----------------------------------------------------------------------
//访问图
void Visit(Vertex vertex)
{
	printf("node:%d is being accessed\n", vertex);
	return;
}

//深度优先
void DFSList(Graph graph, Vertex vertex)
{
	Visit(vertex);
	visited[vertex] = true;
	for (PtrAdjacencyNode i = (graph->list[vertex]).frist; i ; i=i->next) {
		if (!visited[i->node])
			DFSList(graph, i->node);
	}
}

//广度优先--------------------------------------------------------
typedef struct QNode* Queue;
struct QNode {
	Vertex* elementqueue;
	Vertex front, rear;
	int maxsize;
	int count;
};

//创建队列
Queue CreatQueue(int maxsize)
{
	Queue queue = (Queue)malloc(sizeof(struct QNode));
	if (!queue) {
		printf("erroe:line 182\n");
		exit(1);
	}
	queue->count = 0;
	queue->front = queue->rear = 0;
	queue->maxsize = maxsize;
	queue->elementqueue = (Vertex*)malloc(sizeof(Vertex) * maxsize);
	if (!queue->elementqueue) {
		printf("error:line 190\n");
		exit(1);
	}

	return queue;
}

//判断队列空
bool IsEmpty(Queue queue) {
	if (!queue->count)
		return true;
	else
		return false;
}

//判断队列满
bool IsFull(Queue queue) {
	if ((queue->rear + 1) % queue->maxsize == queue->front)
		return true;
	else
		return false;
}

//插入队列元素
bool InsertQueue(Queue queue,Vertex vertex)
{
	if (IsFull(queue)) {
		printf("queue is full\n");
		return false;
	}
	else {
		queue->count += 1;
		queue->rear = (queue->rear + 1) % queue->maxsize;
		queue->elementqueue[queue->rear] = vertex;
		return true;
	}
}

//删除队列元素
Vertex DeleteQueue(Queue queue)
{
	if (IsEmpty(queue)) {
		printf("queue is empty\n");
		return false;
	}
	else {
		queue->count -= 1;
		queue->front = (queue->front + 1) % queue->maxsize;
		return queue->elementqueue[queue->front];
	}
}

//广度优先历遍
void BFSList(Graph graph, Vertex vertex)
{
	Queue queue = CreatQueue(graph->VertexCount);

	Visit(vertex);
	visited[vertex] = true;
	InsertQueue(queue, vertex);

	Vertex out;
	while (!IsEmpty(queue)) {
		out = DeleteQueue(queue);
		for(PtrAdjacencyNode i=graph->list[out].frist;i;i=i->next){
			if (!visited[i->node]) {
				Visit(i->node);
				visited[i->node] = true;
				InsertQueue(queue, i->node);
			}
		}
	}

	return;
}
//-------------------------------------------------------------------------------------------

void FalseToVisited(Graph graph) {
	for (int i = 0; i < graph->VertexCount; i++) {
		visited[i] = false;
	}
	return;
}

int main(void)
{
	Graph graph = BuildGraph();
	ShowGraph(graph);

	Vertex vertex = 5;

	FalseToVisited(graph);
	DFSList(graph, vertex);
	putchar('\n');
	FalseToVisited(graph);
	BFSList(graph, vertex);
	return 0;
}
