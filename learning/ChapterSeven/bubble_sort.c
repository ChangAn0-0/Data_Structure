#include <stdio.h>

typedef int ElementType;

void Swap(ElementType *a, ElementType *b)
{
	ElementType temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void Bubble_sort(ElementType element[], int count)
{
	_Bool flag = 0;
	for (int p = count - 1; p >= 0; p--) {
		flag = 0;
		for (int i = 0; i < p; i++) {
			if (element[i] > element[i + 1])
				Swap(&element[i], &element[i + 1]);
			flag = 1;
		}
		if (flag == 0)
			break;
	}
}

int main(void)
{
	int k;
	ElementType list[10];
	for (int i=0; i <10; i++) {
		k = 10 - i;
		list[i] = k;
	}

	for (int i = 0; i < 10; i++) {
		printf("%d ", list[i]);
	}
	putchar('\n');
	Bubble_sort(list, 10);
	for (int i = 0; i < 10; i++) {
		printf("%d ", list[i]);
	}
	putchar('\n');

	return 0;
}
