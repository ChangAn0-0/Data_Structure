#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int ElementType;
typedef int Position;
typedef struct LNode* List;
struct LNode {
	ElementType Data[20];
	Position Last;
};

List MakeEmpty(void)
{
	List L;
	L = (List)malloc(sizeof(struct LNode));
	L->Last = -1;
	return L;
}

bool Insert(int i, ElementType x, List L)
{
	Position j;

	if (L->Last == 9) {
		printf("List is full");
		return false;
	}

	if (i<1 || i>L->Last + 2) {
		printf("error");
		return false;
	}

	for (j = L->Last; j >= i - 1; j--) {
		L->Data[j + 1] = L->Data[j];
	}

	L->Data[i - 1] = x;
	L->Last++;

	return true;
}

void ShowList(List L)
{
	for (int i = 0; i <= L->Last; i++) {
		printf("%d ", L->Data[i]);
	}
	putchar('\n');
}

List Delete(List L, ElementType max, ElementType min)
{
	int i, p;
	for (i = 0; i <= L->Last; i++) {
		if (L->Data[i] < max && L->Data[i] > min)
			break;
	}

	p = i;

	for (i; i <= L->Last; i++) {
		if (!((L->Data[i] < max) && (L->Data[i] > min))) {
			L->Data[p++] = L->Data[i];
		}
	}
	L->Last = p - 1;

	return L;
}

int main(void)
{
	int i = 1, n, ch;
	List ptr = MakeEmpty();

	printf("enter frist number(enter q to quit):");

	while ((ch = scanf("%d", &n)) == 1)
	{
		if (Insert(i, n, ptr) == false) {
			printf("Insert failed");
		}
		i++;

		//while (getchar() != '\n')
			//continue;

		//printf("enter nxet number(enter q to quit):");
	}
	while (getchar() != '\n')
		continue;

	ShowList(ptr);

	int max, min;
	printf("enter max and min:\n");
	scanf("%d %d", &max, &min);

	printf("%d %d\n", max, min);
	Delete(ptr, max, min);

	ShowList(ptr);
	return 0;
}