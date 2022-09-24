#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

void Merge(ElementType element[], ElementType temp[], int left, int right, int rightend)
{
	int leftend = right - 1;
	int tempstart = left;
	int count = rightend - left + 1;

	while (left <= leftend && right <= rightend) {
		if (element[right] < element[left])
			temp[tempstart++] = element[right++];
		else
			temp[tempstart++] = element[left++];

	}

	while (left <= leftend)
		temp[tempstart++] = element[left++];
	while(right<=rightend)
		temp[tempstart++] = element[right++];

	for (int i = 0; i < count; i++,rightend--)
		element[rightend] = temp[rightend];
}

void Msort(ElementType element[], ElementType temp[], int left, int rightend)
{
	int center;
	if (left < rightend) {
		center = (left + rightend) / 2;
		Msort(element, temp, left, center);
		Msort(element, temp, center + 1, rightend);
		Merge(element, temp, left, center + 1, rightend);
	}
}

void Merge_Sort(ElementType element[], int count)
{
	ElementType* temp = (ElementType*)malloc(count * sizeof(ElementType));
	if (temp!=NULL) {
		Msort(element, temp, 0, count - 1);
		free(temp);
	}
	else 
		printf("error:%d",__LINE__);
}


int main(void)
{
	int k;
	ElementType list[100];
	for (int i = 0; i < 100; i++) {
		k = 100 - i;
		list[i] = k;
	}

	for (int i = 0; i < 100; i++) {
		printf("%d ", list[i]);
	}
	putchar('\n');
	Merge_Sort(list, 100);
	for (int i = 0; i < 100; i++) {
		printf("%d ", list[i]);
	}
	putchar('\n');

	return 0;
}
