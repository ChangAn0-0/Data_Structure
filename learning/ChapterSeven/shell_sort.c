#include <stdio.h>

typedef int ElementType;
void Shell_sort(ElementType element[], int count)
{
	int Sedgewick[] = { 929,505,209,109,41,19,5,1,0 };
	int increment, j;
	ElementType temp;
	for (increment = 0; Sedgewick[increment] > count; increment++);

	for (int D = Sedgewick[increment]; D > 0; D = Sedgewick[increment++]) {
		for (int p = D; p < count; p++) {
			temp = element[p];
			for (j = p; j >=D && element[j - D] > temp; j = j - D) {
				element[j] = element[j - D];
			}
			element[j] = temp;
		}
	}
	
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
	Shell_sort(list, 100);
	for (int i = 0; i < 100; i++) {
		printf("%d ", list[i]);
	}
	putchar('\n');

	return 0;
}//
