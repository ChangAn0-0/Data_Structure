#include <stdio.h>
#include <math.h>

//--------------------��������------------------------------------
#define MAXTABLESIZE 100000
typedef int ElementType;
typedef int Index;
typedef Index Position;

 typedef enum{Legitimate,Empty,Deleted}EntryType;
 typedef enum{false,true}bool;

 typedef struct HashEntry Cell;
 struct HashEntry {
	 ElementType Data;
	 EntryType Info;
 };

 typedef struct TblNode* HashTable;
 struct TblNode {
	 int TableSize;
	 Cell* Cells;
 };

 //-----------------------------��ʼ������---------------------
 //����NextPrime�����ش���N��������
 int NextPrime(int N)
 {
	 int i, p = (N % 2) ? N + 2 : N + 1;

	 while (p <= MAXTABLESIZE) {
		 for (i = (int)sqrt(p); i > 2; i--)
			 if (!(p % i))break;
		 if (i == 2)break;
		 else p += 2;
	 }
	 return p;
 }

 //����ɢ�б���ʼ��
 HashTable CreateTable(int TableSize)
 {
	 HashTable H;
	 int i;
	 H = (HashTable)malloc(sizeof(struct TblNode));
	 H->TableSize = NextPrime(TableSize);
	 H->Cells = (Cell*)malloc(sizeof(Cell) * H->TableSize);
	 for (i = 0; i < H->TableSize; i++)
		 H->Cells[i].Info = Empty;

	 return H;
 }
//------------------��ʼ�����--------------------
//--------------------ƽ��̽�ⷨ���뺯��-------------------
 bool Insert(HashTable H, ElementType key)
 {

 }

