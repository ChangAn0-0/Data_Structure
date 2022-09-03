#include <stdio.h>

typedef enum{false,true}bool;

//��������--------------------------
typedef int Data;

typedef struct HeapNode* Heap;

struct HeapNode {
	Data* data;
	int count;
	int maxsize;
};

typedef Heap MaxHeap;

//�ѵĳ�ʼ��
MaxHeap CreatHeap(int maxsize)
{
	MaxHeap heap = (MaxHeap)malloc(sizeof(struct HeapNode));
	heap->data = (Data*)malloc((maxsize + 1) * sizeof(Data));
	heap->count = 0;
	heap->maxsize = maxsize;

	heap->data[0] = 1000;//�ڱ�

	return heap;
}

//�ж϶���
bool IsFull(MaxHeap heap)
{
	return (heap->count == heap->maxsize) ? true : false;
}

//�ж϶ѿ�
bool IsEmpty(MaxHeap heap)
{
	return (heap->count == 0) ? true : false;
}

//���Ѳ���
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

//����ɾ��
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

//���ѽ���
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
