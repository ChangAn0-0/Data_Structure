#include <stdio.h>

typedef int ElementType;

void Swap(ElementType* a, ElementType* b)
{
	ElementType temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void Selection_sort(ElementType element[], int count)
{
	int i, j;
	for ( i = 0; i < count - 1; i++) {
		int min = i;
		for ( j = i + 1; j < count; j++) {
			if (element[i] > element[j])
				min = j;
		}
		Swap(&element[min],&element[i]);
	}
}

int main(void)
{
	int k;
	ElementType list[10];
	for (int i = 0; i < 10; i++) {
		k = 10 - i;
		list[i] = k;
	}

	for (int i = 0; i < 10; i++) {
		printf("%d ", list[i]);
	}
	putchar('\n');
	Selection_sort(list, 10);
	for (int i = 0; i < 10; i++) {
		printf("%d ", list[i]);
	}
	putchar('\n');

	return 0;
}