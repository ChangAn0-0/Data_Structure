#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { false, true }bool;
//---------------�������ӷ��Ľṹ����-------------------
#define KEYLENGTH 20
typedef char ElementType[KEYLENGTH + 1];
typedef int Index;

typedef struct LNode* PtrToNode;
struct LNode {
	ElementType Data;
	int Count;
	PtrToNode Next;
};
typedef PtrToNode Position;
typedef PtrToNode List;

typedef struct TblNode* HashTable;
struct TblNode {
	int TableSize;
	List Heads;
};

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

//���뵥�ʲ�ͳ�ƴ�Ƶ--------------
void InsertAndCount(HashTable H, ElementType key)
{
	Position P, NewCell;
	Index Pos;
	P = Find(H, key);
	if (!P) {
		NewCell = (Position)malloc(sizeof(struct LNode));
		strcpy(NewCell->Data, key);
		NewCell->Count = 1;
		Pos = Hash(key, H->TableSize);

		NewCell->Next = H->Heads[Pos].Next;
		H->Heads[Pos].Next = NewCell;
		H->Heads[Pos].Count++;
	}

	else {
		P->Count++;
	}

}

//�жϺϷ��ĵ����ַ�
bool IsWordChar(char c)
{
	if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9' || c == '_')
		return true;
	else
		return false;
}

//��ȡһ������------------------------------------
#define MAXWORDLEN 80
int GetAWord(FILE* fp, ElementType word)
{
	char tempword[MAXWORDLEN + 1], c;
	int len = 0;

	c = fgetc(fp);
	while (!feof(fp)) {
		if (IsWordChar(c))
			tempword[len++] = c;
		c = fgetc(fp);

		if (len && !IsWordChar(c))
			break;
	}
	tempword[len] = '\0';
	if (len > KEYLENGTH) {
		tempword[KEYLENGTH] = '\0';
		len = KEYLENGTH;
	}

	strcpy(word, tempword);
	return len;
}

//��ʾ��Ƶ���������ı��������е���
void Show(HashTable H, double percent)
{
	int diffwordcount = 0;
	int maxf = 0;
	int* diffwords;
	int maxCollision = 0; 
	int minCollision = 100;
	Position L;
	int i, j, k, lowerbound, count = 0;

	for (i = 0; i < H->TableSize; i++) {
		diffwordcount += H->Heads[i].Count;

		if (maxCollision < H->Heads[i].Count)
			maxCollision = H->Heads[i].Count;
		if (minCollision > H->Heads[i].Count)
			minCollision = H->Heads[i].Count;

		L = H->Heads[i].Next;
		while (L) {
			if (maxf < L->Count)maxf = L->Count;
			L = L->Next;
		}
	}

	printf("����%d����ͬ���ʣ���Ƶ�����%d;\n", diffwordcount, maxf);
	printf("����ͻ����%d,��С��ͻ����%d.\n", maxCollision, minCollision);

	diffwords = (int*)malloc((maxf + 1) * sizeof(int));
	for (i = 0; i <= maxf; i++)
		diffwords[i] = 0;
	for (i = 0; i < H->TableSize; i++) {
		L = H->Heads[i].Next;
		while (L) {
			diffwords[L->Count]++;
			L = L->Next;
		}
	}

	lowerbound = (int)(diffwordcount * percent);
	for (i = maxf; i >= 1 && count < lowerbound; i--)
		count += diffwords[i];

	for (j = maxf; j >= i; j--) {
		for (k = 0; k < H->TableSize; k++) {
			L = H->Heads[k].Next;
			while (L) {
				if (j == L->Count)
					printf("%-15s:%d\n", L->Data, L->Count);
				L = L->Next;
			}
		}
	}

	free(diffwords);
}

//����ɢ�б�
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

//������----------------------------------
int main(void)
{
	FILE* fp;
	HashTable H;
	ElementType word;
	int TableSize = 100;
	int length, wordcount = 0;
	char document[30] = "HarryPoter.txt";

	H = CreatTable(TableSize);
	if ((fp = fopen(document, "r")) == NULL)
		printf("�޷����ļ�\n");

	while (!feof(fp)) {
		length = GetAWord(fp, word);
		if (length > 3) {
			wordcount++;
			InsertAndCount(H, word);
		}
	}

	fclose(fp);

	printf("���ĵ�������%d����Ч����", wordcount);
	Show(H, 10.0 / 100);
	DestroyTable(H);
	return 0;
}