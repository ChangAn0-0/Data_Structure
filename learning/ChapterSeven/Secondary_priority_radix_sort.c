#include <stdio.h>
#include <stdlib.h>

#define MaxDigit 4
#define Radix 10
typedef int ElementType;

//桶元素节点
typedef struct Node* PtrToNode;
struct Node {
	int key;
	PtrToNode next;
};

//桶头节点
struct HeadNode {
	PtrToNode head, tail;
};
typedef struct HeadNode Bucket[Radix];

int GetDigit(int x, int D)
{
	//默认次位D=1,主位<=MaxDigit
	int d, i;

	for (i = 1; i <= D; i++) {
		d = x % Radix;
		x /= Radix;
	}

	return d;
}

void LSDRadixSort(ElementType element[], int count)
{
	int D, Di, i;
	Bucket B;
	PtrToNode tmp, p, List = NULL;

	for (i = 0; i < Radix; i++)
		B[i].head = B[i].tail = NULL;

	for (i = 0; i < count; i++) {
		tmp = (PtrToNode)malloc(sizeof(struct Node));
		tmp->key = element[i];
		tmp->next = List;
		List = tmp;
	}

	//开始排序
	for (D = 1; D <= MaxDigit; D++) {
		p = List;
		while (p) {
			Di = GetDigit(p->key, D);
			tmp = p; p = p->next;

			tmp->next = NULL;
			if (B[Di].head == NULL)
				B[Di].head = B[Di].tail = tmp;
			else {
				B[Di].tail->next = tmp;
				B[Di].tail = tmp;
			}
		}

		//收集过程
		List = NULL;
		for (Di = Radix - 1; Di >= 0; Di--) {
			if (B[Di].head) {
				B[Di].tail->next = List;
				List = B[Di].head;
				B[Di].head = B[Di].tail = NULL;
			}
		}
	}

	for (i = 0; i < count; i++) {
		tmp = List;
		List = List->next;
		element[i] = tmp->key;
		free(tmp);
	}
}
////