#include <stdio.h>
typedef int ElementType;

void Swap(ElementType* a, ElementType* b)
{
	ElementType temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void Insertion_Sort(ElementType element[], int count)
{
	ElementType temp; int j;
	for (int i = 1; i < count; i++) {
		temp = element[i];
		for ( j = i; j >= 0; j--) {
			if (temp < element[j - 1]) {
				element[j] = element[j - 1];
			}
			else break;
		}
		element[j] = temp;
	}
}

ElementType Median3(ElementType element[], int left, int right)
{
	int center = (left + right) / 2;

	if (element[left] > element[center])
		Swap(&element[left], &element[center]);
	if (element[left] > element[right])
		Swap(&element[left], &element[right]);
	if (element[right] < element[center])
		Swap(&element[right], &element[center]);

	Swap(&element[right-1], &element[center]);
	return element[right - 1];
}

void Quick_Sort_Implementation(ElementType element[], int left, int right)
{
	ElementType pivot;
	int cutoff = 10, low, high;
	if (cutoff <= right - left + 1) {
		pivot = Median3(element, left, right);
		low = left; high = right - 1;

		while (1) {
			while (element[++low] < pivot);
			while (element[--high] > pivot);
			if (low < high) {
				Swap(&element[low], &element[high]);
			}
			else
				break;
		}
		Swap(&element[low], &element[right-1]);
		Quick_Sort_Implementation(element, left, low - 1);
		Quick_Sort_Implementation(element, low + 1, right);
	}
	else {
		Insertion_Sort(element + left, right - left + 1);
	}
}


void Quick_Sort(ElementType element[], int count)
{
	Quick_Sort_Implementation(element, 0, count - 1);
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
	Quick_Sort(list, 100);
	for (int i = 0; i < 100; i++) {
		printf("%d ", list[i]);
	}
	putchar('\n');

	return 0;
}