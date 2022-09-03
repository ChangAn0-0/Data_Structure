#include <stdio.h>

typedef enum{false,true}bool;

//定义最大堆--------------------------
typedef int Data;

typedef struct HeapNode* Heap;

struct HeapNode {
	Data* data;
	int count;
	int maxsize;
};

typedef Heap MaxHeap;

//堆的初始化
MaxHeap CreatHeap(int maxsize)
{
	MaxHeap heap = (MaxHeap)malloc(sizeof(struct HeapNode));
	heap->data = (Data*)malloc((maxsize + 1) * sizeof(Data));
	heap->count = 0;
	heap->maxsize = maxsize;

	heap->data[0] = 1000;//哨兵

	return heap;
}

//判断堆满
bool IsFull(MaxHeap heap)
{
	return (heap->count == heap->maxsize) ? true : false;
}

//判断堆空
bool IsEmpty(MaxHeap heap)
{
	return (heap->count == 0) ? true : false;
}

//最大堆插入
bool Insert(MaxHeap heap, Data data)
{
	if (IsFull(heap)) {
		printf("heap is full");
		return false;
	}

	int i;
	for (i = ++heap->count; data > heap->data[i / 2]; i /= 2) {
		heap->data[i] = heap->data[i / 2];
	}
	heap->data[i] = data;

	return true;
}

//最大堆删除
Data Delete(MaxHeap heap)
{
	if (IsEmpty(heap)) {
		printf("heap is empty");
		return -1;
	}

	int parent, child;
	Data max, temp;

	max = heap->data[1];

	temp = heap->data[heap->count--];
	for (parent = 1; parent * 2 <= heap->count; parent = child) {
		child = parent * 2;
	
		if ((child != heap->count) && (heap->data[child] < heap->data[child + 1])) {
			child++;
		}
	
		if (temp > heap->data[child])
			break;
		else
			heap->data[parent] = heap->data[child];
	}
	heap->data[parent] = temp;

	return max;
}

//最大堆建立
void PercDown(MaxHeap heap, int root)
{
	int parent, child;
	Data temp;

	temp = heap->data[root];
	for (parent = root; parent * 2 < heap->count; parent = child) {
		child = parent * 2;
		if ((child != heap->count) && (heap->data[child] < heap->data[child + 1])) {
			child++;
		}
		if (temp > heap->data[child])break;
		else
			heap->data[parent] = heap->data[child];
		heap->data[parent] = temp;

	}
}

void BuildHeap(MaxHeap heap)
{
	for (int i = heap->count / 2; i > 0; i--)
		PerDown(heap, i);
}
