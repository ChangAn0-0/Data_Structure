#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1001
typedef int Data;
#define Swap(a,b) a^=b,b^=a,a^=b;

typedef int Position;
typedef struct LNode* PtrToLNode;
struct LNode {
	Data data[MAXSIZE];
	Position Last;
};
typedef PtrToLNode Tree;

int NCA(int p1, int p2) {
	while (p1 != p2) {
		if (p1 > p2) {
			Swap(p1,p2)
		}
		while (p2 > p1)
			p2 /= 2;
	}

	return p1;
}