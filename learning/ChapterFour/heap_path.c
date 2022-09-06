#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef int Data;

typedef struct Node* Heap;
struct Node {
	Data* data;
	int count;
	int max;
};

Heap Creat(int max) 
{
	Heap heap = (Heap)malloc(sizeof(struct Node));
	if (heap == NULL) {
		printf("error:line 15");
		exit(1);
	}
	heap->data = (Data*)malloc(sizeof(Data) * (max + 1));
	if (heap->data == NULL) {
		printf("error:line 20");
		exit(2);
	}
	heap->count = 0;
	heap->max = max;
	heap->data[0] = -10001;

	return heap;
}

void Insert(Heap heap,Data data)
{
	if (heap->count == heap->max) {
		printf("heap is full\n");
		return;
	}
	else {
		int i = ++heap->count;

		while (data < heap->data[i / 2]) {
			heap->data[i] = heap->data[i / 2];
			i /= 2;
		}
		heap->data[i] = data;

		return;
	}
}

int main(void)
{
	int max, n;
	Data data;
	Heap heap;

	printf("enter max,n:\n");
	scanf("%d %d", &max, &n);
	heap = Creat(max);

	printf("enter num:\n");
	for (int i = 0; i < max; i++) {
		scanf("%d", &data);
		Insert(heap, data);
	}

	printf("enter mark:\n");
	int mark;
	for (int i = 0; i < n; i++) {
		scanf("%d", &mark);
	//	printf("%d", heap->data[mark]);
		while (mark > 0) {
			printf("%d ", heap->data[mark]);
			mark /= 2;
		}
		putchar('\n');
	}

	return 0;
}
