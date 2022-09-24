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
	while (right <= rightend)
		temp[tempstart++] = element[right++];

//	for (int i = 0; i < count; i++, rightend--)
//		element[rightend] = temp[rightend];
}

void Msort_Pass(ElementType element[], ElementType temp[], int count, int length)
{
	int i;
	for (i = 0; i < count - 2 * length; i += 2 * length)
		Merge(element, temp, i, i + length, i + 2 * length - 1);
	if (i < count - length)
		Merge(element, temp, i, i + length, count - 1);
	else
		for (int j = i; j < count; j++)temp[j] = element[j];
}

void Non_Recusive_Merge_Sort(ElementType element[], int count)
{
	int length = 1;
	ElementType* temp = (ElementType*)malloc(count * sizeof(ElementType));
	if (temp != NULL) {

		while (length < count) {
			Msort_Pass(element, temp, count, length);
			length *= 2;
			Msort_Pass(temp, element, count, length);
			length *= 2;
		}
		free(temp);
	}
	else
		printf("error:%d", __LINE__);
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
	Non_Recusive_Merge_Sort(list, 100);
	for (int i = 0; i < 100; i++) {
		printf("%d ", list[i]);
	}
	putchar('\n');

	return 0;
}