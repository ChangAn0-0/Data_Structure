#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { false, true }bool;
//---------------�������ӷ��Ľṹ����-------------------
#define KEYLENGTH 15
typedef char ElementType[KEYLENGTH + 1];
typedef int Index;

typedef struct LNode* PtrToNode;
struct LNode {
	ElementType Data;
	PtrToNode Next;
};
typedef PtrToNode Position;
typedef PtrToNode List;

typedef struct TblNode* HashTable;
struct TblNode {
	int TableSize;
	List Heads;
};
//------------------�ṹ��������------------------------
//����NextPrime�����ش���N��������
int NextPrime(int N)
{
	int i, p = (N % 2) ? N + 2 : N + 1;

	while (1) {
		for (i = (int)sqrt(p); i > 2; i--)
			if (!(p % i))break;
		if (i == 2)break;
		else p += 2;
	}
	return p;
}
//��ʼ������--------------------------------------
HashTable CreatTable(int TableSize)
{
	HashTable H;
	int i;

	H = (HashTable)malloc(sizeof(struct TblNode));
	H->TableSize = NextPrime(TableSize);

	H->Heads = (List)malloc(H->TableSize * sizeof(struct LNode));
	for (i = 0; i < H->TableSize; i++) {
		H->Heads[i].Data[0] = '\0';
		H->Heads[i].Next = NULL;
	}

	return H;
}

//--------------------hash����------------------
int Hash(const char* key, int tablesize)
{
	unsigned int h = 0;
	while (*key != '\0') {
		h = (h << 5) + *key++;
	}

	return h % tablesize;
}

//���Һ���
Position Find(HashTable H, ElementType key)
{
	Position P;
	Index Pos;

	Pos = Hash(key, H->TableSize);
	P = H->Heads[Pos].Next;
	while (P && (strcmp(P->Data, key)))
		P = P->Next;

	return P;
}

//���뺯��
bool Insert(HashTable H, ElementType key)
{
	Position P, NewCell;
	Index Pos;

	P = Find(H, key);
	if (!P) {
		NewCell = (Position)malloc(sizeof(struct LNode));
		strcpy(NewCell->Data, key);
		Pos = Hash(key, H->TableSize);

		NewCell->Next = H->Heads[Pos].Next;
		H->Heads[Pos].Next = NewCell;

		return true;
	}

	else {
		printf("error:��ֵ�Ѵ���");
		return false;
	}
}

void DestroyTable(HashTable H)
{
	int i;
	Position P, Temp;

	for (i = 0; i < H->TableSize; i++)
	{
		P = H->Heads[i].Next;
		while (P) {
			Temp = P->Next;
			free(P);
			P = Temp;
		}
	}

	free(H->Heads);
	free(H);
}

