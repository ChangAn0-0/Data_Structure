#include <stdio.h>
typedef int ElementType;

void PercDown(ElementType element[], int p, int count)
{
	int parent, child;
	ElementType temp;

	temp = element[p];
	for (parent = p; parent * 2 + 1 < count; parent = child) {
		child = parent * 2 + 1;
		if (child != count - 1 && element[child] < element[child + 1])
			child++;
		if (temp < element[child])
			element[parent] = element[child];
		else break;
	}
	element[parent] = temp;
}

void Swap(ElementType* a, ElementType* b)
{
	ElementType temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void Heap_sort(ElementType element[], int count)
{
	for (int i = count / 2 - 1; i >= 0; i--) {
		PercDown(element, i, count);
	}

	for (int i = count - 1; i > 0; i--) {
		Swap(&element[0], &element[i]);
		PercDown(element, 0, i);
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
	Heap_sort(list, 10);
	for (int i = 0; i < 10; i++) {
		printf("%d ", list[i]);
	}
	putchar('\n');

	return 0;
}

