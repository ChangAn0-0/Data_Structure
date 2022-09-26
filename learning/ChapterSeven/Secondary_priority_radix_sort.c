#include <stdio.h>
#include <stdlib.h>

#define MaxDigit 4
#define Radix 10
typedef int ElementType;

//ͰԪ�ؽڵ�
typedef struct Node* PtrToNode;
struct Node {
	int key;
	PtrToNode next;
};

//Ͱͷ�ڵ�
struct HeadNode {
	PtrToNode head, tail;
};
typedef struct HeadNode Bucket[Radix];

int GetDigit(int x, int D)
{
	//Ĭ�ϴ�λD=1,��λ<=MaxDigit
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

	//��ʼ����
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

		//�ռ�����
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