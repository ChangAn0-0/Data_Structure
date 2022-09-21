#include <stdio.h>

typedef int ElementType;

void Insertion_sort(ElementType element[], int count)
{
	ElementType temp;
	int j;
	for (int i = 1; i < count; i++)
	{
		temp = element[i];
		for  (j = i; j > 0 && temp < element[j-1]; j--) {
			element[j] = element[j-1];
		}
		element[j] = temp;
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
	Insertion_sort(list, 10);
	for (int i = 0; i < 10; i++) {
		printf("%d ", list[i]);
	}
	putchar('\n');

	return 0;
}